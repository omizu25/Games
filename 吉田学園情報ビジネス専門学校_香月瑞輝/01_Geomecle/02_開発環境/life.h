//**************************************************
// 
// life.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _LIFE_H_	//このマクロ定義がされてなかったら
#define _LIFE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 前方宣言
//==================================================
class CObject2D;

//==================================================
// 定義
//==================================================
class CLife
{
	/* ↓定義↓ */
private:
	static const int MAX_LIFE = 5;	// ライフの最大数
	static const float STD_SIZE;	// サイズの標準値
	 
	/* ↓静的メンバ関数↓ */
public:
	static CLife* Create(const D3DXVECTOR3& pos);	// 生成

	/* ↓メンバ関数↓ */
public:
	CLife();	// デフォルトコンストラクタ
	~CLife();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos);	// 初期化
	void Uninit();	// 終了
	void Release();	// 解放
	void Sub();		// 減算
	int Get();		// 取得

	/* ↓メンバ変数↓ */
private:
	CObject2D* m_pObj[MAX_LIFE];	// ライフ
	int m_life;						// 残機
};

#endif // !_LIFE_H_
