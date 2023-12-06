#include "pch.h"
#include "IVCustomShaderEffectPedBoneDamageFX.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVCustomShaderEffectPedBoneDamageFX::IVCustomShaderEffectPedBoneDamageFX(CCustomShaderEffectPedBoneDamageFX* nativePtr)
		: IVCustomShaderEffectBase(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeCustomShaderEffectPedBoneDamageFX = nativePtr;
	}
}