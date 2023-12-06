#include "pch.h"
#include "rage.h"

namespace IVSDKDotNet
{

	// - - - Methods / Functions - - -
	IntPtr RAGE::GetHWND()
	{
		return IntPtr(rage::g_pHWND);
	}
	IntPtr RAGE::GetDirect3DDevice9()
	{
		return IntPtr(rage::g_pDirect3DDevice);
	}

	uint32_t RAGE::AtStringHash(String^ sString)
	{
		msclr::interop::marshal_context ctx;
		return rage::atStringHash(ctx.marshal_as<const char*>(sString));
	}
	uint32_t RAGE::AtStringHash(String^ sString, UIntPtr nExistingHash)
	{
		msclr::interop::marshal_context ctx;
		return rage::atStringHash(ctx.marshal_as<const char*>(sString), (uint32_t*)nExistingHash.ToPointer());
	}

}