#include "pch.h"
#include "IVViewport.h"

namespace IVSDKDotNet
{

	// - - - Constructors - - -
	IVViewport::IVViewport(CViewport* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeViewport = nativePtr;
	}

	IVViewportPrimaryOrtho::IVViewportPrimaryOrtho(CViewportPrimaryOrtho* nativePtr) : IVViewport(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeViewportPrimaryOrtho = nativePtr;
	}
	IVViewportGame::IVViewportGame(CViewportGame* nativePtr) : IVViewport(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeViewportGame = nativePtr;
	}
	IVViewportRadar::IVViewportRadar(CViewportRadar* nativePtr) : IVViewport(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeViewportRadar = nativePtr;
	}
	IVViewportMobilePhone::IVViewportMobilePhone(CViewportMobilePhone* nativePtr) : IVViewport(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeViewportMobilePhone = nativePtr;
	}

}