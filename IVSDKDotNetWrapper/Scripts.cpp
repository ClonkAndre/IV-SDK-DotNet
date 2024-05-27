#include "pch.h"
#include "Native.h"
#include "Scripts.h"

using namespace IVSDKDotNet::Manager;

namespace IVSDKDotNet
{
	namespace Manager
	{

		// =========================================================================
		// ============================= ManagerScript =============================
		// =========================================================================
		ManagerScript::ManagerScript()
		{
			// If there already is a instance of the ManagerScript class. Delete this class.
			if (ManagerScript::s_Instance)
				delete this;
		}

		void ManagerScript::Debug_ShowMessageBox(String^ str)		{ SHOW_MESSAGE(str); }
		void ManagerScript::Debug_ShowInfoMessageBox(String^ str)	{ SHOW_INFO_MESSAGE(str); }
		void ManagerScript::Debug_ShowWarnMessageBox(String^ str)	{ SHOW_WARN_MESSAGE(str); }
		void ManagerScript::Debug_ShowErrorMessageBox(String^ str)	{ SHOW_ERROR_MESSAGE(str); }

	}

	// =========================================================================
	// ================================== Script ===============================
	// =========================================================================
	Script::Script(Guid id)
	{
		ID = id;
	}
	Script::Script()
	{
		AssembliesLocation = eAssembliesLocation::GameRootDirectory;
		CustomAssembliesPath = String::Empty;
		ScriptDomain = AppDomain::CurrentDomain;
		ID = Guid::NewGuid();
	}

	Guid Script::StartNewTask(Func<Object^>^ funcToExecute)
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->StartNewTask(this->ID, funcToExecute, nullptr);

		return Guid::Empty;
	}
	Guid Script::StartNewTask(Func<Object^>^ funcToExecute, Action<Object^>^ continueWithAction)
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->StartNewTask(this->ID, funcToExecute, continueWithAction);

		return Guid::Empty;
	}

	Guid Script::StartNewTimer(int interval, Action^ actionToExecute)
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->StartNewTimer(this->ID, interval, actionToExecute);

		return Guid::Empty;
	}

	void Script::WaitInTask(Guid id, int waitTimeInMilliseconds)
	{
		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->WaitInTask(id, waitTimeInMilliseconds);
	}

	void Script::AbortTaskOrTimer(Guid id)
	{
		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->AbortTaskOrTimer(id);
	}
	void Script::ChangeTimerState(Guid id, bool pause)
	{
		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->ChangeTimerState(id, pause);
	}
	void Script::ChangeTimerInterval(Guid id, int interval)
	{
		if (ManagerScript::s_Instance)
			ManagerScript::s_Instance->ChangeTimerInterval(id, interval);
	}

	void Script::ShowSubtitleMessage(String^ str, uint32_t time)
	{
		IVSDKDotNet::Native::Natives::PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", str, time, true);
	}
	void Script::ShowSubtitleMessage(String^ str, ...array<System::Object^>^ args)
	{
		ShowSubtitleMessage(String::Format(str, args), 3000);
	}
	void Script::ShowSubtitleMessage(String^ str)
	{
		ShowSubtitleMessage(str, 2000);
	}

	bool Script::IsKeyPressed(Keys key)
	{
		return Helper::IsKeyPressedAsync(key);
	}
	bool Script::Abort()
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->AbortScript(ID);
		
		return false;
	}

	bool Script::RegisterConsoleCommand(String^ name, Action<array<String^>^>^ actionToExecute)
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->RegisterConsoleCommand(ID, name, actionToExecute);

		return false;
	}

	bool Script::RegisterPhoneNumber(String^ number, Action^ dialingAction)
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->RegisterPhoneNumber(ID, number, dialingAction);

		return false;
	}
	bool Script::UnregisterPhoneNumber(String^ number)
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->UnregisterPhoneNumber(ID, number);

		return false;
	}

	String^ Script::GetName()
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->GetScriptName(this->ID);

		return String::Empty;
	}
	String^ Script::GetFullPath()
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->GetScriptFullPath(this->ID);

		return String::Empty;
	}

	bool Script::DoesScriptExists(Guid id)
	{
		return GetScript(id) != nullptr;
	}
	bool Script::DoesScriptExists(String^ name)
	{
		return GetScript(name) != nullptr;
	}

	bool Script::IsScriptRunning(Guid id)
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->IsScriptRunning(id);

		return false;
	}
	bool Script::IsScriptRunning(String^ name)
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->IsScriptRunning(name);

		return false;
	}

	Script^ Script::GetScript(Guid id)
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->GetScript(id);

		return nullptr;
	}
	Script^ Script::GetScript(String^ name)
	{
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->GetScript(name);

		return nullptr;
	}

	bool Script::SendScriptCommand(Script^ toScript, String^ command, array<Object^>^ parameters, [OutAttribute] Object^% result)
	{
		if (!toScript)
			return false;
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->SendScriptCommand(ID, toScript->ID, command, parameters, result);

		result = nullptr;
		return false;
	}
	bool Script::SendScriptCommand(Guid toScript, String^ command, array<Object^>^ parameters, [OutAttribute] Object^% result)
	{
		if (toScript == Guid::Empty)
			return false;
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->SendScriptCommand(ID, toScript, command, parameters, result);

		result = nullptr;
		return false;
	}
	bool Script::SendScriptCommand(String^ toScript, String^ command, array<Object^>^ parameters, [OutAttribute] Object^% result)
	{
		if (!toScript)
			return false;
		if (ManagerScript::s_Instance)
			return ManagerScript::s_Instance->SendScriptCommand(ID, toScript, command, parameters, result);

		result = nullptr;
		return false;
	}

}