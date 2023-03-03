//**************************************************
// 
// enemy_escape.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_ESCAPE_H_	//このマクロ定義がされてなかったら
#define _ENEMY_ESCAPE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// 定義
//==================================================
class CEnemyEscape : public CEnemy
{
	/* ↓定義↓ */
private:
	static const float HOMING_SPEED;	// ホーミングの速度
	static const float ESCAPE_SPEED;	// 逃げる時の速度
	static const float ROT_CHANGE;		// 向きの変更値
	static const float STD_INERTIA;		// 慣性の標準値
	static const float FIND_AREA;		// 探すエリア

	/* ↓メンバ関数↓ */
public:
	CEnemyEscape();				// デフォルトコンストラクタ
	~CEnemyEscape() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
	void Kill() override;	// キルされた

private:
	void Escape();	// 弾から逃げる
	void Set(const D3DXVECTOR3& pos) override;	// 設定

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_move;	// 移動量
	float m_rot;		
	bool m_rotDir;		// 回転方向 [ true / 右回り / false : 左回り ]
};

#endif // !_ENEMY_ESCAPE_H_
