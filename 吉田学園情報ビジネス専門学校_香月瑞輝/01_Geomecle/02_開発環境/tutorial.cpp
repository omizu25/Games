//**************************************************
// 
// tutorial.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "tutorial.h"
#include "application.h"
#include "camera.h"
#include "input.h"
#include "object2D.h"
#include "effect_manager.h"
#include "wall.h"
#include "utility.h"
#include "game.h"
#include "sound.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTutorial::CTutorial() : CMode(CMode::MODE_TUTORIAL),
	m_time(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTutorial::~CTutorial()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CTutorial::Init()
{
	m_time = 0;
	
	CObject2D* pTutorial = CObject2D::Create();
	pTutorial->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f));
	pTutorial->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

	CTexture::ELabel label[CGame::GAME_MAX] =
	{
		CTexture::LABEL_TutorialNormal,
		CTexture::LABEL_TutorialSafetyArea,
		CTexture::LABEL_TutorialDangerArea,
	};

	pTutorial->SetTexture(label[CGame::GetMode()]);
	pTutorial->SetFade(0.0f);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTutorial::Uninit()
{
	// 全ての解放
	CObject::ReleaseAll(false);

	CApplication* pApp = CApplication::GetInstanse();

	// テクスチャの破棄
	pApp->GetTexture()->ReleaseAll();

	// 停止
	CApplication::GetInstanse()->GetSound()->Stop(CSound::LABEL_BGM_Title);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CTutorial::Update()
{
	// 更新
	CObject::UpdateAll();

	// エフェクト
	Effect();

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// 決定キーが押された
		if (m_time >= CMode::FADE_TIME)
		{// フェード時間
			Change(MODE_GAME);

			// SE
			CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Enter);
			return;
		}
	}

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CTutorial::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}

//--------------------------------------------------
// エフェクト
//--------------------------------------------------
void CTutorial::Effect()
{
	m_time++;

	if ((m_time % 30) != 0)
	{// 一定間隔待ち
		return;
	}

	// 背景
	CEffectManager::GetInstanse()->BG();
}
