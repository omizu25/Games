//**************************************************
// 
// time.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "time.h"
#include "utility.h"
#include "application.h"
#include "mode.h"
#include "object2D.h"
#include "sound.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CTime::STD_WIDTH = 50.0f;
const float CTime::STD_HEIGHT = 60.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CTime* CTime::Create(const D3DXVECTOR3& pos, int start, int end)
{
	CTime* pTime = nullptr;

	pTime = new CTime;

	if (pTime != nullptr)
	{// nullチェック
		D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

		// 初期化
		pTime->Init(pos, size);
		pTime->m_start = start;
		pTime->m_end = end;
	}

	return pTime;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTime::CTime() :
	m_pPeriod(nullptr),
	m_start(0),
	m_elapsed(0),
	m_end(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTime::~CTime()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CTime::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_start = 0;
	m_elapsed = 0;
	m_end = 0;

	// 初期化
	CNumberManager::Init(pos, size);
	CNumberManager::SetZero(true);
	CNumberManager::SetZeroDigit(4);

	float interval = size.x * 0.5f;

	// 間隔の設定
	CNumberManager::SetInterval(2, interval);

	// ピリオドの生成
	m_pPeriod = CObject2D::Create();

	D3DXVECTOR3 periodPos = D3DXVECTOR3(pos.x, pos.y + (size.y * 0.5f) - (size.y * 0.25f), 0.0f);
	periodPos.x = pos.x - ((size.x * 2.0f) + (interval * 0.5f));

	// 位置の設定
	m_pPeriod->SetPos(periodPos);

	// サイズの設定
	m_pPeriod->SetSize(size * 0.5f);

	// テクスチャの設定
	m_pPeriod->SetTexture(CTexture::LABEL_Period);

	// フェードの設定
	m_pPeriod->SetFade(0.0f);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTime::Uninit()
{
	// 終了
	CNumberManager::Uninit();

	if (m_pPeriod != nullptr)
	{// nullチェック
		// 終了
		m_pPeriod->Uninit();
		m_pPeriod = nullptr;
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CTime::Release()
{
	// 解放
	CNumberManager::Release();

	if (m_pPeriod != nullptr)
	{// nullチェック
		// 解放
		m_pPeriod->Release();
		m_pPeriod = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CTime::Update()
{
	int time = timeGetTime();

	m_elapsed = (time - m_start);

	int number = m_end - (m_elapsed / 10);

	// 数の変更
	CNumberManager::Set(number);

	if (number < 0)
	{// 時間切れ
		// 数の変更
		CNumberManager::Set(0);

		// モードの変更
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_RESULT);

		// SE
		CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_GameClear);
	}
}

//--------------------------------------------------
// 停止
//--------------------------------------------------
void CTime::Restart()
{
	int time = timeGetTime();

	m_start += (time - (m_elapsed + m_start));
}
