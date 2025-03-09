class CImgFileMgr
{
public:
	// TODO: Cleanup this class and create a proper "CdImgFile" class or something which stores all the stuff in the arrays below

	// 1080: 1399810 (0xF99810)
	// 1070: 121DFE8 (0xE1DFE8)
	static inline auto ms_ImgFiles_FileNames = (char*)AddressSetter::Get("CImgFileMgr", "ms_ImgFiles_FileNames");

	// 1080: 1399898 (0xF99898)
	// 1070: 121E070 (0xE1E070)
	static inline auto ms_ImgFiles_FileHandles = (int32_t*)AddressSetter::Get("CImgFileMgr", "ms_ImgFiles_FileHandles");

public:
	static int CloseImageFile(int index)
	{
		int* handle = &ms_ImgFiles_FileHandles[0x28 * index];

		if (!(*(BYTE*)handle - 136))
			return 0;
		if (*handle == -1)
			return 0;

		char* name = &ms_ImgFiles_FileNames[0xA0 * index];

		// Close the img file
		int result = (*(int(__thiscall**)(int, int))(*(DWORD*)handle[0xFFFFFFFE] + 0x2C))(handle[0xFFFFFFFE], *handle);

		// Set handle to -1
		*handle = -1;
		*name = 0;

		return result;
	}
	static int CloseAllImages()
	{
		return ((int(__cdecl*)())(AddressSetter::Get("CImgFileMgr", "CloseAllImages")))();
	}

	static char* GetImageFileName(int index)
	{
		return &ms_ImgFiles_FileNames[0xA0 * index];
	}
	static int GetImageFileHandle(int index)
	{
		return ms_ImgFiles_FileHandles[0x28 * index];
	}
};

// Returns: The index at which the image was added in the array
inline int CdStreamAddImage(char* sPath, uint8_t unk1, int32_t unkNeg1)
{
	return ((int(__cdecl*)(char*, uint8_t, int32_t))(AddressSetter::Get("CImgFileMgr", "CdStreamAddImage")))(sPath, unk1, unkNeg1);
}
