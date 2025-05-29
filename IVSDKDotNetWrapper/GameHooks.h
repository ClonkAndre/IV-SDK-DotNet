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
			delegate HookCallback<bool> IsThisMachineTheServerDelegate();

			delegate HookCallback<int> OnDoPickupGlowDelegate();

		public:
			static event AddSceneLightDelegate^ OnAddSceneLight;
			static event RenderCoronaDelegate^ OnRenderCorona;
			static event GetTrafficLightStateDelegate^ OnGetTrafficLightState1;
			static event GetTrafficLightStateDelegate^ OnGetTrafficLightState2;

			static event RegisterNativeDelegate^ OnRegisterNative;
			static event RegisterNativeDelegate^ OnRegisterNativeNoChecks;

			static event IsNetworkGameRunningDelegate^ OnIsNetworkGameRunning;
			static event IsThisMachineTheServerDelegate^ OnIsThisMachineTheServer;

			static event OnDoPickupGlowDelegate^ OnDoPickupGlow;

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
			static HookCallback<bool> RaiseOnIsThisMachineTheServer()
			{
				return OnIsThisMachineTheServer();
			}

			static HookCallback<int> RaiseOnDoPickupGlow()
			{
				return OnDoPickupGlow();
			}

		};

	}
}

class UnmanagedGameHooks
{
public:
	static void Initialize();

private:
	static bool TryCreateHook(const std::string& section, const std::string& key, LPVOID detour, LPVOID* ppOriginal);

private:
	static inline AddSceneLightT* originalAddSceneLight = nullptr;
	static inline RenderCoronaT* originalRenderCorona = nullptr;

	static inline GetTrafficLightStateT* originalGetTrafficLightState1 = nullptr;
	static inline GetTrafficLightStateT* originalGetTrafficLightState2 = nullptr;

	static inline RegisterNativeT* originalRegisterNative = nullptr;
	static inline RegisterNativeNoChecksT* originalRegisterNativeNoChecks = nullptr;

	static inline IsNetworkGameRunningT* originalIsNetworkGameRunning = nullptr;
	static inline IsThisMachineTheServerT* originalIsThisMachineTheServer = nullptr;

	static inline DoPickupGlowT* originalDoPickupGlow = nullptr;

	//static inline AddExplosionT* originalAddExplosion;

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
	static inline bool __cdecl IsThisMachineTheServer()
	{
		// Raise managed event
		IVSDKDotNet::Hooking::HookCallback<bool> callback = IVSDKDotNet::Hooking::GameHooks::RaiseOnIsThisMachineTheServer();

		if (callback.InterceptCall)
			return callback.CustomReturnValue;

		// Call original function if allowed to
		return originalIsThisMachineTheServer();
	}

	static inline int __cdecl DoPickupGlow()
	{
		// Raise managed event
		IVSDKDotNet::Hooking::HookCallback<int> callback = IVSDKDotNet::Hooking::GameHooks::RaiseOnDoPickupGlow();

		if (callback.InterceptCall)
			return callback.CustomReturnValue;

		return originalDoPickupGlow();
	}

	//static inline bool __cdecl AddExplosionHook(int a1, int a2, int a3, int a4, int a5, char a6, int a7, int a8, float a9, int a10, int a11, int a12, int a13, int a14, char a15, char a16, int a17, char a18, int a19)
	//{
	//	a18 = 1; // Always set to 1 to prevent crashes when manually specifying that the current session is a network game
	//	return originalAddExplosion(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19);
	//}

};