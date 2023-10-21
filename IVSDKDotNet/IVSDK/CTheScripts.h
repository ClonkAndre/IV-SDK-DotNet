struct building_swap_struct
{
	CBuilding* pBuilding;
	uint32_t NewModelIndex;
	uint32_t OldModelIndex;
};

class CTheScripts
{
public:
	static inline auto BuildingSwapArray = (building_swap_struct*)AddressSetter::Get(0xD801E0, 0xDFD080); // BuildingSwapArray[25]

	static inline auto& m_aGlobalVariables = AddressSetter::GetRef<uint32_t*>(0x1449AEC, 0x1394FC0); // m_aGlobalVariables[65535]?
	static inline auto& m_pCurrentThread = AddressSetter::GetRef<uint32_t>(0x1449AE0, 0x1394FB4);
	static uint32_t FindNativeAddress(uint32_t nativeHash)
	{
		__try
		{
			uint32_t funcPtr = AddressSetter::Get(0x1A76D0, 0x226AF0);
			uint32_t nativePtr;
			_asm
			{
				push esi
				mov esi, nativeHash
				call funcPtr
				pop esi
				mov nativePtr, eax
			}

			return nativePtr;
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return 0;
		}
	}
	static bool IsPlayerOnAMission()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get(0x403E00, 0x4AE3E0)))();
	}
	static void GivePedScriptedTask(int handle, CTask* task, int unk)
	{
		((void(__cdecl*)(int, CTask*, int))(AddressSetter::Get(0x4067A0, 0x4B0DF0)))(handle, task, unk);
	}
	static void AddToBuildingSwapArray(CBuilding* pBildng, int32_t OldModIndx, int32_t NewModIndx)
	{
		((void(__cdecl*)(CBuilding*, int32_t, int32_t))(AddressSetter::Get(0x404490, 0x4AEA70)))(pBildng, OldModIndx, NewModIndx);
	}
	static void UndoBuildingSwaps()
	{
		return ((void(__cdecl*)())(AddressSetter::Get(0x4045D0, 0x4AEBB0)))();
	}
	static void Save()
	{
		return ((void(__cdecl*)())(AddressSetter::Get(0x406530, 0x4B0B80)))();
	}
	static void Load()
	{
		return ((void(__cdecl*)())(AddressSetter::Get(0x409AF0, 0x4B40F0)))();
	}
};