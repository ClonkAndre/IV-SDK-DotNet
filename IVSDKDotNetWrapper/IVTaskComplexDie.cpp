#include "pch.h"
#include "IVTaskComplexDie.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVTaskComplexDie::IVTaskComplexDie(CTaskComplexDie* nativePtr) : IVTaskComplex(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeTask = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVTaskComplexDie^ IVTaskComplexDie::Create(uint32_t unk, uint32_t unk2, uint32_t unk3_44, uint32_t unk4_190, float fBlendDelta, float fAnimSpeed, uint32_t unk5_1)
	{
		CTaskComplexDie* ptr = new CTaskComplexDie(unk, unk2, unk3_44, unk4_190, fBlendDelta, fAnimSpeed, unk5_1);
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVTaskComplexDie(ptr);
	}

}