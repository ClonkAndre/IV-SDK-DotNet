#pragma once

namespace IVSDKDotNet
{
	public value struct IVHandlingDataModelFlags
	{
	public:
		property bool IsVan
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bIsVan;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bIsVan = value;
			}
		}
		property bool IsBus
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bIsBus;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bIsBus = value;
			}
		}
		property bool IsLow
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bIsLow;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bIsLow = value;
			}
		}
		property bool IsBig
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bIsBig;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bIsBig = value;
			}
		}
		property bool AbsStd
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAbsStd;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAbsStd = value;
			}
		}
		property bool AbsOption
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAbsOption;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAbsOption = value;
			}
		}
		property bool AbsAltStd
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAbsAltStd;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAbsAltStd = value;
			}
		}
		property bool AbsAltOption
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAbsAltOption;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAbsAltOption = value;
			}
		}
		property bool NoDoors
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bNoDoors;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bNoDoors = value;
			}
		}
		property bool TandemSeats
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bTandemSeats;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bTandemSeats = value;
			}
		}
		property bool SitInBoat
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bSitInBoat;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bSitInBoat = value;
			}
		}
		property bool None
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bNone;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bNone = value;
			}
		}
		property bool NoExhaust
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bNoExhaust;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bNoExhaust = value;
			}
		}
		property bool DoubleExhaust
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bDoubleExhaust;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bDoubleExhaust = value;
			}
		}
		property bool No1fpsLookBehind
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bNo1fpsLookBehind;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bNo1fpsLookBehind = value;
			}
		}
		property bool CanEnterIfNoDoor
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bCanEnterIfNoDoor;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bCanEnterIfNoDoor = value;
			}
		}
		property bool AxleFNotilt
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAxleFNotilt;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAxleFNotilt = value;
			}
		}
		property bool AxleFSolid
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAxleFSolid;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAxleFSolid = value;
			}
		}
		property bool AxleFMcpherson
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAxleFMcpherson;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAxleFMcpherson = value;
			}
		}
		property bool AxleFReverse
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAxleFReverse;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAxleFReverse = value;
			}
		}
		property bool AxleRNotilt
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAxleRNotilt;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAxleRNotilt = value;
			}
		}
		property bool AxleRSolid
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAxleRSolid;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAxleRSolid = value;
			}
		}
		property bool AxleRMcpherson
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAxleRMcpherson;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAxleRMcpherson = value;
			}
		}
		property bool AxleRReverse
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bAxleRReverse;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bAxleRReverse = value;
			}
		}
		property bool IsBike
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bIsBike;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bIsBike = value;
			}
		}
		property bool IsHeli
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bIsHeli;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bIsHeli = value;
			}
		}
		property bool IsPlane
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bIsPlane;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bIsPlane = value;
			}
		}
		property bool IsBoat
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bIsBoat;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bIsBoat = value;
			}
		}
		property bool BouncePanels
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bBouncePanels;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bBouncePanels = value;
			}
		}
		property bool DoubleRWheels
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bDoubleRWheels;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bDoubleRWheels = value;
			}
		}
		property bool ForceGroundClearance
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bForceGroundClearance;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bForceGroundClearance = value;
			}
		}
		property bool IsHatchback
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nModelFlags.bIsHatchback;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nModelFlags.bIsHatchback = value;
			}
		}

	internal:
		IVHandlingDataModelFlags(tHandlingData* nativePtr);

	internal:
		tHandlingData* NativeHandlingData;
	};
	public value struct IVHandlingDataHandlingFlags
	{
	public:
		property bool SmoothCompresn
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bSmoothCompresn;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bSmoothCompresn = value;
			}
		}
		property bool None
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bNone;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bNone = value;
			}
		}
		property bool NpcAntiRoll
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bNpcAntiRoll;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bNpcAntiRoll = value;
			}
		}
		property bool NpcNeutralHandl
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bNpcNeutralHandl;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bNpcNeutralHandl = value;
			}
		}
		property bool NoHandbrake
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bNoHandbrake;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bNoHandbrake = value;
			}
		}
		property bool SteerRearwheels
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bSteerRearwheels;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bSteerRearwheels = value;
			}
		}
		property bool HbRearwheelSteer
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bHbRearwheelSteer;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bHbRearwheelSteer = value;
			}
		}
		property bool AltSteerOpt
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bAltSteerOpt;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bAltSteerOpt = value;
			}
		}
		property bool WheelFNarrow2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bWheelFNarrow2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bWheelFNarrow2 = value;
			}
		}
		property bool WheelFNarrow
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bWheelFNarrow;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bWheelFNarrow = value;
			}
		}
		property bool WheelFWide
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bWheelFWide;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bWheelFWide = value;
			}
		}
		property bool WheelFWide2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bWheelFWide2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bWheelFWide2 = value;
			}
		}
		property bool WheelRNarrow2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bWheelRNarrow2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bWheelRNarrow2 = value;
			}
		}
		property bool WheelRNarrow
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bWheelRNarrow;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bWheelRNarrow = value;
			}
		}
		property bool WheelRWide
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bWheelRWide;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bWheelRWide = value;
			}
		}
		property bool WheelRWide2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bWheelRWide2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bWheelRWide2 = value;
			}
		}
		property bool HydraulicGeom
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bHydraulicGeom;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bHydraulicGeom = value;
			}
		}
		property bool HydraulicInst
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bHydraulicInst;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bHydraulicInst = value;
			}
		}
		property bool HydraulicNone
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bHydraulicNone;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bHydraulicNone = value;
			}
		}
		property bool NosInst
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bNosInst;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bNosInst = value;
			}
		}
		property bool OffroadAbility
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bOffroadAbility;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bOffroadAbility = value;
			}
		}
		property bool OffroadAbility2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bOffroadAbility2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bOffroadAbility2 = value;
			}
		}
		property bool HalogenLights
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bHalogenLights;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bHalogenLights = value;
			}
		}
		property bool ProcRearwheel1st
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bProcRearwheel1st;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bProcRearwheel1st = value;
			}
		}
		property bool UseMaxspLimit
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bUseMaxspLimit;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bUseMaxspLimit = value;
			}
		}
		property bool LowRider
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bLowRider;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bLowRider = value;
			}
		}
		property bool StreetRacer
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bStreetRacer;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bStreetRacer = value;
			}
		}
		property bool None2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bNone2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bNone2 = value;
			}
		}
		property bool SwingingChassis
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bSwingingChassis;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bSwingingChassis = value;
			}
		}
		property bool OldPhysics
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bOldPhysics;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bOldPhysics = value;
			}
		}
		property bool None3
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bNone3;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bNone3 = value;
			}
		}
		property bool None4
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, false);
				return NativeHandlingData->m_nHandlingFlags.bNone4;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nHandlingFlags.bNone4 = value;
			}
		}

	internal:
		IVHandlingDataHandlingFlags(tHandlingData* nativePtr);

	internal:
		tHandlingData* NativeHandlingData;
	};

	public ref class IVHandlingData
	{
	public:
		property String^ Name
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, String::Empty);
				return gcnew String(NativeHandlingData->m_sName);
			}
		}
		property float Mass
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fMass;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fMass = value;
			}
		}
		property float DragMult
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fDragMult;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fDragMult = value;
			}
		}
		property Vector3 CenterOfMass
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, Vector3::Zero);
				CVector_pad v = NativeHandlingData->m_vCenterOfMass;
				return Vector3(v.x, v.y, v.z);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeHandlingData);

				CVector_pad v;
				v.x = value.X;
				v.y = value.Y;
				v.z = value.Z;

				NativeHandlingData->m_vCenterOfMass = v;
			}
		}
		property uint32_t PercentSubmerged
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0);
				return NativeHandlingData->m_nPercentSubmerged;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nPercentSubmerged = value;
			}
		}
		property float PercentSubmergedFloat
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fPercentSubmerged;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fPercentSubmerged = value;
			}
		}
		property float DriveBiasF
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fDriveBiasF;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fDriveBiasF = value;
			}
		}
		property float DriveBiasR
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fDriveBiasR;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fDriveBiasR = value;
			}
		}
		property uint32_t DriveGears
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0);
				return NativeHandlingData->m_nDriveGears;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nDriveGears = value;
			}
		}
		property float DriveForce
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fDriveForce;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fDriveForce = value;
			}
		}
		property float DriveInertia
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fDriveInertia;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fDriveInertia = value;
			}
		}
		property float V_times12
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fV_times12;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fV_times12 = value;
			}
		}
		property float V
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fV;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fV = value;
			}
		}
		property float V_gearR
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fV_gearR;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fV_gearR = value;
			}
		}
		property float V_gear1
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fV_gear1;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fV_gear1 = value;
			}
		}
		property float V_gear2
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fV_gear2;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fV_gear2 = value;
			}
		}
		property float V_gear3
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fV_gear3;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fV_gear3 = value;
			}
		}
		property float V_gear4
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fV_gear4;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fV_gear4 = value;
			}
		}
		property float V_gear5
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fV_gear5;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fV_gear5 = value;
			}
		}
		property float V_gear6
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fV_gear6;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fV_gear6 = value;
			}
		}
		property float V_gear7
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fV_gear7;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fV_gear7 = value;
			}
		}
		property float BrakeForce
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fBrakeForce;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fBrakeForce = value;
			}
		}
		property float BrakeForceF
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fBrakeForceF;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fBrakeForceF = value;
			}
		}
		property float BrakeForceR
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fBrakeForceR;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fBrakeForceR = value;
			}
		}
		property float HBias
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fHBias;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fHBias = value;
			}
		}
		property float SteeringLock
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fSteeringLock;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fSteeringLock = value;
			}
		}
		property float SteeringLockPercent
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fSteeringLockPercent;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fSteeringLockPercent = value;
			}
		}
		property float TractionCurveMax
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fTractionCurveMax;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fTractionCurveMax = value;
			}
		}
		property float TractionCurveMaxPercent
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fTractionCurveMaxPercent;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fTractionCurveMaxPercent = value;
			}
		}
		property float TractionCurveMin
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fTractionCurveMin;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fTractionCurveMin = value;
			}
		}
		property float TractionCurvePercent
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fTractionCurvePercent;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fTractionCurvePercent = value;
			}
		}
		property float TractionCurveLateral
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fTractionCurveLateral;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fTractionCurveLateral = value;
			}
		}
		property float TractionCurveLateralPercent
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fTractionCurveLateralPercent;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fTractionCurveLateralPercent = value;
			}
		}
		property float TractionSpringDeltaMax
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fTractionSpringDeltaMax;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fTractionSpringDeltaMax = value;
			}
		}
		property float TractionSpringDeltaMaxPercent
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fTractionSpringDeltaMaxPercent;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fTractionSpringDeltaMaxPercent = value;
			}
		}
		property float TractionBiasF
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fTractionBiasF;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fTractionBiasF = value;
			}
		}
		property float TractionBiasR
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fTractionBiasR;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fTractionBiasR = value;
			}
		}
		property float SuspensionForce
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fSuspensionForce;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fSuspensionForce = value;
			}
		}
		property float SuspensionCompDamp
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fSuspensionCompDamp;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fSuspensionCompDamp = value;
			}
		}
		property float SuspensionReboundDamp
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fSuspensionReboundDamp;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fSuspensionReboundDamp = value;
			}
		}
		property float SuspensionUpperLimit
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fSuspensionUpperLimit;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fSuspensionUpperLimit = value;
			}
		}
		property float SuspensionLowerLimit
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fSuspensionLowerLimit;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fSuspensionLowerLimit = value;
			}
		}
		property float SuspensionRaise
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fSuspensionRaise;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fSuspensionRaise = value;
			}
		}
		property float SuspensionBiasF
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fSuspensionBiasF;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fSuspensionBiasF = value;
			}
		}
		property float SuspensionBiasR
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fSuspensionBiasR;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fSuspensionBiasR = value;
			}
		}
		property float CollisionDamageMult
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fCollisionDamageMult;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fCollisionDamageMult = value;
			}
		}
		property float WeaponDamageMult
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fWeaponDamageMult;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fWeaponDamageMult = value;
			}
		}
		property float DeformationDamageMult
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fDeformationDamageMult;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fDeformationDamageMult = value;
			}
		}
		property float EngineDamageMult
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fEngineDamageMult;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fEngineDamageMult = value;
			}
		}
		property float SeatOffsetDist
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0.0F);
				return NativeHandlingData->m_fSeatOffsetDist;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_fSeatOffsetDist = value;
			}
		}
		property uint32_t MonetaryValue
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, 0);
				return NativeHandlingData->m_nMonetaryValue;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeHandlingData);
				NativeHandlingData->m_nMonetaryValue = value;
			}
		}

		property IVHandlingDataModelFlags ModelFlags
		{
		public:
			IVHandlingDataModelFlags get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, IVHandlingDataModelFlags());
				return IVHandlingDataModelFlags(NativeHandlingData);
			}
		}
		property IVHandlingDataHandlingFlags HandlingFlags
		{
		public:
			IVHandlingDataHandlingFlags get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, IVHandlingDataHandlingFlags());
				return IVHandlingDataHandlingFlags(NativeHandlingData);
			}
		}

		property UIntPtr BikeHandling
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, UIntPtr::Zero);
				return UIntPtr(NativeHandlingData->m_pBikeHandling);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				NativeHandlingData->m_pBikeHandling = (tBikeHandlingData*)value.ToPointer();
			}
		}
		property UIntPtr FlyingHandling
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, UIntPtr::Zero);
				return UIntPtr(NativeHandlingData->m_pFlyingHandling);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				NativeHandlingData->m_pFlyingHandling = (tFlyingHandlingData*)value.ToPointer();
			}
		}
		property UIntPtr BoatHandling
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeHandlingData, UIntPtr::Zero);
				return UIntPtr(NativeHandlingData->m_pBoatHandling);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				NativeHandlingData->m_pBoatHandling = (tBoatHandlingData*)value.ToPointer();
			}
		}

	internal:
		IVHandlingData(tHandlingData* nativePtr);

	internal:
		tHandlingData* NativeHandlingData;
	};
}