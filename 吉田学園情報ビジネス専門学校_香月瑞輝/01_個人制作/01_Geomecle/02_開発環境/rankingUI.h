//**************************************************
// 
// rankingUI.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RANKING_UI_H_	//このマクロ定義がされてなかったら
#define _RANKING_UI_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "game.h"

//==================================================
// 前方宣言
//==================================================
class CScore;
class CNumber;

//==================================================
// 定義
//==================================================
class CRankingUI
{
	/* ↓静的メンバ関数↓ */
public:
	static const float STD_WIDTH;	// 幅の標準値
	static const float STD_HEIGHT;	// 高さの標準値

private:
	static const int MAX_RANKING = 5;	// ランキングの最大数
	static const char* FILE_NAME[];		// ファイルパス

	/* ↓静的メンバ関数↓ */
public:
	static CRankingUI* Create(const D3DXVECTOR3& pos, float length);	// 生成
	static void Set(int score);	// 設定
	static int Get(int rank);	// 取得

private:
	static void Load();		// 読み込み
	static void Save();		// 保存
	static void Change();	// 変更

	/* ↓静的メンバ変数↓ */
private:
	static int m_score;	// 今回のスコア
	static int m_ranking[MAX_RANKING];	// ランキング

	/* ↓メンバ関数↓ */
public:
	CRankingUI();	// デフォルトコンストラクタ
	~CRankingUI();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos, float length);	// 初期化
	void Uninit();	// 終了
	void Release();	// 解放
	void Update();	// 更新
	void Reset(const D3DXVECTOR3& pos, float length, bool draw);	// リセット

	/* ↓メンバ変数↓ */
private:
	CScore* m_pRanking[MAX_RANKING];	// ランキング
	CNumber* m_pNumber[MAX_RANKING];	// 順位
	CObject2D* m_pRank[MAX_RANKING];	// 位
	int m_newRank;	// 新しいスコア
	int m_time;		// タイム
};

#endif // !_RANKING_UI_H_
