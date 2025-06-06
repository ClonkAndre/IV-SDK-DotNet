#pragma once
#include "pch.h"

// Direct3D9
typedef HRESULT(__stdcall D3D9DeviceBeginSceneT)(IDirect3DDevice9*);
typedef HRESULT(__stdcall D3D9DeviceEndSceneT)(IDirect3DDevice9*);
typedef HRESULT(__stdcall D3D9DeviceResetT)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

// DirectInput
typedef HRESULT(__stdcall DInput8DeviceGetDeviceStateT)(IDirectInputDevice8*, DWORD, LPVOID);
typedef HRESULT(__stdcall DInput8DeviceGetDeviceDataT)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
typedef HRESULT(__stdcall DInput8DeviceAcquireT)(IDirectInputDevice8*);

// XInput
typedef DWORD(WINAPI* XInputGetState_t)(DWORD, XINPUT_STATE*);

// Game Functions
typedef int(__cdecl AddSceneLightT)(uint32_t, uint32_t, uint32_t, CVector*, CVector*, CVector*, CVector*, float, int32_t, int32_t, float, float, float, float, float, int32_t, uint32_t, uint32_t);
typedef int(__cdecl RenderCoronaT)(int, uint8_t, uint8_t, uint8_t, float, CVector*, float, float, float, int, float, char, char, int);
typedef int(__cdecl GetTrafficLightStateT)(bool, int);

typedef bool(__cdecl RegisterNativeT)(uint32_t, LPVOID);
typedef bool(__stdcall RegisterNativeNoChecksT)(uint32_t, LPVOID);

typedef bool(__cdecl IsNetworkGameRunningT)();
typedef bool(__cdecl IsThisMachineTheServerT)();

typedef int(__cdecl DoPickupGlowT)();

typedef bool(__cdecl AddExplosionT)(int a1, int a2, int a3, int a4, int a5, char a6, int a7, int a8, float a9, int a10, int a11, int a12, int a13, int a14, char a15, char a16, int a17, char a18, int a19);