//**************************************************
// 
// pause.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "pause.h"
#include "menu.h"
#include "object2D.h"
#include "application.h"
#include "game.h"
#include "time.h"
#include "input.h"
#include "sound.h"
#include <assert.h>

//--------------------------------------------------
// 生成
//--------------------------------------------------
CPause* CPause::Create()
{
	CPause* pPause = nullptr;

	pPause = new CPause;

	if (pPause != nullptr)
	{// nullチェック
		pPause->Init();
	}

	return pPause;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CPause::CPause() :
	m_pPause(nullptr),
	m_pMenu(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CPause::~CPause()
{
	assert(m_pPause == nullptr);
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CPause::Init()
{
	{// メニュー
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.65f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(350.0f, 100.0f, 0.0f);

		// メニューの生成
		m_pMenu = CMenu::Create(pos, size, ESelect::SELECT_MAX, 40.0f, true, true);

		// テクスチャの設定
		m_pMenu->SetTexture(ESelect::SELECT_RESUME, CTexture::LABEL_Resume);
		m_pMenu->SetTexture(ESelect::SELECT_RESTART, CTexture::LABEL_Restart);
		m_pMenu->SetTexture(ESelect::SELECT_END, CTexture::LABEL_End);
	}

	{// ポーズ
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.25f, 0.0f);

		// ポーズの生成
		m_pPause = CObject2D::Create();

		// 位置の設定
		m_pPause->SetPos(pos);

		// サイズの設定
		m_pPause->SetSize(D3DXVECTOR3(500.0f, 150.0f, 0.0f));

		// テクスチャの設定
		m_pPause->SetTexture(CTexture::LABEL_Pause);

		// フェードの設定
		m_pPause->SetFade(0.0f);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CPause::Uninit()
{
	if (m_pMenu != nullptr)
	{// nullチェック
		m_pMenu->Uninit();
		delete m_pMenu;
		m_pMenu = nullptr;
	}

	if (m_pPause != nullptr)
	{// nullチェック
		m_pPause->Uninit();
		m_pPause = nullptr;
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CPause::Release()
{
	if (m_pMenu != nullptr)
	{// nullチェック
		m_pMenu->Release();
		delete m_pMenu;
		m_pMenu = nullptr;
	}

	if (m_pPause != nullptr)
	{// nullチェック
		m_pPause->Release();
		m_pPause = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
bool CPause::Update()
{
	// 更新
	m_pMenu->Update();

	// 更新
	m_pPause->Update();

	// 選択
	ESelect select = (ESelect)m_pMenu->Select();

	if (CInput::GetKey()->Trigger(CInput::KEY_PAUSE))
	{// Pキーが押された
		// タイムの再開
		CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
		pGame->GetTime()->Restart();

		// SE
		CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Enter);
		return false;
	}

	switch (select)
	{
	case ESelect::SELECT_NONE:
		return true;	// ポーズ中
		break;

	case ESelect::SELECT_RESUME:
	{
		// タイムの再開
		CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
		pGame->GetTime()->Restart();
	}
		break;

	case ESelect::SELECT_RESTART:
		// モードの変更
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_GAME);
		break;

	case ESelect::SELECT_END:
		// モードの変更
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_TITLE);
		break;

	case ESelect::SELECT_MAX:
	default:
		assert(false);
		break;
	}

	return false;
}
