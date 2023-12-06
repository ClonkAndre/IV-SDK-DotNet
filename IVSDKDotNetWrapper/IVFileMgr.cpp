#include "pch.h"
#include "IVFileMgr.h"

namespace IVSDKDotNet
{
	UIntPtr IVFileMgr::OpenFile(String^ sPath, String^ mode)
	{
		CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(sPath, UIntPtr::Zero);
		CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(mode, UIntPtr::Zero);

		msclr::interop::marshal_context ctx;
		uint8_t* ptr = CFileMgr::OpenFile((char*)ctx.marshal_as<const char*>(sPath), (char*)ctx.marshal_as<const char*>(mode));
		NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);

		return UIntPtr(ptr);
	}
	void IVFileMgr::CloseFile(UIntPtr file)
	{
		UINTPTR_ZERO_CHECK(file);
		CFileMgr::CloseFile((uint8_t*)file.ToPointer());
	}
	String^ IVFileMgr::LoadLine(UIntPtr file, int unk)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(file, String::Empty);

		char* ptr = CFileMgr::LoadLine((uint8_t*)file.ToPointer(), unk);
		NULLPTR_CHECK_WITH_RETURN(ptr, String::Empty);

		return gcnew String(ptr);
	}
}