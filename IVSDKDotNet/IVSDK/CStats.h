class CStats
{
public:
	static inline auto LastMissionPassedName = (wchar_t*)AddressSetter::Get("CStats", "LastMissionPassedName");

	static float GetStatValue(uint16_t index)
	{
		return ((float(__cdecl*)(uint16_t))(AddressSetter::Get("CStats", "GetStatValue")))(index);
	}
	static void SetStatValue(uint16_t index, float NewValue)
	{
		((void(__cdecl*)(uint16_t, float))(AddressSetter::Get("CStats", "SetStatValue")))(index, NewValue);
	}
};