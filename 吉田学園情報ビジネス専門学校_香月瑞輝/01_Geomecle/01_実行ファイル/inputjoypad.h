//=============================================================================
//
// 入力処理 [directjoypad.h]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _INPUTJOYPAD_H_		//このマクロ定義がされなかったら
#define _INPUTJOYPAD_H_		//2重インクルード防止のマクロ定義

//----------------------------------------------------------------------------
//ライブラリーファイルのリンク
//----------------------------------------------------------------------------
#pragma comment(lib,"dinput8.lib")//入力処理に必要(キーボード)
#pragma comment(lib,"xinput.lib")//入力処理に必要（ジョイパット）
#pragma comment(lib,"dxguid.lib")//DirectXコンポーネントに使用

//----------------------------------------------------------------------------
//インクルードファイル
//----------------------------------------------------------------------------
#include <Windows.h>
#include <d3dx9.h>
#define	 DIRECTINPUT_VERSION (0x0800)	//ビルド時の警告対策用マクロ(この位置から動かさない)
#include <Xinput.h>						//ジョイパット処理
#include <dinput.h>						//入力処理に必要

//----------------------------------------------------------------------------
//クラス定義
//----------------------------------------------------------------------------
class CInputJoyPad
{
private:
	static const int NUM_KEY_MAX = 256;	//キーの最大数（キーボード）
	static const int PLAYER_MAX = 4;		//プレイヤーの最大人数
	static const int STICK_MAX = 2;
public:

	//キー種類(ジョイパッド)
	enum JOYKEY
	{
		JOYKEY_UP = 0,				//上
		JOYKEY_DOWN,				//下
		JOYKEY_LEFT,				//左
		JOYKEY_RIGHT,				//右
		JOYKEY_START,				//スタートボタン
		JOYKEY_BACK,				//バックボタン
		JOYKEY_LEFT_THUMB,			//左スティック押込み
		JOYKEY_RIGHT_THUMB,			//右スティック押込み
		JOYKEY_LEFT_SHOULDER,		//L１ボタン
		JOYKEY_RIGHT_SHOULDER,		//R１ボタン
		JOYKEY_LEFT_TRIGGER,		//L２トリガー
		JOYKEY_RIGHT_TRIGGER,		//R２トリガー
		JOYKEY_A,					//Aボタン
		JOYKEY_B,					//Bボタン
		JOYKEY_X,					//Xボタン
		JOYKEY_Y,					//Yボタン
		JOYKEY_MAX,
	};

	CInputJoyPad();
	~CInputJoyPad();
	HRESULT Init();		//初期化
	void Uninit();		//終了処理
	void Update();		//更新処理

	bool GetPress(JOYKEY Key, int nPlayer);					//プレス処理
	bool GetTrigger(JOYKEY Key, int nPlayer);				//トリガー処理
	const D3DXVECTOR3& GetStick(bool RightLeft, int nPlayer);	//スティック処理
	int GetTriggerPedal(JOYKEY Key, int nPlayer);			//トリガーペダル処理
	bool GetStickPress(JOYKEY Key, bool RightLeft, int nPlayer);
	bool GetStickTrigger(JOYKEY Key, bool RightLeft, int nPlayer);
private:

	LPDIRECTINPUT8 m_pInput;							//DirectInputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevJoypad;				//入力デバイス（キーボード（コントローラー用は別に作る））へのポインタ
										//ジョイパッド
	XINPUT_STATE m_JoyKeyState[PLAYER_MAX];				//ジョイパットのプレス情報
	XINPUT_STATE m_JoyKeyStateTrigger[PLAYER_MAX];		//ジョイパットのトリガー情報
	D3DXVECTOR3 m_JoyStickPos[PLAYER_MAX];				//ジョイスティックの傾き
	JOYKEY m_JoyStickOldPos[PLAYER_MAX][STICK_MAX];		//ジョイスティックの前回の傾き
};
#endif