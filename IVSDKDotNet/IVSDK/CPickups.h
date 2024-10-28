class CPickup
{
public:
	uint32_t field_0;
	uint32_t WorldObject;
	uint32_t field_8;
	uint32_t RoomKey;
	int32_t Blip;
	uint8_t pad[0x2];
	CVector Position;
	uint8_t pad2[0x20];
	uint8_t Type;
	uint8_t pad3[0xA];

public:
	// Gets rid of this pickup and also of the attached blip if it has one.
	int Destroy()
	{
		return ((int(__thiscall*)(CPickup*))(AddressSetter::Get(0x5350C0, 0x589F10)))(this);
	}
};

class CPickups
{
public:
	// Array which hold the actual CPickup instances:							1080: (int[]) 0x12DEB60 (0xEDEB60)  || 1070: (int[]) 0x1549150 (0x1149150)
	// Array which seems to hold the pickup types individually for some reason: 1080: (char[]) 0x12DEBA4 (0xEDEBA4) || 1070: (char[]) 0x1549194 (0x1149194)

	static inline auto Pickups =		(CPickup*)AddressSetter::Get(0x1149150, 0xEDEB60);
	static inline auto PickupTypes =	(uint8_t*)AddressSetter::Get(0x1149194, 0xEDEBA4);

	// 1080: 0xF43631
	// 1070: 0xF2A064
	//static inline auto& ms_bDeadPedsDropWeapons = AddressSetter::GetRef<bool>(0xF2A064, 0xF43631); // TODO: Check address for 1070 & 1080

public:
	// Destroys all pickups
	static int Shutdown()
	{
		return ((int(__stdcall*)())(AddressSetter::Get(0x535800, 0x58A650)))();
	}

	// Removes and resets all pickups (not the actual pickup object). It also resets all the settings related with pickups to their default value.
	// This always returns 0.
	static int Reset()
	{
		return ((int(__stdcall*)())(AddressSetter::Get(0x534F70, 0x589DC0)))();
																				// How to get the address easily:
																				// Go to the native function "SET_DEAD_PEDS_DROP_WEAPONS" and check for xrefs
																				// to the byte (CPickups__m_bDeadPedDropWeapon) which gets set to 1
	}

	// Creates a new pickup.
	static int CreatePickup(CVector* position, CVector* rotation, int modelIndex, int type, bool a5, bool a6, bool a7_BlipRelated, uint32_t objPointerMaybe, char a12, char a13)
	{
		return ((int(__cdecl*)(CVector*, CVector*, int, int, bool, bool, bool, int, int, int, uint32_t, char, char))(AddressSetter::Get(0x536A00, 0x58B850)))(position, rotation, modelIndex, type, a5, a6, a7_BlipRelated, 0, 0, 0, objPointerMaybe, a12, a13);
	}
	// Removes a pickup with the given handle.
	static int RemovePickup(int handle)
	{
		return ((int(__cdecl*)(int))(AddressSetter::Get(0x535820, 0x58A670)))(handle);
	}

	// Creates a temporary radar blip for each pickup within the range around the given position.
	static void CreateTemporaryRadarBlipsForPickupsInArea(CVector* pos, float radius, int type)
	{
		((void(__cdecl*)(CVector*, float, int))(AddressSetter::Get(0x533A90, 0x588910)))(pos, radius, type);
	}
	// Creates a temporary radar blip for the given pickup only.
	static int CreateTemporaryRadarBlipForPickup(CVector* position, int pickupIndex)
	{
		return ((int(__cdecl*)(CVector*, char[], int))(AddressSetter::Get(0x412780, 0x473340)))(position, 0, pickupIndex);
	}
	// Removes all temporary radar blips.
	static void RemoveTemporaryRadarBlipsForPickups()
	{
		((void(__cdecl*)())(AddressSetter::Get(0x533BC0, 0x588A40)))();
	}

	// Does the pickup glow thing.
	static void DoPickUpEffects()
	{
		((void(__cdecl*)())(AddressSetter::Get(0x534280, 0x589100)))();
	}
};