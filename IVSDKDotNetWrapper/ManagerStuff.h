#pragma once

namespace IVSDKDotNet
{

	// Forward declarations
	ref class Script;

	namespace Manager
	{

		/// <summary>
		/// Only used for the IV-SDK .NET Manager.
		/// </summary>
		public ref class ManagerScript abstract
		{
		public:
			bool SwitchImGuiForceCursorProperty;

		public:

			// General stuff
			virtual void InitializationFinished(SettingsFile^ settings) abstract;
			virtual void Shutdown()								abstract;

			// Console
			virtual void OpenConsole()						abstract;
			virtual void CloseConsole()						abstract;
			virtual void ClearConsole()						abstract;

			virtual bool IsConsoleOpen()					abstract;

			virtual bool RegisterConsoleCommand(Guid fromScript, String^ name, Action<array<String^>^>^ actionToExecute) abstract;
			virtual bool ExecuteConsoleCommand(String^ name) abstract;

			virtual String^ GetLastConsoleCommand() abstract;
			virtual void ResetLastConsoleCommand() abstract;

			// Phone
			virtual bool RegisterPhoneNumber(Guid forScript, String^ number, Action^ dialedAction) abstract;
			virtual bool UnregisterPhoneNumber(Guid fromScript, String^ number) abstract;

			// Game
			virtual bool IsGameInFocus() abstract;
			virtual void GetPlayerAndCurrentVehicleHandle([OutAttribute] int% playerHandle, [OutAttribute] int% vehicleHandle) abstract;
			//virtual bool IsUsingController() abstract;

			// Script
			virtual void RaiseTick()														abstract;
			virtual void RaiseGameLoad()													abstract;
			virtual void RaiseGameLoadPriority()											abstract;
			virtual void RaiseMountDevice()													abstract;
			virtual void RaiseDrawing()														abstract;
			virtual void RaiseProcessCamera()												abstract;
			virtual void RaiseProcessAutomobile(UIntPtr vehPtr)								abstract;
			virtual void RaiseProcessPad(UIntPtr padPtr)									abstract;
			virtual void RaiseIngameStartup()												abstract;
			virtual void RaiseOnD3D9Frame(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)		abstract;
			virtual void RaiseOnBeforeNewImGuiFrame(IntPtr devicePtr)						abstract;

			virtual void LoadScripts()							abstract;
			virtual bool AbortScript(Guid id)					abstract;

			virtual Script^ GetScript(Guid id)					abstract;
			virtual Script^ GetScript(String^ name)				abstract;
			virtual bool IsScriptRunning(Guid id)				abstract;
			virtual bool IsScriptRunning(String^ name)			abstract;
			virtual bool IsIVSDKDotNetScript(Guid id)			abstract;
			virtual bool IsIVSDKDotNetScript(String^ name)		abstract;
			virtual String^ GetScriptName(Guid id)				abstract;
			virtual String^ GetScriptFullPath(Guid id)			abstract;
			virtual int GetActiveScriptsCount()					abstract;

			virtual bool SendScriptCommand(Guid sender, Guid toScript, String^ command, array<Object^>^ parameters, [OutAttribute] Object^% result) abstract;
			virtual bool SendScriptCommand(Guid sender, String^ toScript, String^ command, array<Object^>^ parameters, [OutAttribute] Object^% result) abstract;

			// Plugin
			virtual void LoadPlugins() abstract;
			
			virtual bool SendPluginCommand(bool isSenderAPlugin, Guid sender, Guid toPlugin, String^ command, array<Object^>^ parameters, [OutAttribute] Object^% result) abstract;
			virtual bool SendPluginCommand(bool isSenderAPlugin, Guid sender, String^ toPlugin, String^ command, array<Object^>^ parameters, [OutAttribute] Object^% result) abstract;

			// Thread
			virtual void WaitInScript(Guid id, int milliseconds) abstract;
			virtual Object^ GetScriptThisThreadIsOwnedBy() abstract;

			virtual void DispatchNativeCall(uint32_t hash, UIntPtr contextPointer) abstract;

			virtual int GetMainThreadID() abstract;
			virtual int GetCurrentThreadID() abstract;
			virtual bool IsThisThreadTheScriptRenderThread(int threadId) abstract;

			virtual void ThreadManager_StoreCurrentThreadTlsContext() abstract;
			virtual void ThreadManager_ChangeTlsContextOfCurrentThreadToContextOfTargetThread(int gameThreadId) abstract;
			virtual void ThreadManager_RestoreTlsContextForCurrentThread() abstract;

			// Native Calling
			generic <typename T>
			virtual T CallNativeUsingManagedNativeCaller(uint32_t hash, array<IVSDKDotNet::Native::NativeArg>^ args) abstract;

			virtual uint32_t TryGetNativeHashByName(String^ name) abstract;

			// Task
			virtual Guid StartNewTask(Guid forScript, Func<Object^>^ actionToExecute, Action<Object^>^ continueWithAction)	abstract;
			virtual Guid StartNewTimer(Guid forScript, int interval, Action^ actionToExecute)								abstract;

			virtual void WaitInTask(Guid id, int waitTimeInMilliseconds)						abstract;
			virtual void AbortTaskOrTimer(Guid id)												abstract;
			virtual void ChangeTimerState(Guid id, bool pause)									abstract;
			virtual void ChangeTimerInterval(Guid id, int interval)								abstract;

			// Direct3D9 Stuff
			virtual void DXManager_RegisterScriptTexture(String^ forScript, IntPtr ptr)			abstract;
			virtual void DXManager_RegisterTexture(IntPtr ptr)									abstract;

			virtual void DXManager_UnregisterTexture(IntPtr ptr)								abstract;

			// Hooking Stuff
			virtual bool MinHook_RegisterHook(String^ ofScript, uint32_t address) abstract;

			// Helper
			virtual String^ Helper_ConvertObjectToJsonString(Object^ obj, bool useFormatting) abstract;
			virtual Object^ Helper_ConvertJsonStringToObject(String^ str, Type^ targetType) abstract;

			// ScriptHookDotNet
			virtual int SHDN_LateInitializeScript(String^ name, Object^ script, [OutAttribute] String^% assemblyFullPath) abstract;

			virtual Object^ SHDN_GetScriptByName(String^ name) abstract;
			virtual Object^ SHDN_GetScriptByGUID(Guid id) abstract;

			virtual Guid SHDN_GetIdOfCurrentExecutingScript() abstract;
			virtual Object^ SHDN_GetCurrentScript(int iEvent) abstract;
			virtual void SHDN_SetCurrentScript(int iEvent, Object^ script) abstract;

			virtual void SHDN_AddFont(Object^ obj) abstract;

			virtual bool SHDN_VerboseLoggingEnabled() abstract;
			virtual bool SHDN_NativeCallLoggingEnabled() abstract;
			virtual bool SHDN_IsScriptRunning(Guid id) abstract;

			virtual void SHDN_ShowMessage(String^ str, int time) abstract;

			virtual void SHDNCache_AddEntity(Guid ownerScript, Object^ entity) abstract;
			virtual void SHDNCache_RemoveEntity(Object^ entity) abstract;
			virtual void SHDNCache_RemoveEntity(int handle) abstract;
			virtual Object^ SHDNCache_GetEntity(int handle, int requestedType, Guid ownerScript) abstract;

			virtual void SHDNCache_AddPlayer(Object^ player) abstract;
			virtual void SHDNCache_RemovePlayer(Object^ player) abstract;
			virtual Object^ SHDNCache_GetPlayer(int id) abstract;

		public:
			ManagerScript();

			static ManagerScript^ GetInstance()
			{
				return s_Instance;
			}
			static bool HasInstance()
			{
				return s_Instance != nullptr;
			}

			Script^ GetDummyScript()
			{
				return m_pDummyScript;
			}

		internal:
			static void SetInstance(ManagerScript^ instance)
			{
				s_Instance = instance;
			}
			void SetDummyScript(Script^ s)
			{
				m_pDummyScript = s;
			}

		internal:
			static ManagerScript^ s_Instance;
			Script^ m_pDummyScript;

		};

