#pragma once

namespace IVSDKDotNet
{

	// Forward declarations
	ref class ResultTask;
	ref class Script;

	/// <summary> Internal-only IV-SDK .NET Manager stuff. </summary>
	namespace Manager
	{

		/// <summary>
		/// Only used for the IV-SDK .NET Manager.
		/// There can only be one instance of this class.
		/// </summary>
		public ref class ManagerScript abstract
		{
		public:
			bool SwitchImGuiForceCursorProperty;

		public:

			// General stuff
			virtual void ApplySettings(SettingsFile^ settings)	abstract;
			virtual void Cleanup()								abstract;

			// Console
			virtual void OpenConsole()						abstract;
			virtual void CloseConsole()						abstract;
			virtual void ClearConsole()						abstract;

			virtual bool IsConsoleOpen()					abstract;

			virtual bool RegisterConsoleCommand(Guid fromScript, String^ name, Action<array<String^>^>^ actionToExecute) abstract;
			virtual bool ExecuteConsoleCommand(String^ name) abstract;

			// Phone
			virtual bool RegisterPhoneNumber(Guid forScript, String^ number, Action^ dialedAction) abstract;
			virtual bool UnregisterPhoneNumber(Guid fromScript, String^ number) abstract;

			// Game
			virtual bool IsGameInFocus() abstract;

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

			virtual void RegisterEvent(String^ scriptOrPluginName, Delegate^ source, Delegate^ target) abstract;

			virtual void LoadScripts()							abstract;
			virtual bool AbortScript(Guid id)					abstract;

			virtual Script^ GetScript(Guid id)					abstract;
			virtual Script^ GetScript(String^ name)				abstract;
			virtual bool IsScriptRunning(Guid id)				abstract;
			virtual bool IsScriptRunning(String^ name)			abstract;
			virtual String^ GetScriptName(Guid id)				abstract;
			virtual String^ GetScriptFullPath(Guid id)			abstract;
			virtual int GetActiveScriptsCount()					abstract;

			virtual bool SendScriptCommand(Guid sender, Guid toScript, String^ command, array<Object^>^ parameters, [OutAttribute] Object^% result) abstract;
			virtual bool SendScriptCommand(Guid sender, String^ toScript, String^ command, array<Object^>^ parameters, [OutAttribute] Object^% result) abstract;

			// Task
			virtual Guid StartNewTask(Guid forScript, Func<Object^>^ actionToExecute, Action<Object^>^ continueWithAction)	abstract;
			virtual Guid StartNewTimer(Guid forScript, int interval, Action^ actionToExecute)								abstract;

			virtual void WaitInTask(Guid id, int waitTimeInMilliseconds)						abstract;
			virtual void AbortTaskOrTimer(Guid id)												abstract;
			virtual void ChangeTimerState(Guid id, bool pause)									abstract;
			virtual void ChangeTimerInterval(Guid id, int interval)								abstract;

			// Direct3D9 Stuff
			virtual void Direct3D9_RegisterScriptTexture(String^ forScript, IntPtr ptr)			abstract;
			//virtual void Direct3D9_UnregisterScriptTexture(String^ forScript, IntPtr ptr)		abstract;

			// Helper
			virtual String^ Helper_ConvertObjectToJsonString(Object^ obj, bool useFormatting) abstract;
			virtual Object^ Helper_ConvertJsonStringToObject(String^ str, Type^ targetType) abstract;

			// ScriptHookDotNet
			virtual int SHDN_LateInitializeScript(String^ name, Object^ script, [OutAttribute] String^% assemblyFullPath) abstract;

			virtual Object^ SHDN_GetScriptByName(String^ name) abstract;
			virtual Object^ SHDN_GetScriptByGUID(Guid id) abstract;

			virtual Object^ SHDN_GetCurrentScript(int iEvent) abstract;
			virtual void SHDN_SetCurrentScript(int iEvent, Object^ script) abstract;

			virtual void SHDN_AddFont(Object^ obj) abstract;

			virtual bool SHDN_VerboseLoggingEnabled() abstract;
			virtual bool SHDN_NativeCallLoggingEnabled() abstract;
			virtual bool SHDN_IsScriptRunning(Guid id) abstract;

			// Other
			virtual int GetMainThreadID() abstract;

		public:
			ManagerScript();

			static ManagerScript^ GetInstance()
			{
				return s_Instance;
			}
			Script^ GetDummyScript()
			{
				return m_pDummyScript;
			}

		internal:
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
			delegate void OnImGuiRenderingDelegate(IntPtr devicePtr, ImGuiIV_DrawingContext ctx);

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
			/// Gets raised on the very first Direct3D9 Frame. You can use this to create Textures or Fonts.
			/// </summary>
			event OnFirstD3D9FrameDelegate^ OnFirstD3D9Frame;
			void RaiseOnFirstD3D9Frame(IntPtr devicePtr)
			{
				OnFirstD3D9Frame(devicePtr);
			}

			/// <summary>
			/// Gets raised every frame and allows you to draw stuff on the screen via the ImGuiIV_DrawingContext struct, or draw custom script windows using ImGui via the ImGuiIV wrapper class.
			/// You are not forced to begin a new window first to add content to with this event, as its already getting called from within a ImGui window.
			/// So, you can instantly start using ImGui and use UI Elements such as the Button, Slider etc. These components will show up in the corresponding collapsing header within the IV-SDK .NET Manger Plugins tab.
			/// </summary>
			event OnImGuiRenderingDelegate^ OnImGuiRendering;
			void RaiseOnImGuiRendering(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
			{
				OnImGuiRendering(devicePtr, ctx);
			}

		private:
			Guid m_id;
			String^ m_sDisplayName;
			String^ m_sAuthor;
		};

	}
}