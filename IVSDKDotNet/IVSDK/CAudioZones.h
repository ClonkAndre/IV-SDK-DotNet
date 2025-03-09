class CAudioZones
{
public:
	static inline auto& m_NumSpheres = AddressSetter::GetRef<uint32_t>("CAudioZones", "m_NumSpheres");
	static inline auto m_aActiveSpheres = (int32_t*)AddressSetter::Get("CAudioZones", "m_aActiveSpheres");
	static inline auto& m_NumActiveSpheres = AddressSetter::GetRef<uint32_t>("CAudioZones", "m_NumActiveSpheres");
	static inline auto& m_NumBoxes = AddressSetter::GetRef<uint32_t>("CAudioZones", "m_NumBoxes");
	static inline auto m_aActiveBoxes = (int32_t*)AddressSetter::Get("CAudioZones", "m_aActiveBoxes");
	static inline auto& m_NumActiveBoxes = AddressSetter::GetRef<uint32_t>("CAudioZones", "m_NumActiveBoxes");

	static void Update(bool bForceUpdate, CVector TestCoors)
	{
		((void(__cdecl*)(bool, CVector))(AddressSetter::Get("CAudioZones", "Update")))(bForceUpdate, TestCoors);
	}
};
auto& LastUpdateCoors = AddressSetter::GetRef<CVector>("CAudioZones", "LastUpdateCoors");