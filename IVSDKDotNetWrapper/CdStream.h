#pragma once

class Native_CdStream
{
public:
	static void CdStreamAddImage(char* sPath, uint8_t unk1, int32_t unkNeg1)
	{
		((void(__cdecl*)(char*, uint8_t, int32_t))(AddressSetter::Get(0x497730, 0x622BE0)))(sPath, unk1, unkNeg1);
	}
};

namespace IVSDKDotNet {

	public ref class CdStream
	{
	public:

		static void CdStreamAddImage(String^ sPath, uint8_t unk1, int32_t unkNeg1);

	};

}

