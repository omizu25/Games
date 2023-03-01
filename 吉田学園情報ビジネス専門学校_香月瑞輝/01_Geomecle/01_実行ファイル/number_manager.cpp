//**************************************************
// 
// number_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// ƒCƒ“ƒNƒ‹[ƒh
//==================================================
#include "number_manager.h"
#include "number.h"
#include "utility.h"
#include <assert.h>

//--------------------------------------------------
// ¶¬
//--------------------------------------------------
CNumberManager* CNumberManager::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int value)
{
	CNumberManager* pNumberManager = nullptr;

	pNumberManager = new CNumberManager;

	if (pNumberManager != nullptr)
	{// nullƒ`ƒFƒbƒN
		// ‰Šú‰»
		pNumberManager->Init(pos, size);

		// ”‚Ìİ’è
		pNumberManager->Set(value);
	}

	return pNumberManager;
}

//--------------------------------------------------
// ƒfƒtƒHƒ‹ƒgƒRƒ“ƒXƒgƒ‰ƒNƒ^
//--------------------------------------------------
CNumberManager::CNumberManager() :
	m_value(0),
	m_zeroDigit(0),
	m_interval(0),
	m_width(0.0f),
	m_zero(false)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		m_number[i] = nullptr;
	}
}

//--------------------------------------------------
// ƒfƒXƒgƒ‰ƒNƒ^
//--------------------------------------------------
CNumberManager::~CNumberManager()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		assert(m_number[i] == nullptr);
	}
}

//--------------------------------------------------
// ‰Šú‰»
//--------------------------------------------------
void CNumberManager::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_value = 0;
	m_interval = 0;
	m_width = 0.0f;
	m_zero = false;
	m_zeroDigit = MAX_DIGIT;

	float halfWidth = size.x * 0.5f;

	float posX = 0.0f;

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		posX = pos.x - (halfWidth + (size.x * i));

		// ¶¬
		m_number[i] = CNumber::Create(D3DXVECTOR3(posX, pos.y, 0.0f), size);
	}
	
	// •ÏX
	Change();

	// ƒ[ƒ‚Ì•`‰æ
	ZeroDraw();
}

//--------------------------------------------------
// I—¹
//--------------------------------------------------
void CNumberManager::Uninit()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (m_number[i] != nullptr)
		{
			// I—¹
			m_number[i]->Uninit();
			m_number[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ‰ğ•ú
//--------------------------------------------------
void CNumberManager::Release()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (m_number[i] != nullptr)
		{
			// ‰ğ•ú
			m_number[i]->Release();
			m_number[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ‰ÁZ
//--------------------------------------------------
void CNumberManager::Add(int value)
{
	m_value += value;

	// •ÏX
	Change();
}

//--------------------------------------------------
// İ’è
//--------------------------------------------------
void CNumberManager::Set(int value)
{
	m_value = value;

	// •ÏX
	Change();
}

//--------------------------------------------------
// æ“¾
//--------------------------------------------------
int CNumberManager::Get()
{
	return m_value;
}

//--------------------------------------------------
// ˆÊ’u‚Ìİ’è
//--------------------------------------------------
void CNumberManager::SetPos(const D3DXVECTOR3& pos)
{
	D3DXVECTOR3 size = m_number[0]->GetSize();
	float halfWidth = size.x * 0.5f;

	float posX = 0.0f;

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		posX = pos.x - ((halfWidth + (size.x * i)) + ((i / m_interval) * m_width));

		// ¶¬
		m_number[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// F‚Ìİ’è
//--------------------------------------------------
void CNumberManager::SetCol(const D3DXCOLOR& col)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// F‚Ìİ’è
		m_number[i]->SetCol(col);
	}
}

//--------------------------------------------------
// •`‰æ‚Ìİ’è
//--------------------------------------------------
void CNumberManager::SetDraw(bool draw)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// •`‰æ‚Ìİ’è
		m_number[i]->SetDraw(draw);
	}
}

//--------------------------------------------------
// ƒ[ƒ‚Ìİ’è
//--------------------------------------------------
void CNumberManager::SetZero(bool zero)
{
	m_zero = zero;

	// ƒ[ƒ‚Ì•`‰æ
	ZeroDraw();
}

//--------------------------------------------------
// ƒ[ƒ‚ÌŒ…”‚Ìİ’è
//--------------------------------------------------
void CNumberManager::SetZeroDigit(int digit)
{
	m_zeroDigit = digit;

	// ƒ[ƒ‚Ì•`‰æ
	ZeroDraw();
}

//--------------------------------------------------
// ŠÔŠu‚Ìİ’è
//--------------------------------------------------
void CNumberManager::SetInterval(int interval, float width)
{
	m_interval = interval;
	m_width = width;

	if (m_interval == 0)
	{// ŠÔŠu‚Í‚¢‚ç‚È‚¢
		m_interval = 1;
		m_width = 0.0f;
	}

	D3DXVECTOR3 size = m_number[0]->GetSize();
	float halfWidth = size.x * 0.5f;

	D3DXVECTOR3 pos = m_number[0]->GetPos();
	pos.x += halfWidth;

	float posX = 0.0f;

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		posX = pos.x - ((halfWidth + (size.x * i)) + ((i / m_interval) * m_width));

		// ¶¬
		m_number[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// •`‰æ‚Ìİ’è
//--------------------------------------------------
void CNumberManager::ZeroDraw()
{
	if (m_zero)
	{// ƒ[ƒ‚ğ•`‰æ‚·‚é
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			m_number[i]->SetDraw(false);
		}

		for (int i = 0; i < m_zeroDigit; i++)
		{
			m_number[i]->SetDraw(true);
		}
	}
	else
	{// ƒ[ƒ‚ğ•`‰æ‚µ‚È‚¢
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			m_number[i]->SetDraw(false);
		}

		for (int i = 0; i < Digit(m_value); i++)
		{
			m_number[i]->SetDraw(true);
		}
	}

	// 1Œ…–Ú‚Íâ‘Î‚É•`‰æ‚·‚é
	m_number[0]->SetDraw(true);
}

//--------------------------------------------------
// •ÏX
//--------------------------------------------------
void CNumberManager::Change()
{
	int num[MAX_DIGIT];

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		num[i] = 0;
	}

	int saveValue = m_value;

	for (int i = 0; i < Digit(m_value); i++)
	{// ˆêŒ…‚¸‚Â‚É•ª‚¯‚é
		num[i] = saveValue % 10;
		saveValue /= 10;
	}

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// ”‚Ì•ÏX
		m_number[i]->Change(num[i]);
	}

	// ƒ[ƒ‚Ì•`‰æ
	ZeroDraw();
}
