// any non-class rage functions should go here
namespace rage
{
	static HWND& g_pHWND = AddressSetter::GetRef<HWND>("rage", "g_pHWND");
	static IDirect3DDevice9*& g_pDirect3DDevice = AddressSetter::GetRef<IDirect3DDevice9*>("rage", "g_pDirect3DDevice");
	static uint32_t atStringHash(const char* sString, uint32_t* nExistingHash = nullptr)
	{
		return ((uint32_t(__cdecl*)(const char*, uint32_t*))(AddressSetter::Get("rage", "atStringHash")))(sString, nExistingHash);
	}
}