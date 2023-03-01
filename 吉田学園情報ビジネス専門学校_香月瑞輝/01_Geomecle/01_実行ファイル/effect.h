//**************************************************
// 
// effect.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_H_	//このマクロ定義がされてなかったら
#define _EFFECT_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object.h"

//==================================================
// 定義
//==================================================
class CEffect : public CObject
{
	/* 定義 */
public:
	static const float STD_WIDTH;	// 幅の標準値
	static const float STD_HEIGHT;	// 高さの標準値

private:
	static const int MAX_LIFE;		// 寿命の最大値
	static const float MIN_WIDTH;	// 幅の最小値

	/* ↓静的メンバ関数↓ */
public:
	static CEffect* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXCOLOR& col);	// 生成
	static int GetNumAll();	// 総数の取得

	/* ↓静的メンバ変数↓ */
private:
	static int m_numAll;	// 総数

	/* ↓メンバ関数↓ */
public:
	CEffect();				// デフォルトコンストラクタ
	~CEffect() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	const D3DXVECTOR3& GetPos() const;	// 位置の取得
	const D3DXCOLOR& GetCol() const;	// 色の取得
	const D3DXVECTOR3& GetMove() const;	// 移動量の取得
	const D3DXVECTOR2& GetSize() const;	// サイズの取得
	void SetCollision(bool collision);	// 当たり判定の設定
	void SetColSubtract(bool subtract);	// 色の減算の設定

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_move;	// 移動量
	D3DXVECTOR2 m_size;	// サイズ
	D3DXCOLOR m_col;	// 色
	int m_life;			// 寿命
	bool m_collision;	// 当たり判定をするかどうか
	bool m_colSubtract;	// 色の減算をするかどうか
};

#endif // !_EFFECT_H_
