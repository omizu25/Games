//**************************************************
// 
// enemy_snake_head.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_SNAKE_HEAD_H_	//このマクロ定義がされてなかったら
#define _ENEMY_SNAKE_HEAD_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// 前方宣言
//==================================================
class CEnemySnakeBody;

//==================================================
// 定義
//==================================================
class CEnemySnakeHead : public CEnemy
{
	/* 定義 */
private:
	static const int MAX_BODY;			// 体の最大数
	static const int IDX_PARENT;		// 親の番号
	static const float STD_SIZE;		// サイズの標準値
	static const float STD_MOVE;		// 移動量の標準値
	static const float AMPLITUDE_WIDTH;	// 振幅の幅
	static const float AMPLITUDE_SPEED;	// 振幅の速度

	/* ↓メンバ関数↓ */
public:
	CEnemySnakeHead();				// デフォルトコンストラクタ
	~CEnemySnakeHead() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
	void Kill() override;	// キルされた

public:
	const D3DXVECTOR3& GetPosOld() const;	// 前回の位置の取得

private:
	void Set(const D3DXVECTOR3& pos) override;	// 設定
	void SetMove();	// 移動量の設定

	/* メンバ変数 */
private:
	int m_time;					// タイム
	D3DXVECTOR3 m_move;			// 移動量
	D3DXVECTOR3 m_posOld;		// 前回の位置
	CEnemySnakeBody** m_pBody;	// 体の情報

};

#endif // !_ENEMY_SNAKE_HEAD_H_
