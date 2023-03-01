//**************************************************
// 
// mul.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MUL_H_	//このマクロ定義がされてなかったら
#define _MUL_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "score.h"

//==================================================
// 前方宣言
//==================================================
class CObject2D;

//==================================================
// 定義
//==================================================
class CMul : public CScore
{
	/* ↓定義↓ */
public:
	static const float STD_WIDTH;	// 幅の標準値
	static const float STD_HEIGHT;	// 高さの標準値
	static const float MUL_SIZE;	// 掛けるのサイズ

	/* ↓静的メンバ関数↓ */
public:
	static CMul* Create(const D3DXVECTOR3& pos);	// 生成

	/* ↓メンバ関数↓ */
public:
	CMul();	// デフォルトコンストラクタ
	~CMul();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size) override;	// 初期化
	void Uninit() override;		// 終了
	void Release() override;	// 解放

public:
	void Add();				// 加算
	void Set(int value);	// 設定

	/* ↓メンバ変数↓ */
private:
	CObject2D* m_pMul;	// 掛ける
	D3DXVECTOR3 m_pos;	// 位置
};

#endif // !_MUL_H_
