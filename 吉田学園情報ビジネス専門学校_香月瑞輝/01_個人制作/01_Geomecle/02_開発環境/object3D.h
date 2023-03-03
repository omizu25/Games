//**************************************************
// 
// object3D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT3D_H_	//このマクロ定義がされてなかったら
#define _OBJECT3D_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"
#include "texture.h"
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CObject3D : public CObject
{
	/* ↓定義↓ */
public:
	enum EType
	{
		TYPE_NONE = -1,
		TYPE_PLAYER = 0,	// プレイヤー
		TYPE_BULLET,		// 弾
		TYPE_ENEMY,			// 敵
		TYPE_BODY,			// 体
		TYPE_EXP,			// 経験値
		TYPE_CIRCLE,		// 円
		TYPE_MAX
	};

private:
	struct VERTEX_3D
	{// 頂点データ
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	};

	static const DWORD FVF_VERTEX_3D;	// 頂点フォーマット
	static const int NUM_VERTEX;		// 頂点の数
	static const int NUM_POLYGON;		// ポリゴンの数

	/* ↓静的メンバ関数↓ */
public:
	static CObject3D* Create();			// 生成
	static bool Exist(EType type);		// 存在するかどうか
	static void ReleaseAll(EType type);	// 指定のタイプの全ての解放

	/* ↓メンバ関数↓ */
public:
//	CObject3D() = delete;	// デフォルトコンストラクタ
	explicit CObject3D(CObject::ECategory cat = CObject::CATEGORY_3D);	// コンストラクタ
	~CObject3D() override;	// デストラクタ

public: 
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	void SetPos(const D3DXVECTOR3& pos);	// 位置の設定
	const D3DXVECTOR3& GetPos() const;		// 位置の取得
	void SetSize(const D3DXVECTOR3& size);	// サイズの設定
	const D3DXVECTOR3& GetSize() const;		// サイズの取得
	void SetRot(float rot);					// 向きの設定
	const float GetRot() const;				// 向きの取得
	void SetTexture(CTexture::ELabel texture);					// テクスチャの設定
	void SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v);	// テクスチャ座標の設定
	void SetCol(const D3DXCOLOR& col);	// 色の設定
	const D3DXCOLOR& GetCol() const;	// 色の取得
	void SetType(EType type);			// 種類の設定
	const EType GetType() const;		// 種類の取得
	void SetCollision(bool collision);	// 当たり判定をするかどうかの設定
	const bool GetCollision() const;	// 当たり判定をするかどうかの取得

	/* ↓メンバ変数↓ */
private:
	EType m_type;	// タイプ
	CTexture::ELabel m_texture;	// テクスチャの列挙型
	float m_rot;		// 向き
	D3DXVECTOR3 m_size;	// サイズ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXCOLOR m_col;	// 色
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	bool m_collision;	// 当たり判定をするかどうか
};

#endif // !_OBJECT3D_H_
