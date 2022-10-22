#include "pch.h"
#include "CTheScripts.h"

namespace IVSDKDotNet {

	bool CTheScripts::IsPlayerOnAMission()
	{
		return Native_CTheScripts::IsPlayerOnAMission();
	}

	uint32_t CTheScripts::FindNativeAddress(uint32_t nativeHash)
	{
		return Native_CTheScripts::FindNativeAddress(nativeHash);
	}

}