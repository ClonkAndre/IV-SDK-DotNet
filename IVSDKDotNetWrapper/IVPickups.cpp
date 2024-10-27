#include "pch.h"
#include "IVPickups.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPickup::IVPickup(CPickup* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePickup = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVPickup^ IVPickup::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPickup((CPickup*)ptr.ToPointer());
	}
	UIntPtr IVPickup::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePickup, UIntPtr::Zero);
		return UIntPtr(NativePickup);
	}

	int IVPickup::Destroy()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
		return NativePickup->Destroy();
	}


	// IVPickups
	int IVPickups::Shutdown()
	{
		return CPickups::Shutdown();
	}
	int IVPickups::Reset()
	{
		return CPickups::Reset();
	}
	void IVPickups::DoPickUpEffects()
	{
		CPickups::DoPickUpEffects();
	}
	void IVPickups::CreateTemporaryRadarBlipsForPickupsInArea(Vector3 pos, float range, int type)
	{
		CVector vec = Vector3ToCVector(pos);
		CPickups::CreateTemporaryRadarBlipsForPickupsInArea(&vec, range, type);
	}
	void IVPickups::RemoveTemporaryRadarBlipsForPickups()
	{
		CPickups::RemoveTemporaryRadarBlipsForPickups();
	}

}