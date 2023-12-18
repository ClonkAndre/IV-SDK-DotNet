#include "pch.h"
#include "IVVehicleStructure.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVVehicleStructure::IVVehicleStructure(CVehicleStructure* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeVehicleStructure = nativePtr;
	}
}