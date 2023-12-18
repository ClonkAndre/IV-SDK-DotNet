#pragma once

namespace IVSDKDotNet
{
	public ref class IVCustomShaderEffectPedBoneDamageFX : IVCustomShaderEffectBase
	{
	public:
		property array<float>^ Damage
		{
		public:
			array<float>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectPedBoneDamageFX, nullptr);

				float* ptr = NativeCustomShaderEffectPedBoneDamageFX->m_fDamage;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<float>^ arr = gcnew array<float>(64);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = ptr[i];

				return arr;
			}
			void set(array<float>^ value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectPedBoneDamageFX);
				NULLPTR_CHECK(value);

				float* ptr = NativeCustomShaderEffectPedBoneDamageFX->m_fDamage;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = value[i];
			}
		}

	internal:
		IVCustomShaderEffectPedBoneDamageFX(CCustomShaderEffectPedBoneDamageFX* nativePtr);

	internal:
		CCustomShaderEffectPedBoneDamageFX* NativeCustomShaderEffectPedBoneDamageFX;
	};
}