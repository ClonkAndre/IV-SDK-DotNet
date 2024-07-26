#pragma once

namespace IVSDKDotNet
{
	public ref class IVPlayerInfo
	{
	public:
		property uint64_t XUID
		{
			uint64_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_XUID;
			}
		}
		property String^ Name
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, String::Empty);
				return gcnew String(NativePlayerInfo->m_sName);
			}
		}
		property UIntPtr PlayerPed2
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo->m_pPlayerPed2, UIntPtr::Zero);
				return UIntPtr(NativePlayerInfo->m_pPlayerPed2);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NULLPTR_CHECK(NativePlayerInfo->m_pPlayerPed2);
				UINTPTR_ZERO_CHECK(value);
				NativePlayerInfo->m_pPlayerPed2 = (CPed*)value.ToPointer();
			}
		}
		property float Stamina
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0.0F);
				return NativePlayerInfo->m_fStamina;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_fStamina = value;
			}
		}
		property uint32_t LastHitPedTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nLastHitPedTime;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nLastHitPedTime = value;
			}
		}
		property uint32_t LastHitBuildingTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nLastHitBuildingTime;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nLastHitBuildingTime = value;
			}
		}
		property uint32_t LastHitObjectTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nLastHitObjectTime;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nLastHitObjectTime = value;
			}
		}
		property uint32_t LastDroveOnPavementTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nLastDroveOnPavementTime;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nLastDroveOnPavementTime = value;
			}
		}
		property uint32_t LastRanLightTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nLastRanLightTime;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nLastRanLightTime = value;
			}
		}
		property uint32_t LastDroveAgainstTrafficTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nLastDroveAgainstTrafficTime;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nLastDroveAgainstTrafficTime = value;
			}
		}
		property uint32_t ControlFlags
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nControlFlags;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nControlFlags = value;
			}
		}
		property uint8_t PlayerId
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nPlayerId;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nPlayerId = value;
			}
		}
		property uint8_t pad6
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->pad6;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->pad6 = value;
			}
		}
		property uint32_t State
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nState;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nState = value;
			}
		}
		property uint8_t NeverTired
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nNeverTired;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nNeverTired = value;
			}
		}
		property uint16_t MaxHealth
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nMaxHealth;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nMaxHealth = value;
			}
		}
		property uint16_t MaxArmor
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nMaxArmor;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nMaxArmor = value;
			}
		}
		property uint8_t CanDoDriveby
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nCanDoDriveby;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nCanDoDriveby = value;
			}
		}
		property uint32_t Mood
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nMood;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nMood = value;
			}
		}
		property int32_t Colour
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nColour;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nColour = value;
			}
		}
		property int32_t Team
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nTeam;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nTeam = value;
			}
		}
		property uint8_t HasDiedRecently
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, 0);
				return NativePlayerInfo->m_nHasDiedRecently;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NativePlayerInfo->m_nHasDiedRecently = value;
			}
		}
		property UIntPtr PlayerPed
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo->m_pPlayerPed, UIntPtr::Zero);
				return UIntPtr(NativePlayerInfo->m_pPlayerPed);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NULLPTR_CHECK(NativePlayerInfo->m_pPlayerPed);
				UINTPTR_ZERO_CHECK(value);
				NativePlayerInfo->m_pPlayerPed = (CPed*)value.ToPointer();
			}
		}
		property UIntPtr OnlyEnterThisVehicle
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePlayerInfo->m_pOnlyEnterThisVehicle, UIntPtr::Zero);
				return UIntPtr(NativePlayerInfo->m_pOnlyEnterThisVehicle);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePlayerInfo);
				NULLPTR_CHECK(NativePlayerInfo->m_pOnlyEnterThisVehicle);
				UINTPTR_ZERO_CHECK(value);
				NativePlayerInfo->m_pOnlyEnterThisVehicle = (CVehicle*)value.ToPointer();
			}
		}

	public:
		void KillPlayerOutsideWorld();

	public:
		static IVPlayerInfo^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

	public:
		static bool IsPlayerActive(int id);
		static IVPlayerInfo^ GetPlayerInfo(uint32_t nPlayerId);

		static Vector3 FindThePlayerCentreOfWorld(Vector3 v);
		static UIntPtr FindThePlayerPed();

	internal:
		IVPlayerInfo(CPlayerInfo* nativePtr);

	internal:
		CPlayerInfo* NativePlayerInfo;
	};
}