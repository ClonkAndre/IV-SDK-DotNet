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
		if (Manager::ManagerScript::s_Instance) return Manager::ManagerScript::s_Instance->ExecuteConsoleCommand(name);
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
#pragma endregion

}