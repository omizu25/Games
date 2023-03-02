//**************************************************
// 
// time.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TIME_H_	//このマクロ定義がされてなかったら
#define _TIME_H_	//２重インクルード防止のマクロ定義

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
class CTime : public CNumberManager
{
	/* ↓定義↓ */
public:
	static const float STD_WIDTH;	// 幅の標準値
	static const float STD_HEIGHT;	// 高さの標準値

	/* ↓静的メンバ関数↓ */
public:
	static CTime* Create(const D3DXVECTOR3& pos, int start, int end);	// 生成

	/* ↓メンバ関数↓ */
public:
	CTime();	// デフォルトコンストラクタ
	~CTime();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size) override;	// 初期化
	void Uninit() override;		// 終了
	void Release() override;	// 解放

public:
	void Update();	// 更新
	void Restart();	// 再開

	/* ↓メンバ変数↓ */
private:
	CObject2D* m_pPeriod;	// ピリオド
	int m_start;	// 開始
	int m_elapsed;	// 経過
	int m_end;		// 終了
};

#endif // !_TIME_H_
