#include "pch.h"
#include "IVCDStream.h"

namespace IVSDKDotNet
{
	int IVCDStream::AddImage(String^ sPath, uint8_t unk1, int32_t unkNeg1)
	{
		if (String::IsNullOrWhiteSpace(sPath))
			return 0;

		msclr::interop::marshal_context ctx;
		return CdStreamAddImage((char*)ctx.marshal_as<const char*>(sPath), unk1, unkNeg1);
	}
}