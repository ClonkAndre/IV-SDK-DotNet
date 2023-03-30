#pragma once

class Native_CPed;
class Native_CVehicle;

class Native_CPlayerInfo
{
public:
	uint8_t pad[0x4C];													// 000-04C
	char m_sName[20];													// 04C-060
	uint8_t pad2[0x390];												// 060-3F0
	Native_CPed* m_pPlayerPed2;											// 3F0-3F4
	uint8_t pad3[0x20];													// 3F4-414
	float m_fStamina;													// 414-418
	uint8_t pad3_[0x7C];												// 418-494
	uint32_t m_nLastHitPedTime;											// 494-498
	uint32_t m_nLastHitBuildingTime;									// 498-49C
	uint32_t m_nLastHitObjectTime;										// 49C-4A0
	uint32_t m_nLastDroveOnPavementTime;								// 4A0-4A4
	uint32_t m_nLastRanLightTime;										// 4A4-4A8
	uint32_t m_nLastDroveAgainstTrafficTime;							// 4A8-4AC
	uint8_t pad4[0x10];													// 4AC-4BC
	uint32_t m_nControlFlags;											// 4BC-4C0
	uint8_t pad5[0x1A];													// 4AC-4DA
	uint8_t m_nPlayerId;												// 4DA-4DB
	uint8_t pad6;														// 4DB-4DC
	uint32_t m_nState;													// 4DC-4E0 2: joined game 6: left
	uint8_t pad7[0x66];													// 4E0-546
	// 46C: another playerped but this time its networked
	uint8_t m_nNeverTired;												// 546-547
	uint8_t pad8[0x3];													// 547-54A
	uint16_t m_nMaxHealth;												// 54A-54C
	uint16_t m_nMaxArmor;												// 54C-54E
	uint8_t pad9[0x2];													// 54E-550
	uint8_t m_nCanDoDriveby;											// 550-551
	uint8_t pad10[0xB];													// 551-55C
	uint32_t m_nMood;													// 55C-560
	uint8_t pad11[0x10];												// 560-570
	int32_t m_nColour;													// 570-574
	int32_t m_nTeam;													// 574-578
	uint8_t pad12[0x8];													// 578-580
	uint8_t m_nHasDiedRecently;											// 580-581
	uint8_t pad13[0xB];													// 581-58C
	Native_CPed* m_pPlayerPed;											// 58C-590
	uint8_t pad14[0x4];													// 590-594
	Native_CVehicle* m_pOnlyEnterThisVehicle;							// 594-598
	uint8_t pad15[0x28];												// 598-5C0

	void KillPlayerOutsideWorld()
	{
		((void(__thiscall*)(Native_CPlayerInfo*))(AddressSetter::Get(0x478F7D, 0x4B59D0)))(this);
	}

	static bool IsPlayerActive(int id)
	{
		return ((bool(__cdecl*)(int))(AddressSetter::Get(0x75E230, 0x70B010)))(id);
	}
	static Native_CPlayerInfo* GetPlayerInfo(uint32_t nPlayerId)
	{
		return ((Native_CPlayerInfo*(__cdecl*)(uint32_t))(AddressSetter::Get(0x417F20, 0x3CD210)))(nPlayerId);
	}

	static Native_CVector& FindPlayerCentreOfWorld(Native_CVector* v)
	{
		return ((Native_CVector&(__cdecl*)(Native_CVector*))(AddressSetter::Get(0x418100, 0x3CD3F0)))(v);
	}
	static uint32_t FindPlayerPed()
	{
		return ((uint32_t(__cdecl*)())(AddressSetter::Get(0x417F40, 0x3CD230)))();
	}
	static uint32_t FindPlayerVehicle()
	{
		return ((uint32_t(__cdecl*)())(AddressSetter::Get(0x478890, 0x4B52F0)))(); // Original line
	}

};
VALIDATE_SIZE(Native_CPlayerInfo, 0x5C0);
VALIDATE_OFFSET(Native_CPlayerInfo, m_fStamina, 0x414);
VALIDATE_OFFSET(Native_CPlayerInfo, m_sName, 0x4C);
VALIDATE_OFFSET(Native_CPlayerInfo, m_nLastHitPedTime, 0x494);
VALIDATE_OFFSET(Native_CPlayerInfo, m_nPlayerId, 0x4DA);
VALIDATE_OFFSET(Native_CPlayerInfo, m_nState, 0x4DC);
VALIDATE_OFFSET(Native_CPlayerInfo, m_nNeverTired, 0x546);
VALIDATE_OFFSET(Native_CPlayerInfo, m_nMaxHealth, 0x54A);
VALIDATE_OFFSET(Native_CPlayerInfo, m_nCanDoDriveby, 0x550);
VALIDATE_OFFSET(Native_CPlayerInfo, m_nMood, 0x55C);
VALIDATE_OFFSET(Native_CPlayerInfo, m_nTeam, 0x574);
VALIDATE_OFFSET(Native_CPlayerInfo, m_pPlayerPed, 0x58C);
VALIDATE_OFFSET(Native_CPlayerInfo, m_nControlFlags, 0x4BC);

