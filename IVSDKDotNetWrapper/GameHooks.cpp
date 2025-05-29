#include "pch.h"
#include "GameHooks.h"

namespace IVSDKDotNet
{
	namespace Hooking
	{



	}
}

void UnmanagedGameHooks::Initialize()
{
	TryCreateHook("UnmanagedGameHooks", "AddSceneLight", &AddSceneLightHook, (void**)&originalAddSceneLight);
	TryCreateHook("UnmanagedGameHooks", "RenderCorona", &RenderCoronaHook, (void**)&originalRenderCorona);
	TryCreateHook("UnmanagedGameHooks", "GetTrafficLightState1", &GetTrafficLightState1, (void**)&originalGetTrafficLightState1);
	TryCreateHook("UnmanagedGameHooks", "GetTrafficLightState2", &GetTrafficLightState2, (void**)&originalGetTrafficLightState2);
	TryCreateHook("UnmanagedGameHooks", "RegisterNative", &RegisterNativeHook, (void**)&originalRegisterNative);
	TryCreateHook("UnmanagedGameHooks", "RegisterNativeNoChecks", &RegisterNativeNoChecksHook, (void**)&originalRegisterNativeNoChecks);
	TryCreateHook("UnmanagedGameHooks", "IsNetworkGameRunning", &IsNetworkGameRunning, (void**)&originalIsNetworkGameRunning);
	TryCreateHook("UnmanagedGameHooks", "IsThisMachineTheServer", &IsThisMachineTheServer, (void**)&originalIsThisMachineTheServer);
	TryCreateHook("UnmanagedGameHooks", "DoPickupGlow", &DoPickupGlow, (void**)&originalDoPickupGlow);

	Logger::LogDebug("[GameHooks] Done!");
}
bool UnmanagedGameHooks::TryCreateHook(const std::string& section, const std::string& key, LPVOID detour, LPVOID* ppOriginal)
{
	MH_STATUS mhStatus;

	// Figure out if config is a pattern or a regular memory address
	if (AddressSetter::IsConfigPattern(section, key))
	{
		auto scan = hook::pattern(AddressSetter::GetConfigString(section, key));

		assert(!scan.empty());

		mhStatus = MH_CreateHook((LPVOID*)scan.get_first(0), detour, ppOriginal);

	}
	else
	{
		mhStatus = MH_CreateHook((LPVOID*)AddressSetter::Get(section, key), detour, ppOriginal);
	}

	// Validate
	if (mhStatus != MH_OK)
	{
		Logger::LogError(String::Format("[GameHooks] Could not hook {0} func! Details: {1}", gcnew String(key.c_str()), gcnew String(MH_StatusToString(mhStatus))));
		return false;
	}

	Logger::LogDebug(String::Format("[GameHooks] Hooked {0} func.", gcnew String(key.c_str())));
	return true;
}