#pragma once

namespace IVSDKDotNet
{
	public ref class IVGame
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
			static property bool IsConsoleOpen
			{
				bool get()
				{
					return Manager::ManagerScript::s_Instance ? Manager::ManagerScript::s_Instance->IsConsoleOpen() : false;
				}
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
			/// Prints a string to the console with the default colour.
			/// </summary>
			/// <param name="str">The string you want to print to the console.</param>
			/// <param name="args">The objects to format.</param>
			static void PrintEx(String^ str, ...array<System::Object^>^ args)
			{
				Print(String::Format(str, args));
			}

			/// <summary>
			/// ONLY AVAILABLE IN DEBUG MODE! Prints a string to the console with the debug colours.
			/// </summary>
			/// <param name="str">The string you want to print to the console.</param>
			static void PrintDebug(String^ str);
			/// <summary>
			/// ONLY AVAILABLE IN DEBUG MODE! Prints a string to the console with the debug colours.
			/// </summary>
			/// <param name="str">The string you want to print to the console.</param>
			/// <param name="args">The objects to format.</param>
			static void PrintDebugEx(String^ str, ...array<System::Object^>^ args)
			{
				PrintDebug(String::Format(str, args));
			}

			/// <summary>
			/// Prints a warning to the console.
			/// </summary>
			/// <param name="str">The string you want to print to the console.</param>
			static void PrintWarning(String^ str);
			/// <summary>
			/// Prints a warning to the console.
			/// </summary>
			/// <param name="str">The string you want to print to the console.</param>
			/// <param name="args">The objects to format.</param>
			static void PrintWarningEx(String^ str, ...array<System::Object^>^ args)
			{
				PrintWarning(String::Format(str, args));
			}

			/// <summary>
			/// Prints an error to the console.
			/// </summary>
			/// <param name="str">The string you want to print to the console.</param>
			static void PrintError(String^ str);
			/// <summary>
			/// Prints an error to the console.
			/// </summary>
			/// <param name="str">The string you want to print to the console.</param>
			/// <param name="args">The objects to format.</param>
			static void PrintErrorEx(String^ str, ...array<System::Object^>^ args)
			{
				PrintError(String::Format(str, args));
			}

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

	public:
		/// <summary>
		/// common:/data/gta.dat
		/// </summary>
		static property String^ GameFile
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CGame::sGameFile, String::Empty);
				return gcnew String(CGame::sGameFile);
			}
			void set(String^ value)
			{
				CHECK_NULL_OR_WHITESPACE_STRING(value);
				msclr::interop::marshal_context ctx;
				CGame::sGameFile = (char*)ctx.marshal_as<const char*>(value);
			}
		}

		/// <summary>
		/// Gets or sets the current episode.
		/// </summary>
		static property uint32_t CurrentEpisode
		{
		public:
			uint32_t get()
			{
				return CGame::m_nCurrentEpisode;
			}
			void set(uint32_t value)
			{
				CGame::m_nCurrentEpisode = value;
			}
		}
		/// <summary>
		/// Gets or sets the forced episode.
		/// </summary>
		static property uint32_t ForcedEpisode
		{
		public:
			uint32_t get()
			{
				return CGame::m_nForcedEpisode;
			}
			void set(uint32_t value)
			{
				CGame::m_nForcedEpisode = value;
			}
		}
		/// <summary>
		/// Gets or sets the current episode menu.
		/// Used for switching hudcolor in each episode's menu screen and for loading the right episode when you hit play.
		/// </summary>
		static property uint32_t CurrentEpisodeMenu
		{
		public:
			uint32_t get()
			{
				return CGame::m_nCurrentEpisodeMenu;
			}
			void set(uint32_t value)
			{
				CGame::m_nCurrentEpisodeMenu = value;
			}
		}

		/// <summary>
		/// Gets the current menu.
		/// </summary>
		static property uint32_t MenuState
		{
		public:
			uint32_t get()
			{
				return CGame::m_nMenuState;
			}
			void set(uint32_t value)
			{
				CGame::m_nMenuState = value;
			}
		}

		/// <summary>
		/// Gets the current version of GTA IV.
		/// </summary>
		static property eGameVersion GameVersion
		{
		public:	
			eGameVersion get()
			{
				return MemoryAccess::GameVersion;
			}
		}

		/// <summary>
		/// Gets the absolute path to where GTA IV got started.
		/// </summary>
		static property String^ GameStartupPath
		{
		public:
			String^ get()
			{
				return Application::StartupPath;
			}
		}

		/// <summary>
		/// Gets the resolution of the GTA IV window.
		/// </summary>
		static property Size Resolution
		{
		public:
			System::Drawing::Size get()
			{
				RECT rect;
				GetWindowRect(rage::g_pHWND, &rect);
				return System::Drawing::Size(rect.right - rect.left, rect.bottom - rect.top);
			}
		}

		/// <summary>
		/// Gets the bounds of the GTA IV window.
		/// </summary>
		static property System::Drawing::Rectangle Bounds
		{
		public:
			System::Drawing::Rectangle get()
			{
				RECT rect;

				if (GetWindowRect((HWND)CLR::CLRBridge::TheGTAProcess->MainWindowHandle.ToInt32(), &rect))
					return System::Drawing::Rectangle(rect.left, rect.top, rect.right, rect.bottom);

				return System::Drawing::Rectangle::Empty;
			}
		}

	public:
		/// <summary>
		/// Undocumented.
		/// </summary>
		/// <param name="sGameDat">Path to the gta.dat file?</param>
		/// <returns>True if initialization was successful? Otherwise, false.</returns>
		static bool Initialise(String^ sGameDat);

		static bool IsGameRestarting()
		{
			return CGame::IsGameRestarting();
		}

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
		/// Shows text at the bottom center of the screen where the subtitles are located.
		/// Only works in-game.
		/// </summary>
		/// <param name="str">The text to be shown.</param>
		/// <param name="args">An object array that contains zero or more objects to format.</param>
		static void ShowSubtitleMessageEx(String^ str, ...array<System::Object^>^ args);

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

		static void Idk(int episode, int a2, char a3, char a4)
		{
			CGame::Idk(episode, a2, a3, a4);
		}

	};
}