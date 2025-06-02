class CNetwork
{
public:
	static inline void*& m_pClientBroadcastVars = AddressSetter::GetRef<void*>("CNetwork", "m_pClientBroadcastVars");
	static inline void*& m_pClientBroadcastVarSize = AddressSetter::GetRef<void*>("CNetwork", "m_pClientBroadcastVarSize");
	static inline uint32_t& m_bNetworkSession = AddressSetter::GetRef<uint32_t>("CNetwork", "m_bNetworkSession");
	static inline uint32_t& m_nNetworkStatus = AddressSetter::GetRef<uint32_t>("CNetwork", "m_nNetworkStatus");
	static inline bool& m_bIsHostingGame = AddressSetter::GetRef<bool>("CNetwork", "m_bIsHostingGame");
	static bool IsNetworkGameRunning()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get("CNetwork", "IsNetworkGameRunning")))();
	}
	static bool IsNetworkSession()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get("CNetwork", "IsNetworkSession")))();
	}
	static void CheckFramerate(bool bUnk, int time)
	{
		((void(__cdecl*)(bool, int))(AddressSetter::Get("CNetwork", "CheckFramerate")))(bUnk, time);
	}
};