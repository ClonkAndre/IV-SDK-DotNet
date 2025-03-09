class CFrontEnd
{
public:
	static inline auto& g_iUserWaypointID = AddressSetter::GetRef<int32_t>("CFrontEnd", "g_iUserWaypointID");
	static inline auto& vMapCursor = AddressSetter::GetRef<CVector2D>("CFrontEnd", "vMapCursor");

	static void SwitchOnWaypoint(int unk_8, float x, float y, bool snapToHoveringBlip, CVector* outPos)
	{
		return ((void(__cdecl*)(int, float, float, bool, CVector*))(AddressSetter::Get("CFrontEnd", "SwitchOnWaypoint")))(unk_8, x, y, snapToHoveringBlip, outPos);
	}
	static void SwitchOffWaypoint()
	{
		return ((void(__cdecl*)())(AddressSetter::Get("CFrontEnd", "SwitchOffWaypoint")))();
	}
	static void ToggleWaypoint()
	{
		return ((void(__cdecl*)())(AddressSetter::Get("CFrontEnd", "ToggleWaypoint")))();
	}
};