namespace IVSDKDotNet {

	public ref class CPlayerInfo
	{
	public:
		CPlayerInfo(Native_CPlayerInfo* nativePtr);

		static CPlayerInfo^ FromPointer(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		property String^ Name {
			public: String^ get() { return gcnew String(m_cNativePlayerInfo->m_sName); }
		}

		property UIntPtr PlayerPed2 {
			public:
				UIntPtr	get()
				{
					Native_CPed* ptr = m_cNativePlayerInfo->m_pPlayerPed2;

					if (ptr)
						return UIntPtr(ptr);
					
					return UIntPtr::Zero;
				}
				void	set(UIntPtr value)	{ m_cNativePlayerInfo->m_pPlayerPed2 = (Native_CPed*)value.ToPointer(); }
		}

		property float Stamina {
			public:
				float	get()				{ return m_cNativePlayerInfo->m_fStamina; }
				void	set(float value)	{ m_cNativePlayerInfo->m_fStamina = value; }
		}

		property uint32_t LastHitPedTime {
			public:
				uint32_t	get()				{ return m_cNativePlayerInfo->m_nLastHitPedTime; }
				void		set(uint32_t value) { m_cNativePlayerInfo->m_nLastHitPedTime = value; }
		}

		property uint32_t LastHitBuildingTime {
			public:
				uint32_t	get()				{ return m_cNativePlayerInfo->m_nLastHitBuildingTime;  }
				void		set(uint32_t value) { m_cNativePlayerInfo->m_nLastHitBuildingTime = value; }
		}

		property uint32_t LastHitObjectTime {
			public:
				uint32_t	get()				{ return m_cNativePlayerInfo->m_nLastHitObjectTime; }
				void		set(uint32_t value) { m_cNativePlayerInfo->m_nLastHitObjectTime = value; }
		}

		property uint32_t LastDroveOnPavementTime {
			public:
				uint32_t	get()				{ return m_cNativePlayerInfo->m_nLastDroveOnPavementTime; }
				void		set(uint32_t value) { m_cNativePlayerInfo->m_nLastDroveOnPavementTime = value; }
		}

		property uint32_t LastRanLightTime {
			public:
				uint32_t	get()				{ return m_cNativePlayerInfo->m_nLastRanLightTime; }
				void		set(uint32_t value) { m_cNativePlayerInfo->m_nLastRanLightTime = value; }
		}

		property uint32_t LastDroveAgainstTrafficTime {
			public:
				uint32_t	get()				{ return m_cNativePlayerInfo->m_nLastDroveAgainstTrafficTime; }
				void		set(uint32_t value) { m_cNativePlayerInfo->m_nLastDroveAgainstTrafficTime = value; }
		}

		property uint32_t ControlFlags {
			public:
				uint32_t	get()				{ return m_cNativePlayerInfo->m_nControlFlags; }
				void		set(uint32_t value) { m_cNativePlayerInfo->m_nControlFlags = value; }
		}

		property uint8_t PlayerId {
			public:
				uint8_t get()				{ return m_cNativePlayerInfo->m_nPlayerId; }
				void	set(uint8_t value)	{ m_cNativePlayerInfo->m_nPlayerId = value; }
		}

		property uint8_t pad6 {
			public:
				uint8_t get()				{ return m_cNativePlayerInfo->pad6; }
				void	set(uint8_t value)	{ m_cNativePlayerInfo->pad6 = value; }
		}

		property uint32_t State {
			public:
				uint32_t	get()				{ return m_cNativePlayerInfo->m_nState; }
				void		set(uint32_t value) { m_cNativePlayerInfo->m_nState = value; }
		}

		property uint8_t NeverTired {
			public:
				uint8_t get()				{ return m_cNativePlayerInfo->m_nNeverTired; }
				void	set(uint8_t value)	{ m_cNativePlayerInfo->m_nNeverTired = value; }
		}

		property uint16_t MaxHealth {
			public:
				uint16_t	get()				{ return m_cNativePlayerInfo->m_nMaxHealth; }
				void		set(uint16_t value) { m_cNativePlayerInfo->m_nMaxHealth = value; }
		}

		property uint16_t MaxArmor {
			public:
				uint16_t	get()				{ return m_cNativePlayerInfo->m_nMaxArmor; }
				void		set(uint16_t value) { m_cNativePlayerInfo->m_nMaxArmor = value; }
		}

		property uint8_t CanDoDriveby {
			public:
				uint8_t get()				{ return m_cNativePlayerInfo->m_nCanDoDriveby; }
				void	set(uint8_t value)	{ m_cNativePlayerInfo->m_nCanDoDriveby = value; }
		}

		property uint32_t Mood {
			public:
				uint32_t	get()				{ return m_cNativePlayerInfo->m_nMood; }
				void		set(uint32_t value) { m_cNativePlayerInfo->m_nMood = value; }
		}

		property int32_t Colour {
			public:
				int32_t get()				{ return m_cNativePlayerInfo->m_nColour; }
				void	set(int32_t value)	{ m_cNativePlayerInfo->m_nColour = value; }
		}

		property int32_t Team {
			public:
				int32_t get()				{ return m_cNativePlayerInfo->m_nTeam; }
				void	set(int32_t value)	{ m_cNativePlayerInfo->m_nTeam = value; }
		}

		property uint8_t HasDiedRecently {
			public:
				uint8_t get()				{ return m_cNativePlayerInfo->m_nHasDiedRecently; }
				void	set(uint8_t value)	{ m_cNativePlayerInfo->m_nHasDiedRecently = value; }
		}

		property UIntPtr PlayerPed {
			public:
				UIntPtr	get()
				{
					Native_CPed* ptr = m_cNativePlayerInfo->m_pPlayerPed;

					if (ptr)
						return UIntPtr(ptr);

					return UIntPtr::Zero;
				}
				void	set(UIntPtr value)	{ m_cNativePlayerInfo->m_pPlayerPed = (Native_CPed*)value.ToPointer(); }
		}

		property UIntPtr OnlyEnterThisVehicle {
			public:
				UIntPtr	get()
				{
					Native_CVehicle* ptr = m_cNativePlayerInfo->m_pOnlyEnterThisVehicle;

					if (ptr)
						return UIntPtr(ptr);

					return UIntPtr::Zero;
				}
				void	set(UIntPtr value)	{ m_cNativePlayerInfo->m_pOnlyEnterThisVehicle = (Native_CVehicle*)value.ToPointer(); }
		}

		property Native_CPlayerInfo* PlayerInfoPointer {
			public:
				Native_CPlayerInfo* get()							{ return m_cNativePlayerInfo; }
				void				set(Native_CPlayerInfo* value)	{ m_cNativePlayerInfo = value; }
		}

		void KillPlayerOutsideWorld();

		/// <summary>
		/// Check if the player with the given id is active or not.
		/// </summary>
		/// <param name="id">The player id.</param>
		/// <returns>True if the player with the given id is active. Otherwise, false.</returns>
		static bool IsPlayerActive(int id);

		/// <summary>
		/// Gets the CPlayerInfo object of the given player id.
		/// </summary>
		/// <param name="nPlayerId">The id of the player you want to get the CPlayerInfo object from.</param>
		/// <returns>If successful, the CPlayerInfo object is returned. Otherwise, null.</returns>
		static CPlayerInfo^ GetPlayerInfo(uint32_t nPlayerId);

		/// <summary>
		/// Finds the current player ped.
		/// </summary>
		/// <returns>Returns a pointer to the current player ped.</returns>
		static UIntPtr FindPlayerPed();

		/// <summary>
		/// - DOES NOT WORK YET -
		/// Finds the current vehicle the player is driving.
		/// </summary>
		/// <returns>Returns a pointer to the current vehicle the player is driving.</returns>
		static UIntPtr FindPlayerVehicle();

	private:
		Native_CPlayerInfo* m_cNativePlayerInfo;
	};

}
