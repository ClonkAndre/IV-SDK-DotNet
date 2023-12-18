#include "pch.h"
#include "IVBuilding.h"

namespace IVSDKDotNet
{
	
	// - - - Constructor - - -
	IVBuilding::IVBuilding(CBuilding* nativePtr) : IVEntity(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeBuilding = nativePtr;
	}

	// - - - Methods / Funcions - - -
	void IVBuilding::ReplaceWithNewModel(int32_t index)
	{
		NULLPTR_CHECK(NativeBuilding);
		NativeBuilding->ReplaceWithNewModel(index);
	}

}