//**************************************************
// 
// player.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "player.h"
#include "application.h"
#include "utility.h"
#include "input.h"
#include "wall.h"
#include "enemy.h"
#include "game.h"
#include "effect_manager.h"
#include "sound.h"
#include "life.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CPlayer::INVINCIBLE_TIME = 180;
const int CPlayer::RIGOR_TIME = 30;
const float CPlayer::STD_SIZE = 35.0f;
const float CPlayer::STD_MOVE = 6.0f;
const float CPlayer::STD_ROT = 0.1f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = nullptr;

	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{// nullチェック
		pPlayer->Init();
	}

	return pPlayer;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CPlayer::CPlayer() :
	m_time(0),
	m_rotDest(0.0f)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CPlayer::Init()
{
	m_time = 0;
	m_rotDest = 0;

	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject3D::TYPE_PLAYER);

	// 位置の設定
	CObject3D::SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_Player);

	// パーティクル
	CEffectManager::GetInstanse()->Player(CObject3D::GetPos());
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CPlayer::Uninit()
{
	// パーティクル
	CEffectManager::GetInstanse()->Player(CObject3D::GetPos());

	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CPlayer::Update()
{
	// 無敵時間
	InvincibleTime();

	// 移動
	Move();

	// 向き
	Rot();

	// 当たり判定
	Collision();
	
	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CPlayer::Draw()
{
	// 描画
	CObject3D::Draw();
}

//--------------------------------------------------
// 移動
//--------------------------------------------------
void CPlayer::Move()
{
	if (m_time <= RIGOR_TIME)
	{// 硬直時間
		return;
	}

	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(CInput::KEY_PLAYER_LEFT))
	{// 左キーが押された
		vec.x -= 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_PLAYER_RIGHT))
	{// 右キーが押された
		vec.x += 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_PLAYER_UP))
	{// 上キーが押された
		vec.y += 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_PLAYER_DOWN))
	{// 下キーが押された
		vec.y -= 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// 移動してない
		return;
	}

	// 正規化
	D3DXVec3Normalize(&vec, &vec);

	// 目的の向き
	m_rotDest = atan2f(vec.x, vec.y);

	// 角度の正規化
	NormalizeAngle(&m_rotDest);

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// 移動
	pos.x += vec.x * STD_MOVE;
	pos.y += vec.y * STD_MOVE;

	float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	// 範囲内
	InRange(&pos, D3DXVECTOR3(width, height, 0.0f));

	// 位置の設定
	CObject3D::SetPos(pos);
}

//--------------------------------------------------
// 向き
//--------------------------------------------------
void CPlayer::Rot()
{
	float angle = 0.0f;

	float rot = CObject3D::GetRot();

	angle = m_rotDest - rot;

	// 角度の正規化
	NormalizeAngle(&angle);

	//慣性・向きを更新 (減衰させる)
	rot += angle * STD_ROT;

	// 角度の正規化
	NormalizeAngle(&rot);

	// 向きの設定
	CObject3D::SetRot(rot);
}

//--------------------------------------------------
// 無敵時間
//--------------------------------------------------
void CPlayer::InvincibleTime()
{
	if (m_time >= INVINCIBLE_TIME)
	{// 無敵時間は過ぎた
		// 色の設定
		CObject3D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		return;
	}

	m_time++;

	// 色の取得
	D3DXCOLOR col = CObject3D::GetCol();

	col.a = 1.0f - (CosCurve(m_time, 0.1f) * 0.9f);

	// 色の設定
	CObject3D::SetCol(col);
}

//--------------------------------------------------
// 当たり判定
//--------------------------------------------------
void CPlayer::Collision()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();
	float size = CObject3D::GetSize().x * 0.25f;

	CObject3D** pObject = (CObject3D**)GetMyObject(CObject::CATEGORY_3D);
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);
	D3DXVECTOR3 targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float targetSize = 0.0f;
	CEnemy* pEnemy = nullptr;

	for (int i = 0; i < objMax; i++)
	{
		if (pObject[i] == nullptr)
		{// nullチェック
			continue;
		}

		if (!pObject[i]->GetCollision())
		{// 当たり判定をしない
			continue;
		}

		CObject3D::EType type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_ENEMY && type != CObject3D::TYPE_BODY)
		{// 指定の値ではない
			continue;
		}

		targetPos = pObject[i]->GetPos();
		targetSize = pObject[i]->GetSize().x * 0.5f;

		if (CollisionCircle(pos, size, targetPos, targetSize))
		{// 当たり判定
			if (m_time < INVINCIBLE_TIME)
			{// 無敵時間
				if (type == CObject3D::TYPE_ENEMY)
				{// 敵
					pEnemy = (CEnemy*)pObject[i];

					// キル
					pEnemy->Kill();

					// 敵の解放
					pObject[i]->Release();
				}
				return;
			}

			// 解放
			CObject::Release();

			CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
			CLife* pLife = pGame->GetLife();

			// ライフの減少
			pLife->Sub();

			if (pLife->Get() > 0)
			{// 残機ある
				// リセット
				pGame->Reset();
			}
			else
			{// 残機なし
				// モードの変更
				CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_RESULT);

				// SE
				CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_GameOver);
			}
			
			return;
		}
	}
}