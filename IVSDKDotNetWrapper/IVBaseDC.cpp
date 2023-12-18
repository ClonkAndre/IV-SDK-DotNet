#include "pch.h"
#include "IVBaseDC.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVBaseDC::IVBaseDC(CBaseDC* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeBaseDC = nativePtr;
	}

	// - - - Methods / Functions - - -
	void IVBaseDC::Add()
	{
		NULLPTR_CHECK(NativeBaseDC);
		NativeBaseDC->Add();
	}

}