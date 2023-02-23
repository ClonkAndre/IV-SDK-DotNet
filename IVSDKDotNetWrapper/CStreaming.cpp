#include "pch.h"
#include "CStreaming.h"

namespace IVSDKDotNet {

	bool CStreaming::IsStreamingDisabled()
	{
		return Native_CStreaming::IsStreamingDisabled();
	}

	void CStreaming::ScriptRequestModel(int32_t nHash)
	{
		Native_CStreaming::ScriptRequestModel(nHash);
	}
	void CStreaming::ScriptRequestModel(int32_t nHash, UIntPtr pRunningThread)
	{
		Native_CStreaming::ScriptRequestModel(nHash, (uint32_t*)pRunningThread.ToPointer());
	}
	void CStreaming::RequestModel(int32_t modelIndex, int32_t unk1, int32_t nFlags)
	{
		Native_CStreaming::RequestModel(modelIndex, unk1, nFlags);
	}
	void CStreaming::LoadAllRequestedModels(bool priorityOnly)
	{
		Native_CStreaming::LoadAllRequestedModels(priorityOnly);
	}

	void CStreaming::AddImageList(String^ fileName)
	{
		msclr::interop::marshal_context ctx;
		Native_CStreaming::AddImageList((char*)ctx.marshal_as<const char*>(fileName));
	}

	void CStreaming::ClosePlayerPackfile()
	{
		Native_CStreaming::ClosePlayerPackfile();
	}

}