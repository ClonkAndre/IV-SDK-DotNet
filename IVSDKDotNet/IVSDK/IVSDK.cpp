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

namespace plugin
{
	HMODULE GetCurrentModule()
	{
		HMODULE hModule = NULL;
		GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)GetCurrentModule, &hModule);
		return hModule;
	}

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

	void InitHooks()
	{
		processScriptsEvent::returnAddress =	DoHook(AddressSetter::Get(0x21601, 0x95141),	processScriptsEvent::MainHook);
		gameLoadEvent::returnAddress =			DoHook(AddressSetter::Get(0x4ADB38, 0x770748),	gameLoadEvent::MainHook);
		gameLoadPriorityEvent::returnAddress =	DoHook(AddressSetter::Get(0x4ADA9D, 0x7706AD),	gameLoadPriorityEvent::MainHook);
		drawingEvent::returnAddress =			DoHook(AddressSetter::Get(0x46AFA8, 0x60E1C8),	drawingEvent::MainHook);
		processAutomobileEvent::callAddress =	DoHook(AddressSetter::Get(0x7FE9C6, 0x652C26),	processAutomobileEvent::MainHook);
		processPadEvent::callAddress =			DoHook(AddressSetter::Get(0x3C4002, 0x46A802),	processPadEvent::MainHook);
		processCameraEvent::returnAddress =		DoHook(AddressSetter::Get(0x52C4C2, 0x694232),	processCameraEvent::MainHook);
		mountDeviceEvent::returnAddress =		DoHook(AddressSetter::Get(0x3B2E27, 0x456C27),	mountDeviceEvent::MainHook);
		ingameStartupEvent::returnAddress =		DoHook(AddressSetter::Get(0x20379, 0x93F09),	ingameStartupEvent::MainHook);
	}

	void Init()
	{
		// Initialize AddressSetter if addresses where not read yet
		if (!AddressSetter::bAddressesRead)
			AddressSetter::Init();

		// Init stuff for specific versions
		switch (gameVer)
		{
			// Initialize stuff for 1070 and 1080
			case plugin::VERSION_1070:
			case plugin::VERSION_1080:
				InitHooks();
				gameStartupEvent();
				break;
		}

	}
}

// Entry point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:

			// Initialize plugin
			plugin::Init();

			break;
	}
	return TRUE;
}