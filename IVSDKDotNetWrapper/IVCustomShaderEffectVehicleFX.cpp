#include "pch.h"
#include "IVCustomShaderEffectVehicleFX.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVCustomShaderEffectVehicleFX::IVCustomShaderEffectVehicleFX(CCustomShaderEffectVehicleFX* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeCustomShaderEffectVehicleFX = nativePtr;
    }
}