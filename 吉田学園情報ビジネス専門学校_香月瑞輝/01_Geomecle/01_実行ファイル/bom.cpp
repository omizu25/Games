//**************************************************
// 
// bom.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "bom.h"
#include "object2D.h"
#include "object3D.h"
#include "input.h"
#include "effect_manager.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CBom::STD_SIZE = 20.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CBom* CBom::Create(const D3DXVECTOR3& pos)
{
	CBom* pBom = nullptr;

	pBom = new CBom;

	if (pBom != nullptr)
	{// nullチェック
		// 初期化
		pBom->Init(pos);
	}

	return pBom;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CBom::CBom() :
	m_bom(0)
{
	for (int i = 0; i < MAX_BOM; i++)
	{
		m_pObj[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CBom::~CBom()
{
	for (int i = 0; i < MAX_BOM; i++)
	{
		assert(m_pObj[i] == nullptr);
	}
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CBom::Init(const D3DXVECTOR3& pos)
{
	D3DXVECTOR3 size = D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f);
	m_bom = MAX_BOM;
	
	float halfWidth = size.x * 0.5f;

	float posX = 0.0f;

	for (int i = 0; i < MAX_BOM; i++)
	{
		// 生成
		m_pObj[i] = CObject2D::Create();

		posX = pos.x + (halfWidth + (size.x * i));

		// 位置の設定
		m_pObj[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));

		// サイズの設定
		m_pObj[i]->SetSize(size);

		// テクスチャの設定
		m_pObj[i]->SetTexture(CTexture::LABEL_Bom);

		// フェードの設定
		m_pObj[i]->SetFade(0.0f);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CBom::Uninit()
{
	for (int i = 0; i < MAX_BOM; i++)
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
void CBom::Release()
{
	for (int i = 0; i < MAX_BOM; i++)
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
// 更新
//--------------------------------------------------
void CBom::Update()
{
	if (CInput::GetKey()->Trigger(CInput::KEY_BOM))
	{// ボム用キーが押された
		if (m_bom > 0)
		{// ボムがまだある
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
			CPlayer* pPlayer = pGame->GetPlayer();

			if (pPlayer != nullptr)
			{// nullチェック
				pos = pPlayer->GetPos();
			}

			 // パーティクル
			CEffectManager::GetInstanse()->Bom(pos);

			// 敵の全ての解放
			CObject3D::ReleaseAll(CObject3D::TYPE_ENEMY);

			// EXPの全ての解放
			CObject3D::ReleaseAll(CObject3D::TYPE_EXP);
		}

		// 減少
		Sub();
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int CBom::Get()
{
	return m_bom;
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
void CBom::Reset()
{
	m_bom = MAX_BOM;

	for (int i = 0; i < MAX_BOM; i++)
	{
		m_pObj[i]->SetDraw(false);
	}

	for (int i = 0; i < m_bom; i++)
	{
		m_pObj[i]->SetDraw(true);
	}
}

//--------------------------------------------------
// 減算
//--------------------------------------------------
void CBom::Sub()
{
	m_bom--;

	if (m_bom <= 0)
	{// 指定の値以下
		m_bom = 0;
	}

	for (int i = 0; i < MAX_BOM; i++)
	{
		m_pObj[i]->SetDraw(false);
	}

	for (int i = 0; i < m_bom; i++)
	{
		m_pObj[i]->SetDraw(true);
	}
}
