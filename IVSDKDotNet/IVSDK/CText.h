class CText
{
public:
	const wchar_t* Get(const char* Ident)
	{
		return ((const wchar_t*(__thiscall*)(CText*, const char*))(AddressSetter::Get("CText", "Get")))(this, Ident);
	}
	const wchar_t* Get(uint32_t hash, const char* Ident)
	{
		return ((const wchar_t* (__thiscall*)(CText*, uint32_t, const char*))(AddressSetter::Get("CText", "Get_2")))(this, hash, Ident);
	}
};
auto& TheText = AddressSetter::GetRef<CText>("CText", "TheText");