#include "pch.h"
#include "IVTheScripts.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    BuildingSwapStruct::BuildingSwapStruct(building_swap_struct* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeBuildingSwapStruct = nativePtr;
    }

    // - - - Methods / Functions - - -
    uint32_t IVTheScripts::FindNativeAddress(uint32_t nativeHash)
    {
        return CTheScripts::FindNativeAddress(nativeHash);
    }
    bool IVTheScripts::IsPlayerOnAMission()
    {
        return CTheScripts::IsPlayerOnAMission();
    }
    void IVTheScripts::GivePedScriptedTask(int handle, IVTask^ task, int unk)
    {
        NULLPTR_CHECK(task);

        SetDummyThread(); // This needs to be called otherwise GivePedScriptedTask will attempt to read a nullptr!
        CTheScripts::GivePedScriptedTask(handle, task->NativeBaseTask, unk);
        RestorePreviousThread();
    }
    void IVTheScripts::AddToBuildingSwapArray(IVBuilding^ pBildng, int32_t oldModIndx, int32_t newModIndx)
    {
        NULLPTR_CHECK(pBildng);
        CTheScripts::AddToBuildingSwapArray(pBildng->NativeBuilding, oldModIndx, newModIndx);
    }
    void IVTheScripts::UndoBuildingSwaps()
    {
        CTheScripts::UndoBuildingSwaps();
    }
    void IVTheScripts::Save()
    {
       CTheScripts::Save();
    }
    void IVTheScripts::Load()
    {
        CTheScripts::Load();
    }

    void IVTheScripts::SetDummyThread()
    {
        m_iPreviousThread = CTheScripts::m_pCurrentThread;
        uint8_t threadDummy[256];
        CTheScripts::m_pCurrentThread = (uint32_t)&threadDummy;
    }
    void IVTheScripts::RestorePreviousThread()
    {
        CTheScripts::m_pCurrentThread = m_iPreviousThread;
    }

}