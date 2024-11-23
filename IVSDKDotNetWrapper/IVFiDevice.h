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

		static bool Mount(String^ path, UIntPtr device, bool bUnk1);
		static bool Unmount(String^ path);

	public:
		property uint32_t VFTable
		{
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeFiDevice, 0);
				return NativeFiDevice->m_pVFTable;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeFiDevice);
				NativeFiDevice->m_pVFTable = value;
			}
		}
		
	public:
		static IVFiDevice^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		uint32_t SetPath(String^ path, bool bAbsolute);
		uint32_t SetMountPath(String^ path);

	internal:
		IVFiDevice(rage::fiDevice* nativePtr);

	internal:
		rage::fiDevice* NativeFiDevice;

	};
}