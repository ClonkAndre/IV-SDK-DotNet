#include "ManagedMinHook.h"
#include "pch.h"

namespace IVSDKDotNet
{
	namespace Hooking
	{

		eMinHookStatus ManagedMinHook::CreateHook(uint32_t address, Delegate^ detour, [OutAttribute] IntPtr% pOriginal)
		{
			if (address == NULL)
			{
				pOriginal = IntPtr::Zero;
				return eMinHookStatus::MH_ERROR_NOT_EXECUTABLE;
			}
			if (!detour)
				throw gcnew ArgumentNullException("detour");

			IntPtr detourPtr = Marshal::GetFunctionPointerForDelegate(detour);

			// Create the hook
			void* pOrig;
			eMinHookStatus result = (eMinHookStatus)MH_CreateHook((LPVOID*)address, detourPtr.ToPointer(), (void**)&pOrig);
			pOriginal = IntPtr(pOrig);

			// Register the hook to the current script
			if (result == eMinHookStatus::MH_OK)
			{
				Assembly^ assembly = Assembly::GetCallingAssembly();
				GetManagerScript()->MinHook_RegisterHook(assembly == nullptr ? nullptr : assembly->GetName()->Name->Replace(".ivsdk", ""), address);
			}

			return result;
		}

		generic <typename TDelegate> where TDelegate : Delegate
		eMinHookStatus ManagedMinHook::CreateHook(uint32_t address, Delegate^ detour, [OutAttribute] TDelegate% pOriginal)
		{
			if (address == NULL)
			{
				pOriginal = TDelegate();
				return eMinHookStatus::MH_ERROR_NOT_EXECUTABLE;
			}
			if (!detour)
			{
				pOriginal = TDelegate();
				throw gcnew ArgumentNullException("detour");
			}

			IntPtr detourPtr = Marshal::GetFunctionPointerForDelegate(detour);

			// Create the hook
			void* pOrig;
			eMinHookStatus result = (eMinHookStatus)MH_CreateHook((LPVOID*)address, detourPtr.ToPointer(), (void**)&pOrig);
			
			// Check if hook was successful
			if (result == eMinHookStatus::MH_OK)
			{
				// Create delegate for original function and return it
				if (pOrig)
					pOriginal = Marshal::GetDelegateForFunctionPointer<TDelegate>(IntPtr(pOrig));
				else
					pOriginal = TDelegate();

				// Register the hook to the current script
				Assembly^ assembly = Assembly::GetCallingAssembly();
				GetManagerScript()->MinHook_RegisterHook(assembly == nullptr ? nullptr : assembly->GetName()->Name->Replace(".ivsdk", ""), address);
			}
			else
			{
				pOriginal = TDelegate();
			}

			return result;
		}

		eMinHookStatus ManagedMinHook::EnableHook(uint32_t address)
		{
			if (address == MH_ALL_HOOKS)
				return eMinHookStatus::MH_ERROR_NOT_EXECUTABLE;

			return (eMinHookStatus)(int)MH_EnableHook((LPVOID*)address);
		}
		eMinHookStatus ManagedMinHook::DisableHook(uint32_t address)
		{
			if (address == MH_ALL_HOOKS)
				return eMinHookStatus::MH_ERROR_NOT_EXECUTABLE;

			return (eMinHookStatus)(int)MH_DisableHook((LPVOID*)address);
		}

	}
}