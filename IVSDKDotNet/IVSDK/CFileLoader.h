class CFileLoader
{
public:
	static inline char*& sAmbientDataPath = AddressSetter::GetRef<char*>("CFileLoader", "sAmbientDataPath"); // common:/DATA/Ambient.dat
	static inline char*& sGameRpfPath = AddressSetter::GetRef<char*>("CFileLoader", "sGameRpfPath"); // platform:/data/game.rpf
	static inline char*& sScenariosDatPath = AddressSetter::GetRef<char*>("CFileLoader", "sScenariosDatPath"); // common:/DATA/Scenarios.dat
	static inline char*& sButtonsTxdPath = AddressSetter::GetRef<char*>("CFileLoader", "sButtonsTxdPath"); // platform:/textures/buttons_360
	static inline char*& sProceduralDatPath = AddressSetter::GetRef<char*>("CFileLoader", "sProceduralDatPath"); // common:/data/materials
	static inline char*& sStreamIniPath = AddressSetter::GetRef<char*>("CFileLoader", "sStreamIniPath"); // platform:/stream.ini

	// priority? it's set to 2 and 1 for loading default.dat in TBoGT but 0 everywhere else
	static void LoadLevel(char* levelName, int nUnk)
	{
		((void(__cdecl*)(char*, int))(AddressSetter::Get("CFileLoader", "LoadLevel")))(levelName, nUnk);
	}

	static void LoadObjectTypes(char* fileName)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get("CFileLoader", "LoadObjectTypes")))(fileName);
	}

	static void LoadWater(char* fileName)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get("CFileLoader", "LoadWater")))(fileName);
	}

	static void LoadSpeechData(char* fileName)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get("CFileLoader", "LoadSpeechData")))(fileName);
	}

	static void MountWavePack(char* fileName, char* mount)
	{
		((void(__cdecl*)(char*, char*))(AddressSetter::Get("CFileLoader", "MountWavePack")))(fileName, mount);
	}

	static void LoadObject(char* pLine)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get("CFileLoader", "LoadObject")))(pLine);
	}

	static void LoadPedObject(char* pLine)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get("CFileLoader", "LoadPedObject")))(pLine);
	}

	static void LoadVehicleObject(char* pLine)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get("CFileLoader", "LoadVehicleObject")))(pLine);
	}
};