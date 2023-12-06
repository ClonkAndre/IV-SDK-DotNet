#pragma once

namespace IVSDKDotNet
{
	public ref class IVFiDevice
	{
	public:
		static property int32_t MaxMountPoints
		{
		public:
			int32_t get()
			{
				return rage::fiDevice::g_nMaxMountPoints;
			}
			void set(int32_t value)
			{
				rage::fiDevice::g_nMaxMountPoints = value;
			}
		}

	public:
		// TODO
		//uint32_t SetPath(String^ path, bool bAbsolute);
		//uint32_t SetMountPath(String^ path);
		static bool Mount(String^ path, UIntPtr device, bool bUnk1);
	};
}