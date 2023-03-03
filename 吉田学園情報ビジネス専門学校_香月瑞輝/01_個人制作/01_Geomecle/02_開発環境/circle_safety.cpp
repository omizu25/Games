//**************************************************
// 
// circle_safety.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "circle_safety.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CCircleSafety::COUNTDOWN_TIME = 120;
const int CCircleSafety::MAX_LIFE = 1200;
const D3DXCOLOR CCircleSafety::STD_COLOR = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR CCircleSafety::START_COLOR = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR CCircleSafety::END_COLOR = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR CCircleSafety::DIFF_COLOR = END_COLOR - START_COLOR;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CCircleSafety::CCircleSafety() :
	m_time(0),
	m_changeCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CCircleSafety::~CCircleSafety()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CCircleSafety::Init()
{
	m_time = 0;
	m_changeCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 初期化
	CCircle::Init();

	// 色の設定
	CObject3D::SetCol(STD_COLOR);

	// ライフの設定
	CCircle::SetLife(MAX_LIFE);

	// カウントダウンの時間の設定
	CCircle::SetTime(COUNTDOWN_TIME);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CCircleSafety::Uninit()
{
	// 終了
	CCircle::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CCircleSafety::Update()
{
	// 更新
	CCircle::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CCircleSafety::Draw()
{
	// 描画
	CCircle::Draw();
}

//--------------------------------------------------
// 出現か消滅
//--------------------------------------------------
bool CCircleSafety::Appear()
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

		float size = CObject3D::GetSize().x;

		m_changeCol = (DIFF_COLOR / ((size / DISAPPEAR_SPEED) * 0.75f));

		D3DXCOLOR col = START_COLOR;
		col.a = 1.0f - (CosCurve(m_time, 0.1f) * 0.9f);

		// 色の設定
		CObject3D::SetCol(col);
	}
	else
	{// カウントダウンしていない
		D3DXCOLOR col = CObject3D::GetCol();
		col.a = 1.0f;
		col += m_changeCol;

		if (col.r >= 1.0f)
		{// 赤色になった
			col = END_COLOR;
		}

		// 色の設定
		CObject3D::SetCol(col);
	}
	
	// 出現か消滅
	return CCircle::Appear();
}

//--------------------------------------------------
// 出現か消滅の設定
//--------------------------------------------------
void CCircleSafety::SetAppear(ECircle appear)
{
	if (appear == CCircle::CIRCLE_DISAPPEAR)
	{// 消滅
		float size = CObject3D::GetSize().x;

		m_changeCol = (DIFF_COLOR / ((size / DISAPPEAR_SPEED) * 0.75f));

		// 色の設定
		CObject3D::SetCol(START_COLOR);
	}

	// 出現か消滅の設定
	CCircle::SetAppear(appear);
}
