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

		public:
			static event AddSceneLightDelegate^ OnAddSceneLight;

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

		};

	}
}

class UnmanagedGameHooks
{
public:
	static bool Initialize()
	{
		originalAddSceneLight = nullptr;

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

		return true;
	}

private:
	static inline AddSceneLightT* originalAddSceneLight;

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

};
