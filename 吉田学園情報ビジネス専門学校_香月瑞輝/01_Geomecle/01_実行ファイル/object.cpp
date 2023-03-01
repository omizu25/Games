//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "object.h"
#include "instancing.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const int CObject::MAX_OBJECT[]
{
	1024,
	50000,
	256
};

//==================================================
// 静的メンバ変数
//==================================================
int CObject::m_numAll = 0;
CObject** CObject::m_pObject[CATEGORY_MAX];
CInstancing* CObject::m_pInstancing = nullptr;

//--------------------------------------------------
// 生成
//--------------------------------------------------
void CObject::Create()
{
	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		m_pObject[i] = new CObject* [MAX_OBJECT[i]];
	}

	for (int numCat = 0; numCat < CATEGORY_MAX; numCat++)
	{
		for (int numObj = 0; numObj < MAX_OBJECT[numCat]; numObj++)
		{
			m_pObject[numCat][numObj] = nullptr;
		}
	}

	if (m_pInstancing == nullptr)
	{// nullチェック
		m_pInstancing = CInstancing::Create();
	}
}

//--------------------------------------------------
// 破棄
//--------------------------------------------------
void CObject::Delete()
{
	// 全ての解放
	ReleaseAll(true);

	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		delete[] m_pObject[i];
	}

	if (m_pInstancing != nullptr)
	{// nullチェック
		m_pInstancing->Uninit();
	}
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CObject::ReleaseAll(bool releaseKeep)
{
	for (int numCat = 0; numCat < CATEGORY_MAX; numCat++)
	{
		for (int numObj = 0; numObj < MAX_OBJECT[numCat]; numObj++)
		{
			if (m_pObject[numCat][numObj] == nullptr)
			{// NULLチェック
				continue;
			}

			if (!releaseKeep && m_pObject[numCat][numObj]->m_keep)
			{// キープしてあるものは解放しない
				continue;
			}

			// オブジェクトの開放
			m_pObject[numCat][numObj]->Release();
		}
	}
}

//--------------------------------------------------
// 全ての更新
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int numCat = 0; numCat < CATEGORY_MAX; numCat++)
	{
		for (int numObj = 0; numObj < MAX_OBJECT[numCat]; numObj++)
		{
			if (m_pObject[numCat][numObj] == nullptr)
			{// NULLチェック
				continue;
			}

			// オブジェクトの更新
			m_pObject[numCat][numObj]->Update();
		}
	}
}

//--------------------------------------------------
// 全ての描画
//--------------------------------------------------
void CObject::DrawAll()
{
	for (int numObj = 0; numObj < MAX_OBJECT[CATEGORY_3D]; numObj++)
	{
		if (m_pObject[CATEGORY_3D][numObj] == nullptr)
		{// NULLチェック
			continue;
		}

		// オブジェクトの描画
		m_pObject[CATEGORY_3D][numObj]->Draw();
	}

	if (m_pInstancing != nullptr)
	{// nullチェック
		m_pInstancing->Draw();
	}

	for (int numObj = 0; numObj < MAX_OBJECT[CATEGORY_2D]; numObj++)
	{
		if (m_pObject[CATEGORY_2D][numObj] == nullptr)
		{// NULLチェック
			continue;
		}

		// オブジェクトの描画
		m_pObject[CATEGORY_2D][numObj]->Draw();
	}
}

//--------------------------------------------------
// 総数の取得
//--------------------------------------------------
int CObject::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// 最大数の取得
//--------------------------------------------------
int CObject::GetMax(ECategory cat)
{
	return MAX_OBJECT[cat];
}

//--------------------------------------------------
// オブジェクトの取得
//--------------------------------------------------
CObject** CObject::GetMyObject(ECategory cat)
{
	assert(cat > CATEGORY_NONE && cat < CATEGORY_MAX);

	return m_pObject[cat];
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CObject::CObject(ECategory cat) :
	m_keep(false)
{
	static_assert(sizeof(MAX_OBJECT) / sizeof(MAX_OBJECT[0]) == CATEGORY_MAX, "aho");

	assert(cat > CATEGORY_NONE && cat < CATEGORY_MAX);

	for (int i = 0; i < MAX_OBJECT[cat]; i++)
	{
		if (m_pObject[cat][i] == nullptr)
		{// nullチェック
			m_pObject[cat][i] = this;
			m_cat = cat;
			m_index = i;
			m_numAll++;
			break;
		}
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CObject::~CObject()
{
	m_numAll--;
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CObject::Release()
{
	if (m_pObject[m_cat][m_index] != nullptr)
	{// NULLチェック
		int index = m_index;
		int cat = m_cat;
		m_pObject[cat][index]->Uninit();
		delete m_pObject[cat][index];
		m_pObject[cat][index] = nullptr;
	}
}

//--------------------------------------------------
// ずっと持っているかの設定
//--------------------------------------------------
void CObject::SetKeep(bool keep)
{
	m_keep = keep;
}
