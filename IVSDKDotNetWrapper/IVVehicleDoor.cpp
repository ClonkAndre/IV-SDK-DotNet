#include "pch.h"
#include "IVVehicleDoor.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVVehicleDoor::IVVehicleDoor(CVehicleDoor* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeVehicleDoor = nativePtr;
	}
}