		/// <summary>
		/// Represents a plugin for the IV-SDK .NET Manager.
		/// </summary>
		public ref class ManagerPlugin
		{
		public:
			delegate void OnFirstD3D9FrameDelegate(IntPtr devicePtr);

			delegate void OnImGuiGlobalRenderingDelegate(IntPtr devicePtr, ImGuiIV_DrawingContext ctx);
			delegate void OnImGuiManagerRenderingDelegate(IntPtr devicePtr);
			

			delegate void OnScriptAbortDelegate(Guid id);
			delegate void OnScriptLoadDelegate(Guid id);

			delegate void OnScriptsAbortDelegate(array<Guid>^ ids);
			delegate void OnBeforeScriptsReloadDelegate(array<Guid>^ ids);
			delegate void OnAfterScriptsAbortDelegate();

			delegate Object^ PluginCommandReceivedDelegate(ManagerPlugin^ fromPlugin, array<Object^>^ args, String^ command);

		public:
			/// <summary>
			/// The unique ID of this plugin.
			/// </summary>
			property Guid ID
			{
			public:
				Guid get()
				{
					return m_id;
				}
			private:
				void set(Guid value)
				{
					m_id = value;
				}
			}

			/// <summary>
			/// Gets the display name of this plugin which will show in the IV-SDK .NET Manager Plugins tab.
			/// </summary>
			property String^ DisplayName
			{
			public:
				String^ get()
				{
					return m_sDisplayName;
				}
			private:
				void set(String^ value)
				{
					m_sDisplayName = value;
				}
			}

			/// <summary>
			/// Gets the author of this plugin which will show in the IV-SDK .NET Manager Plugins tab.
			/// </summary>
			property String^ Author
			{
			public:
				String^ get()
				{
					return m_sAuthor;
				}
			private:
				void set(String^ value)
				{
					m_sAuthor = value;
				}
			}

			/// <summary>
			/// Gets or sets the resource folder for this Plugin where all the files required by this Plugin are located.
			/// The folder has to be named the same name as your Plugin (without extension), and needs to be placed in the Plugins folder.
			/// The string will be null if the folder doesn't exist.
			/// </summary>
			property String^ PluginResourceFolder
			{
			public:
				String^ get()
				{
					return m_PluginResourceFolder;
				}
				void set(String^ value)
				{
					m_PluginResourceFolder = value;
				}
			}

			/// <summary>
			/// This makes it so the plugin is not able to be aborted*.
			/// <para>It is recommended to leave this set to false, and should only be activated when you have a very specific usecase for it.</para>
			/// <para>* The plugin is still able to be aborted when: </para>
			/// <para>- It creates an exception which the IV-SDK .NET Manager catches.</para>
			/// </summary>
			property bool ForceNoAbort
			{
			public:
				bool get()
				{
					return m_bForceNoAbort;
				}
				void set(bool value)
				{
					m_bForceNoAbort = value;
				}
			}

			/// <summary>
			/// Gets or sets a value indicating whether scripts can send commands to this plugin.
			/// <para>The default value is false.</para>
			/// </summary>
			property bool AllowReceiveCommandsFromScripts
			{
				bool get()
				{
					return m_bAllowReceiveCommandsFromScripts;
				}
				void set(bool value)
				{
					m_bAllowReceiveCommandsFromScripts = value;
				}
			}

		public:
			ManagerPlugin(String^ displayName, String^ author);

		public:
			/// <summary>
			/// Gets raised when the plugin is about to be unloaded so you can free some previously created stuff in here.
			/// </summary>
			event EventHandler^ Uninitialize;
			void RaiseUninitialize()
			{
				Uninitialize(this, EventArgs::Empty);
			}

			/// <summary>
			/// Gets raised every frame once in-game (CGame.Process).
			/// <para>It is save to call native functions in this event.</para>
			/// </summary>
			event EventHandler^ Tick;
			void RaiseTick()
			{
				Tick(this, EventArgs::Empty);
			}

			/// <summary>
			/// Gets raised when game is loading or when switching from one episode to another.
			/// Can be used for addon files that don't interfere with game files.
			/// </summary>
			event EventHandler^ GameLoad;
			void RaiseGameLoad()
			{
				GameLoad(this, EventArgs::Empty);
			}

			/// <summary>
			/// Gets raised before GameLoad when game is loading or when switching from one episode to another.
			/// Can be used for files that need to overwrite base game files.
			/// </summary>
			event EventHandler^ GameLoadPriority;
			void RaiseGameLoadPriority()
			{
				GameLoadPriority(this, EventArgs::Empty);
			}

			/// <summary>
			/// Gets raised when game is loading, switching from one episode to another or when loading the same save game again.
			/// Can be used for any rage.fiDevice stuff.
			/// </summary>
			event EventHandler^ MountDevice;
			void RaiseMountDevice()
			{
				MountDevice(this, EventArgs::Empty);
			}

			/// <summary>
			/// Gets raised on the very first Direct3D9 Frame. You can use this to create Textures or Fonts.
			/// </summary>
			event OnFirstD3D9FrameDelegate^ OnFirstD3D9Frame;
			void RaiseOnFirstD3D9Frame(IntPtr devicePtr)
			{
				OnFirstD3D9Frame(devicePtr);
			}

			/// <summary>
			/// Gets raised every frame and allows you to draw stuff on the screen via the ImGuiIV_DrawingContext struct, or draw custom script windows using ImGui via the ImGuiIV wrapper class.
			/// </summary>
			event OnImGuiGlobalRenderingDelegate^ OnImGuiGlobalRendering;
			void RaiseOnImGuiGlobalRendering(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
			{
				OnImGuiGlobalRendering(devicePtr, ctx);
			}

			/// <summary>
			/// Gets raised every frame and allows you to draw stuff on the screen via the ImGuiIV_DrawingContext struct, or draw custom script windows using ImGui via the ImGuiIV wrapper class.
			/// You are not forced to begin a new window first to add content to with this event, as its already getting called from within a ImGui window.
			/// So, you can instantly start using ImGui and use UI Elements such as the Button, Slider etc. These components will show up in the corresponding collapsing header within the IV-SDK .NET Manger Plugins tab.
			/// </summary>
			event OnImGuiManagerRenderingDelegate^ OnImGuiManagerRendering;
			void RaiseOnImGuiManagerRendering(IntPtr devicePtr)
			{
				OnImGuiManagerRendering(devicePtr);
			}

			/// <summary>
			/// Gets raised before the IV-SDK .NET Manager is about to shutdown.
			/// </summary>
			event EventHandler^ OnShutdown;
			void RaiseOnShutdown(System::Object^ sender, EventArgs^ args)
			{
				OnShutdown(sender, args);
			}

			/// <summary>
			/// Gets raised after a single script was aborted.
			/// </summary>
			event OnScriptAbortDelegate^ OnScriptAbort;
			void RaiseOnScriptAbort(Guid id)
			{
				OnScriptAbort(id);
			}

			/// <summary>
			/// Gets raised before the script initialize event is getting called.
			/// </summary>
			event OnScriptLoadDelegate^ OnScriptLoad;
			void RaiseOnScriptLoad(Guid id)
			{
				OnScriptLoad(id);
			}

			/// <summary>
			/// Gets raised when the Manager is about to abort all scripts.
			/// </summary>
			event OnBeforeScriptsReloadDelegate^ OnBeforeScriptsAbort;
			void RaiseOnBeforeScriptsAbort(array<Guid>^ ids)
			{
				OnBeforeScriptsAbort(ids);
			}

			/// <summary>
			/// Gets raised when the Manager aborted all scripts.
			/// </summary>
			event OnAfterScriptsAbortDelegate^ OnAfterScriptsAbort;
			void RaiseOnAfterScriptsAbort()
			{
				OnAfterScriptsAbort();
			}

			/// <summary>
			/// Gets raised when another plugin has sent a command to this plugin.
			/// <para>This can also get raised by scripts sending a command to this plugin if the plugin allows it.</para>
			/// </summary>
			event PluginCommandReceivedDelegate^ PluginCommandReceived;
			Object^ RaisePluginCommandReceived(ManagerPlugin^ fromPlugin, array<Object^>^ args, String^ command)
			{
				return PluginCommandReceived(fromPlugin, args, command);
			}

		public:
			/// <summary>
			/// Gives you quick access to the IV-SDK .NET Manager.
			/// </summary>
			/// <returns>The IV-SDK .NET Manager instance. This should never return null, but it's not wrong to always check it before trying to access any members of this class.</returns>
			ManagerScript^ GetManagerInstance()
			{
				return ManagerScript::GetInstance();
			}

			/// <summary>
			/// Allows you to communicate with other plugins.
			/// </summary>
			/// <param name="toPlugin">To which plugin this command should be send to.</param>
			/// <param name="command">The command to send.</param>
			/// <param name="args">The arguments to send with this command.</param>
			/// <param name="result">The object returned by the target plugin.</param>
			/// <returns>If successful, true is returned. Otherwise, false.</returns>
			bool SendPluginCommand(ManagerPlugin^ toPlugin, String^ command, array<Object^>^ args, [OutAttribute] Object^% result)
			{
				if (!toPlugin)
				{
					result = nullptr;
					return false;
				}

				return ManagerScript::GetInstance()->SendPluginCommand(true, ID, toPlugin->ID, command, args, result);
			}
			/// <summary>
			/// Allows you to communicate with other plugins.
			/// </summary>
			/// <param name="toPlugin">The ID of the plugin this command should be send to.</param>
			/// <param name="command">The command to send.</param>
			/// <param name="args">The arguments to send with this command.</param>
			/// <param name="result">The object returned by the target plugin.</param>
			/// <returns>If successful, true is returned. Otherwise, false.</returns>
			bool SendPluginCommand(Guid toPlugin, String^ command, array<Object^>^ args, [OutAttribute] Object^% result)
			{
				return ManagerScript::GetInstance()->SendPluginCommand(true, ID, toPlugin, command, args, result);
			}
			/// <summary>
			/// Allows you to communicate with other plugins.
			/// </summary>
			/// <param name="toPlugin">The name of the plugin this command should be send to.</param>
			/// <param name="command">The command to send.</param>
			/// <param name="args">The arguments to send with this command.</param>
			/// <param name="result">The object returned by the target plugin.</param>
			/// <returns>If successful, true is returned. Otherwise, false.</returns>
			bool SendPluginCommand(String^ toPlugin, String^ command, array<Object^>^ args, [OutAttribute] Object^% result)
			{
				return ManagerScript::GetInstance()->SendPluginCommand(true, ID, toPlugin, command, args, result);
			}

		private:
			Guid m_id;
			String^ m_sDisplayName;
			String^ m_sAuthor;
			String^ m_PluginResourceFolder;
			bool m_bForceNoAbort;
			bool m_bAllowReceiveCommandsFromScripts;
		};

	}
}