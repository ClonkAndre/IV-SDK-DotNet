#pragma once

namespace rage { class grmShaderGroup; }

class Native_CPed;
class Native_phInstGta;

struct Native_tHandlingData;

class Native_CVehicleDoor
{
public:
	uint32_t m_nBoneID;					// 00-04 in the order from tVehicleStruct
	uint8_t pad;						// 04-05
	uint8_t m_nGroupID;					// 05-06 group for detach, needs to be higher than 0
	uint8_t pad2[0x2E];					// 06-34
};
VALIDATE_SIZE(Native_CVehicleDoor, 0x34);
VALIDATE_OFFSET(Native_CVehicleDoor, m_nGroupID, 0x5);


class Native_CVehicleWheel
{
public:
	uint32_t m_nBoneID;					// 000-004 in the order from tVehicleStruct
	uint8_t pad[0x5C];					// 004-060
	Native_CVector m_vPosition;			// 060-06C
	uint8_t pad2[0x104];				// 06C-170
};
VALIDATE_SIZE(Native_CVehicleWheel, 0x170);
VALIDATE_OFFSET(Native_CVehicleWheel, m_vPosition, 0x60);


class CCustomShaderEffectVehicleFX : public CCustomShaderEffectBase
{
public:
	char pad[0x10];														// 000-010
	//4 - E0
	//5 - 02
	//6 - CD
	//7 - CD
	//8 - CDCDCDCD
	//C - CDCDCDCD
	Native_CRGBFloat m_fPrimaryColor;									// 010-01C
	Native_CRGBA m_nPrimaryColor;										// 01C-020
	Native_CRGBFloat m_fSecondaryColor;									// 020-02C
	Native_CRGBA m_nSecondaryColor;										// 02C-030
	Native_CRGBFloat m_fTertiaryColor;									// 030-03C independent of spec color
	Native_CRGBA m_nTertiaryColor;										// 03C-040
	Native_CRGBFloat m_fQuaternaryColor;								// 040-04C
	Native_CRGBA m_nQuaternaryColor;									// 04C-050
	Native_CRGBFloat m_fQuinaryColor;									// 050-04C everything non colorable
	Native_CRGBA m_nQuinaryColor;										// 05C-060
	Native_CRGBFloat m_fSpecularColor;									// 060-06C
	Native_CRGBA m_nSpecularColor;										// 06C-070
	rage::grmShaderGroup* m_pShaderGroup;								// 070-074
	float m_fDirtLevel;													// 074-078
	uint8_t m_bWrecked;													// 078-07C
	uint8_t pad6[0x5C];													// 07C-0D8
	int32_t m_nLivery;													// 0D8-0DC
};
VALIDATE_OFFSET(CCustomShaderEffectVehicleFX, m_fPrimaryColor, 0x10);
VALIDATE_OFFSET(CCustomShaderEffectVehicleFX, m_fSecondaryColor, 0x20);
VALIDATE_OFFSET(CCustomShaderEffectVehicleFX, m_fTertiaryColor, 0x30);
VALIDATE_OFFSET(CCustomShaderEffectVehicleFX, m_fQuaternaryColor, 0x40);
VALIDATE_OFFSET(CCustomShaderEffectVehicleFX, m_fQuinaryColor, 0x50);
VALIDATE_OFFSET(CCustomShaderEffectVehicleFX, m_fSpecularColor, 0x60);
VALIDATE_OFFSET(CCustomShaderEffectVehicleFX, m_nLivery, 0xD8);
VALIDATE_OFFSET(CCustomShaderEffectVehicleFX, m_fDirtLevel, 0x74);
VALIDATE_OFFSET(CCustomShaderEffectVehicleFX, m_bWrecked, 0x78);

