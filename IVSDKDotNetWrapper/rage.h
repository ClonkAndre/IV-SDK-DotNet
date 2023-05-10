#pragma once

extern LONG_PTR oriWndProc;
LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Native_RAGE
{
public:
	static HWND GetHWND() { return AddressSetter::GetRef<HWND>(0x1449DDC, 0x1352060); }
	static IDirect3DDevice9* GetDirect3DDevice9() { return AddressSetter::GetRef<IDirect3DDevice9*>(0x148AB48, 0x1345630); }

	static bool InitWndProcHook()
	{
		// FindWindow(NULL, L"GTAIV")
		oriWndProc = SetWindowLongPtr(GetHWND(), GWLP_WNDPROC, (LONG_PTR)WndProc);
		return oriWndProc != NULL;
	}

	static uint32_t atStringHash(const char* sString, uint32_t* nExistingHash = nullptr)
	{
		return ((uint32_t(__cdecl*)(const char*, uint32_t*))(AddressSetter::Get(0x1B1C30, 0x5CF50)))(sString, nExistingHash);
	}

};

namespace IVSDKDotNet {

	public ref class RAGE
	{
	public:

		delegate bool WndProcMessageDelegate(IntPtr hWnd, uint32_t msg, UIntPtr wParam, IntPtr lParam);

		/// <summary>
		/// Gets raised when the GTA IV window receives Windows Messages. See https://wiki.winehq.org/List_Of_Windows_Messages for a list of all Windows Messages. If you return true from this event, this says that you do not want GTA IV to receive its original message.
		/// </summary>
		static event WndProcMessageDelegate^ OnWndProcMessageReceived;

		/// <summary>
		/// Gets the main window handle pointer.
		/// </summary>
		/// <returns>The pointer to the main window handle of GTA IV.</returns>
		static IntPtr GetHWND();

		/// <summary>
		/// Gets the IDirect3DDevice9 pointer.
		/// </summary>
		/// <returns>The pointer to the IDirect3DDevice9 of GTA IV.</returns>
		static IntPtr GetDirect3DDevice9();

		/// <summary>
		/// Initializes the WndProc hook. This method will automatically be called when IV-SDK .NET initializes.
		/// </summary>
		/// <returns>True when the hook got initialized successfully. Otherwise, false.</returns>
		static bool InitWndProcHook();

		static uint32_t atStringHash(String^ sString);
		static uint32_t atStringHash(String^ sString, UIntPtr nExistingHash);

	internal:
		static bool InvokeOnWndProcMessageReceived(IntPtr hWnd, uint32_t msg, UIntPtr wParam, IntPtr lParam) { return OnWndProcMessageReceived(hWnd, msg, wParam, lParam); };

	private:
		static bool m_bWndProcInitialized;
	};

}

