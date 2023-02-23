#pragma once

#include "EventArgs.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Drawing;
using namespace System::Reflection;
using namespace System::Windows::Forms;

namespace IVSDKDotNet {

	/// <summary>
	///	Marks the class as a IV-SDK DotNet Script.
	///	This class needs to be inherited if you want this class to be the entry point of your IV-SDK DotNet Script.
	/// </summary>
	public ref class Script
	{
	public:
		Script();
		~Script() {};

		delegate String^ ScriptAssemblyResolveDelegate(String^ assemblyFileName);
		delegate void AutomobileDelegate(UIntPtr vehPtr);

		/// <summary>
		/// Gets called after the constructor so you can safely call any functions in here without having to worry about stuff not being initialized yet.
		/// Native functions cannot be called in here yet.
		/// </summary>
		event EventHandler^ Initialized;

		/// <summary>
		/// Gets called when the script is about to be unloaded so you can free some previously created stuff in here.
		/// </summary>
		event EventHandler^ Uninitialize;

		/// <summary>
		/// Gets called every frame when in-game.
		/// (CGame.Process)
		/// </summary>
		event EventHandler^ Tick;

		/// <summary>
		/// Gets called when game is loading or when switching from one episode to another.
		/// Can be used for addon files that don't interfere with game files.
		/// </summary>
		event EventHandler^ GameLoad;

		/// <summary>
		/// Gets called before GameLoad when game is loading or when switching from one episode to another.
		/// Can be used for files that need to overwrite base game files.
		/// </summary>
		event EventHandler^ GameLoadPriority;

		/// <summary>
		/// Gets called when game is loading, switching from one episode to another or when loading the same save game again.
		/// Can be used for any rage.fiDevice stuff.
		/// </summary>
		event EventHandler^ MountDevice;

		/// <summary>
		/// Gets called twice per frame when in game, and even works in main menu.
		/// (CRenderPhasePostRenderViewport)
		/// </summary>
		event EventHandler^ Drawing;

		/// <summary>
		/// Gets called after CCamera.m_pFinalCam has been written to.
		/// </summary>
		event EventHandler^ ProcessCamera;

		/// <summary>
		/// Gets called after CAutomobile.Process, overriding steer & pedals works here.
		/// </summary>
		event AutomobileDelegate^ ProcessAutomobile;

		/// <summary>
		/// Gets called EVERYTIME even when in main menu.
		/// You can set all pad controls here, called once per frame for each pad.
		/// </summary>
		event EventHandler^ ProcessPad;

		/// <summary>
		/// Gets called when a key was released.
		/// </summary>
		event KeyEventHandler^ KeyUp;

		/// <summary>
		/// Gets called when a key was pressed.
		/// </summary>
		event KeyEventHandler^ KeyDown;

		/// <summary>
		/// Gets called when you set Script.AssembliesLocation to DecideManuallyForEachAssembly and an Assembly gets requested for this Script.
		/// You need to return the absolut path of the reqested Assembly.
		/// </summary>
		event ScriptAssemblyResolveDelegate^ AssemblyResolve;

		void RaiseInitialized()						{ Initialized(this, EventArgs::Empty); }
		void RaiseUninitialize()					{ Uninitialize(this, EventArgs::Empty); }
		void RaiseTick()							{ Tick(this, EventArgs::Empty); }
		void RaiseGameLoad()						{ GameLoad(this, EventArgs::Empty); }
		void RaiseGameLoadPriority()				{ GameLoadPriority(this, EventArgs::Empty); }
		void RaiseMountDevice()						{ MountDevice(this, EventArgs::Empty); }
		void RaiseDrawing()							{ Drawing(this, EventArgs::Empty); }
		void RaiseProcessCamera()					{ ProcessCamera(this, EventArgs::Empty); }
		void RaiseProcessAutomobile(UIntPtr vehPtr)	{ ProcessAutomobile(vehPtr); }
		void RaiseProcessPad()						{ ProcessPad(this, EventArgs::Empty); }
		void RaiseKeyUp(KeyEventArgs^ args)			{ KeyUp(this, args); }
		void RaiseKeyDown(KeyEventArgs^ args)		{ KeyDown(this, args); }

		String^ RaiseAssemblyResolve(String^ assemblyFileName) { return AssemblyResolve(assemblyFileName); }

		/// <summary>
		/// Starts a new asynchronous task.
		/// </summary>
		/// <param name="funcToExecute">The function that should be executed.</param>
		/// <returns>The Guid of the just created Task which can be used to control the Task. If Guid is empty then Task could not get created.</returns>
		Guid StartNewTask(Func<Object^>^ funcToExecute);

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
		/// Shows text at the bottom center of the screen where the subtitles are located.
		/// Only works in-game.
		/// </summary>
		/// <param name="str">The text to be shown.</param>
		/// <param name="time">How long the text should be shown in milliseconds.</param>
		void ShowSubtitleMessage(String^ str, uint32_t time);

		/// <summary>
		/// Shows text at the bottom center of the screen where the subtitles are located.
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
		/// Registers a new console command that you can execute by its name in the IV-SDK DotNet console.
		/// </summary>
		/// <param name="name">The name of this command. (Name is not case sensitive)</param>
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
		/// The unique ID of this script.
		/// </summary>
		property Guid ID {
			public:		Guid get()				{ return m_id; }
			private:	void set(Guid value)	{ m_id = value; }
		}

		/// <summary>
		/// Gets the current AppDomain of this script.
		/// </summary>
		property AppDomain^ ScriptDomain {
			public:		AppDomain^ get()			{ return m_AppDomain; }
			internal:	void set(AppDomain^ value)	{ m_AppDomain = value; }
		}

		/// <summary>
		/// Gets or sets where the Assemblies are located for this script. Default: GameRootDirectory
		/// </summary>
		property eAssembliesLocation AssembliesLocation {
			public:
				eAssembliesLocation get()			{ return m_AssembliesLocation; }
				void set(eAssembliesLocation value) { m_AssembliesLocation = value; }
		}

		/// <summary>
		/// Gets or sets the custom Assemblies path for this Script if you have set the AssembliesLocation to Custom.
		/// The path is relative to the root directory of GTA IV.
		/// Example: IVSDKDotNet\scripts\AssembliesForMyEpicScript - The Assemblies for your Script will now be loaded from the AssembliesForMyEpicScript folder.
		/// </summary>
		property String^ CustomAssembliesPath {
			public:
				String^ get()				{ return m_CustomAssembliesPath; }
				void	set(String^ value)	{ m_CustomAssembliesPath = value; }
		}

		/// <summary>
		/// Gets or sets the resource folder for this Script where all the files required by this Script are located.
		/// The folder has to be named the same name as your Script (without extension), and needs to be placed in the scripts folder.
		/// The string will be null if the folder doesn't exist.
		/// </summary>
		property String^ ScriptResourceFolder {
			public:
				String^ get()				{ return m_ScriptResourceFolder; }
				void	set(String^ value)	{ m_ScriptResourceFolder = value; }
		}

		/// <summary>
		/// The settings file of this script.
		/// </summary>
		property SettingsFile^ Settings {
			public: 
				SettingsFile^ get()				{ return m_SettingsFile; }
				void set(SettingsFile^ value)	{ m_SettingsFile = value; }
		}

#pragma region Measurement Properties
		/// <summary>
		/// Gets how much time the Initialized event took to execute.
		/// </summary>
		property TimeSpan InitializedEventExecutionTime {
		public:
			TimeSpan	get() { return m_sInitializedEventExecutionTime; }
			void		set(TimeSpan value) { m_sInitializedEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the Tick event took to execute.
		/// </summary>
		property TimeSpan TickEventExecutionTime {
			public:
				TimeSpan	get()				{ return m_sTickEventExecutionTime; }
				void		set(TimeSpan value) { m_sTickEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the GameLoad event took to execute.
		/// </summary>
		property TimeSpan GameLoadEventExecutionTime {
			public:
				TimeSpan	get()				{ return m_sGameLoadEventExecutionTime; }
				void		set(TimeSpan value) { m_sGameLoadEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the GameLoadPriority event took to execute.
		/// </summary>
		property TimeSpan GameLoadPriorityEventExecutionTime {
			public:
				TimeSpan	get()				{ return m_sGameLoadPriorityEventExecutionTime; }
				void		set(TimeSpan value) { m_sGameLoadPriorityEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the MountDevice event took to execute.
		/// </summary>
		property TimeSpan MountDeviceEventExecutionTime {
			public:
				TimeSpan	get()				{ return m_sMountDeviceEventExecutionTime; }
				void		set(TimeSpan value) { m_sMountDeviceEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the Drawing event took to execute.
		/// </summary>
		property TimeSpan DrawingEventExecutionTime {
			public:
				TimeSpan	get()				{ return m_sDrawingEventExecutionTime; }
				void		set(TimeSpan value) { m_sDrawingEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the ProcessCamera event took to execute.
		/// </summary>
		property TimeSpan ProcessCameraEventExecutionTime {
			public:
				TimeSpan	get()				{ return m_sProcessCameraEventExecutionTime; }
				void		set(TimeSpan value) { m_sProcessCameraEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the ProcessAutomobile event took to execute.
		/// </summary>
		property TimeSpan ProcessAutomobileEventExecutionTime {
			public:
				TimeSpan	get()				{ return m_sProcessAutomobileEventExecutionTime; }
				void		set(TimeSpan value) { m_sProcessAutomobileEventExecutionTime = value; }
		}
		/// <summary>
		/// Gets how much time the ProcessPad event took to execute.
		/// </summary>
		property TimeSpan ProcessPadEventExecutionTime {
			public:
				TimeSpan	get()				{ return m_sProcessPadEventExecutionTime; }
				void		set(TimeSpan value) { m_sProcessPadEventExecutionTime = value; }
		}
#pragma endregion

	private:
		Guid m_id;
		AppDomain^ m_AppDomain;
		eAssembliesLocation m_AssembliesLocation;
		String^ m_CustomAssembliesPath;
		String^ m_ScriptResourceFolder;
		SettingsFile^ m_SettingsFile;

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
	};

	/// <summary> Internal-only IV-SDK Manager stuff. </summary>
	namespace Manager {

		/// <summary>
		/// Only used for the IV-SDK DotNet Manager.
		/// There can only be one instance of this class.
		/// </summary>
		public ref class ManagerScript
		{
		public:
			ManagerScript();

			static ManagerScript^ s_Instance;

			void Debug_ShowMessageBox(String^ str);
			void Debug_ShowInfoMessageBox(String^ str);
			void Debug_ShowWarnMessageBox(String^ str);
			void Debug_ShowErrorMessageBox(String^ str);

			// Helper
			virtual String^ Helper_JSON_ConvertObjectToJsonString(Object^ obj)				abstract;
			virtual System::Object^ Helper_JSON_ConvertJsonStringToObject(String^ str)		abstract;

			// Console
			virtual void OpenConsole()						abstract;
			virtual void CloseConsole()						abstract;
			virtual void ClearConsole()						abstract;
			virtual void PrintToConsole(String^ str)		abstract;
			virtual void PrintDebugToConsole(String^ str)	abstract;
			virtual void PrintWarnToConsole(String^ str)	abstract;
			virtual void PrintErrorToConsole(String^ str)	abstract;

			virtual bool RegisterConsoleCommand(Guid fromScript, String^ name, Action<array<String^>^>^ actionToExecute) abstract;
			virtual bool ExecuteConsoleCommand(String^ name) abstract;

			// Script
			virtual void RaiseTick()							abstract;
			virtual void RaiseGameLoad()						abstract;
			virtual void RaiseGameLoadPriority()				abstract;
			virtual void RaiseMountDevice()						abstract;
			virtual void RaiseDrawing()							abstract;
			virtual void RaiseProcessCamera()					abstract;
			virtual void RaiseProcessAutomobile(UIntPtr vehPtr)	abstract;
			virtual void RaiseProcessPad()						abstract;

			virtual void LoadScripts()							abstract;
			virtual void LoadScript(String^ name)				abstract;
			virtual bool AbortScript(Guid id)					abstract;
			virtual void AbortScripts(bool showMessage)			abstract;

			virtual Script^	GetScript(Guid id)					abstract;
			virtual Script^	GetScript(String^ name)				abstract;
			virtual array<Script^>^ GetAllScripts()				abstract;
			virtual String^	GetScriptName(Guid id)				abstract;
			virtual String^ GetScriptFullPath(Guid id)			abstract;
			virtual int GetActiveScriptsCount()					abstract;

			// Task
			virtual Guid StartNewTask(Guid forScript, Func<Object^>^ actionToExecute)			abstract;
			virtual Guid StartNewTimer(Guid forScript, int interval, Action^ actionToExecute)	abstract;

			virtual void WaitInTask(Guid id, int waitTimeInMilliseconds)						abstract;
			virtual void AbortTaskOrTimer(Guid id)												abstract;
			virtual void ChangeTimerState(Guid id, bool pause)									abstract;

			// Direct3D9 -> Graphics
			virtual void Direct3D9_Graphics_CreateNewInstance(Object^ instance, Script^ forScript)	abstract;
			virtual void Direct3D9_Graphics_DisposeInstance(Script^ ofScript)						abstract;

			virtual Direct3D9::D3DResult^ Direct3D9_Graphics_CreateD3D9Texture(Script^ forScript, IntPtr device, String^ filePath, Size size)					abstract;
			virtual Direct3D9::D3DResult^ Direct3D9_Graphics_CreateD3D9Texture(Script^ forScript, IntPtr device, array<Byte>^ data, Size size)					abstract;
			virtual Exception^ Direct3D9_Graphics_ReleaseD3D9Texture(Script^ ofScript, Direct3D9::D3DResource^ resource)										abstract;

			virtual Direct3D9::D3DResult^ Direct3D9_Graphics_CreateD3D9Font(Script^ forScript, IntPtr device, Direct3D9::D3DFontDescription fontDescription)	abstract;
			virtual Exception^ Direct3D9_Graphics_ReleaseD3D9Font(Script^ ofScript, Direct3D9::D3DResource^ resource)											abstract;

			virtual bool Direct3D9_Graphics_DrawLines(Object^ instance, IntPtr device, array<Vector2>^ vertices, Color color, bool antialias, int pattern, float patternScale, float thickness)								abstract;
			virtual bool Direct3D9_Graphics_DrawLine(Object^ instance, IntPtr device, Vector2 point1, Vector2 point2, Color color, bool antialias, int pattern, float patternScale, float thickness)	abstract;

			virtual bool Direct3D9_Graphics_DrawCircle(Object^ instance, IntPtr device, Vector2 pos, float radius, float rotation, Direct3D9::eD3DCircleType type, bool smoothing, int resolution, Color color)				abstract;
			virtual bool Direct3D9_Graphics_DrawCircleFilled(Object^ instance, IntPtr device, Vector2 pos, float radius, float rotation, Direct3D9::eD3DCircleType type, bool smoothing, int resolution, Color color)			abstract;

			virtual bool Direct3D9_Graphics_DrawBoxFilled(Object^ instance, IntPtr device, Vector2 pos, SizeF size, Color color)																		abstract;
			virtual bool Direct3D9_Graphics_DrawBox(Object^ instance, IntPtr device, Vector2 pos, SizeF size, float lineWidth, Color color)															abstract;
			virtual bool Direct3D9_Graphics_DrawBoxBordered(Object^ instance, IntPtr device, Vector2 pos, SizeF size, float borderWidth, Color color, Color borderColor)								abstract;
			virtual bool Direct3D9_Graphics_DrawBoxRounded(Object^ instance, IntPtr device, Vector2 pos, SizeF size, float radius, bool smoothing, Color color, Color borderColor)					abstract;

			virtual bool Direct3D9_Graphics_DrawTexture(Object^ instance, IntPtr device, Direct3D9::D3DResource^ txt, RectangleF rect, float rotation, Color tint)									abstract;

			virtual bool Direct3D9_Graphics_DrawString(Object^ instance, IntPtr device, Direct3D9::D3DResource^ fontResource, String^ text, Point pos, Color color)									abstract;

		};

	}

}

