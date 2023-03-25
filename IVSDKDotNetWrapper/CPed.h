#pragma once

class CPhysical;
class CPedIntelligenceNY;
class CPlayerInfo;
class CPedDataNY;
//class CObject;
//class CVehicle;
namespace rage { class rmcDrawable; }

class CCustomShaderEffectPedBoneDamageFX : public CCustomShaderEffectBase
{
public:
	uint8_t pad[0x20];													// 000-020
	float m_fDamage[64];												// 020-??? todo: check CCustomShaderEffectPedBoneDamageFX::Update to get a count
	uint8_t pad2[0x250];												// 120-370

	// nop the Update function to test the damage values
};
VALIDATE_SIZE(CCustomShaderEffectPedBoneDamageFX, 0x370);
VALIDATE_OFFSET(CCustomShaderEffectPedBoneDamageFX, m_fDamage, 0x20);

class Native_CPedMoveBlendOnFoot
{
public:
	uint8_t pad[0x8];													// 00-08
	float m_fMoveState;													// 08-0C 3 - sprint, 2 - run, 1 - walk
	uint8_t pad1[0x10];													// 0C-1C
	float m_fMoveLeanAmount;											// 1C-20 3 is normal, less than 3 leans left, more than 3 leans right
	uint8_t pad2[0x4];													// 20-28
	Native_CPed* m_pPed;												// 24-28
	float m_fMoveTurn;													// 28-2C
	uint8_t pad3[0x24];													// 2C-50
	uint32_t m_nUnkFlags;												// 50-54
	uint8_t pad4[0x18];													// 54-6C
	float m_fMoveAnimSpeed;												// 6C-70
	float m_fMaxMoveBlendRatio;											// 70-74 caps m_fMoveState
	uint8_t pad5[0x5C];													// 74-D0
};
VALIDATE_SIZE(Native_CPedMoveBlendOnFoot, 0xD0);
VALIDATE_OFFSET(Native_CPedMoveBlendOnFoot, m_fMoveState, 0x8);
VALIDATE_OFFSET(Native_CPedMoveBlendOnFoot, m_fMoveLeanAmount, 0x1C);
VALIDATE_OFFSET(Native_CPedMoveBlendOnFoot, m_pPed, 0x24);
VALIDATE_OFFSET(Native_CPedMoveBlendOnFoot, m_fMoveTurn, 0x28);
VALIDATE_OFFSET(Native_CPedMoveBlendOnFoot, m_fMoveAnimSpeed, 0x6C);

struct Native_PedWeaponSlot
{
	uint32_t m_nType;													// 00-04
	uint32_t* m_pAmmo;													// 04-08
	uint8_t m_nHasModelLoaded;											// 08-09
	uint8_t pad[0x3];													// 09-0C
};

struct Native_PedWeapons
{
	uint8_t weaponspad1[0x18];											// 00-18 CPed 2B0-2C8
	uint32_t m_nActiveWeaponSlot;										// 18-1C CPed 2C8-2CC
	uint8_t weaponspad2[0x10];											// 1C-2C CPed 2CC-2DC
	Native_CObject* m_pWeaponObject;									// 2C-30 CPed 2DC-2E0
	uint8_t weaponspad3[0xC];											// 30-3C CPed 2E0-388
	Native_PedWeaponSlot m_aWeapons[12];								// 3C-CC CPed 2EC-37C
};
VALIDATE_SIZE(Native_PedWeapons, 0xCC);
VALIDATE_OFFSET(Native_PedWeapons, m_nActiveWeaponSlot, 0x18);
VALIDATE_OFFSET(Native_PedWeapons, m_pWeaponObject, 0x2C);
VALIDATE_OFFSET(Native_PedWeapons, m_aWeapons, 0x3C);

