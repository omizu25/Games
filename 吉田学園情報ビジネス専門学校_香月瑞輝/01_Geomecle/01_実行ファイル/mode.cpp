//**************************************************
// 
// mode.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "mode.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const int CMode::FADE_TIME = 10;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CMode* CMode::Create(EMode mode)
{
	CMode* pMode = nullptr;

	switch (mode)
	{
	case CMode::MODE_TITLE:
		pMode = new CTitle;
		break;

	case CMode::MODE_TUTORIAL:
		pMode = new CTutorial;
		break;

	case CMode::MODE_GAME:
		pMode = new CGame;
		break;

	case CMode::MODE_RESULT:
		pMode = new CResult;
		break;

	case CMode::MODE_RANKING:
		pMode = new CRanking;
		break;

	case CMode::MODE_NONE:
	case CMode::MODE_MAX:
	default:
		assert(false);
		break;
	}

	if (pMode != nullptr)
	{// nullチェック
		pMode->Init();
	}

	return pMode;
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CMode::CMode(EMode mode) :
	m_modeNext(MODE_NONE)
{
	m_mode = mode;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CMode::~CMode()
{
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
CMode* CMode::Set()
{
	if (m_modeNext == MODE_NONE)
	{// 次のモードが決まってない
		return this;
	}

	m_mode = m_modeNext;	// 現在の画面(モード)を切り替える
	m_modeNext = MODE_NONE;

	// 終了
	Uninit();

	return Create(m_mode);
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
CMode::EMode CMode::Get()
{
	return m_mode;
}

//--------------------------------------------------
// 変更
//--------------------------------------------------
void CMode::Change(EMode mode)
{
	assert(mode > MODE_NONE && mode < MODE_MAX);

	m_modeNext = mode;
}
