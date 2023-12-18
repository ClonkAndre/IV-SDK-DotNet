#include "pch.h"
#include "IVAudEngine.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVAudEngine::IVAudEngine(audEngine* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeAudEngine = nativePtr;
	}

	// - - - Methods / Functions - - -
	void IVAudEngine::SetUnknown(float unk1)
	{
		NULLPTR_CHECK(NativeAudEngine);
		NativeAudEngine->SetUnknown(unk1);
	}

}