// incomplete - needs props
struct tPedDrawableInfo
{
	uint8_t pad[0x5C];														// 000-05C
	uint8_t m_nDrawables[11];												// 05C-067
	uint8_t m_nTextures[11];												// 067-072
	uint8_t pad2[0xBA];														// 072-12C
	uint32_t m_nPedType;													// 12C-130
};
VALIDATE_OFFSET(tPedDrawableInfo, m_nDrawables, 0x5C);
VALIDATE_OFFSET(tPedDrawableInfo, m_nTextures, 0x67);
VALIDATE_OFFSET(tPedDrawableInfo, m_nPedType, 0x12C);

struct tPedComponentModels
{
	rage::rmcDrawable* m_pDrawables[11];						// 00-2C
	uint8_t pad[0x2C];											// 2C-58
	CCustomShaderEffectPedBoneDamageFX* m_pPedBoneDamageFX;		// 58-5C
	uint8_t pad2[0x6];											// 5C-62
};
VALIDATE_OFFSET(tPedComponentModels, m_pPedBoneDamageFX, 0x58);

class Native_CPed : public Native_CPhysical
{
public:																	// 000-210
	uint8_t m_bDead;													// 210-211
	uint8_t m_bInjured;													// 211-212
	uint8_t m_bFatallyInjured;											// 212-213
	uint8_t pad1;														// 213-214
	float m_fPedHealth;													// 214-218
	uint8_t m_nPlayerIndex;												// 218-219
	uint8_t m_bIsPlayer;												// 219-21A
	uint8_t pad2[0x2];													// 21A-21C
	tPedDrawableInfo* m_pDrawableInfo;									// 21C-220
	uint8_t pad3[0x4];													// 220-224
	CPedIntelligenceNY* m_pPedIntelligence;								// 224-228
	Native_CPlayerInfo* m_pPlayerInfo;									// 228-22C
	CPedDataNY* m_pPedData;												// 22C-230
	uint8_t pad4[0x30];													// 230-260
	struct
	{
		unsigned int pad : 2;
		unsigned int bNoHeadshots : 1;
		unsigned int pad2 : 29;
	} m_nPedFlags;										// 260-264
	uint8_t pad5[0x8];													// 264-26C
	struct
	{
		unsigned int pad : 3;
		unsigned int bInCar : 1;
		unsigned int pad2 : 9;
		unsigned int bInAir : 1;
		unsigned int pad3 : 18;
	} m_nPedFlags2;										// 26C-270
	uint8_t pad6[0x8];													// 270-278
	float m_fClimbAnimRate;												// 278-27C
	uint8_t pad7[0x34];													// 27C-2B0
	Native_PedWeapons m_pWeaponData;									// 2B0-37C
	uint8_t pad8[0xC];													// 37C-388
	uint8_t m_nShootRate;												// 388-389
	uint8_t m_nAccuracy;												// 389-38A
	uint8_t pad9[0xFA];													// 38A-484
	Native_CEntity* m_pStandingOnEntity;								// 484-488
	uint8_t pad10[0x194];												// 488-61C
	uint32_t m_nVoiceHash;												// 61C-620
	uint8_t pad11[0x19C];												// 620-7BC
	rage::phConstrainedCollider* m_pCollider;							// 7BC-7C0
	uint8_t pad12[0x8];													// 7C0-7C8
	uint32_t m_nRagdollStatus;											// 7C8-7CC
	uint32_t m_nRagdollTime;											// 7CC-7D0
	uint8_t pad13[0x21];												// 7D0-7F1
	uint8_t m_nWeaponObjectVisible;										// 7F1-7F2
	uint8_t pad14[0x27E];												// 7F2-A90
	uint8_t m_nCreatedBy;												// A70-A74
	uint8_t pad15[0x10];												// A74-A84
	uint32_t m_nDeathState;												// A84-A88
	uint8_t pad16[0x8];													// A88-A90
	Native_CPedMoveBlendOnFoot* m_pPedMoveBlendOnFoot;					// A90-A94
	float m_fMaxHealth;													// A94-A98
	uint8_t pad17[0x18];												// A98-AB0
	float m_fCurrentHeading;											// AB0-AB4
	float m_fDesiredHeading;											// AB4-AB8
	uint8_t pad18[0x88];												// AB8-B40
	Native_CVehicle* m_pVehicle;										// B40-B44
	uint8_t pad19[0x33C];												// B44-E80
	uint32_t m_nUnkPlayerSettingsRelated;								// E80-E84 used in CTaskComplexPlayerSettingsTask, initialized as *(dword_14CB008 + 32)
	uint8_t pad20[0x24];												// E84-EA8
	tPedComponentModels* m_pComponentModels;							// EA8-EAC
	uint8_t pad21[0x54];												// EAC-F00

