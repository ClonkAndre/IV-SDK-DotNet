class CPopulation
{
public:
	static inline auto& ms_nNumCop = AddressSetter::GetRef<int32_t>("CPopulation", "ms_nNumCop");
	static inline auto& ms_nNumEmergency = AddressSetter::GetRef<int32_t>("CPopulation", "ms_nNumEmergency");
	static inline auto& m_AllRandomPedsThisType = AddressSetter::GetRef<int32_t>("CPopulation", "m_AllRandomPedsThisType");
	static inline auto& PedDensityMultiplier = AddressSetter::GetRef<float>("CPopulation", "PedDensityMultiplier");

	static inline auto& ScenarioPedDensityMultiplier = AddressSetter::GetRef<float>("CPopulation", "ScenarioPedDensityMultiplier");
	static inline auto& ScenarioPedDensityMultiplier2 = AddressSetter::GetRef<float>("CPopulation", "ScenarioPedDensityMultiplier2");

	static void Initialise()
	{
		return ((void(__cdecl*)())(AddressSetter::Get("CPopulation", "Initialise")))();
	}
	static void RemovePed(CPed* pPed, bool unk)
	{
		return ((void(__cdecl*)(CPed*, bool))(AddressSetter::Get("CPopulation", "RemovePed")))(pPed, unk);
	}
};