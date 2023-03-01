//**************************************************
// 
// menu.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "menu.h"
#include "object2D.h"
#include "utility.h"
#include "input.h"
#include "application.h"
#include "sound.h"
#include "mode.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CMenu::CURSOR_INTERVAL = 30.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CMenu* CMenu::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int numUse, float interval, bool sort, bool cursor)
{
	CMenu* pMenu = nullptr;

	pMenu = new CMenu;

	if (pMenu != nullptr)
	{// nullチェック
		// 初期化
		pMenu->Init(pos, size, numUse, interval, sort, cursor);
	}

	return pMenu;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CMenu::CMenu() :
	m_pFrame(nullptr),
	m_pCursor(nullptr),
	m_selectIdx(0),
	m_numUse(0),
	m_time(0),
	m_sort(false)
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		m_pOption[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CMenu::~CMenu()
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		assert(m_pOption[i] == nullptr);
	}

	assert(m_pFrame == nullptr);
	assert(m_pCursor == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CMenu::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int numUse, float interval, bool sort, bool cursor)
{
	assert(numUse > 0 && numUse <= MAX_OPTION);

	m_numUse = numUse;
	m_sort = sort;
	m_selectIdx = 0;
	m_time = 0;

	// 枠の作成
	m_pFrame = CObject2D::Create();

	// 描画の設定
	m_pFrame->SetDraw(false);

	// 位置の設定
	m_pFrame->SetPos(pos);

	// フェードの設定
	m_pFrame->SetFade(0.0f);

	D3DXVECTOR3 optionPos = pos;

	if (m_sort)
	{// 縦
		optionPos.y -= ((m_numUse - 1) * ((size.y * 0.5f) + (interval * 0.5f)));
	}
	else
	{// 横
		optionPos.x -= ((m_numUse - 1) * ((size.x * 0.5f) + (interval * 0.5f)));
	}

	if (cursor)
	{// カーソルを使用する
		// カーソルの作成
		m_pCursor = CObject2D::Create();

		float cursorSize = size.y * 0.8f;
		D3DXVECTOR3 cursorPos = optionPos;
		cursorPos.x -= ((cursorSize * 0.5f) + (size.x * 0.5f) + CURSOR_INTERVAL);

		// 位置の設定
		m_pCursor->SetPos(cursorPos);

		// サイズの設定
		m_pCursor->SetSize(D3DXVECTOR3(cursorSize, cursorSize, 0.0f));

		// テクスチャの設定
		m_pCursor->SetTexture(CTexture::LABEL_Cursor);

		// フェードの設定
		m_pCursor->SetFade(0.0f);
	}
	else
	{
		m_pCursor = nullptr;
	}
	
	for (int i = 0; i < MAX_OPTION; i++)
	{
		if (i >= m_numUse)
		{// 指定の値以上
			m_pOption[i] = nullptr;
			continue;
		}

		// 選択肢の作成
		m_pOption[i] = CObject2D::Create();

		// 位置の設定
		m_pOption[i]->SetPos(optionPos);

		// サイズの設定
		m_pOption[i]->SetSize(size);

		// フェードの設定
		m_pOption[i]->SetFade(0.0f);

		if (m_sort)
		{// 縦
			optionPos.y += size.y + interval;
		}
		else
		{// 横
			optionPos.x += size.x + interval;
		}
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CMenu::Uninit()
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		if (m_pOption[i] != nullptr)
		{// nullチェック
			// 終了
			m_pOption[i]->Uninit();
			m_pOption[i] = nullptr;
		}
	}

	if (m_pFrame != nullptr)
	{// nullチェック
		// 終了
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pCursor != nullptr)
	{// nullチェック
		// 終了
		m_pCursor->Uninit();
		m_pCursor = nullptr;
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CMenu::Release()
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		if (m_pOption[i] != nullptr)
		{// nullチェック
			// 解放
			m_pOption[i]->Release();
			m_pOption[i] = nullptr;
		}
	}

	if (m_pFrame != nullptr)
	{// nullチェック
		// 解放
		m_pFrame->Release();
		m_pFrame = nullptr;
	}

	if (m_pCursor != nullptr)
	{// nullチェック
		// 解放
		m_pCursor->Release();
		m_pCursor = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CMenu::Update()
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		if (m_pOption[i] != nullptr)
		{// nullチェック
			// 更新
			m_pOption[i]->Update();
		}
	}

	if (m_pFrame != nullptr)
	{// nullチェック
		 // 更新
		m_pFrame->Update();
	}

	if (m_pCursor != nullptr)
	{// nullチェック
		// 更新
		m_pCursor->Update();
	}
}

//--------------------------------------------------
// 選択
//--------------------------------------------------
int CMenu::Select()
{
	m_time++;

	if (m_time <= CMode::FADE_TIME)
	{// フェード中
		return -1;
	}

	CInput* pInput = CInput::GetKey();

	if (m_sort)
	{// 縦
		if (pInput->Trigger(CInput::KEY_UP))
		{// 上キーが押された
			Add(-1);
		}
		if (pInput->Trigger(CInput::KEY_DOWN))
		{// 下キーが押された
			Add(1);
		}
	}
	else
	{// 横
		if (pInput->Trigger(CInput::KEY_LEFT))
		{// 左キーが押された
			Add(-1);
		}
		if (pInput->Trigger(CInput::KEY_RIGHT))
		{// 右キーが押された
			Add(1);
		}
	}

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.a = 1.0f - (CosCurve(m_time, 0.025f) * 0.7f);

	// 色の設定
	m_pOption[m_selectIdx]->SetCol(col);

	if (pInput->Trigger(CInput::KEY_DECISION))
	{// 決定キーが押された
		// SE
		CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Enter);

		return m_selectIdx;
	}

	return -1;
}

