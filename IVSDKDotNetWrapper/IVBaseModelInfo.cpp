#include "pch.h"
#include "IVBaseModelInfo.h"

namespace IVSDKDotNet
{


	IVTimeInfo::IVTimeInfo(CTimeInfo* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeTimeInfo = nativePtr;
	}


	// - - - Constructor - - -
	IVBaseModelInfo::IVBaseModelInfo(CBaseModelInfo* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeModelInfo = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVBaseModelInfo^ IVBaseModelInfo::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVBaseModelInfo((CBaseModelInfo*)ptr.ToPointer());
	}
	UIntPtr IVBaseModelInfo::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, UIntPtr::Zero);
		return UIntPtr(NativeModelInfo);
	}

	uint8_t IVBaseModelInfo::GetModelType()
	{
		NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, 0);
		return NativeModelInfo->GetModelType();
	}
	IVTimeInfo^ IVBaseModelInfo::GetTimeInfo()
	{
		NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, nullptr);
		return gcnew IVTimeInfo(NativeModelInfo->GetTimeInfo());
	}
	void IVBaseModelInfo::SetAnimGroup(String^ group)
	{
		NULLPTR_CHECK(NativeModelInfo);
		CHECK_NULL_OR_WHITESPACE_STRING(group);
		msclr::interop::marshal_context ctx;
		NativeModelInfo->SetAnimGroup((char*)ctx.marshal_as<const char*>(group));
	}
	void IVBaseModelInfo::SetTexDictionary(String^ txd)
	{
		NULLPTR_CHECK(NativeModelInfo);
		CHECK_NULL_OR_WHITESPACE_STRING(txd);
		msclr::interop::marshal_context ctx;
		NativeModelInfo->SetTexDictionary((char*)ctx.marshal_as<const char*>(txd));
	}

}