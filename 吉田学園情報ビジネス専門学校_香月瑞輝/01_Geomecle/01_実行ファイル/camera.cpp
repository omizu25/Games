//**************************************************
// 
// camera.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "camera.h"
#include "application.h"
#include "game.h"
#include "utility.h"
#include "player.h"
#include "wall.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CCamera::MAX_NEAR = 10.0f;
const float CCamera::MAX_FAR = 2500.0f;
const float CCamera::MAX_DISTANCE = -500.0f;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CCamera::CCamera() :
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vecU(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	memset(m_mtxProj, 0, sizeof(m_mtxProj));
	memset(m_mtxView, 0, sizeof(m_mtxView));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CCamera::~CCamera()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CCamera::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posDest = m_pos;
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 固定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = m_rot;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CCamera::Uninit()
{
	
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CCamera::Update()
{
	CMode* pMode = CApplication::GetInstanse()->GetMode();

	if (CMode::MODE_GAME != pMode->Get())
	{// 指定のモードではない
		// ホーミング
		Homing(&m_pos, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5.0f);
		return;
	}

	CGame* pGame = (CGame*)pMode;
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// nullチェック
		// ホーミング
		Homing(&m_pos, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5.0f);
		return;
	}
	
	D3DXVECTOR3 pos = pPlayer->GetPos();

	D3DXVECTOR3 vecDiff = pos - m_pos;

	float length = D3DXVec3Length(&vecDiff);

	// ホーミング
	Homing(&m_pos, m_pos, pos, length);

	float size = CWall::STD_SIZE * 0.5f;
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	// 範囲内
	InRange(&m_pos, D3DXVECTOR3(width * 0.3f, height * 0.3f, 0.0f));

	m_pos.z = 0.0f;	// これをしないとバグる
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CCamera::Set()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 pos = D3DXVECTOR3(m_pos.x, m_pos.y, MAX_DISTANCE);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&pos,
		&m_pos,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProj);

	// プロジェクションマトリックスの作成(平行投影)
	D3DXMatrixOrthoLH(&m_mtxProj,			// プロジェクションマトリックス
		(float)CApplication::SCREEN_WIDTH,	// 幅
		(float)CApplication::SCREEN_HEIGHT,	// 高さ
		MAX_NEAR,							// ニア
		MAX_FAR);							// ファー
	
	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
}

//--------------------------------------------------
// 位置の設定
//--------------------------------------------------
void CCamera::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//--------------------------------------------------
// 位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CCamera::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// プロジェクションの取得
//--------------------------------------------------
const D3DXMATRIX& CCamera::GetProj() const
{
	return m_mtxProj;
}

//--------------------------------------------------
// ビューの取得
//--------------------------------------------------
const D3DXMATRIX& CCamera::GetView() const
{
	return m_mtxView;
}
