#include "pch.h"
#include "IVPad.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPad::IVPad(CPad* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePad = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVPad^ IVPad::GetPad()
	{
		CPad* ptr = CPad::GetPad();
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPad(ptr);
	}

}