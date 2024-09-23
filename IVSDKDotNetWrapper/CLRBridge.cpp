#include "pch.h"
#include "CLRBridge.h"

using namespace IVSDKDotNet;
using namespace IVSDKDotNet::Manager;

WNDPROC originalWndProc = nullptr;
LRESULT __stdcall WndProcHook(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Window starts being destroyed
	if (uMsg == WM_CLOSE || uMsg == WM_DESTROY) // WM_DESTROY
	{
		// Invoke event for scripts
		RAGE::RaiseOnExit();

		// Cleanup internal things
		CLR::CLRBridge::Cleanup();

		// Wait for cleanup process to finish
		while (!CLR::CLRBridge::CanTerminate)
		{
			Sleep(1);
		}

		// Call the original function
		return CallWindowProc(originalWndProc, hWnd, uMsg, wParam, lParam);
	}

	// Invoke event
	RAGE::RaiseOnWndProcMessageReceived(IntPtr(hWnd), uMsg, UIntPtr(wParam), IntPtr(lParam));

	// Invoke ImGui WndProc
	if (ImGuiDraw::OnWndProc(hWnd, uMsg, wParam, lParam))
		return 1L;

	// Call the original function
	return CallWindowProc(originalWndProc, hWnd, uMsg, wParam, lParam);
}

namespace CLR
{

	void CLRBridge::Initialize(uint32_t version, uint32_t baseAddress)
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		// Set paths
		IVSDKDotNetPath =			Application::StartupPath + "\\IVSDKDotNet";
		IVSDKDotNetBinaryPath =		IVSDKDotNetPath + "\\bin";
		IVSDKDotNetDataPath =		IVSDKDotNetPath + "\\data";
		IVSDKDotNetLogsPath =		IVSDKDotNetPath + "\\logs";
		IVSDKDotNetPluginsPath =	IVSDKDotNetPath + "\\plugins";
		IVSDKDotNetScriptsPath =	IVSDKDotNetPath + "\\scripts";
		String^ managerScriptPath = IVSDKDotNetPath + "\\IVSDKDotNet.Manager.dll";

		// Set current log file name
		DateTime dtNow = DateTime::Now;
		CurrentLogFileName = String::Format("IVSDKDotNet@{0}{1}{2}@{3}.log", dtNow.Day, dtNow.Month, dtNow.Year, dtNow.Millisecond);

		// Initialize and try loading the IVSDKDotNet settings file
		Settings = gcnew SettingsFile(IVSDKDotNetPath + "\\config.ini");
		bool settingsLoadResult = Settings->Load();
		
		// Initialize logger
		Logger::Initialize();

		// Force english culture of current thread
		System::Globalization::CultureInfo^ cultureInfo = gcnew System::Globalization::CultureInfo("en-US");
		System::Threading::Thread::CurrentThread->CurrentCulture = cultureInfo;
		System::Threading::Thread::CurrentThread->CurrentUICulture = cultureInfo;

		// Print about text to console
#if _DEBUG
		Logger::Log(String::Format("IV-SDK .NET DEBUG version {0} by ItsClonkAndre", Version));

		// Launch debugger
		if (Settings->GetBoolean("DEBUG", "LaunchDebugger", false))
			Debugger::Launch();
#elif PREVIEW
		Logger::Log(String::Format("IV-SDK .NET PREVIEW version {0} by ItsClonkAndre", Version));
#else
		Logger::Log(String::Format("IV-SDK .NET Release version {0} by ItsClonkAndre", Version));
#endif

		// Log settings file load result
		if (settingsLoadResult)
			Logger::Log("Loaded IV-SDK .NET config.ini!");
		else
			Logger::LogWarning("Could not load IV-SDK .NET config.ini! Using default settings.");

		// Do checks
		if (!File::Exists(managerScriptPath))
		{
			Logger::LogError("Could not initialize IV-SDK .NET because the IVSDKDotNet.Manager.dll file was not found inside the IVSDKDotNet directory!", false);
			goto ERR;
		}
		if (!File::Exists(IVSDKDotNetDataPath + "\\public-sans.regular.ttf"))
		{
			Logger::LogError("Could not initialize IV-SDK .NET because the public-sans.regular.ttf file was not found inside the IVSDKDotNet->Data directory!", false);
			goto ERR;
		}
		if (!File::Exists(IVSDKDotNetBinaryPath + "\\Newtonsoft.Json.dll"))
		{
			Logger::LogError("Could not initialize IV-SDK .NET because the Newtonsoft.Json.dll file was not found inside the IVSDKDotNet->bin directory!", false);
			goto ERR;
		}

