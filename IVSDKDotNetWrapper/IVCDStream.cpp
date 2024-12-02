#include "pch.h"
#include "IVCDStream.h"

namespace IVSDKDotNet
{

	// - - - Methods / Functions - - -
	int IVCDStream::AddImage(String^ sPath, uint8_t unk1, int32_t unkNeg1)
	{
		if (String::IsNullOrWhiteSpace(sPath))
			return 0;

		msclr::interop::marshal_context ctx;
		return CdStreamAddImage((char*)ctx.marshal_as<const char*>(sPath), unk1, unkNeg1);
	}

	int IVCDStream::CloseImageFile(int index)
	{
		return CImgFileMgr::CloseImageFile(index);
	}
	int IVCDStream::CloseAllImages()
	{
		return CImgFileMgr::CloseAllImages();
	}

	String^ IVCDStream::GetImageFileName(int index)
	{
		char* ptr = CImgFileMgr::GetImageFileName(index);

		if (ptr)
			return gcnew String(ptr);

		return String::Empty;
	}
	int IVCDStream::GetImageFileHandle(int index)
	{
		return CImgFileMgr::GetImageFileHandle(index);
	}

}