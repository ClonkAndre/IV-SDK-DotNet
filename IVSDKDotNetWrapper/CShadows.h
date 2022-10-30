#pragma once

class Native_CShadows
{
public:
	// zmenu chaos "It's bright in here":
	/*
		Vector3 v1 = {0,0,-1};
		Vector3 v2 = {0,1,0};
		CShadows::StoreStaticShadow(0, 0, 0x500, &v1, &v2, &pos, &color, 50, 0, 0, 5, 0.3, 3.0, -1, 0, (uint32_t)FindPlayerPed() + 1);
	*/
	// zmenu light spawning:
	// CShadows::StoreStaticShadow(0, 0, LightSources[i].castShadows ? 0x504 : 0x500, (int)&v1, (int)&v2, (int)&LightSources[i].position, (int)&LightSources[i].color, LightSources[i].intensity, 0, 0, LightSources[i].range, 0.3, 3.0, -1, 0, (uint32_t)FindPlayerPed() + 1);
	static void StoreStaticShadow(uint32_t a1, uint32_t a2, uint32_t nFlags, Native_CVector* pVec1, Native_CVector* pVec2, Native_CVector* vPos, Native_CVector* vColor, float fIntensity, uint32_t texHash, uint32_t txdSlot, float fRange, float a12, float a13, uint32_t a14, uint32_t a15, uint32_t nID)
	{
		return ((void(__cdecl*)(uint32_t, uint32_t, uint32_t, Native_CVector*, Native_CVector*, Native_CVector*, Native_CVector*, float, uint32_t, uint32_t, float, float, float, uint32_t, uint32_t, uint32_t))(AddressSetter::Get(0x4C60E0, 0x62E5F0)))(a1, a2, nFlags, pVec1, pVec2, vPos, vColor, fIntensity, texHash, txdSlot, fRange, a12, a13, a14, a15, nID);
	}
};

namespace IVSDKDotNet {

	public ref class CShadows
	{
	public:

		/// <summary>
		/// StoreStaticShadows method with extended parameters.
		/// </summary>
		/// <param name="a1">Unknown.</param>
		/// <param name="a2">Unknown.</param>
		/// <param name="castShadows">Should light cast shadows?</param>
		/// <param name="pVec1">Unknown.</param>
		/// <param name="pVec2">Unknown.</param>
		/// <param name="vPos">Light Position.</param>
		/// <param name="vColor">Light Color.</param>
		/// <param name="fIntensity">Light Intensity.</param>
		/// <param name="texHash">Unknown.</param>
		/// <param name="txdSlot">Unknown.</param>
		/// <param name="fRange">Light Range.</param>
		/// <param name="a12">Unknown.</param>
		/// <param name="a13">Unknown.</param>
		/// <param name="a14">Unknown.</param>
		/// <param name="a15">Unknown.</param>
		/// <param name="nID">Light ID.</param>
		static void StoreStaticShadowAdvanced(uint32_t a1, uint32_t a2, bool castShadows, Vector3 pVec1, Vector3 pVec2, Vector3 vPos, Color vColor, float fIntensity, uint32_t texHash, uint32_t txdSlot, float fRange, float a12, float a13, uint32_t a14, uint32_t a15, uint32_t nID);

		/// <summary>
		/// StoreStaticShadows method with basic parameters.
		/// </summary>
		/// <param name="castShadows">Should light cast shadows?</param>
		/// <param name="vPos">The position of the light.</param>
		/// <param name="vColor">The color of the light.</param>
		/// <param name="fIntensity">Light Intensity.</param>
		/// <param name="fRange">Light Range.</param>
		static void StoreStaticShadow(bool castShadows, Vector3 vPos, Color vColor, float fIntensity, float fRange);

	};

}