	void ProcessWeaponSwitch()
	{
		((void(__thiscall*)(Native_CPed*))(AddressSetter::Get(0x5BE7D0, 0x597180)))(this);
	}
	CPad* GetPadFromPlayer()
	{
		return ((CPad*(__thiscall*)(Native_CPed*))(AddressSetter::Get(0x5BE5D0, 0x596F80)))(this);
	}
	Native_CVehicle* GetVehicle()
	{
		return ((Native_CVehicle * (__thiscall*)(Native_CPed*))(AddressSetter::Get(0x26AB0, 0x9FBA0)))(this);
	}
	void SetHealth(float health, int unk)
	{
		((void(__thiscall*)(Native_CPed*, float, int))(*(void***)this)[61])(this, health, unk);
	}
	void AddHealth(float health)
	{
		((void(__thiscall*)(Native_CPed*, float))(*(void***)this)[62])(this, health);
	}
	void ProcessHeading()
	{
		((void(__thiscall*)(Native_CPed*))(AddressSetter::Get(0x4A28B0, 0x53F9E0)))(this);
	}
};
VALIDATE_SIZE(Native_CPed, 0xF00);
VALIDATE_OFFSET(Native_CPed, m_pCollider, 0x7BC);
VALIDATE_OFFSET(Native_CPed, m_fClimbAnimRate, 0x278);
VALIDATE_OFFSET(Native_CPed, m_nDeathState, 0xA84);
VALIDATE_OFFSET(Native_CPed, m_nCreatedBy, 0xA70);
VALIDATE_OFFSET(Native_CPed, m_nPlayerIndex, 0x218);
VALIDATE_OFFSET(Native_CPed, m_nRagdollStatus, 0x7C8);
VALIDATE_OFFSET(Native_CPed, m_nWeaponObjectVisible, 0x7F1);
VALIDATE_OFFSET(Native_CPed, m_fMaxHealth, 0xA94);
VALIDATE_OFFSET(Native_CPed, m_fCurrentHeading, 0xAB0);
VALIDATE_OFFSET(Native_CPed, m_fDesiredHeading, 0xAB4);
VALIDATE_OFFSET(Native_CPed, m_pVehicle, 0xB40);
VALIDATE_OFFSET(Native_CPed, m_pDrawableInfo, 0x21C);
VALIDATE_OFFSET(Native_CPed, m_nShootRate, 0x388);
VALIDATE_OFFSET(Native_CPed, m_nAccuracy, 0x389);
VALIDATE_OFFSET(Native_CPed, m_pPedMoveBlendOnFoot, 0xA90);
VALIDATE_OFFSET(Native_CPed, m_pComponentModels, 0xEA8);
VALIDATE_OFFSET(Native_CPed, m_nVoiceHash, 0x61C);
VALIDATE_OFFSET(Native_CPed, m_pStandingOnEntity, 0x484);
VALIDATE_OFFSET(Native_CPed, m_pWeaponData, 0x2B0);
VALIDATE_OFFSET(Native_CPed, m_nUnkPlayerSettingsRelated, 0xE80);

namespace IVSDKDotNet {