//--------------------------------------------------
// フレームの設定
//--------------------------------------------------
void CMenu::SetFrame(const D3DXVECTOR3& size, const D3DXCOLOR& col)
{
	if (m_pFrame->GetDraw())
	{// すでにフレームがある
		m_pFrame->SetSize(size);
		return;
	}

	// サイズの設定
	m_pFrame->SetSize(size);

	// 色の設定
	m_pFrame->SetCol(col);

	// 描画の設定
	m_pFrame->SetDraw(true);
}

//--------------------------------------------------
// テクスチャの設定
//--------------------------------------------------
void CMenu::SetTexture(int idx, CTexture::ELabel label)
{
	if (idx == -1)
	{// 指定の値
		m_pFrame->SetTexture(label);
		return;
	}

	assert(idx >= 0 && idx < MAX_OPTION);

	if (m_pOption[idx] != nullptr)
	{// nullチェック
		m_pOption[idx]->SetTexture(label);
	}
}

//--------------------------------------------------
// 加算
//--------------------------------------------------
void CMenu::Add(int add)
{
	// 色の設定
	m_pOption[m_selectIdx]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_selectIdx = ((m_selectIdx + add) + m_numUse) % m_numUse;

	m_time = 0;

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Select);

	if (m_pCursor != nullptr)
	{// nullチェック
		D3DXVECTOR3 pos = m_pOption[m_selectIdx]->GetPos();
		D3DXVECTOR3 optionSize = m_pOption[m_selectIdx]->GetSize();
		D3DXVECTOR3 cursorSize = m_pCursor->GetSize();
		pos.x -= ((optionSize.x * 0.5f) + (cursorSize.x * 0.5f) + CURSOR_INTERVAL);

		// 位置の設定
		m_pCursor->SetPos(pos);
	}
}

//--------------------------------------------------
// 選択されている番号の取得
//--------------------------------------------------
int CMenu::GetSelectIdx()
{
	return m_selectIdx;
}