class Native_CVehicle : public Native_CPhysical
{
public:
	// 0000-0210
	uint8_t pad[0x9D];													// 0210-02AD
	uint8_t m_nPrimaryColor2;											// 02AD-02AE
	uint8_t m_nSecondaryColor2;											// 02AE-02AF
	uint8_t m_nTertiaryColor2;											// 02AF-02B0
	uint8_t m_nQuaternaryColor2;										// 02B0-02B1
	uint8_t pad1[0x3D7];												// 02B1-0688
	float m_fEngineRPM;													// 0688-068C
	uint8_t pad1_[0x788];												// 068C-0E14
	Native_phInstGta* m_pVehicleFragInst;								// 0E14-0E18
	Native_tHandlingData* m_pHandling;									// 0E18-0E1C
	struct
	{
		unsigned int bSmoothCompresn : 1;
		unsigned int bNone : 1;
		unsigned int bNpcAntiRoll : 1;
		unsigned int bNpcNeutralHandl : 1;
		unsigned int bNoHandbrake : 1;
		unsigned int bSteerRearwheels : 1;
		unsigned int bHbRearwheelSteer : 1;
		unsigned int bAltSteerOpt : 1;
		unsigned int bWheelFNarrow2 : 1;
		unsigned int bWheelFNarrow : 1;
		unsigned int bWheelFWide : 1;
		unsigned int bWheelFWide2 : 1;
		unsigned int bWheelRNarrow2 : 1;
		unsigned int bWheelRNarrow : 1;
		unsigned int bWheelRWide : 1;
		unsigned int bWheelRWide2 : 1;
		unsigned int bHydraulicGeom : 1;
		unsigned int bHydraulicInst : 1;
		unsigned int bHydraulicNone : 1;
		unsigned int bNosInst : 1;
		unsigned int bOffroadAbility : 1;
		unsigned int bOffroadAbility2 : 1;
		unsigned int bHalogenLights : 1;
		unsigned int bProcRearwheel1st : 1;
		unsigned int bUseMaxspLimit : 1;
		unsigned int bLowRider : 1;
		unsigned int bStreetRacer : 1;
		unsigned int bNone2 : 1;
		unsigned int bSwingingChassis : 1;
		unsigned int bOldPhysics : 1;
		unsigned int bNone3 : 1;
		unsigned int bNone4 : 1;
	} m_nHandlingFlags;									// 0E1C-0E20
	uint8_t pad2[0x144];												// 0E20-0F64
	struct
	{
		unsigned int pad : 3;
		unsigned int bEngineOn : 1;
		unsigned int bEngineStarting : 1;
		unsigned int pad2 : 2;
		unsigned int bIsHandbrakeOn : 1;
		unsigned int pad3 : 24;
	} m_nVehicleFlags;									// 0F64-0F68
	uint8_t pad3[0x8];													// 0F68-0F70
	struct
	{
		unsigned int pad : 2;
		unsigned int bCanBeVisiblyDamaged : 1;
		unsigned int pad2 : 29;
	} m_nVehicleFlags2;									// 0F70-0F74
	uint8_t pad4[0x2C];													// 0F74-0FA0
	Native_CPed* m_pDriver;												// 0FA0-0FA4
	Native_CPed* m_pPassengers[8];										// 0FA4-0FC4
	uint8_t pad5[0xC];													// 0FC4-0FD0
	Native_CVehicleWheel* m_pWheels;									// 0FD0-0FD4
	uint32_t m_nWheelCount;												// 0FD4-0FD8
	Native_CVehicleDoor* m_pDoors;										// 0FD8-0FDC
	uint32_t m_nDoorCount;												// 0FDC-0FE0
	struct
	{
		unsigned int pad : 16;
		unsigned int bAbs : 1;
		unsigned int bAbsAlt : 1;
		unsigned int pad2 : 13;
	} m_nAbsFlags;										// 0FE0-0FE4
	uint8_t m_nPrimaryColor;											// 0FE4-0FE5
	uint8_t m_nSecondaryColor;											// 0FE5-0FE6
	uint8_t m_nTertiaryColor;											// 0FE6-0FE7
	uint8_t m_nQuaternaryColor;											// 0FE7-0FE8
	uint8_t pad7[0xD8];													// 0FE8-10C0
	uint8_t m_nMaxPassengers;											// 10C0-10C1
	uint8_t pad8[0x7];													// 10C1-10C8
	float m_fGasPedal;													// 10C8-10CC
	float m_fBrakePedal;												// 10CC-10D0
	float m_fSteerDesired;												// 10D0-10D4
	float m_fSteerBias;													// 10D4-10D8
	float m_fSteerActual;												// 10D8-10DC
	uint8_t pad9[0x4];													// 10DC-10E0
	uint8_t m_nCurrentGear;												// 10E0-10E2
	uint8_t pad10[0x1A];												// 10E2-10FC
	float m_fEngineHealth;												// 10FC-1100
	uint8_t pad11[0x8];													// 1100-1108
	uint8_t m_nCreatedBy;												// 1108-1109
	uint8_t pad12[0xB];													// 1109-1118
	uint8_t m_nRespotTimer;												// 1114-1116
	uint8_t pad13[0x2];													// 1116-1118
	float m_fDirtLevel;													// 1118-111C
	uint8_t pad14[0xC];													// 111C-1128
	float m_fPetrolTankHealth;											// 1128-112C
	uint8_t pad15[0xB4];												// 112C-11E0
	uint8_t m_nLights[0xD];												// 11E0-11ED
	uint8_t pad16[0x3];													// 11ED-11F0
	uint8_t m_nSirens[0x8];												// 11F0-11F8
	uint8_t pad17[0x128];												// 11F8-1320
	uint32_t m_nDoorLock;												// 1320-1324
	uint8_t pad18[0x8];													// 1324-132C
	float m_fDeformationMult;											// 132C-1330
	float m_fLightMult;													// 1330-1334
	uint8_t pad19[0x8];													// 1334-133C
	uint32_t m_nHornCounter;											// 133C-1340
	uint8_t pad20[0x14];												// 1340-1354
	uint32_t m_nVehicleType;											// 1354-1358
	uint8_t pad21[0x16C];												// 1358-14C4
	struct
	{
		unsigned int pad : 3;
		unsigned int bNotDamagedUpsideDown : 1; // unused
		unsigned int pad2 : 28;
	} m_nAutomobileFlags;									// 14C4-14C8
	uint8_t pad22[0xA38];												// 14C8-1F00
	float m_fPlaneTurn;													// 1F00-1F04
	float m_fPlaneUpDown;												// 1F04-1F08
	float m_fPlaneRotate;												// 1F08-1F0C
	float m_fPlaneThrust;												// 1F0C-1F10
	uint8_t pad23[0x2C];												// 1F10-1F3C
	float m_fPlanePropSpeed;											// 1F3C-1F40
	uint8_t pad24[0x190];												// 1F40-20D0
	//0x260->0xB03 - gps voice (byte ptr, 0-4)

