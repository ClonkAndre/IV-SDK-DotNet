struct TxdDef
{
	rage::pgDictionary<rage::grcTexturePC>* m_pDictionary;		// 00-04
	int32_t m_nRefCount;										// 04-08
	uint32_t m_nHash;											// 08-0C
	int32_t m_nParent;											// 0C-10
};
VALIDATE_SIZE(TxdDef, 0x10);

class CTxdStore
{
public:
	// txds are rage::pgDictionary<rage::grcTexture>
	// see 0x487460, loads fonts and buttons

	static inline rage::pgDictionary<rage::grcTexturePC>*& ms_pStoredTxd = AddressSetter::GetRef<rage::pgDictionary<rage::grcTexturePC>*>("CTxdStore", "ms_pStoredTxd");

	static void AddRef(int slot)
	{
		((void(__cdecl*)(int))(AddressSetter::Get("CTxdStore", "AddRef")))(slot);
	}
	static int AddTxdSlot(char* sName)
	{
		return ((int(__cdecl*)(char*))(AddressSetter::Get("CTxdStore", "AddTxdSlot")))(sName);
	}
	static int FindTxdSlot(uint32_t nHash)
	{
		return ((int(__cdecl*)(uint32_t))(AddressSetter::Get("CTxdStore", "FindTxdSlot")))(nHash);
	}
	static int FindTxdSlot(char* sName)
	{
		return ((int(__cdecl*)(char*))(AddressSetter::Get("CTxdStore", "FindTxdSlot_2")))(sName);
	}
	static bool LoadTxd(int slot, char* sName)
	{
		return ((bool(__cdecl*)(int, char*))(AddressSetter::Get("CTxdStore", "LoadTxd")))(slot, sName);
	}
	static void PushCurrentTxd()
	{
		((void(__cdecl*)())(AddressSetter::Get("CTxdStore", "PushCurrentTxd")))();
	}
	static void SetCurrentTxd(int slot)
	{
		((void(__cdecl*)(int))(AddressSetter::Get("CTxdStore", "SetCurrentTxd")))(slot);
	}
	static void PopCurrentTxd()
	{
		((void(__cdecl*)())(AddressSetter::Get("CTxdStore", "PopCurrentTxd")))();
	}
	static CSprite2d GetTexture(char* sName)
	{
		return ((CSprite2d(__stdcall*)(char*))(AddressSetter::Get("CTxdStore", "GetTexture")))(sName);
	}
};