class CReplay
{
public:
	static inline auto& Mode = AddressSetter::GetRef<uint32_t>("CReplay", "Mode");
};