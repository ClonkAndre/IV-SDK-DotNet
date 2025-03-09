class CText
{
public:
	const wchar_t* Get(const char* Ident)
	{
		return ((const wchar_t*(__thiscall*)(CText*, const char*))(AddressSetter::Get("CText", "Get")))(this, Ident);
	}
};
auto& TheText = AddressSetter::GetRef<CText>("CText", "TheText");