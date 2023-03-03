//**************************************************
// 
// score.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "score.h"
#include "application.h"
#include "game.h"
#include "mul.h"
#include "object2D.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CScore::STD_WIDTH = 30.0f;
const float CScore::STD_HEIGHT = 40.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CScore* CScore::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	CScore* pScore = nullptr;

	pScore = new CScore;

	if (pScore != nullptr)
	{// nullチェック
		// 初期化
		pScore->Init(pos, size);
	}

	return pScore;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CScore::CScore()
{
	for (int i = 0; i < MAX_COMMA; i++)
	{
		m_pComma[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CScore::~CScore()
{
	for (int i = 0; i < MAX_COMMA; i++)
	{
		assert(m_pComma[i] == nullptr);
	}
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CScore::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// 初期化
	CNumberManager::Init(pos, size);

	float interval = size.x * 0.5f;

	// 間隔の設定
	CNumberManager::SetInterval(3, interval);

	D3DXVECTOR3 commaSize = size * 0.5f;
	D3DXVECTOR3 commaPos = D3DXVECTOR3(pos.x, pos.y + (size.y * 0.5f) - (commaSize.y * 0.5f), 0.0f);
	float width = size.x * 3.0f;
	float halfInterval = interval * 0.5f;

	for (int i = 0; i < MAX_COMMA; i++)
	{
		// カンマの作成
		m_pComma[i] = CObject2D::Create();

		// サイズの設定
		m_pComma[i]->SetSize(commaSize);

		// テクスチャの設定
		m_pComma[i]->SetTexture(CTexture::LABEL_Comma);

		commaPos.x = pos.x - ((i * width) + (i * interval) + width + halfInterval);
		
		// 位置の設定
		m_pComma[i]->SetPos(commaPos);

		// 描画の設定
		m_pComma[i]->SetDraw(false);

		// フェードの設定
		m_pComma[i]->SetFade(0.0f);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CScore::Uninit()
{
	// 終了
	CNumberManager::Uninit();

	for (int i = 0; i < MAX_COMMA; i++)
	{
		if (m_pComma[i] != nullptr)
		{// nullチェック
			// 終了
			m_pComma[i]->Uninit();
			m_pComma[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CScore::Release()
{
	// 解放
	CNumberManager::Release();

	for (int i = 0; i < MAX_COMMA; i++)
	{
		if (m_pComma[i] != nullptr)
		{// nullチェック
			// 解放
			m_pComma[i]->Release();
			m_pComma[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 加算
//--------------------------------------------------
void CScore::Add(int score)
{
	CMode* pMode = CApplication::GetInstanse()->GetMode();

	if (CMode::MODE_GAME == pMode->Get())
	{// ゲーム中
		CGame* pGame = (CGame*)pMode;

		// 加算
		CNumberManager::Add(score + (score * pGame->GetMul()->Get()));
	}
	else
	{
		// 加算
		CNumberManager::Add(score);
	}

	// カンマの描画
	DrawComma();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CScore::Set(int score)
{
	// 設定
	CNumberManager::Set(score);

	// カンマの描画
	DrawComma();
}

//--------------------------------------------------
// 色の設定
//--------------------------------------------------
void CScore::SetCol(const D3DXCOLOR& col)
{
	// 色の設定
	CNumberManager::SetCol(col);

	for (int i = 0; i < MAX_COMMA; i++)
	{
		// 色の設定
		m_pComma[i]->SetCol(col);
	}
}

//--------------------------------------------------
// カンマの描画
//--------------------------------------------------
void CScore::DrawComma()
{
	for (int i = 0; i < MAX_COMMA; i++)
	{
		// 描画の設定
		m_pComma[i]->SetDraw(false);
	}

	int comma = (Digit(CNumberManager::Get()) - 1) / 3;

	for (int i = 0; i < comma; i++)
	{
		// 描画の設定
		m_pComma[i]->SetDraw(true);
	}
}

//--------------------------------------------------
// リセット
//--------------------------------------------------
void CScore::Reset(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, bool draw)
{
	float interval = size.x * 0.5f;

	// 位置の設定
	CNumberManager::SetPos(pos);

	D3DXVECTOR3 commaPos = D3DXVECTOR3(pos.x, 0.0f, 0.0f);
	float width = size.x * 3.0f;
	float halfInterval = interval * 0.5f;

	for (int i = 0; i < MAX_COMMA; i++)
	{
		commaPos.x = pos.x - ((i * width) + (i * interval) + width + halfInterval);

		commaPos.y = m_pComma[i]->GetPos().y;

		// 位置の設定
		m_pComma[i]->SetPos(commaPos);
	}

	if (!draw)
	{// 何も表示しない
		for (int i = 0; i < MAX_COMMA; i++)
		{
			// 描画の設定
			m_pComma[i]->SetDraw(false);
		}
	}
	else
	{
		for (int i = 0; i < MAX_COMMA; i++)
		{
			DrawComma();
		}
	}
}