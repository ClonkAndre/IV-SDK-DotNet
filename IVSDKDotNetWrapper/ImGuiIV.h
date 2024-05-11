#include "pch.h"

// Modified ImGui code to make it work with GTA IV from the InGameTimecycEditor Mod for GTA IV made by akifle47.
// https://github.com/akifle47/InGameTimecycEditor

// Dear ImGui: An awesome, bloat-free UI Library by ocornut
// https://github.com/ocornut/imgui

extern IMGUI_IMPL_API LONG_PTR ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace IVSDKDotNet
{
	public value struct ImGuiIV_DrawCommandData
	{
	public:
		property System::Guid CallerScriptID
		{
		public:
			System::Guid get()
			{
				return m_gCallerScriptID;
			}
		internal:
			void set(System::Guid value)
			{
				m_gCallerScriptID = value;
			}
		}

	internal:
		property Action^ Data
		{
		internal:
			Action^ get()
			{
				return m_aData;
			}
			void set(Action^ value)
			{
				m_aData = value;
			}
		}

	internal:
		ImGuiIV_DrawCommandData(System::Guid callerScriptId, Action^ data)
		{
			CallerScriptID = callerScriptId;
			Data = data;
		}

	private:
		System::Guid m_gCallerScriptID;
		Action^ m_aData;
	};

	public value struct ImGuiIV_Viewport
	{
	public:

		/// <summary>
		/// Native Pointer to the ImGuiViewport structure.
		/// </summary>
		property IntPtr ImGuiViewportPtr
		{
		public:
			IntPtr get()
			{
				return IntPtr(m_vMainViewport);
			}
		}

		/// <summary>
		/// Main Area: Position of the viewport (Dear ImGui coordinates are the same as OS desktop/native coordinates).
		/// </summary>
		property Vector2 Pos
		{
		public:
			Vector2 get()
			{
				if (!m_bIsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_vMainViewport->Pos);
			}
		}

		/// <summary>
		/// Main Area: Size of the viewport.
		/// </summary>
		property Vector2 Size
		{
		public:
			Vector2 get()
			{
				if (!m_bIsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_vMainViewport->Size);
			}
		}

		/// <summary>
		/// Work Area: Position of the viewport minus task bars, menus bars, status bars (bigger then Pos).
		/// </summary>
		property Vector2 WorkPos
		{
		public:
			Vector2 get()
			{
				if (!m_bIsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_vMainViewport->WorkPos);
			}
		}

		/// <summary>
		/// Work Area: Size of the viewport minus task bars, menu bars, status bars (smaller then Size).
		/// </summary>
		property Vector2 WorkSize
		{
		public:
			Vector2 get()
			{
				if (!m_bIsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_vMainViewport->WorkSize);
			}
		}

		/// <summary>
		/// Gets if this struct contains valid data.
		/// </summary>
		property bool IsValid
		{
		public:
			bool get()
			{
				return m_bIsValid;
			}
		}

	public:

		/// <summary>
		/// Gets the center position of the main Area.
		/// </summary>
		/// <returns>The center position of the main Area.</returns>
		Vector2 GetCenter()
		{
			if (!m_bIsValid)
				return Vector2::Zero;

			return ImVec2ToVector2(m_vMainViewport->GetCenter());
		}

		/// <summary>
		/// Gets the center position of the work Area.
		/// </summary>
		/// <returns>The center position of the work Area.</returns>
		Vector2 GetWorkCenter()
		{
			if (!m_bIsValid)
				return Vector2::Zero;

			return ImVec2ToVector2(m_vMainViewport->GetWorkCenter());
		}

	internal:
		ImGuiIV_Viewport(ImGuiViewport* vp, bool isValid)
		{
			m_vMainViewport = vp;
			m_bIsValid = isValid;
		}

	private:
		ImGuiViewport* m_vMainViewport;
		bool m_bIsValid;
	};

	public ref class ImGuiIV
	{
	internal:
		static int SelectedStyle = 0;

		static array<String^>^ FontNameSplitArray = gcnew array<String^>(1) { "," };

	public:

		/// <summary>
		/// Gets if the cursor is currently forced to be drawn on screen.
		/// </summary>
		static property bool ForceCursor
		{
		public:
			bool get()
			{
				return m_bForceCursor;
			}
		internal:
			void set(bool value)
			{
				m_bForceCursor = value;
			}
		}

		/// <summary>
		/// Gets the total amount of active ImGui windows.
		/// </summary>
		static property int ActiveWindows
		{
		public:
			int get()
			{
				return m_iActiveWindows;
			}
		internal:
			void set(int value)
			{
				m_iActiveWindows = value;
			}
		}

		/// <summary>
		/// Min normalized positive value.
		/// </summary>
		static property float FloatMin
		{
		public:
			float get()
			{
				return -FLT_MIN;
			}
		}

		/// <summary>
		/// Can be passed to ImGui Widgets so that they use the full width available. Uses the 'FloatMin' property for the Vector2's 'X' value.
		/// </summary>
		static property Vector2 FullWidth
		{
		public:
			Vector2 get()
			{
				return Vector2(FloatMin, 0.0F);
			}
		}

		/// <summary>
		/// Gets the main Viewport of ImGui.
		/// </summary>
		static property ImGuiIV_Viewport MainViewport
		{
		public:
			ImGuiIV_Viewport get()
			{
				ImGuiViewport* vp = ImGui::GetMainViewport();

				if (vp)
					return ImGuiIV_Viewport(vp, true);

				return ImGuiIV_Viewport(nullptr, false);
			}
		}

	public:
		/// <summary>
		/// Contains draw data from IV-SDK .NET Scripts that want to use utilize ImGui.
		/// Used to actually draw and manage ImGui Windows.
		/// Use "ImGuiIV.AddDrawCommand(this, () => { ... })" to use ImGui in your Script.
		/// </summary>
		static List<ImGuiIV_DrawCommandData>^ DrawCommandsList = gcnew List<ImGuiIV_DrawCommandData>(128);

	public:

		// Texture stuff
		static bool CreateTextureFromFile(Script^ forScript, String^ fileName, [OutAttribute] IntPtr% texturePtr, [OutAttribute] int% textureWidth, [OutAttribute] int% textureHeight)
		{
			if (ImGui::GetCurrentContext() == nullptr)
			{
				Logger::LogError("[ImGuiIV] Failed to create texture from file. Details: ImGui is not initialized.");

				texturePtr = IntPtr::Zero;
				textureWidth = 0;
				textureHeight = 0;
				return false;
			}
			if (forScript == nullptr)
			{
				Logger::LogError("[ImGuiIV] Failed to create texture from file. Details: forScript cannot be nullptr.");

				texturePtr = IntPtr::Zero;
				textureWidth = 0;
				textureHeight = 0;
				return false;
			}
			if (String::IsNullOrWhiteSpace(fileName))
			{
				Logger::LogError("[ImGuiIV] Failed to create texture from file. Details: fileName cannot be null or white space.");

				texturePtr = IntPtr::Zero;
				textureWidth = 0;
				textureHeight = 0;
				return false;
			}

			msclr::interop::marshal_context ctx;
			PDIRECT3DTEXTURE9 texture;

			// Try create texture
			HRESULT hr = D3DXCreateTextureFromFileExA(rage::g_pDirect3DDevice, ctx.marshal_as<const char*>(fileName), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture);
			
			if (hr != S_OK)
			{
				Logger::LogError(String::Format("[ImGuiIV] Failed to create texture from file. HResult: {0}", hr));

				texturePtr = IntPtr::Zero;
				textureWidth = 0;
				textureHeight = 0;
				return false;
			}

			// Get the texture surface description
			D3DSURFACE_DESC imageDesc;
			texture->GetLevelDesc(0, &imageDesc);

			// Set stuff
			texturePtr = IntPtr(texture);
			textureWidth = imageDesc.Width;
			textureHeight = imageDesc.Height;

			// Register texture
			if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
				IVSDKDotNet::Manager::ManagerScript::s_Instance->Direct3D9_RegisterScriptTexture(forScript, texturePtr);

			return true;
		}
		static bool CreateTextureFromMemory(Script^ forScript, array<System::Byte>^ data, [OutAttribute] IntPtr% texturePtr, [OutAttribute] int% textureWidth, [OutAttribute] int% textureHeight)
		{
			if (ImGui::GetCurrentContext() == nullptr)
			{
				Logger::LogError("[ImGuiIV] Failed to create texture from memory. Details: ImGui is not initialized.");

				texturePtr = IntPtr::Zero;
				textureWidth = 0;
				textureHeight = 0;
				return false;
			}
			if (forScript == nullptr)
			{
				Logger::LogError("[ImGuiIV] Failed to create texture from memory. Details: forScript cannot be nullptr.");

				texturePtr = IntPtr::Zero;
				textureWidth = 0;
				textureHeight = 0;
				return false;
			}
			if (data == nullptr)
			{
				Logger::LogError("[ImGuiIV] Failed to create texture from memory. Details: data cannot be null.");

				texturePtr = IntPtr::Zero;
				textureWidth = 0;
				textureHeight = 0;
				return false;
			}

			pin_ptr<System::Byte> pinnedData = &data[0];
			unsigned char* pby = pinnedData;
			void* dataPtr = reinterpret_cast<void*>(pby);

			msclr::interop::marshal_context ctx;
			PDIRECT3DTEXTURE9 texture;
			
			// Try create texture
			//HRESULT hr = D3DXCreateTextureFromFileInMemory(rage::g_pDirect3DDevice, dataPtr, data->Length, &texture);
			HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(rage::g_pDirect3DDevice, dataPtr, data->Length, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture);

			if (hr != S_OK)
			{
				Logger::LogError(String::Format("[ImGuiIV] Failed to create texture from memory. HResult: {0}", hr));

				texturePtr = IntPtr::Zero;
				textureWidth = 0;
				textureHeight = 0;
				return false;
			}

			// Get the texture surface description
			D3DSURFACE_DESC imageDesc;
			texture->GetLevelDesc(0, &imageDesc);

			// Set stuff
			texturePtr = IntPtr(texture);
			textureWidth = imageDesc.Width;
			textureHeight = imageDesc.Height;

			// Register texture
			if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
				IVSDKDotNet::Manager::ManagerScript::s_Instance->Direct3D9_RegisterScriptTexture(forScript, texturePtr);

			return true;
		}
		static bool ReleaseTexture(Script^ fromScript, IntPtr% texturePtr)
		{
			if (fromScript == nullptr)
			{
				Logger::LogError("[ImGuiIV] Failed to release texture. Details: fromScript cannot be nullptr.");
				return false;
			}
			if (texturePtr == IntPtr::Zero)
				return false;

			PDIRECT3DTEXTURE9 texture = (PDIRECT3DTEXTURE9)texturePtr.ToPointer();

			if (texture)
			{
				texture->Release();

				// Unregister texture
				if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
					IVSDKDotNet::Manager::ManagerScript::s_Instance->Direct3D9_UnregisterScriptTexture(fromScript, texturePtr);

				texturePtr = IntPtr::Zero;
				return true;
			}

			return false;
		}

		// Font stuff
		static bool AddFontFromFile(String^ fileName, float sizeInPixel, [OutAttribute] IntPtr% fontPtr)
		{
			//if (!ImGuiStates::s_bIsImGuiInitialized)
			//{
			//	Logger::LogError("[ImGuiIV] Failed to add font from file. Details: ImGui is not initialized.");
			//	fontPtr = IntPtr::Zero;
			//	return false;
			//}
			if (String::IsNullOrWhiteSpace(fileName))
			{
				Logger::LogError("[ImGuiIV] Failed to add font from file. Details: fileName cannot be null or white space.");
				fontPtr = IntPtr::Zero;
				return false;
			}

			// Get the file name with extension of the font file to be added
			String^ fileNameWithExtension = System::IO::Path::GetFileName(fileName)->ToLower();

			// Get ImGui IO
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			
			// Check if this font is already added with the given size
			for (int i = 0; i < io.Fonts->Fonts.Size; i++)
			{
				ImFont* font = io.Fonts->Fonts[i];
				
				if (!font->ConfigData)
					continue;

				String^ fontName = gcnew String(font->ConfigData->Name);

				if (String::IsNullOrWhiteSpace(fontName))
					continue;

				// Split the string at the comma character which divides the font name from the font size stored in the same char array
				fontName = fontName->Split(FontNameSplitArray, StringSplitOptions::None)[0]->ToLower();

				// Compare the font name and the font size with the one the user is trying to add
				if (fileNameWithExtension == fontName
					&& sizeInPixel == font->ConfigData->SizePixels)
				{
					fontPtr = IntPtr::Zero;
					return false;
				}
			}

			msclr::interop::marshal_context ctx;

			// Try add font from file
			ImFont* font = io.Fonts->AddFontFromFileTTF(ctx.marshal_as<const char*>(fileName), sizeInPixel);

			if (font)
			{
				fontPtr = IntPtr(font);
				return true;
			}

			Logger::LogError("[ImGuiIV] Failed to add font from file. Details: Unknown error.");
			fontPtr = IntPtr::Zero;
			return false;
		}

		// Some helper
	public:
		static Color FloatRGBToColor(Vector4 vec)
		{
			int r = Convert::ToInt32(vec.X * 255.0F);
			int g = Convert::ToInt32(vec.Y * 255.0F);
			int b = Convert::ToInt32(vec.Z * 255.0F);
			int a = Convert::ToInt32(vec.W * 255.0F);

			// Validate
			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;
			if (a > 255)
				a = 255;

			return Color::FromArgb(a, r, g, b);
		}
		static Color FloatRGBToColor(Vector3 vec)
		{
			int r = Convert::ToInt32(vec.X * 255.0F);
			int g = Convert::ToInt32(vec.Y * 255.0F);
			int b = Convert::ToInt32(vec.Z * 255.0F);

			// Validate
			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			return Color::FromArgb(255, r, g, b);
		}

		static Vector4 ColorToFloatRGB(Color color)
		{
			float r = Convert::ToSingle(color.R / 255.0F);
			float g = Convert::ToSingle(color.G / 255.0F);
			float b = Convert::ToSingle(color.B / 255.0F);
			float a = Convert::ToSingle(color.A / 255.0F);

			// Validate
			if (r > 1.0F)
				r = 1.0F;
			if (r < 0.0F)
				r = 0.0F;

			if (g > 1.0F)
				g = 1.0F;
			if (g < 0.0F)
				g = 0.0F;

			if (b > 1.0F)
				b = 1.0F;
			if (b < 0.0F)
				b = 0.0F;

			if (a > 1.0F)
				a = 1.0F;
			if (a < 0.0F)
				a = 0.0F;

			return Vector4(r, g, b, a);
		}

		// ImGui Drawing Stuff
	public:

		[ObsoleteAttribute("This will be removed in version 1.3 of IV-SDK .NET. You should instead use the OnImGuiRendering event the Script class provides you.")]
		static bool AddDrawCommand(Script^ caller, Action^ drawingAction)
		{
			if (caller == nullptr)
				return false;
			if (drawingAction == nullptr)
				return false;

			// Dot not allow any more items in this list if an item for that Script already exists with this unique Draw ID
			for (int i = 0; i < DrawCommandsList->Count; i++)
			{
				ImGuiIV_DrawCommandData data = DrawCommandsList[i];

				if (data.CallerScriptID == caller->ID)
					return false;
			}

			// Add draw call to Queue
			DrawCommandsList->Add(ImGuiIV_DrawCommandData(caller->ID, drawingAction));

			return true;
		}
		[ObsoleteAttribute("This will be removed in version 1.3 of IV-SDK .NET.")]
		static void RemoveDrawCommand(Script^ caller)
		{
			if (caller == nullptr)
				return;

			// If exists, remove draw command from list
			for (int i = 0; i < DrawCommandsList->Count; i++)
			{
				ImGuiIV_DrawCommandData data = DrawCommandsList[i];

				if (data.CallerScriptID == caller->ID)
				{
					DrawCommandsList->RemoveAt(i);
					return;
				}
			}
		}

		// General
		static void PushID(String^ id)
		{
			if (String::IsNullOrWhiteSpace(id))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::PushID(ctx.marshal_as<const char*>(id));
		}
		static void PushID(String^ id_begin, String^ id_end)
		{
			if (String::IsNullOrWhiteSpace(id_begin))
				return;
			if (String::IsNullOrWhiteSpace(id_end))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::PushID(ctx.marshal_as<const char*>(id_begin), ctx.marshal_as<const char*>(id_end));
		}
		static void PushID(IntPtr ptr_id)
		{
			if (ptr_id == IntPtr::Zero)
				return;

			ImGui::PushID(ptr_id.ToPointer());
		}
		static void PushID(int int_id)
		{
			ImGui::PushID(int_id);
		}
		static void PopID()
		{
			ImGui::PopID();
		}

		// Primitive Drawing
		[ObsoleteAttribute("This will be removed in version 1.3 of IV-SDK .NET. You should instead use the OnImGuiRendering event the Script class provides you.")]
		static bool BeginCanvas(Script^ caller, RectangleF clippingRect, [OutAttribute] ImGuiIV_DrawingContext% ctx)
		{
			if (caller == nullptr)
				return false;
			
			// Begin a new window which will be the canvas
			Begin(caller->ID.ToString(),
				eImGuiWindowFlags::NoDecoration
				| eImGuiWindowFlags::NoInputs
				| eImGuiWindowFlags::NoBringToFrontOnFocus
				| eImGuiWindowFlags::NoFocusOnAppearing
				| eImGuiWindowFlags::NoNavFocus
				| eImGuiWindowFlags::NoBackground, true);

			// Set window position and size
			SetWindowPos(Vector2::Zero);
			SetWindowSize(MainViewport.Size);

			// Get the draw list from this window
			ImDrawList* drawList = ImGui::GetWindowDrawList();

			// Set the draw list up
			drawList->PushTextureID(ImGui::GetIO().Fonts->TexID);

			// Set a clipping rectangle
			if (clippingRect == RectangleF::Empty)
				drawList->PushClipRectFullScreen();
			else
				drawList->PushClipRect(ImVec2(clippingRect.X, clippingRect.Y), ImVec2(clippingRect.Right, clippingRect.Bottom));

			ctx = ImGuiIV_DrawingContext(drawList);
			return true;

			//ImDrawList* drawList = (ImDrawList*)drawListPtr.ToPointer();

			//if (!drawList)
			//	return false;

			//// Add draw command to draw list if the buffer is 0
			//if (drawList->CmdBuffer.size() == 0)
			//	drawList->AddDrawCmd();

			//drawList->PushTextureID(ImGui::GetIO().Fonts->TexID);

			//if (clippingRect == RectangleF::Empty)
			//	drawList->PushClipRectFullScreen();
			//else
			//	drawList->PushClipRect(ImVec2(clippingRect.X, clippingRect.Y), ImVec2(clippingRect.Right, clippingRect.Bottom));

			//return true;
		}
		[ObsoleteAttribute("This will be removed in version 1.3 of IV-SDK .NET. You should instead use the OnImGuiRendering event the Script class provides you.")]
		static bool BeginCanvas(Script^ caller, [OutAttribute] ImGuiIV_DrawingContext% ctx)
		{
			return BeginCanvas(caller, RectangleF::Empty, ctx);
		}
		[ObsoleteAttribute("This will be removed in version 1.3 of IV-SDK .NET.")]
		static bool EndCanvas()
		{
			// Get the draw list from this window
			ImDrawList* drawList = ImGui::GetWindowDrawList();

			// Pop the texture id that was pushed with the begin function
			drawList->PopTextureID();

			// End the canvas window
			End();

			return true;

			//ImDrawList* drawList = (ImDrawList*)drawListPtr.ToPointer();

			//if (!drawList)
			//	return false;

			//drawList->PopTextureID();

			//return true;
		}

		// Window
		static bool Begin(String^ name, bool% open, eImGuiWindowFlags flags, bool cannotDisableMouse)
		{
			if (String::IsNullOrWhiteSpace(name))
				return false;

			msclr::interop::marshal_context ctx;

			bool pOpen = open;

			ImGuiWindowClass wClass;
			wClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingSplit;
			ImGui::SetNextWindowClass(&wClass);

			bool result = ImGui::Begin(ctx.marshal_as<const char*>(name), &pOpen, (ImGuiWindowFlags)flags);

			open = pOpen;

			// Increase active windows count if Begin function returned true
			if (result)
			{
				// Increase count
				if (!cannotDisableMouse)
					ActiveWindows++;
			}

			return result;
		}
		static bool Begin(String^ name, bool% open, eImGuiWindowFlags flags)
		{
			return Begin(name, open, flags, false);
		}
		static bool Begin(String^ name, eImGuiWindowFlags flags, bool cannotDisableMouse)
		{
			if (String::IsNullOrWhiteSpace(name))
				return false;

			msclr::interop::marshal_context ctx;

			ImGuiWindowClass wClass;
			wClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingSplit;
			ImGui::SetNextWindowClass(&wClass);

			bool result = ImGui::Begin(ctx.marshal_as<const char*>(name), NULL, (ImGuiWindowFlags)flags);

			// Increase active windows count if Begin function returned true
			if (result)
			{
				// Increase count
				if (!cannotDisableMouse)
					ActiveWindows++;
			}

			return result;
		}
		static bool Begin(String^ name)
		{
			if (String::IsNullOrWhiteSpace(name))
				return false;

			msclr::interop::marshal_context ctx;

			ImGuiWindowClass wClass;
			wClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingSplit;
			ImGui::SetNextWindowClass(&wClass);
			
			bool result = ImGui::Begin(ctx.marshal_as<const char*>(name));

			// Increase active windows count if Begin function returned true
			if (result)
			{
				// Increase count
				ActiveWindows++;
			}

			return result;
		}
		static void End()
		{
			ImGui::End();
		}

		static bool BeginChild(String^ id, Vector2 size, bool border, eImGuiWindowFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			ImGuiWindowClass wClass;
			wClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingSplit;
			ImGui::SetNextWindowClass(&wClass);

			msclr::interop::marshal_context ctx;
			return ImGui::BeginChild(ctx.marshal_as<const char*>(id), Vector2ToImVec2(size), border, (ImGuiWindowFlags)flags);
		}
		static bool BeginChild(String^ id, Vector2 size, bool border)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			ImGuiWindowClass wClass;
			wClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingSplit;
			ImGui::SetNextWindowClass(&wClass);

			msclr::interop::marshal_context ctx;
			return ImGui::BeginChild(ctx.marshal_as<const char*>(id), Vector2ToImVec2(size), border);
		}
		static bool BeginChild(String^ id, Vector2 size)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			ImGuiWindowClass wClass;
			wClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingSplit;
			ImGui::SetNextWindowClass(&wClass);

			msclr::interop::marshal_context ctx;
			return ImGui::BeginChild(ctx.marshal_as<const char*>(id), Vector2ToImVec2(size));
		}
		static bool BeginChild(String^ id)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			ImGuiWindowClass wClass;
			wClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingSplit;
			ImGui::SetNextWindowClass(&wClass);

			msclr::interop::marshal_context ctx;
			return ImGui::BeginChild(ctx.marshal_as<const char*>(id));
		}
		static void EndChild()
		{
			ImGui::EndChild();
		}

		static void SetNextWindowBgAlpha(float alpha)
		{
			ImGui::SetNextWindowBgAlpha(alpha);
		}

		static IntPtr FindWindowById(ImGuiID id)
		{
			return IntPtr(ImGui::FindWindowByID(id));
		}
		static IntPtr FindWindowByName(String^ name)
		{
			if (String::IsNullOrWhiteSpace(name))
				return IntPtr::Zero;

			msclr::interop::marshal_context ctx;
			return IntPtr(ImGui::FindWindowByName(ctx.marshal_as<const char*>(name)));
		}
		static IntPtr GetWindowDrawList()
		{
			return IntPtr(ImGui::GetWindowDrawList());
		}

		static float GetWindowWidth()
		{
			return ImGui::GetWindowWidth();
		}
		static float GetWindowHeight()
		{
			return ImGui::GetWindowHeight();
		}

		static Vector2 GetWindowPos()
		{
			return ImVec2ToVector2(ImGui::GetWindowPos());
		}
		static Vector2 GetWindowSize()
		{
			return ImVec2ToVector2(ImGui::GetWindowSize());
		}

		static void SetNextWindowPos(Vector2 pos, eImGuiCond cond, Vector2 pivot)
		{
			ImGui::SetNextWindowPos(Vector2ToImVec2(pos), (ImGuiCond)cond, Vector2ToImVec2(pivot));
		}
		static void SetNextWindowPos(Vector2 pos, eImGuiCond cond)
		{
			ImGui::SetNextWindowPos(Vector2ToImVec2(pos), (ImGuiCond)cond);
		}
		static void SetNextWindowPos(Vector2 pos)
		{
			SetNextWindowPos(pos, eImGuiCond::None);
		}
		static void SetNextWindowSize(Vector2 size, eImGuiCond cond)
		{
			ImGui::SetNextWindowSize(Vector2ToImVec2(size), (ImGuiCond)cond);
		}
		static void SetNextWindowSize(Vector2 size)
		{
			SetNextWindowSize(size, eImGuiCond::None);
		}

		static void SetWindowPos(String^ name, Vector2 pos, eImGuiCond cond)
		{
			if (String::IsNullOrWhiteSpace(name))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::SetWindowPos(ctx.marshal_as<const char*>(name), Vector2ToImVec2(pos), (ImGuiCond)cond);
		}
		static void SetWindowPos(String^ name, Vector2 pos)
		{
			SetWindowPos(name, pos, eImGuiCond::None);
		}
		static void SetWindowPos(IntPtr window, Vector2 pos, eImGuiCond cond)
		{
			if (window == IntPtr::Zero)
				return;

			ImGui::SetWindowPos((ImGuiWindow*)window.ToPointer(), Vector2ToImVec2(pos), (ImGuiCond)cond);
		}
		static void SetWindowPos(IntPtr window, Vector2 pos)
		{
			SetWindowPos(window, pos, eImGuiCond::None);
		}
		static void SetWindowPos(Vector2 pos, eImGuiCond cond)
		{
			ImGui::SetWindowPos(Vector2ToImVec2(pos), (ImGuiCond)cond);
		}
		static void SetWindowPos(Vector2 pos)
		{
			SetWindowPos(pos, eImGuiCond::None);
		}

		static void SetWindowSize(String^ name, Vector2 size, eImGuiCond cond)
		{
			if (String::IsNullOrWhiteSpace(name))
				return;
			
			msclr::interop::marshal_context ctx;
			ImGui::SetWindowSize(ctx.marshal_as<const char*>(name), Vector2ToImVec2(size), (ImGuiCond)cond);
		}
		static void SetWindowSize(String^ name, Vector2 size)
		{
			SetWindowSize(name, size, eImGuiCond::None);
		}
		static void SetWindowSize(IntPtr window, Vector2 size, eImGuiCond cond)
		{
			if (window == IntPtr::Zero)
				return;

			ImGui::SetWindowSize((ImGuiWindow*)window.ToPointer(), Vector2ToImVec2(size), (ImGuiCond)cond);
		}
		static void SetWindowSize(IntPtr window, Vector2 size)
		{
			SetWindowSize(window, size, eImGuiCond::None);
		}
		static void SetWindowSize(Vector2 size, eImGuiCond cond)
		{
			ImGui::SetWindowSize(Vector2ToImVec2(size), (ImGuiCond)cond);
		}
		static void SetWindowSize(Vector2 size)
		{
			SetWindowSize(size, eImGuiCond::None);
		}

		static void BeginDisabled(bool disabled)
		{
			ImGui::BeginDisabled(disabled);
		}
		static void BeginDisabled()
		{
			BeginDisabled(true);
		}
		static void EndDisabled()
		{
			ImGui::EndDisabled();
		}

		static void GcCompactTransientWindowBuffers(IntPtr windowPtr)
		{
			if (windowPtr == IntPtr::Zero)
				return;

			ImGui::GcCompactTransientWindowBuffers((ImGuiWindow*)windowPtr.ToPointer());
		}

		// Window->Focus
		static void SetWindowFocus(String^ name)
		{
			if (String::IsNullOrWhiteSpace(name))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::SetWindowFocus(ctx.marshal_as<const char*>(name));
		}
		static void SetWindowFocus()
		{
			ImGui::SetWindowFocus();
		}
		static void SetNextWindowFocus()
		{
			ImGui::SetNextWindowFocus();
		}
		static void SetKeyboardFocusHere(int offset)
		{
			ImGui::SetKeyboardFocusHere(offset);
		}
		static void SetKeyboardFocusHere()
		{
			SetKeyboardFocusHere(0);
		}

		static void FocusWindow(IntPtr window)
		{
			if (window == IntPtr::Zero)
				return;

			ImGui::FocusWindow((ImGuiWindow*)window.ToPointer());
		}
		static void BringWindowToFocusFront(IntPtr window)
		{
			if (window == IntPtr::Zero)
				return;

			ImGui::BringWindowToFocusFront((ImGuiWindow*)window.ToPointer());
		}

		static bool IsAnyItemFocused()
		{
			return ImGui::IsAnyItemFocused();
		}
		static bool IsWindowFocused()
		{
			return ImGui::IsWindowFocused();
		}

		static ImGuiID GetFocusID()
		{
			return ImGui::GetFocusID();
		}
		static void SetFocusID(ImGuiID id, IntPtr window)
		{
			if (window == IntPtr::Zero)
				return;

			ImGui::SetFocusID(id, (ImGuiWindow*)window.ToPointer());
		}
		
		// Style
		static void PushStyleVar(eImGuiStyleVar idx, Vector2 value)
		{
			ImGui::PushStyleVar((ImGuiStyleVar)idx, Vector2ToImVec2(value));
		}
		static void PushStyleVar(eImGuiStyleVar idx, float value)
		{
			ImGui::PushStyleVar((ImGuiStyleVar)idx, value);
		}

		static void PushStyleColor(eImGuiCol idx, Vector4 color)
		{
			ImGui::PushStyleColor((ImGuiCol)idx, Vector4ToImVec4(color));
		}
		static void PushStyleColor(eImGuiCol idx, Color color)
		{
			ImGui::PushStyleColor((ImGuiCol)idx, ColorToImU32(color));
		}

		static void PopStyleVar(int count)
		{
			ImGui::PopStyleVar(count);
		}
		static void PopStyleVar()
		{
			PopStyleVar(1);
		}
		static void PopStyleColor(int count)
		{
			ImGui::PopStyleColor(count);
		}
		static void PopStyleColor()
		{
			PopStyleColor(1);
		}

		// Input
		static String^ GetKeyName(eImGuiKey key)
		{
			return gcnew String(ImGui::GetKeyName((ImGuiKey)(int)key));
		}
		static int GetKeyPressedAmount(eImGuiKey key, float repeatDelay, float repeatRate)
		{
			return ImGui::GetKeyPressedAmount((ImGuiKey)(int)key, repeatDelay, repeatRate);
		}

		static bool IsKeyDown(eImGuiKey key, ImGuiID ownerId)
		{
			return ImGui::IsKeyDown((ImGuiKey)(int)key, ownerId);
		}
		static bool IsKeyDown(eImGuiKey key)
		{
			return ImGui::IsKeyDown((ImGuiKey)(int)key);
		}
		static bool IsKeyPressed(eImGuiKey key, bool repeat)
		{
			return ImGui::IsKeyPressed((ImGuiKey)(int)key, repeat);
		}
		static bool IsKeyPressed(eImGuiKey key, ImGuiID ownerId, eImGuiInputFlags flags)
		{
			return ImGui::IsKeyPressed((ImGuiKey)(int)key, ownerId, (ImGuiInputFlags)(int)flags);
		}
		static bool IsKeyReleased(eImGuiKey key)
		{
			return ImGui::IsKeyReleased((ImGuiKey)(int)key);
		}
		static bool IsKeyReleased(eImGuiKey key, ImGuiID ownerId)
		{
			return ImGui::IsKeyReleased((ImGuiKey)(int)key, ownerId);
		}

		static bool IsMouseDown(eImGuiMouseButton button)
		{
			return ImGui::IsMouseDown((ImGuiMouseButton)(int)button);
		}
		static bool IsMouseDown(eImGuiMouseButton button, ImGuiID ownerId)
		{
			return ImGui::IsMouseDown((ImGuiMouseButton)(int)button, ownerId);
		}
		static bool IsMouseClicked(eImGuiMouseButton button)
		{
			return ImGui::IsMouseClicked((ImGuiMouseButton)(int)button);
		}
		static bool IsMouseClicked(eImGuiMouseButton button, ImGuiID ownerId)
		{
			return ImGui::IsMouseClicked((ImGuiMouseButton)(int)button, ownerId);
		}
		static bool IsMouseReleased(eImGuiMouseButton button)
		{
			return ImGui::IsMouseReleased((ImGuiMouseButton)(int)button);
		}
		static bool IsMouseReleased(eImGuiMouseButton button, ImGuiID ownerId)
		{
			return ImGui::IsMouseReleased((ImGuiMouseButton)(int)button, ownerId);
		}
		static bool IsMouseDoubleClicked(eImGuiMouseButton button)
		{
			return ImGui::IsMouseDoubleClicked((ImGuiMouseButton)(int)button);
		}
		static int GetMouseClickedCount(eImGuiMouseButton button)
		{
			return ImGui::GetMouseClickedCount((ImGuiMouseButton)(int)button);
		}

		static bool IsMouseHoveringRect(RectangleF rect, bool clip)
		{
			if (rect == RectangleF::Empty)
				return false;

			return ImGui::IsMouseHoveringRect(ImVec2(rect.X, rect.Y), ImVec2(rect.Right, rect.Bottom), clip);
		}
		static bool IsMouseDragPastThreshold(eImGuiMouseButton button, float lockThreshold)
		{
			return ImGui::IsMouseDragPastThreshold((ImGuiMouseButton)(int)button, lockThreshold);
		}
		static bool IsMouseDragging(eImGuiMouseButton button, float lockThreshold)
		{
			return ImGui::IsMouseDragging((ImGuiMouseButton)(int)button, lockThreshold);
		}

		static Vector2 GetMousePos()
		{
			return ImVec2ToVector2(ImGui::GetMousePos());
		}
		static Vector2 GetMouseDragDelta(ImGuiMouseButton button, float lockThreshold)
		{
			return ImVec2ToVector2(ImGui::GetMouseDragDelta((ImGuiMouseButton)(int)button, lockThreshold));
		}
		static void ResetMouseDragDelta(eImGuiMouseButton button)
		{
			ImGui::ResetMouseDragDelta((ImGuiMouseButton)(int)button);
		}

		static eImGuiMouseCursor GetMouseCursor()
		{
			return (eImGuiMouseCursor)(int)ImGui::GetMouseCursor();
		}
		static void SetMouseCursor(eImGuiMouseCursor type)
		{
			ImGui::SetMouseCursor((ImGuiMouseCursor)(int)type);
		}

		static Vector2 GetCursorScreenPos()
		{
			return ImVec2ToVector2(ImGui::GetCursorScreenPos());
		}
		static void SetCursorScreenPos(Vector2 pos)
		{
			ImGui::SetCursorScreenPos(Vector2ToImVec2(pos));
		}
		static Vector2 GetCursorPos()
		{
			return ImVec2ToVector2(ImGui::GetCursorPos());
		}
		static float GetCursorPosX()
		{
			return ImGui::GetCursorPosX();
		}
		static float GetCursorPosY()
		{
			return ImGui::GetCursorPosY();
		}
		static void SetCursorPos(Vector2 localPos)
		{
			ImGui::SetCursorPos(Vector2ToImVec2(localPos));
		}
		static void SetCursorPosX(float x)
		{
			ImGui::SetCursorPosX(x);
		}
		static void SetCursorPosY(float y)
		{
			ImGui::SetCursorPosY(y);
		}
		static Vector2 GetCursorStartPos()
		{
			return ImVec2ToVector2(ImGui::GetCursorStartPos());
		}

		static void SetItemDefaultFocus()
		{
			ImGui::SetItemDefaultFocus();
		}

		static float GetKeyAnalogValue(eImGuiKey key)
		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			return io.KeysData[(int)key].AnalogValue;
		}

		// Font
		static void PushFont(IntPtr fontPtr)
		{
			if (fontPtr == IntPtr::Zero)
				return;

			ImGui::PushFont((ImFont*)fontPtr.ToPointer());
		}
		static void PopFont()
		{
			ImGui::PopFont();
		}

		static IntPtr GetFont()
		{
			return IntPtr(ImGui::GetFont());
		}
		static float GetFontSize()
		{
			return ImGui::GetFontSize();
		}
		static Vector2 GetFontTexUvWhitePixel()
		{
			return ImVec2ToVector2(ImGui::GetFontTexUvWhitePixel());
		}

		static void SetWindowFontScale(float scale)
		{
			if (scale > 0.0F)
				return;

			ImGui::SetWindowFontScale(scale);
		}

		//-----------------------------------------------------------------------------
		// [SECTION] LAYOUT
		//-----------------------------------------------------------------------------
		static void ItemSize(Vector2 size, float textBaselineY)
		{
			ImGui::ItemSize(Vector2ToImVec2(size), textBaselineY);
		}

		static void SameLine(float offsetFromStartX, float spacing)
		{
			ImGui::SameLine(offsetFromStartX, spacing);
		}
		static void SameLine()
		{
			SameLine(0.0F, -1.0F);
		}

		static void Indent(float indentW)
		{
			ImGui::Indent(indentW);
		}
		static void Unindent(float indentW)
		{
			ImGui::Unindent(indentW);
		}

		static void SetNextItemWidth(float width)
		{
			ImGui::SetNextItemWidth(width);
		}

		static void PushItemWidth(float width)
		{
			ImGui::PushItemWidth(width);
		}
		static void PushMultiItemsWidths(int components, float widthFull)
		{
			ImGui::PushMultiItemsWidths(components, widthFull);
		}
		static void PopItemWidth()
		{
			ImGui::PopItemWidth();
		}

		static float CalcItemWidth()
		{
			return ImGui::CalcItemWidth();
		}
		static Vector2 CalcItemSize(Vector2 size, float defaultW, float defaultH)
		{
			return ImVec2ToVector2(ImGui::CalcItemSize(Vector2ToImVec2(size), defaultW, defaultH));
		}

		static float GetTextLineHeight()
		{
			return ImGui::GetTextLineHeight();
		}
		static float GetTextLineHeightWithSpacing()
		{
			return ImGui::GetTextLineHeightWithSpacing();
		}
		static float GetFrameHeight()
		{
			return ImGui::GetFrameHeight();
		}
		static float GetFrameHeightWithSpacing()
		{
			return ImGui::GetFrameHeightWithSpacing();
		}

		static Vector2 GetContentRegionMax()
		{
			return ImVec2ToVector2(ImGui::GetContentRegionMax());
		}
		static Vector2 GetContentRegionAvail()
		{
			return ImVec2ToVector2(ImGui::GetContentRegionAvail());
		}
		static Vector2 GetWindowContentRegionMin()
		{
			return ImVec2ToVector2(ImGui::GetWindowContentRegionMin());
		}
		static Vector2 GetWindowContentRegionMax()
		{
			return ImVec2ToVector2(ImGui::GetWindowContentRegionMax());
		}

		static Vector2 GetItemRectMin()
		{
			return ImVec2ToVector2(ImGui::GetItemRectMin());
		}
		static Vector2 GetItemRectMax()
		{
			return ImVec2ToVector2(ImGui::GetItemRectMax());
		}
		static Vector2 GetItemRectSize()
		{
			return ImVec2ToVector2(ImGui::GetItemRectSize());
		}

		static void BeginGroup()
		{
			ImGui::BeginGroup();
		}
		static void EndGroup()
		{
			ImGui::EndGroup();
		}

		//-----------------------------------------------------------------------------
		// [SECTION] SCROLLING
		//-----------------------------------------------------------------------------
		static void ScrollToItem(eImGuiScrollFlags flags)
		{
			ImGui::ScrollToItem((ImGuiScrollFlags)flags);
		}

		static float GetScrollX()
		{
			return ImGui::GetScrollX();
		}
		static float GetScrollY()
		{
			return ImGui::GetScrollY();
		}
		static float GetScrollMaxX()
		{
			return ImGui::GetScrollMaxX();
		}
		static float GetScrollMaxY()
		{
			return ImGui::GetScrollMaxY();
		}
		static void SetScrollX(float x)
		{
			ImGui::SetScrollX(x);
		}
		static void SetScrollY(float y)
		{
			ImGui::SetScrollY(y);
		}

		static void SetScrollFromPosX(float localX, float centerXRatio)
		{
			ImGui::SetScrollFromPosX(localX, centerXRatio);
		}
		static void SetScrollFromPosY(float localY, float centerYRatio)
		{
			ImGui::SetScrollFromPosY(localY, centerYRatio);
		}

		static void SetScrollHereX(float centerXRatio)
		{
			ImGui::SetScrollHereX(centerXRatio);
		}
		static void SetScrollHereY(float centerYRatio)
		{
			ImGui::SetScrollHereY(centerYRatio);
		}

		//-----------------------------------------------------------------------------
		// [SECTION] TOOLTIPS
		//-----------------------------------------------------------------------------
		static bool BeginTooltip()
		{
			return ImGui::BeginTooltip();
		}
		static bool BeginItemTooltip()
		{
			return ImGui::BeginItemTooltip();
		}
		static bool BeginTooltipEx(eImGuiTooltipFlags tooltipFlags, eImGuiWindowFlags extraWindowFlags)
		{
			return ImGui::BeginTooltipEx((ImGuiTooltipFlags)tooltipFlags, (ImGuiWindowFlags)extraWindowFlags);
		}
		static void EndTooltip()
		{
			ImGui::EndTooltip();
		}

		static void SetTooltip(String^ text, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(text))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::SetTooltip(ctx.marshal_as<const char*>(String::Format(text, args)));
		}

		static void SetItemTooltip(String^ text, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(text))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::SetItemTooltip(ctx.marshal_as<const char*>(String::Format(text, args)));
		}

		static bool ImagePreviewToolTip(IntPtr txtPtr, Vector2 imageSize, Vector2 cursorScreenPos, float regionSize, float zoom, Color tintColor, Color borderColor)
		{
			if (txtPtr == IntPtr::Zero)
				return false;

			if (BeginItemTooltip())
			{
				ImVec2 mousePos = ImGui::GetIO().MousePos;

				float region_x = mousePos.x - cursorScreenPos.X - regionSize * 0.5f;
				float region_y = mousePos.y - cursorScreenPos.Y - regionSize * 0.5f;

				if (region_x < 0.0f)
					region_x = 0.0f;
				else if (region_x > imageSize.X - regionSize)
					region_x = imageSize.X - regionSize;

				if (region_y < 0.0f)
					region_y = 0.0f;
				else if (region_y > imageSize.Y - regionSize)
					region_y = imageSize.Y - regionSize;

				Vector2 uv0 = Vector2((region_x) / imageSize.X, (region_y) / imageSize.Y);
				Vector2 uv1 = Vector2((region_x + regionSize) / imageSize.X, (region_y + regionSize) / imageSize.Y);
				ImGuiIV::Image(txtPtr, Vector2(regionSize * zoom, regionSize * zoom), uv0, uv1, tintColor, borderColor);

				EndTooltip();
				return true;
			}

			return false;
		}
		static bool ImagePreviewToolTip(IntPtr txtPtr, Vector2 imageSize, Vector2 cursorScreenPos, float regionSize, float zoom)
		{
			return ImagePreviewToolTip(txtPtr, imageSize, cursorScreenPos, regionSize, zoom, Color::White, Color::Transparent);
		}

		//-----------------------------------------------------------------------------
		// [SECTION] POPUPS
		//-----------------------------------------------------------------------------
		static bool IsPopupOpen(ImGuiID id, eImGuiPopupFlags flags)
		{
			return ImGui::IsPopupOpen(id, (ImGuiPopupFlags)flags);
		}
		static bool IsPopupOpen(String^ id, eImGuiPopupFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::IsPopupOpen(ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}

		static void OpenPopup(ImGuiID id, eImGuiPopupFlags flags)
		{
			ImGui::OpenPopup(id, (ImGuiPopupFlags)flags);
		}
		static void OpenPopup(String^ id, eImGuiPopupFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::OpenPopup(ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}
		static void OpenPopup(ImGuiID id)
		{
			ImGui::OpenPopup(id);
		}
		static void OpenPopup(String^ id)
		{
			if(String::IsNullOrWhiteSpace(id))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::OpenPopup(ctx.marshal_as<const char*>(id));
		}

		static void OpenPopupEx(ImGuiID id, eImGuiPopupFlags flags)
		{
			return ImGui::OpenPopupEx(id, (ImGuiPopupFlags)flags);
		}

		static void ClosePopupsExceptModals()
		{
			ImGui::ClosePopupsExceptModals();
		}
		static void ClosePopupToLevel(int remaining, bool restoreFocusToWindowUnderPopup)
		{
			ImGui::ClosePopupToLevel(remaining, restoreFocusToWindowUnderPopup);
		}
		static void CloseCurrentPopup()
		{
			ImGui::CloseCurrentPopup();
		}

		static bool BeginPopupEx(ImGuiID id, eImGuiWindowFlags flags)
		{
			return ImGui::BeginPopupEx(id, (ImGuiWindowFlags)flags);
		}
		static bool BeginPopup(String^ id, eImGuiWindowFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopup(ctx.marshal_as<const char*>(id), (ImGuiWindowFlags)flags);
		}
		static bool BeginPopupModal(String^ id, bool% open, eImGuiWindowFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;

			bool pOpen = open;

			bool result = ImGui::BeginPopupModal(ctx.marshal_as<const char*>(id), &pOpen, (ImGuiWindowFlags)flags);

			open = pOpen;
			return result;
		}
		static bool BeginPopupModal(String^ id, eImGuiWindowFlags flags)
		{
			if(String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopupModal(ctx.marshal_as<const char*>(id), NULL, (ImGuiWindowFlags)flags);
		}
		static bool BeginPopupModal(String^ id, bool% open)
		{
			if(String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;

			bool pOpen = open;

			bool result = ImGui::BeginPopupModal(ctx.marshal_as<const char*>(id), &pOpen);

			open = pOpen;
			return result;
		}
		static bool BeginPopupModal(String^ id)
		{
			if(String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopupModal(ctx.marshal_as<const char*>(id));
		}
		static void EndPopup()
		{
			ImGui::EndPopup();
		}

		static void OpenPopupOnItemClick(String^ id, eImGuiPopupFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::OpenPopupOnItemClick(ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}
		static bool BeginPopupContextItem(String^ id, eImGuiPopupFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopupContextItem(ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}
		static bool BeginPopupContextWindow(String^ id, eImGuiPopupFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopupContextWindow(ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}
		static bool BeginPopupContextVoid(String^ id, eImGuiPopupFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopupContextVoid(ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}

		static void CreateSimplePopupDialog(String^ id, String^ description, bool centerInMiddleOfScreen, bool showButtonOne, bool showButtonTwo, String^ buttonOneName, String^ buttonTwoName, Action^ buttonOneAction, Action^ buttonTwoAction)
		{
			if (String::IsNullOrWhiteSpace(id))
				return;
			if (String::IsNullOrWhiteSpace(description))
				return;

			if (BeginPopupModal(id, eImGuiWindowFlags::AlwaysAutoResize))
			{
				Text(description);
				Separator();

				// Button 1
				if (showButtonOne)
				{
					if (Button(buttonOneName, Vector2(120.0F, 0.0F)))
					{
						if (buttonOneAction)
							buttonOneAction();
						CloseCurrentPopup();
					}
				}

				SameLine();

				// Button 2
				if (showButtonTwo)
				{
					if (Button(buttonTwoName, Vector2(120.0F, 0.0F)))
					{
						if (buttonTwoAction)
							buttonTwoAction();
						CloseCurrentPopup();
					}
				}

				EndPopup();
			}
		}

		static RectangleF GetPopupAllowedExtentRect(IntPtr window)
		{
			if (window == IntPtr::Zero)
				return RectangleF::Empty;

			return ImRectToRectangleF(ImGui::GetPopupAllowedExtentRect((ImGuiWindow*)window.ToPointer()));
		}
		static Vector2 FindBestWindowPosForPopup(IntPtr window)
		{
			if (window == IntPtr::Zero)
				return Vector2::Zero;

			return ImVec2ToVector2(ImGui::FindBestWindowPosForPopup((ImGuiWindow*)window.ToPointer()));
		}

		//-----------------------------------------------------------------------------
		// [SECTION] DRAG AND DROP
		//-----------------------------------------------------------------------------
		static bool IsDragDropActive()
		{
			return ImGui::IsDragDropActive();
		}
		static void ClearDragDrop()
		{
			ImGui::ClearDragDrop();
		}

		static bool BeginDragDropSource(eImGuiDragDropFlags flags)
		{
			return ImGui::BeginDragDropSource((ImGuiDragDropFlags)flags);
		}
		static void EndDragDropSource()
		{
			ImGui::EndDragDropSource();
		}

		static bool SetDragDropPayload(String^ type, IntPtr data, uint32_t dataSize, eImGuiCond cond)
		{
			if (String::IsNullOrWhiteSpace(type))
				return false;
			if (data == IntPtr::Zero)
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::SetDragDropPayload(ctx.marshal_as<const char*>(type), data.ToPointer(), dataSize, (ImGuiCond)cond);
		}

		static bool BeginDragDropTargetCustom(RectangleF bb, ImGuiID id)
		{
			return ImGui::BeginDragDropTargetCustom(RectangleFToImRect(bb), id);
		}
		static bool BeginDragDropTarget()
		{
			return ImGui::BeginDragDropTarget();
		}

		static bool IsDragDropPayloadBeingAccepted()
		{
			return ImGui::IsDragDropPayloadBeingAccepted();
		}

		// TODO: These should return a ImGuiPayload*
		static IntPtr AcceptDragDropPayload(String^ type, eImGuiDragDropFlags flags)
		{
			if (String::IsNullOrWhiteSpace(type))
				return IntPtr::Zero;

			msclr::interop::marshal_context ctx;
			return IntPtr((void*)ImGui::AcceptDragDropPayload(ctx.marshal_as<const char*>(type), (ImGuiDragDropFlags)flags));
		}
		static IntPtr GetDragDropPayload()
		{
			return IntPtr((void*)ImGui::GetDragDropPayload());
		}

		static void RenderDragDropTargetRect(RectangleF bb, RectangleF itemClipRect)
		{
			ImGui::RenderDragDropTargetRect(RectangleFToImRect(bb), RectangleFToImRect(itemClipRect));
		}
		static void EndDragDropTarget()
		{
			ImGui::EndDragDropTarget();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: Text, etc.
		//-------------------------------------------------------------------------
		static void Text(String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::Text(ctx.marshal_as<const char*>(String::Format(str, args)));
		}
		static void TextDisabled(String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::TextDisabled(ctx.marshal_as<const char*>(String::Format(str, args)));
		}
		static void TextWrapped(String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;
			
			msclr::interop::marshal_context ctx;
			ImGui::TextWrapped(ctx.marshal_as<const char*>(String::Format(str, args)));
		}
		static void TextColored(Color color, String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::TextColored(ColorToImVec4(color, true), ctx.marshal_as<const char*>(String::Format(str, args)));
		}

		static void BulletText(String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::BulletText(ctx.marshal_as<const char*>(String::Format(str, args)));
		}

		//-----------------------------------------------------------------------------
		// [SECTION] Helpers
		//-----------------------------------------------------------------------------
		static void HelpMarker(String^ text)
		{
			if (String::IsNullOrWhiteSpace(text))
				return;

			ImGui::TextDisabled("(?)");
			if (ImGui::BeginItemTooltip())
			{
				msclr::interop::marshal_context ctx;
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(ctx.marshal_as<const char*>(text));
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: Main
		//-------------------------------------------------------------------------
		static bool ButtonEx(String^ name, Vector2 size, eImGuiButtonFlags flags)
		{
			if (String::IsNullOrWhiteSpace(name))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::ButtonEx(
				ctx.marshal_as<const char*>(name),
				Vector2ToImVec2(size),
				(ImGuiButtonFlags)flags);
		}
		static bool Button(String^ name, Vector2 size)
		{
			return ButtonEx(
				name,
				size,
				eImGuiButtonFlags::None);
		}
		static bool Button(String^ name)
		{
			return ButtonEx(
				name,
				Vector2::Zero,
				eImGuiButtonFlags::None);
		}

		static bool SmallButton(String^ name)
		{
			if (String::IsNullOrWhiteSpace(name))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::SmallButton(ctx.marshal_as<const char*>(name));
		}

		static bool InvisibleButton(String^ name, Vector2 size, eImGuiButtonFlags flags)
		{
			if (String::IsNullOrWhiteSpace(name))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::InvisibleButton(
				ctx.marshal_as<const char*>(name),
				Vector2ToImVec2(size),
				(ImGuiButtonFlags)flags);
		}

		static bool ArrowButtonEx(String^ id, eImGuiDir dir, Vector2 size, eImGuiButtonFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::ArrowButtonEx(
				ctx.marshal_as<const char*>(id),
				(ImGuiDir)dir,
				Vector2ToImVec2(size),
				(ImGuiButtonFlags)flags);
		}
		static bool ArrowButton(String^ id, eImGuiDir dir)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::ArrowButton(ctx.marshal_as<const char*>(id), (ImGuiDir)dir);
		}

		static bool CloseButton(ImGuiID id, Vector2 pos)
		{
			return ImGui::CloseButton(id, Vector2ToImVec2(pos));
		}
		static bool CollapseButton(ImGuiID id, Vector2 pos)
		{
			return ImGui::CollapseButton(id, Vector2ToImVec2(pos), ImGui::GetWindowDockNode());
		}

		static void Scrollbar(eImGuiAxis axis)
		{
			ImGui::Scrollbar((ImGuiAxis)axis);
		}

		static void Image(IntPtr textureId, Vector2 size, Vector2 uv0, Vector2 uv1, Color tintColor, Color borderColor)
		{
			if (textureId == IntPtr::Zero)
				return;

			ImGui::Image(
				(ImTextureID)textureId.ToPointer(),
				Vector2ToImVec2(size),
				Vector2ToImVec2(uv0),
				Vector2ToImVec2(uv1),
				ColorToImVec4(tintColor, true),
				ColorToImVec4(borderColor, true));
		}
		static void Image(IntPtr textureId, Vector2 size)
		{
			Image(
				textureId,
				size,
				Vector2(0.0F, 0.0F),
				Vector2(1.0F, 1.0F),
				Color::White,
				Color::FromArgb(0, 0, 0, 0));
		}

		static bool ImageButtonEx(ImGuiID id, IntPtr textureId, Vector2 size, Vector2 uv0, Vector2 uv1, Color bgColor, Color tintColor, eImGuiButtonFlags flags)
		{
			if (textureId == IntPtr::Zero)
				return false;

			return ImGui::ImageButtonEx(
				id,
				(ImTextureID)textureId.ToPointer(),
				Vector2ToImVec2(size),
				Vector2ToImVec2(uv0),
				Vector2ToImVec2(uv1),
				ColorToImVec4(bgColor, true),
				ColorToImVec4(tintColor, true),
				(ImGuiButtonFlags)flags);
		}
		static bool ImageButton(String^ id, IntPtr textureId, Vector2 size, Vector2 uv0, Vector2 uv1, Color bgColor, Color tintColor)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;
			if (textureId == IntPtr::Zero)
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::ImageButton(
				ctx.marshal_as<const char*>(id),
				(ImTextureID)textureId.ToPointer(),
				Vector2ToImVec2(size),
				Vector2ToImVec2(uv0),
				Vector2ToImVec2(uv1),
				ColorToImVec4(bgColor, true),
				ColorToImVec4(tintColor, true));
		}

		static bool CheckBox(String^ text, bool% value)
		{
			if (String::IsNullOrWhiteSpace(text))
				return false;

			msclr::interop::marshal_context ctx;

			bool v = value;

			bool result = ImGui::Checkbox(ctx.marshal_as<const char*>(text), &v);

			value = v;
			return result;
		}
		static bool RadioButton(String^ text, int% selectedButton, int buttonIndex)
		{
			if (String::IsNullOrWhiteSpace(text))
				return false;

			msclr::interop::marshal_context ctx;

			int sb = selectedButton;
			bool result = ImGui::RadioButton(ctx.marshal_as<const char*>(text), &sb, buttonIndex);
			selectedButton = sb;

			return result;
		}
		static bool RadioButton(String^ text, bool active)
		{
			if (String::IsNullOrWhiteSpace(text))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::RadioButton(ctx.marshal_as<const char*>(text), active);
		}

		static void IndeterminateProgressBar(Vector2 size)
		{
			ImGuiContext& g = *GImGui;
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems)
				return;

			ImGuiStyle& style = g.Style;
			ImVec2 size2 = ImGui::CalcItemSize(Vector2ToImVec2(size), CalcItemWidth(), g.FontSize + style.FramePadding.y * 2.0f);
			ImVec2 pos = window->DC.CursorPos;
			ImRect bb(pos.x, pos.y, pos.x + size2.x, pos.y + size2.y);
			ImGui::ItemSize(size2);
			if (!ImGui::ItemAdd(bb, 0))
				return;

			const float speed = g.FontSize * 0.05f;
			const float phase = ImFmod((float)g.Time * speed, 1.0f);
			const float width_normalized = 0.2f;
			float t0 = phase * (1.0f + width_normalized) - width_normalized;
			float t1 = t0 + width_normalized;

			ImGui::RenderFrame(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);
			bb.Expand(ImVec2(-style.FrameBorderSize, -style.FrameBorderSize));
			ImGui::RenderRectFilledRangeH(window->DrawList, bb, ImGui::GetColorU32(ImGuiCol_PlotHistogram), t0, t1, style.FrameRounding);
		}
		static void IndeterminateProgressBar()
		{
			IndeterminateProgressBar(Vector2(-FLT_MIN, 0.0F));
		}
		static void ProgressBar(float fraction, Vector2 size, String^ overlay)
		{
			msclr::interop::marshal_context ctx;
			ImGui::ProgressBar(fraction, Vector2ToImVec2(size), String::IsNullOrWhiteSpace(overlay) ? (const char*)0 : ctx.marshal_as<const char*>(overlay));
		}
		static void ProgressBar(float fraction)
		{
			ProgressBar(fraction, Vector2(-FLT_MIN, 0.0F), nullptr);
		}

		static void Bullet()
		{
			ImGui::Bullet();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: Low-level Layout helpers
		//-------------------------------------------------------------------------
		static void Spacing()
		{
			ImGui::Spacing();
		}
		static void Dummy(Vector2 size)
		{
			ImGui::Dummy(Vector2ToImVec2(size));
		}
		static void Dummy()
		{
			Dummy(Vector2::Zero);
		}
		static void NewLine()
		{
			ImGui::NewLine();
		}
		static void AlignTextToFramePadding()
		{
			ImGui::AlignTextToFramePadding();
		}

		static void SeparatorEx(eImGuiSeparatorFlags flags, float thickness)
		{
			ImGui::SeparatorEx((ImGuiSeparatorFlags)flags, thickness);
		}
		static void Separator()
		{
			ImGui::Separator();
		}
		static void SeparatorTextEx(ImGuiID id, String^ text, String^ textEnd, float extraW)
		{
			if (String::IsNullOrWhiteSpace(text))
				return;
			if (String::IsNullOrWhiteSpace(textEnd))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::SeparatorTextEx(id, ctx.marshal_as<const char*>(text), ctx.marshal_as<const char*>(textEnd), extraW);
		}
		static void SeparatorText(String^ text)
		{
			if (String::IsNullOrWhiteSpace(text))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::SeparatorText(ctx.marshal_as<const char*>(text));
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: ComboBox
		//-------------------------------------------------------------------------
		static bool Combo(String^ label, int% selectedIndex, array<String^>^ items)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			int index = selectedIndex;

			// Copy managed stuff over to unmanaged stuff
			std::vector<const char*> arr;
			arr.resize(items->Length);

			for (int i = 0; i < items->Length; i++)
				arr[i] = ctx.marshal_as<const char*>(items[i]);
			
			bool result = ImGui::Combo(ctx.marshal_as<const char*>(label), &index, arr.data(), items->Length);

			selectedIndex = index;
			return result;
		}

		static bool BeginCombo(String^ text, String^ previewValue, eImGuiComboFlags flags)
		{
			if (String::IsNullOrWhiteSpace(text))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginCombo(ctx.marshal_as<const char*>(text), String::IsNullOrWhiteSpace(previewValue) ? "" : ctx.marshal_as<const char*>(previewValue), (ImGuiComboFlags)flags);
		}
		static bool BeginCombo(String^ text, String^ previewValue)
		{
			return BeginCombo(text, previewValue, eImGuiComboFlags::None);
		}
		static void EndCombo()
		{
			ImGui::EndCombo();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: DragScalar, DragFloat, DragInt, etc.
		//-------------------------------------------------------------------------
		static bool DragFloat(String^ label, float% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value = v;
			bool result = ImGui::DragFloat(ctx.marshal_as<const char*>(label), &value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = value;
			return result;
		}
		static bool DragFloat(String^ label, float% v, float speed, float min, float max)
		{
			return DragFloat(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat(String^ label, float% v, float min, float max)
		{
			return DragFloat(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat(String^ label, float% v, float speed)
		{
			return DragFloat(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat(String^ label, float% v)
		{
			return DragFloat(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat2(String^ label, array<float>^% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[2] = { v[0], v[1] };
			bool result = ImGui::DragFloat2(ctx.marshal_as<const char*>(label), (float*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(2) { value[0], value[1] };
			return result;
		}
		static bool DragFloat2(String^ label, array<float>^% v, float speed, float min, float max)
		{
			return DragFloat2(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, array<float>^% v, float min, float max)
		{
			return DragFloat2(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, array<float>^% v, float speed)
		{
			return DragFloat2(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, array<float>^% v)
		{
			return DragFloat2(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat2(String^ label, Vector2% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			array<float>^ arr = gcnew array<float>(2) { v.X, v.Y };
			bool result = DragFloat2(label, arr, speed, min, max, format, flags);
			v = Vector2(arr[0], arr[1]);
			return result;
		}
		static bool DragFloat2(String^ label, Vector2% v, float speed, float min, float max)
		{
			return DragFloat2(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, Vector2% v, float min, float max)
		{
			return DragFloat2(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, Vector2% v, float speed)
		{
			return DragFloat2(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, Vector2% v)
		{
			return DragFloat2(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat3(String^ label, array<float>^% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[3] = { v[0], v[1], v[2] };
			bool result = ImGui::DragFloat3(ctx.marshal_as<const char*>(label), (float*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(3) { value[0], value[1], value[2] };
			return result;
		}
		static bool DragFloat3(String^ label, array<float>^% v, float speed, float min, float max)
		{
			return DragFloat3(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, array<float>^% v, float min, float max)
		{
			return DragFloat3(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, array<float>^% v, float speed)
		{
			return DragFloat3(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, array<float>^% v)
		{
			return DragFloat3(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat3(String^ label, Vector3% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			array<float>^ arr = gcnew array<float>(3) { v.X, v.Y, v.Z };
			bool result = DragFloat3(label, arr, speed, min, max, format, flags);
			v = Vector3(arr[0], arr[1], arr[2]);
			return result;
		}
		static bool DragFloat3(String^ label, Vector3% v, float speed, float min, float max)
		{
			return DragFloat3(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, Vector3% v, float min, float max)
		{
			return DragFloat3(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, Vector3% v, float speed)
		{
			return DragFloat3(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, Vector3% v)
		{
			return DragFloat3(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat4(String^ label, array<float>^% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[4] = { v[0], v[1], v[2], v[3]};
			bool result = ImGui::DragFloat4(ctx.marshal_as<const char*>(label), (float*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(4) { value[0], value[1], value[2], value[3] };
			return result;
		}
		static bool DragFloat4(String^ label, array<float>^% v, float speed, float min, float max)
		{
			return DragFloat4(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, array<float>^% v, float min, float max)
		{
			return DragFloat4(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, array<float>^% v, float speed)
		{
			return DragFloat4(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, array<float>^% v)
		{
			return DragFloat4(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat4(String^ label, Vector4% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			array<float>^ arr = gcnew array<float>(4) { v.X, v.Y, v.Z, v.W };
			bool result = DragFloat4(label, arr, speed, min, max, format, flags);
			v = Vector4(arr[0], arr[1], arr[2], arr[3]);
			return result;
		}
		static bool DragFloat4(String^ label, Vector4% v, float speed, float min, float max)
		{
			return DragFloat4(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, Vector4% v, float min, float max)
		{
			return DragFloat4(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, Vector4% v, float speed)
		{
			return DragFloat4(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, Vector4% v)
		{
			return DragFloat4(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragInt(String^ label, int% v, float speed, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value = v;
			bool result = ImGui::DragInt(ctx.marshal_as<const char*>(label), &value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = value;
			return result;
		}
		static bool DragInt(String^ label, int% v, float speed, int min, int max)
		{
			return DragInt(label, v, speed, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt(String^ label, int% v, int min, int max)
		{
			return DragInt(label, v, 1.0F, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt(String^ label, int% v, float speed)
		{
			return DragInt(label, v, speed, 0, 0, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt(String^ label, int% v)
		{
			return DragInt(label, v, 1.0F, 0, 0, "%d", eImGuiSliderFlags::None);
		}

		static bool DragInt2(String^ label, array<int>^% v, float speed, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[2] = { v[0], v[1] };
			bool result = ImGui::DragInt2(ctx.marshal_as<const char*>(label), (int*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(2) { value[0], value[1] };
			return result;
		}
		static bool DragInt2(String^ label, array<int>^% v, float speed, int min, int max)
		{
			return DragInt2(label, v, speed, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt2(String^ label, array<int>^% v, int min, int max)
		{
			return DragInt2(label, v, 1.0F, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt2(String^ label, array<int>^% v, float speed)
		{
			return DragInt2(label, v, speed, 0, 0, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt2(String^ label, array<int>^% v)
		{
			return DragInt2(label, v, 1.0F, 0, 0, "%d", eImGuiSliderFlags::None);
		}

		static bool DragInt3(String^ label, array<int>^% v, float speed, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[3] = { v[0], v[1], v[2]};
			bool result = ImGui::DragInt3(ctx.marshal_as<const char*>(label), (int*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(3) { value[0], value[1], value[2] };
			return result;
		}
		static bool DragInt3(String^ label, array<int>^% v, float speed, int min, int max)
		{
			return DragInt3(label, v, speed, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt3(String^ label, array<int>^% v, int min, int max)
		{
			return DragInt3(label, v, 1.0F, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt3(String^ label, array<int>^% v, float speed)
		{
			return DragInt3(label, v, speed, 0, 0, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt3(String^ label, array<int>^% v)
		{
			return DragInt3(label, v, 1.0F, 0, 0, "%d", eImGuiSliderFlags::None);
		}

		static bool DragInt4(String^ label, array<int>^% v, float speed, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[4] = { v[0], v[1], v[2], v[3] };
			bool result = ImGui::DragInt4(ctx.marshal_as<const char*>(label), (int*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(4) { value[0], value[1], value[2], value[3] };
			return result;
		}
		static bool DragInt4(String^ label, array<int>^% v, float speed, int min, int max)
		{
			return DragInt4(label, v, speed, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt4(String^ label, array<int>^% v, int min, int max)
		{
			return DragInt4(label, v, 1.0F, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt4(String^ label, array<int>^% v, float speed)
		{
			return DragInt4(label, v, speed, 0, 0, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt4(String^ label, array<int>^% v)
		{
			return DragInt4(label, v, 1.0F, 0, 0, "%d", eImGuiSliderFlags::None);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: SliderScalar, SliderFloat, SliderInt, etc.
		//-------------------------------------------------------------------------
		static bool SliderFloat(String^ label, float% v, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value = v;
			bool result = ImGui::SliderFloat(ctx.marshal_as<const char*>(label), &value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = value;
			return result;
		}
		static bool SliderFloat(String^ label, float% v, float min, float max)
		{
			return SliderFloat(label, v, min, max, "%.3f", eImGuiSliderFlags::None);
		}

		static bool SliderFloat2(String^ label, array<float>^% v, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[2] = { v[0], v[1] };
			bool result = ImGui::SliderFloat2(ctx.marshal_as<const char*>(label), (float*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(2) { value[0], value[1] };
			return result;
		}
		static bool SliderFloat2(String^ label, array<float>^% v, float min, float max)
		{
			return SliderFloat2(label, v, min, max, "%.3f", eImGuiSliderFlags::None);
		}

		static bool SliderFloat3(String^ label, array<float>^% v, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[3] = { v[0], v[1], v[2] };
			bool result = ImGui::SliderFloat3(ctx.marshal_as<const char*>(label), (float*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(3) { value[0], value[1], value[2] };
			return result;
		}
		static bool SliderFloat3(String^ label, array<float>^% v, float min, float max)
		{
			return SliderFloat3(label, v, min, max, "%.3f", eImGuiSliderFlags::None);
		}

		static bool SliderFloat4(String^ label, array<float>^% v, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[4] = { v[0], v[1], v[2], v[3] };
			bool result = ImGui::SliderFloat4(ctx.marshal_as<const char*>(label), (float*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(4) { value[0], value[1], value[2], value[3] };
			return result;
		}
		static bool SliderFloat4(String^ label, array<float>^% v, float min, float max)
		{
			return SliderFloat4(label, v, min, max, "%.3f", eImGuiSliderFlags::None);
		}


		static bool SliderInt(String^ label, int% v, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value = v;
			bool result = ImGui::SliderInt(ctx.marshal_as<const char*>(label), &value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = value;
			return result;
		}
		static bool SliderInt(String^ label, int% v, int min, int max)
		{
			return SliderInt(label, v, min, max, "%d", eImGuiSliderFlags::None);
		}

		static bool SliderInt2(String^ label, array<int>^% v, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[2] = { v[0], v[1] };
			bool result = ImGui::SliderInt2(ctx.marshal_as<const char*>(label), (int*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(2) { value[0], value[1] };
			return result;
		}
		static bool SliderInt2(String^ label, array<int>^% v, int min, int max)
		{
			return SliderInt2(label, v, min, max, "%d", eImGuiSliderFlags::None);
		}

		static bool SliderInt3(String^ label, array<int>^% v, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[3] = { v[0], v[1], v[2] };
			bool result = ImGui::SliderInt3(ctx.marshal_as<const char*>(label), (int*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(3) { value[0], value[1], value[2] };
			return result;
		}
		static bool SliderInt3(String^ label, array<int>^% v, int min, int max)
		{
			return SliderInt3(label, v, min, max, "%d", eImGuiSliderFlags::None);
		}

		static bool SliderInt4(String^ label, array<int>^% v, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[4] = { v[0], v[1], v[2], v[3] };
			bool result = ImGui::SliderInt4(ctx.marshal_as<const char*>(label), (int*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(4) { value[0], value[1], value[2], value[3] };
			return result;
		}
		static bool SliderInt4(String^ label, array<int>^% v, int min, int max)
		{
			return SliderInt4(label, v, min, max, "%d", eImGuiSliderFlags::None);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: InputScalar, InputFloat, InputInt, etc.
		//-------------------------------------------------------------------------
		// todo

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: InputText, InputTextMultiline, InputTextWithHint
		//-------------------------------------------------------------------------
		static bool InputText(String^ label, String^% input, eImGuiInputFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			if (String::IsNullOrEmpty(input))
			{
				std::string* str = new std::string("");

				bool result = ImGui::InputText(ctx.marshal_as<const char*>(label), str, (ImGuiInputFlags)flags);

				input = gcnew String(str->c_str());
				delete str;

				return result;
			}

			std::string* str = new std::string(ctx.marshal_as<const char*>(input));

			bool result = ImGui::InputText(ctx.marshal_as<const char*>(label), str, (ImGuiInputFlags)flags);

			input = gcnew String(str->c_str());
			delete str;

			return result;
		}
		static bool InputText(String^ label, String^% input)
		{
			return InputText(label, input, eImGuiInputFlags::None);
		}

		static bool InputTextMultiline(String^ label, String^% input, Vector2 size, eImGuiInputFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			std::string* str = new std::string(ctx.marshal_as<const char*>(input));

			bool result = ImGui::InputTextMultiline(ctx.marshal_as<const char*>(label), str, Vector2ToImVec2(size), (ImGuiInputFlags)flags);

			input = gcnew String(str->c_str());
			delete str;

			return result;
		}
		static bool InputTextMultiline(String^ label, String^% input)
		{
			return InputTextMultiline(label, input, Vector2::Zero, eImGuiInputFlags::None);
		}

		static bool InputTextWithHint(String^ label, String^ hint, String^% input, eImGuiInputFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(hint))
				return false;

			msclr::interop::marshal_context ctx;

			std::string* str = new std::string(ctx.marshal_as<const char*>(input));

			bool result = ImGui::InputTextWithHint(ctx.marshal_as<const char*>(label), ctx.marshal_as<const char*>(hint), str, (ImGuiInputFlags)flags);

			input = gcnew String(str->c_str());
			delete str;

			return result;
		}
		static bool InputTextWithHint(String^ label, String^ hint, String^% input)
		{
			return InputTextWithHint(label, hint, input, eImGuiInputFlags::None);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: ColorEdit, ColorPicker, ColorButton, etc.
		//-------------------------------------------------------------------------
		static bool ColorEdit3(String^ label, Vector3% color, eImGuiColorEditFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			
			ImVec4 vec = ImVec4(color.X, color.Y, color.Z, 0.0F);
			bool result = ImGui::ColorEdit3(ctx.marshal_as<const char*>(label), (float*)&vec, (ImGuiColorEditFlags)flags);

			color = Vector3(vec.x, vec.y, vec.z);
			return result;
		}
		static bool ColorPicker3(String^ label, Vector3% color, eImGuiColorEditFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			ImVec4 vec = ImVec4(color.X, color.Y, color.Z, 0.0F);
			bool result = ImGui::ColorPicker3(ctx.marshal_as<const char*>(label), (float*)&vec, (ImGuiColorEditFlags)flags);

			color = Vector3(vec.x, vec.y, vec.z);
			return result;
		}

		static bool ColorEdit4(String^ label, Vector4% color, eImGuiColorEditFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			ImVec4 vec = ImVec4(color.X, color.Y, color.Z, color.W);
			bool result = ImGui::ColorEdit4(ctx.marshal_as<const char*>(label), (float*)&vec, (ImGuiColorEditFlags)flags);

			color = Vector4(vec.x, vec.y, vec.z, vec.w);
			return result;
		}
		static bool ColorPicker4(String^ label, Vector4% color, eImGuiColorEditFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			ImVec4 vec = ImVec4(color.X, color.Y, color.Z, color.W);
			bool result = ImGui::ColorPicker4(ctx.marshal_as<const char*>(label), (float*)&vec, (ImGuiColorEditFlags)flags);

			color = Vector4(vec.x, vec.y, vec.z, vec.w);
			return result;
		}

		static void ColorTooltip(String^ label, Vector4 color, eImGuiColorEditFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;

			ImVec4 vec = ImVec4(color.X, color.Y, color.Z, color.W);
			ImGui::ColorTooltip(ctx.marshal_as<const char*>(label), (float*)&vec, (ImGuiColorEditFlags)flags);
		}

		static void SetColorEditOptions(eImGuiColorEditFlags flags)
		{
			ImGui::SetColorEditOptions((ImGuiColorEditFlags)flags);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: TreeNode, CollapsingHeader, etc.
		//-------------------------------------------------------------------------
		static bool TreeNode(String^ label)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::TreeNode(ctx.marshal_as<const char*>(label));
		}
		static void TreePop()
		{
			ImGui::TreePop();
		}

		static void TreePush(String^ id)
		{
			if (String::IsNullOrWhiteSpace(id))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::TreePush(ctx.marshal_as<const char*>(id));
		}
		static void TreePush(IntPtr ptrId)
		{
			if (ptrId == IntPtr::Zero)
				return;

			ImGui::TreePush(ptrId.ToPointer());
		}
		static void TreePushOverrideID(ImGuiID id)
		{
			ImGui::TreePushOverrideID(id);
		}

		static bool CollapsingHeader(String^ label, bool% visible, eImGuiTreeNodeFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			bool pVisible = visible;

			bool result = ImGui::CollapsingHeader(ctx.marshal_as<const char*>(label), &pVisible, (ImGuiTreeNodeFlags)flags);

			visible = pVisible;

			return result;
		}
		static bool CollapsingHeader(String^ label, bool% visible)
		{
			return CollapsingHeader(label, visible, eImGuiTreeNodeFlags::None);
		}

		static bool CollapsingHeader(String^ label, eImGuiTreeNodeFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::CollapsingHeader(ctx.marshal_as<const char*>(label), (ImGuiTreeNodeFlags)flags);
		}
		static bool CollapsingHeader(String^ label)
		{
			return CollapsingHeader(label, eImGuiTreeNodeFlags::None);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: Selectable
		//-------------------------------------------------------------------------
		static bool Selectable(String^ label, bool selected, eImGuiSelectableFlags flags, Vector2 size)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::Selectable(ctx.marshal_as<const char*>(label), selected, (ImGuiSelectableFlags)flags, Vector2ToImVec2(size));
		}
		static bool Selectable(String^ label, bool selected)
		{
			return Selectable(label, selected, eImGuiSelectableFlags::None, Vector2::Zero);
		}
		static bool Selectable(String^ label)
		{
			return Selectable(label, false, eImGuiSelectableFlags::None, Vector2::Zero);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: ListBox
		//-------------------------------------------------------------------------
		static bool BeginListBox(String^ label, Vector2 size)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginListBox(ctx.marshal_as<const char*>(label), Vector2ToImVec2(size));
		}
		static bool BeginListBox(String^ label)
		{
			return BeginListBox(label, Vector2::Zero);
		}
		static void EndListBox()
		{
			ImGui::EndListBox();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: PlotLines, PlotHistogram
		//-------------------------------------------------------------------------
		static void PlotLines(String^ label, array<float>^ data)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			pin_ptr<float> pinnedData = &data[0];
			float* pby = pinnedData;
			const float* dataPtr = reinterpret_cast<const float*>(pby);

			msclr::interop::marshal_context ctx;
			ImGui::PlotLines(ctx.marshal_as<const char*>(label), dataPtr, data->Length);
		}
		static void PlotHistogram(String^ label, array<float>^ data)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			pin_ptr<float> pinnedData = &data[0];
			float* pby = pinnedData;
			const float* dataPtr = reinterpret_cast<const float*>(pby);

			msclr::interop::marshal_context ctx;
			ImGui::PlotHistogram(ctx.marshal_as<const char*>(label), dataPtr, data->Length);
		}

		//-------------------------------------------------------------------------
		// [SECTION] MenuItem, BeginMenu, EndMenu, etc.
		//-------------------------------------------------------------------------
		static bool BeginMenuBar()
		{
			return ImGui::BeginMenuBar();
		}
		static void EndMenuBar()
		{
			ImGui::EndMenuBar();
		}

		static bool BeginMainMenuBar()
		{
			return ImGui::BeginMainMenuBar();
		}
		static void EndMainMenuBar()
		{
			ImGui::EndMainMenuBar();
		}

		static bool BeginMenuEx(String^ label, String^ icon, bool enabled)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(icon))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginMenuEx(ctx.marshal_as<const char*>(label), ctx.marshal_as<const char*>(icon), enabled);
		}
		static bool BeginMenuEx(String^ label, String^ icon)
		{
			return BeginMenuEx(label, icon, true);
		}
		static bool BeginMenu(String^ label, bool enabled)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginMenu(ctx.marshal_as<const char*>(label), enabled);
		}
		static bool BeginMenu(String^ label)
		{
			return BeginMenu(label, true);
		}
		static void EndMenu()
		{
			ImGui::EndMenu();
		}

		static bool MenuItemEx(String^ label, String^ icon, String^ shortcut, bool selected, bool enabled)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(icon))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::MenuItemEx(
				ctx.marshal_as<const char*>(label),
				ctx.marshal_as<const char*>(icon),
				String::IsNullOrWhiteSpace(shortcut) ? (const char*)0 : ctx.marshal_as<const char*>(shortcut),
				selected,
				enabled);
		}
		static bool MenuItemEx(String^ label, String^ icon)
		{
			return MenuItemEx(label, icon, nullptr, false, true);
		}
		static bool MenuItem(String^ label, String^ shortcut, bool selected, bool enabled)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::MenuItem(
				ctx.marshal_as<const char*>(label),
				String::IsNullOrWhiteSpace(shortcut) ? (const char*)0 : ctx.marshal_as<const char*>(shortcut),
				selected,
				enabled);
		}
		static bool MenuItem(String^ label)
		{
			return MenuItem(label, nullptr, false, true);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: BeginTabBar, EndTabBar, etc.
		//-------------------------------------------------------------------------
		static bool BeginTabBar(String^ id, eImGuiTabBarFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginTabBar(ctx.marshal_as<const char*>(id), (ImGuiTabBarFlags)flags);
		}
		static bool BeginTabBar(String^ id)
		{
			return BeginTabBar(id, eImGuiTabBarFlags::None);
		}
		static void EndTabBar()
		{
			ImGui::EndTabBar();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: BeginTabItem, EndTabItem, etc.
		//-------------------------------------------------------------------------
		static bool BeginTabItem(String^ label, bool% open, eImGuiTabItemFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			bool pOpen = open;

			bool result = ImGui::BeginTabItem(ctx.marshal_as<const char*>(label), &pOpen, (ImGuiTabItemFlags)flags);

			open = pOpen;
			return result;
		}
		static bool BeginTabItem(String^ label, bool% open)
		{
			return BeginTabItem(label, open, eImGuiTabItemFlags::None);
		}
		static bool BeginTabItem(String^ label)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginTabItem(ctx.marshal_as<const char*>(label));
		}
		static void EndTabItem()
		{
			ImGui::EndTabItem();
		}

		static bool TabItemButton(String^ label, eImGuiTabItemFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			
			msclr::interop::marshal_context ctx;
			return ImGui::TabItemButton(ctx.marshal_as<const char*>(label), (ImGuiTabItemFlags)flags);
		}

		//-----------------------------------------------------------------------------
		// [SECTION] Tables: BeginTable, EndTable.
		//-----------------------------------------------------------------------------
		static bool BeginTable(String^ label, int columns_count, eImGuiTableFlags flags, Vector2 outer_size, float inner_width)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginTable(ctx.marshal_as<const char*>(label), columns_count, (ImGuiTableFlags) flags, Vector2ToImVec2(outer_size), inner_width);
		}
		static bool BeginTable(String^ label, int columns_count, eImGuiTableFlags flags)
		{
			return BeginTable(label, columns_count, flags, Vector2(0.0F), 0.0F);
		}
		static bool BeginTable(String^ label, int columns_count)
		{
			return BeginTable(label, columns_count, eImGuiTableFlags::None, Vector2(0.0F), 0.0F);
		}
		static void EndTable()
		{
			ImGui::EndTable();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Tables: Row changes
		//-------------------------------------------------------------------------
		static int TableGetRowIndex()
		{
			return ImGui::TableGetRowIndex();
		}
		static void TableNextRow(eImGuiTableRowFlags row_flags, float row_min_height)
		{
			ImGui::TableNextRow((ImGuiTableRowFlags) row_flags, row_min_height);
		}
		static void TableNextRow()
		{
			TableNextRow(eImGuiTableRowFlags::None, 0.0F);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Tables: Columns changes
		//-------------------------------------------------------------------------
		static int TableGetColumnIndex()
		{
			return ImGui::TableGetColumnIndex();
		}
		static bool TableSetColumnIndex(int column_n)
		{
			return ImGui::TableSetColumnIndex(column_n);
		}
		static bool TableNextColumn()
		{
			return ImGui::TableNextColumn();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Extensions: Timeline
		//-------------------------------------------------------------------------
		static bool BeginTimeline(String^ label, Vector2 size, eImGuiChildFlags childFlags, eImGuiWindowFlags windowFlags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginTimeline(ctx.marshal_as<const char*>(label), Vector2ToImVec2(size), (ImGuiChildFlags)childFlags, (ImGuiWindowFlags)windowFlags);
		}
		static bool BeginTimeline(String^ label, Vector2 size, eImGuiChildFlags childFlags)
		{
			return BeginTimeline(label, size, childFlags, eImGuiWindowFlags::None);
		}
		static bool BeginTimeline(String^ label, Vector2 size)
		{
			return BeginTimeline(label, size, eImGuiChildFlags::None, eImGuiWindowFlags::None);
		}
		static bool BeginTimeline(String^ label)
		{
			return BeginTimeline(label, Vector2::Zero, eImGuiChildFlags::None, eImGuiWindowFlags::None);
		}

		static bool Timeline(String^ label, array<float>^% values, int maxFrames)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (!values)
				return false;
			if (values->Length > 2)
				return false;

			msclr::interop::marshal_context ctx;

			float v[2] = { values[0], values[1] };
			bool result = ImGui::Timeline(ctx.marshal_as<const char*>(label), (float*)&v, maxFrames);

			values[0] = v[0];
			values[1] = v[1];

			return result;
		}
		static bool Timeline(String^ label, Vector2% values, int maxFrames)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			array<float>^ arr = gcnew array<float>(2)
			{
				values.X, values.Y
			};

			bool result = Timeline(label, arr, maxFrames);

			values = Vector2(arr[0], arr[1]);

			return result;
		}
		static void EndTimeline(bool drawCurrentFrame, int currentFrame, int maxFrames, bool drawLines, int lineCount, bool drawValues)
		{
			ImGui::EndTimeline(drawCurrentFrame, currentFrame, maxFrames, drawLines, lineCount, drawValues);
		}

	private:
		static bool m_bForceCursor;
		static int m_iActiveWindows;
	};
}

class ImGuiDraw
{
public:
	static bool OnWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGuiStates::s_bIsImGuiInitialized)
		{
			if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
				return true;
		}

		return false;
	}

	static void OnBeforeD3D9DeviceEndScene(IDirect3DDevice9* d3d9Device)
	{
		// Initialize ImGui if not initialized yet
		InitializeImGui(d3d9Device);

		// ImGui is not initialized, return.
		if (!ImGuiStates::s_bIsImGuiInitialized)
			return;

		IntPtr d3d9DevicePointer = IntPtr(d3d9Device);

		// Set the style
		switch (ImGuiIV::SelectedStyle)
		{
			case 0: // dark
				ImGui::StyleColorsDark();
				break;
			case 1: // classic
				ImGui::StyleColorsClassic();
				break;
			case 2: // light
				ImGui::StyleColorsLight();
				break;
		}

		// Get ImGuiIO
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Get the main Viewport of ImGui
		ImGuiViewport* vp = ImGui::GetMainViewport();

		// Invoke on before ImGui new frame event
		if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
			IVSDKDotNet::Manager::ManagerScript::s_Instance->RaiseOnBeforeNewImGuiFrame(d3d9DevicePointer);

		// Rebuild the font atlas if not built yet
		if (!io.Fonts->IsBuilt())
		{
			//if (io.Fonts->Build())
				ImGui_ImplDX9_CreateFontsTexture();
		}

		// Create new ImGui Frame
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//ImGui::Begin("Test");

		//if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right, false))
		//{
		//	ImRect rect = ImGui::GetCurrentWindow()->TitleBarRect();

		//	if (ImGui::IsMouseHoveringRect(rect.Min, rect.Max, false))
		//	{
		//		ImGui::OpenPopup("Testgset4365");
		//	}
		//}

		//if (ImGui::BeginPopup("Testgset4365"))
		//{
		//	ImGui::Selectable("lol");
		//	ImGui::Selectable("Exit");
		//	ImGui::EndPopup();
		//}

		//ImGui::End();

		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		// Do ImGui stuff in here

		DoDockspace();

		int windowDrawCallsQueueCount = ImGuiIV::DrawCommandsList->Count;

		// Script/Internal Drawing
		if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
		{
			ImDrawList* drawList = ImGui::GetBackgroundDrawList();
			IVSDKDotNet::Manager::ManagerScript::s_Instance->RaiseOnD3D9Frame(d3d9DevicePointer, ImGuiIV_DrawingContext(drawList));
		}

#pragma region Custom Drawing
		System::Guid callerScriptGuid = System::Guid::Empty;

		try
		{
			for (int i = 0; i < IVSDKDotNet::ImGuiIV::DrawCommandsList->Count; i++)
			{
				ImGuiIV_DrawCommandData drawData = ImGuiIV::DrawCommandsList[i];
				callerScriptGuid = drawData.CallerScriptID;
				drawData.Data->Invoke();
			}
		}
		catch (System::Exception^ ex)
		{
			if (callerScriptGuid != System::Guid::Empty)
			{
				// Abort script
				if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
					IVSDKDotNet::Manager::ManagerScript::s_Instance->AbortScript(callerScriptGuid);
			}
		}
#pragma endregion

#if _DEBUG
		// TODO: Remove later
		static bool debugWindowOpened = false;

		if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_F9, false))
			debugWindowOpened = !debugWindowOpened;

		if (debugWindowOpened)
		{
			ImGui::Begin("IV-SDK .NET Wrapper Debug", &debugWindowOpened, ImGuiWindowFlags_AlwaysAutoResize);

			ImGui::SeparatorText("ImGuiIV States");

			// Active Script Windows
			ImGui::Text("Active Script Windows: %s", std::to_string(ImGuiIV::ActiveWindows).c_str());
			ImGui::Text("Window Draw Calls List: %s", std::to_string(windowDrawCallsQueueCount).c_str());

			ImGui::BeginDisabled();
			ImGui::Checkbox("Wants Mouse Disabled", &ImGuiStates::s_bImGuiWantsMouseDisabled);
			ImGui::Checkbox("Wants Keyboard Disabled", &ImGuiStates::s_bImGuiWantsKeyboardDisabled);
			ImGui::Checkbox("Reactivate Keyboard Inputs", &ImGuiStates::s_bReactivateKeyboardInputs);
			ImGui::EndDisabled();

			// Dear ImGui Input
			ImGui::SeparatorText("Dear ImGui");
			ImGui::BeginDisabled();
			ImGui::Checkbox("Wants Mouse Input", &io.WantCaptureMouse);
			ImGui::Checkbox("Wants Keyboard Input", &io.WantCaptureKeyboard);
			ImGui::Checkbox("Wants Text Input", &io.WantTextInput);
			ImGui::EndDisabled();

			ImGui::SetWindowPos(ImVec2(10.0F, vp->Size.y - (ImGui::GetWindowSize().y + 250.0F)), ImGuiCond_FirstUseEver);
			ImGui::End();
		}
#endif // _DEBUG

		// Do ImGui stuff in here
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

		// TODO: Fix cursor jump to center of screen when keyboard gets reacquired.

		// Disable mouse input if there are any opened ImGui windows or if the cursor should be forced.
		if (ImGuiIV::ActiveWindows > 0 || ImGuiIV::ForceCursor)
		{
			// Draw a mouse cursor on screen
			io.MouseDrawCursor = true;

			ImGuiStates::s_bImGuiWantsMouseDisabled = true;

			// If ImGui wants text input, disable Keyboard Input too.
			if (io.WantTextInput)
				ImGuiStates::s_bImGuiWantsKeyboardDisabled = true;
			else
			{
				// Set s_bReactivateKeyboardInputs to true so the Keyboard Inputs can be regained after we set s_bImGuiWantsKeyboardDisabled to false
				if (ImGuiStates::s_bImGuiWantsKeyboardDisabled)
					ImGuiStates::s_bReactivateKeyboardInputs = true;

				ImGuiStates::s_bImGuiWantsKeyboardDisabled = false;

				// Regain Keyboard Input
				if (ImGuiStates::s_bReactivateKeyboardInputs)
				{
					// Set both to false so the devices can be reacquired
					ImGuiStates::s_bImGuiWantsMouseDisabled = false;
					ImGuiStates::s_bImGuiWantsKeyboardDisabled = false;

					// Reset so this process can be repeated if necessary
					ImGuiStates::s_bReactivateKeyboardInputs = false;
				}
			}
		}
		else
		{
			// Reset all
			io.MouseDrawCursor = false;
			ImGuiStates::s_bImGuiWantsMouseDisabled = false;
			ImGuiStates::s_bImGuiWantsKeyboardDisabled = false;
			ImGuiStates::s_bReactivateKeyboardInputs = false;
		}

		// Reset active window count
		ImGuiIV::ActiveWindows = 0;

		// End ImGui Frame and draw
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	static void OnBeforeD3D9DeviceReset(IDirect3DDevice9* d3d9Device)
	{
		// Initialize ImGui if not initialized yet
		InitializeImGui(d3d9Device);

		// Invalidate device objects for ImGui
		ImGui_ImplDX9_InvalidateDeviceObjects();
	}
	static void OnAfterD3D9DeviceReset()
	{
		// Create device objects for ImGui
		ImGui_ImplDX9_CreateDeviceObjects();
	}

	static void UninitializeImGui()
	{
		if (!ImGuiStates::s_bIsImGuiInitialized)
			return;

		// Set ImGui status as uninitialized
		ImGuiStates::SetImGuiStatusAsWasUninitialized();

		// Shutdown ImGui stuff
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX9_Shutdown();
		ImGui::DestroyContext();
	}

private:
	static void InitializeImGui(IDirect3DDevice9* d3d9Device)
	{
		if (ImGuiStates::s_bIsImGuiInitialized)
			return;
		if (ImGuiStates::s_bStopTryingToInitializeImGui)
			return;

		D3DDEVICE_CREATION_PARAMETERS creationParams;
		d3d9Device->GetCreationParameters(&creationParams);

		// Setup ImGui stuff
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.IniFilename = NULL;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

		// Initialize the win32 backend
		ImGui_ImplWin32_Init(creationParams.hFocusWindow);

		// Initialize the dx9 backend
		ImGui_ImplDX9_Init(d3d9Device);

		// Add font
		String^ fontFile = CLR::CLRBridge::IVSDKDotNetDataPath + "\\public-sans.regular.ttf";
		msclr::interop::marshal_context ctx;
		io.Fonts->AddFontFromFileTTF(ctx.marshal_as<const char*>(fontFile), 14.5F);
		io.FontGlobalScale = 1.05F;
		
		ImGuiStates::s_bIsImGuiInitialized = true;
	}
	static void DoDockspace()
	{
		static bool opt_fullscreen = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::Begin("MainDockSpace", nullptr, window_flags);

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		ImGui::End();
	}
};