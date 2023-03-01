//**************************************************
// 
// enemy_wave.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_WAVE_H_	//このマクロ定義がされてなかったら
#define _ENEMY_WAVE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// 定義
//==================================================
class CEnemyWave
{
	/* ↓定義↓ */
private:
	static const int SPAWN_INTERVAL;	// スポーンのインターバル

	struct SLoad
	{
		D3DXVECTOR3 pos;
		int timing;
		CEnemy::EType type;
	};

	/* ↓静的メンバ関数↓ */
public:
	static CEnemyWave* Create(const char* pPath);	// 生成
	
	/* ↓メンバ関数↓ */
public:
	CEnemyWave();	// デフォルトコンストラクタ
	~CEnemyWave();	// デストラクタ

public:
	void Load(const char* pPath);	// 読み込み
	bool Spawn();	// スポーン
	void Release();	// 解放
	void Reset();	// リセット

	/* ↓メンバ変数↓ */
private:
	SLoad* m_pLoad;	// 読み込み
	int m_time;		// 時間
	int m_timing;	// タイミング
	int m_max;		// 最大数
	int m_spawn;	// スポーン
};

#endif // !_ENEMY_WAVE_H_
