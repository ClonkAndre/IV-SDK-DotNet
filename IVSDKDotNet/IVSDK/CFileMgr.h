class CFileMgr
{
public:
	static uint8_t* OpenFile(char* sPath, char* mode)
	{
		return ((uint8_t*(__cdecl*)(char*, char*))(AddressSetter::Get("CFileMgr", "OpenFile")))(sPath, mode);
	}
	static void CloseFile(uint8_t* file)
	{
		((void(__cdecl*)(uint8_t*))(AddressSetter::Get("CFileMgr", "CloseFile")))(file);
	}
	// 2nd param usually 1
	static char* LoadLine(uint8_t* file, int unk)
	{
		return ((char*(__cdecl*)(uint8_t*, int))(AddressSetter::Get("CFileMgr", "LoadLine")))(file, unk);
	}
};