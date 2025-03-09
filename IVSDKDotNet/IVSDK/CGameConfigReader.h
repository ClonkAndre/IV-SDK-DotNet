class CGameConfigReader
{
public:
	void LoadFile(char* fileName)
	{
		((void(__thiscall*)(CGameConfigReader*, char*))(AddressSetter::Get("CGameConfigReader", "LoadFile")))(this, fileName);
	}
};
CGameConfigReader*& GameConfigReader = AddressSetter::GetRef<CGameConfigReader*>("CGameConfigReader", "GameConfigReader");