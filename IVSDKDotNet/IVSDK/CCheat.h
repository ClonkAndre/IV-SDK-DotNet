class CCheat
{
public:
	static inline auto& m_bHasPlayerCheated = AddressSetter::GetRef<bool>("CCheat", "m_bHasPlayerCheated");
};