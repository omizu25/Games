//**************************************************
// 
// enemy_division.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_division.h"
#include "enemy_rolling.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEnemyDivision::STD_MOVE = 2.5f;
const float CEnemyDivision::ROT_CHANGE = 0.2f;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyDivision::CEnemyDivision() :
	m_time(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyDivision::~CEnemyDivision()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemyDivision::Init()
{
	m_time = 0;

	// 初期化
	CEnemy::Init();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemyDivision::Uninit()
{
	// 終了
	CEnemy::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemyDivision::Update()
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
	
	m_time++;

	D3DXVECTOR3 posDest = pPlayer->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// ホーミング
	Homing(&pos, pos, posDest, STD_MOVE + FloatRandom(STD_MOVE, 0.0f));

	// 位置の設定
	CObject3D::SetPos(pos);

	D3DXVECTOR3 posDiff = posDest - pos;

	float rot = atan2f(posDiff.x, posDiff.y) + (D3DX_PI * 0.25f);
	rot += (sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * ROT_CHANGE) * (D3DX_PI * 2.0f);

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
void CEnemyDivision::Draw()
{
	// 描画
	CEnemy::Draw();
}

//--------------------------------------------------
// キルされた
//--------------------------------------------------
void CEnemyDivision::Kill()
{
	// 生成
	CEnemyRolling::Create(CObject3D::GetPos());

	// キルされた
	CEnemy::Kill();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CEnemyDivision::Set(const D3DXVECTOR3& pos)
{
	// 位置の設定
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_HomingDivision);

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
}
