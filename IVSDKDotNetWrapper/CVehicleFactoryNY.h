#pragma once

class Native_CVehicleFactory
{
public:

};

class Native_CVehicleFactoryNY : Native_CVehicleFactory
{
public:

	Native_CVehicle* CreateVehicle(int32_t model, int32_t createdBy, Native_CMatrix* mat, bool bNetwork)
	{
		return ((Native_CVehicle * (__thiscall*)(Native_CVehicleFactoryNY*, int32_t, int32_t, Native_CMatrix*, bool))(*(void***)this)[1])(this, model, createdBy, mat, bNetwork);
	}
};

namespace IVSDKDotNet {

	public ref class CVehicleFactoryNY
	{
	public:
		static CVehicle^ CreateVehicle(int32_t model, int32_t createdBy, GTAMatrix mat, bool bNetwork);
	};

}