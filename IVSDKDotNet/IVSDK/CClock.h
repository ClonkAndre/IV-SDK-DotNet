class CClock
{
public:
	static inline uint32_t& ms_nGameClockForcedMinutes = AddressSetter::GetRef<uint32_t>("CClock", "ms_nGameClockForcedMinutes");
	static inline uint32_t& ms_nGameClockForcedHours = AddressSetter::GetRef<uint32_t>("CClock", "ms_nGameClockForcedHours");
	static inline uint32_t& CurrentDay = AddressSetter::GetRef<uint32_t>("CClock", "CurrentDay");
	static inline uint32_t& ms_nGameClockSeconds = AddressSetter::GetRef<uint32_t>("CClock", "ms_nGameClockSeconds");
	static inline uint32_t& ms_nGameClockMinutes = AddressSetter::GetRef<uint32_t>("CClock", "ms_nGameClockMinutes");
	static inline uint32_t& ms_nGameClockHours = AddressSetter::GetRef<uint32_t>("CClock", "ms_nGameClockHours");
	static inline uint32_t& ms_nGameClockDays = AddressSetter::GetRef<uint32_t>("CClock", "ms_nGameClockDays");
	static inline uint32_t& ms_nGameClockMonth = AddressSetter::GetRef<uint32_t>("CClock", "ms_nGameClockMonth");
	static inline uint32_t& ms_nMillisecondsPerGameMinute = AddressSetter::GetRef<uint32_t>("CClock", "ms_nMillisecondsPerGameMinute");
};