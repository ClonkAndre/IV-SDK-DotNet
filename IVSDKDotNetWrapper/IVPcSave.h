#pragma once

namespace IVSDKDotNet
{
	public ref class IVPcSave
	{
	public:
		// slot -1 is autosave
		static int SaveSlot(int32_t slotNum);
		static int LoadSlot(int32_t slotNum);
	};
}