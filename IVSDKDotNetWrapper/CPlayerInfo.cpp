#include "pch.h"
#include "CPlayerInfo.h"

namespace IVSDKDotNet {

	uint32_t CPlayerInfo::FindPlayerPed()
	{
		return Native_CPlayerInfo::FindPlayerPed();
	}
	uint32_t CPlayerInfo::FindPlayerVehicle()
	{
		return Native_CPlayerInfo::FindPlayerVehicle();
	}

}