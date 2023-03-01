//**************************************************
// 
// exp.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "exp.h"
#include "wall.h"
#include "utility.h"
#include "application.h"
#include "player.h"
#include "game.h"
#include "mul.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CExp::MAX_EXP = 15;
const int CExp::STD_LIFE = 300;
const int CExp::BLINK_START = 200;
const float CExp::BLINK_SPEED = 0.1f;
const float CExp::HOMING_START = 150;
const float CExp::HOMING_SPEED = 7.5f;
const float CExp::STD_SIZE = 10.0f;
const float CExp::STD_ROTATION = 0.01f;
const float CExp::MAX_MOVE = 0.5f;
const float CExp::MAX_RADIUS = 25.0f;

//--------------------------------------------------
// 全ての生成
//--------------------------------------------------
void CExp::CreateAll(const D3DXVECTOR3& pos)
{
	float rot = 0.0f;
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < MAX_EXP; i++)
	{
		rot = FloatRandom(D3DX_PI * 2.0f, 0.0f);

		vec = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(MAX_RADIUS, 0.0f);

		// 生成
		Create(pos + vec, rot);
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CExp* CExp::Create(const D3DXVECTOR3& pos, float rot)
{
	CExp* pExp = nullptr;

	pExp = new CExp;

	if (pExp != nullptr)
	{// nullチェック
		pExp->Init();
		pExp->SetPos(pos);
		pExp->SetMove(rot);
	}

	return pExp;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CExp::CExp() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_life(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CExp::~CExp()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CExp::Init()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_life = 0;

	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject3D::TYPE_EXP);

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_Homing);

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CExp::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CExp::Update()
{
	m_life++;

	if (m_life >= STD_LIFE)
	{// 寿命が来た
		// 解放
		CObject::Release();
	}
	else if (m_life >= BLINK_START)
	{// 点滅開始
		D3DXCOLOR col = CObject3D::GetCol();

		col.a = SinCurve(m_life, BLINK_SPEED);

		// 色の設定
		CObject3D::SetCol(col);
	}

	D3DXVECTOR3 pos = CObject3D::GetPos() + m_move;

	// 位置の設定
	CObject3D::SetPos(pos);

	float rot = CObject3D::GetRot();

	rot += STD_ROTATION;

	// 向きの設定
	CObject3D::SetRot(rot);

	// 吸収
	Absorption();

	// 壁
	Wall();

	// 当たり判定
	Collision();

	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CExp::Draw()
{
	// 描画
	CObject3D::Draw();
}

//--------------------------------------------------
// 移動量の設定
//--------------------------------------------------
void CExp::SetMove(float rot)
{
	// 向きの設定
	CObject3D::SetRot(rot);

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(MAX_MOVE, 0.0f);
}

//--------------------------------------------------
// 当たり判定
//--------------------------------------------------
void CExp::Collision()
{
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// nullチェック
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();
	float size = CObject3D::GetSize().x * 0.5f;

	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	float playerSize = pPlayer->GetSize().x * 0.5f;

	if (CollisionCircle(pos, size, playerPos, playerSize))
	{// 当たり判定
		// 倍率の加算
		pGame->GetMul()->Add();

		// 解放
		CObject::Release();
		return;
	}
}

//==================================================
// 吸収
//==================================================
void CExp::Absorption()
{
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// nullチェック
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	D3DXVECTOR3 vecDiff = playerPos - pos;

	float length = D3DXVec3Length(&vecDiff);

	if (length <= HOMING_START)
	{// ホーミングする
		// ホーミング
		Homing(&pos, pos, playerPos, HOMING_SPEED);
	}

	// 位置の設定
	CObject3D::SetPos(pos);
}

//==================================================
// 壁
//==================================================
void CExp::Wall()
{
	D3DXVECTOR3 pos = CObject3D::GetPos() + m_move;
	float size = (CObject3D::GetSize().x * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	// 範囲内で反射
	InRangeReflect(&pos, &m_move, D3DXVECTOR3(width, height, 0.0f));
}
