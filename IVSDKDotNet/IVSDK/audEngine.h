class audConfig
{
public:

	void LoadFromFile(char* path)
	{
		((void(__thiscall*)(audConfig*, char*))(AddressSetter::Get("audConfig", "LoadFromFile")))(this, path);
	}
};

class audEngine
{
public:
	static inline audConfig& m_pSoundsConfig = AddressSetter::GetRef<audConfig>("audEngine", "m_pSoundsConfig");
	static inline audConfig& m_pCurvesConfig = AddressSetter::GetRef<audConfig>("audEngine", "m_pCurvesConfig");
	static inline audConfig& m_pGameConfig = AddressSetter::GetRef<audConfig>("audEngine", "m_pGameConfig");

	// this is used after every category patch, but the parameter is 1 in ep2 and 0 in the rest
	void SetUnknown(float unk1)
	{
		((void(__thiscall*)(audEngine*, float))(AddressSetter::Get("audEngine", "SetUnknown")))(this, unk1);
	}
};

audEngine& AudioEngine = AddressSetter::GetRef<audEngine>("audEngine", "AudioEngine");