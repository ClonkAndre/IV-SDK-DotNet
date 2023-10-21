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

	static inline rage::pgDictionary<rage::grcTexturePC>*& ms_pStoredTxd = AddressSetter::GetRef<rage::pgDictionary<rage::grcTexturePC>*>(0x15ACACC, 0x15CE510);

	static void AddRef(int slot)
	{
		((void(__cdecl*)(int))(AddressSetter::Get(0x1ED00, 0x8ECA0)))(slot);
	}
	static int AddTxdSlot(char* sName)
	{
		return ((int(__cdecl*)(char*))(AddressSetter::Get(0x1EC20, 0x8EBC0)))(sName);
	}
	static int FindTxdSlot(uint32_t nHash)
	{
		return ((int(__cdecl*)(uint32_t))(AddressSetter::Get(0x1F130, 0x8F0B0)))(nHash);
	}
	static int FindTxdSlot(char* sName)
	{
		return ((int(__cdecl*)(char*))(AddressSetter::Get(0x1ECE0, 0x8EC80)))(sName);
	}
	static bool LoadTxd(int slot, char* sName)
	{
		return ((bool(__cdecl*)(int, char*))(AddressSetter::Get(0x420D40, 0x4CCC60)))(slot, sName);
	}
	static void PushCurrentTxd()
	{
		((void(__cdecl*)())(AddressSetter::Get(0x4204F0, 0x4CC410)))();
	}
	static void SetCurrentTxd(int slot)
	{
		((void(__cdecl*)(int))(AddressSetter::Get(0x420900, 0x4CC820)))(slot);
	}
	static void PopCurrentTxd()
	{
		((void(__cdecl*)())(AddressSetter::Get(0x420960, 0x4CC880)))();
	}
	static CSprite2d GetTexture(char* sName)
	{
		return ((CSprite2d(__stdcall*)(char*))(AddressSetter::Get(0x21DA10, 0xD300)))(sName);
	}
};