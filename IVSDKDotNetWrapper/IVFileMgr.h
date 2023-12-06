#pragma once

namespace IVSDKDotNet
{
	public ref class IVFileMgr
	{
	public:
		static UIntPtr OpenFile(String^ sPath, String^ mode);
		static void CloseFile(UIntPtr file);
		static String^ LoadLine(UIntPtr file, int unk);
	};
}