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
		IVVehicle^ CreateVehicle(int32_t model, int32_t createdBy, IVMatrix^ mat, bool bNetwork);

	internal:
		IVVehicleFactoryNY(CVehicleFactoryNY* nativePtr);

	internal:
		CVehicleFactoryNY* NativeVehicleFactoryNY;
	};
}