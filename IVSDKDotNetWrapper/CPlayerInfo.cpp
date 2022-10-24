#include "pch.h"
#include "CPlayerInfo.h"

namespace IVSDKDotNet {

	bool CPlayerInfo::IsPlayerActive(int id)
	{
		return Native_CPlayerInfo::IsPlayerActive(id);
	}

	uint32_t CPlayerInfo::FindPlayerPed()
	{
		return Native_CPlayerInfo::FindPlayerPed();
	}
	uint32_t CPlayerInfo::FindPlayerVehicle()
	{
		return Native_CPlayerInfo::FindPlayerVehicle();
	}

}