	void Fix()
	{
		((void(__thiscall*)(Native_CVehicle*))(*(void***)this)[101])(this);
	}
	void MakeDirty()
	{
		((void(__thiscall*)(Native_CVehicle*))(AddressSetter::Get(0x5D3E90, 0x4FE1E0)))(this);
	}
	void GetVehicleLightsStatus()
	{
		((void(__thiscall*)(Native_CVehicle*))(AddressSetter::Get(0x5C63D0, 0x4F0340)))(this);
	}

	// returns VehicleStruct part enum
	int GetSeatPartId(int seat)
	{
		return ((int(__cdecl*)(Native_CVehicle*, int))(AddressSetter::Get(0x5C6EF0, 0x4F0E60)))(this, seat);
	}
	// see eVehicleCameraType
	bool GetCameraType(int* type)
	{
		return ((bool(__stdcall*)(Native_CVehicle*, int*))(AddressSetter::Get(0x5D68F0, 0x679B50)))(this, type);
	}
	void ProcessRespot(float delta)
	{
		((void(__thiscall*)(Native_CVehicle*, float))(AddressSetter::Get(0x5D3A10, 0x4FDD60)))(this, delta);
	}
	void ProcessAirControl(void* unk)
	{
		((void(__thiscall*)(Native_CVehicle*, void*))(AddressSetter::Get(0x7FD450, 0x651580)))(this, unk);
	}

