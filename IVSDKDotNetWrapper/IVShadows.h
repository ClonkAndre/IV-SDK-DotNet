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
		/// <param name="nID">Used by shadow system to track scene lights - 0 if no shadows and tracking.</param>
		static void StoreStaticShadow(bool castShadows, Vector3 vPos, Color vColor, float fIntensity, float fRange, uint32_t nID);

		/// <summary>
		/// StoreStaticShadows method with basic parameters. This internally calls the AddSceneLight function.
		/// </summary>
		/// <param name="castShadows">Should light cast shadows?</param>
		/// <param name="vPos">The position of the light.</param>
		/// <param name="vColor">The color of the light.</param>
		/// <param name="fIntensity">Light Intensity.</param>
		/// <param name="fRange">Light Range.</param>
		static void StoreStaticShadow(bool castShadows, Vector3 vPos, Color vColor, float fIntensity, float fRange);

		/// <summary>
		/// Renders a corona. This function will probably be moved somewhere else in the future!
		/// </summary>
		/// <param name="id">The id of the corona.</param>
		/// <param name="color">The color of the corona.</param>
		/// <param name="a5">Unk.</param>
		/// <param name="pos">The position of where to place the corona.</param>
		/// <param name="range">The size of the corona.</param>
		/// <param name="a8">Unk.</param>
		/// <param name="a9">Unk.</param>
		/// <param name="a10">Unk.</param>
		/// <param name="a11">Unk.</param>
		/// <param name="a12">Unk.</param>
		/// <param name="a13">Unk.</param>
		/// <param name="a14">Unk.</param>
		static void RenderCorona(int id, Color color, float a5, Vector3 pos, float range, float a8, float a9, int a10, float a11, char a12, char a13, int a14)
		{
			CVector m_vPos;
			m_vPos.x = pos.X;
			m_vPos.y = pos.Y;
			m_vPos.z = pos.Z;

			CShadows::RenderCorona(id, color.R, color.G, color.B, a5, &m_vPos, range, a8, a9, a10, a11, a12, a13, a14);
		}

	};
}