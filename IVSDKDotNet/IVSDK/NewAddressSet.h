namespace AddressSetter
{
	static uint32_t gCurrentExeVersion;
	static uint32_t gBaseAddress;
	static bool bAddressesRead = false;

	static INI<>* loadedConfig = nullptr;

	static inline bool DoesFileExists(const std::string& name)
	{
		std::ifstream f(name.c_str());
		return f.good();
	}
	static inline uint32_t GetVersionFromEXE()
	{
		TCHAR szFileName[MAX_PATH];

		GetModuleFileName(NULL, szFileName, MAX_PATH);

		DWORD  verHandle = 0;
		UINT   size = 0;
		LPBYTE lpBuffer = NULL;
		DWORD  verSize = GetFileVersionInfoSize(szFileName, &verHandle);

		if (verSize != NULL)
		{
			LPSTR verData = new char[verSize];

			if (GetFileVersionInfo(szFileName, verHandle, verSize, verData))
			{
				if (VerQueryValue(verData, TEXT("\\"), (VOID FAR * FAR*) & lpBuffer, &size))
				{
					if (size)
					{
						VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
						if (verInfo->dwSignature == 0xfeef04bd)
						{
							std::string str = std::to_string((verInfo->dwFileVersionMS >> 16) & 0xffff);
							str += std::to_string((verInfo->dwFileVersionMS >> 0) & 0xffff);
							str += std::to_string((verInfo->dwFileVersionLS >> 16) & 0xffff);
							str += std::to_string((verInfo->dwFileVersionLS >> 0) & 0xffff);
							delete[] verData;
							return std::stoi(str);
						}
					}
				}
			}
			delete[] verData;
		}
		return 0;
	}

	static inline void DetermineVersion()
	{
		// Determine the game version
		gCurrentExeVersion = GetVersionFromEXE();

		// Set the game version
		plugin::gameVer = (plugin::eGameVersion)gCurrentExeVersion;
	}

	static inline bool LoadCurrentVersionConfig()
	{
		std::string path = std::string(".\\IVSDK\\").append(std::to_string(gCurrentExeVersion)).append(".ini");

		if (!DoesFileExists(path))
			return false;

		loadedConfig = new INI<>(path, true);
		return true;
	}
	static inline void Init()
	{
		if (bAddressesRead)
			return;

		// Dertemine the game version
		DetermineVersion();
		gBaseAddress = (uint32_t)GetModuleHandle(NULL);

		// Load config file according to the game version
		if (!LoadCurrentVersionConfig())
		{
			MessageBoxA(NULL, std::string("Config file for version ").append(std::to_string(gCurrentExeVersion)).append(" was not found! IVSDK might not be compatible with this version yet.").c_str(), "IVSDK", MB_ICONERROR);
			exit(1);
			return;
		}

		bAddressesRead = true;
	}

	static inline bool IsConfigPattern(const std::string& section, const std::string& key)
	{
		if (!bAddressesRead)
			Init();

		// Get string from section
		std::string str = loadedConfig->get(section, key, std::string());

		if (str.empty())
			return false;
		if (str.find("0x") == 0 || str.find("0X") == 0)
			return false;

		return true;
	}
	static inline std::string GetConfigString(const std::string& section, const std::string& key)
	{
		if (!bAddressesRead)
			Init();

		// Get string from section
		return loadedConfig->get(section, key, std::string());
	}
	static inline uint32_t GetAddressFromConfig(const std::string& section, const std::string& key)
	{
		if (!bAddressesRead)
			Init();

		// Get string from section
		std::string str = loadedConfig->get(section, key, std::string());

		if (str.empty())
		{
			MessageBoxA(NULL, std::string("Address for section ").append(section).append(" and key ").append(key).append(" was not found in the config file!").c_str(), "IVSDK", MB_ICONERROR);
			exit(1);
			return 0;
		}

		if (str.find("0x") == 0 || str.find("0X") == 0)
		{
			// Try convert string to uint32_t
			uint32_t num = static_cast<uint32_t>(std::stoul(str, nullptr, 16));

			return num;
		}
		else
		{
			// Try getting the address from the pattern
			auto scan = hook::pattern(str);

			uint32_t* ptr = scan.get(0).get<uint32_t>(0);

			//assert(ptr);

			return *ptr;
		}

		return 0;
	}

	// Note that the base address is added here and 0x400000 is not subtracted, so rebase your .idb to 0x0 or subtract it yourself
	template<typename T>
	static inline T& GetRef(uint32_t addr1070, uint32_t addr1080)
	{
		if (!bAddressesRead)
			Init();

		switch(plugin::gameVer)
		{
			case plugin::VERSION_1080: return *reinterpret_cast<T*>(gBaseAddress + addr1080);
			case plugin::VERSION_1070: return *reinterpret_cast<T*>(gBaseAddress + addr1070);
		}

		return *reinterpret_cast<T*>(nullptr);
	}

	template<typename T>
	static inline T& GetRef(uint32_t addr)
	{
		if (!bAddressesRead)
			Init();

		return *reinterpret_cast<T*>(gBaseAddress + addr);
	}

	template<typename T>
	static inline T& GetRef(const std::string& section, const std::string& key)
	{
		return GetRef<T>(GetAddressFromConfig(section, key));
	}

	static inline uint32_t Get(uint32_t addr1070, uint32_t addr1080)
	{
		if (!bAddressesRead)
			Init();

		switch(plugin::gameVer)
		{
			case plugin::VERSION_1080: return gBaseAddress + addr1080;
			case plugin::VERSION_1070: return gBaseAddress + addr1070;
		}

		return 0;
	}
	static inline uint32_t Get(uint32_t addr)
	{
		if (!bAddressesRead)
			Init();

		return gBaseAddress + addr;
	}
	static inline uint32_t Get(const std::string& section, const std::string& key)
	{
		return Get(GetAddressFromConfig(section, key));
	}

}