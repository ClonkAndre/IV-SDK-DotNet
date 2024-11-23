// Returns: The index at which the image was added in the array
inline int CdStreamAddImage(char* sPath, uint8_t unk1, int32_t unkNeg1)
{
	return ((int(__cdecl*)(char*, uint8_t, int32_t))(AddressSetter::Get(0x497730, 0x622BE0)))(sPath, unk1, unkNeg1);
}