//**************************************************
// 
// tutorial.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TUTORIAL_H_	//このマクロ定義がされてなかったら
#define _TUTORIAL_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 定義
//==================================================
class CTutorial : public CMode
{
	/* ↓メンバ関数↓ */
public:
	CTutorial();			// デフォルトコンストラクタ
	~CTutorial() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void Effect();	// エフェクト

	/* メンバ変数 */
private:
	int m_time;	// 時間
};

#endif // !_TUTORIAL_H_
