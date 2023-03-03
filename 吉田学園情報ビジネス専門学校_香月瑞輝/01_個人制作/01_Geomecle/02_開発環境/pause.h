//**************************************************
// 
// pause.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PAUSE_H_	//このマクロ定義がされてなかったら
#define _PAUSE_H_	//２重インクルード防止のマクロ定義

//==================================================
// 前方宣言
//==================================================
class CObject2D;
class CMenu;

//==================================================
// 定義
//==================================================
class CPause
{
	/* ↓定義↓ */
private:
	enum ESelect
	{
		SELECT_NONE = -1,	// 使用しない
		SELECT_RESUME = 0,	// 再開
		SELECT_RESTART,		// 始めから
		SELECT_END,			// 終了
		SELECT_MAX
	};

	/* ↓静的メンバ関数↓ */
public:
	static CPause* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CPause();	// デフォルトコンストラクタ
	~CPause();	// デストラクタ

public:
	void Init();	// 初期化
	void Uninit();	// 終了
	void Release();	// 解放
	bool Update();	// 更新

private:
	CObject2D* m_pPause;	// ポーズ
	CMenu* m_pMenu;			// メニュー
};

#endif // !_PAUSE_H_
