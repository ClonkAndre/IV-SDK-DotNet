#include "pch.h"
#include "IVCustomShaderEffectBase.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVCustomShaderEffectBase::IVCustomShaderEffectBase(CCustomShaderEffectBase* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeCustomShaderEffectBase = nativePtr;
	}

	// - - - Methods / Functions - - -
	void IVCustomShaderEffectBase::Update(IVEntity^ attachedEntity)
	{
		NULLPTR_CHECK(NativeCustomShaderEffectBase);
		NULLPTR_CHECK(attachedEntity);
		NULLPTR_CHECK(attachedEntity->NativeEntity);

		NativeCustomShaderEffectBase->Update(attachedEntity->NativeEntity);
	}

}