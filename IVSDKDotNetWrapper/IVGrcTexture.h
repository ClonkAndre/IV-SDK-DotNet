#pragma once

namespace IVSDKDotNet
{
	public ref class IVGrcTexture
	{
	internal:
		IVGrcTexture(rage::grcTexture* nativePtr);

	internal:
		rage::grcTexture* NativeTexture;
	};

	public ref class IVGrcTexturePC : IVGrcTexture
	{
	public:
		property UIntPtr D3DTexture
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTexturePC, UIntPtr::Zero);
				return UIntPtr(NativeTexturePC->m_pD3DTexture);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				NativeTexturePC->m_pD3DTexture = (LPDIRECT3DTEXTURE9)value.ToPointer();
			}
		}

	internal:
		IVGrcTexturePC(rage::grcTexturePC* nativePtr);

	internal:
		rage::grcTexturePC* NativeTexturePC;
	};
}