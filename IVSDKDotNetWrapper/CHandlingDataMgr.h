#pragma once

struct Native_tHandlingData
{
	char m_sName[16];											// 000-010
	float m_fMass;												// 010-014
	float m_fDragMult;											// 014-018
	uint8_t pad[0x8];											// 018-020 always 0
	Native_CVector_pad m_vCenterOfMass;							// 020-02C
	uint32_t m_nPercentSubmerged;								// 030-034
	float m_fPercentSubmerged;									// 034-038 100.0 / m_nPercentSubmerged
	float m_fDriveBiasF;										// 038-03C
	float m_fDriveBiasR;										// 03C-040
	uint32_t m_nDriveGears;										// 040-044
	float m_fDriveForce;										// 044-048
	float m_fDriveInertia;										// 048-04C
	float m_fV_times12;											// 04C-050 m_fV * 1.2
	float m_fV;													// 050-054
	float m_fV_gearR;											// 054-058
	float m_fV_gear1;											// 058-05C
	float m_fV_gear2;											// 05C-060
	float m_fV_gear3;											// 060-064
	float m_fV_gear4;											// 064-068
	float m_fV_gear5;											// 068-06C
	float m_fV_gear6;											// 06C-070
	float m_fV_gear7;											// 070-074
	float m_fBrakeForce;										// 074-078
	float m_fBrakeForceF;										// 078-07C
	float m_fBrakeForceR;										// 07C-080
	float m_fHBias;												// 080-084
	float m_fSteeringLock;										// 084-088
	float m_fSteeringLockPercent;								// 088-08C 1.0 / m_fSteeringLock
	float m_fTractionCurveMax;									// 08C-090
	float m_fTractionCurveMaxPercent;							// 090-094 1.0 / m_fTractionCurveMaxPercent
	float m_fTractionCurveMin;									// 094-098
	float m_fTractionCurvePercent;								// 098-09C
	float m_fTractionCurveLateral;								// 09C-0A0
	float m_fTractionCurveLateralPercent;						// 0A0-0A4 1.0 / m_fTractionCurveLateral
	float m_fTractionSpringDeltaMax;							// 0A4-0A8
	float m_fTractionSpringDeltaMaxPercent;						// 0A8-0AC 1.0 / m_fTractionSpringDeltaMax
	float m_fTractionBiasF;										// 0AC-0B0
	float m_fTractionBiasR;										// 0B0-0B4
	float m_fSuspensionForce;									// 0B4-0B8
	float m_fSuspensionCompDamp;								// 0B8-0BC
	float m_fSuspensionReboundDamp;								// 0BC-0C0
	float m_fSuspensionUpperLimit;								// 0C0-0C4
	float m_fSuspensionLowerLimit;								// 0C4-0C8
	float m_fSuspensionRaise;									// 0C8-0CC
	float m_fSuspensionBiasF;									// 0CC-0D0
	float m_fSuspensionBiasR;									// 0D0-0D4
	float m_fCollisionDamageMult;								// 0D4-0D8
	float m_fWeaponDamageMult;									// 0D8-0DC
	float m_fDeformationDamageMult;								// 0DC-0E0
	float m_fEngineDamageMult;									// 0E0-0E4
	float m_fSeatOffsetDist;									// 0E4-0E8
	uint32_t m_nMonetaryValue;									// 0E8-0EC
	struct
	{
		unsigned int bIsVan : 1;
		unsigned int bIsBus : 1;
		unsigned int bIsLow : 1;
		unsigned int bIsBig : 1;
		unsigned int bAbsStd : 1;
		unsigned int bAbsOption : 1;
		unsigned int bAbsAltStd : 1;
		unsigned int bAbsAltOption : 1;
		unsigned int bNoDoors : 1;
		unsigned int bTandemSeats : 1;
		unsigned int bSitInBoat : 1;
		unsigned int bNone : 1;
		unsigned int bNoExhaust : 1;
		unsigned int bDoubleExhaust : 1;
		unsigned int bNo1fpsLookBehind : 1;
		unsigned int bCanEnterIfNoDoor : 1;
		unsigned int bAxleFNotilt : 1;
		unsigned int bAxleFSolid : 1;
		unsigned int bAxleFMcpherson : 1;
		unsigned int bAxleFReverse : 1;
		unsigned int bAxleRNotilt : 1;
		unsigned int bAxleRSolid : 1;
		unsigned int bAxleRMcpherson : 1;
		unsigned int bAxleRReverse : 1;
		unsigned int bIsBike : 1;
		unsigned int bIsHeli : 1;
		unsigned int bIsPlane : 1;
		unsigned int bIsBoat : 1;
		unsigned int bBouncePanels : 1;
		unsigned int bDoubleRWheels : 1;
		unsigned int bForceGroundClearance : 1;
		unsigned int bIsHatchback : 1;
	} m_nModelFlags;											// 0EC-0F0
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
	} m_nHandlingFlags;											// 0F0-0F4
	uint8_t pad2[0x1C];											// 0F4-110
};
VALIDATE_SIZE(Native_tHandlingData, 0x110);
VALIDATE_OFFSET(Native_tHandlingData, m_fMass, 0x10);
VALIDATE_OFFSET(Native_tHandlingData, m_fDragMult, 0x14);
VALIDATE_OFFSET(Native_tHandlingData, m_vCenterOfMass, 0x20);
VALIDATE_OFFSET(Native_tHandlingData, m_nPercentSubmerged, 0x30);
VALIDATE_OFFSET(Native_tHandlingData, m_nDriveGears, 0x40);
VALIDATE_OFFSET(Native_tHandlingData, m_fDriveForce, 0x44);
VALIDATE_OFFSET(Native_tHandlingData, m_fBrakeForce, 0x74);
VALIDATE_OFFSET(Native_tHandlingData, m_fTractionCurveMax, 0x8C);
VALIDATE_OFFSET(Native_tHandlingData, m_fTractionCurveMin, 0x94);
VALIDATE_OFFSET(Native_tHandlingData, m_fSuspensionForce, 0xB4);
VALIDATE_OFFSET(Native_tHandlingData, m_fSuspensionCompDamp, 0xB8);
VALIDATE_OFFSET(Native_tHandlingData, m_fSuspensionReboundDamp, 0xBC);
VALIDATE_OFFSET(Native_tHandlingData, m_fSuspensionUpperLimit, 0xC0);
VALIDATE_OFFSET(Native_tHandlingData, m_fSuspensionLowerLimit, 0xC4);
VALIDATE_OFFSET(Native_tHandlingData, m_fSuspensionRaise, 0xC8);
VALIDATE_OFFSET(Native_tHandlingData, m_fCollisionDamageMult, 0xD4);
VALIDATE_OFFSET(Native_tHandlingData, m_fWeaponDamageMult, 0xD8);
VALIDATE_OFFSET(Native_tHandlingData, m_fDeformationDamageMult, 0xDC);
VALIDATE_OFFSET(Native_tHandlingData, m_fEngineDamageMult, 0xE0);
VALIDATE_OFFSET(Native_tHandlingData, m_fSeatOffsetDist, 0xE4);
VALIDATE_OFFSET(Native_tHandlingData, m_nMonetaryValue, 0xE8);
VALIDATE_OFFSET(Native_tHandlingData, m_nModelFlags, 0xEC);
VALIDATE_OFFSET(Native_tHandlingData, m_nHandlingFlags, 0xF0);

