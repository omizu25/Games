//**************************************************
// 
// mode.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MODE_H_	//このマクロ定義がされてなかったら
#define _MODE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CMode
{
	/* ↓定義↓ */
public:
	enum EMode
	{
		MODE_NONE = -1,
		MODE_TITLE = 0,	// タイトル
		MODE_TUTORIAL,	// チュートリアル
		MODE_GAME,		// ゲーム
		MODE_RESULT,	// リザルト
		MODE_RANKING,	// ランキング
		MODE_MAX,
	};

	static const int FADE_TIME;	// フェードの時間

	/* ↓静的メンバ関数↓ */
public:
	static CMode* Create(EMode mode);	// 生成

	/* ↓メンバ関数↓ */
public:
	CMode() = delete;	// デフォルトコンストラクタ
	CMode(EMode mode);	// コンストラクタ
	virtual ~CMode();	// デストラクタ

public:
	virtual void Init() = 0;	// 初期化
	virtual void Uninit() = 0;	// 終了
	virtual void Update() = 0;	// 更新
	virtual void Draw() = 0;	// 描画

public:
	CMode* Set();				// 設定
	EMode Get();				// 取得
	void Change(EMode mode);	// 変更

	 /* ↓メンバ変数↓ */
private:
	EMode m_mode;		// モード
	EMode m_modeNext;	// 次のモード
};

#endif // !_MODE_H_
