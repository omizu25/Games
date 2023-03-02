//**************************************************
// 
// bg.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _BG_H_	//このマクロ定義がされてなかったら
#define _BG_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CBG : public CObject3D
{
	/* ↓静的メンバ関数↓ */
public:
	static CBG* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// 生成

	/* ↓メンバ関数↓ */
public:
	CBG();				// デフォルトコンストラクタ
	~CBG() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
};

#endif // !_BG_H_