	static float HeightAboveCeiling(float height, int flightModel)
	{
		return ((float(__stdcall*)(float, int))(AddressSetter::Get(0x5C6100, 0x4F0070)))(height, flightModel);
	}
	static bool UsesSiren(int32_t id)
	{
		return ((bool(__cdecl*)(int32_t))(AddressSetter::Get(0x5C5F50, 0x4EFEC0)))(id);
	}
};
VALIDATE_SIZE(Native_CVehicle, 0x20D0);
VALIDATE_OFFSET(Native_CVehicle, m_fEngineRPM, 0x688);
VALIDATE_OFFSET(Native_CVehicle, m_nDoorLock, 0x1320);
VALIDATE_OFFSET(Native_CVehicle, m_nVehicleType, 0x1354);
VALIDATE_OFFSET(Native_CVehicle, m_fLightMult, 0x1330);
VALIDATE_OFFSET(Native_CVehicle, m_nHornCounter, 0x133C);
VALIDATE_OFFSET(Native_CVehicle, m_nVehicleFlags, 0xF64);
VALIDATE_OFFSET(Native_CVehicle, m_nVehicleFlags2, 0xF70);
VALIDATE_OFFSET(Native_CVehicle, m_nCreatedBy, 0x1108);
VALIDATE_OFFSET(Native_CVehicle, m_pVehicleFragInst, 0xE14);
VALIDATE_OFFSET(Native_CVehicle, m_nRespotTimer, 0x1114);
VALIDATE_OFFSET(Native_CVehicle, m_fDirtLevel, 0x1118);
VALIDATE_OFFSET(Native_CVehicle, m_fDeformationMult, 0x132C);
VALIDATE_OFFSET(Native_CVehicle, m_pDriver, 0xFA0);
VALIDATE_OFFSET(Native_CVehicle, m_nPrimaryColor, 0xFE4);
VALIDATE_OFFSET(Native_CVehicle, m_nMaxPassengers, 0x10C0);
VALIDATE_OFFSET(Native_CVehicle, m_fGasPedal, 0x10C8);
VALIDATE_OFFSET(Native_CVehicle, m_nCurrentGear, 0x10E0);
VALIDATE_OFFSET(Native_CVehicle, m_fPetrolTankHealth, 0x1128);
VALIDATE_OFFSET(Native_CVehicle, m_fEngineHealth, 0x10FC);
VALIDATE_OFFSET(Native_CVehicle, m_pHandling, 0xE18);
VALIDATE_OFFSET(Native_CVehicle, m_pDoors, 0xFD8);
VALIDATE_OFFSET(Native_CVehicle, m_nLights, 0x11E0);
VALIDATE_OFFSET(Native_CVehicle, m_nSirens, 0x11F0);
VALIDATE_OFFSET(Native_CVehicle, m_fPlaneTurn, 0x1F00);
VALIDATE_OFFSET(Native_CVehicle, m_fPlaneUpDown, 0x1F04);
VALIDATE_OFFSET(Native_CVehicle, m_fPlaneRotate, 0x1F08);
VALIDATE_OFFSET(Native_CVehicle, m_fPlaneThrust, 0x1F0C);
VALIDATE_OFFSET(Native_CVehicle, m_fPlanePropSpeed, 0x1F3C);
VALIDATE_OFFSET(Native_CVehicle, m_nAbsFlags, 0xFE0);

namespace IVSDKDotNet {

