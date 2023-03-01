//**************************************************
// 
// object3D.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "object3D.h"
#include "application.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const DWORD CObject3D::FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
const int CObject3D::NUM_VERTEX = 4;
const int CObject3D::NUM_POLYGON = 2;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CObject3D* CObject3D::Create()
{
	CObject3D* pObject3D = nullptr;

	pObject3D = new CObject3D;

	if (pObject3D != nullptr)
	{// nullチェック
		pObject3D->Init();
	}

	return pObject3D;
}

//--------------------------------------------------
// 存在するかどうか
//--------------------------------------------------
bool CObject3D::Exist(EType type)
{
	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);

	for (int i = 0; i < objMax; i++)
	{
		if (pObject[i] == nullptr)
		{// nullチェック
			continue;
		}

		if (pObject[i]->m_type == type)
		{// 指定の値と同じ
			return true;
		}
	}

	return false;
}

//--------------------------------------------------
// 指定のタイプの全ての解放
//--------------------------------------------------
void CObject3D::ReleaseAll(EType type)
{
	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);

	for (int i = 0; i < objMax; i++)
	{
		if (pObject[i] == nullptr)
		{// nullチェック
			continue;
		}

		if (pObject[i]->m_type == type)
		{// 指定の値と同じ
			// 解放
			pObject[i]->Release();
		}
	}
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CObject3D::CObject3D(CObject::ECategory cat) : CObject(cat),
	m_type(TYPE_NONE),
	m_texture(CTexture::LABEL_NONE),
	m_rot(0.0f),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_pVtxBuff(nullptr),
	m_collision(false)
{
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CObject3D::~CObject3D()
{
	assert(m_pVtxBuff == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CObject3D::Init()
{
	m_rot = 0.0f;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_texture = CTexture::LABEL_NONE;
	m_collision = true;

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CObject3D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{// 頂点バッファの破棄
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CObject3D::Update()
{
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CObject3D::Draw()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture* pTexture = CApplication::GetInstanse()->GetTexture();

	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->Get(m_texture));

	D3DXMATRIX mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転の反映
	D3DXMatrixRotationZ(&m_mtxWorld, -m_rot);

	// 位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, 0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,						// 描画する最初の頂点インデックス
		NUM_POLYGON);			// プリミティブ(ポリゴン)数
}

//--------------------------------------------------
// 位置の設定
//--------------------------------------------------
void CObject3D::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//--------------------------------------------------
// 位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CObject3D::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// サイズの設定
//--------------------------------------------------
void CObject3D::SetSize(const D3DXVECTOR3& size)
{
	m_size = size;

	VERTEX_3D *pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float width = m_size.x * 0.5f;
	float height = m_size.y * 0.5f;

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(-width, +height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+width, +height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-width, -height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+width, -height, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// サイズの取得
//--------------------------------------------------
const D3DXVECTOR3& CObject3D::GetSize() const
{
	return m_size;
}

//--------------------------------------------------
// 向きの設定
//--------------------------------------------------
void CObject3D::SetRot(float rot)
{
	m_rot = rot;
}

//--------------------------------------------------
// 向きの取得
//--------------------------------------------------
const float CObject3D::GetRot() const
{
	return m_rot;
}

//--------------------------------------------------
// テクスチャの設定
//--------------------------------------------------
void CObject3D::SetTexture(CTexture::ELabel texture)
{
	m_texture = texture;
}

//--------------------------------------------------
// テクスチャ座標の設定
//--------------------------------------------------
void CObject3D::SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v)
{
	VERTEX_3D *pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(u.x, v.x);
	pVtx[1].tex = D3DXVECTOR2(u.y, v.x);
	pVtx[2].tex = D3DXVECTOR2(u.x, v.y);
	pVtx[3].tex = D3DXVECTOR2(u.y, v.y);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// 色の設定
//--------------------------------------------------
void CObject3D::SetCol(const D3DXCOLOR& col)
{
	m_col = col;

	VERTEX_3D *pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// 色の取得
//--------------------------------------------------
const D3DXCOLOR& CObject3D::GetCol() const
{
	return m_col;
}

//--------------------------------------------------
// 種類の設定
//--------------------------------------------------
void CObject3D::SetType(EType type)
{
	m_type = type;
}

//--------------------------------------------------
// 種類の取得
//--------------------------------------------------
const CObject3D::EType CObject3D::GetType() const
{
	return m_type;
}

//--------------------------------------------------
// 当たり判定をするかどうかの設定
//--------------------------------------------------
void CObject3D::SetCollision(bool collision)
{
	m_collision = collision;
}

//--------------------------------------------------
// 当たり判定をするかどうかの取得
//--------------------------------------------------
const bool CObject3D::GetCollision() const
{
	return m_collision;
}
