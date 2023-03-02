//**************************************************
// 
// circle.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "circle.h"
#include "circle_safety.h"
#include "circle_danger.h"
#include "application.h"
#include "player.h"
#include "game.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CCircle::STD_SIZE = 200.0f;
const float CCircle::APPEAR_SPEED = 5.0f;
const float CCircle::DISAPPEAR_SPEED = 1.5f;

//==================================================
// 静的メンバ変数
//==================================================
bool CCircle::m_collision = false;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CCircle* CCircle::Create(const D3DXVECTOR3& pos)
{
	CCircle* pCircle = nullptr;

	switch (CGame::GetMode())
	{
	case CGame::GAME_SAFETY_AREA:
		pCircle = new CCircleSafety;
		break;

	case CGame::GAME_DANGER_AREA:
		pCircle = new CCircleDanger;
		break;

	case CGame::GAME_NONE:
	case CGame::GAME_MAX:
	default:
		assert(false);
		break;
	}

	if (pCircle != nullptr)
	{// nullチェック
		pCircle->Init();
		pCircle->SetPos(pos);
	}

	return pCircle;
}

//--------------------------------------------------
// 当たり判定
//--------------------------------------------------
void CCircle::Collision()
{
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// nullチェック
		return;
	}

	m_collision = false;

	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CObject3D** pEnemy = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CObject3D::EType type = CObject3D::TYPE_NONE;
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);
	CCircle* pCircle = nullptr;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float size = 0.0f;
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 enemyPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float enemySize = 0.0f;

	for (int i = 0; i < objMax; i++)
	{
		if (pObject[i] == nullptr)
		{// nullチェック
			continue;
		}

		type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_CIRCLE)
		{// 指定のタイプではない
			continue;
		}

		pos = pObject[i]->GetPos();
		size = pObject[i]->GetSize().x * 0.5f;

		if (CollisionCircle(pos, size, playerPos, 0.0f))
		{// 当たり判定
			if (CGame::GetMode() == CGame::GAME_SAFETY_AREA)
			{// 安全エリアモード
				pCircle = (CCircle*)pObject[i];

				if (pCircle->GetAppear() != CIRCLE_DISAPPEAR)
				{// 消滅中ではない
					// 消滅
					pCircle->SetAppear(CIRCLE_DISAPPEAR);
				}
			}

			m_collision = true;
		}

		for (int j = 0; j < objMax; j++)
		{
			if (pEnemy[j] == nullptr)
			{// nullチェック
				continue;
			}

			type = pEnemy[j]->GetType();

			if (type != CObject3D::TYPE_ENEMY)
			{// 指定のタイプではない
				continue;
			}

			enemyPos = pEnemy[j]->GetPos();
			enemySize = pEnemy[j]->GetSize().x * 0.5f;

			if (CollisionArea(pos, size, &enemyPos, enemySize))
			{// 当たった
				// 位置の設定
				pEnemy[j]->SetPos(enemyPos);
			}
		}
	}
}

//--------------------------------------------------
// 当たっているかどうかの取得
//--------------------------------------------------
bool CCircle::GetCollision()
{
	return m_collision;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CCircle::CCircle() :
	m_time(0),
	m_countDownTime(0),
	m_life(0),
	m_appear(CIRCLE_NONE),
	m_countDown(false)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CCircle::~CCircle()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CCircle::Init()
{
	m_time = 0;
	m_countDownTime = 0;
	m_life = 0;
	m_appear = CIRCLE_APPEAR;
	m_countDown = false;

	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject3D::TYPE_CIRCLE);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_Circle);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CCircle::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CCircle::Update()
{
	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CCircle::Draw()
{
	// 描画
	CObject3D::Draw();
}

//--------------------------------------------------
// 出現か消滅
//--------------------------------------------------
bool CCircle::Appear()
{
	switch (m_appear)
	{
	case CIRCLE_NONE:
		break;

	case CIRCLE_APPEAR:
	{
		D3DXVECTOR3 size = CObject3D::GetSize();

		size.x += APPEAR_SPEED;
		size.y += APPEAR_SPEED;

		if ((size.x >= STD_SIZE) && (size.y >= STD_SIZE))
		{// 指定の値以上
			size.x = STD_SIZE;
			size.y = STD_SIZE;

			m_appear = CIRCLE_NONE;
			m_time = 0;
			m_countDown = true;
		}

		// サイズの設定
		CObject3D::SetSize(size);
	}
		break;

	case CIRCLE_DISAPPEAR:
	{
		if (m_countDown)
		{// カウントダウンをする
			m_time++;

			if (m_time >= m_countDownTime)
			{// カウントダウン終わり
				m_time = 0;
				m_countDown = false;
			}

			return false;	// 消滅してない
		}

		D3DXVECTOR3 size = CObject3D::GetSize();

		size.x -= DISAPPEAR_SPEED;
		size.y -= DISAPPEAR_SPEED;

		// サイズの設定
		CObject3D::SetSize(size);

		if ((size.x <= 0.0f) && (size.y <= 0.0f))
		{// 指定の値以下
			return true;	// 消滅した
		}
	}
		break;

	case CIRCLE_MAX:
	default:
		assert(false);
		break;
	}

	return false;	// 消滅してない
}

//--------------------------------------------------
// 出現か消滅の設定
//--------------------------------------------------
void CCircle::SetAppear(ECircle appear)
{
	assert(appear >= CIRCLE_NONE && appear < CIRCLE_MAX);
	m_appear = appear;
}

//--------------------------------------------------
// カウントダウンの取得
//--------------------------------------------------
bool CCircle::GetCountDown()
{
	return m_countDown;
}

//--------------------------------------------------
// カウントダウンのタイム設定
//--------------------------------------------------
void CCircle::SetTime(int time)
{
	m_countDownTime = time;
}

//--------------------------------------------------
// 寿命の設定
//--------------------------------------------------
void CCircle::SetLife(int life)
{
	m_life = life;
}

//--------------------------------------------------
// 寿命の取得
//--------------------------------------------------
int CCircle::GetLife()
{
	return m_life;
}

//--------------------------------------------------
// 出現か消滅の取得
//--------------------------------------------------
CCircle::ECircle CCircle::GetAppear()
{
	return m_appear;
}
