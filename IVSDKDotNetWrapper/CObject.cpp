#include "pch.h"
#include "CObject.h"

namespace IVSDKDotNet {

	CObject::CObject(Native_CObject* nativePtr) : CPhysical(nativePtr)
	{
		ObjectPointer = nativePtr;
	}

	CObject^ CObject::FromPointer(UIntPtr ptr)
	{
		if (ptr == UIntPtr::Zero)
			return nullptr;

		return gcnew CObject((Native_CObject*)ptr.ToPointer());
	}
	UIntPtr CObject::GetUIntPtr()
	{
		if (!ObjectPointer)
			return UIntPtr::Zero;

		return UIntPtr(ObjectPointer);
	}

}