		// Initialize Memory Access stuff
		MemoryAccess::Initialise(version, baseAddress);

		// Get the GTA IV Process
		TheGTAProcess = Process::GetCurrentProcess();
		
		// Wait till process has a MainWindowHandle and for g_pDirect3DDevice to return a valid pointer
		while (TheGTAProcess->MainWindowHandle == IntPtr::Zero)
			Sleep(100);
		while (rage::g_pDirect3DDevice == nullptr)
			Sleep(100);

		// Initialize stuff
		MH_STATUS minHookStatus = MH_Initialize();

		if (minHookStatus != MH_STATUS::MH_OK)
			Logger::LogError(String::Format("[MinHook] Failed to initialize! Details: {0}", gcnew String(MH_StatusToString(minHookStatus))));

		// Hook stuff
		if (DXHook::Initialize())
			Logger::LogDebug("[DXHook] Done!");
		if (DirectInputHook::Initialize())
			Logger::LogDebug("[DirectInputHook] Done!");
		if (XInputHook::Initialize())
			Logger::LogDebug("[XInputHook] Done!");
		if (UnmanagedGameHooks::Initialize())
			Logger::LogDebug("[GameHooks] Done!");

		// FindWindow(L"grcWindow", L"GTAIV")
		originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr((HWND)TheGTAProcess->MainWindowHandle.ToPointer(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProcHook)));

		// Enable hooks
		minHookStatus = MH_EnableHook(MH_ALL_HOOKS);

		if (minHookStatus != MH_STATUS::MH_OK)
			Logger::LogError(String::Format("[MinHook] Failed to enable Hooks! Details: {0}", gcnew String(MH_StatusToString(minHookStatus))));

		// Schleep a bit
		Sleep(1100);

		// Do late checks
		if (Settings->GetBoolean("Scripts", "LoadScriptHookDotNetScripts", true))
		{
			if (File::Exists("ScriptHookDotNet.dll") || File::Exists("ScriptHookDotNet.asi"))
			{
				String^ msg = String::Format("Incompability detected!{0}{0}"
					+ "Please remove the old ScriptHookDotNet if you want to use the ScriptHookDotNet mod loader from IV-SDK .NET!{0}{0}"
					+ "The files that would need to be removed: ScriptHookDotNet.dll and ScriptHookDotNet.asi{0}{0}"
					+ "- Why am i seeing this message?{0}"
					+ "You are seeing this message because the 'LoadScriptHookDotNetScripts' option in the IV-SDK .NET config file is enabled, which enables the experimental ScriptHookDotNet mod loader of IV-SDK .NET. For more information about this, open the Console and type in 'wiki' to get to the IV-SDK .NET GitHub Wiki page.{0}{0}"
					+ "Would you like to close the game now and remove the old ScriptHookDotNet?", Environment::NewLine);

				switch (MessageBox::Show(msg,
					"IV-SDK .NET",
					MessageBoxButtons::YesNo,
					MessageBoxIcon::Warning,
					MessageBoxDefaultButton::Button1,
					MessageBoxOptions::DefaultDesktopOnly))
				{
					case DialogResult::Yes:
						Environment::Exit(0);
						break;
					case DialogResult::No:
						DisableScriptHookDotNetLoading = true;
						MessageBox::Show("Disabled the IV-SDK .NET ScriptHookDotNet mod loader to avoid conflicts.", "IV-SDK .NET", MessageBoxButtons::OK, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button1, MessageBoxOptions::DefaultDesktopOnly);
						break;
				}
			}
		}

		// Do early assembly loading
		try
		{
			// Load Newtonsoft.Json assembly
			Assembly::UnsafeLoadFrom(IVSDKDotNetBinaryPath + "\\Newtonsoft.Json.dll");
			Logger::LogDebug("Early loaded the Newtonsoft.Json.dll assembly.");
		}
		catch (Exception^ ex)
		{
			Logger::LogError(String::Format("An exception occured while trying to early load some assemblies. Details: {0}", ex->ToString()));

#if _DEBUG
			if (Debugger::IsAttached)
				throw;
#endif // _DEBUG

			goto ERR;
		}

		// Load manager script
		try
		{
			// Load the manager assembly
			Assembly^ assembly = Assembly::UnsafeLoadFrom(managerScriptPath);

			// Get types from assembly
			array<Type^>^ containedTypes = assembly->GetTypes();
			for (int i = 0; i < containedTypes->Length; i++)
			{
				Type^ containedType = containedTypes[i];

				if (containedType->IsSubclassOf(ManagerScript::typeid))
				{
					// Create new instance of type for assembly
					ManagerScript^ ms = (ManagerScript^)assembly->CreateInstance(containedType->FullName);

					if (ms)
					{
						// Set static instance
						ManagerScript::s_Instance = ms;

						// Apply Settings
						ms->ApplySettings(Settings);

						// Create and set dummy script for manager
						ms->SetDummyScript(gcnew Script(Guid("00000000-0000-0000-0000-000000000001")));

						// Load scripts
						if (!Settings->GetBoolean("DEBUG", "DisableScriptLoadOnStartup", false))
							ms->LoadScripts();

						return;
					}

					// This line of code should never be reached
					Logger::LogError("'ms' is nullptr in CLR::CLRBridge::Initialize!");
				}
			}

		}
		catch (ReflectionTypeLoadException^ ex)
		{
			array<Exception^>^ exs = ex->LoaderExceptions;
			for (int i = 0; i < exs->Length; i++)
			{
				Exception^ e = exs[i];
				Logger::LogError(String::Format("A ReflectionTypeLoadException occured while trying to load the IV-SDK .NET Manager. Details: {0}", e->ToString()), false);
			}

#if _DEBUG
			if (Debugger::IsAttached)
				throw;
#endif // _DEBUG
		}
		catch (Exception^ ex)
		{
			Logger::LogError(String::Format("An exception occured while trying to load the IV-SDK .NET Manager. Details: {0}", ex->ToString()));
		
#if _DEBUG
			if (Debugger::IsAttached)
				throw;
#endif // _DEBUG
		}


