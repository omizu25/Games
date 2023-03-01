//**************************************************
// 
// menu.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MENU_H_	//このマクロ定義がされてなかったら
#define _MENU_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "texture.h"

//==================================================
// 前方宣言
//==================================================
class CObject2D;

//==================================================
// 定義
//==================================================
class CMenu
{
	/* ↓定義↓ */
private:
	static const int MAX_OPTION = 5;	// 選択肢の最大数
	static const float CURSOR_INTERVAL;	// カーソルの間隔

	/* ↓静的メンバ関数↓ */
public:
	//--------------------------------------------------
	// 生成
	// pos / 位置
	// size / サイズ
	// numUse / 選択肢の使用数
	// interval / 間隔
	// sort / 並べ方 [ true : 縦 false : 横 ]
	// cursor / カーソルを使うかどうか
	//--------------------------------------------------
	static CMenu* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int numUse, float interval, bool sort, bool cursor);

	/* ↓メンバ関数↓ */
public:
	CMenu();	// デフォルトコンストラクタ
	~CMenu();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int numUse, float interval, bool sort, bool cursor);	// 初期化
	void Uninit();	// 終了
	void Release();	// 解放
	void Update();	// 更新
	int Select();	// 選択
	void SetFrame(const D3DXVECTOR3& size, const D3DXCOLOR& col);	// 枠の設定
	void SetTexture(int idx, CTexture::ELabel label);	// テクスチャの設定
	int GetSelectIdx();	// 選択されている番号の取得

private:
	void Add(int add);

	/* ↓メンバ変数↓ */
private:
	CObject2D* m_pOption[MAX_OPTION];	// 選択肢
	CObject2D* m_pFrame;	// 枠
	CObject2D* m_pCursor;	// カーソル
	int m_selectIdx;		// 選択されている番号
	int m_numUse;			// 使用数
	int m_time;				// タイム
	bool m_sort;			// 並べ方 [ true : 縦 false : 横 ]
};

#endif // !_MENU_H_
