//**************************************************
// 
// circle_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "circle_manager.h"
#include "circle.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CCircleManager::MAX_INTERVAL = 180;
const int CCircleManager::MIN_INTERVAL = 60;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CCircleManager* CCircleManager::Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size)
{
	CCircleManager* pManager = nullptr;

	pManager = new CCircleManager;

	if (pManager != nullptr)
	{// nullチェック
		pManager->Init(pos, size);
	}

	return pManager;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CCircleManager::CCircleManager() :
	m_pCircle(nullptr),
	m_time(0),
	m_interval(0),
	m_areaTop(0.0f),
	m_areaBottom(0.0f),
	m_areaRight(0.0f),
	m_areaLeft(0.0f)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CCircleManager::~CCircleManager()
{
	assert(m_pCircle == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CCircleManager::Init(const D3DXVECTOR3& pos, const D3DXVECTOR2& size)
{
	m_time = 0;
	m_interval = IntRandom(MAX_INTERVAL, MIN_INTERVAL);

	m_pCircle = nullptr;

	m_areaTop = pos.y + size.y;
	m_areaBottom = pos.y - size.y;
	m_areaRight = pos.x + size.x;
	m_areaLeft = pos.x - size.x;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CCircleManager::Uninit()
{
	if (m_pCircle != nullptr)
	{// nullチェック
		m_pCircle->Uninit();
		m_pCircle = nullptr;
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CCircleManager::Release()
{
	if (m_pCircle != nullptr)
	{// nullチェック
		m_pCircle->Release();
		m_pCircle = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CCircleManager::Update()
{
	if (m_pCircle == nullptr)
	{// 円がない
		m_time++;

		if (m_time <= m_interval)
		{// インターバル中
			return;
		}

		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pos.x = FloatRandom(m_areaRight, m_areaLeft);
		pos.y = FloatRandom(m_areaTop, m_areaBottom);

		pos.x = FloatRandom(m_areaRight, m_areaLeft);
		pos.y = FloatRandom(m_areaTop, m_areaBottom);

		// 生成
		m_pCircle = CCircle::Create(pos);

		return;
	}

	if (m_pCircle->Appear())
	{// 消滅した
		m_time = 0;
		m_interval = IntRandom(MAX_INTERVAL, MIN_INTERVAL);

		// 解放
		m_pCircle->Release();
		m_pCircle = nullptr;
		return;
	}

	/* 消滅してない */

	if (m_pCircle->GetAppear() == CCircle::CIRCLE_DISAPPEAR)
	{// 消滅中
		return;
	}

	m_time++;

	int life = m_pCircle->GetLife();

	if (m_time >= life)
	{// 寿命を超した
		// 消滅
		m_pCircle->SetAppear(CCircle::CIRCLE_DISAPPEAR);
	}
}
