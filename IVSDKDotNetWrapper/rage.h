#pragma once

class Native_RAGE
{
public:

	static HWND GetHWND() { return AddressSetter::GetRef<HWND>(0x1449DDC, 0x1352060); }
	static IDirect3DDevice9* GetDirect3DDevice() { return AddressSetter::GetRef<IDirect3DDevice9*>(0x148AB48, 0x1345630); }

};

namespace IVSDKDotNet {

	public ref class RAGE
	{
	public:

		static IntPtr GetHWND();

	};

}

