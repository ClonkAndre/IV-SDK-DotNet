#pragma once

namespace IVSDKDotNet
{
	public ref class IVShadows
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