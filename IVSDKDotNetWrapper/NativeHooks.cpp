#include "pch.h"
#include "NativeHooks.h"

namespace IVSDKDotNet
{
	namespace Native
	{

		// - - - - - Hooks - - - - -
		// - - - Methods / Functions - - -
		void Hooks::Initialize()
		{
			if (Initialized)
				return;

			installedHooks = gcnew List<InstalledHook^>();
		}
		void Hooks::Cleanup()
		{
			// Uninstall all hooks
			for (int i = 0; i < installedHooks->Count; i++)
			{
				InstalledHook^ hook = installedHooks[i];

				// Uninstall hook
				hook->Unhook();
			}
			installedHooks->Clear();
		}

		Hooks::InstalledHook^ Hooks::FindInstalledHook(eNativeHash byNativeHash)
		{
			for (int i = 0; i < installedHooks->Count; i++)
			{
				InstalledHook^ hook = installedHooks[i];

				// Try find hook
				if (hook->NativeHash == byNativeHash)
					return hook;
			}

			return nullptr;
		}
		void Hooks::AddHook(InstalledHook^ hook)
		{
			if (!hook)
				return;

			installedHooks->Add(hook);
		}
		bool Hooks::VerifyHooks()
		{
			int verifiedHooks = 0;

			for (int i = 0; i < installedHooks->Count; i++)
			{
				InstalledHook^ hook = installedHooks[i];

				if (hook->TrampolinePtr)
					verifiedHooks++;
			}

			return verifiedHooks >= installedHooks->Count;
		}

		// - - - - - NativeHookFunctions - - - - -
	    // - - - Methods / Functions - - -
		bool NativeHookFunctions::Initialize()
		{
			if (Hooks::Initialized)
				return false;

			DoHooking();

			Hooks::Initialized = true;
			return Hooks::VerifyHooks();
		}
		void NativeHookFunctions::DoHooking()
		{
			// - NATIVE_PRINTSTRING - 
			Hooks::AddHook(gcnew Hooks::InstalledHook(eNativeHash::NATIVE_PRINTSTRING, (DWORD)NATIVE_PRINTSTRING));

			// - NATIVE_PRINTINT - 
			Hooks::AddHook(gcnew Hooks::InstalledHook(eNativeHash::NATIVE_PRINTINT, (DWORD)NATIVE_PRINTINT));

			// - NATIVE_PRINTFLOAT -
			Hooks::AddHook(gcnew Hooks::InstalledHook(eNativeHash::NATIVE_PRINTFLOAT, (DWORD)NATIVE_PRINTFLOAT));

			// - NATIVE_SHOW_SIGNIN_UI -
			Hooks::AddHook(gcnew Hooks::InstalledHook(eNativeHash::NATIVE_SHOW_SIGNIN_UI, (DWORD)NATIVE_SHOW_SIGNIN_UI));

			// - NATIVE_NETWORK_SHOW_FRIEND_PROFILE_UI -
			Hooks::AddHook(gcnew Hooks::InstalledHook(eNativeHash::NATIVE_NETWORK_SHOW_FRIEND_PROFILE_UI, (DWORD)NATIVE_NETWORK_SHOW_FRIEND_PROFILE_UI));

			// - NATIVE_AWARD_ACHIEVEMENT -
			Hooks::AddHook(gcnew Hooks::InstalledHook(eNativeHash::NATIVE_AWARD_ACHIEVEMENT, (DWORD)NATIVE_AWARD_ACHIEVEMENT));

			// - NATIVE_ENABLE_CHASE_AUDIO -
			Hooks::AddHook(gcnew Hooks::InstalledHook(eNativeHash::NATIVE_ENABLE_CHASE_AUDIO, (DWORD)NATIVE_ENABLE_CHASE_AUDIO));
		}

		void NativeHookFunctions::NATIVE_PRINTSTRING(IVNativeCallContext* pNativeContext)
		{
			char* result = pNativeContext->GetArgument<char*>(0);

			// Raise event
			Hooks::RaisePrintStringHook(gcnew String(result));
		}
		void NativeHookFunctions::NATIVE_PRINTINT(IVNativeCallContext* pNativeContext)
		{
			int result = pNativeContext->GetArgument<int>(0);

			// Raise event
			Hooks::RaisePrintIntHook(result);
		}
		void NativeHookFunctions::NATIVE_PRINTFLOAT(IVNativeCallContext* pNativeContext)
		{
			float result = pNativeContext->GetArgument<float>(0);

			// Raise event
			Hooks::RaisePrintFloatHook(result);
		}

		void NativeHookFunctions::NATIVE_SHOW_SIGNIN_UI(IVNativeCallContext* pNativeContext)
		{
			// Raise event
			bool shouldReturn = Hooks::RaiseShowSignInUIHook();

			if (shouldReturn)
				return;

			// Unhook
			Hooks::InstalledHook^ hook = Hooks::FindInstalledHook(eNativeHash::NATIVE_SHOW_SIGNIN_UI);

			if (!hook)
				return;

			hook->Unhook();

			// Call orginal native
			Natives::SHOW_SIGNIN_UI();

			// Hook
			hook->Hook();
		}
		void NativeHookFunctions::NATIVE_NETWORK_SHOW_FRIEND_PROFILE_UI(IVNativeCallContext* pNativeContext)
		{
			char* result = pNativeContext->GetArgument<char*>(0);
			String^ str = gcnew String(result);

			// Raise event
			bool shouldReturn = Hooks::RaiseNetworkShowFriendProfileUIHook(str);

			if (shouldReturn)
				return;

			// Unhook
			Hooks::InstalledHook^ hook = Hooks::FindInstalledHook(eNativeHash::NATIVE_NETWORK_SHOW_FRIEND_PROFILE_UI);

			if (!hook)
				return;

			hook->Unhook();

			// Call orginal native
			Natives::NETWORK_SHOW_FRIEND_PROFILE_UI(str);

			// Hook
			hook->Hook();
		}

		void NativeHookFunctions::NATIVE_AWARD_ACHIEVEMENT(IVNativeCallContext* pNativeContext)
		{
			int result = pNativeContext->GetArgument<int>(0);

			// Raise event
			bool shouldReturn = Hooks::RaiseAwardAchievementHook(result);

			if (shouldReturn)
				return;

			// Unhook
			Hooks::InstalledHook^ hook = Hooks::FindInstalledHook(eNativeHash::NATIVE_AWARD_ACHIEVEMENT);

			if (!hook)
				return;

			hook->Unhook();

			// Call orginal native
			Natives::AWARD_ACHIEVEMENT(result);

			// Hook
			hook->Hook();
		}
		void NativeHookFunctions::NATIVE_ENABLE_CHASE_AUDIO(IVNativeCallContext* pNativeContext)
		{
			bool result = pNativeContext->GetArgument<bool>(0);

			// Raise event
			bool shouldReturn = Hooks::RaiseEnableChaseAudioHook(result);

			if (shouldReturn)
				return;
			
			// Unhook
			Hooks::InstalledHook^ hook = Hooks::FindInstalledHook(eNativeHash::NATIVE_ENABLE_CHASE_AUDIO);

			if (!hook)
				return;

			hook->Unhook();

			// Call orginal native
			Natives::ENABLE_CHASE_AUDIO(result);

			// Hook
			hook->Hook();
		}

	}
}