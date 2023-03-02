//**************************************************
// 
// enemy.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_H_	//このマクロ定義がされてなかったら
#define _ENEMY_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CEnemy : public CObject3D
{
	/* 定義 */
public:
	enum EType
	{
		TYPE_NONE = -1,
		TYPE_HOMING = 0,	// ホーミング
		TYPE_ROUNDTRIP,		// 往復
		TYPE_WINDMILL,		// 風車
		TYPE_SNAKE,			// 蛇
		TYPE_DIVISION,		// 分裂
		TYPE_ESCAPE,		// 弾から逃げる
		TYPE_ROLLING,		// 回転
		TYPE_MAX
	};

	static const int STD_SCORE;		// スコアの標準値
	static const int CREATE_TIME;	// 生成時間
	
private:
	static const float STD_SIZE;	// サイズの標準値

	/* ↓静的メンバ関数↓ */
public:
	static CEnemy* Create(CEnemy::EType type, const D3DXVECTOR3& pos);	// 生成
	static void Collision(); // 当たり判定

	/* ↓メンバ関数↓ */
public:
	CEnemy();				// デフォルトコンストラクタ
	 ~CEnemy() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
	virtual void Kill();	// キルされた

public:
	int GetTime();	// タイムの取得

private:
	EType GetType();	// 種類の取得
	virtual void Set(const D3DXVECTOR3& pos) = 0;	// 設定

	/* ↓メンバ変数↓ */
private:
	int m_time;		// タイム
	EType m_type;	// 種類
};

#endif // !_ENEMT_H_
