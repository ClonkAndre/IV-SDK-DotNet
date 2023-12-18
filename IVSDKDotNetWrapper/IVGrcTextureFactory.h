#pragma once

namespace IVSDKDotNet
{
	public ref class IVGrcTextureFactory
	{
	internal:
		IVGrcTextureFactory(rage::grcTextureFactory* nativePtr);

	internal:
		rage::grcTextureFactory* NativeTextureFactory;
	};

	public ref class IVGrcTextureFactoryPC : IVGrcTextureFactory
	{
	public:
		static property IVGrcTextureFactoryPC^ TheTextureFactory
		{
		public:
			IVGrcTextureFactoryPC^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(rage::TextureFactory, nullptr);
				return gcnew IVGrcTextureFactoryPC(rage::TextureFactory);
			}
			void set(IVGrcTextureFactoryPC^ value)
			{
				NULLPTR_CHECK(value);
				rage::TextureFactory = value->NativeTextureFactoryPC;
			}
		}

	public:
		IVGrcTexturePC^ CreateTexture(String^ sName, UIntPtr pUnk);

	internal:
		IVGrcTextureFactoryPC(rage::grcTextureFactoryPC* nativePtr);

	internal:
		rage::grcTextureFactoryPC* NativeTextureFactoryPC;
	};
}