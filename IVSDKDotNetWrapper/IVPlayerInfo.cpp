#include "pch.h"
#include "IVPlayerInfo.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPlayerInfo::IVPlayerInfo(CPlayerInfo* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePlayerInfo = nativePtr;
	}

	// - - - Methods / Functions - - -
	void IVPlayerInfo::KillPlayerOutsideWorld()
	{
		NULLPTR_CHECK(NativePlayerInfo);
		NativePlayerInfo->KillPlayerOutsideWorld();
	}
	bool IVPlayerInfo::IsPlayerActive(int id)
	{
		return CPlayerInfo::IsPlayerActive(id);
	}
	IVPlayerInfo^ IVPlayerInfo::GetPlayerInfo(uint32_t nPlayerId)
	{
		CPlayerInfo* ptr = CPlayerInfo::GetPlayerInfo(nPlayerId);
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPlayerInfo(ptr);
	}
	Vector3 IVPlayerInfo::FindThePlayerCentreOfWorld(Vector3 v)
	{
		CVector* nv = new CVector();
		nv->x = v.X;
		nv->y = v.Y;
		nv->z = v.Z;

		CVector& vec = FindPlayerCentreOfWorld(nv);

		delete nv;

		return Vector3(vec.x, vec.y, vec.z);
	}
	UIntPtr IVPlayerInfo::FindThePlayerPed()
	{
		CPed* ptr = FindPlayerPed();
		NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
		return UIntPtr(ptr);
	}

}