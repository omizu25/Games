//**************************************************
// 
// enemy.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy.h"
#include "enemy_homing.h"
#include "enemy_round_trip.h"
#include "enemy_windmill.h"
#include "enemy_snake_head.h"
#include "enemy_division.h"
#include "enemy_rolling.h"
#include "enemy_escape.h"
#include "effect_manager.h"
#include "application.h"
#include "game.h"
#include "exp.h"
#include "score.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CEnemy::STD_SCORE = 100;
const int CEnemy::CREATE_TIME = 30;
const float CEnemy::STD_SIZE = 35.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEnemy* CEnemy::Create(CEnemy::EType type, const D3DXVECTOR3& pos)
{
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case CEnemy::TYPE_HOMING:
		pEnemy = new CEnemyHoming;
		break;

	case CEnemy::TYPE_ROUNDTRIP:
		pEnemy = new CEnemyRoundTrip;
		break;

	case CEnemy::TYPE_WINDMILL:
		pEnemy = new CEnemyWindmill;
		break;

	case CEnemy::TYPE_SNAKE:
		pEnemy = new CEnemySnakeHead;
		break;

	case CEnemy::TYPE_DIVISION:
		pEnemy = new CEnemyDivision;
		break;

	case CEnemy::TYPE_ESCAPE:
		pEnemy = new CEnemyEscape;
		break;

	case CEnemy::TYPE_ROLLING:
		pEnemy = new CEnemyRolling;
		break;

	case CEnemy::TYPE_MAX:
	case CEnemy::TYPE_NONE:
	default:
		assert(false);
		break;
	}

	if (pEnemy != nullptr)
	{// nullチェック
		pEnemy->Init();
		pEnemy->Set(pos);
		pEnemy->m_type = type;
	}

	return pEnemy;
}

//--------------------------------------------------
// 当たり判定
//--------------------------------------------------
void CEnemy::Collision()
{
	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CObject3D** pTarget = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CEnemy* pEnemy = nullptr;
	CObject3D::EType type = CObject3D::TYPE_NONE;
	CEnemy::EType typeObject = CEnemy::TYPE_NONE;
	CEnemy::EType typeTarget = CEnemy::TYPE_NONE;
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float width = STD_SIZE * 0.35f;

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

		type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_ENEMY)
		{// エネミーではない
			continue;
		}

		pEnemy = (CEnemy*)pObject[i];

		typeObject = pEnemy->GetType();
		
		if (typeObject != CEnemy::TYPE_HOMING
			&& typeObject != CEnemy::TYPE_DIVISION
			&& typeObject != CEnemy::TYPE_ESCAPE)
		{// 指定のエネミーではない
			continue;
		}

		pos = pObject[i]->GetPos();

		for (int j = i + 1; j < objMax; j++)
		{
			if (pTarget[j] == nullptr)
			{// nullチェック
				continue;
			}

			if (!pTarget[j]->GetCollision())
			{// 当たり判定をしない
				continue;
			}

			type = pTarget[j]->GetType();

			if (type != CObject3D::TYPE_ENEMY)
			{// エネミーではない
				continue;
			}

			pEnemy = (CEnemy*)pTarget[j];

			typeTarget = pEnemy->GetType();

			if (typeObject != typeTarget)
			{// 同じエネミーではない
				continue;
			}

			targetPos = pTarget[j]->GetPos();

			if (CollisionArea(pos, width, &targetPos, width))
			{// 当たった
				// 位置の設定
				pTarget[j]->SetPos(targetPos);
			}
		}
	}
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemy::CEnemy() :
	m_time(0),
	m_type(TYPE_NONE)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemy::~CEnemy()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemy::Init()
{
	m_time = 0;
	m_type = TYPE_NONE;

	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject3D::TYPE_ENEMY);

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemy::Uninit()
{
	// 爆発
	CEffectManager::GetInstanse()->Explosion(CObject3D::GetPos());

	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemy::Update()
{
	m_time++;

	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemy::Draw()
{
	// 描画
	CObject3D::Draw();
}

//--------------------------------------------------
// キルされた
//--------------------------------------------------
void CEnemy::Kill()
{
	// 経験値の生成
	CExp::CreateAll(CObject3D::GetPos());

	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

	// スコアの加算
	pGame->GetScore()->Add(STD_SCORE);
}

//--------------------------------------------------
// タイムの取得
//--------------------------------------------------
int CEnemy::GetTime()
{
	return m_time;
}

//--------------------------------------------------
// 種類の取得
//--------------------------------------------------
CEnemy::EType CEnemy::GetType()
{
	return m_type;
}
