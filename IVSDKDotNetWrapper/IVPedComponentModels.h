#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedComponentModels
	{
	public:
		property array<UIntPtr>^ Drawables
		{
		public:
			array<UIntPtr>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedComponentModels, nullptr);

				rage::rmcDrawable** ptr = NativePedComponentModels->m_pDrawables;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<UIntPtr>^ arr = gcnew array<UIntPtr>(11);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = UIntPtr(ptr[i]);

				return arr;
			}
			void set(array<UIntPtr>^ value)
			{
				NULLPTR_CHECK(NativePedComponentModels);
				NULLPTR_CHECK(value);

				rage::rmcDrawable** ptr = NativePedComponentModels->m_pDrawables;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = (rage::rmcDrawable*)value[i].ToPointer();
			}
		}
		property IVCustomShaderEffectPedBoneDamageFX^ PedBoneDamageFX
		{
		public:
			IVCustomShaderEffectPedBoneDamageFX^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedComponentModels, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePedComponentModels->m_pPedBoneDamageFX, nullptr);
				return gcnew IVCustomShaderEffectPedBoneDamageFX(NativePedComponentModels->m_pPedBoneDamageFX);
			}
			void set(IVCustomShaderEffectPedBoneDamageFX^ value)
			{
				NULLPTR_CHECK(NativePedComponentModels);
				NULLPTR_CHECK(value);
				NativePedComponentModels->m_pPedBoneDamageFX = value->NativeCustomShaderEffectPedBoneDamageFX;
			}
		}

	internal:
		IVPedComponentModels(tPedComponentModels* nativePtr);

	internal:
		tPedComponentModels* NativePedComponentModels;
	};
}