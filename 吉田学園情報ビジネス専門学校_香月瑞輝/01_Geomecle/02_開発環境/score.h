//**************************************************
// 
// score.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _SCORE_H_	//このマクロ定義がされてなかったら
#define _SCORE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "number_manager.h"

//==================================================
// 前方宣言
//==================================================
class CObject2D;

//==================================================
// 定義
//==================================================
class CScore : public CNumberManager
{
	/* ↓定義↓ */
public:
	static const float STD_WIDTH;	// 幅の標準値
	static const float STD_HEIGHT;	// 高さの標準値

	/* ↓静的メンバ関数↓ */
public:
	static CScore* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// 生成

	/* ↓メンバ関数↓ */
public:
	CScore();	// デフォルトコンストラクタ
	~CScore();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size) override;	// 初期化
	void Uninit() override;		// 終了
	void Release() override;	// 解放

public:
	void Add(int score);	// 加算
	void Set(int value);	// 設定
	void SetCol(const D3DXCOLOR& col);	// 色の設定
	void DrawComma();	// カンマの描画
	void Reset(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, bool draw);	// リセット

	/* ↓メンバ変数↓ */
private:
	CObject2D* m_pComma[MAX_COMMA];	// カンマ
};

#endif // !_SCORE_H_
