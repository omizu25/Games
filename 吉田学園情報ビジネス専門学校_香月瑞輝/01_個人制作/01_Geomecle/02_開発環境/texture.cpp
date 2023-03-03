//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "texture.h"
#include "application.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const char* CTexture::FILE_NAME[] =
{// テクスチャのパス
	"data/TEXTURE/Player.png",				// プレイヤー
	"data/TEXTURE/Bullet.png",				// 弾
	"data/TEXTURE/effect.jpg",				// エフェクト
	"data/TEXTURE/bg.png",					// 背景
	"data/TEXTURE/Cursor.png",				// カーソル
	"data/TEXTURE/TutorialNormal.png",		// 通常のチュートリアル
	"data/TEXTURE/TutorialSafetyArea.png",	// 安全エリアのチュートリアル
	"data/TEXTURE/TutorialDangerArea.png",	// 危険エリアのチュートリアル
	"data/TEXTURE/Circle.png",				// 円
	"data/TEXTURE/Bom.png",					// ボム

	/* ↓敵↓ */
	"data/TEXTURE/Homing.png",			// ホーミング
	"data/TEXTURE/HomingEscape.png",	// 逃げるホーミング
	"data/TEXTURE/HomingDivision.png",	// 分裂ホーミング
	"data/TEXTURE/PaperAirplane.png",	// 紙飛行機
	"data/TEXTURE/Windmill.png",		// 風車
	"data/TEXTURE/snake_body.png",		// 蛇の体

	/* ↓テキスト↓ */
	"data/TEXTURE/TEXT/Number.png",			// 数
	"data/TEXTURE/TEXT/result.png",			// リザルト
	"data/TEXTURE/TEXT/title.png",			// タイトル
	"data/TEXTURE/TEXT/mul.png",			// 掛ける
	"data/TEXTURE/TEXT/rank.png",			// 位
	"data/TEXTURE/TEXT/Ranking_Title.png",	// タイトル用のランキング
	"data/TEXTURE/TEXT/Ranking_Result.png",	// リザルト用のランキング
	"data/TEXTURE/TEXT/NewScore.png",		// 新しいスコア
	"data/TEXTURE/TEXT/Comma.png",			// カンマ
	"data/TEXTURE/TEXT/Period.png",			// ピリオド
	"data/TEXTURE/TEXT/Pause.png",			// ポーズ
	"data/TEXTURE/TEXT/Resume.png",			// 再開
	"data/TEXTURE/TEXT/Restart.png",		// リスタート
	"data/TEXTURE/TEXT/End.png",			// 終了
	"data/TEXTURE/TEXT/End_Ranking.png",	// ランキング用の終了
	"data/TEXTURE/TEXT/Retry.png",			// リトライ
	"data/TEXTURE/TEXT/Normal.png",			// 通常
	"data/TEXTURE/TEXT/SafetyArea.png",		// 安全エリア
	"data/TEXTURE/TEXT/DangerArea.png",		// 危険エリア
};

static_assert(sizeof(CTexture::FILE_NAME) / sizeof(CTexture::FILE_NAME[0]) == CTexture::LABEL_MAX, "aho");

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTexture::CTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CTexture::LoadAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// テクスチャの読み込みがされている
			continue;
		}

		// 読み込み
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CTexture::Load(ELabel label)
{
	assert(label >= 0 && label < LABEL_MAX);

	if (s_pTexture[label] != nullptr)
	{// テクスチャの読み込みがされている
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_NAME[label],
		&s_pTexture[label]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CTexture::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// テクスチャの解放
			s_pTexture[i]->Release();
			s_pTexture[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CTexture::Release(ELabel label)
{
	assert(label >= 0 && label < LABEL_MAX);

	if (s_pTexture[label] != nullptr)
	{// テクスチャの解放
		s_pTexture[label]->Release();
		s_pTexture[label] = nullptr;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::Get(ELabel label)
{
	if (label == LABEL_NONE)
	{// テクスチャを使用しない
		return nullptr;
	}

	assert(label >= 0 && label < LABEL_MAX);

	// 読み込み
	Load(label);

	return s_pTexture[label];
}
