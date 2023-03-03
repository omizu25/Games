//**************************************************
// 
// title.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "title.h"
#include "application.h"
#include "camera.h"
#include "object2D.h"
#include "effect_manager.h"
#include "wall.h"
#include "utility.h"
#include "menu.h"
#include "sound.h"
#include "game.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTitle::CTitle() : CMode(CMode::MODE_TITLE),
	m_pMenu(nullptr),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_time(0),
	m_partCnt(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CTitle::Init()
{
	m_time = 0;
	m_partCnt = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	CObject2D* pTitle = CObject2D::Create();
	pTitle->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.3f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f));
	pTitle->SetSize(D3DXVECTOR3(750.0f, 250.0f, 0.0f));
	pTitle->SetTexture(CTexture::LABEL_Title);
	pTitle->SetFade(0.0f);

	{// メニュー
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.85f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(350.0f, 100.0f, 0.0f);

		// メニューの生成
		m_pMenu = CMenu::Create(pos, size, ESelect::SELECT_MAX, 50.0f, true, true);

		// 枠の設定
		m_pMenu->SetFrame(D3DXVECTOR3(600.0f, (float)CApplication::SCREEN_HEIGHT, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// テクスチャの設定
		m_pMenu->SetTexture(ESelect::SELECT_NORMAL, CTexture::LABEL_Normal);
		m_pMenu->SetTexture(ESelect::SELECT_SAFETY_AREA, CTexture::LABEL_SafetyArea);
		m_pMenu->SetTexture(ESelect::SELECT_DANGER_AREA, CTexture::LABEL_DangerArea);
		m_pMenu->SetTexture(ESelect::SELECT_RANKING, CTexture::LABEL_Rankig_Title);
	}

	// BGM
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_BGM_Title);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTitle::Uninit()
{
	if (m_pMenu != nullptr)
	{// nullチェック
		m_pMenu->Uninit();
		delete m_pMenu;
		m_pMenu = nullptr;
	}

	// 全ての解放
	CObject::ReleaseAll(false);

	CApplication* pApp = CApplication::GetInstanse();

	// テクスチャの破棄
	pApp->GetTexture()->ReleaseAll();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CTitle::Update()
{
	// 更新
	CObject::UpdateAll();

	// エフェクト
	Effect();

	// 選択
	CTitle::ESelect select = (ESelect)m_pMenu->Select();

	if (m_time >= CMode::FADE_TIME)
	{// フェード時間
		switch (select)
		{
		case ESelect::SELECT_NONE:
			break;

		case ESelect::SELECT_NORMAL:
			CGame::SetMode(CGame::GAME_NORMAL);
			Change(MODE_TUTORIAL);
			return;
			break;

		case ESelect::SELECT_SAFETY_AREA:
			CGame::SetMode(CGame::GAME_SAFETY_AREA);
			Change(MODE_TUTORIAL);
			return;
			break;

		case ESelect::SELECT_DANGER_AREA:
			CGame::SetMode(CGame::GAME_DANGER_AREA);
			Change(MODE_TUTORIAL);
			return;
			break;

		case ESelect::SELECT_RANKING:
			CGame::SetMode(CGame::GAME_NORMAL);
			Change(MODE_RANKING);
			return;
			break;

		case ESelect::SELECT_MAX:
		default:
			assert(false);
			break;
		}
	}

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CTitle::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}

//--------------------------------------------------
// エフェクト
//--------------------------------------------------
void CTitle::Effect()
{
	m_time++;

	if ((m_time % 13) != 0)
	{// 一定間隔待ち
		return;
	}

	if (m_partCnt % 15 == 0)
	{// 一定間隔
		m_col.r = FloatRandom(1.0f, 0.0f);
		m_col.g = FloatRandom(1.0f, 0.0f);
		m_col.b = FloatRandom(1.0f, 0.0f);
	}

	m_partCnt++;

	// パーティクル
	CEffectManager::GetInstanse()->Particle(m_col);
}
