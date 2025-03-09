class CCutsceneMgr
{
public:
	static inline uint32_t& ms_running = AddressSetter::GetRef<uint32_t>("CCutsceneMgr", "ms_running");

	static bool IsRunning()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get("CCutsceneMgr", "IsRunning")))();
	}
};