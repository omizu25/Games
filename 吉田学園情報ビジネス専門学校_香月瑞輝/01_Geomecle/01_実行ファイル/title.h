//**************************************************
// 
// title.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TITLE_H_	//このマクロ定義がされてなかったら
#define _TITLE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 前方宣言
//==================================================
class CMenu;

//==================================================
// 定義
//==================================================
class CTitle : public CMode
{
	/* 定義 */
private:
	enum ESelect
	{
		SELECT_NONE = -1,
		SELECT_NORMAL = 0,	// 通常
		SELECT_SAFETY_AREA,	// 安全エリア
		SELECT_DANGER_AREA,	// 危険エリア
		SELECT_RANKING,		// ランキング
		SELECT_MAX
	};

	/* ↓メンバ関数↓ */
public:
	CTitle();			// デフォルトコンストラクタ
	~CTitle() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void Effect();	// エフェクト

	/* メンバ変数 */
private:
	CMenu* m_pMenu;		// メニュー
	D3DXCOLOR m_col;	// 色
	int m_time;			// 時間
	int m_partCnt;		// パーティクルカウンター
};

#endif // !_TITLE_H_
