class CRestart
{
public:
	static inline auto& NumberOfHospitalRestarts = AddressSetter::GetRef<uint32_t>("CRestart", "NumberOfHospitalRestarts");
	static inline auto& NumberOfPoliceRestarts = AddressSetter::GetRef<uint32_t>("CRestart", "NumberOfPoliceRestarts");
	static inline auto& NumberOfSafehouses = AddressSetter::GetRef<uint32_t>("CRestart", "NumberOfSafehouses");

	static inline auto HospitalRestartPoints = (CVector_pad*)AddressSetter::Get("CRestart", "HospitalRestartPoints");
	static inline auto HospitalRestartHeadings = (float*)AddressSetter::Get("CRestart", "HospitalRestartHeadings");
	static inline auto HospitalRestartWhenToUse = (int*)AddressSetter::Get("CRestart", "HospitalRestartWhenToUse");

	static inline auto PoliceRestartPoints = AddressSetter::GetRef<CVector_pad>("CRestart", "PoliceRestartPoints");
	static inline auto PoliceRestartHeadings = AddressSetter::GetRef<float>("CRestart", "PoliceRestartHeadings");
	static inline auto PoliceRestartWhenToUse = AddressSetter::GetRef<int>("CRestart", "PoliceRestartWhenToUse");

	struct tSafehouse
	{
		CVector_pad vPos;							// 00-10
		float fHeading;								// 10-14
		char sName[32];								// 14-34
		uint32_t nWhenToUse;						// 34-38
		uint8_t bEnabled;							// 38-39
		uint8_t pad[0x7];							// 39-40
	};
	VALIDATE_SIZE(tSafehouse, 0x40);

	static inline auto Safehouses = (tSafehouse*)AddressSetter::Get("CRestart", "Safehouses");

	static inline auto& bOverrideRestart = AddressSetter::GetRef<bool>("CRestart", "bOverrideRestart");
	static inline auto& OverridePosition = AddressSetter::GetRef<CVector_pad>("CRestart", "OverridePosition");
	static inline auto& OverrideHeading = AddressSetter::GetRef<float>("CRestart", "OverrideHeading");
	static inline auto& bFadeInAfterNextDeath = AddressSetter::GetRef<bool>("CRestart", "bFadeInAfterNextDeath");
	static inline auto& ExtraHospitalRestartCoors = AddressSetter::GetRef<CVector_pad>("CRestart", "ExtraHospitalRestartCoors");
	static inline auto& ExtraHospitalRestartHeading = AddressSetter::GetRef<float>("CRestart", "ExtraHospitalRestartHeading");
	static inline auto& ExtraHospitalRestartWhenToUse = AddressSetter::GetRef<uint32_t>("CRestart", "ExtraHospitalRestartWhenToUse");
	static inline auto& ExtraPoliceStationRestartCoors = AddressSetter::GetRef<CVector_pad>("CRestart", "ExtraPoliceStationRestartCoors");
	static inline auto& ExtraPoliceStationRestartHeading = AddressSetter::GetRef<float>("CRestart", "ExtraPoliceStationRestartHeading");
	static inline auto& ExtraPoliceStationRestartWhenToUse = AddressSetter::GetRef<uint32_t>("CRestart", "ExtraPoliceStationRestartWhenToUse");

	static bool Save()
	{
		return ((int(__cdecl*)())(AddressSetter::Get("CRestart", "Save")))();
	}
	static bool Load()
	{
		return ((int(__cdecl*)())(AddressSetter::Get("CRestart", "Load")))();
	}
};