class CPickup
{
public:
	uint32_t field_0;
	uint32_t field_4; // deffo pointer to the pickup cobject
	uint32_t field_8;
	uint32_t roomHash;
	uint16_t blip;
	uint32_t field_14;
	CVector pos;

	// TODO: Tidy up this class

	//uint32_t field_24;
	//uint32_t field_28;
	//uint32_t field_2C;
	//uint32_t field_30;
	//uint32_t field_34;
	//uint32_t field_38;
	//uint16_t field_3C;
	//uint32_t field_40;
	//uint16_t field_42;
	//uint16_t type;
	//uint8_t field_45;
	//uint8_t field_46;
	//uint8_t field_47;
	//uint8_t field_48;
	//uint8_t field_49;
	//uint8_t field_4A;
	//uint8_t field_4B;
	//uint8_t field_4C;

public:
	int Destroy()
	{
		return ((int(__thiscall*)(CPickup*))(AddressSetter::Get(0x0, 0x589F10)))(this); // TODO: Get address for 1070
	}
};

// TODO: Expand this class
class CPickups
{
public:
	// array:					0x12DEBA4 (0xEDEBA4) <- this seems to hold the type of pickup?
	// some array:				0x12DEB70
	// another array:	(int[]) 0x12DEB60 (0xEDEB60) <- this actually holds the pickups
	static inline auto Pickups = (CPickup*)AddressSetter::Get(0x0, 0xEDEB60); // TODO: Get address for 1070
	static inline auto PickupTypes = (uint8_t*)AddressSetter::Get(0x0, 0xEDEBA4); // TODO: Get address for 1070

public:
	// Destroys all pickups
	static int Shutdown()
	{
		return ((int(__stdcall*)())(AddressSetter::Get(0x0, 0x58A650)))(); // TODO: Get address for 1070
	}

	// Removes and resets all pickups (not the actual pickup object). It also resets all the settings related with pickups to their default value.
	// This always returns 0.
	static int Reset()
	{
		return ((int(__stdcall*)())(AddressSetter::Get(0x0, 0x589DC0)))(); // TODO: Get address for 1070
																		 // How to get the address easily:
																		 // Go to the native function "SET_DEAD_PEDS_DROP_WEAPONS" and check for xrefs
																		 // to the byte (CPickups__m_bDeadPedDropWeapon) which gets set to 1
	}

	static int CreatePickup(CVector* position, CVector* rotation, int modelIndex, int type, bool a5, bool a6, bool a7_maybeBlipRelated, uint32_t objPointerMaybe, char a12, char a13)
	{
		return ((int(__cdecl*)(CVector*, CVector*, int, int, bool, bool, bool, int, int, int, uint32_t, char, char))(AddressSetter::Get(0x0, 0x58B850)))(position, rotation, modelIndex, type, a5, a6, a7_maybeBlipRelated, 0, 0, 0, objPointerMaybe, a12, a13); // TODO: Get address for 1070
	}
	static int RemovePickup(int handle)
	{
		return ((int(__cdecl*)(int))(AddressSetter::Get(0x0, 0x58A670)))(handle); // TODO: Get address for 1070
	}

	static void CreateTemporaryRadarBlipsForPickupsInArea(CVector* pos, float radius, int type)
	{
		((void(__cdecl*)(CVector*, float, int))(AddressSetter::Get(0x533A90, 0x588910)))(pos, radius, type);
	}
	static void RemoveTemporaryRadarBlipsForPickups()
	{
		((void(__cdecl*)())(AddressSetter::Get(0x0, 0x588A40)))(); // TODO: Get address for 1070
	}

	static void DoPickUpEffects()
	{
		((void(__cdecl*)())(AddressSetter::Get(0x534280, 0x589100)))();
	}
};