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
	int IVPickups::CreatePickup(Vector3 position, Vector3 rotation, int modelIndex, int type, bool a5, bool a6, bool a7_maybeBlipRelated, uint32_t objPointerMaybe, char a12, char a13)
	{
		CVector pos = Vector3ToCVector(position);
		CVector rot = Vector3ToCVector(rotation);

		return CPickups::CreatePickup(&pos, &rot, modelIndex, type, a5, a6, a7_maybeBlipRelated, objPointerMaybe, a12, a13);
	}
	int IVPickups::RemovePickup(int handle)
	{
		return CPickups::RemovePickup(handle);
	}
	void IVPickups::CreateTemporaryRadarBlipsForPickupsInArea(Vector3 position, float range, int type)
	{
		CVector pos = Vector3ToCVector(position);
		CPickups::CreateTemporaryRadarBlipsForPickupsInArea(&pos, range, type);
	}
	int IVPickups::CreateTemporaryRadarBlipForPickup(Vector3 position, int pickupIndex)
	{
		CVector pos = Vector3ToCVector(position);
		return CPickups::CreateTemporaryRadarBlipForPickup(&pos, pickupIndex);
	}
	void IVPickups::RemoveTemporaryRadarBlipsForPickups()
	{
		CPickups::RemoveTemporaryRadarBlipsForPickups();
	}

	// Helper functions
	uint8_t IVPickups::GetTypeOfPickup(int index)
	{
		return CPickups::PickupTypes[0x50 * index];
	}

}