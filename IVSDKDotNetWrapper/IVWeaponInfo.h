#pragma once

namespace IVSDKDotNet
{
	public ref class IVWeaponFlags
	{
	public:
		property bool CanAim
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bCanAim;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bCanAim = value;
			}
		}
		property bool CanAimWithArm
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bCanAimWithArm;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bCanAimWithArm = value;
			}
		}
		property bool CanFreeAim
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bCanFreeAim;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bCanFreeAim = value;
			}
		}
		property bool FirstPerson
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bFirstPerson;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bFirstPerson = value;
			}
		}
		property bool KeepCameraBehind
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bKeepCameraBehind;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bKeepCameraBehind = value;
			}
		}
		property bool Gun
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bGun;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bGun = value;
			}
		}
		property bool Thrown
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bThrown;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bThrown = value;
			}
		}
		property bool Heavy
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bHeavy;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bHeavy = value;
			}
		}
		property bool Silenced
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bSilenced;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bSilenced = value;
			}
		}
		property bool MeleeClub
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bMeleeClub;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bMeleeClub = value;
			}
		}
		property bool MeleeBlade
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bMeleeBlade;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bMeleeBlade = value;
			}
		}
		property bool ArmourPenetrating
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bArmourPenetrating;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bArmourPenetrating = value;
			}
		}
		property bool TwoHanded
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.b2Handed;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.b2Handed = value;
			}
		}
		property bool TreatAsTwoHandedInCover
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bTreatAs2HandedInCover;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bTreatAs2HandedInCover = value;
			}
		}
		property bool AnimReload
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bAnimReload;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bAnimReload = value;
			}
		}
		property bool AnimCrouchFire
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bAnimCrouchFire;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bAnimCrouchFire = value;
			}
		}
		property bool CreateVisibleOrdnance
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bCreateVisibleOrdnance;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bCreateVisibleOrdnance = value;
			}
		}
		property bool ExplosionBasedOnImpact
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bExplosionBasedOnImpact;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bExplosionBasedOnImpact = value;
			}
		}
		property bool AddSmokeOnExplosion
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bAddSmokeOnExplosion;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bAddSmokeOnExplosion = value;
			}
		}
		property bool InstantKillInMP
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bInstantKillInMP;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bInstantKillInMP = value;
			}
		}
		property bool HigherBreakForce
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bHigherBreakForce;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bHigherBreakForce = value;
			}
		}
		property bool CanBeUsedAsDriveBy
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bCanBeUsedAsDriveBy;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bCanBeUsedAsDriveBy = value;
			}
		}
		property bool HeavyWeaponUsesRifleAnims
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bHeavyWeaponUsesRifleAnims;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bHeavyWeaponUsesRifleAnims = value;
			}
		}
		property bool MissionCanForceDriveByUse
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bMissionCanForceDriveByUse;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bMissionCanForceDriveByUse = value;
			}
		}
		property bool DontRumbleWhenDoingDriveBy
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, false);
				return NativeWeaponInfo->m_nWeaponFlags.bDontRumbleWhenDoingDriveBy;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponFlags.bDontRumbleWhenDoingDriveBy = value;
			}
		}

	internal:
		IVWeaponFlags(CWeaponInfo* nativePtr);

	internal:
		CWeaponInfo* NativeWeaponInfo;
	};

	public ref class IVWeaponInfo
	{
	public:
		static property array<IVWeaponInfo^>^ WeaponInfo
		{
		public:
			array<IVWeaponInfo^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(aWeaponInfo, nullptr);

				array<IVWeaponInfo^>^ arr = gcnew array<IVWeaponInfo^>(60);
				
				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVWeaponInfo(&aWeaponInfo[i]);

				return arr;
			}
			void set(array<IVWeaponInfo^>^ value)
			{
				NULLPTR_CHECK(aWeaponInfo);
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					aWeaponInfo[i] = *value[i]->NativeWeaponInfo;
			}
		}
		static property array<String^>^ WeaponNames
		{
		public:
			array<String^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CWeaponInfo::ms_aWeaponNames, nullptr);

				array<String^>^ arr = gcnew array<String^>(60);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew String(CWeaponInfo::ms_aWeaponNames[i]);

				return arr;
			}
			void set(array<String^>^ value)
			{
				NULLPTR_CHECK(aWeaponInfo);
				NULLPTR_CHECK(value);

				msclr::interop::marshal_context ctx;
				for(int i = 0; i < value->Length; i++)
					CWeaponInfo::ms_aWeaponNames[i] = (char*)ctx.marshal_as<const char*>(value[i]);
			}
		}

	public:
		property uint32_t WeaponType
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nWeaponType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponType = value;
			}
		}
		property uint32_t WeaponSlot
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nWeaponSlot;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nWeaponSlot = value;
			}
		}
		property uint32_t FireType
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nFireType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nFireType = value;
			}
		}
		property uint32_t DamageType
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nDamageType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nDamageType = value;
			}
		}
		property uint32_t Group
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nGroup;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nGroup = value;
			}
		}
		property float TargetRange
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fTargetRange;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fTargetRange = value;
			}
		}
		property float WeaponRange
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fWeaponRange;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fWeaponRange = value;
			}
		}
		property uint32_t StatType
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nStatType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nStatType = value;
			}
		}
		property IVWeaponFlags^ WeaponFlags
		{
		public:
			IVWeaponFlags^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, nullptr);
				return gcnew IVWeaponFlags(NativeWeaponInfo);
			}
		}
		property uint32_t ModelHash
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nModelHash;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nModelHash = value;
			}
		}
		property uint32_t AnimGroup
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_animGroup;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_animGroup = value;
			}
		}
		property float FireRate
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fFireRate;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fFireRate = value;
			}
		}
		property float BlindFireRate
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fBlindFireRate;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fBlindFireRate = value;
			}
		}
		property float Accuracy
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fAccuracy;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fAccuracy = value;
			}
		}
		property float AccuracyFPS
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fAccuracyFPS;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fAccuracyFPS = value;
			}
		}
		property Vector3 Offset
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, Vector3::Zero);
				return CVectorPadToVector(NativeWeaponInfo->m_vOffset);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_vOffset = VectorToCVectorPad(value);
			}
		}
		property Vector3 CrouchOffset
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, Vector3::Zero);
				return CVectorPadToVector(NativeWeaponInfo->m_vCrouchOffset);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_vCrouchOffset = VectorToCVectorPad(value);
			}
		}
		property float AimingPitch
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fAimingPitch;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fAimingPitch = value;
			}
		}
		property float ReticuleStanding
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fReticuleStanding;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fReticuleStanding = value;
			}
		}
		property float ReticuleDucked
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fReticuleDucked;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fReticuleDucked = value;
			}
		}
		property float ReticuleScale
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fReticuleScale;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fReticuleScale = value;
			}
		}
		property uint32_t RumbleDuration
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nRumbleDuration;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nRumbleDuration = value;
			}
		}
		property float RumbleIntensity
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fRumbleIntensity;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fRumbleIntensity = value;
			}
		}
		property uint32_t PickupRegenTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nPickupRegenTime;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nPickupRegenTime = value;
			}
		}
		property uint16_t PickupAmmoOnStreet
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nPickupAmmoOnStreet;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nPickupAmmoOnStreet = value;
			}
		}
		property uint16_t Damage
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nDamage;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nDamage = value;
			}
		}
		property uint16_t DamageFPS
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nDamageFPS;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nDamageFPS = value;
			}
		}
		property uint16_t ClipSize
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nClipSize;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nClipSize = value;
			}
		}
		property uint32_t MaxAmmo
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nMaxAmmo;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nMaxAmmo = value;
			}
		}
		property uint32_t TimeBetweenShots
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nTimeBetweenShots;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nTimeBetweenShots = value;
			}
		}
		property float PhysicsForce
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fPhysicsForce;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fPhysicsForce = value;
			}
		}
		property uint32_t ReloadTimeNormal
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nReloadTimeNormal;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nReloadTimeNormal = value;
			}
		}
		property uint32_t ReloadTimeFast
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nReloadTimeFast;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nReloadTimeFast = value;
			}
		}
		property uint32_t ReloadTimeCrouch
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nReloadTimeCrouch;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nReloadTimeCrouch = value;
			}
		}
		property uint32_t ProjectileType
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nProjectileType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nProjectileType = value;
			}
		}
		property uint32_t ProjectileFuseTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nProjectileFuseTime;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nProjectileFuseTime = value;
			}
		}
		property uint32_t ProjectileToCreate
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nProjectileToCreate;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nProjectileToCreate = value;
			}
		}
		property uint32_t ProjectileExplosionType
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nProjectileExplosionType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nProjectileExplosionType = value;
			}
		}
		property Vector3 ProjectileOffset
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, Vector3::Zero);
				return CVectorPadToVector(NativeWeaponInfo->m_vProjectileOffset);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_vProjectileOffset = VectorToCVectorPad(value);
			}
		}
		property Vector3 ProjectileRotOffset
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, Vector3::Zero);
				return CVectorPadToVector(NativeWeaponInfo->m_vProjectileRotOffset);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_vProjectileRotOffset = VectorToCVectorPad(value);
			}
		}
		property float ProjectilePhysicsExplodeImpactThreshold
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fProjectilePhysicsExplodeImpactThreshold;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fProjectilePhysicsExplodeImpactThreshold = value;
			}
		}
		property float ProjectilePhysicsExplodeImpactVehicleThreshold
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fProjectilePhysicsExplodeImpactVehicleThreshold;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fProjectilePhysicsExplodeImpactVehicleThreshold = value;
			}
		}
		property float ProjectilePhysicsVehicleVelocity
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fProjectilePhysicsVehicleVelocity;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fProjectilePhysicsVehicleVelocity = value;
			}
		}
		property uint32_t MeleeAnim
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nMeleeAnim;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nMeleeAnim = value;
			}
		}
		property uint32_t MuzzleFx
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nMuzzleFx;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nMuzzleFx = value;
			}
		}
		property uint32_t ShellFx
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nShellFx;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nShellFx = value;
			}
		}
		property uint32_t ProjectileTrailFx
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nProjectileTrailFx;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nProjectileTrailFx = value;
			}
		}
		property float NetworkPlayerMod
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fNetworkPlayerMod;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fNetworkPlayerMod = value;
			}
		}
		property float NetworkPedMod
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fNetworkPedMod;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fNetworkPedMod = value;
			}
		}
		property float AimingAccuracyTime
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0.0F);
				return NativeWeaponInfo->m_fAimingAccuracyTime;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_fAimingAccuracyTime = value;
			}
		}
		property uint32_t AimingPellets
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nAimingPellets;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nAimingPellets = value;
			}
		}
		property uint32_t ShotsFired
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeWeaponInfo, 0);
				return NativeWeaponInfo->m_nShotsFired;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeWeaponInfo);
				NativeWeaponInfo->m_nShotsFired = value;
			}
		}

	public:
		static IVWeaponInfo^ GetWeaponInfo(uint32_t weaponID);
		static void LoadWeaponData(String^ path);
		static int FindWeaponType(uint32_t nameHash, int defaultReturn);
		static int FindWeaponType(String^ pString, int defaultReturn);
		static int FindWeaponFireType(String^ pString);
		static int FindWeaponDamageType(String^ pString);

	internal:
		IVWeaponInfo(CWeaponInfo* nativePtr);

	internal:
		CWeaponInfo* NativeWeaponInfo;
	};
}