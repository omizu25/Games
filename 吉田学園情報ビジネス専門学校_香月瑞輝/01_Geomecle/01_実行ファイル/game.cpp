//**************************************************
// 
// game.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "game.h"
#include "application.h"
#include "camera.h"
#include "player.h"
#include "enemy_manager.h"
#include "bullet.h"
#include "number_manager.h"
#include "time.h"
#include "score.h"
#include "mul.h"
#include "effect_manager.h"
#include "input.h"
#include "rankingUI.h"
#include "utility.h"
#include "pause.h"
#include "object2D.h"
#include "sound.h"
#include "wall.h"
#include "circle.h"
#include "life.h"
#include "bom.h"
#include "enemy.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const int CGame::MAX_TIME = 4500;
const int CGame::PAUSE_TIME = 100;

//==================================================
// 静的メンバ変数
//==================================================
CGame::EGame CGame::m_mode = GAME_NONE;

//--------------------------------------------------
// ゲームモードの設定
//--------------------------------------------------
void CGame::SetMode(EGame mode)
{
	m_mode = mode;
}

//--------------------------------------------------
// ゲームモードの取得
//--------------------------------------------------
CGame::EGame CGame::GetMode()
{
	return m_mode;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CGame::CGame() : CMode(CMode::MODE_GAME),
	m_pPauseBG(nullptr),
	m_pPlayer(nullptr),
	m_pPause(nullptr),
	m_pTime(nullptr),
	m_pMul(nullptr),
	m_pLife(nullptr),
	m_pBom(nullptr),
	m_pScore(nullptr),
	m_pBestScore(nullptr),
	m_time(0)
{
	for (int i = 0; i < CCircleManager::MAX_CIRCLE; i++)
	{
		m_pCircle[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CGame::~CGame()
{
	for (int i = 0; i < CCircleManager::MAX_CIRCLE; i++)
	{
		assert(m_pCircle[i] == nullptr);
	}

	assert(m_pPauseBG == nullptr);
	assert(m_pPlayer == nullptr);
	assert(m_pPause == nullptr);
	assert(m_pTime == nullptr);
	assert(m_pMul == nullptr);
	assert(m_pLife == nullptr);
	assert(m_pBom == nullptr);
	assert(m_pScore == nullptr);
	assert(m_pBestScore == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CGame::Init()
{
	m_time = 0;
	m_pPause = nullptr;

	{// ポーズの背景
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f);

		// 生成
		m_pPauseBG = CObject2D::Create();

		// 位置の設定
		m_pPauseBG->SetPos(pos);

		// サイズの設定
		m_pPauseBG->SetSize(size);

		// 色の設定
		m_pPauseBG->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));

		// 描画の設定
		m_pPauseBG->SetDraw(false);
	}

	if (m_pPlayer == nullptr)
	{// nullチェック
		// 生成
		m_pPlayer = CPlayer::Create();
	}

	// 初期化
	CEnemyManager::GetInstanse()->Init();

	if (m_mode != GAME_NORMAL)
	{// 円が必要なモード
		float width = CWall::STD_WIDTH * 0.25f;
		float height = CWall::STD_HEIGHT * 0.25f;

		D3DXVECTOR3 pos[CCircleManager::MAX_CIRCLE]
		{
			D3DXVECTOR3(-width, +height, 0.0f),	// 左上
			D3DXVECTOR3(+width, +height, 0.0f),	// 右上
			D3DXVECTOR3(-width, -height, 0.0f),	// 左下
			D3DXVECTOR3(+width, -height, 0.0f),	// 右下
		};

		D3DXVECTOR2 size = D3DXVECTOR2(width * 0.25f, height * 0.25f);

		for (int i = 0; i < CCircleManager::MAX_CIRCLE; i++)
		{
			// 生成
			m_pCircle[i] = CCircleManager::Create(pos[i], size);
		}
	}
	else
	{
		for (int i = 0; i < CCircleManager::MAX_CIRCLE; i++)
		{
			m_pCircle[i] = nullptr;
		}
	}

	{// タイム
		float width = (float)CApplication::SCREEN_WIDTH * 0.5f + (CTime::STD_WIDTH * 2.25f);
		float height = CTime::STD_HEIGHT * 0.5f + 15.0f;

		// タイムの生成
		m_pTime = CTime::Create(D3DXVECTOR3(width, height, 0.0f), timeGetTime(), MAX_TIME);
	}

	{// ライフ
		float width = (float)CApplication::SCREEN_WIDTH * 0.5f;
		float height = CTime::STD_HEIGHT + 30.0f;

		// ライフの生成
		m_pLife = CLife::Create(D3DXVECTOR3(width, height, 0.0f));
	}

	{// ボム
		float width = (float)CApplication::SCREEN_WIDTH * 0.5f;
		float height = CTime::STD_HEIGHT + 30.0f;

		// ボムの生成
		m_pBom = CBom::Create(D3DXVECTOR3(width, height, 0.0f));
	}

	{// スコア
		D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
		float width = (float)CApplication::SCREEN_WIDTH;
		float height = CScore::STD_HEIGHT * 0.5f + 10.0f;

		// スコアの生成
		m_pScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);
	}
	
	{// 倍率
		float width = (float)CApplication::SCREEN_WIDTH;
		float height = (CMul::STD_HEIGHT * 0.5f) + CScore::STD_HEIGHT + 10.0f;

		// 倍率の生成
		m_pMul = CMul::Create(D3DXVECTOR3(width, height, 0.0f));
	}
	
	{// ベストスコア
		D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
		int score = CRankingUI::Get(0);

		float width = (size.x * Digit(score)) + (((Digit(score) - 1) / 3) * (size.x * 0.5f));
		float height = size.y * 0.5f + 10.0f;

		// ベストスコアの生成
		m_pBestScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);

		// スコアの設定
		m_pBestScore->Set(score);
	}

	// BGM
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_BGM_Game);

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Start);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{	
	// ランキングの設定
	CRankingUI::Set(m_pScore->Get());

	for (int i = 0; i < CCircleManager::MAX_CIRCLE; i++)
	{
		if (m_pCircle[i] != nullptr)
		{// nullチェック
			m_pCircle[i]->Uninit();
			delete m_pCircle[i];
			m_pCircle[i] = nullptr;
		}
	}

	if (m_pPause != nullptr)
	{// nullチェック
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}

	if (m_pBestScore != nullptr)
	{// nullチェック
		m_pBestScore->Uninit();
		delete m_pBestScore;
		m_pBestScore = nullptr;
	}

	if (m_pScore != nullptr)
	{// nullチェック
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = nullptr;
	}

	if (m_pTime != nullptr)
	{// nullチェック
		m_pTime->Uninit();
		delete m_pTime;
		m_pTime = nullptr;
	}

	if (m_pMul != nullptr)
	{// nullチェック
		m_pMul->Uninit();
		delete m_pMul;
		m_pMul = nullptr;
	}

	if (m_pLife != nullptr)
	{// nullチェック
		m_pLife->Uninit();
		delete m_pLife;
		m_pLife = nullptr;
	}

	if (m_pBom != nullptr)
	{// nullチェック
		m_pBom->Uninit();
		delete m_pBom;
		m_pBom = nullptr;
	}

	// 全ての解放
	CObject::ReleaseAll(false);

	if (m_pPlayer != nullptr)
	{// nullチェック
		m_pPlayer = nullptr;
	}

	if (m_pPauseBG != nullptr)
	{// nullチェック
		m_pPauseBG = nullptr;
	}

	// 解放
	CEnemyManager::GetInstanse()->Release();

	// 停止
	CApplication::GetInstanse()->GetSound()->Stop(CSound::LABEL_BGM_Game);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	if (m_pPlayer == nullptr)
	{// nullチェック
		return;
	}

	if (m_pPause != nullptr)
	{// nullチェック
		// 更新
		m_pPauseBG->Update();

		bool pause = m_pPause->Update();

		if (!pause)
		{// ポーズ終わり
			if (m_pPause != nullptr)
			{// nullチェック
				m_pPause->Release();
				delete m_pPause;
				m_pPause = nullptr;
			}

			// 描画の設定
			m_pPauseBG->SetDraw(false);
		}

		return;
	}

	/* ポーズしていない */

	if (CInput::GetKey()->Trigger(CInput::KEY_PAUSE))
	{// Pキーが押された
		if (m_pTime->Get() <= MAX_TIME - PAUSE_TIME)
		{// ポーズ可能
			m_pPause = CPause::Create();

			// 描画の設定
			m_pPauseBG->SetDraw(true);

			// フェードの設定
			m_pPauseBG->SetFade(0.0f);

			// SE
			CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Enter);
			return;
		}
	}

	// 敵の出現の更新
	CEnemyManager::GetInstanse()->Update();

	// エフェクト
	Effect();

	if (m_mode != GAME_NORMAL)
	{// 円が必要なモード
		// 円の更新
		for (int i = 0; i < CCircleManager::MAX_CIRCLE; i++)
		{
			if (m_pCircle[i] != nullptr)
			{// nullチェック
				m_pCircle[i]->Update();
			}
		}

		// 当たり判定
		CCircle::Collision();
	}

	// 弾の発射
	CBullet::Shot();

	// ボムの更新
	m_pBom->Update();

	// タイムの減算
	m_pTime->Update();

	// 更新
	CObject::UpdateAll();

	// 敵の当たり判定
	CEnemy::Collision();

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CGame::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}

