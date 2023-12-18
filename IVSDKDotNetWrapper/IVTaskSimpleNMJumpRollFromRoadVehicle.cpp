#include "pch.h"
#include "IVTaskSimpleNMJumpRollFromRoadVehicle.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTaskSimpleNMJumpRollFromRoadVehicle::IVTaskSimpleNMJumpRollFromRoadVehicle(CTaskSimpleNMJumpRollFromRoadVehicle* nativePtr) : IVTaskSimple(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTask = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVTaskSimpleNMJumpRollFromRoadVehicle^ IVTaskSimpleNMJumpRollFromRoadVehicle::Create(uint32_t time, uint32_t time2)
    {
        CTaskSimpleNMJumpRollFromRoadVehicle* ptr = new CTaskSimpleNMJumpRollFromRoadVehicle(time, time2);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVTaskSimpleNMJumpRollFromRoadVehicle(ptr);
    }

}