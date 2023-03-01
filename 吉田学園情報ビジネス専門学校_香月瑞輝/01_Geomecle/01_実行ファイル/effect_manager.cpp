//**************************************************
// 
// effect_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "effect_manager.h"
#include "utility.h"
#include "effect.h"
#include "application.h"
#include "sound.h"
#include "wall.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CEffectManager::MAX_PARTICLE = 200;
const int CEffectManager::MAX_PLAYER = 500;
const int CEffectManager::MAX_EXPLOSION = 50;
const int CEffectManager::HALF_EXPLOSION = MAX_EXPLOSION / 2;
const int CEffectManager::MAX_BULLET = 50;
const int CEffectManager::MAX_BOM = 500;
const float CEffectManager::PARTICLE_MOVE = 20.0f;
const float CEffectManager::PLAYER_MOVE = 50.0f;
const float CEffectManager::EXPLOSION_MOVE = 10.0f;
const float CEffectManager::BULLET_MOVE = 5.0f;
const float CEffectManager::BOM_MOVE = 70.0f;

//==================================================
// 静的メンバ変数
//==================================================
CEffectManager* CEffectManager::m_pEffectManager = nullptr;

//--------------------------------------------------
// インスタンスの取得
//--------------------------------------------------
CEffectManager* CEffectManager::GetInstanse()
{
	if (m_pEffectManager == nullptr)
	{// nullチェック
		m_pEffectManager = new CEffectManager;
	}

	return m_pEffectManager;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEffectManager::CEffectManager()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEffectManager::~CEffectManager()
{
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEffectManager::Release()
{
	if (m_pEffectManager != nullptr)
	{// nullチェック
		delete m_pEffectManager;
		m_pEffectManager = nullptr;
	}
}

//--------------------------------------------------
// パーティクル
//--------------------------------------------------
void CEffectManager::Particle(const D3DXCOLOR& col)
{
	float width = CWall::STD_WIDTH * 0.4f;
	float height = CWall::STD_HEIGHT * 0.4f;

	D3DXVECTOR3 pos = D3DXVECTOR3(FloatRandom(width, -width), FloatRandom(height, -height), 0.0f);

	D3DXCOLOR randomCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 randomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	float random = 0.0f;

	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_PARTICLE * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(100.0f, 50.0f);

		random = FloatRandom(PARTICLE_MOVE, PARTICLE_MOVE * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		randomCol.r = col.r + FloatRandom(0.25f, -0.25f);
		randomCol.g = col.g + FloatRandom(0.25f, -0.25f);
		randomCol.b = col.b + FloatRandom(0.25f, -0.25f);

		// 生成
		CEffect::Create(pos + randomPos, move, randomCol);
	}
}

//--------------------------------------------------
// プレイヤー
//--------------------------------------------------
void CEffectManager::Player(const D3DXVECTOR3& pos)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 randomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	float random = 0.0f;

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_PLAYER * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(100.0f, 50.0f);

		random = FloatRandom(PLAYER_MOVE, PLAYER_MOVE * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = 1.0f + FloatRandom(0.0f, -0.25f);
		col.g = 1.0f + FloatRandom(0.0f, -0.25f);
		col.b = 1.0f + FloatRandom(0.0f, -0.25f);

		// 生成
		CEffect::Create(pos + randomPos, move, col);
	}
}

//--------------------------------------------------
// 爆発
//--------------------------------------------------
void CEffectManager::Explosion(const D3DXVECTOR3& pos)
{
	float red = FloatRandom(1.0f, 0.0f);
	float green = FloatRandom(1.0f, 0.0f);
	float blue = FloatRandom(1.0f, 0.0f);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 randomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	float random = 0.0f;

	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_EXPLOSION * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(75.0f, 50.0f);

		random = FloatRandom(EXPLOSION_MOVE, EXPLOSION_MOVE * 0.5f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = red + FloatRandom(0.25f, -0.25f); 
		col.g = green + FloatRandom(0.25f, -0.25f);
		col.b = blue + FloatRandom(0.25f, -0.25f);

		// 生成
		CEffect::Create(pos + randomPos, move, col);
	}

	for (int i = 0; i < HALF_EXPLOSION; i++)
	{
		rot = (D3DX_PI * 2.0f) / HALF_EXPLOSION * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(75.0f, 50.0f);

		random = FloatRandom(EXPLOSION_MOVE, EXPLOSION_MOVE * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = red + FloatRandom(0.25f, -0.25f);
		col.g = green + FloatRandom(0.25f, -0.25f);
		col.b = blue + FloatRandom(0.25f, -0.25f);

		// 生成
		CEffect::Create(pos + randomPos, move, col);
	}

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Explosion);
}

//--------------------------------------------------
// 弾
//--------------------------------------------------
void CEffectManager::Bullet(const D3DXVECTOR3& pos)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 0.2f, 0.1f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	float random = 0.0f;

	for (int i = 0; i < MAX_BULLET; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_BULLET * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		random = FloatRandom(BULLET_MOVE, BULLET_MOVE * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = 0.5f + FloatRandom(0.1f, -0.1f);

		// 生成
		CEffect::Create(pos, move, col);
	}
}

//--------------------------------------------------
// ボム
//--------------------------------------------------
void CEffectManager::Bom(const D3DXVECTOR3& pos)
{
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	CEffect* pEffect = nullptr;

	for (int i = 0; i < MAX_BOM; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_BOM * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		{// 外側
			move.x = sinf(rot) * BOM_MOVE;
			move.y = cosf(rot) * BOM_MOVE;

			// 生成
			pEffect = CEffect::Create(pos, move, col);

			// 当たり判定をしない
			pEffect->SetCollision(false);
		}

		{// 内側
			move.x = sinf(rot) * (BOM_MOVE * 0.75f);
			move.y = cosf(rot) * (BOM_MOVE * 0.75f);

			// 生成
			pEffect = CEffect::Create(pos, move, col);

			// 当たり判定をしない
			pEffect->SetCollision(false);
		}
	}

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Bom);
}

//--------------------------------------------------
// 背景
//--------------------------------------------------
void CEffectManager::BG()
{
	float width = CWall::STD_WIDTH * 0.7f;
	float height = CWall::STD_HEIGHT * 0.7f;

	D3DXVECTOR3 pos = D3DXVECTOR3(FloatRandom(width, -width), FloatRandom(height, -height), 0.0f);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	col.r = FloatRandom(1.0f, 0.0f);
	col.g = FloatRandom(1.0f, 0.0f);
	col.b = FloatRandom(1.0f, 0.0f);

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 randomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR randomCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
	float rot = 0.0f;
	float random = 0.0f;
	CEffect* pEffect = nullptr;

	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_PARTICLE * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(100.0f, 50.0f);

		random = FloatRandom(PARTICLE_MOVE, PARTICLE_MOVE * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		randomCol.r = col.r + FloatRandom(0.25f, -0.25f);
		randomCol.g = col.g + FloatRandom(0.25f, -0.25f);
		randomCol.b = col.b + FloatRandom(0.25f, -0.25f);

		// 生成
		pEffect = CEffect::Create(pos + randomPos, move, randomCol);

		// 色の減算をしない
		pEffect->SetColSubtract(false);

		// 当たり判定をしない
		pEffect->SetCollision(false);
	}
}
