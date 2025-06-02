class CPedType
{
public:

	// takes pedtype string and returns 1 if PLAYER1, PLAYER2, PLAYER_NETWORK or PLAYER_UNUSED
	// if true the game sets CPedModelInfo::m_bStreamedPed to 1
	static bool IsPedTypePlayer(char* type)
	{
		return ((bool(__cdecl*)(char*))(AddressSetter::Get("CPedType", "IsPedTypePlayer")))(type);
	}
	// returns pedtype id from string
	static int FindPedType(char* type)
	{
		return ((int(__cdecl*)(char*))(AddressSetter::Get("CPedType", "FindPedType")))(type);
	}
};