// ==================================================================
// ==================================================================
// ================ IV-SDK .NET by ItsClonkAndre ====================
// =============== https://github.com/ClonkAndre ====================
// ==================================================================
// ==================== IV-SDK by Zolika1351 ========================
// =============== https://github.com/Zolika1351 ====================
// ==================================================================
// ==================================================================

#define _CRT_SECURE_NO_WARNINGS
#define UNICODE
#pragma comment(lib, "version.lib")
#include <windows.h>
#include <stdint.h>
#include <string>
#include <list>
#include <d3dx9.h>
#include "injector/injector.hpp"

#include "Addresses.h"
#include "IVSDK.h"
#include "Hooks.h"

#pragma managed

namespace plugin
{

	// Events
	void ScriptLoop()
	{
		CLR::CLRBridge::InvokeTickEvents();
	}
	void GameLoad()
	{
		CLR::CLRBridge::InvokeGameLoadEvents();
	}
	void GameLoadPriority()
	{
		CLR::CLRBridge::InvokeGameLoadPriorityEvents();
	}
	void MountDevice()
	{
		CLR::CLRBridge::InvokeMountDeviceEvents();
	}
	void Drawing()
	{
		CLR::CLRBridge::InvokeDrawingEvents();
	}
	void ProcessCamera()
	{
		CLR::CLRBridge::InvokeProcessCameraEvents();
	}
	void ProcessAutomobile(CVehicle* veh)
	{
		CLR::CLRBridge::InvokeProcessAutomobileEvents((uint32_t*)veh);
	}
	void ProcessPad(CPad* pad)
	{
		CLR::CLRBridge::InvokeProcessPadEvents((uint32_t*)pad);
	}
	void IngameStartupEvent()
	{
		CLR::CLRBridge::InvokeIngameStartupEvent();
	}

	// Functions
	uint32_t DoHook(uint32_t address, void(*Function)())
	{
		if (address)
		{
			uint32_t origcall = (uint32_t)injector::ReadRelativeOffset(address + 1);

			injector::MakeCALL(address, Function);

			return origcall;
		}
		return 0;
	}

	// Methods
	void InitHooks()
	{
		processScriptsEvent::returnAddress = DoHook(AddressSetter::Get("Hooks", "processScriptsEvent"), processScriptsEvent::MainHook);
		gameLoadEvent::returnAddress = DoHook(AddressSetter::Get("Hooks", "gameLoadEvent"), gameLoadEvent::MainHook);
		gameLoadPriorityEvent::returnAddress = DoHook(AddressSetter::Get("Hooks", "gameLoadPriorityEvent"), gameLoadPriorityEvent::MainHook);
		drawingEvent::returnAddress = DoHook(AddressSetter::Get("Hooks", "drawingEvent"), drawingEvent::MainHook);
		processAutomobileEvent::callAddress = DoHook(AddressSetter::Get("Hooks", "processAutomobileEvent"), processAutomobileEvent::MainHook);
		processPadEvent::callAddress = DoHook(AddressSetter::Get("Hooks", "processPadEvent"), processPadEvent::MainHook);
		processCameraEvent::returnAddress = DoHook(AddressSetter::Get("Hooks", "processCameraEvent"), processCameraEvent::MainHook);
		mountDeviceEvent::returnAddress = DoHook(AddressSetter::Get("Hooks", "mountDeviceEvent"), mountDeviceEvent::MainHook);
		ingameStartupEvent::returnAddress = DoHook(AddressSetter::Get("Hooks", "ingameStartupEvent"), ingameStartupEvent::MainHook);
	}
	void InitWrapper()
	{
		// Initialize IV-SDK .NET
		CLR::CLRBridge::Initialize((uint32_t)plugin::gameVer, AddressSetter::gBaseAddress);

		// Subscribe to IV-SDK Events
		processScriptsEvent::Add(ScriptLoop);
		gameLoadEvent::Add(GameLoad);
		gameLoadPriorityEvent::Add(GameLoadPriority);
		mountDeviceEvent::Add(MountDevice);
		drawingEvent::Add(Drawing);
		processCameraEvent::Add(ProcessCamera);
		processAutomobileEvent::Add(ProcessAutomobile);
		processPadEvent::Add(ProcessPad);
		ingameStartupEvent::Add(IngameStartupEvent);
	}

	DWORD WINAPI Initialize(HMODULE hModule)
	{
		// Initialize AddressSetter
		if (!AddressSetter::bAddressesRead)
			AddressSetter::Init();

		// Init stuff
		InitHooks();
		//gameStartupEvent();
		InitWrapper();

		// Keep the plugin alive. I guess.
		while (!CLR::CLRBridge::CanTerminate)
			Sleep(1000);

		FreeLibraryAndExitThread(hModule, 0);
		return 0;
	}

}

#pragma unmanaged

// Entry point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:

			DisableThreadLibraryCalls(hModule);

			// Launch thread to initialize the plugin and all that stuff
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&plugin::Initialize, hModule, 0, nullptr);

			break;
	}
	return TRUE;
}