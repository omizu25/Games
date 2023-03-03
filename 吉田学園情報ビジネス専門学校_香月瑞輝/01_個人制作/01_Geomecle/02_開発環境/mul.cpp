//**************************************************
// 
// mul.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "mul.h"
#include "object2D.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CMul::STD_WIDTH = 22.5f;
const float CMul::STD_HEIGHT = 30.0f;
const float CMul::MUL_SIZE = 20.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CMul* CMul::Create(const D3DXVECTOR3& pos)
{
	CMul* pMul = nullptr;

	pMul = new CMul;

	if (pMul != nullptr)
	{// nullチェック
		D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

		// 初期化
		pMul->Init(pos, size);
	}

	return pMul;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CMul::CMul() :
	m_pMul(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CMul::~CMul()
{
	assert(m_pMul == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CMul::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_pos = pos;

	// 初期化
	CScore::Init(pos, size);

	// 掛けるの生成
	m_pMul = CObject2D::Create();

	// サイズの設定
	m_pMul->SetSize(D3DXVECTOR3(MUL_SIZE, MUL_SIZE, 0.0f));

	float PosX = m_pos.x - STD_WIDTH - (MUL_SIZE * 0.5f);

	// 位置の設定
	m_pMul->SetPos(D3DXVECTOR3(PosX, m_pos.y, 0.0f));

	// テクスチャの設定
	m_pMul->SetTexture(CTexture::LABEL_Mul);

	// フェードの設定
	m_pMul->SetFade(0.0f);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CMul::Uninit()
{
	// 終了
	CScore::Uninit();

	if (m_pMul != nullptr)
	{// nullチェック
		// 終了
		m_pMul->Uninit();
		m_pMul = nullptr;
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CMul::Release()
{
	// 解放
	CScore::Release();

	if (m_pMul != nullptr)
	{// nullチェック
		// 解放
		m_pMul->Release();
		m_pMul = nullptr;
	}
}

//--------------------------------------------------
// 加算
//--------------------------------------------------
void CMul::Add()
{
	// 加算
	CNumberManager::Add(1);

	// カンマの描画
	CScore::DrawComma();

	int digit = Digit(CNumberManager::Get());
	int comma = (Digit(CNumberManager::Get()) - 1) / 3;
	float PosX = m_pos.x - (digit * STD_WIDTH) - (MUL_SIZE * 0.5f) - (comma * (STD_WIDTH * 0.5f));

	// 位置の設定
	m_pMul->SetPos(D3DXVECTOR3(PosX, m_pos.y, 0.0f));
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CMul::Set(int score)
{
	// 設定
	CNumberManager::Set(score);

	// カンマの描画
	CScore::DrawComma();

	int digit = Digit(CNumberManager::Get());
	int comma = (Digit(CNumberManager::Get()) - 1) / 3;
	float PosX = m_pos.x - (digit * STD_WIDTH) - (MUL_SIZE * 0.5f) - (comma * (STD_WIDTH * 0.5f));

	// 位置の設定
	m_pMul->SetPos(D3DXVECTOR3(PosX, m_pos.y, 0.0f));
}
