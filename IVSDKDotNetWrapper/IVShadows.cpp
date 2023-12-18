#include "pch.h"
#include "IVShadows.h"

namespace IVSDKDotNet
{
	// - - - Methods / Functions - - -
	void IVShadows::StoreStaticShadowAdvanced(uint32_t a1, uint32_t a2, bool castShadows, Vector3 pVec1, Vector3 pVec2, Vector3 vPos, Color vColor, float fIntensity, uint32_t texHash, uint32_t txdSlot, float fRange, float a12, float a13, uint32_t a14, uint32_t a15, uint32_t nID)
	{
		CVector v1;
		v1.x = 0.0F;
		v1.y = 0.0F;
		v1.z = -1.0F;

		CVector v2;
		v2.x = 0.0F;
		v2.y = 1.0F;
		v2.z = 0.0F;

		CVector v3Pos;
		v3Pos.x = vPos.X;
		v3Pos.y = vPos.Y;
		v3Pos.z = vPos.Z;

		CVector v4Color;
		v4Color.x = vColor.R;
		v4Color.y = vColor.G;
		v4Color.z = vColor.B;

		CShadows::StoreStaticShadow(a1, a2, castShadows ? 0x504 : 0x500, &v1, &v2, &v3Pos, &v4Color, fIntensity, texHash, txdSlot, fRange, a12, a13, a14, a15, nID);
	}
	void IVShadows::StoreStaticShadow(bool castShadows, Vector3 vPos, Color vColor, float fIntensity, float fRange)
	{
		CVector v1;
		v1.x = 0.0F;
		v1.y = 0.0F;
		v1.z = -1.0F;

		CVector v2;
		v2.x = 0.0F;
		v2.y = 1.0F;
		v2.z = 0.0F;

		CVector v3Pos;
		v3Pos.x = vPos.X;
		v3Pos.y = vPos.Y;
		v3Pos.z = vPos.Z;

		CVector v4Color;
		v4Color.x = vColor.R;
		v4Color.y = vColor.G;
		v4Color.z = vColor.B;

		CShadows::StoreStaticShadow(0, 0, castShadows ? 0x504 : 0x500, &v1, &v2, &v3Pos, &v4Color, fIntensity, 0, 0, fRange, 0.3F, 3.0F, -1, 0, (uint32_t)FindPlayerPed() + 1);
	}
}