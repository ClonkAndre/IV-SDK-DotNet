#include "pch.h"
#include "IVBaseModelInfo.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVBaseModelInfo::IVBaseModelInfo(CBaseModelInfo* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeModelInfo = nativePtr;
	}

	// - - - Methods / Functions - - -
	uint8_t IVBaseModelInfo::GetModelType()
	{
		NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, 0);
		return NativeModelInfo->GetModelType();
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