#include "pch.h"
#include "Native.h"
#include "Scripts.h"

using namespace IVSDKDotNet::Manager;

namespace IVSDKDotNet {
	namespace Manager {

		// =========================================================================
		// ============================= ManagerScript =============================
		// =========================================================================
		ManagerScript::ManagerScript()
		{
			if (ManagerScript::s_Instance) delete this; // There is already a instance of the ManagerScript class. Delete this class.
		}

		void ManagerScript::Debug_ShowMessageBox(String^ str)		{ SHOW_MESSAGE(str); }
		void ManagerScript::Debug_ShowInfoMessageBox(String^ str)	{ SHOW_INFO_MESSAGE(str); }
		void ManagerScript::Debug_ShowWarnMessageBox(String^ str)	{ SHOW_WARN_MESSAGE(str); }
		void ManagerScript::Debug_ShowErrorMessageBox(String^ str)	{ SHOW_ERROR_MESSAGE(str); }

	}

	// =========================================================================
	// ================================== Script ===============================
	// =========================================================================
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
			return ManagerScript::s_Instance->StartNewTask(this->ID, funcToExecute);

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
		if (ManagerScript::s_Instance) ManagerScript::s_Instance->WaitInTask(id, waitTimeInMilliseconds);
	}

	void Script::ShowSubtitleMessage(String^ str, uint32_t time)
	{
		IVSDKDotNet::Native::Natives::PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", str, time, true);
	}
	void Script::ShowSubtitleMessage(String^ str)
	{
		IVSDKDotNet::Native::Natives::PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", str, 2000, true);
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

}