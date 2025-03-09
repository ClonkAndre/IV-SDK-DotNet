namespace rage { class fiPackfile; }

class CStreaming
{
public:
	// static inline rage::fiPackfile* m_pPlayerPackfile = AddressSetter::GetRef<rage::fiPackfile*>(0xF503FC, 0xECEBCC); // player:/
	static inline uint32_t& m_nPedModelBudget = AddressSetter::GetRef<uint32_t>("CStreaming", "m_nPedModelBudget");
	static inline uint32_t& m_nVehicleModelBudget = AddressSetter::GetRef<uint32_t>("CStreaming", "m_nVehicleModelBudget");
	static inline uint8_t& ms_disableStreaming = AddressSetter::GetRef<uint8_t>("CStreaming", "ms_disableStreaming");

	static bool IsStreamingDisabled()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get("CStreaming", "IsStreamingDisabled")))();
	}

	// this is easier to use until RequestModel is fully documented
	static void ScriptRequestModel(int32_t nHash, uint32_t* pRunningThread = nullptr)
	{
		((void(__cdecl*)(int32_t, uint32_t*))(AddressSetter::Get("CStreaming", "ScriptRequestModel")))(nHash, pRunningThread);
	}
	//ScriptRequestModel: CStreaming::RequestModel(v4, dword_11F73A0, dword_12C38A8 | 0xC);
	// todo: look into this
	static void RequestModel(int32_t modelIndex, int32_t unk1, int32_t nFlags)
	{
		((void(__cdecl*)(int32_t, int32_t, int32_t))(AddressSetter::Get("CStreaming", "RequestModel")))(modelIndex, unk1, nFlags);
	}
	static void LoadAllRequestedModels(bool priorityOnly)
	{
		((void(__cdecl*)(bool))(AddressSetter::Get("CStreaming", "LoadAllRequestedModels")))(priorityOnly);
	}
	// images.txt
	static void AddImageList(char* fileName)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get("CStreaming", "AddImageList")))(fileName);
	}

	static rage::fiPackfile* GetPlayerPackfile()
	{
		return ((rage::fiPackfile*(__cdecl*)())(AddressSetter::Get("CStreaming", "GetPlayerPackfile")))();
	}
	static void ClosePlayerPackfile()
	{
		((void(__cdecl*)())(AddressSetter::Get("CStreaming", "ClosePlayerPackfile")))();
	}
};