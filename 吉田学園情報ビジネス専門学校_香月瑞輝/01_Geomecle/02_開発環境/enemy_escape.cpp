//**************************************************
// 
// enemy_escape.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_escape.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEnemyEscape::HOMING_SPEED = 4.5f;
const float CEnemyEscape::ESCAPE_SPEED = 10.0f;
const float CEnemyEscape::ROT_CHANGE = 0.1f;
const float CEnemyEscape::STD_INERTIA = 0.07f;
const float CEnemyEscape::FIND_AREA = 100.0f;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyEscape::CEnemyEscape() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDir(false)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyEscape::~CEnemyEscape()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemyEscape::Init()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDir = false;

	// 初期化
	CEnemy::Init();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemyEscape::Uninit()
{
	// 終了
	CEnemy::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemyEscape::Update()
{
	{
		int time = CEnemy::GetTime();

		if (time <= CEnemy::CREATE_TIME)
		{// 生成時間中

			// 色の取得
			D3DXCOLOR col = CObject3D::GetCol();

			col.a = SinCurve(time, 0.1f);

			// 色の設定
			CObject3D::SetCol(col);

			// 当たり判定の設定
			CObject3D::SetCollision(false);

			// 更新
			CEnemy::Update();
			return;
		}

		// 当たり判定の設定
		CObject3D::SetCollision(true);

		D3DXCOLOR col = CObject3D::GetCol();

		col.a = 1.0f;

		// 色の設定
		CObject3D::SetCol(col);
	}

	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// nullチェック
		return;
	}

	D3DXVECTOR3 posDest = pPlayer->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// ホーミング
	Homing(&pos, pos, posDest, HOMING_SPEED);

	// 弾から逃げる
	Escape();

	pos += m_move;

	// 慣性
	m_move.x += (0.0f - m_move.x) * STD_INERTIA;
	m_move.y += (0.0f - m_move.y) * STD_INERTIA;

	float size = (CObject3D::GetSize().x * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	//	範囲内
	InRange(&pos, D3DXVECTOR3(width, height, 0.0f));

	// 位置の設定
	CObject3D::SetPos(pos);

	// 向きの取得
	float rot = CObject3D::GetRot();

	if (m_rotDir)
	{// 右回り
		rot += ROT_CHANGE;
	}
	else
	{// 左回り
		rot -= ROT_CHANGE;
	}

	// 角度の正規化
	NormalizeAngle(&rot);

	// 向きの設定
	CEnemy::SetRot(rot);

	// 更新
	CEnemy::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemyEscape::Draw()
{
	// 描画
	CEnemy::Draw();
}

//--------------------------------------------------
// キルされた
//--------------------------------------------------
void CEnemyEscape::Kill()
{
	// キルされた
	CEnemy::Kill();
}

//--------------------------------------------------
// 弾から逃げる
//--------------------------------------------------
void CEnemyEscape::Escape()
{
	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CObject3D::EType type = CObject3D::TYPE_NONE;
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);
	D3DXVECTOR3 targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float targetSize = 0.0f;
	float targetRot = 0.0f;
	D3DXVECTOR3 pos = CObject3D::GetPos();
	D3DXVECTOR3 posDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;

	for (int i = 0; i < objMax; i++)
	{
		if (pObject[i] == nullptr)
		{// nullチェック
			continue;
		}

		type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_BULLET)
		{// 弾ではない
			continue;
		}

		targetPos = pObject[i]->GetPos();
		targetSize = pObject[i]->GetSize().x * 0.5f;

		if (CollisionCircle(pos, FIND_AREA, targetPos, targetSize))
		{// 当たり判定
			posDiff = targetPos - pos;

			rot = atan2f(posDiff.x, posDiff.y);

			// 向きの取得
			targetRot = pObject[i]->GetRot();

			if (targetRot >= rot)
			{
				rot += D3DX_PI;
			}
			else
			{
				rot -= D3DX_PI;
			}

			m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * ESCAPE_SPEED;
			return;
		}
	}
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CEnemyEscape::Set(const D3DXVECTOR3& pos)
{
	// 位置の設定
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_HomingEscape);

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	
	if (pos.x >= 0.0f)
	{// 右側
		m_rotDir = false;
	}
	else
	{// 左側
		m_rotDir = true;
	}
}
