#pragma once

class Native_RAGE
{
public:

	static HWND GetHWND() { return AddressSetter::GetRef<HWND>(0x1449DDC, 0x1352060); }
	static IDirect3DDevice9* GetDirect3DDevice9() { return AddressSetter::GetRef<IDirect3DDevice9*>(0x148AB48, 0x1345630); }

	static uint32_t atStringHash(const char* sString, uint32_t* nExistingHash = nullptr)
	{
		return ((uint32_t(__cdecl*)(const char*, uint32_t*))(AddressSetter::Get(0x1B1C30, 0x5CF50)))(sString, nExistingHash);
	}

};

namespace IVSDKDotNet {

	public ref class RAGE
	{
	public:

		static IntPtr GetHWND();
		static IntPtr GetDirect3DDevice9();
		static uint32_t atStringHash(String^ sString);

	};

}

