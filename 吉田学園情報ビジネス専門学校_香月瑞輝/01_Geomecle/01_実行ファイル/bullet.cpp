//**************************************************
// 
// bullet.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "bullet.h"
#include "application.h"
#include "utility.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "wall.h"
#include "effect_manager.h"
#include "game.h"
#include "sound.h"
#include "circle.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CBullet::SHOT_INTERVAL = 8;
const float CBullet::STD_SIZE = 25.0f;
const float CBullet::STD_MOVE = 15.0f;
const float CBullet::STD_INERTIA = 0.4f;

//==================================================
// 静的メンバ変数
//==================================================
int CBullet::m_time = 0;
float CBullet::m_dest = 0.0f;
float CBullet::m_now = 0.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CBullet* CBullet::Create(float rot)
{
	CBullet* pBullet = nullptr;

	pBullet = new CBullet;

	if (pBullet != nullptr)
	{// nullチェック
		pBullet->Init();
		pBullet->SetMove(rot);
	}

	return pBullet;
}

//--------------------------------------------------
// 発射
//--------------------------------------------------
void CBullet::Shot()
{
	switch (CGame::GetMode())
	{
	case CGame::GAME_NORMAL:
		break;

	case CGame::GAME_SAFETY_AREA:
		if (!CCircle::GetCollision())
		{// 当たってない
			m_dest = 0.0f;
			m_now = 0.0f;
			m_time = 0;
			return;
		}
		break;

	case CGame::GAME_DANGER_AREA:
		if (CCircle::GetCollision())
		{// 当たっている
			m_dest = 0.0f;
			m_now = 0.0f;
			m_time = 0;
			return;
		}
		break;

	case CGame::GAME_NONE:
	case CGame::GAME_MAX:
	default:
		assert(false);
		break;
	}

	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(CInput::KEY_BULLET_LEFT))
	{// 左キーが押された
		vec.x -= 1.0f;
	}

	if (pInput->Press(CInput::KEY_BULLET_RIGHT))
	{// 右キーが押された
		vec.x += 1.0f;
	}

	if (pInput->Press(CInput::KEY_BULLET_UP))
	{// 上キーが押された
		vec.y += 1.0f;
	}

	if (pInput->Press(CInput::KEY_BULLET_DOWN))
	{// 下キーが押された
		vec.y -= 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// 弾の発射していない
		m_dest = 0.0f;
		m_now = 0.0f;
		m_time = 0;
		return;
	}

	if ((m_time % SHOT_INTERVAL) != 0)
	{// インターバル中
		m_time++;
		return;
	}

	if (m_time == 0)
	{// １発目
		// 目的の向き
		m_dest = atan2f(vec.x, vec.y);

		// 角度の正規化
		NormalizeAngle(&m_dest);

		m_now = m_dest;

		// 弾発射
		CBullet::Create(m_now);

		m_time++;
		return;
	}

	m_time++;

	// 目的の向き
	m_dest = atan2f(vec.x, vec.y);

	// 角度の正規化
	NormalizeAngle(&m_dest);

	float angle = m_dest - m_now;

	// 角度の正規化
	NormalizeAngle(&angle);

	// 慣性・向きを更新 (減衰させる)
	m_now += angle * STD_INERTIA;

	// 角度の正規化
	NormalizeAngle(&m_now);

	// 弾発射
	CBullet::Create(m_now);

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Bullet);
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CBullet::CBullet() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CBullet::~CBullet()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CBullet::Init()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject3D::TYPE_BULLET);

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_Bullet);

	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// nullチェック
		return;
	}

	D3DXVECTOR3 pos = pPlayer->GetPos();

	// 位置の設定
	CObject3D::SetPos(pos);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CBullet::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CBullet::Update()
{
	D3DXVECTOR3 pos = CObject3D::GetPos() + m_move;

	// 位置の設定
	CObject3D::SetPos(pos);

	// 更新
	CObject3D::Update();

	{
		float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
		float width = (CWall::STD_WIDTH * 0.5f) - size;
		float height = (CWall::STD_HEIGHT * 0.5f) - size;

		if (InRange(&pos, D3DXVECTOR3(width, height, 0.0f)))
		{// 範囲外
			// 爆発
			CEffectManager::GetInstanse()->Bullet(pos);

			// 解放
			CObject::Release();
			return;
		}
	}

	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CObject3D::EType type = CObject3D::TYPE_NONE;
	D3DXVECTOR3 targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CEnemy* pEnemy = nullptr;
	float targetSize = 0.0f;
	float size = STD_SIZE * 0.5f;
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);

	for (int i = 0; i < objMax; i++)
	{
		if (pObject[i] == nullptr)
		{// nullチェック
			continue;
		}

		type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_ENEMY && type != CObject3D::TYPE_BODY)
		{// 指定のタイプではない
			continue;
		}

		targetPos = pObject[i]->GetPos();
		targetSize = pObject[i]->GetSize().x * 0.5f;

		switch (type)
		{
		case CObject3D::TYPE_BODY:
			if (CollisionCircle(pos, size, targetPos, targetSize))
			{// 当たり判定
				// 解放
				CObject::Release();
				return;
			}
			break;

		case CObject3D::TYPE_ENEMY:
			if (CollisionCircle(pos, size, targetPos, targetSize))
			{// 当たり判定
				pEnemy = (CEnemy*)pObject[i];

				// キル
				pEnemy->Kill();

				// 敵の解放
				pObject[i]->Release();
			}
			break;

		default:
			assert(false);
			break;
		}
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CBullet::Draw()
{
	// 描画
	CObject3D::Draw();
}

//--------------------------------------------------
// 移動量の設定
//--------------------------------------------------
void CBullet::SetMove(float rot)
{
	// 向きの設定
	CObject3D::SetRot(rot);

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;
}