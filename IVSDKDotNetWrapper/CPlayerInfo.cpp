#include "pch.h"
#include "CPlayerInfo.h"

namespace IVSDKDotNet {

	bool CPlayerInfo::IsPlayerActive(int id)
	{
		return Native_CPlayerInfo::IsPlayerActive(id);
	}

	UIntPtr CPlayerInfo::FindPlayerPed()
	{
		return UIntPtr(Native_CPlayerInfo::FindPlayerPed());
	}
	UIntPtr CPlayerInfo::FindPlayerVehicle()
	{
		//return Native_CPlayerInfo::FindPlayerVehicle();
		return UIntPtr::Zero;
	}

}