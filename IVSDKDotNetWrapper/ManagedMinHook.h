#pragma once

namespace IVSDKDotNet
{
	namespace Hooking
	{
		public ref class ManagedMinHook
		{
		public:

			/// <summary>
			/// Creates a Hook for the specified target function, in disabled state.
			/// </summary>
			/// <param name="address">A pointer to the target function, which will be overridden by the detour function.</param>
			/// <param name="detour">A pointer to the detour function, which will override the target function.</param>
			/// <param name="pOriginal">A pointer to the trampoline function, which will be used to call the original target function. This parameter can be NULL.</param>
			/// <returns>A MinHook status code containing information about the operation.</returns>
			static eMinHookStatus CreateHook(uint32_t address, Delegate^ detour, [OutAttribute] IntPtr% pOriginal);

			/// <summary>
			/// Creates a Hook for the specified target function, in disabled state.
			/// </summary>
			/// <param name="address">A pointer to the target function, which will be overridden by the detour function.</param>
			/// <param name="detour">A pointer to the detour function, which will override the target function.</param>
			/// <param name="pOriginal">A delegate which is the original target function. This parameter can be NULL.</param>
			/// <returns>A MinHook status code containing information about the operation.</returns>
			generic <typename TDelegate> where TDelegate : Delegate
			static eMinHookStatus CreateHook(uint32_t address, Delegate^ detour, [OutAttribute] TDelegate% pOriginal);

			/// <summary>
			/// Enables an already created hook.
			/// </summary>
			/// <param name="address">A pointer to the target function.</param>
			/// <returns>A MinHook status code containing information about the operation.</returns>
			static eMinHookStatus EnableHook(uint32_t address);

			/// <summary>
			/// Disables an already created hook.
			/// </summary>
			/// <param name="address">A pointer to the target function.</param>
			/// <returns>A MinHook status code containing information about the operation.</returns>
			static eMinHookStatus DisableHook(uint32_t address);

		};
	}
}