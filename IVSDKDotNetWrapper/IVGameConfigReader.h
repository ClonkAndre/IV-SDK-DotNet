#pragma once

namespace IVSDKDotNet
{
	public ref class IVGameConfigReader
	{
	public:
		static property IVGameConfigReader^ TheGameConfigReader
		{
		public:
			IVGameConfigReader^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(GameConfigReader, nullptr);
				return gcnew IVGameConfigReader(GameConfigReader);
			}
			void set(IVGameConfigReader^ value)
			{
				NULLPTR_CHECK(value);
				GameConfigReader = value->NativeConfigReader;
			}
		}

	public:
		void LoadFile(String^ fileName);

	internal:
		IVGameConfigReader(CGameConfigReader* nativePtr);

	internal:
		CGameConfigReader* NativeConfigReader;
	};
}