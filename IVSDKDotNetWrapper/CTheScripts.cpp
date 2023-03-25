#include "pch.h"
#include "CTheScripts.h"

namespace IVSDKDotNet {

	void CTheScripts::SetDummyThread()
	{
		m_iPreviousThread = Native_CTheScripts::GetCurrentThread();
		uint8_t threadDummy[256];
		Native_CTheScripts::SetCurrentThread((uint32_t)&threadDummy);
	}
	void CTheScripts::RestorePreviousThread()
	{
		Native_CTheScripts::SetCurrentThread(m_iPreviousThread);
	}

	uint32_t CTheScripts::FindNativeAddress(uint32_t nativeHash)
	{
		return Native_CTheScripts::FindNativeAddress(nativeHash);
	}

	bool CTheScripts::IsPlayerOnAMission()
	{
		return Native_CTheScripts::IsPlayerOnAMission();
	}

	void CTheScripts::GivePedScriptedTask(int handle, UIntPtr task, int unk)
	{
		if (task == UIntPtr::Zero)
			return;

		SetDummyThread(); // This needs to be called otherwise GivePedScriptedTask will attempt to read a nullptr!
		Native_CTheScripts::GivePedScriptedTask(handle, (uint32_t*)task.ToPointer(), unk);
	}

}