//**************************************************
// 
// bom.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _BOM_H_	//このマクロ定義がされてなかったら
#define _BOM_H_	//２重インクルード防止のマクロ定義

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
class CBom
{
	/* ↓定義↓ */
private:
	static const int MAX_BOM = 3;	// ボムの最大数
	static const float STD_SIZE;	// サイズの標準値

	/* ↓静的メンバ関数↓ */
public:
	static CBom* Create(const D3DXVECTOR3& pos);	// 生成

	/* ↓メンバ関数↓ */
public:
	CBom();	// デフォルトコンストラクタ
	~CBom();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos);	// 初期化
	void Uninit();	// 終了
	void Release();	// 解放
	void Update();	// 更新
	int Get();		// 取得
	void Reset();	// リセット

private:
	void Sub();	// 減算

	/* ↓メンバ変数↓ */
private:
	CObject2D* m_pObj[MAX_BOM];	// ボム
	int m_bom;					// ボムの数
};

#endif // !_BOM_H_
