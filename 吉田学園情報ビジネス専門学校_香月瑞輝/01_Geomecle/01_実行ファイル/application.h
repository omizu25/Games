//**************************************************
// 
// application.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _APPLICATION_H_	//このマクロ定義がされてなかったら
#define _APPLICATION_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 前方宣言
//==================================================
class CRenderer;
class CInput;
class CSound;
class CMode;
class CTexture;
class CCamera;

//==================================================
// 定義
//==================================================
class CApplication
{
	/* ↓定義↓ */
public:
	static const int SCREEN_WIDTH = 1280;	// スクリーンの幅
	static const int SCREEN_HEIGHT = 720;	// スクリーンの高さ

private:
	static const bool FULL_SCREEN;	// フルスクリーンにするかどうか

	/* ↓静的メンバ関数↓ */
public:
	static CApplication* GetInstanse();	// インスタンスの取得

	/* ↓静的メンバ変数↓ */
private:
	static CApplication* m_pApplication;	// 自分のクラス

	/* ↓メンバ関数↓ */
private:
	CApplication();		// デフォルトコンストラクタ

public:
	~CApplication();	// デストラクタ

public:
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画
	LPDIRECT3DDEVICE9 GetDevice();	// デバイスの取得
	CSound* GetSound();				// サウンドの情報の取得
	CMode* GetMode();				// モードの情報の取得
	CTexture* GetTexture();			// テクスチャの情報の取得
	CCamera* GetCamera();			// カメラの情報の取得

	/* ↓メンバ変数↓ */
private:
	CRenderer* m_pRenderer;	// レンダラーの情報
	CInput* m_pInput;		// 入力の情報
	CSound* m_pSound;		// サウンドの情報
	CMode* m_pMode;			// モードの情報
	CTexture* m_pTexture;	// テクスチャの情報
	CCamera* m_pCamera;		// カメラの情報
};

#endif // !_APPLICATION_H_
