//**************************************************
// 
// wall.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _WALL_H_	//このマクロ定義がされてなかったら
#define _WALL_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CWall : public CObject3D
{
	/* 定義 */
public:
	static const float STD_SIZE;	// サイズの標準値
	static const float STD_WIDTH;	// 幅の標準値
	static const float STD_HEIGHT;	// 高さの標準値

	/* ↓静的メンバ関数↓ */
public:
	static void AllCreate();	// 全ての生成

private:
	static CWall* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// 生成

	/* ↓メンバ関数↓ */
public:
	CWall();			// デフォルトコンストラクタ
	~CWall() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
};

#endif // !_BG_H_
