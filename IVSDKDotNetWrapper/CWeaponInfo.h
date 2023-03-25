#pragma once

class Native_CWeaponInfo
{
public:
	uint32_t m_nWeaponType;									// 000-004
	uint32_t m_nSlot;										// 004-008
	uint32_t m_nFireType;									// 008-00C
	uint32_t m_nDamageType;									// 00C-010
	uint32_t m_nGroup;										// 010-014
	float m_fTargetRange;									// 014-018
	float m_fWeaponRange;									// 018-01C
	uint32_t m_nStatType;									// 01C-020
	struct
	{
		unsigned int bCanAim : 1;
		unsigned int bCanAimWithArm : 1;
		unsigned int bCanFreeAim : 1;
		unsigned int bFirstPerson : 1;
		unsigned int bKeepCameraBehind : 1;
		unsigned int bGun : 1;
		unsigned int bThrown : 1;
		unsigned int bHeavy : 1;
		unsigned int bSilenced : 1;
		unsigned int bMeleeClub : 1;
		unsigned int bMeleeBlade : 1;
		unsigned int bArmourPenetrating : 1;
		unsigned int b2Handed : 1;
		unsigned int bTreatAs2HandedInCover : 1;
		unsigned int bAnimReload : 1;
		unsigned int bAnimCrouchFire : 1;
		unsigned int bCreateVisibleOrdnance : 1;
		unsigned int bExplosionBasedOnImpact : 1;
		unsigned int bAddSmokeOnExplosion : 1;
		unsigned int bInstantKillInMP : 1;
		unsigned int bHigherBreakForce : 1;
		unsigned int bCanBeUsedAsDriveBy : 1;
		unsigned int bHeavyWeaponUsesRifleAnims : 1;
		unsigned int bMissionCanForceDriveByUse : 1;
		unsigned int bDontRumbleWhenDoingDriveBy : 1;
	} m_nWeaponFlags;										// 020-024
	uint32_t m_nModelHash;									// 024-028
	uint32_t m_nAnimation;									// 028-02C
	float m_fFireRate;										// 02C-030
	float m_fBlindFireRate;									// 030-034
	float m_fAccuracy;										// 034-038
	float m_fAccuracyFPS;									// 038-03C
	uint8_t pad[0x4];										// 03C-040
	Native_CVector_pad m_vOffset;							// 040-050
	Native_CVector_pad m_vCrouchOffset;						// 050-060
	float m_fAimingPitch;									// 060-064
	float m_fReticuleStanding;								// 064-068
	float m_fReticuleDucked;								// 068-06C
	float m_fReticuleScale;									// 06C-070
	uint32_t m_nRumbleDuration;								// 070-074
	float m_fRumbleIntensity;								// 074-078
	uint32_t m_nPickupRegenTime;							// 078-07C
	uint8_t pad2[0x4];										// 07C-080
	uint16_t m_nPickupAmmoOnStreet;							// 080-082
	uint16_t m_nDamage;										// 082-084
	uint16_t m_nDamageFPS;									// 084-086
	uint16_t m_nClipSize;									// 086-088
	uint32_t m_nMaxAmmo;									// 088-08C
	uint32_t m_nTimeBetweenShots;							// 08C-090
	float m_fPhysicsForce;									// 090-094
	uint32_t m_nReloadTimeNormal;							// 094-098
	uint32_t m_nReloadTimeFast;								// 098-09C
	uint32_t m_nReloadTimeCrouch;							// 09C-0A0
	uint32_t m_nProjectileType;								// 0A0-0A4
	uint32_t m_nProjectileFuseTime;							// 0A4-0A8
	uint32_t m_nProjectileToCreate;							// 0A8-0AC
	uint32_t m_nProjectileExplosionType;					// 0AC-0B0
	Native_CVector_pad m_vProjectileOffset;					// 0B0-0C0
	Native_CVector_pad m_vProjectileRotOffset;				// 0C0-0D0
	float m_fProjectilePhysicsExplodeImpactThreshold;		// 0D0-0D4
	float m_fProjectilePhysicsExplodeImpactVehicleThreshold;// 0D4-0D8
	float m_fProjectilePhysicsVehicleVelocity;				// 0D8-0DC
	uint32_t m_nMeleeAnim;									// 0DC-0E0
	uint8_t pad3[0x4];										// 0E0-0E4
	uint32_t m_nMuzzleFx;									// 0E4-0E8
	uint32_t m_nShellFx;									// 0E8-0EC
	uint32_t m_nProjectileTrailFx;							// 0EC-0F0
	float m_fNetworkPlayerMod;								// 0F0-0F4
	float m_fNetworkPedMod;									// 0F4-0F8
	float m_fAimingAccuracyTime;							// 0F8-0FC
	uint32_t m_nAimingPellets;								// 0FC-100
	uint32_t m_nShotsFired;									// 100-104
	uint8_t pad4[0xC];										// 104-110

