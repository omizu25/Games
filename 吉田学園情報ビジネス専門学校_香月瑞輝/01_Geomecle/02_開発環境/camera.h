//**************************************************
// 
// camera.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CAMERA_H_	// このマクロ定義がされてなかったら
#define _CAMERA_H_	// ２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CCamera
{
	/* ↓定義↓ */
private:
	static const float MAX_NEAR;		// ニアの最大値
	static const float MAX_FAR;			// ファーの最大値
	static const float MAX_DISTANCE;	// 視点の距離の最大値

	/* ↓メンバ関数↓ */
public:
	CCamera();	// デフォルトコンストラクタ
	~CCamera();	// デストラクタ

public:
	void Init();	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Set();		// 設定
	void SetPos(const D3DXVECTOR3& pos);	// 位置の設定
	const D3DXVECTOR3& GetPos() const;		// 位置の取得
	const D3DXMATRIX& GetProj() const;		// プロジェクションの取得
	const D3DXMATRIX& GetView() const;		// ビューの取得

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_pos;		// 現在の視点
	D3DXVECTOR3 m_posDest;	// 目的の視点
	D3DXVECTOR3 m_vecU;		// 上方向ベクトル
	D3DXVECTOR3 m_rot;		// 現在の向き
	D3DXVECTOR3 m_rotDest;	// 目的の向き
	D3DXMATRIX m_mtxProj;	// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;	// ビューマトリックス
};

#endif // !_CAMERA_H_
