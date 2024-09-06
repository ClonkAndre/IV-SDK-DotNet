#pragma once

#include "EventArgs.h"

namespace IVSDKDotNet
{

	ref class ResultTask;

	/// <summary>
	///	Marks the class as a IV-SDK .NET Script.
	///	This class needs to be inherited if you want this class to be the entry point of your IV-SDK .NET Script.
	/// </summary>
	public ref class Script
	{
		// Constructor / Destructor
	internal:
		Script(Guid id);

	public:
		Script();
		~Script() { }

		// Delegates
	public:
		delegate void ProcessDelegate(UIntPtr ptr);
		delegate void ProcessAutomobileDelegate(UIntPtr vehPtr);
		delegate void ProcessPadDelegate(UIntPtr padPtr);
		delegate Object^ ScriptCommandReceivedDelegate(Script^ fromScript, array<Object^>^ args, String^ command);
		delegate String^ ScriptAssemblyResolveDelegate(String^ assemblyFileName);

		delegate void OnFirstD3D9FrameDelegate(IntPtr devicePtr);
		delegate void OnImGuiRenderingDelegate(IntPtr devicePtr, ImGuiIV_DrawingContext ctx);

		// Events
	public:
		/// <summary>
		/// Gets raised after the constructor so you can safely call any functions in here without having to worry about stuff not being initialized yet.
		/// Native functions cannot be called in here yet.
		/// </summary>
		event EventHandler^ Initialized;
		void RaiseInitialized()
		{
			Initialized(this, EventArgs::Empty);
		}

		/// <summary>
		/// Gets raised when the script is about to be unloaded so you can free some previously created stuff in here.
		/// </summary>
		event EventHandler^ Uninitialize;
		void RaiseUninitialize()
		{
			Uninitialize(this, EventArgs::Empty);
		}

		/// <summary>
		/// Gets raised every frame when in-game (CGame.Process).
		/// This event uses the CTheScripts.SetDummyThread/RestorePreviousThread method that means that any natives calls in this event will work just fine.
		/// </summary>
		event EventHandler^ Tick;
		void RaiseTick()
		{
			Tick(this, EventArgs::Empty);
		}

		/// <summary>
		/// Gets raised every X milliseconds depending on what you set the WaitTickInterval property to (Default is 100ms).
		/// This event will internally be called from the Tick event which means it uses the CTheScripts.SetDummyThread/RestorePreviousThread method.
		/// </summary>
		event EventHandler^ WaitTick;
		void RaiseWaitTick()
		{
			WaitTick(this, EventArgs::Empty);
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
		/// Gets raised twice per frame when in-game, and even works in main menu (CRenderPhasePostRenderViewport).
		/// </summary>
		event EventHandler^ Drawing;
		void RaiseDrawing()
		{
			Drawing(this, EventArgs::Empty);
		}

		/// <summary>
		/// Gets raised after IVCamera.FinalCam has been written to.
		/// </summary>
		event EventHandler^ ProcessCamera;
		void RaiseProcessCamera()
		{
			ProcessCamera(this, EventArgs::Empty);
		}

		/// <summary>
		/// Gets raised after IVAutomobile.Process, overriding steer and pedals works here.
		/// </summary>
		event ProcessAutomobileDelegate^ ProcessAutomobile;
		void RaiseProcessAutomobile(UIntPtr vehPtr)
		{
			ProcessAutomobile(vehPtr);
		}

		/// <summary>
		/// Gets raised EVERYTIME even when in main menu.
		/// You can set all pad controls here, called once per frame for each pad.
		/// </summary>
		event ProcessPadDelegate^ ProcessPad;
		void RaiseProcessPad(UIntPtr padPtr)
		{
			ProcessPad(padPtr);
		}

		/// <summary>
		/// Gets raised right before loading a save, starting a new game, switching episodes, etc.
		/// </summary>
		event EventHandler^ IngameStartup;
		void RaiseIngameStartup()
		{
			IngameStartup(this, EventArgs::Empty);
		}

		/// <summary>
		/// Gets raised when a key was released.
		/// </summary>
		event KeyEventHandler^ KeyUp;
		void RaiseKeyUp(KeyEventArgs^ args)
		{
			KeyUp(this, args);
		}

		/// <summary>
		/// Gets raised when a key was pressed.
		/// </summary>
		event KeyEventHandler^ KeyDown;
		void RaiseKeyDown(KeyEventArgs^ args)
		{
			KeyDown(this, args);
		}

		/// <summary>
		/// Gets raised when another IV-SDK .NET Script has sent a command to this IV-SDK .NET Script. 
		/// </summary>
		event ScriptCommandReceivedDelegate^ ScriptCommandReceived;
		Object^ RaiseScriptCommandReceived(Script^ fromScript, array<Object^>^ args, String^ command)
		{
			return ScriptCommandReceived(fromScript, args, command);
		}

		/// <summary>
		/// Gets raised when you set Script.AssembliesLocation to DecideManuallyForEachAssembly and an Assembly gets requested for this Script.
		/// You need to return the absolut path of the reqested Assembly.
		/// </summary>
		event ScriptAssemblyResolveDelegate^ AssemblyResolve;
		String^ RaiseAssemblyResolve(String^ assemblyFileName)
		{
			return AssemblyResolve(assemblyFileName);
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
		event OnImGuiRenderingDelegate^ OnImGuiRendering;
		void RaiseOnImGuiRendering(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
		{
			OnImGuiRendering(devicePtr, ctx);
		}

		/// <summary>
		/// Starts a new asynchronous task.
		/// </summary>
		/// <param name="funcToExecute">The function that should be executed.</param>
		/// <returns>The Guid of the just created Task which can be used to control the Task. If Guid is empty then Task could not get created.</returns>
		Guid StartNewTask(Func<Object^>^ funcToExecute);

		/// <summary>
		/// Starts a new asynchronous task.
		/// </summary>
		/// <param name="funcToExecute">The function that should be executed.</param>
		/// <param name="continueWithAction">The action that should be executed when the given tasks function completed and is about to reach its end. The object parameter of this action is the data returned from the function.</param>
		/// <returns>The Guid of the just created Task which can be used to control the Task. If Guid is empty then Task could not get created.</returns>
		Guid StartNewTask(Func<Object^>^ funcToExecute, Action<Object^>^ continueWithAction);

		/// <summary>
		/// Waits in the Task for the specified amount of time.
		/// </summary>
		/// <param name="id">The ID of the Task.</param>
		/// <param name="waitTimeInMilliseconds">The time to wait in milliseconds.</param>
		void WaitInTask(Guid id, int waitTimeInMilliseconds);

		/// <summary>
		/// Starts a new asynchronous Timer.
		/// </summary>
		/// <param name="interval">The interval how fast the Timer should run.</param>
		/// <param name="actionToExecute">The action that should be executed each Timer Tick.</param>
		/// <returns>The Guid of the just created Timer which can be used to control the Timer. If Guid is empty then Timer could not get created.</returns>
		Guid StartNewTimer(int interval, Action^ actionToExecute);

		/// <summary>
		/// Aborts a task or timer with the given id.
		/// </summary>
		/// <param name="id">The ID of the task or timer to abort.</param>
		void AbortTaskOrTimer(Guid id);

		/// <summary>
		/// Changes the pause state of a timer.
		/// </summary>
		/// <param name="id">The ID of the timer to change its pause state.</param>
		/// <param name="pause">Pause, or not pause.</param>
		void ChangeTimerState(Guid id, bool pause);

		/// <summary>
		/// Changes the interval of a timer.
		/// </summary>
		/// <param name="id">The ID of the timer to change its interval.</param>
		/// <param name="interval">The new interval. Default is 100 milliseconds.</param>
		void ChangeTimerInterval(Guid id, int interval);

		/// <summary>
		/// Shows text at the bottom center of the screen where the subtitles are located.
		/// Only works in-game.
		/// </summary>
		/// <param name="str">The text to be shown.</param>
		/// <param name="time">How long the text should be shown in milliseconds.</param>
		void ShowSubtitleMessage(String^ str, uint32_t time);

		/// <summary>
		/// Shows text at the bottom center of the screen where the subtitles are located for 3 seconds.
		/// Only works in-game.
		/// </summary>
		/// <param name="str">The text to be shown.</param>
		/// <param name="args">An object array that contains zero or more objects to format.</param>
		void ShowSubtitleMessage(String^ str, ...array<System::Object^>^ args);

		/// <summary>
		/// Shows text at the bottom center of the screen where the subtitles are located for 2 seconds.
		/// Only works in-game.
		/// </summary>
		/// <param name="str">The text to be shown.</param>
		void ShowSubtitleMessage(String^ str);

		/// <summary>
		/// Checks if the specified key is pressed.
		/// </summary>
		/// <param name="Key">: The key to check if it's pressed.</param>
		/// <returns>True if the key is pressed, otherwise false.</returns>
		bool IsKeyPressed(Keys Key);

		/// <summary>
		/// Aborts this script.
		/// <returns>True if the script got aborted. Otherwise, false.</returns>
		/// </summary>
		bool Abort();

		/// <summary>
		/// Registers a new console command that you can execute by its name in the IV-SDK .NET console.
		/// </summary>
		/// <param name="name">The name of this command (Name is not case sensitive).</param>
		/// <param name="actionToExecute">The action that should be executed if the command gets executed.</param>
		/// <returns>True if the command got registered. False if the command already exists, or if the given name is null or whitespace.</returns>
		bool RegisterConsoleCommand(String^ name, Action<array<String^>^>^ actionToExecute);

		/// <summary>
		/// Registers a phone number.
		/// </summary>
		/// <param name="number">The phone number to unregister.</param>
		/// <param name="dialingAction">The action that will be executed when this number was dialed.</param>
		/// <returns>True if the number got registered. Otherwise false.</returns>
		bool RegisterPhoneNumber(String^ number, Action^ dialingAction);

		/// <summary>
		/// Unregisters a phone number.
		/// </summary>
		/// <param name="number">The phone number to unregister.</param>
		/// <returns>True if the number got unregistered. Otherwise false.</returns>
		bool UnregisterPhoneNumber(String^ number);

		/// <summary>
		/// Returns the name of this script.
		/// </summary>
		/// <returns>The name of this script, or an empty string if the name could not get retrieved.</returns>
		String^ GetName();

		/// <summary>
		/// Return the absolute path of this script.
		/// </summary>
		/// <returns>The absolute path of the script, or an empty string if the full path could not get retrieved.</returns>
		String^ GetFullPath();

		/// <summary>
		/// Allows you to check if the script you are checking for exists.
		/// </summary>
		/// <param name="id">The id of the script you want to check for.</param>
		/// <returns>True if the script exists. Otherwise, false.</returns>
		bool DoesScriptExists(Guid id);
		/// <summary>
		/// Allows you to check if the script you are checking for exists.
		/// </summary>
		/// <param name="name">The name of the script you want to check for.</param>
		/// <returns>True if the script exists. Otherwise, false.</returns>
		bool DoesScriptExists(String^ name);

		/// <summary>
		/// Allows you to check if the script you are checking for is running.
		/// </summary>
		/// <param name="id">The name of the script you want to check for.</param>
		/// <returns>True if the script is running. Otherwise, false.</returns>
		bool IsScriptRunning(Guid id);
		/// <summary>
		/// Allows you to check if the script you are checking for is running.
		/// </summary>
		/// <param name="name">The name of the script you want to check for.</param>
		/// <returns>True if the script is running. Otherwise, false.</returns>
		bool IsScriptRunning(String^ name);

		/// <summary>
		/// Returns a script by its id if available.
		/// </summary>
		/// <param name="id">The id of the script you want to get.</param>
		/// <returns>The script if found. Otherwise, null.</returns>
		Script^ GetScript(Guid id);
		/// <summary>
		/// Returns a script by its name if available.
		/// </summary>
		/// <param name="name">The name of the script you want to get.</param>
		/// <returns>The script if found. Otherwise, null.</returns>
		Script^ GetScript(String^ name);

		/// <summary>
		/// Allows you to communicate with other scripts.
		/// </summary>
		/// <param name="toScript">To which the script the command should be send to.</param>
		/// <param name="command">The command to send to the script.</param>
		/// <param name="args">The arguments to send to the script with this command.</param>
		/// <param name="result">The object returned by the target script.</param>
		/// <returns>If successful, true is returned. Otherwise, false.</returns>
		bool SendScriptCommand(Script^ toScript, String^ command, array<Object^>^ args, [OutAttribute] Object^% result);
		/// <summary>
		/// Allows you to communicate with other scripts.
		/// </summary>
		/// <param name="toScript">The ID of the script to which the command should be send to.</param>
		/// <param name="command">The command to send to the script.</param>
		/// <param name="args">The arguments to send to the script with this command.</param>
		/// <param name="result">The object returned by the target script.</param>
		/// <returns>If successful, true is returned. Otherwise, false.</returns>
		bool SendScriptCommand(Guid toScript, String^ command, array<Object^>^ args, [OutAttribute] Object^% result);
		/// <summary>
		/// Allows you to communicate with other scripts.
		/// </summary>
		/// <param name="toScript">The name of the script to which the command should be send to.</param>
		/// <param name="command">The command to send to the script.</param>
		/// <param name="args">The arguments to send to the script with this command.</param>
		/// <param name="result">The object returned by the target script.</param>
		/// <returns>If successful, true is returned. Otherwise, false.</returns>
		bool SendScriptCommand(String^ toScript, String^ command, array<Object^>^ args, [OutAttribute] Object^% result);

		/// <summary>
		/// The unique ID of this script.
		/// </summary>
		property Guid ID
		{
			public:		Guid get()				{ return m_id; }
			private:	void set(Guid value)	{ m_id = value; }
		}

		/// <summary>
		/// Gets the current AppDomain.
		/// </summary>
		property AppDomain^ ScriptDomain
		{
			public:		AppDomain^ get() { return m_AppDomain; }
			internal:	void set(AppDomain^ value) { m_AppDomain = value; }
		}

		/// <summary>
		/// If you uploaded your Modification to the IV Launchers Workshop, you can set the value of this property to the ID of the Modification in the Workshop.
		/// </summary>
		property Guid IVLauncherWorkshopID
		{
			public:	
				Guid get()				{ return m_ivLauncherWorkshopID; }
				void set(Guid value)	{ m_ivLauncherWorkshopID = value; }
		}

		/// <summary>
		/// Gets or sets where the Assemblies are located for this script. Default: GameRootDirectory
		/// </summary>
		property eAssembliesLocation AssembliesLocation
		{
			public:
				eAssembliesLocation get()			{ return m_AssembliesLocation; }
				void set(eAssembliesLocation value) { m_AssembliesLocation = value; }
		}

		/// <summary>
		/// Gets or sets the custom Assemblies path for this Script if you have set the AssembliesLocation to Custom.
		/// The path is relative to the root directory of GTA IV.
		/// Example: IVSDKDotNet\scripts\AssembliesForMyEpicScript - The Assemblies for your Script will now be loaded from the AssembliesForMyEpicScript folder.
		/// </summary>
		property String^ CustomAssembliesPath
		{
			public:
				String^ get()				{ return m_CustomAssembliesPath; }
				void	set(String^ value)	{ m_CustomAssembliesPath = value; }
		}

		/// <summary>
		/// Gets or sets the resource folder for this Script where all the files required by this Script are located.
		/// The folder has to be named the same name as your Script (without extension), and needs to be placed in the scripts folder.
		/// The string will be null if the folder doesn't exist.
		/// </summary>
		property String^ ScriptResourceFolder
		{
			public:
				String^ get()				{ return m_ScriptResourceFolder; }
				void	set(String^ value)	{ m_ScriptResourceFolder = value; }
		}

		/// <summary>
		/// The settings file of this script.
		/// </summary>
		property SettingsFile^ Settings
		{
			public: 
				SettingsFile^ get()				{ return m_SettingsFile; }
				void set(SettingsFile^ value)	{ m_SettingsFile = value; }
		}

		/// <summary>
		/// Gets or sets if the KeyDown and KeyUp events should only be raised when the player is actually in-game and not in main menu.
		/// </summary>
		property bool OnlyRaiseKeyEventsWhenInGame
		{
			public:
				bool get()				{ return m_bOnlyInvokeKeyEventsWhenInGame; }
				void set(bool value)	{ m_bOnlyInvokeKeyEventsWhenInGame = value; }
		}

		/// <summary>
		/// Gets or sets the interval with which the WaitTick event should get raised. The default is 100ms and it cannot go below 1.
		/// </summary>
		property int WaitTickInterval
		{
			public:
				int get() { return m_iWaitTickInterval; }
				void set(int value)
				{
					if (value < 1)
						return;

					m_iWaitTickInterval = value;
				}
		}

	private:
		Guid m_id;
		AppDomain^ m_AppDomain;
		Guid m_ivLauncherWorkshopID;
		eAssembliesLocation m_AssembliesLocation;
		String^ m_CustomAssembliesPath;
		String^ m_ScriptResourceFolder;
		SettingsFile^ m_SettingsFile;
		bool m_bOnlyInvokeKeyEventsWhenInGame;
		int m_iWaitTickInterval = 100;
	};

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

			virtual void LoadScripts()							abstract;
			virtual bool AbortScript(Guid id)					abstract;

			virtual Script^	GetScript(Guid id)					abstract;
			virtual Script^	GetScript(String^ name)				abstract;
			virtual bool IsScriptRunning(Guid id)				abstract;
			virtual bool IsScriptRunning(String^ name)			abstract;
			virtual String^	GetScriptName(Guid id)				abstract;
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

		public ref class ManagerPlugin abstract
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

		public:
			ManagerPlugin();

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
			/// </summary>
			event OnImGuiRenderingDelegate^ OnImGuiRendering;
			void RaiseOnImGuiRendering(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
			{
				OnImGuiRendering(devicePtr, ctx);
			}

		private:
			Guid m_id;
		};

	}

}

