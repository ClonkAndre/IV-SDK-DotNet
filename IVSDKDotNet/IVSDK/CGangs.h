class CGangInfo
{
public:
	int8_t PedModelOverride;					// 00-01
	uint8_t pad[0x3];							// 01-04
	uint32_t FirstWeapon;						// 04-08
	uint32_t SecondWeapon;						// 08-0C
	uint32_t ThirdWeapon;						// 0C-10
	uint8_t FirstWeaponChance;					// 10-11
	uint8_t SecondWeaponChance;					// 11-12
	uint8_t ThirdWeaponChance;					// 12-13
	uint8_t pad2;								// 13-14
};
VALIDATE_SIZE(CGangInfo, 0x14);

class CGangs
{
public:
	static inline auto Gang = (CGangInfo*)AddressSetter::Get("CGangs", "Gang"); // Gang[12]

	static bool Save()
	{
		return ((int(__cdecl*)())(AddressSetter::Get("CGangs", "Save")))();
	}
	static bool Load()
	{
		return ((int(__cdecl*)())(AddressSetter::Get("CGangs", "Load")))();
	}
};