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
    IVVehicle^ IVVehicleFactoryNY::CreateVehicle(int32_t modelIndex, int32_t createdBy, IVMatrix mat, bool bNetwork)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeVehicleFactoryNY, nullptr);

        CVehicle* veh = VehicleFactory->CreateVehicle(modelIndex, createdBy, &mat.ToCMatrix(), bNetwork);
        NULLPTR_CHECK_WITH_RETURN(veh, nullptr);

        return gcnew IVVehicle(veh);
    }
    IVVehicle^ IVVehicleFactoryNY::CreateVehicle(int32_t modelIndex, int32_t createdBy, Vector3 pos, bool bNetwork)
    {
        return CreateVehicle(modelIndex, createdBy, IVMatrix::Translation(pos), bNetwork);
    }
    int IVVehicleFactoryNY::DeleteVehicle(IVVehicle^ veh)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeVehicleFactoryNY, 0);
        NULLPTR_CHECK_WITH_RETURN(veh, 0);
        NULLPTR_CHECK_WITH_RETURN(veh->NativeVehicle, 0);

        return VehicleFactory->DeleteVehicle(veh->NativeVehicle);
    }

}