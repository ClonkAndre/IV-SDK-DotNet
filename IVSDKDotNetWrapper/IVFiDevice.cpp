#include "pch.h"
#include "IVFiDevice.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVFiDevice::IVFiDevice(rage::fiDevice* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeFiDevice = nativePtr;
    }

    // - - - Methods / Functions - - -
    bool IVFiDevice::Mount(String^ path, UIntPtr device, bool bUnk1)
    {
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(path, false);
        msclr::interop::marshal_context ctx;
        return rage::fiDevice::Mount((char*)ctx.marshal_as<const char*>(path), (rage::fiDeviceLocal*)device.ToPointer(), bUnk1);
    }
    bool IVFiDevice::Unmount(String^ path)
    {
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(path, false);
        msclr::interop::marshal_context ctx;
        return rage::fiDevice::Unmount((char*)ctx.marshal_as<const char*>(path));
    }

    IVFiDevice^ IVFiDevice::FromUIntPtr(UIntPtr ptr)
    {
        UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVFiDevice((rage::fiDevice*)ptr.ToPointer());
    }
    UIntPtr IVFiDevice::GetUIntPtr()
    {
        NULLPTR_CHECK_WITH_RETURN(NativeFiDevice, UIntPtr::Zero);
        return UIntPtr(NativeFiDevice);
    }

    uint32_t IVFiDevice::SetPath(String^ path, bool bAbsolute)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeFiDevice, 0);
        msclr::interop::marshal_context ctx;
        return NativeFiDevice->SetPath((char*)ctx.marshal_as<const char*>(path), bAbsolute);
    }
    uint32_t IVFiDevice::SetMountPath(String^ path)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeFiDevice, 0);
        msclr::interop::marshal_context ctx;
        return NativeFiDevice->SetMountPath((char*)ctx.marshal_as<const char*>(path));
    }

}