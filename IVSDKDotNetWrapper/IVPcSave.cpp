#include "pch.h"
#include "IVPcSave.h"

namespace IVSDKDotNet
{
	int IVPcSave::SaveSlot(int32_t slotNum)
	{
		return C_PcSave::SaveSlot(slotNum);
	}
	int IVPcSave::LoadSlot(int32_t slotNum)
	{
		return C_PcSave::LoadSlot(slotNum);;
	}
}