ERR:
		CLRBridge::IsBridgeDisabled = true;
		Logger::ForceCreateLogFile();
		MessageBox::Show("IV-SDK .NET got disabled due to errors while trying to load it. Check the 'IVSDKDotNet.log' file, to find out what went wrong.", "IV-SDK .NET", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}

	void CLRBridge::InvokeTickEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->RaiseTick();
	}
	void CLRBridge::InvokeGameLoadEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->RaiseGameLoad();
	}
	void CLRBridge::InvokeGameLoadPriorityEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->RaiseGameLoadPriority();

		// Initialize native function hooks
		Native::Hooks::Initialize();
		if (Native::NativeHookFunctions::Initialize())
			Logger::LogDebug("[NativeHook] Done!");
	}
	void CLRBridge::InvokeMountDeviceEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;
		
		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->RaiseMountDevice();
	}
	void CLRBridge::InvokeDrawingEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->RaiseDrawing();
	}
	void CLRBridge::InvokeProcessCameraEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->RaiseProcessCamera();
	}
	void CLRBridge::InvokeProcessAutomobileEvents(uint32_t* vehPtr)
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->RaiseProcessAutomobile(UIntPtr(vehPtr));
	}
	void CLRBridge::InvokeProcessPadEvents(uint32_t* padPtr)
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance)
		{
			// Disable inputs if ImGui wants text input
			if (DisableInputs && !Native::Natives::IS_USING_CONTROLLER())
			{
				CPad* pad = reinterpret_cast<CPad*>(padPtr);

				for (int i = 0; i < 187; i++)
				{
					tPadValues* values = &pad->m_aValues[i];
					IVSDKDotNet::Enums::ePadControls control = (IVSDKDotNet::Enums::ePadControls)i;

					uint8_t newCurrentValue = 0;
					uint8_t newLastValue = 0;

					switch (control)
					{
						// All of these have to be set to 128, otherwise they can produce some ugly results

						case IVSDKDotNet::Enums::ePadControls::INPUT_MOVE_LEFT:
						case IVSDKDotNet::Enums::ePadControls::INPUT_MOVE_RIGHT:
						case IVSDKDotNet::Enums::ePadControls::INPUT_MOVE_UP:
						case IVSDKDotNet::Enums::ePadControls::INPUT_MOVE_DOWN:

						case IVSDKDotNet::Enums::ePadControls::INPUT_LOOK_LEFT:
						case IVSDKDotNet::Enums::ePadControls::INPUT_LOOK_RIGHT:
						case IVSDKDotNet::Enums::ePadControls::INPUT_LOOK_UP:
						case IVSDKDotNet::Enums::ePadControls::INPUT_LOOK_DOWN:

						case IVSDKDotNet::Enums::ePadControls::INPUT_VEH_MOVE_LEFT:
						case IVSDKDotNet::Enums::ePadControls::INPUT_VEH_MOVE_RIGHT:
						case IVSDKDotNet::Enums::ePadControls::INPUT_VEH_MOVE_UP:
						case IVSDKDotNet::Enums::ePadControls::INPUT_VEH_MOVE_DOWN:

						case IVSDKDotNet::Enums::ePadControls::INPUT_VEH_GUN_LEFT:
						case IVSDKDotNet::Enums::ePadControls::INPUT_VEH_GUN_RIGHT:
						case IVSDKDotNet::Enums::ePadControls::INPUT_VEH_GUN_UP:
						case IVSDKDotNet::Enums::ePadControls::INPUT_VEH_GUN_DOWN:

						case IVSDKDotNet::Enums::ePadControls::INPUT_FRONTEND_AXIS_X:
						case IVSDKDotNet::Enums::ePadControls::INPUT_FRONTEND_AXIS_Y:
						case IVSDKDotNet::Enums::ePadControls::INPUT_FRONTEND_RIGHT_AXIS_X:
						case IVSDKDotNet::Enums::ePadControls::INPUT_FRONTEND_RIGHT_AXIS_Y:

						case IVSDKDotNet::Enums::ePadControls::INPUT_MOUSE_UD:
						case IVSDKDotNet::Enums::ePadControls::INPUT_MOUSE_LR:

						case IVSDKDotNet::Enums::ePadControls::INPUT_MOVE_KEY_STUNTJUMP:

						case IVSDKDotNet::Enums::ePadControls::INPUT_FRONTEND_AXIS_UD:
						case IVSDKDotNet::Enums::ePadControls::INPUT_FRONTEND_AXIS_LR:

						case IVSDKDotNet::Enums::ePadControls::INPUT_VEH_MOVE_LEFT_2:
						case IVSDKDotNet::Enums::ePadControls::INPUT_VEH_MOVE_RIGHT_2:

							newCurrentValue = 128;
							newLastValue = 128;

							break;
					}

					values->m_nCurrentValue = newCurrentValue;
					values->m_nLastValue = newLastValue;
				}
			}

			// ManagerScript things
			if (ManagerScript::s_Instance->SwitchImGuiForceCursorProperty)
			{
				ImGuiIV::ForceCursor = !ImGuiIV::ForceCursor;
				ManagerScript::s_Instance->SwitchImGuiForceCursorProperty = false;
			}

			// Raise event for all subscribers
			ManagerScript::s_Instance->RaiseProcessPad(UIntPtr(padPtr));
		}
	}
	void CLRBridge::InvokeIngameStartupEvent()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->RaiseIngameStartup();
	}

	void CLRBridge::Cleanup()
	{
		// Return if already shutting down
		if (IsShuttingDown)
			return;

		IsShuttingDown = true;

		// Log
		Logger::Log("Application is closing, starting cleanup process...");

		// Start cleanup in manager script
		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->Cleanup();

		// MinHook
		MH_STATUS minHookStatus = MH_DisableHook(MH_ALL_HOOKS);

		if (minHookStatus != MH_STATUS::MH_OK)
			Logger::LogError(String::Format("[MinHook] Failed to disable Hooks! Details: {0}", gcnew String(MH_StatusToString(minHookStatus))), false);

		minHookStatus = MH_Uninitialize();

		if (minHookStatus != MH_STATUS::MH_OK)
			Logger::LogError(String::Format("[MinHook] Failed to uninitialize! Details: {0}", gcnew String(MH_StatusToString(minHookStatus))), false);

		// ImGui
		ImGuiDraw::UninitializeImGui();

		// Log
		Logger::Log("Cleanup process finished!");
		Logger::ForceCreateLogFile();

		CanTerminate = true;
	}

}