	static inline char** ms_aWeaponNames = (char**)AddressSetter::Get(0xB27A88, 0xB3ECA8);
	static inline Native_CWeaponInfo* ms_WeaponInfo = (Native_CWeaponInfo*)AddressSetter::Get(0x1140A20, 0xE4A600); // ms_WeaponInfo[60]

	static Native_CWeaponInfo* GetWeaponInfo(uint32_t type)
	{
		return ((Native_CWeaponInfo* (__cdecl*)(uint32_t))(AddressSetter::Get(0x524E80, 0x4DDEB0)))(type);
	}
};
VALIDATE_SIZE(Native_CWeaponInfo, 0x110);

namespace IVSDKDotNet {

	public ref class CWeaponInfo
	{
	public:
		ref class WeaponFlags
		{
		public:
			WeaponFlags(CWeaponInfo^ parent);

			property bool CanAim {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bCanAim; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bCanAim = value; }
			}

			property bool CanAimWithArm {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bCanAimWithArm; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bCanAimWithArm = value; }
			}

			property bool CanFreeAim {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bCanFreeAim; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bCanFreeAim = value; }
			}

			property bool FirstPerson {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bFirstPerson; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bFirstPerson = value; }
			}

			property bool KeepCameraBehind {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bKeepCameraBehind; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bKeepCameraBehind = value; }
			}

			property bool Gun {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bGun; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bGun = value; }
			}

			property bool Thrown {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bThrown; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bThrown = value; }
			}

			property bool Heavy {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bHeavy; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bHeavy = value; }
			}

			property bool Silenced {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bSilenced; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bSilenced = value; }
			}

			property bool MeleeClub {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bMeleeClub; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bMeleeClub = value; }
			}

			property bool MeleeBlade {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bMeleeBlade; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bMeleeBlade = value; }
			}

			property bool ArmourPenetrating {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bArmourPenetrating; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bArmourPenetrating = value; }
			}

			property bool TwoHanded {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.b2Handed; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.b2Handed = value; }
			}

			property bool TreatAsTwoHandedInCover {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bTreatAs2HandedInCover; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bTreatAs2HandedInCover = value; }
			}

			property bool AnimReload {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bAnimReload; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bAnimReload = value; }
			}

			property bool AnimCrouchFire {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bAnimCrouchFire; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bAnimCrouchFire = value; }
			}

			property bool CreateVisibleOrdnance {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bCreateVisibleOrdnance; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bCreateVisibleOrdnance = value; }
			}

			property bool ExplosionBasedOnImpact {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bExplosionBasedOnImpact; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bExplosionBasedOnImpact = value; }
			}

			property bool AddSmokeOnExplosion {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bAddSmokeOnExplosion; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bAddSmokeOnExplosion = value; }
			}

			property bool InstantKillInMP {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bInstantKillInMP; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bInstantKillInMP = value; }
			}

			property bool HigherBreakForce {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bHigherBreakForce; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bHigherBreakForce = value; }
			}

			property bool CanBeUsedAsDriveBy {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bCanBeUsedAsDriveBy; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bCanBeUsedAsDriveBy = value; }
			}

			property bool HeavyWeaponUsesRifleAnims {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bHeavyWeaponUsesRifleAnims; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bHeavyWeaponUsesRifleAnims = value; }
			}

			property bool MissionCanForceDriveByUse {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bMissionCanForceDriveByUse; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bMissionCanForceDriveByUse = value; }
			}

			property bool DontRumbleWhenDoingDriveBy {
				public:
					bool	get()			{ return m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bDontRumbleWhenDoingDriveBy; }
					void	set(bool value) { m_cParent->m_cNativeWeaponInfo->m_nWeaponFlags.bDontRumbleWhenDoingDriveBy = value; }
			}

		private:
			CWeaponInfo^ m_cParent;
		};

	public:
		CWeaponInfo(Native_CWeaponInfo* nativePtr);

		static CWeaponInfo^ GetWeaponInfo(uint32_t type);

		property uint32_t WeaponType {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nWeaponType; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nWeaponType = value; }
		}

		property uint32_t Slot {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nSlot; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nSlot = value; }
		}

		property uint32_t FireType {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nFireType; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nFireType = value; }
		}

		property uint32_t DamageType {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nDamageType; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nDamageType = value; }
		}

		property uint32_t Group {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nGroup; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nGroup = value; }
		}

		property float TargetRange {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fTargetRange; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fTargetRange = value; }
		}

		property float WeaponRange {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fWeaponRange; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fWeaponRange = value; }
		}

		property uint32_t StatType {
			public:
				uint32_t	get() { return m_cNativeWeaponInfo->m_nStatType; }
				void	set(uint32_t value) { m_cNativeWeaponInfo->m_nStatType = value; }
		}

		property WeaponFlags^ TheWeaponFlags {
			public: WeaponFlags^ get() { return m_cWeaponFlags; }
		}

		property uint32_t ModelHash {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nModelHash; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nModelHash = value; }
		}

		property uint32_t Animation {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nAnimation; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nAnimation = value; }
		}

		property float FireRate {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fFireRate; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fFireRate = value; }
		}

		property float BlindFireRate {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fBlindFireRate; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fBlindFireRate = value; }
		}

		property float Accuracy {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fAccuracy; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fAccuracy = value; }
		}

		property float AccuracyFPS {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fAccuracyFPS; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fAccuracyFPS = value; }
		}

		property Vector3 Offset {
			public:
				Vector3 get()
				{
					Native_CVector_pad pad = m_cNativeWeaponInfo->m_vOffset;
					return Vector3(pad.x, pad.y, pad.z);
				}
				void set(Vector3 value)
				{
					Native_CVector_pad pad = m_cNativeWeaponInfo->m_vOffset;
					m_cNativeWeaponInfo->m_vOffset = Native_CVector_pad(pad.flags, value.X, value.Y, value.Z);
				}
		}

		property Vector3 CrouchOffset {
			public:
				Vector3 get()
				{
					Native_CVector_pad pad = m_cNativeWeaponInfo->m_vCrouchOffset;
					return Vector3(pad.x, pad.y, pad.z);
				}
				void set(Vector3 value)
				{
					Native_CVector_pad pad = m_cNativeWeaponInfo->m_vCrouchOffset;
					m_cNativeWeaponInfo->m_vCrouchOffset = Native_CVector_pad(pad.flags, value.X, value.Y, value.Z);
				}
		}

		property float AimingPitch {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fAimingPitch; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fAimingPitch = value; }
		}

		property float ReticuleStanding {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fReticuleStanding; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fReticuleStanding = value; }
		}

		property float ReticuleDucked {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fReticuleDucked; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fReticuleDucked = value; }
		}

		property float ReticuleScale {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fReticuleScale; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fReticuleScale = value; }
		}

		property uint32_t RumbleDuration {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nRumbleDuration; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nRumbleDuration = value; }
		}

		property float RumbleIntensity {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fRumbleIntensity; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fRumbleIntensity = value; }
		}

		property uint32_t PickupRegenTime {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nPickupRegenTime; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nPickupRegenTime = value; }
		}

		property uint16_t PickupAmmoOnStreet {
			public:
				uint16_t	get()				{ return m_cNativeWeaponInfo->m_nPickupAmmoOnStreet; }
				void		set(uint16_t value) { m_cNativeWeaponInfo->m_nPickupAmmoOnStreet = value; }
		}

		property uint16_t Damage {
			public:
				uint16_t	get()				{ return m_cNativeWeaponInfo->m_nDamage; }
				void		set(uint16_t value) { m_cNativeWeaponInfo->m_nDamage = value; }
		}

		property uint16_t DamageFPS {
			public:
				uint16_t	get()				{ return m_cNativeWeaponInfo->m_nDamageFPS; }
				void		set(uint16_t value) { m_cNativeWeaponInfo->m_nDamageFPS = value; }
		}

		property uint16_t ClipSize {
			public:
				uint16_t	get()				{ return m_cNativeWeaponInfo->m_nClipSize; }
				void		set(uint16_t value) { m_cNativeWeaponInfo->m_nClipSize = value; }
		}

		property uint32_t MaxAmmo {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nMaxAmmo; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nMaxAmmo = value; }
		}

		property uint32_t TimeBetweenShots {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nTimeBetweenShots; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nTimeBetweenShots = value; }
		}

		property float PhysicsForce {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fPhysicsForce; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fPhysicsForce = value; }
		}

		property uint32_t ReloadTimeNormal {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nReloadTimeNormal; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nReloadTimeNormal = value; }
		}

		property uint32_t ReloadTimeFast {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nReloadTimeFast; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nReloadTimeFast = value; }
		}

		property uint32_t ReloadTimeCrouch {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nReloadTimeCrouch; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nReloadTimeCrouch = value; }
		}

		property uint32_t ProjectileType {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nProjectileType; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nProjectileType = value; }
		}

		property uint32_t ProjectileFuseTime {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nProjectileFuseTime; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nProjectileFuseTime = value; }
		}

		property uint32_t ProjectileToCreate {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nProjectileToCreate; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nProjectileToCreate = value; }
		}

		property uint32_t ProjectileExplosionType {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nProjectileExplosionType; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nProjectileExplosionType = value; }
		}

		property Vector3 ProjectileOffset {
			public:
				Vector3 get()
				{
					Native_CVector_pad pad = m_cNativeWeaponInfo->m_vProjectileOffset;
					return Vector3(pad.x, pad.y, pad.z);
				}
				void set(Vector3 value)
				{
					Native_CVector_pad pad = m_cNativeWeaponInfo->m_vProjectileOffset;
					m_cNativeWeaponInfo->m_vProjectileOffset = Native_CVector_pad(pad.flags, value.X, value.Y, value.Z);
				}
		}

		property Vector3 ProjectileRotOffset {
			public:
				Vector3 get()
				{
					Native_CVector_pad pad = m_cNativeWeaponInfo->m_vProjectileRotOffset;
					return Vector3(pad.x, pad.y, pad.z);
				}
				void set(Vector3 value)
				{
					Native_CVector_pad pad = m_cNativeWeaponInfo->m_vProjectileRotOffset;
					m_cNativeWeaponInfo->m_vProjectileRotOffset = Native_CVector_pad(pad.flags, value.X, value.Y, value.Z);
				}
		}

		property float ProjectilePhysicsExplodeImpactThreshold {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fProjectilePhysicsExplodeImpactThreshold; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fProjectilePhysicsExplodeImpactThreshold = value; }
		}

		property float ProjectilePhysicsExplodeImpactVehicleThreshold {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fProjectilePhysicsExplodeImpactVehicleThreshold; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fProjectilePhysicsExplodeImpactVehicleThreshold = value; }
		}

		property float ProjectilePhysicsVehicleVelocity {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fProjectilePhysicsVehicleVelocity; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fProjectilePhysicsVehicleVelocity = value; }
		}

		property uint32_t MeleeAnim {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nMeleeAnim; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nMeleeAnim = value; }
		}

		property uint32_t MuzzleFx {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nMuzzleFx; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nMuzzleFx = value; }
		}

		property uint32_t ShellFx {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nShellFx; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nShellFx = value; }
		}

		property uint32_t ProjectileTrailFx {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nProjectileTrailFx; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nProjectileTrailFx = value; }
		}

		property float NetworkPlayerMod {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fNetworkPlayerMod; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fNetworkPlayerMod = value; }
		}

		property float NetworkPedMod {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fNetworkPedMod; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fNetworkPedMod = value; }
		}

		property float AimingAccuracyTime {
			public:
				float	get()				{ return m_cNativeWeaponInfo->m_fAimingAccuracyTime; }
				void	set(float value)	{ m_cNativeWeaponInfo->m_fAimingAccuracyTime = value; }
		}

		property uint32_t AimingPellets {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nAimingPellets; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nAimingPellets = value; }
		}

		property uint32_t ShotsFired {
			public:
				uint32_t	get()				{ return m_cNativeWeaponInfo->m_nShotsFired; }
				void		set(uint32_t value) { m_cNativeWeaponInfo->m_nShotsFired = value; }
		}

		property Native_CWeaponInfo* WeaponInfoPointer {
			public:
				Native_CWeaponInfo* get()							{ return m_cNativeWeaponInfo; }
				void				set(Native_CWeaponInfo* value)	{ m_cNativeWeaponInfo = value; }
		}

	private:
		Native_CWeaponInfo* m_cNativeWeaponInfo;
		WeaponFlags^ m_cWeaponFlags;
	};

}