#include "pch.h"
#include "CLRBridge.h"

using namespace IVSDKDotNet;
using namespace IVSDKDotNet::Manager;

namespace CLR {

	void CLRBridge::Initialize(int version, uint32_t baseAddress)
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		// Set stuff
		CGame::GameVersion = (eGameVersion)version;
		AddressSetter::Initialise(version, baseAddress);
		MemoryAccess::Initialise(version, baseAddress);

		// Load manager script
		try {
			String^ managerScriptPath = Application::StartupPath + "\\IVSDKDotNet\\IVSDKDotNet.Manager.dll";

			if (!File::Exists(managerScriptPath))
				goto ERR;

			Assembly^ assembly = Assembly::UnsafeLoadFrom(managerScriptPath);

			// Get types from assembly
			array<Type^>^ containedTypes = assembly->GetTypes();
			for (int i = 0; i < containedTypes->Length; i++) {
				Type^ containedType = containedTypes[i];

				if (containedType->IsSubclassOf(ManagerScript::typeid)) {

					// Create new instance of type for assembly
					ManagerScript^ ms = (ManagerScript^)assembly->CreateInstance(containedType->FullName);

					if (ms) {
						// Set static instance
						ManagerScript::s_Instance = ms;

						// Load scripts
						ms->LoadScripts();

						return;
					}

					SHOW_ERROR_MESSAGE("'ms' is nullptr in CLR::CLRBridge::Initialize!");
				}
			}

		} catch (ReflectionTypeLoadException^ ex) {

			array<Exception^>^ exs = ex->LoaderExceptions;
			for (int i = 0; i < exs->Length; i++) {
				Exception^ e = exs[i];
				SHOW_ERROR_MESSAGE(String::Format("A ReflectionTypeLoadException occured while loading manager assembly. Details: {0}", e->ToString()));
			}

		} catch (Exception^ ex) {
			SHOW_ERROR_MESSAGE(String::Format("An unknown exception occured while loading manager assembly. Details: {0}", ex->ToString()));
		}

ERR:

		CLRBridge::IsBridgeDisabled = true;
		SHOW_WARN_MESSAGE("CLR Bridge got disabled due to IV-SDK DotNet load errors.");
	}

	void CLRBridge::InvokeTickEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance) ManagerScript::s_Instance->RaiseTick();
	}
	void CLRBridge::InvokeGameLoadEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance) ManagerScript::s_Instance->RaiseGameLoad();
	}
	void CLRBridge::InvokeGameLoadPriorityEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance) ManagerScript::s_Instance->RaiseGameLoadPriority();
	}
	void CLRBridge::InvokeMountDeviceEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;
		
		if (ManagerScript::s_Instance) ManagerScript::s_Instance->RaiseMountDevice();
	}
	void CLRBridge::InvokeDrawingEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance) ManagerScript::s_Instance->RaiseDrawing();
	}
	void CLRBridge::InvokeProcessCameraEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance) ManagerScript::s_Instance->RaiseProcessCamera();
	}
	void CLRBridge::InvokeProcessAutomobileEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance) ManagerScript::s_Instance->RaiseProcessAutomobile();
	}
	void CLRBridge::InvokeProcessPadEvents()
	{
		if (CLRBridge::IsBridgeDisabled)
			return;

		if (ManagerScript::s_Instance) ManagerScript::s_Instance->RaiseProcessPad();
	}

}
