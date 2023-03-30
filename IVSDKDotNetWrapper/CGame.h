#pragma once

using namespace IVSDKDotNet::Enums;

class Native_CGame
{
public:

	static char*	GetGameFile()				{ return AddressSetter::GetRef<char*>(0x1FDC9, 0x93949); }
	static void		SetGameFile(char* gameFile) { AddressSetter::GetRef<char*>(0x1FDC9, 0x93949) = gameFile; }

	static uint32_t GetCurrentEpisode()				{ return AddressSetter::GetRef<uint32_t>(0xCF8044, 0xD2D754); }
	static void		SetCurrentEpisode(uint32_t id)	{ AddressSetter::GetRef<uint32_t>(0xCF8044, 0xD2D754) = id;	}

	static uint32_t GetCurrentEpisodeMenu()				{ return AddressSetter::GetRef<uint32_t>(0xCF8078, 0xD2D788); }
	static void		SetCurrentEpisodeMenu(uint32_t id)	{ AddressSetter::GetRef<uint32_t>(0xCF8078, 0xD2D788) = id; }

	static bool Initialise(const char* sGameDat)
	{
		return ((bool(__cdecl*)(const char*))(AddressSetter::Get(0x4ADA50, 0x770660)))(sGameDat);
	}
};

namespace IVSDKDotNet {

