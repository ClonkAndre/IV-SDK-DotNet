class CShaderLib
{
public:
	// default, unlit, deferred, etc.
	static int GetTechniqueID(char* name)
	{
		return ((int(__cdecl*)(char*))(AddressSetter::Get("CShaderLib", "GetTechniqueID")))(name);
	}
};