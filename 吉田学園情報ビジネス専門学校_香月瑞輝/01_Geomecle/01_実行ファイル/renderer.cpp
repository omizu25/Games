//**************************************************
// 
// renderer.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "renderer.h"
#include "main.h"
#include "application.h"
#include "object.h"
#include "effect.h"
#include "mode.h"
#include <assert.h>
#include <tchar.h> // _T

//==================================================
// ライブラリーリンク
//==================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CRenderer::CRenderer() : 
#ifdef _DEBUG
	m_pFont(nullptr),
#endif // _DEBUG
	m_pD3D(nullptr),
	m_pD3DDevice(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CRenderer::~CRenderer()
{
	assert(m_pD3D == nullptr);
	assert(m_pD3DDevice == nullptr);
	assert(m_pFont == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		// 生成失敗
		return E_FAIL;
	}

	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{// 現在のディスプレイモードを取得
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.BackBufferWidth = CApplication::SCREEN_WIDTH;			// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = CApplication::SCREEN_HEIGHT;		// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;									// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画と頂点処理をCPUで行なう
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{// 生成失敗
		return E_FAIL;
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// 画像を小さくしても綺麗にする
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 画像を大きくしても綺麗にする
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャのUの繰り返し方を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャのVの繰り返し方を設定

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// ポリゴンとテクスチャのαをまぜる
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// １つ目の色はテクスチャの色
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２つ目の色は現在の色

	// ライトを無効にする
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

#ifdef _DEBUG
	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif // _DEBUG

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CRenderer::Uninit()
{
#ifdef _DEBUG
	if (m_pFont != nullptr)
	{// デバッグ情報表示用フォントの破棄
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG

	if (m_pD3DDevice != nullptr)
	{// デバイスの破棄
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	if (m_pD3D != nullptr)
	{// Direct3Dオブジェクトの破棄
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CRenderer::Update()
{
	// モードの更新
	CApplication::GetInstanse()->GetMode()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CRenderer::Draw()
{
	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{// Direct3Dによる描画の開始

		// モードの描画
		CApplication::GetInstanse()->GetMode()->Draw();

#ifdef _DEBUG
		// FPS表示
		DrawFPS();
#endif // _DEBUG

		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//--------------------------------------------------
// デバイスの取得
//--------------------------------------------------
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
};

#ifdef _DEBUG
//--------------------------------------------------
// FPS表示
//--------------------------------------------------
void CRenderer::DrawFPS()
{
	RECT rect = { 0, 0, CApplication::SCREEN_WIDTH, CApplication::SCREEN_HEIGHT };
	TCHAR str[256];
	int length = 0;

	wsprintf(&str[length], _T("FPS : %d\n"), GetFPS());
	length = (int)strlen(str);

	wsprintf(&str[length], _T("オブジェクトの総数 : %d\n"), CObject::GetNumAll() - CEffect::GetNumAll());
	length = (int)strlen(str);

	wsprintf(&str[length], _T("エフェクトの総数 : %d\n"), CEffect::GetNumAll());
	length = (int)strlen(str);

	// テキスト描画
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0x00));
}
#endif // _DEBUG