//--------------------------------------------------
// リセット
//--------------------------------------------------
void CGame::Reset()
{
	// プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	// 敵の全ての解放
	CObject3D::ReleaseAll(CObject3D::TYPE_ENEMY);

	// 弾の全ての解放
	CObject3D::ReleaseAll(CObject3D::TYPE_BULLET);

	// EXPの全ての解放
	CObject3D::ReleaseAll(CObject3D::TYPE_EXP);

	// ボムのリセット
	m_pBom->Reset();

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Start);
}

//--------------------------------------------------
// プレイヤーの取得
//--------------------------------------------------
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//--------------------------------------------------
// スコアの取得
//--------------------------------------------------
CScore* CGame::GetScore()
{
	return m_pScore;
}

//--------------------------------------------------
// 倍率の取得
//--------------------------------------------------
CMul* CGame::GetMul()
{
	return m_pMul;
}

//--------------------------------------------------
// タイムの取得
//--------------------------------------------------
CTime* CGame::GetTime()
{
	return m_pTime;
}

//--------------------------------------------------
// ライフの取得
//--------------------------------------------------
CLife* CGame::GetLife()
{
	return m_pLife;
}

//--------------------------------------------------
// エフェクト
//--------------------------------------------------
void CGame::Effect()
{
	m_time++;

	if ((m_time % 30) != 0)
	{// 一定間隔待ち
		return;
	}

	// 背景
	CEffectManager::GetInstanse()->BG();
}
