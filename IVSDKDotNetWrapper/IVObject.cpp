#include "pch.h"
#include "IVObject.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVObject::IVObject(CObject* nativePtr) : IVPhysical(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeObject = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVObject^ IVObject::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVObject((CObject*)ptr.ToPointer());
	}
	UIntPtr IVObject::GetUIntPtr()
	{
		return UIntPtr(NativeObject);
	}

}