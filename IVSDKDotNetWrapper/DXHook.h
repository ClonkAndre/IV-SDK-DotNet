#include "pch.h"

// Modified Direct3D9 Hook code from the InGameTimecycEditor Mod for GTA IV made by akifle47.
// https://github.com/akifle47/InGameTimecycEditor

static D3D9DeviceEndSceneT* g_sD3D9DeviceEndSceneOriginal = nullptr;
static D3D9DeviceResetT* g_sD3D9DeviceResetOriginal = nullptr;

static HRESULT __stdcall D3D9DeviceEndSceneHook(LPDIRECT3DDEVICE9 device)
{
	ImGuiDraw::OnBeforeD3D9DeviceEndScene(device);

	return g_sD3D9DeviceEndSceneOriginal(device);
}
static HRESULT __stdcall D3D9DeviceResetHook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGuiDraw::OnBeforeD3D9DeviceReset(device);

	HRESULT hr = g_sD3D9DeviceResetOriginal(device, pPresentationParameters);

	ImGuiDraw::OnAfterD3D9DeviceReset();

	return hr;
}

class DXHook
{
public:
	static bool Initialize()
	{
		void* g_sD3D9Device_vtbl[119];

		if (GetD3D9DeviceVTable(g_sD3D9Device_vtbl))
		{
			MH_STATUS mhStatus;

			if (!g_sD3D9DeviceEndSceneOriginal)
			{
				mhStatus = MH_CreateHook((LPVOID*)g_sD3D9Device_vtbl[42], &D3D9DeviceEndSceneHook, (void**)&g_sD3D9DeviceEndSceneOriginal);

				if (mhStatus != MH_OK)
				{
					Logger::LogError(String::Format("[DXHook] Could not hook IDirect3DDevice9::EndScene! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
					return false;
				}

				Logger::LogDebug("[DXHook] Hooked EndScene.");
			}

			if (!g_sD3D9DeviceResetOriginal)
			{
				mhStatus = MH_CreateHook((LPVOID*)g_sD3D9Device_vtbl[16], &D3D9DeviceResetHook, (void**)&g_sD3D9DeviceResetOriginal);

				if (mhStatus != MH_OK)
				{
					Logger::LogError(String::Format("[DXHook] Could not hook IDirect3DDevice9::Reset! Details: {0}", gcnew String(MH_StatusToString(mhStatus))));
					return false;
				}

				Logger::LogDebug("[DXHook] Hooked Reset.");
			}

			return true;
		}
		else
		{
			Logger::LogError("[DXHook] Failed to get device vtable!");
		}

		return false;
	}
	static bool GetD3D9DeviceVTable(void** vtable)
	{
		IDirect3DDevice9* device = rage::g_pDirect3DDevice;

		if (!device)
			return false;

		memcpy(vtable, *reinterpret_cast<void***>(device), 119 * 4);

		return true;
	}
};