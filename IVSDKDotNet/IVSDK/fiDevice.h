namespace rage
{
	class fiDeviceLocal
	{
		uint32_t m_pVFTable = AddressSetter::Get(0x95A9BC, 0x9894C4);
		uint8_t pad[0x20C];
	};
	VALIDATE_SIZE(fiDeviceLocal, 0x210);

	class fiDevice
	{
	public:
		static inline int& g_nMaxMountPoints = AddressSetter::GetRef<int>(0x22E6, 0x8FB46);

		static bool Mount(char* path, fiDeviceLocal* device, bool bUnk1)
		{
			return ((char(__cdecl*)(const char*, fiDeviceLocal*, int))(AddressSetter::Get(0x1ABE20, 0x5DDA0)))(path, device, bUnk1);
		}
		static bool Unmount(char* path)
		{
			return ((char(__cdecl*)(const char*))(AddressSetter::Get(0x0, 0x5E000)))(path); // TODO: Get address for 1070
		}

	public:
		uint32_t m_pVFTable = AddressSetter::Get(0x953D0C, 0x9856A4);
		uint8_t pad[0x20C];

		uint32_t SetPath(char* path, bool bAbsolute)
		{
			return ((uint32_t(__thiscall*)(fiDevice*, char*, bool))(AddressSetter::Get(0x1B43F0, 0x6F7D0)))(this, path, bAbsolute);
		}
		uint32_t SetMountPath(char* path)
		{
			return ((uint32_t(__thiscall*)(fiDevice*, const char*))(AddressSetter::Get(0x1B4480, 0x6F860)))(this, path);
		}

	};
	VALIDATE_SIZE(fiDevice, 0x210);

	class fiFile
	{
	public:
		// TODO: Needs to be worked on

		//// 1080: 17525B0 (0x13525B0)
		//// 1070: (0x)
		//static inline auto ms_Files = (fiFile*)AddressSetter::Get(0x0, 0x13525B0);

		//static fiFile* GetFile(int index)
		//{
		//	//return &ms_Files[0x1C * index];
		//	return (fiFile*)(AddressSetter::Get(0x0, 0x13525B0) + 0x1C * index);
		//}

	public:
		uint32_t* m_pDevice;
		int32_t m_hFile;
		uint8_t pad[0x14];

	public:
		void Close()
		{
			((int(__thiscall*)(fiFile*))(AddressSetter::Get(0x0, 0x604D0)))(this);
		}
		int GetLength()
		{
			return ((int(__thiscall*)(fiFile*))(AddressSetter::Get(0x0, 0x60510)))(this);
		}
		int Flush()
		{
			return ((int(__thiscall*)(fiFile*))(AddressSetter::Get(0x0, 0x60520)))(this);
		}

	};

};