#include "pch.h"
#include "ImGuiIV.h"

bool ImGuiDraw::OnWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGuiIV::ActiveScriptWindows > 0 || ImGuiIV::ForceCursor)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;
	}
	else
	{
		// Only handle key inputs so the "IsKeyXXX" functions work even if no ImGui window is visible
		ImGui_ImplWin32_WndProcKeyOnlyHandler(hWnd, msg, wParam, lParam);
	}

	return false;
}

void ImGuiDraw::InitializeImGui(IDirect3DDevice9* d3d9Device)
{
	if (!d3d9Device)
	{
		WRITE_TO_DEBUG_OUTPUT("[ImGuiIV] Could not initialize ImGui as the device passed into the init func was nullptr!");
		return;
	}
	if (ImGuiIV::WasImGuiInitialized)
		return;

	Logger::LogDebug("[ImGuiIV] Beginning to initialize ImGui...");

	D3DDEVICE_CREATION_PARAMETERS creationParams;
	d3d9Device->GetCreationParameters(&creationParams);

	// Setup ImGui stuff
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = NULL;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Controller Navigation

	// Initialize the win32 backend
	ImGui_ImplWin32_Init(creationParams.hFocusWindow);

	// Initialize the dx9 backend
	ImGui_ImplDX9_Init(d3d9Device);

	// Add font
	String^ fontFile = CLR::CLRBridge::IVSDKDotNetDataPath + "\\public-sans.regular.ttf";
	msclr::interop::marshal_context ctx;
	io.Fonts->AddFontFromFileTTF(ctx.marshal_as<const char*>(fontFile), 15.5F);

	// Set flag
	ImGuiIV::WasImGuiInitialized = true;

	Logger::LogDebug("[ImGuiIV] Finished initializing ImGui.");
}
void ImGuiDraw::UninitializeImGui()
{
	if (!ImGuiIV::WasImGuiInitialized)
		return;

	// Shutdown ImGui stuff
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX9_Shutdown();
	ImGui::DestroyContext();
}
void ImGuiDraw::DoDockspace()
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
	ImGui::Begin("IVSDKDotNetMainDockSpace", nullptr, window_flags);

	// Store ID of the dockspace window so we can exclude this window in certain functions if we have to
	ImGuiIV::DockspaceWindowID = ImGui::GetCurrentWindowRead()->ID;

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

void ImGuiDraw::EnableControllerNavigation(ImGuiIO& io)
{
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}
void ImGuiDraw::DisableControllerNavigation(ImGuiIO& io)
{
	io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableGamepad;
}

void ImGuiDraw::OnAfterD3D9DeviceBeginScene(IDirect3DDevice9* d3d9Device)
{

}
void ImGuiDraw::OnBeforeD3D9DeviceEndScene(IDirect3DDevice9* d3d9Device)
{
	// Initialize ImGui if not initialized yet
	InitializeImGui(d3d9Device);

	// ImGui is not initialized, return.
	if (!ImGuiIV::WasImGuiInitialized)
		return;

	IntPtr d3d9DevicePointer = IntPtr(d3d9Device);

	// Get ImGuiIO
	ImGuiIO& io = ImGui::GetIO();

	// Little hack to get the mouse XButtons to register
	SHORT x1 = GetAsyncKeyState(VK_XBUTTON1);
	SHORT x2 = GetAsyncKeyState(VK_XBUTTON2);
	io.AddMouseButtonEvent(3, (x1 & 0x8000) != 0);
	io.AddMouseButtonEvent(4, (x2 & 0x8000) != 0);

	// Get the main Viewport of ImGui
	ImGuiViewport* vp = ImGui::GetMainViewport();

	// Invoke on before ImGui new frame event
	if (IVSDKDotNet::Manager::ManagerScript::HasInstance())
		IVSDKDotNet::Manager::ManagerScript::GetInstance()->RaiseOnBeforeNewImGuiFrame(d3d9DevicePointer);

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

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// Do ImGui stuff in here

	DoDockspace();

	// Script/Internal Drawing
	if (IVSDKDotNet::Manager::ManagerScript::HasInstance())
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		IVSDKDotNet::Manager::ManagerScript::GetInstance()->RaiseOnD3D9Frame(d3d9DevicePointer, ImGuiIV_DrawingContext(drawList, true));
	}

	if (ImGuiIV::DoesAnyWindowHasThisAdditionalFlag("DisableControllerInput"))
	{
		ImGuiIV::DisableControllerInput = true;
		EnableControllerNavigation(io);
	}
	else
	{
		ImGuiIV::DisableControllerInput = false;
		DisableControllerNavigation(io);
	}

	// Get the amount of active windows
	ImGuiIV::ActiveScriptWindows = ImGuiIV::GetActiveWindowCount();

	// Do ImGui stuff in here
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	// Disable inputs for ImGui if there are any active script windows or if the cursor should be forced to be shown on screen.
	if (ImGuiIV::ActiveScriptWindows > 0 || ImGuiIV::ForceCursor)
	{
		// Draw a mouse cursor on screen
		io.MouseDrawCursor = true;

		int windowsWithDoNotDisableMouseInputFlag = ImGuiIV::CountWindowsWhichHaveThisAdditionalFlag("DoNotDisableMouseInput");
		int windowsWithDoNotDisableKeyboardInputFlag = ImGuiIV::CountWindowsWhichHaveThisAdditionalFlag("DoNotDisableKeyboardInput");

		// If there are as many active windows as there are windows with the "DoNotDisableMouseInput" flag, we can safely enable input
		ImGuiIV::DisableMouseInput = ImGuiIV::ActiveScriptWindows != windowsWithDoNotDisableMouseInputFlag;

		if (io.WantTextInput)
		{
			// If ImGui wants text input we definitly want to disable the keyboard input
			ImGuiIV::DisableKeyboardInput = true;
		}
		else
		{
			// If there are as many active windows as there are windows with the "DoNotDisableKeyboardInput" flag, we can safely enable input
			ImGuiIV::DisableKeyboardInput = ImGuiIV::ActiveScriptWindows != windowsWithDoNotDisableKeyboardInputFlag;
		}
		
		m_bDidResetInputStates = false;
	}
	else
	{
		if (!m_bDidResetInputStates)
		{
			// No longer draw mouse cursor
			io.MouseDrawCursor = false;

			// Reset all
			ImGuiIV::DisableMouseInput = false;
			ImGuiIV::DisableKeyboardInput = false;

			m_bDidResetInputStates = true;
		}
	}

	// End ImGui Frame and draw
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}


void ImGuiDraw::OnBeforeD3D9DeviceReset(IDirect3DDevice9* d3d9Device)
{
	WRITE_TO_DEBUG_OUTPUT("A D3D9 device reset is about to happen.");

	// Initialize ImGui if not initialized yet
	InitializeImGui(d3d9Device);

	// Invalidate device objects for ImGui
	ImGui_ImplDX9_InvalidateDeviceObjects();
}
void ImGuiDraw::OnAfterD3D9DeviceReset()
{
	WRITE_TO_DEBUG_OUTPUT("The D3D9 device was reset.");

	// Create device objects for ImGui
	ImGui_ImplDX9_CreateDeviceObjects();
}