	public ref class CGame
	{
	public:

		/// <summary>
		/// Gives you access to some functions of the IV-SDK .NET console.
		/// </summary>
		ref class Console
		{
		public:
			/// <summary>
			/// Gets if the IV-SDK .NET console is currently open.
			/// </summary>
			static property bool IsConsoleOpen {
				bool get() { return Manager::ManagerScript::s_Instance ? Manager::ManagerScript::s_Instance->IsConsoleOpen() : false; }
			}

			/// <summary>
			/// Opens the IV-SDK .NET console.
			/// </summary>
			static void Open();

			/// <summary>
			/// Closes the IV-SDK .NET console.
			/// </summary>
			static void Close();

			/// <summary>
			/// Clears everything in the IV-SDK .NET console.
			/// </summary>
			static void Clear();

			/// <summary>
			/// Prints a string to the console with the default colour.
			/// </summary>
			/// <param name="str">The string you want to print to the console.</param>
			static void Print(String^ str);

			/// <summary>
			/// ONLY AVAILABLE IN DEBUG MODE! Prints a string to the console with the debug colours.
			/// </summary>
			/// <param name="str">The string you want to print to the console.</param>
			static void PrintDebug(String^ str);

			/// <summary>
			/// Prints a warning to the console.
			/// </summary>
			/// <param name="str">The string you want to print to the console.</param>
			static void PrintWarning(String^ str);

			/// <summary>
			/// Prints an error to the console.
			/// </summary>
			/// <param name="str">The string you want to print to the console.</param>
			static void PrintError(String^ str);

			/// <summary>
			/// Registers a new console command that you can execute by its name in the IV-SDK .NET console.
			/// </summary>
			/// <param name="addFor">The script the console command belongs to.</param>
			/// <param name="name">The name of this command. (Name is not case sensitive)</param>
			/// <param name="actionToExecute">The action that should be executed if the command gets executed.</param>
			/// <returns>True if the command got registered. False if the command already exists, or if the given name is null or whitespace.</returns>
			static bool RegisterCommand(Script^ addFor, String^ name, Action<array<String^>^>^ actionToExecute);

			/// <summary>
			/// Executes a command registered in the IV-SDK .NET console by its name.
			/// </summary>
			/// <param name="name">The name of this command.</param>
			/// <returns>True if the command got registered. False if the command does not exists, or if the given name is null or whitespace.</returns>
			static bool ExecuteCommand(String^ name);
		};

		/// <summary>
		/// Gives you access to some functions of the IV-SDK .NET mouse.
		/// </summary>
		ref class Mouse
		{
		public:

			/// <summary>
			/// Gets or sets if the mouse cursor should be visible.
			/// </summary>
			static property bool IsVisible {
				bool get() { return Manager::ManagerScript::s_Instance ? Manager::ManagerScript::s_Instance->GetMouseVisibility() : false; }
				void set(bool value)
				{
					if (Manager::ManagerScript::s_Instance)
						Manager::ManagerScript::s_Instance->SetMouseVisibility(value);
				}
			}

			/// <summary>
			/// Gets if the left button is pressed or not.
			/// </summary>
			static property bool LeftButtonDown {
				bool get() { return Manager::ManagerScript::s_Instance ? Manager::ManagerScript::s_Instance->GetMouseLeftButtonDown() : false; }
			}

			/// <summary>
			/// Gets if the right button is pressed or not.
			/// </summary>
			static property bool RightButtonDown {
				bool get() { return Manager::ManagerScript::s_Instance ? Manager::ManagerScript::s_Instance->GetMouseRightButtonDown() : false; }
			}

			/// <summary>
			/// Gets if the first x button on the mouse is pressed or not.
			/// </summary>
			static property bool XButton1Down {
				bool get() { return Manager::ManagerScript::s_Instance ? Manager::ManagerScript::s_Instance->GetMouseXButton1Down() : false; }
			}

			/// <summary>
			/// Gets if the second x button on the mouse is pressed or not.
			/// </summary>
			static property bool XButton2Down {
				bool get() { return Manager::ManagerScript::s_Instance ? Manager::ManagerScript::s_Instance->GetMouseXButton2Down() : false; }
			}

			/// <summary>
			/// Gets the current mouse wheel value.
			/// </summary>
			static property int MouseWheel {
				int get() { return Manager::ManagerScript::s_Instance ? Manager::ManagerScript::s_Instance->GetMouseWheelValue() : 0; }
			}

			/// <summary>
			/// Gets or sets the size of the cursor.
			/// </summary>
			static property Size CursorSize {
				Size get() { return Manager::ManagerScript::s_Instance ? Manager::ManagerScript::s_Instance->GetMouseCursorSize() : Size::Empty; }
				void set(Size value)
				{
					if (Manager::ManagerScript::s_Instance)
						Manager::ManagerScript::s_Instance->SetMouseCursorSize(value);
				}
			}

			/// <summary>
			/// Gets or sets the position of the mouse cursor.
			/// </summary>
			static property Point Position {
				Point get() { return Manager::ManagerScript::s_Instance ? Manager::ManagerScript::s_Instance->GetMousePosition() : Point::Empty; }
				void set(Point value)
				{
					if (Manager::ManagerScript::s_Instance)
						Manager::ManagerScript::s_Instance->SetMousePosition(value);
				}
			}

			/// <summary>
			/// Gets if the mouse cursor intersects with the given rectangle.
			/// </summary>
			/// <param name="rect">The rectangle to check.</param>
			/// <returns>True if the mouse cursor intersects with the given rectangle. Otherwise, false.</returns>
			static bool IntersectsWith(Drawing::Rectangle rect);

		};

		delegate void OnWndMessageDelegate(IntPtr hWnd, int msg, IntPtr wParam, IntPtr lParam);
		delegate void GameWindowFocusChangedDelegate(bool focused);

		/// <summary>
		/// Gets raised when the GTA IV window receives Windows Messages. See https://wiki.winehq.org/List_Of_Windows_Messages for a list of all Windows Messages.
		/// </summary>
		static event OnWndMessageDelegate^ OnWndMessage;
		static void RaiseOnWndMessage(IntPtr hWnd, int msg, IntPtr wParam, IntPtr lParam) { OnWndMessage(hWnd, msg, wParam, lParam); }

		/// <summary>
		/// Gets raised when the focus of the GTA IV window changes.
		/// </summary>
		static event GameWindowFocusChangedDelegate^ OnWindowFocusChanged;
		static void RaiseOnWindowFocusChanged(bool focused) { OnWindowFocusChanged(focused); }

		/// <summary>
		/// Gets or sets the gta.dat path (common:/data/gta.dat).
		/// </summary>
		static property String^ GameFile {
			public:
				String^ get() { return gcnew String(Native_CGame::GetGameFile()); }
				void	set(String^ value) {
					msclr::interop::marshal_context ctx;
					Native_CGame::SetGameFile((char*)ctx.marshal_as<const char*>(value));
				}
		}

		/// <summary>
		/// Gets or sets the current episode id.
		/// </summary>
		static property uint32_t CurrentEpisode {
			public:
				uint32_t	get()				{ return Native_CGame::GetCurrentEpisode(); }
				void		set(uint32_t value) { Native_CGame::SetCurrentEpisode(value);	}
		}

		/// <summary>
		/// Gets or sets the current episode menu id.
		/// Used for switching hudcolor in each episode's menu screen and for loading the right episode when you hit play.
		/// </summary>
		static property uint32_t CurrentEpisodeMenu {
			public:
				uint32_t	get()				{ return Native_CGame::GetCurrentEpisodeMenu(); }
				void		set(uint32_t value) { Native_CGame::SetCurrentEpisodeMenu(value);	}
		}

		/// <summary>
		/// Gets the current version of GTA IV.
		/// </summary>
		static property eGameVersion GameVersion {
			public:		eGameVersion get()				{ return m_gameVersion; }
			internal:	void set(eGameVersion value)	{ m_gameVersion = value; }
		}

		/// <summary>
		/// Gets the resolution of the GTA IV window.
		/// </summary>
		static property System::Drawing::Size Resolution {
			public: System::Drawing::Size get() {
				RECT rect;
				GetWindowRect(Native_RAGE::GetHWND(), &rect);
				return System::Drawing::Size(rect.right - rect.left, rect.bottom - rect.top);
			}
		}

		/// <summary>
		/// Gets the absolute path to where GTA IV got started.
		/// </summary>
		static property String^ GameStartupPath {
			public: String^ get() { return Application::StartupPath; }
		}

		/// <summary>
		/// Undocumented.
		/// </summary>
		/// <param name="sGameDat">Path to the gta.dat file?</param>
		/// <returns>True if initialization was successful? Otherwise, false.</returns>
		static bool Initialise(String^ sGameDat);

		/// <summary>
		/// Gets if the GTA IV main window is currently in focus.
		/// </summary>
		/// <returns>True if GTA IV is currently in focus. Otherwise, false.</returns>
		static bool IsInFocus();

		/// <summary>
		/// Checks if the specified key is pressed.
		/// </summary>
		/// <param name="key">The key to check if it's pressed.</param>
		/// <returns>True if the key is pressed, otherwise false.</returns>
		static bool IsKeyPressed(Keys key);

		/// <summary>
		/// Gets the rectangle of the radar with the specific scaling.
		/// </summary>
		/// <param name="scaling">The scaling to apply.</param>
		/// <returns>The rectangle of the radar.</returns>
		static RectangleF GetRadarRectangle(eFontScaling scaling);

		/// <summary>
		/// Gets the rectangle of the radar in pixel.
		/// </summary>
		/// <returns>The rectangle of the radar.</returns>
		static RectangleF GetRadarRectangle();

		/// <summary>
		/// Shows text at the bottom center of the screen where the subtitles are located.
		/// Only works in-game.
		/// </summary>
		/// <param name="str">The text to be shown.</param>
		/// <param name="time">How long the text should be shown in milliseconds.</param>
		static void ShowSubtitleMessage(String^ str, uint32_t time);

		/// <summary>
		/// Shows text at the bottom center of the screen where the subtitles are located.
		/// Only works in-game.
		/// </summary>
		/// <param name="str">The text to be shown.</param>
		static void ShowSubtitleMessage(String^ str);

	internal:
		static eGameVersion m_gameVersion;
	};

}
