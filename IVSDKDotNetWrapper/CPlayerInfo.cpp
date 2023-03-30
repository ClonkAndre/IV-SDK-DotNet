#include "pch.h"
#include "CPlayerInfo.h"

namespace IVSDKDotNet {

	CPlayerInfo::CPlayerInfo(Native_CPlayerInfo* nativePtr)
	{
		PlayerInfoPointer = nativePtr;
	}

	CPlayerInfo^ CPlayerInfo::FromPointer(UIntPtr ptr)
	{
		if (ptr == UIntPtr::Zero)
			return nullptr;

		return gcnew CPlayerInfo((Native_CPlayerInfo*)ptr.ToPointer());
	}
	UIntPtr CPlayerInfo::GetUIntPtr()
	{
		if (!PlayerInfoPointer)
			return UIntPtr::Zero;

		return UIntPtr(PlayerInfoPointer);
	}

	void CPlayerInfo::KillPlayerOutsideWorld()
	{
		PlayerInfoPointer->KillPlayerOutsideWorld();
	}

	// Statics
	bool CPlayerInfo::IsPlayerActive(int id)
	{
		return Native_CPlayerInfo::IsPlayerActive(id);
	}
	CPlayerInfo^ CPlayerInfo::GetPlayerInfo(uint32_t nPlayerId)
	{
		Native_CPlayerInfo* ptr = Native_CPlayerInfo::GetPlayerInfo(nPlayerId);

		if (ptr)
			return gcnew CPlayerInfo(ptr);

		return nullptr;
	}

	UIntPtr CPlayerInfo::FindPlayerPed()
	{
		return UIntPtr(Native_CPlayerInfo::FindPlayerPed());
	}
	UIntPtr CPlayerInfo::FindPlayerVehicle()
	{
		//return UIntPtr(Native_CPlayerInfo::FindPlayerVehicle());
		return UIntPtr::Zero;
	}

}