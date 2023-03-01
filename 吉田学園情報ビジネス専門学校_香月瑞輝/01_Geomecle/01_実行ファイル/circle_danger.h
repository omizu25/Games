//**************************************************
// 
// circle_danger.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CIRCLE_DANGER_H_	//このマクロ定義がされてなかったら
#define _CIRCLE_DANGER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "circle.h"

//==================================================
// 定義
//==================================================
class CCircleDanger : public CCircle
{
	/* 定義 */
public:
	static const int COUNTDOWN_TIME;	// カウントダウンの時間

private:
	static const int MAX_LIFE;			// 寿命の最大値
	static const int MIN_LIFE;			// 寿命の最小値
	static const D3DXCOLOR STD_COLOR;	// 標準の色

	/* ↓メンバ関数↓ */
public:
	CCircleDanger();			// デフォルトコンストラクタ
	~CCircleDanger() override;	// デストラクタ

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
};

#endif // !_CIRCLE_DANGER_H_
