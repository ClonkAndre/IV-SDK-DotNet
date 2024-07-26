#include "pch.h"

static XInputGetState_t originalXInputGetState = NULL;

static DWORD WINAPI HookedXInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
{
    if (ImGuiStates::s_bDisableControllerInput)
        return ERROR_DEVICE_NOT_CONNECTED;

	return originalXInputGetState(dwUserIndex, pState);
}

class XInputHook
{
public:
	static bool Initialize()
	{
        HMODULE hXInput = GetModuleHandle(L"xinput1_3.dll");

        if (hXInput)
        {
            originalXInputGetState = (XInputGetState_t)GetProcAddress(hXInput, "XInputGetState");

            if (originalXInputGetState)
            {
                 MH_STATUS mhStatus = MH_CreateHook(originalXInputGetState, HookedXInputGetState, (LPVOID*)&originalXInputGetState);

                 if (mhStatus != MH_OK)
                 {
                     Logger::LogError(String::Format("[XInputHook] Could not Hook XInputGetState! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
                     return false;
                 }

                 Logger::LogDebug("[XInputHook] Hooked XInputGetState.");

                 return true;
            }
        }

		return false;
	}
};