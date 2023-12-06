#include "pch.h"
#include "IVFiDevice.h"

namespace IVSDKDotNet
{
    // - - - Methods / Functions - - -
    bool IVFiDevice::Mount(String^ path, UIntPtr device, bool bUnk1)
    {
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(path, false);
        msclr::interop::marshal_context ctx;
        return rage::fiDevice::Mount((char*)ctx.marshal_as<const char*>(path), (rage::fiDeviceLocal*)device.ToPointer(), bUnk1);
    }
}