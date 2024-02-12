#pragma once

namespace IVSDKDotNet
{
	public ref class IVVehicleHandlingFlags
	{
	public:
		property bool SmoothCompresn
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bSmoothCompresn;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bSmoothCompresn = value;
			}
		}
		property bool None
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bNone;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bNone = value;
			}
		}
		property bool NpcAntiRoll
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bNpcAntiRoll;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bNpcAntiRoll = value;
			}
		}
		property bool NpcNeutralHandl
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bNpcNeutralHandl;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bNpcNeutralHandl = value;
			}
		}
		property bool NoHandbrake
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bNoHandbrake;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bNoHandbrake = value;
			}
		}
		property bool SteerRearwheels
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bSteerRearwheels;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bSteerRearwheels = value;
			}
		}
		property bool HbRearwheelSteer
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bHbRearwheelSteer;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bHbRearwheelSteer = value;
			}
		}
		property bool AltSteerOpt
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bAltSteerOpt;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bAltSteerOpt = value;
			}
		}
		property bool WheelFNarrow2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bWheelFNarrow2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bWheelFNarrow2 = value;
			}
		}
		property bool WheelFNarrow
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bWheelFNarrow;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bWheelFNarrow = value;
			}
		}
		property bool WheelFWide
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bWheelFWide;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bWheelFWide = value;
			}
		}
		property bool WheelFWide2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bWheelFWide2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bWheelFWide2 = value;
			}
		}
		property bool WheelRNarrow2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bWheelRNarrow2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bWheelRNarrow2 = value;
			}
		}
		property bool WheelRNarrow
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bWheelRNarrow;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bWheelRNarrow = value;
			}
		}
		property bool WheelRWide
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bWheelRWide;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bWheelRWide = value;
			}
		}
		property bool WheelRWide2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bWheelRWide2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bWheelRWide2 = value;
			}
		}
		property bool HydraulicGeom
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bHydraulicGeom;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bHydraulicGeom = value;
			}
		}
		property bool HydraulicInst
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bHydraulicInst;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bHydraulicInst = value;
			}
		}
		property bool HydraulicNone
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bHydraulicNone;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bHydraulicNone = value;
			}
		}
		property bool NosInst
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bNosInst;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bNosInst = value;
			}
		}
		property bool OffroadAbility
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bOffroadAbility;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bOffroadAbility = value;
			}
		}
		property bool OffroadAbility2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bOffroadAbility2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bOffroadAbility2 = value;
			}
		}
		property bool HalogenLights
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bHalogenLights;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bHalogenLights = value;
			}
		}
		property bool ProcRearwheel1st
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bProcRearwheel1st;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bProcRearwheel1st = value;
			}
		}
		property bool UseMaxspLimit
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bUseMaxspLimit;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bUseMaxspLimit = value;
			}
		}
		property bool LowRider
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bLowRider;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bLowRider = value;
			}
		}
		property bool StreetRacer
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bStreetRacer;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bStreetRacer = value;
			}
		}
		property bool None2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bNone2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bNone2 = value;
			}
		}
		property bool SwingingChassis
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bSwingingChassis;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bSwingingChassis = value;
			}
		}
		property bool OldPhysics
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bOldPhysics;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bOldPhysics = value;
			}
		}
		property bool None3
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bNone3;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bNone3 = value;
			}
		}
		property bool None4
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nHandlingFlags.bNone4;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHandlingFlags.bNone4 = value;
			}
		}

	internal:
		IVVehicleHandlingFlags(CVehicle* nativePtr);

	internal:
		CVehicle* NativeVehicle;
	};

	public ref class IVVehicleFlags
	{
	public:
		property bool _f0
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f0;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f0 = value;
			}
		}
		property bool _f1
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f1;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f1 = value;
			}
		}
		property bool _f2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f2 = value;
			}
		}
		property bool EngineOn
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bEngineOn;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bEngineOn = value;
			}
		}
		property bool EngineStarting
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bEngineStarting;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bEngineStarting = value;
			}
		}
		property bool _f5
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f5;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f5 = value;
			}
		}
		property bool _f6
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f6;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f6 = value;
			}
		}
		property bool IsHandbrakeOn
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bIsHandbrakeOn;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bIsHandbrakeOn = value;
			}
		}
		property bool LightsOn
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bLightsOn;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bLightsOn = value;
			}
		}
		property bool Freebies
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bFreebies;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bFreebies = value;
			}
		}
		property bool _fa
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._fa;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._fa = value;
			}
		}
		property bool _fb
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._fb;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._fb = value;
			}
		}
		property bool BigVehicle
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bBigVehicle;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bBigVehicle = value;
			}
		}
		property bool _fd
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._fd;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._fd = value;
			}
		}
		property bool _fe
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._fe;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._fe = value;
			}
		}
		property bool _ff
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._ff;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._ff = value;
			}
		}
		property bool TakesLessDamage
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bTakesLessDamage;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bTakesLessDamage = value;
			}
		}
		property bool HasBeenOwnedByPlayer
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bHasBeenOwnedByPlayer;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bHasBeenOwnedByPlayer = value;
			}
		}
		property bool NeedsToBeHotWired
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bNeedsToBeHotWired;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bNeedsToBeHotWired = value;
			}
		}
		property bool _f14
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f14;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f14 = value;
			}
		}
		property bool _f15
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f15;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f15 = value;
			}
		}
		property bool _f16
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f16;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f16 = value;
			}
		}
		property bool _f17
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f17;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f17 = value;
			}
		}
		property bool _f18
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f18;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f18 = value;
			}
		}
		property bool PartOfConvoy
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bPartOfConvoy;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bPartOfConvoy = value;
			}
		}
		property bool HeliStabiliser
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bHeliStabiliser;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bHeliStabiliser = value;
			}
		}
		property bool _f1b
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f1b;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f1b = value;
			}
		}
		property bool IsDead
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bIsDead;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bIsDead = value;
			}
		}
		property bool CanBurstTyres
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags.bCanBurstTyres;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags.bCanBurstTyres = value;
			}
		}
		property bool _f1d
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f1d;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f1d = value;
			}
		}
		property bool _f1e
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f1e;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f1e = value;
			}
		}
		property bool _f1f
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags._f1f;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags._f1f = value;
			}
		}

	internal:
		IVVehicleFlags(CVehicle* nativePtr);

	internal:
		CVehicle* NativeVehicle;
	};
	public ref class IVVehicleFlags2
	{
	public:
		property bool _f0
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f0;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f0 = value;
			}
		}
		property bool _f1
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f1;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f1 = value;
			}
		}
		property bool _f2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f2 = value;
			}
		}
		property bool _f3
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f3;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f3 = value;
			}
		}
		property bool _f4
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f4;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f4 = value;
			}
		}
		property bool AlwaysCreateSkids
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2.bAlwaysCreateSkids;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2.bAlwaysCreateSkids = value;
			}
		}
		property bool CanBeTargetted
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2.bCanBeTargetted;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2.bCanBeTargetted = value;
			}
		}
		property bool _f7
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f7;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f7 = value;
			}
		}
		property bool CanBeTargetedByHSmmissile
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2.bCanBeTargetedByHSmmissile;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2.bCanBeTargetedByHSmmissile = value;
			}
		}
		property bool LongLight
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2.bLongLight;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2.bLongLight = value;
			}
		}
		property bool _fa
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._fa;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._fa = value;
			}
		}
		property bool _fb
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._fb;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._fb = value;
			}
		}
		property bool SirenSwitchedOn
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2.bSirenSwitchedOn;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2.bSirenSwitchedOn = value;
			}
		}
		property bool SirenRelated
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2.bSirenRelated;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2.bSirenRelated = value;
			}
		}
		property bool _fe
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._fe;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._fe = value;
			}
		}
		property bool _ff
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._ff;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._ff = value;
			}
		}
		property bool _f10
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f10;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f10 = value;
			}
		}
		property bool _f11
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f11;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f11 = value;
			}
		}
		property bool _f12
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f12;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f12 = value;
			}
		}
		property bool BikeRiderWillPutDownFootWhenStopped
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2.bBikeRiderWillPutDownFootWhenStopped;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2.bBikeRiderWillPutDownFootWhenStopped = value;
			}
		}
		property bool ProvideCover
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2.bProvideCover;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2.bProvideCover = value;
			}
		}
		property bool _f15
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f15;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f15 = value;
			}
		}
		property bool _f16
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f16;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f16 = value;
			}
		}
		property bool VehicleIsConsideredByPlayer
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2.bVehicleIsConsideredByPlayer;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2.bVehicleIsConsideredByPlayer = value;
			}
		}
		property bool PetrolTankWeakpoint
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2.bPetrolTankWeakpoint;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2.bPetrolTankWeakpoint = value;
			}
		}
		property bool _f19
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f19;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f19 = value;
			}
		}
		property bool CarBeenResprayed
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2.bCarBeenResprayed;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2.bCarBeenResprayed = value;
			}
		}
		property bool _f1b
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f1b;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f1b = value;
			}
		}
		property bool _f1c
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f1c;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f1c = value;
			}
		}
		property bool _f1d
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f1d;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f1d = value;
			}
		}
		property bool _f1e
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f1e;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f1e = value;
			}
		}

	internal:
		IVVehicleFlags2(CVehicle* nativePtr);

	internal:
		CVehicle* NativeVehicle;
	};
	public ref class IVVehicleFlags3
	{
	public:
		property bool LeftIndicator
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags2._f1f;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags2._f1f = value;
			}
		}
		property bool RightIndicator
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bRightIndicator;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bRightIndicator = value;
			}
		}
		property bool HazardLights
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bHazardLights;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bHazardLights = value;
			}
		}
		property bool IndicatorLights
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bIndicatorLights;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bIndicatorLights = value;
			}
		}
		property bool _f3
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f3;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f3 = value;
			}
		}
		property bool InteriorLights
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bInteriorLights;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bInteriorLights = value;
			}
		}
		property bool VehicleIsHot
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bVehicleIsHot;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bVehicleIsHot = value;
			}
		}
		property bool _f6
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f6;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f6 = value;
			}
		}
		property bool _f7
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f7;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f7 = value;
			}
		}
		property bool _f8
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f8;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f8 = value;
			}
		}
		property bool _f9
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f9;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f9 = value;
			}
		}
		property bool Deleted
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bDeleted;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bDeleted = value;
			}
		}
		property bool _fb
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._fb;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._fb = value;
			}
		}
		property bool TiresIsDestroyed
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bTiresIsDestroyed;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bTiresIsDestroyed = value;
			}
		}
		property bool PretendOccupants
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bPretendOccupants;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bPretendOccupants = value;
			}
		}
		property bool _fe
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._fe;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._fe = value;
			}
		}
		property bool _ff
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._ff;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._ff = value;
			}
		}
		property bool _f10
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f10;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f10 = value;
			}
		}
		property bool _f11
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f11;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f11 = value;
			}
		}
		property bool _f12
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f12;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f12 = value;
			}
		}
		property bool _f13
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f13;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f13 = value;
			}
		}
		property bool _f14
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f14;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f14 = value;
			}
		}
		property bool HaveSiren
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bHaveSiren;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bHaveSiren = value;
			}
		}
		property bool PoliceFocusWillTrackCar
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bPoliceFocusWillTrackCar;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bPoliceFocusWillTrackCar = value;
			}
		}
		property bool _f17
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f17;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f17 = value;
			}
		}
		property bool _f18
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f18;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f18 = value;
			}
		}
		property bool SetBlipThrottleRandomly
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bSetBlipThrottleRandomly;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bSetBlipThrottleRandomly = value;
			}
		}
		property bool _f1a
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f1a;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f1a = value;
			}
		}
		property bool InCutscene
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bInCutscene;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bInCutscene = value;
			}
		}
		property bool _f1c
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f1c;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f1c = value;
			}
		}
		property bool PoliceVehicle
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bPoliceVehicle;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bPoliceVehicle = value;
			}
		}
		property bool EmergencyServicesVehicle
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3.bEmergencyServicesVehicle;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3.bEmergencyServicesVehicle = value;
			}
		}
		property bool _f1f
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags3._f1f;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags3._f1f = value;
			}
		}

	internal:
		IVVehicleFlags3(CVehicle* nativePtr);

	internal:
		CVehicle* NativeVehicle;
	};
	public ref class IVVehicleFlags4
	{
	public:
		property bool _f0
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f0;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f0 = value;
			}
		}
		property bool _f1
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f1;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f1 = value;
			}
		}
		property bool CanBeVisiblyDamaged
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4.bCanBeVisiblyDamaged;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4.bCanBeVisiblyDamaged = value;
			}
		}
		property bool HasStrongAxles
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4.bHasStrongAxles;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4.bHasStrongAxles = value;
			}
		}
		property bool _f4
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f4;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f4 = value;
			}
		}
		property bool _f5
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f5;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f5 = value;
			}
		}
		property bool _f6
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f6;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f6 = value;
			}
		}
		property bool _f7
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f7;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f7 = value;
			}
		}
		property bool _f8
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f8;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f8 = value;
			}
		}
		property bool _f9
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f9;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f9 = value;
			}
		}
		property bool Nitro
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4.bNitro;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4.bNitro = value;
			}
		}
		property bool OldCarExhaustFX
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4.bOldCarExhaustFX;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4.bOldCarExhaustFX = value;
			}
		}
		property bool _fc
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._fc;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._fc = value;
			}
		}
		property bool _fd
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._fd;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._fd = value;
			}
		}
		property bool _fe
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._fe;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._fe = value;
			}
		}
		property bool _ff
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._ff;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._ff = value;
			}
		}
		property bool _f10
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f10;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f10 = value;
			}
		}
		property bool _f11
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f11;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f11 = value;
			}
		}
		property bool _f12
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f12;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f12 = value;
			}
		}
		property bool _f13
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f13;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f13 = value;
			}
		}
		property bool _f14
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f14;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f14 = value;
			}
		}
		property bool _f15
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f15;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f15 = value;
			}
		}
		property bool _f16
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f16;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f16 = value;
			}
		}
		property bool _f17
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f17;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f17 = value;
			}
		}
		property bool _f18
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f18;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f18 = value;
			}
		}
		property bool _f19
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f19;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f19 = value;
			}
		}
		property bool _f1a
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f1a;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f1a = value;
			}
		}
		property bool _f1b
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f1b;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f1b = value;
			}
		}
		property bool _f1c
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f1c;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f1c = value;
			}
		}
		property bool _f1d
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f1d;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f1d = value;
			}
		}
		property bool _f1e
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f1e;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f1e = value;
			}
		}
		property bool _f1f
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nVehicleFlags4._f1f;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleFlags4._f1f = value;
			}
		}

	internal:
		IVVehicleFlags4(CVehicle* nativePtr);

	internal:
		CVehicle* NativeVehicle;
	};

	public ref class IVVehicleAbsFlags
	{
	public:
		property bool _f0
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f0;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f0 = value;
			}
		}
		property bool _f1
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f1;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f1 = value;
			}
		}
		property bool _f2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f2 = value;
			}
		}
		property bool _f3
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f3;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f3 = value;
			}
		}
		property bool _f4
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f4;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f4 = value;
			}
		}
		property bool _f5
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f5;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f5 = value;
			}
		}
		property bool _f6
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f6;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f6 = value;
			}
		}
		property bool _f7
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f7;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f7 = value;
			}
		}
		property bool _f8
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f8;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f8 = value;
			}
		}
		property bool _f9
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f9;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f9 = value;
			}
		}
		property bool _fa
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._fa;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._fa = value;
			}
		}
		property bool _fb
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._fb;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._fb = value;
			}
		}
		property bool _fc
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._fc;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._fc = value;
			}
		}
		property bool _fd
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._fd;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._fd = value;
			}
		}
		property bool _fe
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._fe;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._fe = value;
			}
		}
		property bool _ff
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._ff;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._ff = value;
			}
		}
		property bool Abs
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags.bAbs;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags.bAbs = value;
			}
		}
		property bool AbsAlt
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags.bAbsAlt;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags.bAbsAlt = value;
			}
		}
		property bool _f12
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f12;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f12 = value;
			}
		}
		property bool _f13
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f13;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f13 = value;
			}
		}
		property bool _f14
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f14;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f14 = value;
			}
		}
		property bool _f15
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f15;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f15 = value;
			}
		}
		property bool _f16
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f16;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f16 = value;
			}
		}
		property bool _f17
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f17;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f17 = value;
			}
		}
		property bool _f18
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f18;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f18 = value;
			}
		}
		property bool _f19
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f19;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f19 = value;
			}
		}
		property bool _f1a
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f1a;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f1a = value;
			}
		}
		property bool _f1b
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f1b;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f1b = value;
			}
		}
		property bool _f1c
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f1c;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f1c = value;
			}
		}
		property bool _f1d
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f1d;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f1d = value;
			}
		}
		property bool _f1e
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f1e;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f1e = value;
			}
		}
		property bool _f1f
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAbsFlags._f1f;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAbsFlags._f1f = value;
			}
		}

	internal:
		IVVehicleAbsFlags(CVehicle* nativePtr);

	internal:
		CVehicle* NativeVehicle;
	};
	public ref class IVVehicleAutomobileFlags
	{
	public:
		/// <summary>
		/// This is not used.
		/// </summary>
		property bool NotDamagedUpsideDown
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, false);
				return NativeVehicle->m_nAutomobileFlags.bNotDamagedUpsideDown;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nAutomobileFlags.bNotDamagedUpsideDown = value;
			}
		}

	internal:
		IVVehicleAutomobileFlags(CVehicle* nativePtr);

	internal:
		CVehicle* NativeVehicle;
	};

	public ref class IVVehicle : public IVPhysical
	{
	public:
		property uint8_t PrimaryColor2
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nPrimaryColor2;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nPrimaryColor2 = value;
			}
		}
		property uint8_t SecondaryColor2
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nSecondaryColor2;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nSecondaryColor2 = value;
			}
		}
		property uint8_t TertiaryColor2
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nTertiaryColor2;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nTertiaryColor2 = value;
			}
		}
		property uint8_t QuaternaryColor2
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nQuaternaryColor2;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nQuaternaryColor2 = value;
			}
		}
		property float EngineRPM
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fEngineRPM;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fEngineRPM = value;
			}
		}

		/// <summary>
		/// Use with: IVPhInstGta.FromUIntPtr(...);
		/// </summary>
		property UIntPtr VehicleFragInst
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle->m_pVehicleFragInst, UIntPtr::Zero);
				return UIntPtr(NativeVehicle->m_pVehicleFragInst);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeVehicle);
				UINTPTR_ZERO_CHECK(value);
				NativeVehicle->m_pVehicleFragInst = (phInstGta*)value.ToPointer();
			}
		}
		property IVHandlingData^ Handling
		{
		public:
			IVHandlingData^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle->m_pHandling, nullptr);
				return gcnew IVHandlingData(NativeVehicle->m_pHandling);
			}
			void set(IVHandlingData^ value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_pHandling = value->NativeHandlingData;
			}
		}

		property IVVehicleHandlingFlags^ HandlingFlags
		{
		public:
			IVVehicleHandlingFlags^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				return gcnew IVVehicleHandlingFlags(NativeVehicle);
			}
		}
		property IVVehicleFlags^ VehicleFlags
		{
		public:
			IVVehicleFlags^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				return gcnew IVVehicleFlags(NativeVehicle);
			}
		}
		property IVVehicleFlags2^ VehicleFlags2
		{
		public:
			IVVehicleFlags2^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				return gcnew IVVehicleFlags2(NativeVehicle);
			}
		}
		property IVVehicleFlags3^ VehicleFlags3
		{
		public:
			IVVehicleFlags3^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				return gcnew IVVehicleFlags3(NativeVehicle);
			}
		}
		property IVVehicleFlags4^ VehicleFlags4
		{
		public:
			IVVehicleFlags4^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				return gcnew IVVehicleFlags4(NativeVehicle);
			}
		}

		property UIntPtr Driver
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle->m_pDriver, UIntPtr::Zero);
				return UIntPtr(NativeVehicle->m_pDriver);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeVehicle);
				UINTPTR_ZERO_CHECK(value);
				NativeVehicle->m_pDriver = (CPed*)value.ToPointer();
			}
		}
		property array<UIntPtr>^ Passengers
		{
		public:
			array<UIntPtr>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle->m_pPassengers, nullptr);

				array<UIntPtr>^ arr = gcnew array<UIntPtr>(8);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = UIntPtr(NativeVehicle->m_pPassengers[i]);

				return arr;
			}
			void set(array<UIntPtr>^ value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NULLPTR_CHECK(value);
				
				for(int i = 0; i < value->Length; i++)
					NativeVehicle->m_pPassengers[i] = (CPed*)value[i].ToPointer();
			}
		}

		property array<IVVehicleWheel^>^ Wheels
		{
		public:
			array<IVVehicleWheel^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle->m_pWheels, nullptr);

				array<IVVehicleWheel^>^ arr = gcnew array<IVVehicleWheel^>(WheelCount);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVVehicleWheel(&NativeVehicle->m_pWheels[i]);

				return arr;
			}
			void set(array<IVVehicleWheel^>^ value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					NativeVehicle->m_pWheels[i] = *value[i]->NativeVehicleWheel;
			}
		}
		property uint32_t WheelCount
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nWheelCount;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nWheelCount = value;
			}
		}
		property array<IVVehicleDoor^>^ Doors
		{
		public:
			array<IVVehicleDoor^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle->m_pDoors, nullptr);

				array<IVVehicleDoor^>^ arr = gcnew array<IVVehicleDoor^>(DoorCount);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVVehicleDoor(&NativeVehicle->m_pDoors[i]);

				return arr;
			}
			void set(array<IVVehicleDoor^>^ value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					NativeVehicle->m_pDoors[i] = *value[i]->NativeVehicleDoor;
			}
		}
		property uint32_t DoorCount
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nDoorCount;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nDoorCount = value;
			}
		}

		property IVVehicleAbsFlags^ AbsFlags
		{
		public:
			IVVehicleAbsFlags^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				return gcnew IVVehicleAbsFlags(NativeVehicle);
			}
		}

		property uint8_t PrimaryColor
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nPrimaryColor;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nPrimaryColor = value;
			}
		}
		property uint8_t SecondaryColor
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nSecondaryColor;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nSecondaryColor = value;
			}
		}
		property uint8_t TertiaryColor
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nTertiaryColor;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nTertiaryColor = value;
			}
		}
		property uint8_t QuaternaryColor
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nQuaternaryColor;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nQuaternaryColor = value;
			}
		}
		property uint8_t MaxPassengers
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nMaxPassengers;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nMaxPassengers = value;
			}
		}
		property float GasPedal
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fGasPedal;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fGasPedal = value;
			}
		}
		property float BrakePedal
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fBrakePedal;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fBrakePedal = value;
			}
		}
		property float SteerDesired
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fSteerDesired;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fSteerDesired = value;
			}
		}
		property float SteerBias
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fSteerBias;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fSteerBias = value;
			}
		}
		property float SteerActual
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fSteerActual;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fSteerActual = value;
			}
		}
		property uint16_t CurrentGear
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nCurrentGear;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nCurrentGear = value;
			}
		}
		property uint16_t _f10e2
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->_f10e2;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->_f10e2 = value;
			}
		}
		property float EngineRevs
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fEngineRevs;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fEngineRevs = value;
			}
		}
		property float _f10e8
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->_f10e8;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->_f10e8 = value;
			}
		}
		property float _f10ec
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->_f10ec;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->_f10ec = value;
			}
		}
		property float _f10f0
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->_f10f0;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->_f10f0 = value;
			}
		}
		property float _f10f4
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->_f10f4;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->_f10f4 = value;
			}
		}
		property uint32_t _f10f8
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->_f10f8;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->_f10f8 = value;
			}
		}
		property float EngineHealth
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fEngineHealth;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fEngineHealth = value;
			}
		}
		property float _f1100
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->_f1100;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->_f1100 = value;
			}
		}
		property float _f1104
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->_f1104;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->_f1104 = value;
			}
		}
		property uint8_t CreatedBy
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nCreatedBy;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nCreatedBy = value;
			}
		}
		property uint8_t RespotTimer
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nRespotTimer;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nRespotTimer = value;
			}
		}
		property float DirtLevel
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fDirtLevel;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fDirtLevel = value;
			}
		}
		property float PetrolTankHealth
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fPetrolTankHealth;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fPetrolTankHealth = value;
			}
		}
		property array<uint8_t>^ Lights
		{
		public:
			array<uint8_t>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				
				array<uint8_t>^ arr = gcnew array<uint8_t>(13);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = NativeVehicle->m_nLights[i];

				return arr;
			}
			void set(array<uint8_t>^ value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					NativeVehicle->m_nLights[i] = value[i];
			}
		}
		property array<uint8_t>^ Sirens
		{
		public:
			array<uint8_t>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);

				array<uint8_t>^ arr = gcnew array<uint8_t>(8);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = NativeVehicle->m_nSirens[i];

				return arr;
			}
			void set(array<uint8_t>^ value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					NativeVehicle->m_nSirens[i] = value[i];
			}
		}
		property uint32_t DoorLock
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nDoorLock;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nDoorLock = value;
			}
		}
		property float DeformationMult
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fDeformationMult;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fDeformationMult = value;
			}
		}
		property float LightMult
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fLightMult;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fLightMult = value;
			}
		}
		property uint32_t HornCounter
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nHornCounter;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nHornCounter = value;
			}
		}
		property uint32_t VehicleType
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0);
				return NativeVehicle->m_nVehicleType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_nVehicleType = value;
			}
		}
		property IVVehicleAutomobileFlags^ AutomobileFlags
		{
		public:
			IVVehicleAutomobileFlags^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, nullptr);
				return gcnew IVVehicleAutomobileFlags(NativeVehicle);
			}
		}
		property float PlaneTurn
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fPlaneTurn;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fPlaneTurn = value;
			}
		}
		property float PlaneUpDown
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fPlaneUpDown;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fPlaneUpDown = value;
			}
		}
		property float PlaneRotate
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fPlaneRotate;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fPlaneRotate = value;
			}
		}
		property float PlaneThrust
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fPlaneThrust;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fPlaneThrust = value;
			}
		}
		property float PlanePropSpeed
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicle, 0.0F);
				return NativeVehicle->m_fPlanePropSpeed;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicle);
				NativeVehicle->m_fPlanePropSpeed = value;
			}
		}

	public:
		static IVVehicle^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		void Fix();
		void SetRemap(int32_t id);
		int GetRemapIndex();
		void MakeDirty();
		void GetVehicleLightsStatus();
		// returns VehicleStruct part enum
		int GetSeatPartId(int32_t seat);
		// see eVehicleCameraType
		bool GetCameraType([OutAttribute] int32_t% type);
		void ProcessRespot(float delta);
		void ProcessAirControl(UIntPtr unk);
		bool IsDriver(IVPed^ pPed);

	public:
		static float HeightAboveCeiling(float height, int32_t flightModel);
		static bool UsesSiren(int32_t id);

	internal:
		IVVehicle(CVehicle* nativePtr);

	internal:
		CVehicle* NativeVehicle;
	};
}