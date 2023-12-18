#include "pch.h"
#include "IVStreaming.h"

namespace IVSDKDotNet
{
    // - - - Methods / Functions - - -
    bool IVStreaming::IsStreamingDisabled()
    {
        return CStreaming::IsStreamingDisabled();
    }
    void IVStreaming::ScriptRequestModel(int32_t nHash, UIntPtr pRunningThread)
    {
        CStreaming::ScriptRequestModel(nHash, pRunningThread == UIntPtr::Zero ? nullptr : (uint32_t*)pRunningThread.ToPointer());
    }
    void IVStreaming::ScriptRequestModel(int32_t nHash)
    {
        ScriptRequestModel(nHash, UIntPtr::Zero);
    }
    void IVStreaming::RequestModel(int32_t modelIndex, int32_t unk1, int32_t nFlags)
    {
        CStreaming::RequestModel(modelIndex, unk1, nFlags);
    }
    void IVStreaming::LoadAllRequestedModels(bool priorityOnly)
    {
        CStreaming::LoadAllRequestedModels(priorityOnly);
    }
    void IVStreaming::AddImageList(String^ fileName)
    {
        CHECK_NULL_OR_WHITESPACE_STRING(fileName);
        msclr::interop::marshal_context ctx;
        CStreaming::AddImageList((char*)ctx.marshal_as<const char*>(fileName));
    }
    UIntPtr IVStreaming::GetPlayerPackfile()
    {
        rage::fiPackfile* ptr = CStreaming::GetPlayerPackfile();
        NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
        return UIntPtr(ptr);
    }
    void IVStreaming::ClosePlayerPackfile()
    {
        CStreaming::ClosePlayerPackfile();
    }
}