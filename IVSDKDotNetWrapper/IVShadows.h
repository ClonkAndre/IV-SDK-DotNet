#pragma once

namespace IVSDKDotNet
{
	public ref class IVShadows
	{
	public:

		/// <summary>
		/// Adds a light to the scene!
		/// </summary>
		/// <param name="a1">Unknown.</param>
		/// <param name="nLightType">The type of the light.</param>
		/// <param name="nFlags">The light flags.</param>
		/// <param name="vDir">The light direction.</param>
		/// <param name="vTanDir">The light tangent direction.</param>
		/// <param name="vPos">The light position.</param>
		/// <param name="vColor">The light color.</param>
		/// <param name="fIntensity">The light intensity.</param>
		/// <param name="txdSlot">The slot the texture is in.</param>
		/// <param name="texHash">The texture hash within the given slot.</param>
		/// <param name="fRange">The light range.</param>
		/// <param name="fInnerConeAngle">The volume inner cone angle.</param>
		/// <param name="fOuterConeAngle">The volume outer cone angle.</param>
		/// <param name="fVolIntensity">The volume intensity (brightness).</param>
		/// <param name="fVolSizeScale">The volume radius scale (1.0f means the same radius as the light).</param>
		/// <param name="interiorId">If you want the light to work in an interior, this needs to be set to the current interior the char is in. Use the GET_INTERIOR_FROM_CHAR native to get the interior.</param>
		/// <param name="a15">Unknown.</param>
		/// <param name="nID">Used by shadow system to track scene lights - 0 if no shadows and tracking.</param>
		static void AddSceneLight(uint32_t a1, uint32_t nLightType, uint32_t nFlags, Vector3 vDir, Vector3 vTanDir, Vector3 vPos, Color vColor, float fIntensity, int32_t txdSlot, int32_t texHash, float fRange, float fInnerConeAngle, float fOuterConeAngle, float fVolIntensity, float fVolSizeScale, int32_t interiorId, uint32_t a15, uint32_t nID);

		/// <summary>
		/// StoreStaticShadows method with basic parameters. This internally calls the AddSceneLight function.
		/// </summary>
		/// <param name="castShadows">Should light cast shadows?</param>
		/// <param name="vPos">The position of the light.</param>
		/// <param name="vColor">The color of the light.</param>
		/// <param name="fIntensity">Light Intensity.</param>
		/// <param name="fRange">Light Range.</param>
		static void StoreStaticShadow(bool castShadows, Vector3 vPos, Color vColor, float fIntensity, float fRange);

	};
}