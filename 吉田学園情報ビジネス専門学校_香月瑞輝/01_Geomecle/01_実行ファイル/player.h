//**************************************************
// 
// player.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PLAYER_H_	//このマクロ定義がされてなかったら
#define _PLAYER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CPlayer : public CObject3D
{
	/* 定義 */
private:
	static const int INVINCIBLE_TIME;	// 無敵時間
	static const int RIGOR_TIME;		// 硬直時間
	static const float STD_MOVE;		// 移動量の標準値
	static const float STD_SIZE;		// サイズの標準値
	static const float STD_ROT;			// 向きの標準値

	/* ↓静的メンバ関数↓ */
public:
	static CPlayer* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CPlayer();				// デフォルトコンストラクタ
	 ~CPlayer() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void Move();			// 移動
	void Rot();				// 向き
	void InvincibleTime();	// 無敵時間
	void Collision();		// 当たり判定

private:
	int m_time;			// タイム
	float m_rotDest;	// 目的の向き
};

#endif // !_OBJECT_H_
