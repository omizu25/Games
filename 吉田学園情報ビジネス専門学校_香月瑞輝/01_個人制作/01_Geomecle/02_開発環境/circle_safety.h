//**************************************************
// 
// circle_safety.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CIRCLE_SAFETY_H_	//このマクロ定義がされてなかったら
#define _CIRCLE_SAFETY_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "circle.h"

//==================================================
// 定義
//==================================================
class CCircleSafety : public CCircle
{
	/* 定義 */
public:
	static const int COUNTDOWN_TIME;	// カウントダウンの時間

private:
	static const int MAX_LIFE;			// 寿命の最大値
	static const D3DXCOLOR STD_COLOR;	// 標準の色
	static const D3DXCOLOR START_COLOR;	// 始まりの色
	static const D3DXCOLOR END_COLOR;	// 終わりの色
	static const D3DXCOLOR DIFF_COLOR;	// 色の差分

	/* ↓メンバ関数↓ */
public:
	CCircleSafety();			// デフォルトコンストラクタ
	~CCircleSafety() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	bool Appear() override;						// 出現か消滅
	void SetAppear(ECircle appear) override;	// 出現か消滅の設定

	/* ↓メンバ変数↓ */
private:
	int m_time;	// タイム
	D3DXCOLOR m_changeCol;	// 色の変化量
};

#endif // !_CIRCLE_SAFETY_H_
