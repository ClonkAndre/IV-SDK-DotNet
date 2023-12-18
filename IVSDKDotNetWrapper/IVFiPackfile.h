#pragma once

namespace IVSDKDotNet
{
	public ref class IVFiPackfile
	{
	public:
		static IVFiPackfile^ Create();

	public:
		bool OpenPackfile(String^ path, char unk1_1, char unk2_0, int unk3_0or3);
		bool Mount(String^ mountPoint);

	internal:
		IVFiPackfile(rage::fiPackfile* nativePtr);

	internal:
		rage::fiPackfile* NativePackfile;
	};
}