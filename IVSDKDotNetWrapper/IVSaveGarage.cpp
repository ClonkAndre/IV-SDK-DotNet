#include "pch.h"
#include "IVSaveGarage.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVSaveGarage::IVSaveGarage(CSaveGarage* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeSaveGarage = nativePtr;
	}

	// - - - Methods / Functions - - -
	void IVSaveGarage::CopyGarageIntoSaveGarage(IVGarage^ pGarage)
	{
		NULLPTR_CHECK(NativeSaveGarage);
		NULLPTR_CHECK(pGarage);
		NativeSaveGarage->CopyGarageIntoSaveGarage(pGarage->NativeGarage);
	}
	void IVSaveGarage::CopyGarageOutOfSaveGarage(IVGarage^ pGarage)
	{
		NULLPTR_CHECK(NativeSaveGarage);
		NULLPTR_CHECK(pGarage);
		NativeSaveGarage->CopyGarageOutOfSaveGarage(pGarage->NativeGarage);
	}

}


