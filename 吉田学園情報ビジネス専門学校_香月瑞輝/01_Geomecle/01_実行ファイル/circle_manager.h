//**************************************************
// 
// circle_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CIRCLE_MANAGER_H_	//このマクロ定義がされてなかったら
#define _CIRCLE_MANAGER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 前方宣言
//==================================================
class CCircle;

//==================================================
// 定義
//==================================================
class CCircleManager
{
	/* 定義 */
public:
	static const int MAX_CIRCLE = 4;	// 円の最大数

private:
	static const int MAX_INTERVAL;	// インターバルの最大値
	static const int MIN_INTERVAL;	// インターバルの最小値

	/* ↓静的メンバ関数↓ */
public:
	static CCircleManager* Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);	// 生成

	/* ↓メンバ関数↓ */
public:
	CCircleManager();	// デフォルトコンストラクタ
	~CCircleManager();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);	// 初期化
	void Uninit();	// 終了
	void Release();	// 解放
	void Update();	// 更新

	/* ↓メンバ変数↓ */
private:
	CCircle* m_pCircle;	// 円
	int m_time;			// タイム
	int m_interval;		// インターバル
	float m_areaTop;	// エリアの上
	float m_areaBottom;	// エリアの下
	float m_areaRight;	// エリアの右
	float m_areaLeft;	// エリアの左
};

#endif // !_CIRCLE_MANAGER_H_
