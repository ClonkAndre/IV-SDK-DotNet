#pragma once

namespace IVSDKDotNet
{
	public ref class IVVehicleFactoryNY
	{
	public:
		static property IVVehicleFactoryNY^ TheVehicleFactory
		{
		public:
			IVVehicleFactoryNY^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(VehicleFactory, nullptr);
				return gcnew IVVehicleFactoryNY(VehicleFactory);
			}
			void set(IVVehicleFactoryNY^ value)
			{
				NULLPTR_CHECK(value);
				VehicleFactory = value->NativeVehicleFactoryNY;
			}
		}

	public:
		IVVehicle^ CreateVehicle(int32_t modelIndex, int32_t createdBy, IVMatrix mat, bool bNetwork);
		IVVehicle^ CreateVehicle(int32_t modelIndex, int32_t createdBy, Vector3 pos, bool bNetwork);
		int DeleteVehicle(IVVehicle^ veh);

	internal:
		IVVehicleFactoryNY(CVehicleFactoryNY* nativePtr);

	internal:
		CVehicleFactoryNY* NativeVehicleFactoryNY;
	};
}