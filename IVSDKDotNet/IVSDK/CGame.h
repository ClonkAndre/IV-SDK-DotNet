class CGame
{
public:
	static inline char*& sGameFile = AddressSetter::GetRef<char*>("CGame", "sGameFile"); // common:/data/gta.dat

	static inline uint32_t& m_nCurrentEpisode = AddressSetter::GetRef<uint32_t>("CGame", "m_nCurrentEpisode");
	static inline uint32_t& m_nForcedEpisode = AddressSetter::GetRef<uint32_t>("CGame", "m_nForcedEpisode");
	static inline uint32_t& m_nCurrentEpisodeMenu = AddressSetter::GetRef<uint32_t>("CGame", "m_nCurrentEpisodeMenu"); // used for switching hudcolor in each episode's menu screen and for loading the right episode when you hit play
	
	// 1080: 10FC650 (0xCFC650)
	// 1070: 10C7F80 (0xCC7F80)
	static inline uint32_t& m_nMenuState = AddressSetter::GetRef<uint32_t>("CGame", "m_nMenuState");

	static bool Initialise(const char* sGameDat)
	{
		return ((bool(__cdecl*)(const char*))(AddressSetter::Get("CGame", "Initialise")))(sGameDat);
	}

	static bool IsGameRestarting()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get("CGame", "IsGameRestarting")))();
	}

	static bool SetMenuState(int state)
	{
		return ((bool(__cdecl*)(int))(AddressSetter::Get("CGame", "SetMenuState")))(state);
	}

};