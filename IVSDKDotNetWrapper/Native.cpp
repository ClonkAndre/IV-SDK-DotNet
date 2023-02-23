#include "pch.h"
#include "Native.h"

namespace IVSDKDotNet {
	namespace Native {

		generic <typename T>
		void Function::Call(NativeHash nativeHash, ...array<T>^ params)
		{

		}

		generic <typename R, typename T>
		R Function::Call(NativeHash nativeHash, ...array<T>^ params)
		{
			return R();
		}

	}
}