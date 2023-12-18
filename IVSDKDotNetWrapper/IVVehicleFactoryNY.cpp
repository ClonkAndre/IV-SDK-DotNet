#include "pch.h"
#include "IVVehicleFactoryNY.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVVehicleFactoryNY::IVVehicleFactoryNY(CVehicleFactoryNY* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicleFactoryNY = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVVehicle^ IVVehicleFactoryNY::CreateVehicle(int32_t model, int32_t createdBy, IVMatrix^ mat, bool bNetwork)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeVehicleFactoryNY, nullptr);
        NULLPTR_CHECK_WITH_RETURN(mat, nullptr);
        NULLPTR_CHECK_WITH_RETURN(mat->NativeMatrix, nullptr);

        CVehicle* veh = VehicleFactory->CreateVehicle(model, createdBy, mat->NativeMatrix, bNetwork);
        NULLPTR_CHECK_WITH_RETURN(veh, nullptr);

        return gcnew IVVehicle(veh);
    }

}