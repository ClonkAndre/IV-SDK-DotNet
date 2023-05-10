#include "pch.h"
#include "rage.h"

extern LONG_PTR oriWndProc = NULL;

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool result = RAGE::InvokeOnWndProcMessageReceived(IntPtr(hWnd), uMsg, UIntPtr(wParam), IntPtr(lParam));

	if (result)
		return 0;

	// Call the original function
	return CallWindowProcW((WNDPROC)oriWndProc, hWnd, uMsg, wParam, lParam);
}

namespace IVSDKDotNet {

	IntPtr RAGE::GetHWND()
	{
		return IntPtr(Native_RAGE::GetHWND());
	}
	IntPtr RAGE::GetDirect3DDevice9()
	{
		return IntPtr(Native_RAGE::GetDirect3DDevice9());
	}

	bool RAGE::InitWndProcHook()
	{
		if (m_bWndProcInitialized)
			return true;

		m_bWndProcInitialized = Native_RAGE::InitWndProcHook();
		return m_bWndProcInitialized;
	}

	uint32_t RAGE::atStringHash(String^ sString)
	{
		msclr::interop::marshal_context ctx;
		return Native_RAGE::atStringHash(ctx.marshal_as<const char*>(sString));
	}
	uint32_t RAGE::atStringHash(String^ sString, UIntPtr nExistingHash)
	{
		msclr::interop::marshal_context ctx;
		return Native_RAGE::atStringHash(ctx.marshal_as<const char*>(sString), (uint32_t*)nExistingHash.ToPointer());
	}

}