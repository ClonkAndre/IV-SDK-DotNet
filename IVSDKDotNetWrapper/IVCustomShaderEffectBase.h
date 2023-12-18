#pragma once

namespace IVSDKDotNet
{
	public ref class IVCustomShaderEffectBase
	{
	public:
		void Update(IVEntity^ attachedEntity);

	internal:
		IVCustomShaderEffectBase(CCustomShaderEffectBase* nativePtr);

	internal:
		CCustomShaderEffectBase* NativeCustomShaderEffectBase;
	};
}