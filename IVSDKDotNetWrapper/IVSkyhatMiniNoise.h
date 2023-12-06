#pragma once

namespace IVSDKDotNet
{
	public ref class IVSkyhatMiniNoise
	{
	public:
		property UIntPtr RenderTarget
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSkyhatMiniNoise, UIntPtr::Zero);
				return UIntPtr(NativeSkyhatMiniNoise->m_pRenderTarget);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeSkyhatMiniNoise);
				UINTPTR_ZERO_CHECK(value);
				NativeSkyhatMiniNoise->m_pRenderTarget = (rage::grcRenderTargetPC*)value.ToPointer();
			}
		}
		property array<IVSprite2D^>^ Texture
		{
		public:
			array<IVSprite2D^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSkyhatMiniNoise, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeSkyhatMiniNoise->m_pTexture, nullptr);

				array<IVSprite2D^>^ arr = gcnew array<IVSprite2D^>(6);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVSprite2D(&NativeSkyhatMiniNoise->m_pTexture[i]);

				return arr;
			}
			void set(array<IVSprite2D^>^ value)
			{
				NULLPTR_CHECK(NativeSkyhatMiniNoise);
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					NativeSkyhatMiniNoise->m_pTexture[i] = *value[i]->NativeSprite2D;
			}
		}

	internal:
		IVSkyhatMiniNoise(rage::SkyhatMiniNoise* nativePtr);

	internal:
		rage::SkyhatMiniNoise* NativeSkyhatMiniNoise;
	};
}