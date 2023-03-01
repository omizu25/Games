//**************************************************
// 
// enemy_snake_head.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_snake_head.h"
#include "enemy_snake_body.h"
#include "application.h"
#include "utility.h"
#include "game.h"
#include "player.h"
#include "wall.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CEnemySnakeHead::MAX_BODY = 25;
const int CEnemySnakeHead::IDX_PARENT = 0;
const float CEnemySnakeHead::STD_SIZE = 35.0f;
const float CEnemySnakeHead::STD_MOVE = 2.0f;
const float CEnemySnakeHead::AMPLITUDE_WIDTH = 3.0f;
const float CEnemySnakeHead::AMPLITUDE_SPEED = 2.0f;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemySnakeHead::CEnemySnakeHead() :
	m_time(0),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemySnakeHead::~CEnemySnakeHead()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemySnakeHead::Init()
{
	m_time = 0;

	// 初期化
	CEnemy::Init();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemySnakeHead::Uninit()
{
	for (int i = 0; i < MAX_BODY; i++)
	{
		if (m_pBody[i] == nullptr)
		{// nullチェック
			continue;
		}

		// 解放
		m_pBody[i]->Release();
		m_pBody[i] = nullptr;
	}

	if (m_pBody != nullptr)
	{// nullチェック
		delete[] m_pBody;
		m_pBody = nullptr;
	}

	// 終了
	CEnemy::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemySnakeHead::Update()
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

			for (int i = 0; i < MAX_BODY; i++)
			{
				if (m_pBody[i] == nullptr)
				{// nullチェック
					continue;
				}

				// 色の取得
				D3DXCOLOR colBody = m_pBody[i]->GetCol();

				colBody.a = SinCurve(time, 0.1f) * 0.5f;

				// 色の設定
				m_pBody[i]->SetCol(colBody);

				// 当たり判定の設定
				m_pBody[i]->SetCollision(false);
			}

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

		for (int i = 0; i < MAX_BODY; i++)
		{
			if (m_pBody[i] == nullptr)
			{// nullチェック
				continue;
			}

			// 色の取得
			D3DXCOLOR colBody = m_pBody[i]->GetCol();

			colBody.a = 1.0f;

			// 色の設定
			m_pBody[i]->SetCol(colBody);

			// 当たり判定の設定
			m_pBody[i]->SetCollision(true);
		}
	}

	m_time++;

	// 移動量の設定
	SetMove();

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// 前回の位置の保存
	m_posOld = pos;

	pos.x += m_move.x;
	pos.y += m_move.y;

	float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	//	範囲内
	InRange(&pos, D3DXVECTOR3(width, height, 0.0f));

	// 位置の設定
	CObject3D::SetPos(pos);

	if (m_pBody[IDX_PARENT] != nullptr)
	{// nullチェック
		// 目的の位置の設定
		m_pBody[IDX_PARENT]->SetPosDest(m_posOld);
	}

	for (int i = 0; i < MAX_BODY; i++)
	{
		if (m_pBody[i] == nullptr || i == IDX_PARENT)
		{// nullチェック
			continue;
		}

		int parent = i - 1;
		D3DXVECTOR3 posOld = m_pBody[parent]->GetPosOld();

		// 目的の位置の設定
		m_pBody[i]->SetPosDest(posOld);
	}

	// 更新
	CEnemy::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemySnakeHead::Draw()
{
	// 描画
	CEnemy::Draw();
}

//--------------------------------------------------
// 前回の位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CEnemySnakeHead::GetPosOld() const
{
	return m_posOld;
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CEnemySnakeHead::Set(const D3DXVECTOR3& pos)
{
	// 位置の設定
	CObject3D::SetPos(pos);

	m_posOld = pos;

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_Bullet);

	// 移動量の設定
	SetMove();

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f));

	m_pBody = new CEnemySnakeBody*[MAX_BODY];

	for (int i = 0; i < MAX_BODY; i++)
	{
		m_pBody[i] = nullptr;
	}

	for (int i = 0; i < MAX_BODY; i++)
	{
		// 生成
		m_pBody[i] = CEnemySnakeBody::Create();
		m_pBody[i]->SetPos(pos);
		m_pBody[i]->SetPosDest(pos);
	}
}

//--------------------------------------------------
// キルされた
//--------------------------------------------------
void CEnemySnakeHead::Kill()
{
	// キルされた
	CEnemy::Kill();
}

//--------------------------------------------------
// 移動量の設定
//--------------------------------------------------
void CEnemySnakeHead::SetMove()
{
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();
	
	if (pPlayer == nullptr)
	{// nullチェック
		return;
	}

	float fRotMove, fRotDest, fRotDiff;

	// 現在の移動方向(角度)
	fRotMove = atan2f(m_move.x, m_move.y);

	// 目的の移動方向(角度)
	fRotDest = atan2f(pPlayer->GetPos().x - GetPos().x, pPlayer->GetPos().y - GetPos().y);

	fRotDiff = fRotDest - fRotMove;	// 目的の移動方向までの差分

	// 角度の正規化
	NormalizeAngle(&fRotDiff);

	fRotMove += fRotDiff;	// 移動方向(角度)の補正

	// 角度の正規化
	NormalizeAngle(&fRotMove);

	float sinCurve = sinf(D3DXToRadian(m_time * AMPLITUDE_SPEED)) * AMPLITUDE_WIDTH;

	m_move.x = (sinf(fRotMove) * (STD_MOVE + FloatRandom(STD_MOVE, 0.0f))) + (sinCurve * sinf(fRotMove + D3DX_PI * 0.5f));
	m_move.y = (cosf(fRotMove) * (STD_MOVE + FloatRandom(STD_MOVE, 0.0f))) + (sinCurve * cosf(fRotMove + D3DX_PI * 0.5f));

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move.x = (sinf(fRotMove) * STD_MOVE) + (sinCurve * sinf(fRotMove + D3DX_PI * 0.5f));
	move.y = (cosf(fRotMove) * STD_MOVE) + (sinCurve * cosf(fRotMove + D3DX_PI * 0.5f));

	float rot = atan2f(move.x, move.y);

	// 角度の正規化
	NormalizeAngle(&rot);

	// 向きの設定
	CObject3D::SetRot(rot);
}
