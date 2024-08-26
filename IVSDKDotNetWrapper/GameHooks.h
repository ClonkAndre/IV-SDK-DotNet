#pragma once

// For any game related hooking stuff

namespace IVSDKDotNet
{
	namespace Hooking
	{

		generic <typename T>
		public value struct HookCallback
		{
		public:
			property bool InterceptCall
			{
				bool get()
				{
					return m_bInterceptCall;
				}
			}
			property T CustomReturnValue
			{
				T get()
				{
					return m_customReturnValue;
				}
			}

		public:
			HookCallback(bool interceptCall, T customReturnValue)
			{
				m_bInterceptCall = interceptCall;
				m_customReturnValue = customReturnValue;
			}
			HookCallback(bool interceptCall)
			{
				m_bInterceptCall = interceptCall;
				m_customReturnValue = T();
			}

		private:
			bool m_bInterceptCall;
			T m_customReturnValue;
		};

		/// <summary>
		/// Contains hooks for certain game functions.
		/// </summary>
		public ref class GameHooks
		{
		public:
			delegate HookCallback<int> AddSceneLightDelegate(uint32_t a1, uint32_t nLightType, uint32_t nFlags, Vector3 vDir, Vector3 vTanDir, Vector3 vPos, Vector3 vColor, float fIntensity, int32_t texHash, int32_t txdSlot, float fRange, float fInnerConeAngle, float fOuterConeAngle, float fVolIntensity, float fVolSizeScale, int32_t interiorId, uint32_t a15, uint32_t nID);
			delegate HookCallback<int> RenderCoronaDelegate(int id, Color color, float a5, Vector3 pos, float range, float a8, float a9, int a10, float a11, char a12, char a13, int a14);

		public:
			static event AddSceneLightDelegate^ OnAddSceneLight;
			static event RenderCoronaDelegate^ OnRenderCorona;

		internal:
			static HookCallback<int> RaiseOnAddSceneLight(uint32_t a1, uint32_t nLightType, uint32_t nFlags, CVector* vDir, CVector* vTanDir, CVector* vPos, CVector* vColor, float fIntensity, int32_t texHash, int32_t txdSlot, float fRange, float fInnerConeAngle, float fOuterConeAngle, float fVolIntensity, float fVolSizeScale, int32_t interiorId, uint32_t a15, uint32_t nID)
			{
				return OnAddSceneLight(a1,
					nLightType,
					nFlags,
					CVectorToVector3(*vDir),
					CVectorToVector3(*vTanDir),
					CVectorToVector3(*vPos),
					CVectorToVector3(*vColor),
					fIntensity,
					texHash,
					txdSlot,
					fRange,
					fInnerConeAngle,
					fOuterConeAngle,
					fVolIntensity,
					fVolSizeScale,
					interiorId,
					a15,
					nID);
			}
			static HookCallback<int> RaiseOnRenderCorona(int id, uint8_t r, uint8_t g, uint8_t b, float a5, CVector* pos, float range, float a8, float a9, int a10, float a11, char a12, char a13, int a14)
			{
				return OnRenderCorona(
					id,
					Color::FromArgb(255, r, g, b),
					a5,
					CVectorToVector3(*pos),
					range,
					a8,
					a9,
					a10,
					a11,
					a12,
					a13,
					a14);
			}

		};

	}
}

class UnmanagedGameHooks
{
public:
	static bool Initialize()
	{
		originalAddSceneLight = nullptr;
		originalRenderCorona = nullptr;

		MH_STATUS mhStatus;

		// AddSceneLight func hook
		if (!originalAddSceneLight)
		{
			mhStatus = MH_CreateHook((LPVOID*)AddressSetter::Get(0x4C59F0, 0x62DF00), &AddSceneLightHook, (void**)&originalAddSceneLight);

			if (mhStatus != MH_OK)
			{
				Logger::LogError(String::Format("[GameHooks] Could not hook AddSceneLight func! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
				return false;
			}

			Logger::LogDebug("[GameHooks] Hooked AddSceneLight func.");
		}

		// RenderCorona func hook
		if (!originalRenderCorona)
		{
			mhStatus = MH_CreateHook((LPVOID*)AddressSetter::Get(0x3E1970, 0x66F7B0), &RenderCoronaHook, (void**)&originalRenderCorona);

			if (mhStatus != MH_OK)
			{
				Logger::LogError(String::Format("[GameHooks] Could not hook RenderCorona func! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
				return false;
			}

			Logger::LogDebug("[GameHooks] Hooked RenderCorona func.");
		}

		return true;
	}

private:
	static inline AddSceneLightT* originalAddSceneLight;
	static inline RenderCoronaT* originalRenderCorona;

private:
	static inline int __cdecl AddSceneLightHook(uint32_t a1, uint32_t nLightType, uint32_t nFlags, CVector* vDir, CVector* vTanDir, CVector* vPos, CVector* vColor, float fIntensity, int32_t texHash, int32_t txdSlot, float fRange, float fInnerConeAngle, float fOuterConeAngle, float fVolIntensity, float fVolSizeScale, int32_t interiorId, uint32_t a15, uint32_t nID)
	{
		// Raise managed event
		IVSDKDotNet::Hooking::HookCallback<int> callback = IVSDKDotNet::Hooking::GameHooks::RaiseOnAddSceneLight(a1, nLightType, nFlags, vDir, vTanDir, vPos, vColor, fIntensity, texHash, txdSlot, fRange, fInnerConeAngle, fOuterConeAngle, fVolIntensity, fVolSizeScale, interiorId, a15, nID);

		if (callback.InterceptCall)
			return callback.CustomReturnValue;

		// Call original function if allowed to
		return originalAddSceneLight(a1, nLightType, nFlags, vDir, vTanDir, vPos, vColor, fIntensity, texHash, txdSlot, fRange, fInnerConeAngle, fOuterConeAngle, fVolIntensity, fVolSizeScale, interiorId, a15, nID);
	}
	static inline int __cdecl RenderCoronaHook(int id, uint8_t r, uint8_t g, uint8_t b, float a5, CVector* pos, float range, float a8, float a9, int a10, float a11, char a12, char a13, int a14)
	{
		// Raise managed event
		IVSDKDotNet::Hooking::HookCallback<int> callback = IVSDKDotNet::Hooking::GameHooks::RaiseOnRenderCorona(id, r, g, b, a5, pos, range, a8, a9, a10, a11, a12, a13, a14);

		if (callback.InterceptCall)
			return callback.CustomReturnValue;

		// Call original function if allowed to
		return originalRenderCorona(id, r, g, b, a5, pos, range, a8, a9, a10, a11, a12, a13, a14);
	}

};
