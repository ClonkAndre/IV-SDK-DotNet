#pragma once
#include "pch.h"

namespace IVSDKDotNet
{
	namespace Exceptions
	{

		/// <summary>
		/// Thrown when a native function could not be found by name.
		/// </summary>
		public ref class NativeNotFoundException : Exception
		{
		public:
			property String^ TheNativeName
			{
			public:
				String^ get()
				{
					return nativeName;
				}
			}

		public:
			NativeNotFoundException(String^ theNativeName) : Exception(String::Format("Could not find native function with name '{0}'!", theNativeName))
			{

			}

		private:
			String^ nativeName;
		};

	}
}