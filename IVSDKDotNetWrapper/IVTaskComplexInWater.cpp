#include "pch.h"
#include "IVTaskComplexInWater.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVTaskComplexInWater::IVTaskComplexInWater(CTaskComplexInWater* nativePtr) : IVTaskComplex(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeTask = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVTaskComplexInWater^ IVTaskComplexInWater::Create(uint32_t unk, uint32_t unk2, bool bUnk)
	{
		CTaskComplexInWater* ptr = new CTaskComplexInWater(unk, unk2, bUnk);
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVTaskComplexInWater(ptr);
	}

}