#include "pch.h"
#include "IVGameConfigReader.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVGameConfigReader::IVGameConfigReader(CGameConfigReader* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeConfigReader = nativePtr;
	}

	// - - - Methods / Functions - - -
	void IVGameConfigReader::LoadFile(String^ fileName)
	{
		CHECK_NULL_OR_WHITESPACE_STRING(fileName);
		msclr::interop::marshal_context ctx;
		NativeConfigReader->LoadFile((char*)ctx.marshal_as<const char*>(fileName));
	}

}


