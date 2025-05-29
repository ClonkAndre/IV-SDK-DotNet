#include "pch.h"

enum D3D9VTable : int
{
    VTABLE_QueryInterface = 0,
    VTABLE_AddRef,
    VTABLE_Release,
    VTABLE_TestCooperativeLevel,
    VTABLE_GetAvailableTextureMem,
    VTABLE_EvictManagedResources,
    VTABLE_GetDirect3D,
    VTABLE_GetDeviceCaps,
    VTABLE_GetDisplayMode,
    VTABLE_GetCreationParameters,
    VTABLE_SetCursorProperties,
    VTABLE_SetCursorPosition,
    VTABLE_ShowCursor,
    VTABLE_CreateAdditionalSwapChain,
    VTABLE_GetSwapChain,
    VTABLE_GetNumberOfSwapChains,
    VTABLE_Reset,
    VTABLE_Present,
    VTABLE_GetBackBuffer,
    VTABLE_GetRasterStatus,
    VTABLE_SetDialogBoxMode,
    VTABLE_SetGammaRamp,
    VTABLE_GetGammaRamp,
    VTABLE_CreateTexture,
    VTABLE_CreateVolumeTexture,
    VTABLE_CreateCubeTexture,
    VTABLE_CreateVertexBuffer,
    VTABLE_CreateIndexBuffer,
    VTABLE_CreateRenderTarget,
    VTABLE_CreateDepthStencilSurface,
    VTABLE_UpdateSurface,
    VTABLE_UpdateTexture,
    VTABLE_GetRenderTargetData,
    VTABLE_GetFrontBufferData,
    VTABLE_StretchRect,
    VTABLE_ColorFill,
    VTABLE_CreateOffscreenPlainSurface,
    VTABLE_SetRenderTarget,
    VTABLE_GetRenderTarget,
    VTABLE_SetDepthStencilSurface,
    VTABLE_GetDepthStencilSurface,
    VTABLE_BeginScene,
    VTABLE_EndScene,
    VTABLE_Clear,
    VTABLE_SetTransform,
    VTABLE_GetTransform,
    VTABLE_MultiplyTransform,
    VTABLE_SetViewport,
    VTABLE_GetViewport,
    VTABLE_SetMaterial,
    VTABLE_GetMaterial,
    VTABLE_SetLight,
    VTABLE_GetLight,
    VTABLE_LightEnable,
    VTABLE_GetLightEnable,
    VTABLE_SetClipPlane,
    VTABLE_GetClipPlane,
    VTABLE_SetRenderState,
    VTABLE_GetRenderState,
    VTABLE_CreateStateBlock,
    VTABLE_BeginStateBlock,
    VTABLE_EndStateBlock,
    VTABLE_SetClipStatus,
    VTABLE_GetClipStatus,
    VTABLE_GetTexture,
    VTABLE_SetTexture,
    VTABLE_GetTextureStageState,
    VTABLE_SetTextureStageState,
    VTABLE_GetSamplerState,
    VTABLE_SetSamplerState,
    VTABLE_ValidateDevice,
    VTABLE_SetPaletteEntries,
    VTABLE_GetPaletteEntries,
    VTABLE_SetCurrentTexturePalette,
    VTABLE_GetCurrentTexturePalette,
    VTABLE_SetScissorRect,
    VTABLE_GetScissorRect,
    VTABLE_SetSoftwareVertexProcessing,
    VTABLE_GetSoftwareVertexProcessing,
    VTABLE_SetNPatchMode,
    VTABLE_GetNPatchMode,
    VTABLE_DrawPrimitive,
    VTABLE_DrawIndexedPrimitive,
    VTABLE_DrawPrimitiveUP,
    VTABLE_DrawIndexedPrimitiveUP,
    VTABLE_ProcessVertices,
    VTABLE_CreateVertexDeclaration,
    VTABLE_SetVertexDeclaration,
    VTABLE_GetVertexDeclaration,
    VTABLE_SetFVF,
    VTABLE_GetFVF,
    VTABLE_CreateVertexShader,
    VTABLE_SetVertexShader,
    VTABLE_GetVertexShader,
    VTABLE_SetVertexShaderConstantF,
    VTABLE_GetVertexShaderConstantF,
    VTABLE_SetVertexShaderConstantI,
    VTABLE_GetVertexShaderConstantI,
    VTABLE_SetVertexShaderConstantB,
    VTABLE_GetVertexShaderConstantB,
    VTABLE_SetStreamSource,
    VTABLE_GetStreamSource,
    VTABLE_SetStreamSourceFreq,
    VTABLE_GetStreamSourceFreq,
    VTABLE_SetIndices,
    VTABLE_GetIndices,
    VTABLE_CreatePixelShader,
    VTABLE_SetPixelShader,
    VTABLE_GetPixelShader,
    VTABLE_SetPixelShaderConstantF,
    VTABLE_GetPixelShaderConstantF,
    VTABLE_SetPixelShaderConstantI,
    VTABLE_GetPixelShaderConstantI,
    VTABLE_SetPixelShaderConstantB,
    VTABLE_GetPixelShaderConstantB,
    VTABLE_DrawRectPatch,
    VTABLE_DrawTriPatch,
    VTABLE_DeletePatch,
    VTABLE_CreateQuery,
    VTABLE_COUNT
};

