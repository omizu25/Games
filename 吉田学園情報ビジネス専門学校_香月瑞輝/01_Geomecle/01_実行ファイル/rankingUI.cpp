//**************************************************
// 
// rankingUI.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "rankingUI.h"
#include "score.h"
#include "number.h"
#include "object2D.h"
#include "utility.h"

#include <assert.h>
#include <stdio.h>

//==================================================
// 定義
//==================================================
const float CRankingUI::STD_WIDTH = 40.0f;
const float CRankingUI::STD_HEIGHT = 50.0f;
const char* CRankingUI::FILE_NAME[] =
{// ランキングのテキストのパス
	"data/TEXT/Ranking_Normal.txt",		// 通常
	"data/TEXT/Ranking_SafetyArea.txt",	// 安全エリア
	"data/TEXT/Ranking_DangerArea.txt",	// 危険エリア
};

//==================================================
// 静的メンバ変数
//==================================================
int CRankingUI::m_score = 0;
int CRankingUI::m_ranking[MAX_RANKING] = {};

//--------------------------------------------------
// 生成
//--------------------------------------------------
CRankingUI* CRankingUI::Create(const D3DXVECTOR3& pos, float length)
{
	CRankingUI* pRanking = nullptr;

	pRanking = new CRankingUI;

	if (pRanking != nullptr)
	{// nullチェック
		// 初期化
		pRanking->Init(pos, length);
	}

	return pRanking;
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CRankingUI::Set(int score)
{
	m_score = score;

	// 読み込み
	Load();

	// 変更
	Change();

	// 保存
	Save();
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int CRankingUI::Get(int rank)
{
	if (rank == -1)
	{// 指定の値
		return m_score;
	}

	assert(rank >= 0 && rank < MAX_RANKING);

	// 読み込み
	Load();

	return m_ranking[rank];
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CRankingUI::Load()
{
	FILE *pFile = nullptr;

	// ファイルを開く
	pFile = fopen(FILE_NAME[CGame::GetMode()], "r");

	if (pFile != nullptr)
	{// ファイルが開いた場合

		for (int i = 0; i < MAX_RANKING; i++)
		{
			fscanf(pFile, "%d", &m_ranking[i]);
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開かない場合
		assert(false);
	}
}

//--------------------------------------------------
// 保存
//--------------------------------------------------
void CRankingUI::Save()
{
	FILE *pFile = nullptr;

	// ファイルを開く
	pFile = fopen(FILE_NAME[CGame::GetMode()], "w");

	if (pFile != nullptr)
	{// ファイルが開いた場合

		for (int i = 0; i < MAX_RANKING; i++)
		{
			fprintf(pFile, "%d\n\n", m_ranking[i]);
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開かない場合
		assert(false);
	}
}

//--------------------------------------------------
// 変更
//--------------------------------------------------
void CRankingUI::Change()
{
	int ranking[MAX_RANKING + 1] = {};

	for (int i = 0; i < MAX_RANKING; i++)
	{
		ranking[i] = m_ranking[i];
	}

	ranking[MAX_RANKING] = m_score;

	int save = 0;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		save = ranking[i];

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (save < ranking[j])
			{// 相手が大きかったら交代
				save = ranking[j];
			}
		}

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (save == ranking[j])
			{// 最大値を探して交代
				ranking[j] = ranking[i];
				ranking[i] = save;
				break;
			}
		}
	}

	for (int i = 0; i < MAX_RANKING; i++)
	{
		m_ranking[i] = ranking[i];
	}
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CRankingUI::CRankingUI() :
	m_newRank(0),
	m_time(0)
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		m_pRanking[i] = nullptr;
		m_pRank[i] = nullptr;
		m_pNumber[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CRankingUI::~CRankingUI()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		assert(m_pRanking[i] == nullptr);
		assert(m_pNumber[i] == nullptr);
		assert(m_pRank[i] == nullptr);
	}
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CRankingUI::Init(const D3DXVECTOR3& pos, float length)
{
	m_time = 0;

	D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

	float height = STD_HEIGHT;

	if (length <= 0.0f)
	{// 値がマイナス
		height *= -1.0f;
	}

	float posY = 0.0f;
	float interval = 3 * (size.x * 0.5f);
	float maxWidth = CNumberManager::MAX_DIGIT * size.x;
	float rankPosX = 0.0f;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		posY = pos.y + (i * (length + height));

		// スコアの生成
		m_pRanking[i] = CScore::Create(D3DXVECTOR3(pos.x, posY, 0.0f), size);

		// スコアの設定
		m_pRanking[i]->Set(m_ranking[i]);

		rankPosX = pos.x - maxWidth - interval - (STD_HEIGHT * 0.5f);

		// 位の生成
		m_pRank[i] = CObject2D::Create();
		m_pRank[i]->SetPos(D3DXVECTOR3(rankPosX - 20.0f, posY, 0.0f));
		m_pRank[i]->SetSize(D3DXVECTOR3(STD_HEIGHT, STD_HEIGHT, 0.0f));
		m_pRank[i]->SetTexture(CTexture::LABEL_Rank);
		m_pRank[i]->SetFade(0.0f);

		// 順位の生成
		m_pNumber[i] = CNumber::Create(D3DXVECTOR3(rankPosX - 65.0f, posY, 0.0f), size * 1.2f);
		m_pNumber[i]->Change(i + 1);
	}

	m_newRank = -1;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		if (m_ranking[i] != m_score)
		{// 指定の値ではない
			continue;
		}

		m_newRank = i;

		break;
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CRankingUI::Uninit()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		if (m_pRanking[i] != nullptr)
		{// nullチェック
			// 終了
			m_pRanking[i]->Uninit();
			delete m_pRanking[i];
			m_pRanking[i] = nullptr;
		}

		if (m_pRank[i] != nullptr)
		{// nullチェック
			// 終了
			m_pRank[i]->Uninit();
			m_pRank[i] = nullptr;
		}

		if (m_pNumber[i] != nullptr)
		{// nullチェック
			// 終了
			m_pNumber[i]->Uninit();
			m_pNumber[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CRankingUI::Release()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		if (m_pRanking[i] != nullptr)
		{// nullチェック
			// 解放
			m_pRanking[i]->Release();
			delete m_pRanking[i];
			m_pRanking[i] = nullptr;
		}

		if (m_pRank[i] != nullptr)
		{// nullチェック
			// 解放
			m_pRank[i]->Release();
			m_pRank[i] = nullptr;
		}

		if (m_pNumber[i] != nullptr)
		{// nullチェック
			// 解放
			m_pNumber[i]->Release();
			m_pNumber[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CRankingUI::Update()
{
	if (m_newRank == -1)
	{// 指定の値
		return;
	}

	m_time++;

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.a = 1.0f - (CosCurve(m_time, 0.01f) * 0.9f);

	// 色の設定
	m_pRanking[m_newRank]->SetCol(col);
}

//--------------------------------------------------
// リセット
//--------------------------------------------------
void CRankingUI::Reset(const D3DXVECTOR3& pos, float length, bool draw)
{
	// 読み込み
	Load();

	D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

	float height = STD_HEIGHT;

	if (length <= 0.0f)
	{// 値がマイナス
		height *= -1.0f;
	}

	float posY = 0.0f;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		posY = pos.y + (i * (length + height));

		// スコアの設定
		m_pRanking[i]->Set(m_ranking[i]);

		// スコアのリセット
		m_pRanking[i]->Reset(D3DXVECTOR3(pos.x, posY, 0.0f), size, draw);
	}

	if (!draw)
	{// 何も表示しない
		for (int i = 0; i < MAX_RANKING; i++)
		{
			// スコアの描画の設定
			m_pRanking[i]->SetDraw(false);

			// 描画の設定
			m_pRank[i]->SetDraw(false);

			// 描画の設定
			m_pNumber[i]->SetDraw(false);
		}
	}
	else
	{
		for (int i = 0; i < MAX_RANKING; i++)
		{
			// スコアの描画の設定
			m_pRanking[i]->SetZero(false);

			// 描画の設定
			m_pRank[i]->SetDraw(true);

			// 描画の設定
			m_pNumber[i]->SetDraw(true);
		}
	}
}
