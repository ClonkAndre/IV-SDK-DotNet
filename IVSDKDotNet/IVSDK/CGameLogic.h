class CGameLogic
{
public:
	static inline auto& bPenaltyForDeathApplies = AddressSetter::GetRef<bool>("CGameLogic", "bPenaltyForDeathApplies");
	static inline auto& bPenaltyForArrestApplies = AddressSetter::GetRef<bool>("CGameLogic", "bPenaltyForArrestApplies");

	static bool Save()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get("CGameLogic", "Save")))();
	}
	static bool Load()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get("CGameLogic", "Load")))();
	}
	static void RestorePlayerStuffDuringResurrection(CPed* pPlayerPed, CVector NewCoors, float NewHeading)
	{
		((void(__cdecl*)(CPed*, CVector, float))(AddressSetter::Get("CGameLogic", "RestorePlayerStuffDuringResurrection")))(pPlayerPed, NewCoors, NewHeading);
	}
};