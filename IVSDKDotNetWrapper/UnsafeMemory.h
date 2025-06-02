#pragma once
#include "pch.h"

namespace IVSDKDotNet
{
	namespace Internal
	{
		public ref class UnsafeMemory
		{
		public:

			static IntPtr MemoryCopy(IntPtr dest, IntPtr source, uint32_t size)
			{
				return IntPtr(memcpy(dest.ToPointer(), source.ToPointer(), size));
			}

		};
	}
}