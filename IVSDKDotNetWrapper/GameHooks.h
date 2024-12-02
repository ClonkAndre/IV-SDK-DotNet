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
			delegate HookCallback<int> GetTrafficLightStateDelegate(bool a1, int timeOffsetMilliseconds);
			delegate HookCallback<bool> RegisterNativeDelegate(uint32_t% hash, IntPtr% funcPtr);

			delegate HookCallback<bool> IsNetworkGameRunningDelegate();

		public:
			static event AddSceneLightDelegate^ OnAddSceneLight;
			static event RenderCoronaDelegate^ OnRenderCorona;
			static event GetTrafficLightStateDelegate^ OnGetTrafficLightState1;
			static event GetTrafficLightStateDelegate^ OnGetTrafficLightState2;

			static event RegisterNativeDelegate^ OnRegisterNative;
			static event RegisterNativeDelegate^ OnRegisterNativeNoChecks;

			static event IsNetworkGameRunningDelegate^ OnIsNetworkGameRunning;

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
			static HookCallback<int> RaiseOnGetTrafficLightState1(bool a1, int timeOffsetMilliseconds)
			{
				return OnGetTrafficLightState1(a1, timeOffsetMilliseconds);
			}
			static HookCallback<int> RaiseOnGetTrafficLightState2(bool a1, int timeOffsetMilliseconds)
			{
				return OnGetTrafficLightState2(a1, timeOffsetMilliseconds);
			}

			static HookCallback<bool> RaiseOnRegisterNative(uint32_t% hash, IntPtr% funcPtr)
			{
				return OnRegisterNative(hash, funcPtr);
			}
			static HookCallback<bool> RaiseOnRegisterNativeNoChecks(uint32_t% hash, IntPtr% funcPtr)
			{
				return OnRegisterNativeNoChecks(hash, funcPtr);
			}

			static HookCallback<bool> RaiseOnIsNetworkGameRunning()
			{
				return OnIsNetworkGameRunning();
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

		// GetTrafficLightState1 func hook
		if (!originalGetTrafficLightState1)
		{
			// First patterns test (Works for 1070 and 1080 other versions are yet to be tested)
			// 80 7C 24 04 00 8B 44 24 08 74 28      (FUNC: 80 7C 24 04 00 8B 44 24 08 74) // 1070: 0x88C6F0
			auto scan = hook::pattern(std::string_view("80 7C 24 04 00 8B 44 24 08 74 28"));

			assert(!scan.empty());

			mhStatus = MH_CreateHook((LPVOID*)scan.get_first(0), &GetTrafficLightState1, (void**)&originalGetTrafficLightState1);

			if (mhStatus != MH_OK)
			{
				Logger::LogError(String::Format("[GameHooks] Could not hook GetTrafficLightState1 func! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
				return false;
			}
		}

		// GetTrafficLightState2 func hook
		if (!originalGetTrafficLightState2)
		{
			// First patterns test (Works for 1070 and 1080 other versions are yet to be tested)
			// 80 7C 24 04 00 74 2F      (FUNC: 80 7C 24 04 00 74 2F) // 1070: 0x88C750
			auto scan = hook::pattern(std::string_view("80 7C 24 04 00 74 2F"));

			assert(!scan.empty());

			mhStatus = MH_CreateHook((LPVOID*)scan.get_first(0), &GetTrafficLightState2, (void**)&originalGetTrafficLightState2);

			if (mhStatus != MH_OK)
			{
				Logger::LogError(String::Format("[GameHooks] Could not hook GetTrafficLightState2 func! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
				return false;
			}
		}

		// RegisterNative func hook
		if (!originalRegisterNative)
		{
			mhStatus = MH_CreateHook((LPVOID*)AddressSetter::Get(0x1A6200, 0x225620), &RegisterNativeHook, (void**)&originalRegisterNative);

			if (mhStatus != MH_OK)
			{
				Logger::LogError(String::Format("[GameHooks] Could not hook RegisterNative func! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
				return false;
			}

			Logger::LogDebug("[GameHooks] Hooked RegisterNative func.");
		}

		// RegisterNativeNoChecks func hook
		if (!originalRegisterNativeNoChecks)
		{
			mhStatus = MH_CreateHook((LPVOID*)AddressSetter::Get(0x1A7720, 0x226B40), &RegisterNativeNoChecksHook, (void**)&originalRegisterNativeNoChecks);

			if (mhStatus != MH_OK)
			{
				Logger::LogError(String::Format("[GameHooks] Could not hook RegisterNativeNoChecks func! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
				return false;
			}

			Logger::LogDebug("[GameHooks] Hooked RegisterNativeNoChecks func.");
		}

		// IsNetworkGameRunning func hook
		if (!originalIsNetworkGameRunning)
		{
			auto scan = hook::pattern(std::string_view("53 8A 1D ? ? ? ? 84 DB 74"));

			assert(!scan.empty());

			mhStatus = MH_CreateHook((LPVOID*)scan.get_first(0), &IsNetworkGameRunning, (void**)&originalIsNetworkGameRunning);

			if (mhStatus != MH_OK)
			{
				Logger::LogError(String::Format("[GameHooks] Could not hook IsNetworkGameRunning func! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
				return false;
			}
		}

		return true;
	}

private:
	static inline AddSceneLightT* originalAddSceneLight;
	static inline RenderCoronaT* originalRenderCorona;

	static inline GetTrafficLightStateT* originalGetTrafficLightState1;
	static inline GetTrafficLightStateT* originalGetTrafficLightState2;

	static inline RegisterNativeT* originalRegisterNative;
	static inline RegisterNativeNoChecksT* originalRegisterNativeNoChecks;

	static inline IsNetworkGameRunningT* originalIsNetworkGameRunning;

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

	// a1 = When set to false: Times them signals differently
	static inline int __cdecl GetTrafficLightState1(bool a1, int timeOffsetMilliseconds)
	{
		// Raise managed event
		IVSDKDotNet::Hooking::HookCallback<int> callback = IVSDKDotNet::Hooking::GameHooks::RaiseOnGetTrafficLightState1(a1, timeOffsetMilliseconds);

		if (callback.InterceptCall)
			return callback.CustomReturnValue;

		// Call original function if allowed to
		return originalGetTrafficLightState1(a1, timeOffsetMilliseconds);
	}
	static inline int __cdecl GetTrafficLightState2(bool a1, int timeOffsetMilliseconds)
	{
		// Raise managed event
		IVSDKDotNet::Hooking::HookCallback<int> callback = IVSDKDotNet::Hooking::GameHooks::RaiseOnGetTrafficLightState2(a1, timeOffsetMilliseconds);

		if (callback.InterceptCall)
			return callback.CustomReturnValue;

		// Call original function if allowed to
		return originalGetTrafficLightState2(a1, timeOffsetMilliseconds);
	}

	static inline bool __cdecl RegisterNativeHook(uint32_t hash, LPVOID funcPtr)
	{
		uint32_t managedHash = hash;
		IntPtr managedFuncPtr = IntPtr(funcPtr);

		// Raise managed event
		IVSDKDotNet::Hooking::HookCallback<bool> callback = IVSDKDotNet::Hooking::GameHooks::RaiseOnRegisterNative(managedHash, managedFuncPtr);

		// Apply new parameters
		hash = managedHash;
		funcPtr = managedFuncPtr.ToPointer();

		// Check if call should be intercepted
		if (callback.InterceptCall)
			return callback.CustomReturnValue;

		return originalRegisterNative(hash, funcPtr);
	}
	static inline bool __stdcall RegisterNativeNoChecksHook(uint32_t hash, LPVOID funcPtr)
	{
		uint32_t managedHash = hash;
		IntPtr managedFuncPtr = IntPtr(funcPtr);

		// Raise managed event
		IVSDKDotNet::Hooking::HookCallback<bool> callback = IVSDKDotNet::Hooking::GameHooks::RaiseOnRegisterNativeNoChecks(managedHash, managedFuncPtr);

		// Apply new parameters
		hash = managedHash;
		funcPtr = managedFuncPtr.ToPointer();

		// Check if call should be intercepted
		if (callback.InterceptCall)
			return callback.CustomReturnValue;

		return originalRegisterNativeNoChecks(hash, funcPtr);
	}

	static inline bool __cdecl IsNetworkGameRunning()
	{
		// Raise managed event
		IVSDKDotNet::Hooking::HookCallback<bool> callback = IVSDKDotNet::Hooking::GameHooks::RaiseOnIsNetworkGameRunning();

		if (callback.InterceptCall)
			return callback.CustomReturnValue;

		// Call original function if allowed to
		return originalIsNetworkGameRunning();
	}

};