// ==================================================================
// ==================================================================
// ================ IV-SDK .NET by ItsClonkAndre ====================
// =============== https://github.com/ClonkAndre ====================
// ==================================================================
// ==================== IV-SDK by Zolika1351 ========================
// =============== https://github.com/Zolika1351 ====================
// ==================================================================
// ==================================================================

#include "IVSDK.cpp"

#pragma region Variables
static HANDLE managedThreadHandle;
#pragma endregion

#pragma region Events
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
#pragma endregion

// Managed Entry Point Thread
DWORD WINAPI ManagedEntryPoint(HMODULE hModule)
{
	// Initialize IV-SDK .NET
	CLR::CLRBridge::Initialize((uint32_t)plugin::gameVer, AddressSetter::gBaseAddress);

	// Keep the plugin alive. I guess.
	while (!CLR::CLRBridge::CanTerminate)
	{
		Sleep(1000);
	}

	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

// IV-SDK Stuff
void plugin::gameStartupEvent()
{
	// Force english culture of current thread
	System::Globalization::CultureInfo^ cultureInfo = gcnew System::Globalization::CultureInfo("en-US");
	System::Threading::Thread::CurrentThread->CurrentCulture = cultureInfo;
	System::Threading::Thread::CurrentThread->CurrentUICulture = cultureInfo;

	// Launch a thread to get a managed entry point and to keep the plugin alive
	managedThreadHandle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&ManagedEntryPoint, GetCurrentModule(), 0, nullptr);

	// Subscribe to IV-SDK Events
	plugin::processScriptsEvent::Add(ScriptLoop);
	plugin::gameLoadEvent::Add(GameLoad);
	plugin::gameLoadPriorityEvent::Add(GameLoadPriority);
	plugin::mountDeviceEvent::Add(MountDevice);
	plugin::drawingEvent::Add(Drawing);
	plugin::processCameraEvent::Add(ProcessCamera);
	plugin::processAutomobileEvent::Add(ProcessAutomobile);
	plugin::processPadEvent::Add(ProcessPad);
	plugin::ingameStartupEvent::Add(IngameStartupEvent);
}