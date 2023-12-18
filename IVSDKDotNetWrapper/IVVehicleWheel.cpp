#include "pch.h"
#include "IVVehicleWheel.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVVehicleWheelFlags::IVVehicleWheelFlags(CVehicleWheel* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicleWheel = nativePtr;
    }
    IVVehicleWheel::IVVehicleWheel(CVehicleWheel* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicleWheel = nativePtr;
    }
}