class CVehicleFactory
{
public:
	CVehicle* CreateVehicle(int32_t model, int32_t createdBy, CMatrix* mat, bool bNetwork)
	{
		return ((CVehicle * (__thiscall*)(CVehicleFactory*, int32_t, int32_t, CMatrix*, bool))(*(void***)this)[1])(this, model, createdBy, mat, bNetwork);
	}
	int DeleteVehicle(CVehicle* veh)
	{
		return ((int(__thiscall*)(CVehicleFactory*, CVehicle*))(*(void***)this)[2])(this, veh);
	}

};
class CVehicleFactoryNY : public CVehicleFactory
{
public:

};

static CVehicleFactoryNY*& VehicleFactory = AddressSetter::GetRef<CVehicleFactoryNY*>("CVehicleFactory", "VehicleFactory");