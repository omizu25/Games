//**************************************************
// 
// object2D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT2D_H_	//このマクロ定義がされてなかったら
#define _OBJECT2D_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"
#include "texture.h"
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CObject2D : public CObject
{
	/* ↓定義↓ */
private:
	struct VERTEX_2D
	{// 頂点データ
		D3DXVECTOR3 pos;
		float rhw;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	};

	static const DWORD FVF_VERTEX_2D;	// 頂点フォーマット
	static const int NUM_VERTEX;		// 頂点の数
	static const int NUM_POLYGON;		// ポリゴンの数

	/* ↓静的メンバ関数↓ */
public:
	static CObject2D* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CObject2D();			// デフォルトコンストラクタ
	~CObject2D() override;	// デストラクタ

public: 
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	void SetPos(const D3DXVECTOR3& pos);		// 位置の設定
	const D3DXVECTOR3& GetPos() const;			// 位置の取得
	void SetSize(const D3DXVECTOR3& size);		// サイズの設定
	const D3DXVECTOR3& GetSize() const;			// サイズの取得
	void SetRot(float rot);						// 向きの設定
	const float GetRot() const;					// 向きの取得
	void SetCol(const D3DXCOLOR& col);			// 色の設定
	void SetDraw(bool draw);					// 描画するかどうかの設定
	bool GetDraw();								// 描画するかどうかの取得
	void SetTexture(CTexture::ELabel texture);	// テクスチャの設定
	void SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v);	// テクスチャ座標の設定
	void SetFade(float alpha);	// フェードの設定

private:
	void SetVtxPos();	// 頂点情報の設定

	/* ↓メンバ変数↓ */
private:
	CTexture::ELabel m_texture;	// テクスチャの列挙型
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	D3DXVECTOR3 m_size;	// サイズ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXCOLOR m_col;	// 色
	float m_alpha;		// アルファ
	float m_rot;		// 向き
	bool m_fade;		// フェード
	bool m_inOut;		// フェードがイン・アウト
	bool m_draw;		// 描画するかどうか
};

#endif // !_OBJECT2D_H_