	public ref class PedWeaponSlot
	{
	public:
		PedWeaponSlot(Native_PedWeaponSlot* nativePtr);

		property uint32_t Type {
			public:
				uint32_t	get()				{ return PedWeaponSlotPointer->m_nType; }
				void		set(uint32_t value) { PedWeaponSlotPointer->m_nType = value; }
		}

		// TODO: Look into this.
		property uint32_t Ammo {
			public:
				uint32_t get() {
					return *PedWeaponSlotPointer->m_pAmmo;
				}
				void set(uint32_t value) { PedWeaponSlotPointer->m_pAmmo = &value; }
		} 

		property uint8_t HasModelLoaded {
			public:
				uint8_t	get() { return PedWeaponSlotPointer->m_nHasModelLoaded; }
		}

		property Native_PedWeaponSlot* PedWeaponSlotPointer {
			public:
				Native_PedWeaponSlot*	get()								{ return m_cNativePedWeaponSlot; }
				void					set(Native_PedWeaponSlot* value)	{ m_cNativePedWeaponSlot = value; }
		}

	private:
		Native_PedWeaponSlot* m_cNativePedWeaponSlot;
	};

	public ref class PedWeapons
	{
	public:
		PedWeapons(Native_PedWeapons* nativePtr);

		property uint32_t ActiveWeaponSlot {
			public:
				uint32_t	get()				{ return PedWeaponsPointer->m_nActiveWeaponSlot; }
				void		set(uint32_t value) { PedWeaponsPointer->m_nActiveWeaponSlot = value; }
		}

		property CObject^ WeaponObject {
			public:
				CObject^	get()				{ return gcnew CObject(PedWeaponsPointer->m_pWeaponObject); }
				void		set(CObject^ value) { PedWeaponsPointer->m_pWeaponObject = value->ObjectPointer; }
		}

		property array<PedWeaponSlot^>^ Weapons {
			public:
				array<PedWeaponSlot^>^ get()
				{
					array<PedWeaponSlot^>^ arr = gcnew array<PedWeaponSlot^>(12);

					for (int i = 0; i < arr->Length; i++)
					{
						arr[i] = gcnew PedWeaponSlot(&PedWeaponsPointer->m_aWeapons[i]);
					}

					return arr;
				}
				void set(array<PedWeaponSlot^>^ value)
				{
					for (int i = 0; i < value->Length; i++)
					{
						PedWeaponsPointer->m_aWeapons[i] = *value[i]->PedWeaponSlotPointer;
					}
				}
		}

		property Native_PedWeapons* PedWeaponsPointer {
			public:
				Native_PedWeapons*	get()							{ return m_cNativePedWeapons; }
				void				set(Native_PedWeapons* value)	{ m_cNativePedWeapons = value; }
		}

	private:
		Native_PedWeapons* m_cNativePedWeapons;
	};

	public ref class CPedMoveBlendOnFoot
	{
	public:
		CPedMoveBlendOnFoot(Native_CPedMoveBlendOnFoot* nativePtr);

		/// <summary>
		/// Move states: 0 - Stopped, 1 - Walk, 2 - Run, 3 - Sprint.
		/// </summary>
		property float MoveState {
			public:
				float	get()				{ return Pointer->m_fMoveState; }
				void	set(float value)	{ Pointer->m_fMoveState = value; }
		}

		/// <summary>
		/// 3 is normal, less than 3 leans left, more than 3 leans right.
		/// </summary>
		property float MoveLeanAmount {
			public:
				float	get()				{ return Pointer->m_fMoveLeanAmount; }
				void	set(float value)	{ Pointer->m_fMoveLeanAmount = value; }
		}

		property UIntPtr Ped {
			public:
				UIntPtr get() {
					Native_CPed* ped = Pointer->m_pPed;

					if (!ped)
						return UIntPtr::Zero;

					return UIntPtr(ped);
				}
				void set(UIntPtr value) { Pointer->m_pPed = (Native_CPed*)value.ToPointer(); }
		}

		property float MoveTurn {
			public:
				float	get()				{ return Pointer->m_fMoveTurn; }
				void	set(float value)	{ Pointer->m_fMoveTurn = value; }
		}

		property uint32_t UnkFlags {
			public:
				uint32_t	get()				{ return Pointer->m_nUnkFlags; }
				void		set(uint32_t value) { Pointer->m_nUnkFlags = value; }
		}

		property float MoveAnimSpeed {
			public:
				float	get()				{ return Pointer->m_fMoveAnimSpeed; }
				void	set(float value)	{ Pointer->m_fMoveAnimSpeed = value; }
		}

		/// <summary>
		///	Caps MoveState.
		/// </summary>
		property float MaxMoveBlendRatio {
			public:
				float	get()				{ return Pointer->m_fMaxMoveBlendRatio; }
				void	set(float value)	{ Pointer->m_fMaxMoveBlendRatio = value; }
		}

		property Native_CPedMoveBlendOnFoot* Pointer {
			public:
				Native_CPedMoveBlendOnFoot* get()									{ return m_cNativeCPedMoveBlendOnFoot; }
				void						set(Native_CPedMoveBlendOnFoot* value)	{ m_cNativeCPedMoveBlendOnFoot = value; }
		}

	private:
		Native_CPedMoveBlendOnFoot* m_cNativeCPedMoveBlendOnFoot;
	};

