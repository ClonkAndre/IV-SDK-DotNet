#pragma once

class Native_CPools
{
public:
	static CPool<Native_CPed>* PedPool()			{ return AddressSetter::GetRef<CPool<Native_CPed>*>(0x14A82AC, 0x14CB03C); }
	static CPool<Native_CVehicle>* VehiclePool()	{ return AddressSetter::GetRef<CPool<Native_CVehicle>*>(0x1219240, 0xE52CD0); }
	static CPool<Native_CObject>* ObjectPool()		{ return AddressSetter::GetRef<CPool<Native_CObject>*>(0xF50CE0, 0xE52B48); }

	//static inline CPool<CBuilding>*& ms_pBuildingPool = AddressSetter::GetRef<CPool<CBuilding>*>(0x128FED0, 0xE4A5E8);
	//static inline CPool<CCam>*& ms_pCameraPool = AddressSetter::GetRef<CPool<CCam>*>(0x1218020, 0xF68158);
	//static inline CPool<CTask>*& ms_pTaskPool = AddressSetter::GetRef<CPool<CTask>*>(0x124B01C, 0x126FE3C);
	//static inline CPool<CInteriorInst>*& ms_pInteriorInstPool = AddressSetter::GetRef<CPool<CInteriorInst>*>(0x125D2E4, 0xE54D74);
	//static inline CPool<CVehicleStructure>*& ms_pVehicleStructPool = AddressSetter::GetRef<CPool<CVehicleStructure>*>(0x12D6594, 0x1001BCC);
	//static inline CPool<CPedMoveBlendOnFoot>*& ms_pPedMoveBlendPool = AddressSetter::GetRef<CPool<CPedMoveBlendOnFoot>*>(0x14A82B4, 0x14CB044);
	//static inline CPool<CDummyPed>*& ms_pDummyPedPool = AddressSetter::GetRef<CPool<CDummyPed>*>(0x14A82BC, 0x14CB04C);
	//static inline CPool<CDummyTask>*& ms_pDummyTaskPool = AddressSetter::GetRef<CPool<CDummyTask>*>(0x1306E8C, 0x128AAC0);
	//static inline CPool<tPedData>*& ms_pUnkPedDataPool = AddressSetter::GetRef<CPool<tPedData>*>(0x14A82B8, 0x14CB048);
	//static inline CPool<CPedIntelligenceNY>*& ms_pPedIntelligencePool = AddressSetter::GetRef<CPool<CPedIntelligenceNY>*>(0x14A82B0, 0x14CB040);
	//static inline CPool<CAnimBlender>*& ms_pAnimBlenderPool = AddressSetter::GetRef<CPool<CAnimBlender>*>(0x12397B0, 0xE4E6B0);
	//static inline CPool<fragInstNMGta>*& ms_pFragInstNMGtaPool = AddressSetter::GetRef<CPool<fragInstNMGta>*>(0x1306660, 0x12767C8);
	//static inline CPool<CPedDataNY>*& ms_pPedDataPool = AddressSetter::GetRef<CPool<CPedDataNY>*>(0x14A82A8, 0x14CB038);
	//static inline CPool<CQuadTreeNode>*& ms_pQuadTreeNodePool = AddressSetter::GetRef<CPool<CQuadTreeNode>*>(0xF504D0, 0x127608C);
	//static inline CPool<TxdDef>*& ms_pTxdPool = AddressSetter::GetRef<CPool<TxdDef>*>(0xDD52D4, 0xE291E0);
	//static inline CPool<IplDef>*& ms_pIplPool = AddressSetter::GetRef<CPool<IplDef>*>(0x128FF98, 0xF6E468);
};

namespace IVSDKDotNet {

	public ref class CPools
	{
	public:

		// - - - Handles only - - -

		static array<Ped>^		GetAllPedHandles();
		static array<Vehicle>^	GetAllVehicleHandles();

		[System::ObsoleteAttribute("Use GetAllObjects function instead.")]
		static array<Entity>^	GetAllObjectHandles();

		/// <summary>
		/// Deletes a char with the given handle.
		/// </summary>
		/// <param name="handle">The handle of the char.</param>
		static void DeleteChar(Ped handle);

		/// <summary>
		/// Deletes a vehicle with the given handle.
		/// </summary>
		/// <param name="handle">The handle of the vehicle.</param>
		static void DeleteCar(Vehicle handle);

		/// <summary>
		/// Deletes a object with the given handle.
		/// </summary>
		/// <param name="handle">The handle of the object.</param>
		static void DeleteObject(Entity handle);

		// - - - IV-SDK Objects - - -

		static array<CVehicle^>^	GetAllVehicles();
		static array<CObject^>^		GetAllObjects();

	};

}