//**************************************************
// 
// enemy_round_trip.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_ROUND_TRIP_H_	//このマクロ定義がされてなかったら
#define _ENEMY_ROUND_TRIP_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// 定義
//==================================================
class CEnemyRoundTrip : public CEnemy
{
	/* 定義 */
private:
	static const float STD_MOVE;	// 移動量の標準値

	/* ↓メンバ関数↓ */
public:
	CEnemyRoundTrip();				// デフォルトコンストラクタ
	~CEnemyRoundTrip() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
	void Kill() override;	// キルされた

private:
	void Set(const D3DXVECTOR3& pos) override;	// 設定
	void SetMove();	// 移動量の設定

	/* メンバ変数 */
private:
	D3DXVECTOR3 m_move;	// 移動量
};

#endif // !_ENEMY_ROUND_TRIP_H_
