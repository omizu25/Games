//**************************************************
// 
// enemy_rolling.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_rolling.h"
#include "utility.h"
#include "wall.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEnemyRolling::STD_SIZE = 20.0f;
const float CEnemyRolling::STD_MOVE = 4.0f;
const float CEnemyRolling::ROT_CHANGE = 0.2f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
void CEnemyRolling::Create(const D3DXVECTOR3& pos)
{
	{// 1対目
		CEnemyRolling* pEnemy = nullptr;

		pEnemy = new CEnemyRolling;

		if (pEnemy != nullptr)
		{// nullチェック
			pEnemy->Init();
			pEnemy->Set(pos);
			pEnemy->SetRotDir(false);
		}
	}

	{// 2対目
		CEnemyRolling* pEnemy = nullptr;

		pEnemy = new CEnemyRolling;

		if (pEnemy != nullptr)
		{// nullチェック
			pEnemy->Init();
			pEnemy->Set(pos);
			pEnemy->SetRotDir(true);
		}
	}
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyRolling::CEnemyRolling() :
	m_time(0),
	m_rotDir(false)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyRolling::~CEnemyRolling()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemyRolling::Init()
{
	m_time = 0;

	// 初期化
	CEnemy::Init();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemyRolling::Uninit()
{
	// 終了
	CEnemy::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemyRolling::Update()
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
		}
		else
		{
			// 当たり判定の設定
			CObject3D::SetCollision(true);

			D3DXCOLOR col = CObject3D::GetCol();

			col.a = 1.0f;

			// 色の設定
			CObject3D::SetCol(col);
		}
	}

	m_time++;

	D3DXVECTOR3 pos = CObject3D::GetPos();

	if (m_rotDir)
	{// 右回り
		pos.x += sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * STD_MOVE;
	}
	else
	{// 左回り
		pos.x += -sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * STD_MOVE;
	}
	
	pos.y += cosf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * STD_MOVE;

	float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	// 範囲内
	InRange(&pos, D3DXVECTOR3(width, height, 0.0f));

	// 位置の設定
	CObject3D::SetPos(pos);

	float rot = (sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * ROT_CHANGE) * (D3DX_PI * 2.0f);

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
void CEnemyRolling::Draw()
{
	// 描画
	CEnemy::Draw();
}

//--------------------------------------------------
// キルされた
//--------------------------------------------------
void CEnemyRolling::Kill()
{
	// キルされた
	CEnemy::Kill();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CEnemyRolling::Set(const D3DXVECTOR3& pos)
{
	// 位置の設定
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_HomingDivision);

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));
}

//--------------------------------------------------
// 回転方向の設定
//--------------------------------------------------
void CEnemyRolling::SetRotDir(bool rotDir)
{
	m_rotDir = rotDir;
}
