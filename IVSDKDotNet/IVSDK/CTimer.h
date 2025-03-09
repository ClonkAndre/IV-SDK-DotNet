class CTimer
{
public:
	static inline uint8_t& m_CodePause = AddressSetter::GetRef<uint8_t>("CTimer", "m_CodePause");
	static inline uint8_t& m_UserPause = AddressSetter::GetRef<uint8_t>("CTimer", "m_UserPause");
	static inline uint32_t& m_FrameCounter = AddressSetter::GetRef<uint32_t>("CTimer", "m_FrameCounter");
	static inline uint32_t& m_snTimeInMilliseconds = AddressSetter::GetRef<uint32_t>("CTimer", "m_snTimeInMilliseconds");
	static inline uint32_t& m_sTimerLength = AddressSetter::GetRef<uint32_t>("CTimer", "m_sTimerLength");
	static inline float& ms_fMinTimeStep = AddressSetter::GetRef<float>("CTimer", "ms_fMinTimeStep");
	static inline float& ms_fMaxTimeStep = AddressSetter::GetRef<float>("CTimer", "ms_fMaxTimeStep");
	static inline float& ms_fTimeStep = AddressSetter::GetRef<float>("CTimer", "ms_fTimeStep");
	static inline float& ms_fTimeStepNonClipped = AddressSetter::GetRef<float>("CTimer", "ms_fTimeStepNonClipped");
	static inline float& ms_fTimeScale = AddressSetter::GetRef<float>("CTimer", "ms_fTimeScale"); // set by scripts
	static inline float& ms_fTimeScale2 = AddressSetter::GetRef<float>("CTimer", "ms_fTimeScale2"); // set by scripts
	static inline float& ms_fTimeScale3 = AddressSetter::GetRef<float>("CTimer", "ms_fTimeScale3"); // changes for death camera

	static bool GetIsPaused()
	{
		return ((uint32_t(__cdecl*)())(AddressSetter::Get("CTimer", "GetIsPaused")))();
	}
};