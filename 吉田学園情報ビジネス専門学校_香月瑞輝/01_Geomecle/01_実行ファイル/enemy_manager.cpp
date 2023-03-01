//**************************************************
// 
// enemy_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_manager.h"
#include "enemy_wave.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const char* CEnemyManager::FILE_NAME[] =
{// テクスチャのパス
	"data/TEXT/EnemySpawn000.json",
	"data/TEXT/EnemySpawn001.json",
	"data/TEXT/EnemySpawn002.json",
	"data/TEXT/EnemySpawn003.json",
	"data/TEXT/EnemySpawn004.json",
	"data/TEXT/EnemySpawn005.json",
	"data/TEXT/EnemySpawn006.json",
};

//==================================================
// 静的メンバ変数
//==================================================
CEnemyManager* CEnemyManager::m_pEnemyManager = nullptr;

//--------------------------------------------------
// インスタンスの取得
//--------------------------------------------------
CEnemyManager* CEnemyManager::GetInstanse()
{
	if (m_pEnemyManager == nullptr)
	{// nullチェック
		m_pEnemyManager = new CEnemyManager;
	}

	return m_pEnemyManager;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyManager::CEnemyManager() :
	m_nowWave(0)
{
	static_assert(sizeof(FILE_NAME) / sizeof(FILE_NAME[0]) == MAX_WAVE, "aho");

	for (int i = 0; i < MAX_WAVE; i++)
	{
		m_pWave[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyManager::~CEnemyManager()
{
	for (int i = 0; i < MAX_WAVE; i++)
	{
		assert(m_pWave[i] == nullptr);
	}
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemyManager::Init()
{
	for (int i = 0; i < MAX_WAVE; i++)
	{
		m_pWave[i] = CEnemyWave::Create(FILE_NAME[i]);
	}

	m_nowWave = 0;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemyManager::Uninit()
{
	for (int i = 0; i < MAX_WAVE; i++)
	{
		if (m_pWave[i] != nullptr)
		{// nullチェック
			m_pWave[i]->Release();
			m_pWave[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CEnemyManager::Release()
{
	for (int i = 0; i < MAX_WAVE; i++)
	{
		if (m_pWave[i] != nullptr)
		{// nullチェック
			m_pWave[i]->Release();
			m_pWave[i] = nullptr;
		}
	}

	if (m_pEnemyManager != nullptr)
	{// nullチェック
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemyManager::Update()
{
	if (m_pWave[m_nowWave] == nullptr)
	{// nullチェック
		assert(false);
	}

	if (!m_pWave[m_nowWave]->Spawn())
	{// 全てのスポーンをした
		return;
	}

	m_nowWave++;

	if (m_nowWave >= MAX_WAVE)
	{
 		m_nowWave = 2;
	}

	if (m_pWave[m_nowWave] == nullptr)
	{// nullチェック
		assert(false);
	}

	// リセット
	m_pWave[m_nowWave]->Reset();
}
