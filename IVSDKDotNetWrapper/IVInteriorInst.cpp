#include "pch.h"
#include "IVInteriorInst.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVInteriorInst::IVInteriorInst(CInteriorInst* nativePtr) : IVBuilding(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NaiveInteriorInst = nativePtr;
	}
}