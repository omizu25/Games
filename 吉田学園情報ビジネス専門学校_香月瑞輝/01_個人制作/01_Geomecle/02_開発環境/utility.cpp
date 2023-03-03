//**************************************************
// 
// utility.cpp
// Author  : katsuki mizuki
// Author YudaKaito
// 
//**************************************************

//==================================================
// ƒCƒ“ƒNƒ‹[ƒh
//==================================================
#include "utility.h"

//--------------------------------------------------
// Šp“x‚Ì³‹K‰»
//--------------------------------------------------
void NormalizeAngle(float *pAngle)
{
	if (*pAngle >= D3DX_PI)
	{// 3.14‚æ‚è‘å‚«‚¢
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{// -3.14‚æ‚è¬‚³‚¢
		*pAngle += D3DX_PI * 2.0f;
	}
}

//--------------------------------------------------
// ƒz[ƒ~ƒ“ƒO
//--------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed)
{
	D3DXVECTOR3 vecDiff = posDest - posNow;

	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength <= fSpeed)
	{// ‘¬‚³‚æ‚è’·‚³‚ª¬‚³‚¢
		*pPosOut = posDest;
		return true;
	}
	else
	{// ‘¬‚³‚æ‚è’·‚³‚ª‘å‚«‚¢
		*pPosOut = posNow + ((vecDiff / fLength) * fSpeed);
		return false;
	}
}

//--------------------------------------------------
// ¬”“_‚Ìƒ‰ƒ“ƒ_ƒ€
//--------------------------------------------------
float FloatRandom(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}

//--------------------------------------------------
// ®”‚Ìƒ‰ƒ“ƒ_ƒ€
//--------------------------------------------------
int IntRandom(int nMax, int nMin)
{
	return (int)((rand() / (float)RAND_MAX) * (nMax - nMin)) + nMin;
}

//--------------------------------------------------
// sinƒJ[ƒu‚Ì’l‚ª1.0f`0.0f‚Å‹A‚Á‚Ä‚­‚é
//--------------------------------------------------
float SinCurve(int nTime, float fCycle)
{
	return  (sinf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// cosƒJ[ƒu‚Ì’l‚ª1.0f`0.0f‚Å‹A‚Á‚Ä‚­‚é
//--------------------------------------------------
float CosCurve(int nTime, float fCycle)
{
	return  (cosf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// ƒJ[ƒu‚Ì’l‚ª‹A‚Á‚Ä‚­‚é
//--------------------------------------------------
float Curve(float fCurve, float fMax, float fMin)
{
	return (fCurve * (fMax - fMin)) + fMin;
}

//--------------------------------------------------
// ”ÍˆÍ“à
//--------------------------------------------------
bool InRange(D3DXVECTOR3* pPos, const D3DXVECTOR3& range)
{
	bool out = false;

	if (pPos->x >= range.x)
	{// ‰E‚Ì•Ç
		pPos->x = range.x;
		out = true;
	}
	else if (pPos->x <= -range.x)
	{// ¶‚Ì•Ç
		pPos->x = -range.x;
		out = true;
	}

	if (pPos->y >= range.y)
	{// ã‚Ì•Ç
		pPos->y = range.y;
		out = true;
	}
	else if (pPos->y <= -range.y)
	{// ‰º‚Ì•Ç
		pPos->y = -range.y;
		out = true;
	}

	return out;
}

//--------------------------------------------------
// ”ÍˆÍ“à‚Å”½Ë
//--------------------------------------------------
bool InRangeReflect(D3DXVECTOR3* pPos, D3DXVECTOR3* pMove, const D3DXVECTOR3& range)
{
	bool out = false;

	if (pPos->x >= range.x)
	{// ‰E‚Ì•Ç
		pPos->x = range.x;
		pMove->x *= -1.0f;
		out = true;
	}
	else if (pPos->x <= -range.x)
	{// ¶‚Ì•Ç
		pPos->x = -range.x;
		pMove->x *= -1.0f;
		out = true;
	}

	if (pPos->y >= range.y)
	{// ã‚Ì•Ç
		pPos->y = range.y;
		pMove->y *= -1.0f;
		out = true;
	}
	else if (pPos->y <= -range.y)
	{// ‰º‚Ì•Ç
		pPos->y = -range.y;
		pMove->y *= -1.0f;
		out = true;
	}

	return out;
}

//--------------------------------------------------
// ‰~‚Ì“–‚½‚è”»’è
//--------------------------------------------------
bool CollisionCircle(const D3DXVECTOR3& pos1, float radius1, const D3DXVECTOR3& pos2, float radius2)
{
	// ‚Q‚Â‚Ì•¨‘Ì‚Ì”¼Œa“¯m‚Ì˜a
	float radius = radius1 + radius2;

	// X‚Ì·•ª
	float diffX = pos1.x - pos2.x;

	// Y‚Ì·•ª
	float diffY = pos1.y - pos2.y;

	// Œ»İ‚Ì‚Q“_‚Ì‹——£
	float length = sqrtf((diffX * diffX) + (diffY * diffY));

	if (radius >= length)
	{// ‚Q‚Â‚Ì•¨‘Ì‚Ì”¼Œa“¯m‚Ì˜a‚æ‚èŒ»İ‚Ì‚Q“_‚Ì‹——£‚ª¬‚³‚¢‚©‚Ç‚¤‚©
		// “–‚½‚Á‚½
		return true;
	}

	// “–‚½‚Á‚Ä‚È‚¢
	return false;
}

//--------------------------------------------------
// ƒGƒŠƒA‚Ì“–‚½‚è”»’è
//--------------------------------------------------
bool CollisionArea(const D3DXVECTOR3& pos1, float radius1, D3DXVECTOR3* pPos2, float radius2)
{
	// ‚Q‚Â‚Ì•¨‘Ì‚Ì”¼Œa“¯m‚Ì˜a
	float radius = radius1 + radius2;

	// X‚Ì·•ª
	float diffX = pos1.x - pPos2->x;

	// Y‚Ì·•ª
	float diffY = pos1.y - pPos2->y;

	// Œ»İ‚Ì‚Q“_‚Ì‹——£
	float length = sqrtf((diffX * diffX) + (diffY * diffY));

	if (radius >= length)
	{// ‚Q‚Â‚Ì•¨‘Ì‚Ì”¼Œa“¯m‚Ì˜a‚æ‚èŒ»İ‚Ì‚Q“_‚Ì‹——£‚ª¬‚³‚¢‚©‚Ç‚¤‚©
		float rot = atan2f(diffX, diffY);
		pPos2->x = pos1.x - (sinf(rot) * radius);
		pPos2->y = pos1.y - (cosf(rot) * radius);

		// “–‚½‚Á‚½
		return true;
	}

	// “–‚½‚Á‚Ä‚È‚¢
	return false;
}

//--------------------------------------------------
// ƒoƒbƒtƒ@‚ÌƒRƒs[
//--------------------------------------------------
void CopyBuf(IDirect3DVertexBuffer9* pBuf, void* pSrc, unsigned size)
{
	void *p = 0;
	pBuf->Lock(0, 0, &p, 0);
	memcpy(p, pSrc, size);
	pBuf->Unlock();
}

//--------------------------------------------------
// Œ…”
//--------------------------------------------------
int Digit(int number)
{
	if (number == 0)
	{
		return 1;
	}

	return (int)log10f((float)number) + 1;
}
