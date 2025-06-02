#pragma once

namespace IVSDKDotNet
{
	namespace Native
	{
		/// <summary>
		/// This class gives you the possiblity to manually call native functions by their name.
		/// This works by using reflection to find the method by its name and then calling it.
		/// Disadvantage of this is that you can only call functions which actually exist in the Natives class.
		/// </summary>
		public ref class Function
		{
		internal:
			static void Init();

			generic <typename T>
			static T ConvertResult(Object^ result);

		public:
			/// <summary>
			/// Calls a native function by name and returns the result the native returned.
			/// </summary>
			/// <typeparam name="T">The return type of the native.</typeparam>
			/// <param name="name">The name of the native function to call.</param>
			/// <param name="args">The arguments of the native function.</param>
			/// <returns>The result of the called native function.</returns>
			generic <typename T>
			static T Call(String^ name, ...array<Object^>^ args);

			/// <summary>
			/// Calls a native function by name.
			/// </summary>
			/// <param name="name">The name of the native function to call.</param>
			/// <param name="args">The arguments of the native function.</param>
			static void Call(String^ name, ...array<Object^>^ args);

		private:
			static Dictionary<uint32_t, List<MethodInfo^>^>^ natives;

		};

		/// <summary>
		/// The new native caller which is more direct and also faster.
		/// </summary>
		public ref class FunctionV2
		{
		public:
			generic <typename T>
			static T Call(uint32_t hash, ...array<NativeArg>^ args);
			static void Call(uint32_t hash, ...array<NativeArg>^ args);

			generic <typename T>
			static T Call(eNativeHash hash, ...array<NativeArg>^ args);
			static void Call(eNativeHash hash, ...array<NativeArg>^ args);

		};
	}
}