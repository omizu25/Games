//**************************************************
// 
// circle.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CIRCLE_H_	//このマクロ定義がされてなかったら
#define _CIRCLE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CCircle : public CObject3D
{
	/* 定義 */
public:
	enum ECircle
	{
		CIRCLE_NONE = -1,
		CIRCLE_APPEAR = 0,	// 出現
		CIRCLE_DISAPPEAR,	// 消滅
		CIRCLE_MAX
	};

	static const float DISAPPEAR_SPEED;	// 消滅の速度

private:
	static const float STD_SIZE;	// サイズの標準値
	static const float APPEAR_SPEED;	// 出現の速度

	/* ↓静的メンバ関数↓ */
public:
	static CCircle* Create(const D3DXVECTOR3& pos);	// 生成
	static void Collision();	// 当たり判定
	static bool GetCollision();	// 当たっているかどうかの取得

	/* ↓静的メンバ変数↓ */
private:
	static bool m_collision;	// 当たり判定

	/* ↓メンバ関数↓ */
public:
	CCircle();				// デフォルトコンストラクタ
	~CCircle() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	virtual bool Appear();					// 出現か消滅
	virtual void SetAppear(ECircle appear);	// 出現か消滅の設定
	
public:
	bool GetCountDown();	// カウントダウンをしているかどうか
	void SetTime(int time);	// カウントダウンのタイムの設定
	void SetLife(int life);	// 寿命の設定
	int GetLife();			// 寿命の取得
	ECircle GetAppear();	// 出現か消滅の取得

	/* ↓メンバ変数↓ */
private:
	int m_time;				// タイム
	int m_countDownTime;	// カウントダウンのタイム
	int m_life;				// 寿命
	ECircle m_appear;		// 出現か消滅
	bool m_countDown;		// カウントダウンをするかどうか
};

#endif // !_CIRCLE_H_
