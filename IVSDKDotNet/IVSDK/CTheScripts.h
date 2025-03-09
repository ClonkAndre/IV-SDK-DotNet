#pragma unmanaged

struct building_swap_struct
{
	CBuilding* pBuilding;
	uint32_t NewModelIndex;
	uint32_t OldModelIndex;
};

class CTheScripts
{
public:
	static inline auto BuildingSwapArray = (building_swap_struct*)AddressSetter::Get("CTheScripts", "BuildingSwapArray"); // BuildingSwapArray[25]

	static inline auto& m_aGlobalVariables = AddressSetter::GetRef<uint32_t*>("CTheScripts", "m_aGlobalVariables"); // m_aGlobalVariables[65535]?
	static inline auto& m_pCurrentThread = AddressSetter::GetRef<uint32_t>("CTheScripts", "m_pCurrentThread");

	static uint32_t FindNativeAddress(uint32_t nativeHash)
	{
		uint32_t funcPtr = AddressSetter::Get("CTheScripts", "FindNativeAddress");
		
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

		//__try
		//{

		//}
		//__except (EXCEPTION_EXECUTE_HANDLER)
		//{
		//	return 0;
		//}
	}
	static int RegisterNativeNoChecks(uint32_t hash, LPVOID funcPtr)
	{
		return ((int (__stdcall*)(uint32_t, LPVOID))(AddressSetter::Get("CTheScripts", "RegisterNativeNoChecks")))(hash, funcPtr);
	}
	static int RegisterNative(uint32_t hash, LPVOID funcPtr)
	{
		return ((int(__cdecl*)(uint32_t, LPVOID))(AddressSetter::Get("CTheScripts", "RegisterNative")))(hash, funcPtr);
	}

	static const char* GetNameOfCurrentScript()
	{
		return ((const char* (__cdecl*)())(AddressSetter::Get("CTheScripts", "GetNameOfCurrentScript")))();
	}

	static bool IsPlayerOnAMission()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get("CTheScripts", "IsPlayerOnAMission")))();
	}
	static void GivePedScriptedTask(int handle, CTask* task, int unk)
	{
		((void(__cdecl*)(int, CTask*, int))(AddressSetter::Get("CTheScripts", "GivePedScriptedTask")))(handle, task, unk);
	}
	static void AddToBuildingSwapArray(CBuilding* pBildng, int32_t OldModIndx, int32_t NewModIndx)
	{
		((void(__cdecl*)(CBuilding*, int32_t, int32_t))(AddressSetter::Get("CTheScripts", "AddToBuildingSwapArray")))(pBildng, OldModIndx, NewModIndx);
	}
	static void UndoBuildingSwaps()
	{
		return ((void(__cdecl*)())(AddressSetter::Get("CTheScripts", "UndoBuildingSwaps")))();
	}
	static void Save()
	{
		return ((void(__cdecl*)())(AddressSetter::Get("CTheScripts", "Save")))();
	}
	static void Load()
	{
		return ((void(__cdecl*)())(AddressSetter::Get("CTheScripts", "Load")))();
	}
};

#pragma managed