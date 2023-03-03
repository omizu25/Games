//**************************************************
// 
// enemy_snake_body.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_SNAKE_BODY_H_	//このマクロ定義がされてなかったら
#define _ENEMY_SNAKE_BODY_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CEnemySnakeBody : public CObject3D
{
	/* 定義 */
private:
	static const float STD_SIZE;	// サイズの標準値
	static const int MOVE_INTERVAL;	// 移動のインターバル

		/* ↓静的メンバ関数↓ */
public:
	static CEnemySnakeBody* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CEnemySnakeBody();				// デフォルトコンストラクタ
	~CEnemySnakeBody() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
	void SetPosDest(const D3DXVECTOR3& posDest);	// 目的の位置の設定
	const D3DXVECTOR3& GetPosOld() const;			// 前回の位置の取得

	/* メンバ変数 */
private:
	int m_time;				// タイム
	D3DXVECTOR3 m_posDest;	// 目的の位置
	D3DXVECTOR3 m_posOld;	// 前回の位置
};

#endif // !_ENEMY_SNAKE_BODY_H_
