#pragma once

namespace IVSDKDotNet
{
	public ref class IVSprite2D
	{
	public:
		property IVGrcTexturePC^ Texture
		{
		public:
			IVGrcTexturePC^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSprite2D, nullptr);
				return gcnew IVGrcTexturePC(NativeSprite2D->m_pTexture);
			}
			void set(IVGrcTexturePC^ value)
			{
				NULLPTR_CHECK(NativeSprite2D);
				NULLPTR_CHECK(value);
				NativeSprite2D->m_pTexture = value->NativeTexturePC;
			}
		}

	public:
		void SetTexture(String^ sName);
		void Delete();

	internal:
		IVSprite2D(CSprite2d* nativePtr);

	internal:
		CSprite2d* NativeSprite2D;
	};
}