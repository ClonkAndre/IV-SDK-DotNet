class CBaseDC
{
public:
	uint8_t pad[0x8];					// 00-08
	void* operator new(size_t nSize, uint32_t nUnk0)
	{
		return ((CBaseDC * (__cdecl*)(size_t, uint32_t))(AddressSetter::Get("CBaseDC", "new")))(nSize, nUnk0);
	}
	void operator delete(void*, size_t, uint32_t) {};
	void Add()
	{
		((void(__thiscall*)(CBaseDC*))(AddressSetter::Get("CBaseDC", "Add")))(this);
	}
};
VALIDATE_SIZE(CBaseDC, 0x8);