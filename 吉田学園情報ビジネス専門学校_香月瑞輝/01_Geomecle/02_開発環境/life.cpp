//**************************************************
// 
// life.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "life.h"
#include "object2D.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CLife::STD_SIZE = 20.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CLife* CLife::Create(const D3DXVECTOR3& pos)
{
	CLife* pLife = nullptr;

	pLife = new CLife;

	if (pLife != nullptr)
	{// nullチェック
		// 初期化
		pLife->Init(pos);
	}

	return pLife;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CLife::CLife() :
	m_life(0)
{
	for (int i = 0; i < MAX_LIFE; i++)
	{
		m_pObj[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CLife::~CLife()
{
	for (int i = 0; i < MAX_LIFE; i++)
	{
		assert(m_pObj[i] == nullptr);
	}
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CLife::Init(const D3DXVECTOR3& pos)
{
	D3DXVECTOR3 size = D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f);
	m_life = MAX_LIFE;
	
	float halfWidth = size.x * 0.5f;

	float posX = 0.0f;

	for (int i = 0; i < MAX_LIFE; i++)
	{
		// 生成
		m_pObj[i] = CObject2D::Create();

		posX = pos.x - (halfWidth + (size.x * i));

		// 位置の設定
		m_pObj[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));

		// サイズの設定
		m_pObj[i]->SetSize(size);

		// テクスチャの設定
		m_pObj[i]->SetTexture(CTexture::LABEL_Player);

		// フェードの設定
		m_pObj[i]->SetFade(0.0f);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CLife::Uninit()
{
	for (int i = 0; i < MAX_LIFE; i++)
	{
		if (m_pObj[i] != nullptr)
		{// nullチェック
			// 終了
			m_pObj[i]->Uninit();
			m_pObj[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CLife::Release()
{
	for (int i = 0; i < MAX_LIFE; i++)
	{
		if (m_pObj[i] != nullptr)
		{// nullチェック
			// 解放
			m_pObj[i]->Release();
			m_pObj[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 減算
//--------------------------------------------------
void CLife::Sub()
{
	m_life--;

	if (m_life <= 0)
	{// 指定の値以下
		m_life = 0;
	}

	for (int i = 0; i < MAX_LIFE; i++)
	{
		m_pObj[i]->SetDraw(false);
	}

	for (int i = 0; i < m_life; i++)
	{
		m_pObj[i]->SetDraw(true);
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int CLife::Get()
{
	return m_life;
}
