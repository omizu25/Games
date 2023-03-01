//=============================================================================
//
// 入力処理 [inputjoypad.cpp]
// Author1 : HAMADA RYUUGA
// input.hを参照を推奨
//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "inputjoypad.h"

//*************************************************************************************
//コンストラクタ
//*************************************************************************************
CInputJoyPad::CInputJoyPad()
{
	m_pInput = nullptr;
	m_pDevJoypad = nullptr;
}

//*************************************************************************************
//デストラクタ
//*************************************************************************************
CInputJoyPad::~CInputJoyPad()
{
}

//*************************************************************************************
//初期化
//*************************************************************************************
HRESULT CInputJoyPad::Init()
{
	//XInputのステートを設定（有効にする）
	XInputEnable(true);

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		//メモリーのクリア
		memset(&m_JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));
	}
	return S_OK;
}

//*************************************************************************************
//終了処理
//*************************************************************************************
void CInputJoyPad::Uninit(void)
{
	//XInputのステートを設定（無効にする）
	XInputEnable(false);
}

//*************************************************************************************
//更新処理
//*************************************************************************************
void CInputJoyPad::Update(void)
{
	XINPUT_STATE JoyKeyState[PLAYER_MAX];		//ジョイパッド入力情報

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		//ジョイパッドの状態を取得
		if (XInputGetState(nCnt, &JoyKeyState[nCnt]) == ERROR_SUCCESS)
		{
			m_JoyKeyStateTrigger[nCnt].Gamepad.wButtons
				= ~m_JoyKeyState[nCnt].Gamepad.wButtons
				& JoyKeyState[nCnt].Gamepad.wButtons; //トリガー情報を保存
			m_JoyKeyState[nCnt] = JoyKeyState[nCnt];  //プレス処理
		}
	}
}

//プレス処理
bool CInputJoyPad::GetPress(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
//トリガー処理
bool CInputJoyPad::GetTrigger(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//スティックプレス処理
const D3DXVECTOR3& CInputJoyPad::GetStick(bool RightLeft, int nPlayer)
{
	if (RightLeft)
	{// 右
		m_JoyStickPos[nPlayer] = D3DXVECTOR3(m_JoyKeyState[nPlayer].Gamepad.sThumbRX / 32767.0f, -m_JoyKeyState[nPlayer].Gamepad.sThumbRY / 32767.0f, 0.0f);
	}
	else
	{// 左
		m_JoyStickPos[nPlayer] = D3DXVECTOR3(m_JoyKeyState[nPlayer].Gamepad.sThumbLX / 32767.0f, -m_JoyKeyState[nPlayer].Gamepad.sThumbLY / 32767.0f, 0.0f);
	}

	return m_JoyStickPos[nPlayer];
}

//トリガーペダル処理
int  CInputJoyPad::GetTriggerPedal(JOYKEY Key, int nPlayer)
{
	int nJoypadTriggerPedal = 0;
	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState[nPlayer].Gamepad.bLeftTrigger;
		break;
	case JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState[nPlayer].Gamepad.bRightTrigger;
		break;
	}

	return nJoypadTriggerPedal;
}

//ジョイパッドスティックプレス８方向
bool CInputJoyPad::GetStickPress(JOYKEY Key, bool RightLeft, int nPlayer)
{
	D3DXVECTOR3 pos = GetStick(RightLeft, nPlayer);	//現在の傾きの取得
	pos.y *= -1.0f;//Yを分かりやすくするために＋－を反転

	if (pos.y > 0.5f
		&& JOYKEY_UP == Key)
	{
		return true;
	}
	else if (pos.x > 0.5f
		&& JOYKEY_RIGHT == Key)
	{
		return true;
	}
	else if (pos.y < -0.5f
		&& JOYKEY_DOWN == Key)
	{
		return true;
	}
	else if (pos.x < -0.5f
		&& JOYKEY_LEFT == Key)
	{
		return true;
	}
	return false;
}

//ジョイパッドスティックトリガー８方向
bool CInputJoyPad::GetStickTrigger(JOYKEY Key, bool RightLeft, int nPlayer)
{
	if (GetStickPress(Key, RightLeft, nPlayer)
		&& Key != m_JoyStickOldPos[nPlayer][RightLeft])
	{
		m_JoyStickOldPos[nPlayer][RightLeft] = Key;
		return true;
	}
	else if (GetStickPress(Key, RightLeft, nPlayer)
		&& Key == m_JoyStickOldPos[nPlayer][RightLeft])
	{
		return false;
	}
	else if (!GetStickPress(Key, RightLeft, nPlayer)
		&& Key != m_JoyStickOldPos[nPlayer][RightLeft])
	{
		return false;
	}

	m_JoyStickOldPos[nPlayer][RightLeft] = JOYKEY_MAX;
	return false;
}
