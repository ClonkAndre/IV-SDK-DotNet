#pragma once

namespace IVSDKDotNet
{
	namespace Internal
	{

		public ref class TlsHelper
		{
		public:
			/// <summary>
			/// Gets the current thread local storage context.
			/// </summary>
			static UIntPtr GetTlsContext();
			/// <summary>
			/// Sets the current thread local storage context.
			/// </summary>
			static void SetTlsContext(UIntPtr ctx);
		};

	}
}