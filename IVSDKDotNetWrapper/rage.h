#pragma once

namespace IVSDKDotNet
{

	public ref class RAGE
	{
	public:
		delegate void WndProcMessageDelegate(IntPtr hWnd, uint32_t msg, UIntPtr wParam, IntPtr lParam);
		delegate void GameWindowFocusChangedDelegate(bool focused);

	public:

		/// <summary>
		/// Gets raised when the GTA IV window receives Windows Messages.
		/// See https://wiki.winehq.org/List_Of_Windows_Messages for a list of all Windows Messages.
		/// </summary>
		static event WndProcMessageDelegate^ OnWndProcMessageReceived;

		/// <summary>
		/// Gets raised when the focus of the GTA IV window changes.
		/// This event is NOT thread-safe!
		/// </summary>
		static event GameWindowFocusChangedDelegate^ OnWindowFocusChanged;

		/// <summary>
		/// Gets raised when GTA IV is about to close.
		/// </summary>
		static event EventHandler^ OnExit;

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

		static uint32_t AtStringHash(String^ sString);
		static uint32_t AtStringHash(String^ sString, UIntPtr nExistingHash);

	internal:
		static void RaiseOnWndProcMessageReceived(IntPtr hWnd, uint32_t msg, UIntPtr wParam, IntPtr lParam) { OnWndProcMessageReceived(hWnd, msg, wParam, lParam); };
		static void RaiseOnExit() { OnExit(nullptr, EventArgs::Empty); }
		static void RaiseOnWindowFocusChanged(bool focused) { OnWindowFocusChanged(focused); }
	};

}

