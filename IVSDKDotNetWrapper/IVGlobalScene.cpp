#include "pch.h"
#include "IVGlobalScene.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVGlobalScene::IVGlobalScene(tGlobalScene* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeGlobalScene = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVGlobalScene IVGlobalScene::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, IVGlobalScene());
		return IVGlobalScene((tGlobalScene*)ptr.ToPointer());
	}
	UIntPtr IVGlobalScene::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene, UIntPtr::Zero);
		return UIntPtr(NativeGlobalScene);
	}
}