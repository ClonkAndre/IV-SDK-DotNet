#include "pch.h"
#include "CGame.h"

namespace IVSDKDotNet {

#pragma region Console
	void CGame::Console::Open()
	{
		if (Manager::ManagerScript::s_Instance) Manager::ManagerScript::s_Instance->OpenConsole();
	}
	void CGame::Console::Close()
	{
		if (Manager::ManagerScript::s_Instance) Manager::ManagerScript::s_Instance->CloseConsole();
	}
	void CGame::Console::Clear()
	{
		if (Manager::ManagerScript::s_Instance) Manager::ManagerScript::s_Instance->ClearConsole();
	}

	void CGame::Console::Print(String^ str)
	{
		if (Manager::ManagerScript::s_Instance) Manager::ManagerScript::s_Instance->PrintToConsole(str);
	}
	void CGame::Console::PrintDebug(String^ str)
	{
#ifndef NDEBUG
		if (Manager::ManagerScript::s_Instance) Manager::ManagerScript::s_Instance->PrintDebugToConsole(str);
#endif
	}
	void CGame::Console::PrintWarning(String^ str)
	{
		if (Manager::ManagerScript::s_Instance) Manager::ManagerScript::s_Instance->PrintWarnToConsole(str);
	}
	void CGame::Console::PrintError(String^ str)
	{
		if (Manager::ManagerScript::s_Instance) Manager::ManagerScript::s_Instance->PrintErrorToConsole(str);
	}

	bool CGame::Console::RegisterCommand(Script^ addFor, String^ name, Action<array<String^>^>^ actionToExecute)
	{
		if (!addFor)
			return false;
		if (!Manager::ManagerScript::s_Instance)
			return false;
			
		return Manager::ManagerScript::s_Instance->RegisterConsoleCommand(addFor->ID, name, actionToExecute);
	}
	bool CGame::Console::ExecuteCommand(String^ name)
	{
		if (Manager::ManagerScript::s_Instance)
			return Manager::ManagerScript::s_Instance->ExecuteConsoleCommand(name);

		return false;
	}
#pragma endregion

#pragma region CGame
	bool CGame::Initialise(String^ sGameDat)
	{
		msclr::interop::marshal_context ctx;
		return Native_CGame::Initialise(ctx.marshal_as<const char*>(sGameDat));
	}

	bool CGame::IsKeyPressed(Keys key)
	{
		return Helper::IsKeyPressedAsync(key);
	}

	RectangleF CGame::GetRadarRectangle(eFontScaling scaling)
	{
		float w = float(CGame::Resolution.Width);
		float h = float(CGame::Resolution.Height);
		float pixel = System::Math::Min(w * 0.156f, h * 0.2f);
		RectangleF rect;

		rect.Width  = Helper::Drawing::ConvertX(pixel, w, eFontScaling::Pixel, scaling);
		rect.Height = Helper::Drawing::ConvertY(pixel, h, eFontScaling::Pixel, scaling);
		rect.X = rect.Width * 0.45f;
		if (CGame::Resolution.Width >= CGame::Resolution.Height)
			rect.Y = Helper::Drawing::ConvertY(0.75f, h, eFontScaling::ScreenUnits, scaling);
		else
			rect.Y = Helper::Drawing::ConvertY(h - pixel - h * 0.05f, h, eFontScaling::Pixel, scaling);

		return rect;
	}
	RectangleF CGame::GetRadarRectangle()
	{
		return CGame::GetRadarRectangle(eFontScaling::Pixel);
	}

	void CGame::ShowSubtitleMessage(String^ str, uint32_t time)
	{
		IVSDKDotNet::Native::Natives::PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", str, time, true);
	}
	void CGame::ShowSubtitleMessage(String^ str)
	{
		ShowSubtitleMessage(str, 2000);
	}
#pragma endregion

}