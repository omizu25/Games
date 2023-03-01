//**************************************************
// 
// game.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _GAME_H_	//このマクロ定義がされてなかったら
#define _GAME_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"
#include "circle_manager.h"

//==================================================
// 前方宣言
//==================================================
class CObject2D;
class CPause;
class CTime;
class CScore;
class CMul;
class CLife;
class CPlayer;
class CBom;

//==================================================
// 定義
//==================================================
class CGame : public CMode
{
	/* 定義 */
public:
	enum EGame
	{
		GAME_NONE = -1,
		GAME_NORMAL = 0,	// 通常
		GAME_SAFETY_AREA,	// 安全エリア
		GAME_DANGER_AREA,	// 危険エリア
		GAME_MAX
	};

private:
	static const int MAX_TIME;		// 時間の最大値
	static const int PAUSE_TIME;	// ポーズが出来る様になるまでの時間
	
	/* ↓静的メンバ関数↓ */
public:
	static void SetMode(EGame mode);	// ゲームモードの設定
	static EGame GetMode();				// ゲームモードの取得

	/* ↓静的メンバ変数↓ */
private:
	static EGame m_mode;	// ゲームモード

	/* ↓メンバ関数↓ */
public:
	CGame();			// デフォルトコンストラクタ
	~CGame() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	void Reset();	// リセット

public:
	CPlayer* GetPlayer();	// プレイヤーの取得
	CScore* GetScore();		// スコアの取得
	CMul* GetMul();			// 倍率の取得
	CTime* GetTime();		// タイムの取得
	CLife* GetLife();		// ライフの取得

private:
	void Effect();	// エフェクト

	/* ↓メンバ変数↓ */
private:
	CCircleManager* m_pCircle[CCircleManager::MAX_CIRCLE];	// 円
	CObject2D* m_pPauseBG;	// ポーズの背景
	CPlayer* m_pPlayer;		// プレイヤー
	CPause* m_pPause;		// ポーズ
	CTime* m_pTime;			// タイム
	CMul* m_pMul;			// 倍率
	CLife* m_pLife;			// ライフ
	CBom* m_pBom;			// ボム
	CScore* m_pScore;		// スコア
	CScore* m_pBestScore;	// ベストスコア
	int m_time;	//タイム
};

#endif // !_GAME_H_
