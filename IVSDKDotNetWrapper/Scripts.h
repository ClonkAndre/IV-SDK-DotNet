#pragma once

#include "EventArgs.h"

namespace IVSDKDotNet
{

	/// <summary>
	///	Marks the class as a IV-SDK .NET Script.
	///	This class needs to be inherited if you want this class to be the entry point of your IV-SDK .NET Script.
	/// </summary>
	public ref class Script
	{
	internal:
		Script(Guid id);

	public:
		Script();
		~Script() {};

		delegate void ProcessAutomobileDelegate(UIntPtr vehPtr);
		delegate void ProcessPadDelegate(UIntPtr vehPtr);
		delegate Object^ ScriptCommandReceivedDelegate(Script^ fromScript, String^ command);
		delegate String^ ScriptAssemblyResolveDelegate(String^ assemblyFileName);
		delegate void ImGuiPrimitiveDrawingDelegate(ImGuiIV_DrawingContext context);
		delegate void ImGuiUIRenderingDelegate();

		/// <summary>
		/// Gets raised after the constructor so you can safely call any functions in here without having to worry about stuff not being initialized yet.
		/// Native functions cannot be called in here yet.
		/// </summary>
		event EventHandler^ Initialized;

		/// <summary>
		/// Gets raised when the script is about to be unloaded so you can free some previously created stuff in here.
		/// </summary>
		event EventHandler^ Uninitialize;

		/// <summary>
		/// Gets raised every frame when in-game.
		/// (CGame.Process).
		/// This event uses the CTheScripts.SetDummyThread/RestorePreviousThread method.
		/// </summary>
		event EventHandler^ Tick;

		/// <summary>
		/// Gets raised when game is loading or when switching from one episode to another.
		/// Can be used for addon files that don't interfere with game files.
		/// </summary>
		event EventHandler^ GameLoad;

		/// <summary>
		/// Gets raised before GameLoad when game is loading or when switching from one episode to another.
		/// Can be used for files that need to overwrite base game files.
		/// </summary>
		event EventHandler^ GameLoadPriority;

		/// <summary>
		/// Gets raised when game is loading, switching from one episode to another or when loading the same save game again.
		/// Can be used for any rage.fiDevice stuff.
		/// </summary>
		event EventHandler^ MountDevice;

		/// <summary>
		/// Gets raised twice per frame when in-game, and even works in main menu.
		/// (CRenderPhasePostRenderViewport)
		/// </summary>
		event EventHandler^ Drawing;

		/// <summary>
		/// Gets raised after CCamera.m_pFinalCam has been written to.
		/// </summary>
		event EventHandler^ ProcessCamera;

		/// <summary>
		/// Gets raised after CAutomobile.Process, overriding steer and pedals works here.
		/// </summary>
		event ProcessAutomobileDelegate^ ProcessAutomobile;

		/// <summary>
		/// Gets raised EVERYTIME even when in main menu.
		/// You can set all pad controls here, called once per frame for each pad.
		/// </summary>
		event ProcessPadDelegate^ ProcessPad;

		/// <summary>
		/// Gets raised when a key was released.
		/// </summary>
		event KeyEventHandler^ KeyUp;

		/// <summary>
		/// Gets raised when a key was pressed.
		/// </summary>
		event KeyEventHandler^ KeyDown;

		/// <summary>
		/// Gets raised when another IV-SDK .NET Script has sent a command to this IV-SDK .NET Script. 
		/// </summary>
		event ScriptCommandReceivedDelegate^ ScriptCommandReceived;

		/// <summary>
		/// Gets raised when you set Script.AssembliesLocation to DecideManuallyForEachAssembly and an Assembly gets requested for this Script.
		/// You need to return the absolut path of the reqested Assembly.
		/// </summary>
		event ScriptAssemblyResolveDelegate^ AssemblyResolve;

		/// <summary>
		/// Gets raised on the very first Direct3D9 Frame. You can use this to create Textures.
		/// </summary>
		static event EventHandler^ OnFirstD3D9Frame;

		void RaiseInitialized()													{ Initialized(this, EventArgs::Empty); }
		void RaiseUninitialize()												{ Uninitialize(this, EventArgs::Empty); }
		void RaiseTick()														{ Tick(this, EventArgs::Empty); }
		void RaiseGameLoad()													{ GameLoad(this, EventArgs::Empty); }
		void RaiseGameLoadPriority()											{ GameLoadPriority(this, EventArgs::Empty); }
		void RaiseMountDevice()													{ MountDevice(this, EventArgs::Empty); }
		void RaiseDrawing()														{ Drawing(this, EventArgs::Empty); }
		void RaiseProcessCamera()												{ ProcessCamera(this, EventArgs::Empty); }
		void RaiseProcessAutomobile(UIntPtr vehPtr)								{ ProcessAutomobile(vehPtr); }
		void RaiseProcessPad(UIntPtr padPtr)									{ ProcessPad(padPtr); }
		void RaiseKeyUp(KeyEventArgs^ args)										{ KeyUp(this, args); }
		void RaiseKeyDown(KeyEventArgs^ args)									{ KeyDown(this, args); }
		void RaiseOnFirstD3D9Frame()											{ OnFirstD3D9Frame(this, EventArgs::Empty); }
		Object^ RaiseScriptCommandReceived(Script^ fromScript, String^ command)	{ return ScriptCommandReceived(fromScript, command); }

		String^ RaiseAssemblyResolve(String^ assemblyFileName)					{ return AssemblyResolve(assemblyFileName); }

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
		/// Shows text at the bottom center of the screen where the subtitles are located for 2 seconds.
		/// Only works in-game.
		/// </summary>
		/// <param name="str">The text to be shown.</param>
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
		/// Returns an array of all currently running scripts.
		/// </summary>
		/// <returns>If successful, an array of all currently running script is returned. Otherwise, null.</returns>
		array<Script^>^ GetAllScripts();

		/// <summary>
		/// Allows you to communicate with other scripts.
		/// </summary>
		/// <param name="toScript">To which the script the command should be sent to.</param>
		/// <param name="command">The command to sent to the script.</param>
		/// <param name="result">The object returned by the target script.</param>
		/// <returns>If successful, true is returned. Otherwise, false.</returns>
		bool SendScriptCommand(Script^ toScript, String^ command, [OutAttribute] Object^% result);

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
		property AppDomain^ ScriptDomain {
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
			bool get()				{ return m_bOnlyInvokeKeyEventsWhenInGame; }
			void set(bool value)	{ m_bOnlyInvokeKeyEventsWhenInGame = value; }
		}

#pragma region Measurement Properties
		/// <summary>
		/// Gets how much time the Initialized event took to execute.
		/// </summary>
		property TimeSpan InitializedEventExecutionTime
		{
			public:
				TimeSpan	get() { return m_sInitializedEventExecutionTime; }
				void		set(TimeSpan value) { m_sInitializedEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the Tick event took to execute.
		/// </summary>
		property TimeSpan TickEventExecutionTime
		{
			public:
				TimeSpan	get()				{ return m_sTickEventExecutionTime; }
				void		set(TimeSpan value) { m_sTickEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the GameLoad event took to execute.
		/// </summary>
		property TimeSpan GameLoadEventExecutionTime
		{
			public:
				TimeSpan	get()				{ return m_sGameLoadEventExecutionTime; }
				void		set(TimeSpan value) { m_sGameLoadEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the GameLoadPriority event took to execute.
		/// </summary>
		property TimeSpan GameLoadPriorityEventExecutionTime
		{
			public:
				TimeSpan	get()				{ return m_sGameLoadPriorityEventExecutionTime; }
				void		set(TimeSpan value) { m_sGameLoadPriorityEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the MountDevice event took to execute.
		/// </summary>
		property TimeSpan MountDeviceEventExecutionTime
		{
			public:
				TimeSpan	get()				{ return m_sMountDeviceEventExecutionTime; }
				void		set(TimeSpan value) { m_sMountDeviceEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the Drawing event took to execute.
		/// </summary>
		property TimeSpan DrawingEventExecutionTime
		{
			public:
				TimeSpan	get()				{ return m_sDrawingEventExecutionTime; }
				void		set(TimeSpan value) { m_sDrawingEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the ProcessCamera event took to execute.
		/// </summary>
		property TimeSpan ProcessCameraEventExecutionTime
		{
			public:
				TimeSpan	get()				{ return m_sProcessCameraEventExecutionTime; }
				void		set(TimeSpan value) { m_sProcessCameraEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the ProcessAutomobile event took to execute.
		/// </summary>
		property TimeSpan ProcessAutomobileEventExecutionTime
		{
			public:
				TimeSpan	get()				{ return m_sProcessAutomobileEventExecutionTime; }
				void		set(TimeSpan value) { m_sProcessAutomobileEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the ProcessPad event took to execute.
		/// </summary>
		property TimeSpan ProcessPadEventExecutionTime
		{
			public:
				TimeSpan	get()				{ return m_sProcessPadEventExecutionTime; }
				void		set(TimeSpan value) { m_sProcessPadEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the OnFirstD3D9Frame event took to execute.
		/// </summary>
		property TimeSpan OnFirstD3D9FrameEventExecutionTime
		{
		public:
			TimeSpan	get() { return m_sOnFirstD3D9FrameEventExecutionTime; }
			void		set(TimeSpan value) { m_sOnFirstD3D9FrameEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the KeyDown event took to execute.
		/// </summary>
		property TimeSpan KeyDownEventExecutionTime
		{
		public:
			TimeSpan	get() { return m_sKeyDownEventExecutionTime; }
			void		set(TimeSpan value) { m_sKeyDownEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the KeyUp event took to execute.
		/// </summary>
		property TimeSpan KeyUpEventExecutionTime
		{
		public:
			TimeSpan	get() { return m_sKeyUpEventExecutionTime; }
			void		set(TimeSpan value) { m_sKeyUpEventExecutionTime = value; }
		}
#pragma endregion

	private:
		Guid m_id;
		AppDomain^ m_AppDomain;
		Guid m_ivLauncherWorkshopID;
		eAssembliesLocation m_AssembliesLocation;
		String^ m_CustomAssembliesPath;
		String^ m_ScriptResourceFolder;
		SettingsFile^ m_SettingsFile;
		bool m_bOnlyInvokeKeyEventsWhenInGame;

		// Measurements
		TimeSpan m_sInitializedEventExecutionTime;
		TimeSpan m_sTickEventExecutionTime;
		TimeSpan m_sGameLoadEventExecutionTime;
		TimeSpan m_sGameLoadPriorityEventExecutionTime;
		TimeSpan m_sMountDeviceEventExecutionTime;
		TimeSpan m_sDrawingEventExecutionTime;
		TimeSpan m_sProcessCameraEventExecutionTime;
		TimeSpan m_sProcessAutomobileEventExecutionTime;
		TimeSpan m_sProcessPadEventExecutionTime;
		TimeSpan m_sOnFirstD3D9FrameEventExecutionTime;
		TimeSpan m_sKeyDownEventExecutionTime;
		TimeSpan m_sKeyUpEventExecutionTime;
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
			event RAGE::GameWindowFocusChangedDelegate^ WindowFocusChanged;
			void RaiseWindowFocusChanged(bool focused) { WindowFocusChanged(focused); }

		public:

			// Debug
			void Debug_ShowMessageBox(String^ str);
			void Debug_ShowInfoMessageBox(String^ str);
			void Debug_ShowWarnMessageBox(String^ str);
			void Debug_ShowErrorMessageBox(String^ str);

			// General stuff
			virtual void ApplySettings(SettingsFile^ settings)	abstract;
			virtual void SetDummyScript(Script^ script)			abstract;
			virtual void Cleanup()								abstract;

			// Console
			virtual void OpenConsole()						abstract;
			virtual void CloseConsole()						abstract;
			virtual void ClearConsole()						abstract;

			virtual bool IsConsoleOpen()					abstract;

			virtual bool RegisterConsoleCommand(Guid fromScript, String^ name, Action<array<String^>^>^ actionToExecute) abstract;
			virtual bool ExecuteConsoleCommand(String^ name) abstract;

			// Game
			virtual bool IsGameInFocus() abstract;

			// Script
			virtual void RaiseTick()											abstract;
			virtual void RaiseGameLoad()										abstract;
			virtual void RaiseGameLoadPriority()								abstract;
			virtual void RaiseMountDevice()										abstract;
			virtual void RaiseDrawing()											abstract;
			virtual void RaiseProcessCamera()									abstract;
			virtual void RaiseProcessAutomobile(UIntPtr vehPtr)					abstract;
			virtual void RaiseProcessPad(UIntPtr padPtr)						abstract;
			virtual void RaiseIngameStartup()									abstract;
			virtual void RaiseUIRendering()										abstract;

			virtual void LoadScripts()							abstract;
			virtual bool AbortScript(Guid id)					abstract;

			virtual Script^	GetScript(Guid id)					abstract;
			virtual Script^	GetScript(String^ name)				abstract;
			virtual bool IsScriptRunning(Guid id)				abstract;
			virtual bool IsScriptRunning(String^ name)			abstract;
			virtual array<Script^>^ GetAllScripts()				abstract;
			virtual String^	GetScriptName(Guid id)				abstract;
			virtual String^ GetScriptFullPath(Guid id)			abstract;
			virtual int GetActiveScriptsCount()					abstract;

			virtual bool SendScriptCommand(Script^ toScript, String^ command, [OutAttribute] Object^% result) abstract;

			// Task
			virtual Guid StartNewTask(Guid forScript, Func<Object^>^ actionToExecute, Action<Object^>^ continueWithAction)	abstract;
			virtual Guid StartNewTimer(Guid forScript, int interval, Action^ actionToExecute)								abstract;

			virtual void WaitInTask(Guid id, int waitTimeInMilliseconds)						abstract;
			virtual void AbortTaskOrTimer(Guid id)												abstract;
			virtual void ChangeTimerState(Guid id, bool pause)									abstract;
			virtual void ChangeTimerInterval(Guid id, int interval)								abstract;

			// Direct3D9 Stuff
			virtual void Direct3D9_RegisterScriptTexture(Script^ forScript, IntPtr ptr)			abstract;
			virtual void Direct3D9_UnregisterScriptTexture(Script^ forScript, IntPtr ptr)		abstract;

		public:
			ManagerScript();

		internal:
			static ManagerScript^ s_Instance;

		};

	}

}

