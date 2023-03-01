//**************************************************
// 
// effect_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_MANAGER_H_	//このマクロ定義がされてなかったら
#define _EFFECT_MANAGER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CEffectManager
{
	/* 定義 */
private:
	static const int MAX_PARTICLE;		// パーティクルの最大数
	static const int MAX_PLAYER;		// プレイヤーの最大数
	static const int MAX_EXPLOSION;		// 爆発の最大数
	static const int HALF_EXPLOSION;	// 爆発の最大数の半分
	static const int MAX_BULLET;		// 弾の最大数
	static const int MAX_BOM;			// ボムの最大数
	static const float PARTICLE_MOVE;	// パーティクルの移動量
	static const float PLAYER_MOVE;		// プレイヤーの移動量
	static const float EXPLOSION_MOVE;	// 爆発の移動量
	static const float BULLET_MOVE;		// 弾の移動量
	static const float BOM_MOVE;		// ボムの移動量

	/* ↓静的メンバ関数↓ */
public:
	static CEffectManager* GetInstanse();	// インスタンスの取得

	/* ↓静的メンバ変数↓ */
private:
	static CEffectManager* m_pEffectManager;	// 自分のクラス

	/* ↓メンバ関数↓ */
private:
	CEffectManager();	// デフォルトコンストラクタ

public:
	~CEffectManager();	// デストラクタ

public:
	void Release();	// 解放
	void Particle(const D3DXCOLOR& col);	// パーティクル
	void Player(const D3DXVECTOR3& pos);	// プレイヤー
	void Explosion(const D3DXVECTOR3& pos);	// 爆発
	void Bullet(const D3DXVECTOR3& pos);	// 弾
	void Bom(const D3DXVECTOR3& pos);		// ボム
	void BG();	// 背景

	/* ↓メンバ変数↓ */
private:
};

#endif // !_EFFECT_MANAGER_H_
