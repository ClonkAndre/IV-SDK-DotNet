#include "pch.h"
#include "CShadows.h"

namespace IVSDKDotNet {

	void CShadows::StoreStaticShadowAdvanced(uint32_t a1, uint32_t a2, bool castShadows, CVector^ pVec1, CVector^ pVec2, CVector^ vPos, CVector^ vColor, float fIntensity, uint32_t texHash, uint32_t txdSlot, float fRange, float a12, float a13, uint32_t a14, uint32_t a15, uint32_t nID)
	{
		Native_CVector v1 = { 0, 0, -1 };
		Native_CVector v2 = { 0, 1, 0 };
		Native_CVector v3Pos = { vPos->X, vPos->Y, vPos->Z };
		Native_CVector v4Color = { vColor->X, vColor->Y, vColor->Z };
		Native_CShadows::StoreStaticShadow(a1, a2, castShadows ? 0x504 : 0x500, &v1, &v2, &v3Pos, &v4Color, fIntensity, texHash, txdSlot, fRange, a12, a13, a14, a15, nID);
	}

	void CShadows::StoreStaticShadow(bool castShadows, CVector^ vPos, CVector^ vColor, float fIntensity, float fRange)
	{
		Native_CVector v1 = { 0, 0, -1 };
		Native_CVector v2 = { 0, 1, 0 };
		Native_CVector v3Pos = { vPos->X, vPos->Y, vPos->Z };
		Native_CVector v4Color = { vColor->X, vColor->Y, vColor->Z };
		Native_CShadows::StoreStaticShadow(0, 0, castShadows ? 0x504 : 0x500, &v1, &v2, &v3Pos, &v4Color, fIntensity, 0, 0, fRange, 0.3F, 3.0F, -1, 0, (uint32_t)Native_CPlayerInfo::FindPlayerPed() + 1);
	}

}