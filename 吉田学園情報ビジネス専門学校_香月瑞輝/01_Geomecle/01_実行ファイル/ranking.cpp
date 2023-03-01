//**************************************************
// 
// ranking.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "ranking.h"
#include "application.h"
#include "camera.h"
#include "effect_manager.h"
#include "utility.h"
#include "wall.h"
#include "rankingUI.h"
#include "menu.h"
#include "object2D.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CRanking::CRanking() : CMode(CMode::MODE_RANKING),
	m_pRanking(nullptr),
	m_pMenu(nullptr),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_time(0),
	m_partCnt(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CRanking::~CRanking()
{
	assert(m_pRanking == nullptr);
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CRanking::Init()
{
	m_time = 0;
	m_partCnt = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ランキングの設定
	CRankingUI::Set(-1);

	{// ランキングの背景
		float width = (float)CApplication::SCREEN_WIDTH * 0.75f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.5f - 15.0f;

		// ランキングの背景の生成
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(600.0f, 650.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_NONE);
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		pObj->SetFade(0.0f);
	}

	{// ランキング
		float width = (float)CApplication::SCREEN_WIDTH - 35.0f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

		// ランキングの生成
		m_pRanking = CRankingUI::Create(D3DXVECTOR3(width, height, 0.0f), 40.0f);
	}

	{// ランキングの文字列
		float width = (float)CApplication::SCREEN_WIDTH * 0.75f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.15f;

		// 文字列の生成
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(450.0f, 150.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_Rankig_Result);
		pObj->SetFade(0.0f);
	}

	{// メニュー
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.25f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(350.0f, 100.0f, 0.0f);

		// メニューの生成
		m_pMenu = CMenu::Create(pos, size, ESelect::SELECT_MAX, 50.0f, true, true);

		// 枠の設定
		m_pMenu->SetFrame(D3DXVECTOR3(600.0f, (float)CApplication::SCREEN_HEIGHT, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// テクスチャの設定
		m_pMenu->SetTexture(ESelect::SELECT_NORMAL, CTexture::LABEL_Normal);
		m_pMenu->SetTexture(ESelect::SELECT_SAFETY_AREA, CTexture::LABEL_SafetyArea);
		m_pMenu->SetTexture(ESelect::SELECT_DANGER_AREA, CTexture::LABEL_DangerArea);
		m_pMenu->SetTexture(ESelect::SELECT_END, CTexture::LABEL_End_Ranking);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CRanking::Uninit()
{
	if (m_pRanking != nullptr)
	{// nullチェック
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = nullptr;
	}

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
void CRanking::Update()
{
	// 更新
	CObject::UpdateAll();

	// エフェクト
	Effect();

	// ランキングの更新
	m_pRanking->Update();

	// 選択
	ESelect select = (ESelect)m_pMenu->Select();

	if (m_time >= CMode::FADE_TIME)
	{// フェード時間
		switch (select)
		{
		case ESelect::SELECT_NONE:
		case ESelect::SELECT_NORMAL:
		case ESelect::SELECT_SAFETY_AREA:
		case ESelect::SELECT_DANGER_AREA:
			break;

		case ESelect::SELECT_END:
			Change(MODE_TITLE);
			return;
			break;

		case ESelect::SELECT_MAX:
		default:
			assert(false);
			break;
		}
	}

	CGame::EGame mode = (CGame::EGame)m_pMenu->GetSelectIdx();

	if (mode > CGame::GAME_NONE && mode < CGame::GAME_MAX)
	{// 範囲内
		CGame::SetMode(mode);
		float width = (float)CApplication::SCREEN_WIDTH - 35.0f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

		// リセット
		m_pRanking->Reset(D3DXVECTOR3(width, height, 0.0f), 40.0f, true);
	}
	else
	{
		float width = (float)CApplication::SCREEN_WIDTH - 35.0f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

		// リセット
		m_pRanking->Reset(D3DXVECTOR3(width, height, 0.0f), 40.0f, false);
	}

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CRanking::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}

//--------------------------------------------------
// エフェクト
//--------------------------------------------------
void CRanking::Effect()
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