	public ref class CPed : CPhysical
	{
	public:
		CPed(Native_CPed* nativePtr);

		static CPed^ FromPointer(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		property bool Dead {
			public:
				bool	get()			{ return PedPointer->m_bDead; }
				void	set(bool value)	{ PedPointer->m_bDead = value; }
		}

		property bool Injured {
			public:
				bool	get()			{ return PedPointer->m_bInjured; }
				void	set(bool value)	{ PedPointer->m_bInjured = value; }
		}

		property bool FatallyInjured {
			public:
				bool	get()			{ return PedPointer->m_bFatallyInjured; }
				void	set(bool value)	{ PedPointer->m_bFatallyInjured = value; }
		}

		property uint8_t pad1 {
			public:
				uint8_t get()				{ return PedPointer->pad1; }
				void	set(uint8_t value)	{ PedPointer->pad1 = value; }
		}

		property float PedHealth {
			public:
				float	get()				{ return PedPointer->m_fPedHealth; }
				void	set(float value)	{ PedPointer->m_fPedHealth = value; }
		}

		property uint8_t PlayerIndex {
			public:
				uint8_t get()				{ return PedPointer->m_nPlayerIndex; }
				void	set(uint8_t value)	{ PedPointer->m_nPlayerIndex = value; }
		}

		property bool IsPlayer {
			public:
				bool	get()			{ return PedPointer->m_bIsPlayer; }
				void	set(bool value)	{ PedPointer->m_bIsPlayer = value; }
		}

	//	property uint8_t m_pPlayerInfo {
	//public:
	//	uint8_t get() {}
	//	void set(uint8_t value) {}
	//	}

		property float ClimbAnimRate {
			public:
				float	get()				{ return PedPointer->m_fClimbAnimRate; }
				void	set(float value)	{ PedPointer->m_fClimbAnimRate = value; }
		}

		property PedWeapons^ m_pWeaponData {
			public:
				PedWeapons^ get()
				{
					return gcnew PedWeapons(&PedPointer->m_pWeaponData);
				}
				//void	set(float value)	{ PedPointer->m_pWeaponData = value; }
		}

		property uint8_t ShootRate {
			public:
				uint8_t get()				{ return PedPointer->m_nShootRate; }
				void	set(uint8_t value)	{ PedPointer->m_nShootRate = value; }
		}

		property uint8_t Accuracy {
			public:
				uint8_t get()				{ return PedPointer->m_nAccuracy; }
				void	set(uint8_t value)	{ PedPointer->m_nAccuracy = value; }
		}

		property CEntity^ StandingOnEntity {
			public:
				CEntity^ get() {
					Native_CEntity* ent = PedPointer->m_pStandingOnEntity;

					if (!ent)
						return nullptr;

					return gcnew CEntity(ent);
				}
				void set(CEntity^ value) { PedPointer->m_pStandingOnEntity = value->EntityPointer; }
		}

		property uint32_t VoiceHash {
			public:
				uint32_t	get()				{ return PedPointer->m_nVoiceHash; }
				void		set(uint32_t value) { PedPointer->m_nVoiceHash = value; }
		}

		property uint32_t RagdollStatus {
			public:
				uint32_t	get()				{ return PedPointer->m_nRagdollStatus; }
				void		set(uint32_t value) { PedPointer->m_nRagdollStatus = value; }
		}

		property uint32_t RagdollTime {
			public:
				uint32_t	get()				{ return PedPointer->m_nRagdollTime; }
				void		set(uint32_t value) { PedPointer->m_nRagdollTime = value; }
		}

		property uint8_t WeaponObjectVisible {
			public:
				uint8_t get()				{ return PedPointer->m_nWeaponObjectVisible; }
				void	set(uint8_t value)	{ PedPointer->m_nWeaponObjectVisible = value; }
		}

		property uint8_t CreatedBy {
				public:
					uint8_t get()				{ return PedPointer->m_nCreatedBy; }
					void	set(uint8_t value)	{ PedPointer->m_nCreatedBy = value; }
		}

		property uint32_t DeathState {
			public:
				uint32_t	get()				{ return PedPointer->m_nDeathState; }
				void		set(uint32_t value) { PedPointer->m_nDeathState = value; }
		}

		property CPedMoveBlendOnFoot^ PedMoveBlendOnFoot {
			public:
				CPedMoveBlendOnFoot^ get() { 
					Native_CPedMoveBlendOnFoot* ptr = m_cNativePed->m_pPedMoveBlendOnFoot;

					if (!ptr)
						return nullptr;

					return gcnew CPedMoveBlendOnFoot(ptr);
				}
				void set(CPedMoveBlendOnFoot^ value) { m_cNativePed->m_pPedMoveBlendOnFoot = value->Pointer; }
		}

		property float MaxHealth {
			public:
				float	get()				{ return PedPointer->m_fMaxHealth; }
				void	set(float value)	{ PedPointer->m_fMaxHealth = value; }
		}

		property float CurrentHeading {
			public:
				float	get()				{ return PedPointer->m_fCurrentHeading; }
				void	set(float value)	{ PedPointer->m_fCurrentHeading = value; }
		}

		property float DesiredHeading {
			public:
				float	get()				{ return PedPointer->m_fDesiredHeading; }
				void	set(float value)	{ PedPointer->m_fDesiredHeading = value; }
		}

		property CVehicle^ Vehicle {
			public:
				CVehicle^ get() {
					Native_CVehicle* veh = PedPointer->m_pVehicle;

					if (!veh)
						return nullptr;

					return gcnew CVehicle(veh);
				}
				void set(CVehicle^ value) { PedPointer->m_pVehicle = value->VehiclePointer; }
		}

		///	<summary>
		///	Used in CTaskComplexPlayerSettingsTask, initialized as *(dword_14CB008 + 32).
		/// </summary>
		property uint32_t UnkPlayerSettingsRelated {
			public:
				uint32_t	get()				{ return PedPointer->m_nUnkPlayerSettingsRelated; }
				void		set(uint32_t value) { PedPointer->m_nUnkPlayerSettingsRelated = value; }
		}

		property Native_CPed* PedPointer {
			public:
				Native_CPed*	get()					{ return m_cNativePed; }
				void			set(Native_CPed* value)	{ m_cNativePed = value; }
		}

		void ProcessWeaponSwitch();
		//CPad* GetPadFromPlayer();
		CVehicle^ GetVehicle();
		void SetHealth(float health, int unk);
		void AddHealth(float health);
		void ProcessHeading();

	private:
		Native_CPed* m_cNativePed;

	};

}