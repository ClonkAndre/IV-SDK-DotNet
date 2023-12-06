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
}