//**************************************************
// 
// enemy_homing.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_HOMING_H_	//このマクロ定義がされてなかったら
#define _ENEMY_HOMING_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// 定義
//==================================================
class CEnemyHoming : public CEnemy
{
	/* ↓定義↓ */
private:
	static const float STD_MOVE;	// 移動量の標準値
	static const float SIZE_CHANGE;	// サイズの変更値

	/* ↓メンバ関数↓ */
public:
	CEnemyHoming();				// デフォルトコンストラクタ
	~CEnemyHoming() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
	void Kill() override;	// キルされた

private:
	void Set(const D3DXVECTOR3& pos) override;	// 設定

	/* ↓メンバ変数↓ */
private:
	int m_time;				// タイム
	D3DXVECTOR3 m_saveSize;	// サイズの保存
};

#endif // !_ENEMY_HOMING_H_
