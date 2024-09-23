#pragma once

namespace IVSDKDotNet
{
	namespace Hooking
	{

		public ref class Patterns
		{
		public:

			/// <summary>
			/// Scans for the given pattern at the given module and returns the address.
			/// </summary>
			/// <param name="pattern">The pattern to scan for.</param>
			/// <param name="index">Get the match at that index.</param>
			/// <param name="offset">Offset for the pattern.</param>
			/// <returns>The address from the given pattern.</returns>
			static UIntPtr GetAddress(IntPtr moduleAddress, String^ pattern, uint32_t index, uint32_t offset);

			/// <summary>
			/// Scans for the given pattern and returns the address.
			/// </summary>
			/// <param name="pattern">The pattern to scan for.</param>
			/// <param name="index">Get the match at that index.</param>
			/// <param name="offset">Offset for the pattern.</param>
			/// <returns>The address from the given pattern.</returns>
			static UIntPtr GetAddress(String^ pattern, uint32_t index, uint32_t offset);

		};

	}
}