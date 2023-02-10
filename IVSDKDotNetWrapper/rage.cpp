#include "pch.h"
#include "rage.h"

namespace IVSDKDotNet {

	IntPtr RAGE::GetHWND()
	{
		return IntPtr(Native_RAGE::GetHWND());
	}
	IntPtr RAGE::GetDirect3DDevice9()
	{
		return IntPtr(Native_RAGE::GetDirect3DDevice9());
	}

	uint32_t RAGE::atStringHash(String^ sString)
	{
		msclr::interop::marshal_context ctx;
		return Native_RAGE::atStringHash(ctx.marshal_as<const char*>(sString));
	}

}