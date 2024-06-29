#include "pch.h"

// Modified DirectInput8 Hook code from the InGameTimecycEditor Mod for GTA IV made by akifle47.
// https://github.com/akifle47/InGameTimecycEditor

static DInput8DeviceGetDeviceStateT* g_sDInput8DeviceGetDeviceStateOriginal = nullptr;
static DInput8DeviceGetDeviceDataT* g_sDInput8DeviceGetDeviceDataOriginal = nullptr;

static DInput8DeviceAcquireT* g_sDInput8DeviceAcquireOriginal = nullptr;

static HRESULT __stdcall DInput8DeviceGetDeviceStateHook(IDirectInputDevice8* device, DWORD cbData, LPVOID lpvData)
{
	HRESULT hr = g_sDInput8DeviceGetDeviceStateOriginal(device, cbData, lpvData);

	if (ImGuiStates::s_bImGuiWantsMouseDisabled)
	{
		if (cbData == sizeof(DIMOUSESTATE) || cbData == sizeof(DIMOUSESTATE2))
		{
			device->Unacquire();
			return DI_OK;
		} 
	}

	//if (SUCCEEDED(hr))
	//{
	//	ImGuiIO& io = ImGui::GetIO();

	//	// Pass the input data to ImGui
	//	if ((cbData == sizeof(DIMOUSESTATE) || cbData == sizeof(DIMOUSESTATE2)) && io.WantCaptureMouse)
	//	{
	//		// Cast to DIMOUSESTATE
	//		DIMOUSESTATE* mouseState = (DIMOUSESTATE*)lpvData;

	//		// Pass the mouse data to ImGui
	//		io.MousePos.x += mouseState->lX;
	//		io.MousePos.y += mouseState->lY;
	//		io.MouseDown[0] = (mouseState->rgbButtons[0] & 0x80) != 0;
	//		io.MouseDown[1] = (mouseState->rgbButtons[1] & 0x80) != 0;
	//		io.MouseDown[2] = (mouseState->rgbButtons[2] & 0x80) != 0;

	//		// Clear the input data to prevent it from reaching the original application
	//		ZeroMemory(lpvData, cbData);
	//	}
	//	else if (cbData == sizeof(BYTE[256]) && (io.WantCaptureKeyboard || io.WantTextInput))
	//	{
	//		BYTE* keyboardState = (BYTE*)lpvData;

	//		// Pass the keyboard data to ImGui
	//		for (int i = 0; i < 256; ++i)
	//			io.KeysData[i].Down = (keyboardState[i] & 0x80) != 0;

	//		// Clear the input data to prevent it from reaching the original application
	//		ZeroMemory(lpvData, cbData);
	//	}
	//}

	return hr;
}
static HRESULT __stdcall DInput8DeviceGetDeviceDataHook(IDirectInputDevice8* device, DWORD cbData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD flags)
{
	HRESULT hr = g_sDInput8DeviceGetDeviceDataOriginal(device, cbData, rgdod, pdwInOut, flags);

	if (ImGuiStates::s_bImGuiWantsKeyboardDisabled)
	{
		device->Unacquire();
		return DI_OK;
	}

	//if (SUCCEEDED(hr))
	//{
	//	ImGuiIO& io = ImGui::GetIO();

	//	// Clear the input data to prevent it from reaching the original application
	//	if (io.WantCaptureMouse || io.WantCaptureKeyboard || io.WantTextInput)
	//	{
	//		//ZeroMemory(rgdod, cbData);
	//		ZeroMemory(rgdod, cbData * (*pdwInOut));
	//		*pdwInOut = 0;
	//	}

	//	//ZeroMemory(rgdod, cbData * (*pdwInOut));
	//}

	return hr;
}

static HRESULT __stdcall DInput8DeviceAcquireHook(IDirectInputDevice8* device)
{
	if (ImGuiStates::s_bImGuiWantsMouseDisabled)
		return DI_OK;

	return g_sDInput8DeviceAcquireOriginal(device);
}

class DirectInputHook
{
public:
	static bool Initialize()
	{
		void* vtable[32];

		if (GetDInput8DeviceVTable(vtable))
		{
			MH_STATUS mhStatus;

			// GetDeviceState
			if (!g_sDInput8DeviceGetDeviceStateOriginal)
			{
				mhStatus = MH_CreateHook(vtable[9], &DInput8DeviceGetDeviceStateHook, (void**)&g_sDInput8DeviceGetDeviceStateOriginal);

				if (mhStatus != MH_OK)
				{
					Logger::LogError(String::Format("[DirectInputHook] Could not Hook GetDeviceState! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
					return false;
				}

				Logger::LogDebug("[DirectInputHook] Hooked GetDeviceState.");
			}

			// GetDeviceData
			if (!g_sDInput8DeviceGetDeviceDataOriginal)
			{
				mhStatus = MH_CreateHook(vtable[10], &DInput8DeviceGetDeviceDataHook, (void**)&g_sDInput8DeviceGetDeviceDataOriginal);

				if (mhStatus != MH_OK)
				{
					Logger::LogError(String::Format("[DirectInputHook] Could not Hook GetDeviceData! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
					return false;
				}

				Logger::LogDebug("[DirectInputHook] Hooked GetDeviceData.");
			}

			// Acquire
			if (!g_sDInput8DeviceAcquireOriginal)
			{
				mhStatus = MH_CreateHook(vtable[7], &DInput8DeviceAcquireHook, (void**)&g_sDInput8DeviceAcquireOriginal);

				if (mhStatus != MH_OK)
				{
					Logger::LogError(String::Format("[DirectInputHook] Could not Hook Acquire! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
					return false;
				}

				Logger::LogDebug("[DirectInputHook] Hooked Acquire.");
			}

			return true;
		}
		else
		{
			Logger::LogError("[DirectInputHook] Failed to get device vtable!");
		}
		
		return false;
	}
	static bool GetDInput8DeviceVTable(void** vtable)
	{
		IDirectInput8W* dinput8 = nullptr;

		// Create DirectInput8 device
		if (DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8W, (void**)&dinput8, 0) != DI_OK)
			return false;

		IDirectInputDevice8W* dummyDevice = nullptr;

		// Create device
		if (dinput8->CreateDevice(GUID_SysKeyboard, &dummyDevice, NULL) != DI_OK)
		{
			dinput8->Release();
			return false;
		}

		// Get vtable
		memcpy(vtable, *(void***)dummyDevice, 32 * 4);

		// Free stuff
		dinput8->Release();
		dummyDevice->Release();

		return true;
	}
};