class Native_CHandlingDataMgr
{
public:
	static inline Native_tHandlingData* HandlingData = (Native_tHandlingData*)AddressSetter::Get(0x11E3BF0, 0x12773B0); // HandlingData[160]

	static void Initialise()
	{
		((void(__cdecl*)())(AddressSetter::Get(0x571FC0, 0x7A2C10)))();
	}
	static void LoadHandlingData(char* sPath)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get(0x571D60, 0x7A29B0)))(sPath);
	}
	static Native_tHandlingData* GetHandlingData(int id)
	{
		return ((Native_tHandlingData* (__cdecl*)(int))(AddressSetter::Get(0x5719C0, 0x7A2610)))(id);
	}
	static int GetHandlingId(char* handlingName)
	{
		return ((int(__cdecl*)(char*))(AddressSetter::Get(0x571BF0, 0x7A2840)))(handlingName);
	}
};

namespace IVSDKDotNet {

	public ref class tHandlingData
	{
	public:
		ref class ModelFlags
		{
		public:
			ModelFlags(tHandlingData^ parent);

			property bool IsVan {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsVan; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsVan = value; }
			}

			property bool IsBus {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsBus; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsBus = value; }
			}

			property bool IsLow {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsLow; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsLow = value; }
			}

			property bool IsBig {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsBig; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsBig = value; }
			}

			property bool AbsStd {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAbsStd; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAbsStd = value; }
			}

			property bool AbsOption {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAbsOption; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAbsOption = value; }
			}

			property bool AbsAltStd {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAbsAltStd; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAbsAltStd = value; }
			}

			property bool AbsAltOption {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAbsAltOption; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAbsAltOption = value; }
			}

			property bool NoDoors {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bNoDoors; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bNoDoors = value; }
			}

			property bool TandemSeats {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bTandemSeats; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bTandemSeats = value; }
			}

			property bool SitInBoat {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bSitInBoat; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bSitInBoat = value; }
			}

			property bool None {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bNone; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bNone = value; }
			}

			property bool NoExhaust {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bNoExhaust; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bNoExhaust = value; }
			}

			property bool DoubleExhaust {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bDoubleExhaust; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bDoubleExhaust = value; }
			}

			property bool No1fpsLookBehind {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bNo1fpsLookBehind; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bNo1fpsLookBehind = value; }
			}

			property bool CanEnterIfNoDoor {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bCanEnterIfNoDoor; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bCanEnterIfNoDoor = value; }
			}

			property bool AxleFNotilt {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleFNotilt; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleFNotilt = value; }
			}

			property bool AxleFSolid {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleFSolid; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleFSolid = value; }
			}

			property bool AxleFMcpherson {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleFMcpherson; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleFMcpherson = value; }
			}

			property bool AxleFReverse {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleFReverse; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleFReverse = value; }
			}

			property bool AxleRNotilt {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleRNotilt; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleRNotilt = value; }
			}

			property bool AxleRSolid {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleRSolid; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleRSolid = value; }
			}

			property bool AxleRMcpherson {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleRMcpherson; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleRMcpherson = value; }
			}

			property bool AxleRReverse {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleRReverse; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bAxleRReverse = value; }
			}

			property bool IsBike {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsBike; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsBike = value; }
			}

			property bool IsHeli {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsHeli; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsHeli = value; }
			}

			property bool IsPlane {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsPlane; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsPlane = value; }
			}

			property bool IsBoat {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsBoat; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsBoat = value; }
			}

			property bool BouncePanels {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bBouncePanels; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bBouncePanels = value; }
			}

			property bool DoubleRWheels {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bDoubleRWheels; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bDoubleRWheels = value; }
			}

			property bool ForceGroundClearance {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bForceGroundClearance; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bForceGroundClearance = value; }
			}

			property bool IsHatchback {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsHatchback; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nModelFlags.bIsHatchback = value; }
			}

		private:
			tHandlingData^ m_cParent;
		};

		ref class HandlingFlags
		{
		public:
			HandlingFlags(tHandlingData^ parent);

			property bool SmoothCompresn {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bSmoothCompresn; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bSmoothCompresn = value; }
			}

			property bool None {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNone; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNone = value; }
			}

			property bool NpcAntiRoll {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNpcAntiRoll; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNpcAntiRoll = value; }
			}

			property bool NpcNeutralHandl {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNpcNeutralHandl; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNpcNeutralHandl = value; }
			}

			property bool NoHandbrake {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNoHandbrake; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNoHandbrake = value; }
			}

			property bool SteerRearwheels {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bSteerRearwheels; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bSteerRearwheels = value; }
			}

			property bool HbRearwheelSteer {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bHbRearwheelSteer; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bHbRearwheelSteer = value; }
			}

			property bool AltSteerOpt {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bAltSteerOpt; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bAltSteerOpt = value; }
			}

			property bool WheelFNarrow2 {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelFNarrow2; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelFNarrow2 = value; }
			}

			property bool WheelFNarrow {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelFNarrow; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelFNarrow = value; }
			}

			property bool WheelFWide {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelFWide; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelFWide = value; }
			}

			property bool WheelFWide2 {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelFWide2; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelFWide2 = value; }
			}

			property bool WheelRNarrow2 {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelRNarrow2; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelRNarrow2 = value; }
			}

			property bool WheelRNarrow {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelRNarrow; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelRNarrow = value; }
			}

			property bool WheelRWide {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelRWide; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelRWide = value; }
			}

			property bool WheelRWide2 {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelRWide2; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bWheelRWide2 = value; }
			}

			property bool HydraulicGeom {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bHydraulicGeom; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bHydraulicGeom = value; }
			}

			property bool HydraulicInst {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bHydraulicInst; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bHydraulicInst = value; }
			}

			property bool HydraulicNone {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bHydraulicNone; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bHydraulicNone = value; }
			}

			property bool NosInst {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNosInst; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNosInst = value; }
			}

			property bool OffroadAbility {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bOffroadAbility; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bOffroadAbility = value; }
			}

			property bool OffroadAbility2 {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bOffroadAbility2; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bOffroadAbility2 = value; }
			}

			property bool HalogenLights {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bHalogenLights; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bHalogenLights = value; }
			}

			property bool ProcRearwheel1st {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bProcRearwheel1st; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bProcRearwheel1st = value; }
			}

			property bool UseMaxspLimit {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bUseMaxspLimit; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bUseMaxspLimit = value; }
			}

			property bool LowRider {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bLowRider; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bLowRider = value; }
			}

			property bool StreetRacer {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bStreetRacer; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bStreetRacer = value; }
			}

			property bool None2 {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNone2; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNone2 = value; }
			}

			property bool SwingingChassis {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bSwingingChassis; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bSwingingChassis = value; }
			}

			property bool OldPhysics {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bOldPhysics; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bOldPhysics = value; }
			}

			property bool None3 {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNone3; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNone3 = value; }
			}

			property bool None4 {
				public:
					bool get()				{ return m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNone4; }
					void set(bool value)	{ m_cParent->m_cNativeHandlingData->m_nHandlingFlags.bNone4 = value; }
			}

		private:
			tHandlingData^ m_cParent;
		};

	public:
		tHandlingData(Native_tHandlingData* nativePtr);

		static tHandlingData^ FromPointer(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		property String^ Name {
			public: String^ get() { return gcnew String(m_cNativeHandlingData->m_sName); }
		}

		property float Mass {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fMass; }
				void	set(float value)	{ m_cNativeHandlingData->m_fMass = value; }
		}

		property float DragMult {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fDragMult; }
				void	set(float value)	{ m_cNativeHandlingData->m_fDragMult = value; }
		}

		property Vector3 CenterOfMass {
			public:
				Vector3 get()
				{
					Native_CVector_pad pad = m_cNativeHandlingData->m_vCenterOfMass;
					return Vector3(pad.x, pad.y, pad.z);
				}
				void set(Vector3 value)
				{
					Native_CVector_pad pad = m_cNativeHandlingData->m_vCenterOfMass;
					m_cNativeHandlingData->m_vCenterOfMass = Native_CVector_pad(pad.flags, value.X, value.Y, value.Z);
				}
		}

		property uint32_t PercentSubmerged {
			public:
				uint32_t	get()				{ return m_cNativeHandlingData->m_nPercentSubmerged; }
				void		set(uint32_t value) { m_cNativeHandlingData->m_nPercentSubmerged = value; }
		}

		property float FloatPercentSubmerged {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fPercentSubmerged; }
				void	set(float value)	{ m_cNativeHandlingData->m_fPercentSubmerged = value; }
		}

		property float DriveBiasF {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fDriveBiasF; }
				void	set(float value)	{ m_cNativeHandlingData->m_fDriveBiasF = value; }
		}

		property float DriveBiasR {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fDriveBiasR; }
				void	set(float value)	{ m_cNativeHandlingData->m_fDriveBiasR = value; }
		}

		property uint32_t DriveGears {
			public:
				uint32_t	get()				{ return m_cNativeHandlingData->m_nDriveGears; }
				void		set(uint32_t value)	{ m_cNativeHandlingData->m_nDriveGears = value; }
		}

		property float DriveForce {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fDriveForce; }
				void	set(float value)	{ m_cNativeHandlingData->m_fDriveForce = value; }
		}

		property float DriveInertia {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fDriveInertia; }
				void	set(float value)	{ m_cNativeHandlingData->m_fDriveInertia = value; }
		}

		property float V_times12 {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fV_times12; }
				void	set(float value)	{ m_cNativeHandlingData->m_fV_times12 = value; }
		}

		property float V {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fV; }
				void	set(float value)	{ m_cNativeHandlingData->m_fV = value; }
		}

		property float V_gearR {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fV_gearR; }
				void	set(float value)	{ m_cNativeHandlingData->m_fV_gearR = value; }
		}

		property float V_gear1 {
			public:
				float get() { return m_cNativeHandlingData->m_fV_gear1; }
				void set(float value) { m_cNativeHandlingData->m_fV_gear1 = value; }
		}

		property float V_gear2 {
			public:
				float get() { return m_cNativeHandlingData->m_fV_gear2; }
				void set(float value) { m_cNativeHandlingData->m_fV_gear2 = value; }
		}

		property float V_gear3 {
			public:
				float get() { return m_cNativeHandlingData->m_fV_gear3; }
				void set(float value) { m_cNativeHandlingData->m_fV_gear3 = value; }
		}

		property float V_gear4 {
			public:
				float get() { return m_cNativeHandlingData->m_fV_gear4; }
				void set(float value) { m_cNativeHandlingData->m_fV_gear4 = value; }
		}

		property float V_gear5 {
			public:
				float get() { return m_cNativeHandlingData->m_fV_gear5; }
				void set(float value) { m_cNativeHandlingData->m_fV_gear5 = value; }
		}

		property float V_gear6 {
			public:
				float get() { return m_cNativeHandlingData->m_fV_gear6; }
				void set(float value) { m_cNativeHandlingData->m_fV_gear6 = value; }
		}

		property float V_gear7 {
			public:
				float get() { return m_cNativeHandlingData->m_fV_gear7; }
				void set(float value) { m_cNativeHandlingData->m_fV_gear7 = value; }
		}

		property float BrakeForce {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fBrakeForce; }
				void	set(float value)	{ m_cNativeHandlingData->m_fBrakeForce = value; }
		}

		property float BrakeForceF {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fBrakeForceF; }
				void	set(float value)	{ m_cNativeHandlingData->m_fBrakeForceF = value; }
		}

		property float BrakeForceR {
			public:
				float		get()				{ return m_cNativeHandlingData->m_fBrakeForceR; }
				void		set(float value)	{ m_cNativeHandlingData->m_fBrakeForceR = value; }
		}

		property float HBias {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fHBias; }
				void	set(float value)	{ m_cNativeHandlingData->m_fHBias = value; }
		}

		property float SteeringLock {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fSteeringLock; }
				void	set(float value)	{ m_cNativeHandlingData->m_fSteeringLock = value; }
		}

		property float SteeringLockPercent {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fSteeringLockPercent; }
				void	set(float value)	{ m_cNativeHandlingData->m_fSteeringLockPercent = value; }
		}

		property float TractionCurveMax {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fTractionCurveMax; }
				void	set(float value)	{ m_cNativeHandlingData->m_fTractionCurveMax = value; }
		}

		property float TractionCurveMaxPercent {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fTractionCurveMaxPercent; }
				void	set(float value)	{ m_cNativeHandlingData->m_fTractionCurveMaxPercent = value; }
		}

		property float TractionCurveMin {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fTractionCurveMin; }
				void	set(float value)	{ m_cNativeHandlingData->m_fTractionCurveMin = value; }
		}

		property float TractionCurvePercent {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fTractionCurvePercent; }
				void	set(float value)	{ m_cNativeHandlingData->m_fTractionCurvePercent = value; }
		}

		property float TractionCurveLateral {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fTractionCurveLateral; }
				void	set(float value)	{ m_cNativeHandlingData->m_fTractionCurveLateral = value; }
		}

		property float TractionCurveLateralPercent {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fTractionCurveLateralPercent; }
				void	set(float value)	{ m_cNativeHandlingData->m_fTractionCurveLateralPercent = value; }
		}

		property float TractionSpringDeltaMax {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fTractionSpringDeltaMax; }
				void	set(float value)	{ m_cNativeHandlingData->m_fTractionSpringDeltaMax = value; }
		}

		property float TractionSpringDeltaMaxPercent {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fTractionSpringDeltaMaxPercent; }
				void	set(float value)	{ m_cNativeHandlingData->m_fTractionSpringDeltaMaxPercent = value; }
		}

		property float TractionBiasF {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fTractionBiasF; }
				void	set(float value)	{ m_cNativeHandlingData->m_fTractionBiasF = value; }
		}

		property float TractionBiasR {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fTractionBiasR; }
				void	set(float value)	{ m_cNativeHandlingData->m_fTractionBiasR = value; }
		}

		property float SuspensionForce {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fSuspensionForce; }
				void	set(float value)	{ m_cNativeHandlingData->m_fSuspensionForce = value; }
		}

		property float SuspensionCompDamp {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fSuspensionCompDamp; }
				void	set(float value)	{ m_cNativeHandlingData->m_fSuspensionCompDamp = value; }
		}

		property float SuspensionReboundDamp {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fSuspensionReboundDamp; }
				void	set(float value)	{ m_cNativeHandlingData->m_fSuspensionReboundDamp = value; }
		}

		property float SuspensionUpperLimit {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fSuspensionUpperLimit; }
				void	set(float value)	{ m_cNativeHandlingData->m_fSuspensionUpperLimit = value; }
		}

		property float SuspensionLowerLimit {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fSuspensionLowerLimit; }
				void	set(float value)	{ m_cNativeHandlingData->m_fSuspensionLowerLimit = value; }
		}

		property float SuspensionRaise {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fSuspensionRaise; }
				void	set(float value)	{ m_cNativeHandlingData->m_fSuspensionRaise = value; }
		}

		property float SuspensionBiasF {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fSuspensionBiasF; }
				void	set(float value)	{ m_cNativeHandlingData->m_fSuspensionBiasF = value; }
		}

		property float SuspensionBiasR {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fSuspensionBiasR; }
				void	set(float value)	{ m_cNativeHandlingData->m_fSuspensionBiasR = value; }
		}

		property float CollisionDamageMult {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fCollisionDamageMult; }
				void	set(float value)	{ m_cNativeHandlingData->m_fCollisionDamageMult = value; }
		}

		property float WeaponDamageMult {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fWeaponDamageMult; }
				void	set(float value)	{ m_cNativeHandlingData->m_fWeaponDamageMult = value; }
		}

		property float DeformationDamageMult {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fDeformationDamageMult; }
				void	set(float value)	{ m_cNativeHandlingData->m_fDeformationDamageMult = value; }
		}

		property float EngineDamageMult {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fEngineDamageMult; }
				void	set(float value)	{ m_cNativeHandlingData->m_fEngineDamageMult = value; }
		}

		property float SeatOffsetDist {
			public:
				float	get()				{ return m_cNativeHandlingData->m_fSeatOffsetDist; }
				void	set(float value)	{ m_cNativeHandlingData->m_fSeatOffsetDist = value; }
		}

		property uint32_t MonetaryValue {
			public:
				uint32_t	get()				{ return m_cNativeHandlingData->m_nMonetaryValue; }
				void		set(uint32_t value) { m_cNativeHandlingData->m_nMonetaryValue = value; }
		}

		property ModelFlags^ TheModelFlags {
			public:		ModelFlags^ get()					{ return m_cModelFlags; }
			private:	void		set(ModelFlags^ value)	{ m_cModelFlags = value; }
		}

		property HandlingFlags^ TheHandlingFlags {
			public:		HandlingFlags^	get()						{ return m_cHandlingFlags; }
			private:	void			set(HandlingFlags^ value)	{ m_cHandlingFlags = value; }
		}

		property Native_tHandlingData* HandlingDataPointer {
			public:
				Native_tHandlingData*	get()								{ return m_cNativeHandlingData; }
				void					set(Native_tHandlingData* value)	{ m_cNativeHandlingData = value; }
		}

	private:
		Native_tHandlingData* m_cNativeHandlingData;
		ModelFlags^ m_cModelFlags;
		HandlingFlags^ m_cHandlingFlags;
	};

	public ref class CHandlingDataMgr
	{
	public:

		/// <summary>
		/// - DOES NOT WORK PROPERLY YET - Gets the handling data of every car that is definied in the handling.dat file. Length: 160.
		/// </summary>
		static property array<tHandlingData^>^ HandlingData {
			array<tHandlingData^>^ get()
			{
				array<tHandlingData^>^ arr = gcnew array<tHandlingData^>(160);

				for (int i = 0; i < arr->Length; i++)
				{
					Native_tHandlingData* ptr = &Native_CHandlingDataMgr::HandlingData[i];

					if (ptr)
						arr[i] = gcnew tHandlingData(ptr);
				}

				return arr;
			}
			void set(array<tHandlingData^>^ value)
			{
				if (!value)
					return;

				for (int i = 0; i < value->Length; i++)
				{
					tHandlingData^ ptr = value[i];

					if (ptr)
						Native_CHandlingDataMgr::HandlingData[i] = *ptr->HandlingDataPointer;
				}
			}
		}

		static void Initialise();
		static void LoadHandlingData(String^ sPath);

		/// <summary>
		/// Gets the handling data from the given id.
		/// </summary>
		/// <param name="id">The handling data id.</param>
		/// <returns>If successful, the handling data from the given id is returned. Otherwise, null.</returns>
		static tHandlingData^ GetHandlingData(int id);

		/// <summary>
		/// Gets the handling id from the given name.
		/// </summary>
		/// <param name="handlingName">The handling name how it is defined in the handling.dat file.</param>
		/// <returns>The handling id from the given name.</returns>
		static int GetHandlingId(String^ handlingName);

	};

}