	public ref class CVehicleDoor
	{
	public:
		CVehicleDoor::CVehicleDoor(Native_CVehicleDoor* nativePtr);

		property uint32_t BoneID {
			public:
				uint32_t	get()				{ return m_cVehicleDoor->m_nBoneID; }
				void		set(uint32_t value) { m_cVehicleDoor->m_nBoneID = value; }
		}
		property uint8_t GroupID {
			public:
				uint8_t	get()				{ return m_cVehicleDoor->m_nGroupID; }
				void	set(uint8_t value)	{ m_cVehicleDoor->m_nGroupID = value; }
		}

	private:
		Native_CVehicleDoor* m_cVehicleDoor;
	};

	public ref class CVehicleWheel
	{
	public:
		CVehicleWheel::CVehicleWheel(Native_CVehicleWheel* nativePtr);

		property uint32_t BoneID {
			public:
				uint32_t	get()				{ return m_cVehicleWheel->m_nBoneID; }
				void		set(uint32_t value) { m_cVehicleWheel->m_nBoneID = value; }
		}
		property Vector3 Position {
			public:
				Vector3	get() {
					Native_CVector v = m_cVehicleWheel->m_vPosition;
					return Vector3(v.x, v.y, v.z);
				}
				void set(Vector3 value) { m_cVehicleWheel->m_vPosition = Native_CVector(value.X, value.Y, value.Z); }
		}

	private:
		Native_CVehicleWheel* m_cVehicleWheel;
	};

