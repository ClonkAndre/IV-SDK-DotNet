#pragma once

namespace IVSDKDotNet
{
	public ref class IVGameConfigReader
	{
	public:
		void LoadFile(String^ fileName);

	internal:
		IVGameConfigReader(CGameConfigReader* nativePtr);

	internal:
		CGameConfigReader* NativeConfigReader;
	};
}