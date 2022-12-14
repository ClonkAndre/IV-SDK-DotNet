#pragma once

#include "EventArgs.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Drawing;
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

		/// <summary>
		/// Gets called after the constructor so you can safely call any functions in here without having to worry about stuff not being initialized yet.
		/// </summary>
		event EventHandler^ Initialized;

		/// <summary>
		/// Gets called every frame when in-game.
		/// </summary>
		event EventHandler^ Tick;

		/// <summary>
		/// Gets called when game is loading or when switching from one episode to another.
		/// </summary>
		event EventHandler^ GameLoad;

		/// <summary>
		/// Gets called before GameLoad when game is loading or when switching from one episode to another.
		/// </summary>
		event EventHandler^ GameLoadPriority;

		/// <summary>
		/// Gets called when game is loading, switching from one episode to another or when loading the same save game again.
		/// </summary>
		event EventHandler^ MountDevice;

		/// <summary>
		/// Gets called EVERYTIME even when in main menu.
		/// </summary>
		event EventHandler^ Drawing;

		/// <summary>
		/// Gets called everytime when in-game.
		/// </summary>
		event EventHandler^ ProcessCamera;

		/// <summary>
		/// Gets called everytime when in-game.
		/// </summary>
		event EventHandler^ ProcessAutomobile;

		/// <summary>
		/// Gets called EVERYTIME even when in main menu.
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

		void RaiseInitialized()					{ Initialized(this, EventArgs::Empty); }
		void RaiseTick()						{ Tick(this, EventArgs::Empty); }
		void RaiseGameLoad()					{ GameLoad(this, EventArgs::Empty); }
		void RaiseGameLoadPriority()			{ GameLoadPriority(this, EventArgs::Empty); }
		void RaiseMountDevice()					{ MountDevice(this, EventArgs::Empty); }
		void RaiseDrawing()						{ Drawing(this, EventArgs::Empty); }
		void RaiseProcessCamera()				{ ProcessCamera(this, EventArgs::Empty); }
		void RaiseProcessAutomobile()			{ ProcessAutomobile(this, EventArgs::Empty); }
		void RaiseProcessPad()					{ ProcessPad(this, EventArgs::Empty); }
		void RaiseKeyUp(KeyEventArgs^ args)		{ KeyUp(this, args); }
		void RaiseKeyDown(KeyEventArgs^ args)	{ KeyDown(this, args); }
		
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
				String^ get()			{ return m_CustomAssembliesPath; }
				void set(String^ value) { m_CustomAssembliesPath = value; }
		}

		/// <summary>
		/// The settings file of this script.
		/// </summary>
		property SettingsFile^ Settings {
			public: 
				SettingsFile^ get()				{ return m_SettingsFile; }
				void set(SettingsFile^ value)	{ m_SettingsFile = value; }
		}

	private:
		Guid m_id;
		AppDomain^ m_AppDomain;
		eAssembliesLocation m_AssembliesLocation;
		String^ m_CustomAssembliesPath;
		SettingsFile^ m_SettingsFile;
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

			// Console
			virtual void OpenConsole()						abstract;
			virtual void CloseConsole()						abstract;
			virtual void ClearConsole()						abstract;
			virtual void PrintToConsole(String^ str)		abstract;
			virtual void PrintDebugToConsole(String^ str)	abstract;
			virtual void PrintWarnToConsole(String^ str)	abstract;
			virtual void PrintErrorToConsole(String^ str)	abstract;

			virtual bool RegisterConsoleCommand(Guid fromScript, String^ name, Action<array<String^>^>^ actionToExecute) abstract;
			virtual bool ExecuteConsoleCommand(String^ name)	abstract;

			// Script
			virtual void RaiseTick()						abstract;
			virtual void RaiseGameLoad()					abstract;
			virtual void RaiseGameLoadPriority()			abstract;
			virtual void RaiseMountDevice()					abstract;
			virtual void RaiseDrawing()						abstract;
			virtual void RaiseProcessCamera()				abstract;
			virtual void RaiseProcessAutomobile()			abstract;
			virtual void RaiseProcessPad()					abstract;

			virtual void LoadScripts()						abstract;
			virtual bool AbortScript(Guid id)				abstract;
			virtual void AbortScripts(bool showMessage)		abstract;

			virtual Script^	GetScript(Guid id)				abstract;
			virtual Script^	GetScript(String^ name)			abstract;
			virtual array<Script^>^ GetAllScripts()			abstract;
			virtual String^	GetScriptName(Guid id)			abstract;
			virtual String^ GetScriptFullPath(Guid id)		abstract;
			virtual int GetActiveScriptsCount()				abstract;

			// Task
			virtual Guid StartNewTask(Guid forScript, Func<Object^>^ actionToExecute)	abstract;
			virtual Guid StartNewTimer(Guid forScript, int interval, Action^ actionToExecute)	abstract;

			virtual void WaitInTask(Guid id, int waitTimeInMilliseconds) abstract;

		};

	}

}