	public ref class CVehicle : CPhysical
	{
	public:
		ref class VehicleAbsFlags
		{
		public:
			VehicleAbsFlags(CVehicle^ parent);

			property bool Abs {
				public:
					bool get()				{ return m_cParent->VehiclePointer->m_nAbsFlags.bAbs; }
					void set(bool value)	{ m_cParent->VehiclePointer->m_nAbsFlags.bAbs = value; }
			}

			property bool AbsAlt {
				public:
					bool get()				{ return m_cParent->VehiclePointer->m_nAbsFlags.bAbsAlt; }
					void set(bool value)	{ m_cParent->VehiclePointer->m_nAbsFlags.bAbsAlt = value; }
			}

		private:
			CVehicle^ m_cParent;
		};

		ref class VehicleFlags
		{
		public:
			VehicleFlags(CVehicle^ parent);

			property bool EngineOn {
				public:
					bool get()				{ return m_cParent->VehiclePointer->m_nVehicleFlags.bEngineOn; }
					void set(bool value)	{ m_cParent->VehiclePointer->m_nVehicleFlags.bEngineOn = value; }
			}

			property bool EngineStarting {
				public:
					bool get()				{ return m_cParent->VehiclePointer->m_nVehicleFlags.bEngineStarting; }
					void set(bool value)	{ m_cParent->VehiclePointer->m_nVehicleFlags.bEngineStarting = value; }
			}

			property bool IsHandbrakeOn {
				public:
					bool get()				{ return m_cParent->VehiclePointer->m_nVehicleFlags.bIsHandbrakeOn; }
					void set(bool value)	{ m_cParent->VehiclePointer->m_nVehicleFlags.bIsHandbrakeOn = value; }
			}

			property bool CanBeVisiblyDamaged {
				public:
					bool get()				{ return m_cParent->VehiclePointer->m_nVehicleFlags2.bCanBeVisiblyDamaged; }
					void set(bool value)	{ m_cParent->VehiclePointer->m_nVehicleFlags2.bCanBeVisiblyDamaged = value; }
			}

			/// <summary>
			/// Apparently unused.
			/// </summary>
			property bool NotDamagedUpsideDown {
				public:
					bool get()				{ return m_cParent->VehiclePointer->m_nAutomobileFlags.bNotDamagedUpsideDown; }
					void set(bool value)	{ m_cParent->VehiclePointer->m_nAutomobileFlags.bNotDamagedUpsideDown = value; }
			}

		private:
			CVehicle^ m_cParent;
		};

	public:
		CVehicle(Native_CVehicle* nativePtr);

		static CVehicle^ FromPointer(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		property uint8_t PrimaryColor2 {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nPrimaryColor2; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nPrimaryColor2 = value; }
		}
		property uint8_t SecondaryColor2 {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nSecondaryColor2; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nSecondaryColor2 = value; }
		}
		property uint8_t TertiaryColor2 {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nTertiaryColor2; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nTertiaryColor2 = value; }
		}
		property uint8_t QuaternaryColor2 {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nQuaternaryColor2; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nQuaternaryColor2 = value; }
		}

		property float EngineRPM {
			public:
				float	get()				{ return m_cNativeVehicle->m_fEngineRPM; }
				void	set(float value)	{ m_cNativeVehicle->m_fEngineRPM = value; }
		}

		/// <summary>
		/// Use with phInstGta.FromPointer
		/// </summary>
		property UIntPtr VehicleFragInst {
			public:
				UIntPtr get()
				{
					Native_phInstGta* ptr = m_cNativeVehicle->m_pVehicleFragInst;

					if (ptr)
						return UIntPtr(ptr);

					return UIntPtr::Zero;
				}
		}

		property UIntPtr Handling {
			public:
				UIntPtr get()
				{
					Native_tHandlingData* ptr = m_cNativeVehicle->m_pHandling;

					if (ptr)
						return UIntPtr(ptr);

					return UIntPtr::Zero;
				}
				void set(UIntPtr value)
				{
					if (value == UIntPtr::Zero)
						return;

					m_cNativeVehicle->m_pHandling = (Native_tHandlingData*)value.ToPointer();
				}
		}

		property VehicleFlags^ TheVehicleFlags {
			public: VehicleFlags^ get() { return m_cVehicleFlags; }
		}

		property UIntPtr Driver {
			public:
				UIntPtr get()				{ return UIntPtr((uint32_t*)m_cNativeVehicle->m_pDriver); }
				void	set(UIntPtr value)	{ m_cNativeVehicle->m_pDriver = (Native_CPed*)value.ToPointer(); }
		}

		property array<UIntPtr>^ Passengers {
			public:
				array<UIntPtr>^ get()
				{

					// Copy unmanaged array into managed array
					array<IntPtr>^ arr = gcnew array<IntPtr>(8);
					Marshal::Copy(IntPtr(VehiclePointer->m_pPassengers), arr, 0, 8);

					// Convert intptr's of array 1 to uintptr's for final array
					array<UIntPtr>^ finalArr = gcnew array<UIntPtr>(8);
					for (int i = 0; i < finalArr->Length; i++)
					{
						finalArr[i] = UIntPtr(arr[i].ToPointer());
					}

					return finalArr;

				}
				void set(array<UIntPtr>^ value)
				{
					for (int i = 0; i < 8; i++)
					{
						VehiclePointer->m_pPassengers[i] = (Native_CPed*)value[i].ToPointer();
					}
				}
		}

		property CVehicleDoor^ Doors {
			public:
				CVehicleDoor^	get() { return gcnew CVehicleDoor(m_cNativeVehicle->m_pDoors); }
				void set(CVehicleDoor^ value) 
				{
					Native_CVehicleDoor* n = new Native_CVehicleDoor();
					n->m_nBoneID = value->BoneID;
					n->m_nGroupID = value->GroupID;
					m_cNativeVehicle->m_pDoors = n;
					delete n;
				}
		}
		property uint32_t DoorCount {
			public:
				uint32_t	get()				{ return m_cNativeVehicle->m_nDoorCount; }
				void		set(uint32_t value) { m_cNativeVehicle->m_nDoorCount = value; }
		}

		property VehicleAbsFlags^ TheVehicleAbsFlags {
			public: VehicleAbsFlags^ get() { return m_cVehicleAbsFlags; }
		}

		property CVehicleWheel^ Wheels {
			public:
				CVehicleWheel^	get() { return gcnew CVehicleWheel(m_cNativeVehicle->m_pWheels); }
				void set(CVehicleWheel^ value) 
				{
					Native_CVehicleWheel* n = new Native_CVehicleWheel();
					n->m_nBoneID = value->BoneID;
					n->m_vPosition = Native_CVector(value->Position.X, value->Position.Y, value->Position.Z);
					m_cNativeVehicle->m_pWheels = n;
					delete n;
				}
		}
		property uint32_t WheelCount {
			public:
				uint32_t	get()				{ return m_cNativeVehicle->m_nWheelCount; }
				void		set(uint32_t value) { m_cNativeVehicle->m_nWheelCount = value; }
		}

		property uint8_t PrimaryColor {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nPrimaryColor; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nPrimaryColor = value; }
		}
		property uint8_t SecondaryColor {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nSecondaryColor; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nSecondaryColor = value; }
		}
		property uint8_t TertiaryColor {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nTertiaryColor; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nTertiaryColor = value; }
		}
		property uint8_t QuaternaryColor {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nQuaternaryColor; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nQuaternaryColor = value; }
		}

		property uint8_t MaxPassengers {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nMaxPassengers; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nMaxPassengers = value; }
		}

		property float GasPedal {
			public:
				float	get()				{ return m_cNativeVehicle->m_fGasPedal; }
				void	set(float value)	{ m_cNativeVehicle->m_fGasPedal = value; }
		}
		property float BrakePedal {
			public:
				float	get()				{ return m_cNativeVehicle->m_fBrakePedal; }
				void	set(float value)	{ m_cNativeVehicle->m_fBrakePedal = value; }
		}
		property float SteerDesired {
			public:
				float	get()				{ return m_cNativeVehicle->m_fSteerDesired; }
				void	set(float value)	{ m_cNativeVehicle->m_fSteerDesired = value; }
		}
		property float SteerBias {
			public:
				float	get()				{ return m_cNativeVehicle->m_fSteerBias; }
				void	set(float value)	{ m_cNativeVehicle->m_fSteerBias = value; }
		}
		property float SteerActual {
			public:
				float	get()				{ return m_cNativeVehicle->m_fSteerActual; }
				void	set(float value)	{ m_cNativeVehicle->m_fSteerActual = value; }
		}

		property uint8_t CurrentGear {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nCurrentGear; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nCurrentGear = value; }
		}

		property float EngineHealth {
			public:
				float	get()				{ return m_cNativeVehicle->m_fEngineHealth; }
				void	set(float value)	{ m_cNativeVehicle->m_fEngineHealth = value; }
		}

		property uint8_t CreatedBy {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nCreatedBy; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nCreatedBy = value; }
		}
		property uint8_t RespotTimer {
			public:
				uint8_t	get()				{ return m_cNativeVehicle->m_nRespotTimer; }
				void	set(uint8_t value)	{ m_cNativeVehicle->m_nRespotTimer = value; }
		}

		property float DirtLevel {
			public:
				float	get()				{ return m_cNativeVehicle->m_fDirtLevel; }
				void	set(float value)	{ m_cNativeVehicle->m_fDirtLevel = value; }
		}
		property float PetrolTankHealth {
			public:
				float	get()				{ return m_cNativeVehicle->m_fPetrolTankHealth; }
				void	set(float value)	{ m_cNativeVehicle->m_fPetrolTankHealth = value; }
		}

		/// <summary>
		/// Array of all vehicle lights. "1" seems to be when a light is broken and "0" when it's working.
		/// </summary>
		property array<Byte>^ Lights {
			public:
				array<Byte>^ get()
				{ 
					int arrLenght = sizeof(m_cNativeVehicle->m_nLights);
					array<Byte>^ arr = gcnew array<Byte>(arrLenght);
					Marshal::Copy((IntPtr)m_cNativeVehicle->m_nLights, arr, 0, arrLenght);

					return arr;
				}
				void set(array<Byte>^ value)
				{
					for (int i = 0; i < value->Length; i++) {
						m_cNativeVehicle->m_nLights[i] = value[i];
					}
				}
		}

		property array<Byte>^ Sirens {
			public:
				array<Byte>^ get()
				{
					int arrLenght = sizeof(m_cNativeVehicle->m_nSirens);
					array<Byte>^ arr = gcnew array<Byte>(arrLenght);
					Marshal::Copy((IntPtr)m_cNativeVehicle->m_nSirens, arr, 0, arrLenght);
					
					return arr;
				}
				void set(array<Byte>^ value)
				{
					for (int i = 0; i < value->Length; i++) {
						m_cNativeVehicle->m_nSirens[i] = value[i];
					}
				}
		}

		property uint32_t DoorLock {
			public:
				uint32_t	get()				{ return m_cNativeVehicle->m_nDoorLock; }
				void		set(uint32_t value)	{ m_cNativeVehicle->m_nDoorLock = value; }
		}

		property float DeformationMult {
			public:
				float	get()				{ return m_cNativeVehicle->m_fDeformationMult; }
				void	set(float value)	{ m_cNativeVehicle->m_fDeformationMult = value; }
		}
		property float LightMult {
			public:
				float	get()				{ return m_cNativeVehicle->m_fLightMult; }
				void	set(float value)	{ m_cNativeVehicle->m_fLightMult = value; }
		}

		property uint32_t HornCounter {
			public:
				uint32_t	get()				{ return m_cNativeVehicle->m_nHornCounter; }
				void		set(uint32_t value)	{ m_cNativeVehicle->m_nHornCounter = value; }
		}
		property uint32_t VehicleType {
			public:
				uint32_t	get()				{ return m_cNativeVehicle->m_nVehicleType; }
				void		set(uint32_t value)	{ m_cNativeVehicle->m_nVehicleType = value; }
		}

		property float PlaneTurn {
			public:
				float	get()				{ return m_cNativeVehicle->m_fPlaneTurn; }
				void	set(float value)	{ m_cNativeVehicle->m_fPlaneTurn = value; }
		}
		property float PlaneUpDown {
			public:
				float	get()				{ return m_cNativeVehicle->m_fPlaneUpDown; }
				void	set(float value)	{ m_cNativeVehicle->m_fPlaneUpDown = value; }
		}
		property float PlaneRotate {
			public:
				float	get()				{ return m_cNativeVehicle->m_fPlaneRotate; }
				void	set(float value)	{ m_cNativeVehicle->m_fPlaneRotate = value; }
		}
		property float PlaneThrust {
			public:
				float	get()				{ return m_cNativeVehicle->m_fPlaneThrust; }
				void	set(float value)	{ m_cNativeVehicle->m_fPlaneThrust = value; }
		}
		property float PlanePropSpeed {
			public:		
				float	get()				{ return m_cNativeVehicle->m_fPlanePropSpeed; }
				void	set(float value)	{ m_cNativeVehicle->m_fPlanePropSpeed = value; }
		}

		property Native_CVehicle* VehiclePointer {
			public:
				Native_CVehicle*	get()						{ return m_cNativeVehicle; }
				void				set(Native_CVehicle* value) { m_cNativeVehicle = value; }
		}

		static float HeightAboveCeiling(float height, int flightModel);
		static bool UsesSiren(int32_t id);

		void Fix();
		void MakeDirty();
		void GetVehicleLightsStatus();
		void ProcessRespot(float delta);
		void ProcessAirControl(IntPtr unk);

		int GetSeatPartId(int seat);
		bool GetCameraType([OutAttribute] eVehicleCameraType% type);

	private:
		Native_CVehicle* m_cNativeVehicle;
		VehicleFlags^ m_cVehicleFlags;
		VehicleAbsFlags^ m_cVehicleAbsFlags;
	};

}