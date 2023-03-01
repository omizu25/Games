//**************************************************
// 
// circle_danger.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "circle_danger.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CCircleDanger::COUNTDOWN_TIME = 60;
const int CCircleDanger::MAX_LIFE = 900;
const int CCircleDanger::MIN_LIFE = 120;
const D3DXCOLOR CCircleDanger::STD_COLOR = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CCircleDanger::CCircleDanger() :
	m_time(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CCircleDanger::~CCircleDanger()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CCircleDanger::Init()
{
	m_time = 0;

	// 初期化
	CCircle::Init();

	// 色の設定
	CObject3D::SetCol(STD_COLOR);

	// ライフの設定
	CCircle::SetLife(IntRandom(MAX_LIFE, MIN_LIFE));

	// カウントダウンの時間の設定
	CCircle::SetTime(COUNTDOWN_TIME);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CCircleDanger::Uninit()
{
	// 終了
	CCircle::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CCircleDanger::Update()
{
	// 更新
	CCircle::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CCircleDanger::Draw()
{
	// 描画
	CCircle::Draw();
}

//--------------------------------------------------
// 出現か消滅
//--------------------------------------------------
bool CCircleDanger::Appear()
{
	if (CCircle::GetAppear() != CCircle::CIRCLE_DISAPPEAR)
	{// 消滅中ではない
		// 出現か消滅
		return CCircle::Appear();
	}

	/* 消滅中 */

	if (CCircle::GetCountDown())
	{// カウントダウン中
		m_time++;

		D3DXCOLOR col = CObject3D::GetCol();

		col.a = 1.0f - (CosCurve(m_time, 0.1f) * 0.9f);

		// 色の設定
		CObject3D::SetCol(col);
	}
	else
	{// カウントダウンしていない
		m_time++;

		D3DXCOLOR col = CObject3D::GetCol();

		col.a = 1.0f - (CosCurve(m_time, 0.1f) * 0.9f);

		// 色の設定
		CObject3D::SetCol(col);
	}

	// 出現か消滅
	return CCircle::Appear();
}

//--------------------------------------------------
// 出現か消滅の設定
//--------------------------------------------------
void CCircleDanger::SetAppear(ECircle appear)
{
	if (CCircle::GetAppear() == CCircle::CIRCLE_DISAPPEAR)
	{// 消滅
		m_time = 0;
	}

	// 出現か消滅の設定
	CCircle::SetAppear(appear);
}
