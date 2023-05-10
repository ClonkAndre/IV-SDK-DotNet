#include "pch.h"
#include "CVehicleFactoryNY.h"

namespace IVSDKDotNet {

	CVehicle^ CVehicleFactoryNY::CreateVehicle(int32_t model, int32_t createdBy, GTAMatrix mat, bool bNetwork)
	{
		Native_CMatrix* matrix = new Native_CMatrix(mat.right, mat.up, mat.at, mat.pos);

		Native_CVehicleFactoryNY* vehicleFactory = AddressSetter::GetRef<Native_CVehicleFactoryNY*>(0x11F5514, 0xE52DE8);
		Native_CVehicle* nativeVehicle = vehicleFactory->CreateVehicle(model, createdBy, matrix, bNetwork);

		if (nativeVehicle)
		{
			CVehicle^ vehicle = gcnew CVehicle(nativeVehicle);

			delete matrix;

			return vehicle;
		}

		delete matrix;

		return nullptr;
	}

}