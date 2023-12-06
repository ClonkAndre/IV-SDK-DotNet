#pragma once

namespace IVSDKDotNet
{
	public ref class IVGangInfo
	{
	public:
		property int8_t PedModelOverride
		{
		public:
			int8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGangInfo, 0);
				return NativeGangInfo->PedModelOverride;
			}
			void set(int8_t value)
			{
				NULLPTR_CHECK(NativeGangInfo);
				NativeGangInfo->PedModelOverride = value;
			}
		}
		property uint32_t FirstWeapon
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGangInfo, 0);
				return NativeGangInfo->FirstWeapon;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeGangInfo);
				NativeGangInfo->FirstWeapon = value;
			}
		}
		property uint32_t SecondWeapon
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGangInfo, 0);
				return NativeGangInfo->SecondWeapon;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeGangInfo);
				NativeGangInfo->SecondWeapon = value;
			}
		}
		property uint32_t ThirdWeapon
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGangInfo, 0);
				return NativeGangInfo->ThirdWeapon;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeGangInfo);
				NativeGangInfo->ThirdWeapon = value;
			}
		}
		property uint8_t FirstWeaponChance
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGangInfo, 0);
				return NativeGangInfo->FirstWeaponChance;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeGangInfo);
				NativeGangInfo->FirstWeaponChance = value;
			}
		}
		property uint8_t SecondWeaponChance
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGangInfo, 0);
				return NativeGangInfo->SecondWeaponChance;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeGangInfo);
				NativeGangInfo->SecondWeaponChance = value;
			}
		}
		property uint8_t ThirdWeaponChance
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGangInfo, 0);
				return NativeGangInfo->ThirdWeaponChance;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeGangInfo);
				NativeGangInfo->ThirdWeaponChance = value;
			}
		}

	internal:
		IVGangInfo(CGangInfo* nativePtr);

	internal:
		CGangInfo* NativeGangInfo;
	};
}