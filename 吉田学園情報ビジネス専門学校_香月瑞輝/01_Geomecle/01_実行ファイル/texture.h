//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CTexture
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_NONE = -1,	// 使用しない
		LABEL_Player = 0,			// プレイヤー
		LABEL_Bullet,				// 弾
		LABEL_Effect,				// エフェクト
		LABEL_BG,					// 背景
		LABEL_Cursor,				// カーソル
		LABEL_TutorialNormal,		// 通常のチュートリアル
		LABEL_TutorialSafetyArea,	// 安全エリアのチュートリアル
		LABEL_TutorialDangerArea,	// 危険エリアのチュートリアル
		LABEL_Circle,				// 円
		LABEL_Bom,					// ボム

		/* ↓敵↓ */
		LABEL_Homing,			// ホーミング
		LABEL_HomingEscape,		// 逃げるホーミング
		LABEL_HomingDivision,	// 分裂ホーミング
		LABEL_PaperAirplane,	// 紙飛行機
		LABEL_Windmill,			// 風車
		LABEL_Snake_Body,		// 蛇の体
		
		/* ↓テキスト↓ */
		LABEL_Number,			// 数
		LABEL_Result,			// リザルト
		LABEL_Title,			// タイトル
		LABEL_Mul,				// 掛ける
		LABEL_Rank,				// 位
		LABEL_Rankig_Title,		// タイトル用のランキング
		LABEL_Rankig_Result,	// リザルト用のランキング
		LABEL_NewScore,			// 新しいスコア
		LABEL_Comma,			// カンマ
		LABEL_Period,			// ピリオド
		LABEL_Pause,			// ポーズ
		LABEL_Resume,			// 再開
		LABEL_Restart,			// リスタート
		LABEL_End,				// 終了
		LABEL_End_Ranking,		// ランキング用の終了
		LABEL_Retry,			// リトライ
		LABEL_Normal,			// 通常
		LABEL_SafetyArea,		// 安全エリア
		LABEL_DangerArea,		// 危険エリア
		LABEL_MAX
	};

	static const char* FILE_NAME[];	// ファイルパス

	/* ↓メンバ関数↓ */
public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public:
	void LoadAll();				// 全ての読み込み
	void Load(ELabel label);	// 指定の読み込み
	void ReleaseAll();			// 全ての破棄
	void Release(ELabel label);	// 指定の破棄
	LPDIRECT3DTEXTURE9 Get(ELabel label);	// 情報の取得

	/* ↓メンバ変数↓ */
private:
	LPDIRECT3DTEXTURE9 s_pTexture[LABEL_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
