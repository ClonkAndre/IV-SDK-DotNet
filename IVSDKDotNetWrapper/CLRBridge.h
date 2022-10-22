#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Windows::Forms;

namespace CLR {

	/// <summary>
	/// Bridge between IVSDKDotNet.asi and IVSDKDotNetWrapper.dll.
	/// There can only be one instance of this class.
	/// </summary>
	public ref class CLRBridge
	{
	public:
		static void Initialize(int version, uint32_t baseAddress);

		static void InvokeTickEvents();
		static void InvokeGameLoadEvents();
		static void InvokeGameLoadPriorityEvents();
		static void InvokeMountDeviceEvents();
		static void InvokeDrawingEvents();
		static void InvokeProcessCameraEvents();
		static void InvokeProcessAutomobileEvents();
		static void InvokeProcessPadEvents();

		// If set to true, communication between IVSDKDotNet.asi and IVSDKDotNetWrapper.dll is disabled.
		// This is usually only set to true if ManagerScript::s_Instance did not got set or if an error occured while trying to set it.
		static property bool IsBridgeDisabled {
			public:		bool get()			 { return isBridgeDisabled; }
			internal:	void set(bool value) { isBridgeDisabled = value; }
		}

	private:
		static bool isBridgeDisabled = false;
	};

}