#include "pch.h"
#include "IVShadows.h"

namespace IVSDKDotNet
{

	// - - - Methods / Functions - - -
	void IVShadows::AddSceneLight(uint32_t a1, uint32_t nLightType, uint32_t nFlags, Vector3 vDir, Vector3 vTanDir, Vector3 vPos, Color vColor, float fIntensity, int32_t txdSlot, int32_t texHash, float fRange, float fInnerConeAngle, float fOuterConeAngle, float fVolIntensity, float fVolSizeScale, int32_t interiorId, uint32_t a15, uint32_t nID)
	{
		CVector m_vDir;
		m_vDir.x = vDir.X;
		m_vDir.y = vDir.Y;
		m_vDir.z = vDir.Z;

		CVector m_vTanDir;
		m_vTanDir.x = vTanDir.X;
		m_vTanDir.y = vTanDir.Y;
		m_vTanDir.z = vTanDir.Z;

		CVector m_vPos;
		m_vPos.x = vPos.X;
		m_vPos.y = vPos.Y;
		m_vPos.z = vPos.Z;

		CVector m_vColor;
		m_vColor.x = vColor.R / 256.0F;
		m_vColor.y = vColor.G / 256.0F;
		m_vColor.z = vColor.B / 256.0F;

		CShadows::AddSceneLight(
			a1,							// a1
			nLightType,					// a2
			*(uint32_t*)&nFlags,		// a3
			&m_vDir,					// a4
			&m_vTanDir,					// a5
			&m_vPos,					// a6
			&m_vColor,					// a7
			*(float*)&fIntensity,		// a8
			texHash,					// a9
			txdSlot,					// a10
			*(float*)&fRange,			// a11
			*(float*)&fInnerConeAngle,	// a12
			*(float*)&fOuterConeAngle,	// a13
			*(float*)&fVolIntensity,	// a14
			fVolSizeScale,				// a15
			interiorId,					// a16
			a15,						// a17
			nID);						// a18
	}

	void IVShadows::StoreStaticShadow(bool castShadows, Vector3 vPos, Color vColor, float fIntensity, float fRange, uint32_t nID)
	{
		AddSceneLight(0, 0, castShadows ? 0x504 : 0x500, -Vector3::UnitZ, Vector3::UnitY, vPos, vColor, fIntensity, 0, 0, fRange, 0.0F, 0.0F, 0.0F, 0.0F, 0, 0, nID);
	}
	void IVShadows::StoreStaticShadow(bool castShadows, Vector3 vPos, Color vColor, float fIntensity, float fRange)
	{
		AddSceneLight(0, 0, castShadows ? 0x504 : 0x500, -Vector3::UnitZ, Vector3::UnitY, vPos, vColor, fIntensity, 0, 0, fRange, 0.0F, 0.0F, 0.0F, 0.0F, 0, 0, castShadows ? (uint32_t)FindPlayerPed() + 1 : 0);
	}

}