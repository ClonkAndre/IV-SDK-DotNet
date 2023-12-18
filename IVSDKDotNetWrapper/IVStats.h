#pragma once

namespace IVSDKDotNet
{
	public ref class IVStats
	{
	public:
		static property String^ LastMissionPassedName
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CStats::LastMissionPassedName, nullptr);
				return gcnew String(CStats::LastMissionPassedName);
			}
		}

	public:
		static float GetStatValue(uint16_t index);
		static void SetStatValue(uint16_t index, float newValue);

	};
}