#pragma once

using namespace IVSDKDotNet;

namespace CLR
{

	/// <summary>
	/// The main bridge between IVSDKDotNet.asi and IVSDKDotNetWrapper.dll.
	/// There can only be one instance of this class.
	/// </summary>
	public ref class CLRBridge
	{
	public:

		/// <summary>
		/// If set to true, communication between IVSDKDotNet.asi and IVSDKDotNetWrapper.dll is disabled.
		/// This is usually only set to true if an error occured while trying to load the IV-SDK .NET Manager.
		/// </summary>
		static property bool IsBridgeDisabled
		{
		public:
			bool get()
			{
				return m_bIsBridgeDisabled;
			}
		internal:
			void set(bool value)
			{
				m_bIsBridgeDisabled = value;
			}
		}

		/// <summary>
		/// Tells the IVSDKDotNet.asi that it can free its library and exit the thread. 
		/// </summary>
		static property bool CanTerminate
		{
		public:
			bool get()
			{
				return m_bCanTerminate;
			}
		internal:
			void set(bool value)
			{
				m_bCanTerminate = value;
			}
		}

		/// <summary>
		/// Will get set to true when everything is about to shut down. 
		/// </summary>
		static property bool IsShuttingDown
		{
		public:
			bool get()
			{
				return m_bShuttingDown;
			}
		internal:
			void set(bool value)
			{
				m_bShuttingDown = value;
			}
		}

		/// <summary>
		/// Will get set to true only if the IV-SDK .NET ScriptHookDotNet mod loader is activated AND the user installed the old ScriptHookDotNet to avoid conflicts.
		/// </summary>
		static property bool DisableScriptHookDotNetLoading
		{
		public:
			bool get()
			{
				return m_bDisableScriptHookDotNetLoading;
			}
		internal:
			void set(bool value)
			{
				m_bDisableScriptHookDotNetLoading = value;
			}
		}

		/// <summary>
		/// Will get set to true when any ImGui window is open and it wants text input.
		/// </summary>
		static property bool DisableInputs
		{
		public:
			bool get()
			{
				return m_bDisableInputs;
			}
		internal:
			void set(bool value)
			{
				m_bDisableInputs = value;
			}
		}

		/// <summary>
		/// Gets the current version of IV-SDK .NET
		/// </summary>
		static property String^ Version
		{
		public:
			String^ get()
			{
				return m_sVersion;
			}
		}

		/// <summary>
		/// Gets the current log file name for this session.
		/// This will only get used when the setting 'CreateLogFilesInMainDirectory' is set to false.
		/// Format: IVSDKDotNet@[DAY][MONTH][YEAR]@[MILLISECOND].log
		/// </summary>
		static property String^ CurrentLogFileName
		{
		public:
			String^ get()
			{
				return m_sLogFileName;
			}
		internal:
			void set(String^ value)
			{
				m_sLogFileName = value;
			}
		}

		/// <summary>
		/// Gets the full path to the IVSDKDotNet folder.
		/// </summary>
		static property String^ IVSDKDotNetPath
		{
		public:
			String^ get()
			{
				return m_sIVSDKDotNetPath;
			}
		internal:
			void set(String^ value)
			{
				m_sIVSDKDotNetPath = value;
			}
		}

		/// <summary>
		/// Gets the full path to the bin folder inside the IVSDKDotNet directory.
		/// </summary>
		static property String^ IVSDKDotNetBinaryPath
		{
		public:
			String^ get()
			{
				return m_sIVSDKDotNetBinaryPath;
			}
		internal:
			void set(String^ value)
			{
				m_sIVSDKDotNetBinaryPath = value;
			}
		}

		/// <summary>
		/// Gets the full path to the data folder inside the IVSDKDotNet directory.
		/// </summary>
		static property String^ IVSDKDotNetDataPath
		{
		public:
			String^ get()
			{
				return m_sIVSDKDotNetDataPath;
			}
		internal:
			void set(String^ value)
			{
				m_sIVSDKDotNetDataPath = value;
			}
		}

		/// <summary>
		/// Gets the full path to the logs folder inside the IVSDKDotNet directory.
		/// </summary>
		static property String^ IVSDKDotNetLogsPath
		{
		public:
			String^ get()
			{
				return m_sIVSDKDotNetLogsPath;
			}
		internal:
			void set(String^ value)
			{
				m_sIVSDKDotNetLogsPath = value;
			}
		}

		/// <summary>
		/// Gets the full path to the plugins folder inside the IVSDKDotNet directory.
		/// </summary>
		static property String^ IVSDKDotNetPluginsPath
		{
		public:
			String^ get()
			{
				return m_sIVSDKDotNetPluginsPath;
			}
		internal:
			void set(String^ value)
			{
				m_sIVSDKDotNetPluginsPath = value;
			}
		}

		/// <summary>
		/// Gets the full path to the scripts folder inside the IVSDKDotNet directory.
		/// </summary>
		static property String^ IVSDKDotNetScriptsPath
		{
		public:
			String^ get()
			{
				return m_sIVSDKDotNetScriptsPath;
			}
		internal:
			void set(String^ value)
			{
				m_sIVSDKDotNetScriptsPath = value;
			}
		}

		/// <summary>
		/// Gets the loaded IVSDKDotNet settings file.
		/// </summary>
		static property SettingsFile^ Settings
		{
		public:
			SettingsFile^ get()
			{
				return m_cSettings;
			}
		internal:
			void set(SettingsFile^ value)
			{
				m_cSettings = value;
			}
		}

    public:
		static System::Diagnostics::Process^ TheGTAProcess;

	public:
		static void Initialize(uint32_t version, uint32_t baseAddress);

		static void InvokeTickEvents();
		static void InvokeGameLoadEvents();
		static void InvokeGameLoadPriorityEvents();
		static void InvokeMountDeviceEvents();
		static void InvokeDrawingEvents();
		static void InvokeProcessCameraEvents();
		static void InvokeProcessAutomobileEvents(uint32_t* vehPtr);
		static void InvokeProcessPadEvents(uint32_t* padPtr);
		static void InvokeIngameStartupEvent();

	internal:
		static void Cleanup();

	private:
		static bool m_bIsBridgeDisabled = false;
		static bool m_bCanTerminate = false;
		static bool m_bShuttingDown = false;
		static bool m_bDisableScriptHookDotNetLoading = false;
		static bool m_bDisableInputs = false;

		static String^ m_sVersion = "1.6";
		static String^ m_sLogFileName;
		static String^ m_sIVSDKDotNetPath;
		static String^ m_sIVSDKDotNetBinaryPath;
		static String^ m_sIVSDKDotNetDataPath;
		static String^ m_sIVSDKDotNetLogsPath;
		static String^ m_sIVSDKDotNetPluginsPath;
		static String^ m_sIVSDKDotNetScriptsPath;

		static SettingsFile^ m_cSettings;

};
}