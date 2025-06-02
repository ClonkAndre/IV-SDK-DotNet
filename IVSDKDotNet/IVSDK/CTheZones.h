class CZone
{
public:
	char InfoLabel[8];								// 00-08
	char TextLabel[8];								// 08-10
	int16_t MinX;									// 10-12
	int16_t MinY;									// 12-14
	int16_t MinZ;									// 14-16
	int16_t MaxX;									// 16-18
	int16_t MaxY;									// 18-1A
	int16_t MaxZ;									// 1A-1C
	int16_t unk1;									// 1C-1E
	int16_t unk2;									// 1E-20
	uint8_t PopulationType;							// 20-21
	uint8_t Scumminess;								// 21-22
	uint8_t pad[0x6];								// 22-28
};
VALIDATE_SIZE(CZone, 0x28);
VALIDATE_OFFSET(CZone, TextLabel, 0x8);
VALIDATE_OFFSET(CZone, PopulationType, 0x20);

class CTheZones
{
public:
	static inline auto& TotalNumberOfMapZones = AddressSetter::GetRef<uint32_t>("CTheZones", "TotalNumberOfMapZones");
	static inline auto MapZoneArray = (CZone*)AddressSetter::Get("CTheZones", "MapZoneArray");

	static inline auto& ZonesRevealed = AddressSetter::GetRef<uint32_t>("CTheZones", "ZonesRevealed");
	static inline auto ZonesVisited = (bool*)AddressSetter::Get("CTheZones", "ZonesVisited"); // ZonesVisited[100] ZonesVisited[10][10]

	static bool Save()
	{
		return ((int(__cdecl*)())(AddressSetter::Get("CTheZones", "Save")))();
	}
	static bool Load()
	{
		return ((int(__cdecl*)())(AddressSetter::Get("CTheZones", "Load")))();
	}

	static CZone* Reset()
	{
		return ((CZone*(__cdecl*)())(AddressSetter::Get("CTheZones", "Reset")))();
	}

	// Returns probably the index of the next slot in the zones array (result * 2 = next slot?)
	static int Add(const char* name, float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const char* a8)
	{
		return ((int(__cdecl*)(const char*, float, float, float, float, float, float, const char*))(AddressSetter::Get("CTheZones", "Add")))(
			name,
			minX,
			minY,
			minZ,
			maxX,
			maxY,
			maxZ,
			a8);
	}

	static const char* GetZoneNameByCoords(CVector* vec)
	{
		return ((const char* (__cdecl*)(CVector*))(AddressSetter::Get("CTheZones", "GetZoneNameByCoords")))(vec);
	}
	static const char* GetZoneNameByIndex(int index)
	{
		return ((const char* (__cdecl*)(int))(AddressSetter::Get("CTheZones", "GetZoneNameByIndex")))(index);
	}
	static int GetZoneNumberByName(const char* name)
	{
		return ((int (__cdecl*)(const char*))(AddressSetter::Get("CTheZones", "GetZoneNumberByName")))(name);
	}

	static bool IsPointInZone(CVector* vec, CZone* zone)
	{
		return ((bool (__cdecl*)(CVector*, CZone*))(AddressSetter::Get("CTheZones", "IsPointInZone")))(vec, zone);
	}

};