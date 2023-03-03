//**************************************************
// 
// enemy_round_trip.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_round_trip.h"
#include "application.h"
#include "player.h"
#include "game.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEnemyRoundTrip::STD_MOVE = 7.5f;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyRoundTrip::CEnemyRoundTrip() : 
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyRoundTrip::~CEnemyRoundTrip()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemyRoundTrip::Init()
{
	// 初期化
	CEnemy::Init();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemyRoundTrip::Uninit()
{
	// 終了
	CEnemy::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemyRoundTrip::Update()
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

	D3DXVECTOR3 pos = CObject3D::GetPos();

	pos += m_move;

	float size = (CObject3D::GetSize().x * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	if (InRange(&pos, D3DXVECTOR3(width, height, 0.0f)))
	{// 範囲内
		m_move *= -1.0f;

		float rot = CObject3D::GetRot();

		rot += D3DX_PI;

		// 角度の正規化
		NormalizeAngle(&rot);

		// 向きの設定
		CObject3D::SetRot(rot);
	}

	// 位置の設定
	CObject3D::SetPos(pos);

	// 更新
	CEnemy::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemyRoundTrip::Draw()
{
	// 描画
	CEnemy::Draw();
}

//--------------------------------------------------
// キルされた
//--------------------------------------------------
void CEnemyRoundTrip::Kill()
{
	// キルされた
	CEnemy::Kill();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CEnemyRoundTrip::Set(const D3DXVECTOR3& pos)
{
	// 位置の設定
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_PaperAirplane);

	// 移動量の設定
	SetMove();

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
}

//--------------------------------------------------
// 移動量の設定
//--------------------------------------------------
void CEnemyRoundTrip::SetMove()
{
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// nullチェック
		return;
	}

	D3DXVECTOR3 pos = pPlayer->GetPos();

	D3DXVECTOR3 posDiff = pos - CObject3D::GetPos();

	float rot = atan2f(posDiff.x, posDiff.y);

	// 角度の正規化
	NormalizeAngle(&rot);

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;

	// 向きの設定
	CObject3D::SetRot(rot);
}