// Modified Direct3D9 Hook code from the InGameTimecycEditor Mod for GTA IV made by akifle47.
// https://github.com/akifle47/InGameTimecycEditor

static D3D9DeviceBeginSceneT* g_sD3D9DeviceBeginSceneOriginal = nullptr;
static D3D9DeviceEndSceneT* g_sD3D9DeviceEndSceneOriginal = nullptr;
static D3D9DeviceResetT* g_sD3D9DeviceResetOriginal = nullptr;

static HRESULT __stdcall D3D9DeviceBeginSceneHook(LPDIRECT3DDEVICE9 device)
{
    HRESULT result = g_sD3D9DeviceBeginSceneOriginal(device);

    ImGuiDraw::OnAfterD3D9DeviceBeginScene(device);

	return result;
}
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

            if (!g_sD3D9DeviceBeginSceneOriginal)
            {
                mhStatus = MH_CreateHook((LPVOID*)g_sD3D9Device_vtbl[D3D9VTable::VTABLE_BeginScene], &D3D9DeviceBeginSceneHook, (void**)&g_sD3D9DeviceBeginSceneOriginal);

                if (mhStatus != MH_OK)
                {
                    Logger::LogErrorEx("[DXHook] Could not hook IDirect3DDevice9::BeginScene! Details: {0}", gcnew String(MH_StatusToString(mhStatus)));
                    return false;
                }

                Logger::LogDebug("[DXHook] Hooked BeginScene.");
            }

			if (!g_sD3D9DeviceEndSceneOriginal)
			{
				mhStatus = MH_CreateHook((LPVOID*)g_sD3D9Device_vtbl[D3D9VTable::VTABLE_EndScene], &D3D9DeviceEndSceneHook, (void**)&g_sD3D9DeviceEndSceneOriginal);

				if (mhStatus != MH_OK)
				{
					Logger::LogErrorEx("[DXHook] Could not hook IDirect3DDevice9::EndScene! Details: {0}", gcnew String(MH_StatusToString(mhStatus)));
					return false;
				}

				Logger::LogDebug("[DXHook] Hooked EndScene.");
			}

			if (!g_sD3D9DeviceResetOriginal)
			{
				mhStatus = MH_CreateHook((LPVOID*)g_sD3D9Device_vtbl[D3D9VTable::VTABLE_Reset], &D3D9DeviceResetHook, (void**)&g_sD3D9DeviceResetOriginal);

				if (mhStatus != MH_OK)
				{
					Logger::LogErrorEx("[DXHook] Could not hook IDirect3DDevice9::Reset! Details: {0}", gcnew String(MH_StatusToString(mhStatus)));
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