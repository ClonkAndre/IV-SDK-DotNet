class CGenericGameStorage
{
public:
	static inline auto ms_ValidSaveName = (char*)AddressSetter::Get("CGenericGameStorage", "ms_ValidSaveName");

	// returns "SGTA4"
	static const char* GetDefaultPCSaveFileName()
	{
		return ((const char*(__cdecl*)())(AddressSetter::Get("CGenericGameStorage", "GetDefaultPCSaveFileName")))();
	}
	static void MakeValidSaveName(const char* pString, int SlotNumber)
	{
		((void(__cdecl*)(const char*, int))(AddressSetter::Get("CGenericGameStorage", "MakeValidSaveName")))(pString, SlotNumber);
	}
	static bool SaveDataToWorkBuffer(void* pData, int32_t SizeOfData)
	{
		return ((bool(__cdecl*)(void*, int32_t))(AddressSetter::Get("CGenericGameStorage", "SaveDataToWorkBuffer")))(pData, SizeOfData);
	}
	static bool LoadDataFromWorkBuffer(void* pData, int32_t SizeOfData)
	{
		return ((bool(__cdecl*)(void*, int32_t))(AddressSetter::Get("CGenericGameStorage", "LoadDataFromWorkBuffer")))(pData, SizeOfData);
	}
};