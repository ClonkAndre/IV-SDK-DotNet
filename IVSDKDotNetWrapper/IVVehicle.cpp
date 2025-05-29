#include "pch.h"
#include "IVVehicle.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVVehicleHandlingFlags::IVVehicleHandlingFlags(CVehicle* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicle = nativePtr;
    }
    IVVehicleFlags::IVVehicleFlags(CVehicle* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicle = nativePtr;
    }
    IVVehicleFlags2::IVVehicleFlags2(CVehicle* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicle = nativePtr;
    }
    IVVehicleFlags3::IVVehicleFlags3(CVehicle* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicle = nativePtr;
    }
    IVVehicleFlags4::IVVehicleFlags4(CVehicle* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicle = nativePtr;
    }
    IVVehicleAbsFlags::IVVehicleAbsFlags(CVehicle* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicle = nativePtr;
    }
    IVVehicleAutomobileFlags::IVVehicleAutomobileFlags(CVehicle* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicle = nativePtr;
    }
    IVVehicle::IVVehicle(CVehicle* nativePtr) : IVPhysical(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicle = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVVehicle^ IVVehicle::FromUIntPtr(UIntPtr ptr)
    {
        UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVVehicle((CVehicle*)ptr.ToPointer());
    }
    UIntPtr IVVehicle::GetUIntPtr()
    {
        NULLPTR_CHECK_WITH_RETURN(NativeVehicle, UIntPtr::Zero);
        return UIntPtr(NativeVehicle);
    }

    void IVVehicle::Fix()
    {
        NULLPTR_CHECK(NativeVehicle);
        NativeVehicle->Fix();
    }
    void IVVehicle::SetRemap(int32_t id)
    {
        NULLPTR_CHECK(NativeVehicle);
        NativeVehicle->SetRemap(id);
    }
    int IVVehicle::GetRemapIndex()
    {
        NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
        return NativeVehicle->GetRemapIndex();
    }
    void IVVehicle::MakeDirty()
    {
        NULLPTR_CHECK(NativeVehicle);
        NativeVehicle->MakeDirty();
    }
    void IVVehicle::GetVehicleLightsStatus()
    {
        NULLPTR_CHECK(NativeVehicle);
        NativeVehicle->GetVehicleLightsStatus();
    }
    int IVVehicle::GetSeatPartId(int32_t seat)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
        return NativeVehicle->GetSeatPartId(seat);
    }
    bool IVVehicle::GetCameraType(int32_t% type)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
        
        int nType;
        bool result = NativeVehicle->GetCameraType(&nType);
        type = nType;
        return result;
    }
    void IVVehicle::ProcessRespot(float delta)
    {
        NULLPTR_CHECK(NativeVehicle);
        NativeVehicle->ProcessRespot(delta);
    }
    void IVVehicle::ProcessAirControl(UIntPtr unk)
    {
        NULLPTR_CHECK(NativeVehicle);
        UINTPTR_ZERO_CHECK(unk);
        NativeVehicle->ProcessAirControl(unk.ToPointer());
    }
    bool IVVehicle::IsDriver(IVPed^ pPed)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
        NULLPTR_CHECK_WITH_RETURN(pPed, false);
        return NativeVehicle->IsDriver(pPed->NativePed);
    }

    int IVVehicle::GetNumberOfWheelsTouchingGround()
    {
        NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
        return NativeVehicle->GetNumberOfWheelsTouchingGround();;
    }

    float IVVehicle::HeightAboveCeiling(float height, int32_t flightModel)
    {
        return CVehicle::HeightAboveCeiling(height, flightModel);
    }
    bool IVVehicle::UsesSiren(int32_t id)
    {
        return CVehicle::UsesSiren(id);
    }

}