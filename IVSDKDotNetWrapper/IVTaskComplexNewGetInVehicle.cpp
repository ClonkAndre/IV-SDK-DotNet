#include "pch.h"
#include "IVTaskComplexNewGetInVehicle.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTaskComplexNewGetInVehicle::IVTaskComplexNewGetInVehicle(CTaskComplexNewGetInVehicle* nativePtr) : IVTaskComplex(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTask = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVTaskComplexNewGetInVehicle^ IVTaskComplexNewGetInVehicle::Create(UIntPtr veh, int32_t getInType, uint32_t unk27, int32_t unk, float fUnk)
    {
        UINTPTR_ZERO_CHECK_WITH_RETURN(veh, nullptr);

        CTaskComplexNewGetInVehicle* ptr = new CTaskComplexNewGetInVehicle((CVehicle*)veh.ToPointer(), getInType, unk27, unk, fUnk);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

        return gcnew IVTaskComplexNewGetInVehicle(ptr);
    }

}