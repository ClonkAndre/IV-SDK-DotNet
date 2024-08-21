#include "pch.h"
#include "IVGame.h"

namespace IVSDKDotNet
{

	// - - - Methods / Functions - - -
	void IVGame::Console::Open()
	{
		if(Manager::ManagerScript::s_Instance)
			Manager::ManagerScript::s_Instance->OpenConsole();
	}
	void IVGame::Console::Close()
	{
		if(Manager::ManagerScript::s_Instance)
			Manager::ManagerScript::s_Instance->CloseConsole();
	}
	void IVGame::Console::Clear()
	{
		if(Manager::ManagerScript::s_Instance)
			Manager::ManagerScript::s_Instance->ClearConsole();
	}
	void IVGame::Console::Print(String^ str)
	{
		Logger::Log(str);
	}
	void IVGame::Console::PrintDebug(String^ str)
	{
#if _DEBUG
		Logger::LogDebug(str);
#endif
	}
	void IVGame::Console::PrintWarning(String^ str)
	{
		Logger::LogWarning(str);
	}
	void IVGame::Console::PrintError(String^ str)
	{
		Logger::LogError(str);
	}
	bool IVGame::Console::RegisterCommand(Script^ addFor, String^ name, Action<array<String^>^>^ actionToExecute)
	{
		if(!addFor)
			return false;
		if(!Manager::ManagerScript::s_Instance)
			return false;

		return Manager::ManagerScript::s_Instance->RegisterConsoleCommand(addFor->ID, name, actionToExecute);
	}
	bool IVGame::Console::ExecuteCommand(String^ name)
	{
		if(Manager::ManagerScript::s_Instance)
			return Manager::ManagerScript::s_Instance->ExecuteConsoleCommand(name);

		return false;
	}

	bool IVGame::Initialise(String^ sGameDat)
	{
		CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(sGameDat, false);
		msclr::interop::marshal_context ctx;
		return CGame::Initialise(ctx.marshal_as<const char*>(sGameDat));
	}
	bool IVGame::IsInFocus()
	{
		if(Manager::ManagerScript::s_Instance)
			return Manager::ManagerScript::s_Instance->IsGameInFocus();

		return false;
	}
	bool IVGame::IsKeyPressed(Keys key)
	{
		return Helper::IsKeyPressedAsync(key);
	}

	void IVGame::ShowSubtitleMessage(String^ str, uint32_t time)
	{
		IVSDKDotNet::Native::Natives::PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", str, time, true);
	}
	void IVGame::ShowSubtitleMessage(String^ str)
	{
		ShowSubtitleMessage(str, 2000);
	}
	void IVGame::ShowSubtitleMessageEx(String^ str, ...array<System::Object^>^ args)
	{
		ShowSubtitleMessage(String::Format(str, args), 3000);
	}

	RectangleF IVGame::GetRadarRectangle(eFontScaling scaling)
	{
		Size res = Resolution;

		float w = float(res.Width);
		float h = float(res.Height);
		float pixel = System::Math::Min(w * 0.156f, h * 0.2f);
		RectangleF rect;

		rect.Width = Helper::Drawing::ConvertX(pixel, w, eFontScaling::Pixel, scaling);
		rect.Height = Helper::Drawing::ConvertY(pixel, h, eFontScaling::Pixel, scaling);
		rect.X = rect.Width * 0.45f;
		if (res.Width >= res.Height)
			rect.Y = Helper::Drawing::ConvertY(0.75f, h, eFontScaling::ScreenUnits, scaling);
		else
			rect.Y = Helper::Drawing::ConvertY(h - pixel - h * 0.05f, h, eFontScaling::Pixel, scaling);

		return rect;
	}
	RectangleF IVGame::GetRadarRectangle()
	{
		return GetRadarRectangle(eFontScaling::Pixel);
	}

}