class CRadioStation
{
public:
	uint8_t pad[0x17FC];								// 0000-17FC
	char m_sName[32];									// 17FC-181C
	uint8_t pad2[0x10B];								// 181C-1927
	uint8_t m_bFrozen;									// 1927-1928
	uint8_t pad3[0xC];									// 1928-1934

	void ForceTrack(char* trackName, int nUnk1, int nUnk2)
	{
		((void(__thiscall*)(char*, int, int))(AddressSetter::Get("CRadioStation", "ForceTrack")))(trackName, nUnk1, nUnk2);
	}
};
VALIDATE_SIZE(CRadioStation, 0x1934);
VALIDATE_OFFSET(CRadioStation, m_sName, 0x17FC);
VALIDATE_OFFSET(CRadioStation, m_bFrozen, 0x1927);

class CAERadioTrackManager
{
public:
	static inline auto& m_bLazlowStationLocked = AddressSetter::GetRef<bool>("CAERadioTrackManager", "m_bLazlowStationLocked");
	static inline auto& m_bTaxiGarageRadioState = AddressSetter::GetRef<bool>("CAERadioTrackManager", "m_bTaxiGarageRadioState");
	static inline auto& m_nNumRadioStations = AddressSetter::GetRef<uint32_t>("CAERadioTrackManager", "m_nNumRadioStations");
	static inline auto m_aRadioStations = (CRadioStation**)AddressSetter::Get("CAERadioTrackManager", "m_aRadioStations"); // CRadioStation*[30]

	static CRadioStation* GetRadioStation(int id)
	{
		return ((CRadioStation*(__cdecl*)(int))(AddressSetter::Get("CAERadioTrackManager", "GetRadioStation")))(id);
	}
	static CRadioStation* GetRadioStationByName(char* name)
	{
		return ((CRadioStation*(__cdecl*)(char*))(AddressSetter::Get("CAERadioTrackManager", "GetRadioStationByName")))(name);
	}
	static CRadioStation* GetRadioStationByHash(uint32_t hash)
	{
		return ((CRadioStation*(__cdecl*)(uint32_t))(AddressSetter::Get("CAERadioTrackManager", "GetRadioStationByHash")))(hash);
	}
};