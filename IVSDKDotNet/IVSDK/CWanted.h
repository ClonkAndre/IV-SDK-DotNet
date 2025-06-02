class CWanted
{
public:
	static inline auto& MaximumWantedLevel = AddressSetter::GetRef<uint32_t>("CWanted", "MaximumWantedLevel");
	static inline auto& nMaximumWantedLevel = AddressSetter::GetRef<uint32_t>("CWanted", "nMaximumWantedLevel");
};