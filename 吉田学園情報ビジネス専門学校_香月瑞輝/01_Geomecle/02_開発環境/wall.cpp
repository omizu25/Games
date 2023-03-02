//**************************************************
// 
// wall.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "wall.h"
#include <assert.h>

//==================================================
// インクルード
//==================================================
const float CWall::STD_SIZE = 10.0f;
const float CWall::STD_WIDTH = 1300.0f;
const float CWall::STD_HEIGHT = 900.0f;

//--------------------------------------------------
// 全ての生成
//--------------------------------------------------
void CWall::AllCreate()
{
	{// 上下の壁
		D3DXVECTOR3 size = D3DXVECTOR3(CWall::STD_WIDTH, CWall::STD_SIZE, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, CWall::STD_HEIGHT * 0.5f, 0.0f);

		// 上の壁
		CWall::Create(pos, size);

		// 下の壁
		CWall::Create(-pos, size);
	}

	{// 左右の壁
		D3DXVECTOR3 size = D3DXVECTOR3(CWall::STD_SIZE, CWall::STD_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(CWall::STD_WIDTH * 0.5f, 0.0f, 0.0f);

		// 右の壁
		CWall::Create(pos, size);

		// 左の壁
		CWall::Create(-pos, size);
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CWall* CWall::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	CWall* pWall = nullptr;

	pWall = new CWall;

	if (pWall != nullptr)
	{// nullチェック
		pWall->Init();
		pWall->SetPos(pos);
		pWall->SetSize(size);
	}

	return pWall;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CWall::CWall()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CWall::~CWall()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CWall::Init()
{
	// 初期化
	CObject3D::Init();

	// キープの設定
	CObject::SetKeep(true);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CWall::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CWall::Update()
{
	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CWall::Draw()
{
	// 描画
	CObject3D::Draw();
}
