#include "pch.h"
#include "CdStream.h"

namespace IVSDKDotNet {

	void CdStream::CdStreamAddImage(String^ sPath, uint8_t unk1, int32_t unkNeg1)
	{
		msclr::interop::marshal_context ctx;
		Native_CdStream::CdStreamAddImage((char*)ctx.marshal_as<const char*>(sPath), unk1, unkNeg1);
	}

}