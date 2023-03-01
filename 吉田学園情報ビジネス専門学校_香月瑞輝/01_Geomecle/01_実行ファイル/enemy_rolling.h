//**************************************************
// 
// enemy_rolling.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_ROLLING_H_	//このマクロ定義がされてなかったら
#define _ENEMY_ROLLING_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// 定義
//==================================================
class CEnemyRolling : public CEnemy
{
	/* ↓定義↓ */
private:
	static const float STD_SIZE;	// サイズの標準値
	static const float STD_MOVE;	// 移動量の標準値
	static const float ROT_CHANGE;	// 向きの変更値

	/* ↓静的メンバ関数↓ */
public:
	static void Create(const D3DXVECTOR3& pos);	// 生成

	/* ↓メンバ関数↓ */
public:
	CEnemyRolling();			// デフォルトコンストラクタ
	~CEnemyRolling() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
	void Kill() override;	// キルされた

private:
	void Set(const D3DXVECTOR3& pos) override;	// 設定
	void SetRotDir(bool rotDir);				// 回転方向の設定

	/* ↓メンバ変数↓ */
private:
	int m_time;		// タイム
	bool m_rotDir;	// 回転方向 [ true / 右回り / false : 左回り ]
};

#endif // !_ENEMY_ROLLING_H_
