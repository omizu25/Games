//**************************************************
// 
// exp.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EXP_H_	//このマクロ定義がされてなかったら
#define _EXP_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CExp : public CObject3D
{
	/* 定義 */
private:
	static const int MAX_EXP;			// 経験値の最大数
	static const int STD_LIFE;			// 寿命の標準値
	static const int BLINK_START;		// 点滅の始まり
	static const float BLINK_SPEED;		// 点滅の速度
	static const float HOMING_START;	// ホーミングの始まり
	static const float HOMING_SPEED;	// ホーミングの速度
	static const float STD_SIZE;		// サイズの標準値
	static const float STD_ROTATION;	// 回転の標準値
	static const float MAX_MOVE;		// 移動量の最大値
	static const float MAX_RADIUS;		// 半径の最大値

	/* ↓静的メンバ関数↓ */
public:
	static void CreateAll(const D3DXVECTOR3& pos);	// 全ての生成

private:
	static CExp* Create(const D3DXVECTOR3& pos, float rot);	// 生成

	/* ↓メンバ関数↓ */
public:
	CExp();				// デフォルトコンストラクタ
	~CExp() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void SetMove(float rot);	// 動量の設定
	void Collision();			// 当たり判定
	void Absorption();			// 吸収
	void Wall();				// 壁

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_move;	// 移動量
	int m_life;	// 寿命
};

#endif // !_EXP_H_
