#include "pch.h"
#include "IVTheScripts.h"

namespace IVSDKDotNet
{

    static uint8_t ms_aThreadDummy[256];

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
    int IVTheScripts::RegisterNativeNoChecks(uint32_t hash, IntPtr funcPtr)
    {
        return CTheScripts::RegisterNativeNoChecks(hash, funcPtr.ToPointer());
    }
    int IVTheScripts::RegisterNative(uint32_t hash, IntPtr funcPtr)
    {
        return CTheScripts::RegisterNative(hash, funcPtr.ToPointer());
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
        CTheScripts::m_pCurrentThread = (uint32_t)&ms_aThreadDummy;
    }
    void IVTheScripts::RestorePreviousThread()
    {
        CTheScripts::m_pCurrentThread = m_iPreviousThread;
    }

    uint32_t IVTheScripts::GetGlobalAddress(int index)
    {
        if (index < 0 || index > 65535)
            throw gcnew System::ArgumentOutOfRangeException("index", index, "The index must be 0 or greater, and below or equal 65535!");

        return *(uint32_t*)std::addressof(CTheScripts::m_aGlobalVariables[index]);
    }

    int IVTheScripts::GetGlobalInteger(int index)
    {
        try
        {
            uint32_t* addr = &CTheScripts::m_aGlobalVariables[index];
            return *(int*)addr;
        }
        catch (...)
        {
            return 0;
        }
    }
    float IVTheScripts::GetGlobalFloat(int index)
    {
        try
        {
            uint32_t* addr = &CTheScripts::m_aGlobalVariables[index];
            return *(float*)addr;
        }
        catch (...)
        {
            return 0.0f;
        }
    }
    String^ IVTheScripts::GetGlobalString(int index)
    {
        try
        {
            uint32_t* addr = &CTheScripts::m_aGlobalVariables[index];
            return gcnew String((char*)addr);
        }
        catch (...)
        {
            return String::Empty;
        }
    }

    void IVTheScripts::SetGlobal(int index, int value)
    {
        if (index < 0 || index > 65535)
            throw gcnew System::ArgumentOutOfRangeException("index", index, "The index must be 0 or greater, and below or equal 65535!");
        
        try
        {
            uint32_t* addr = &CTheScripts::m_aGlobalVariables[index];
            *(int*)addr = value;
        }
        catch (...) {}
    }
    void IVTheScripts::SetGlobal(int index, float value)
    {
        if (index < 0 || index > 65535)
            throw gcnew System::ArgumentOutOfRangeException("index", index, "The index must be 0 or greater, and below or equal 65535!");

        try
        {
            uint32_t* addr = &CTheScripts::m_aGlobalVariables[index];
            *(float*)addr = value;
        }
        catch (...) {}
    }
    bool IVTheScripts::SetGlobal(int index, String^ value)
    {
        if (index < 0 || index > 65535)
            throw gcnew System::ArgumentOutOfRangeException("index", index, "The index must be 0 or greater, and below or equal 65535!");
        if (value == nullptr)
            throw gcnew System::ArgumentNullException("value");
        if (String::IsNullOrWhiteSpace(value))
            throw gcnew System::ArgumentNullException("value");

        if (value->Length > 264607)
            return false;

        try
        {
            msclr::interop::marshal_context ctx;

            uint32_t* globalAddr = &CTheScripts::m_aGlobalVariables[index];

            char* str = (char*)globalAddr;
            char* newStr = (char*)ctx.marshal_as<const char*>(value);
            memcpy(str, newStr, value->Length);

            *(str + value->Length) = 0;

            return true;
        }
        catch (...) {}

        return false;
    }

}