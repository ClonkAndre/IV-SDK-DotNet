#include "pch.h"
#include "IVAudConfig.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVAudConfig::IVAudConfig(audConfig* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeAudConfig = nativePtr;
	}

	// - - - Methods / Functions - - -
	void IVAudConfig::LoadFromFile(String^ path)
	{
		NULLPTR_CHECK(NativeAudConfig);

		if (String::IsNullOrWhiteSpace(path))
			return;

		msclr::interop::marshal_context ctx;
		NativeAudConfig->LoadFromFile((char*)ctx.marshal_as<const char*>(path));
	}
	UIntPtr IVAudConfig::GetUIntPtr()
	{
		return UIntPtr(NativeAudConfig);
	}

}