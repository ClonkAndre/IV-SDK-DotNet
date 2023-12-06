#pragma once

namespace IVSDKDotNet
{
	public value struct IVPedFlags
	{
	public:
		property bool NoHeadshots
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags.bNoHeadshots;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags.bNoHeadshots = value;
			}
		}

	internal:
		IVPedFlags(CPed* nativePtr);

	internal:
		CPed* NativePed;
	};
	public value struct IVPedFlags2
	{
	public:
		property bool InCar
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2.bInCar;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2.bInCar = value;
			}
		}
		property bool InAir
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2.bInAir;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2.bInAir = value;
			}
		}

	internal:
		IVPedFlags2(CPed* nativePtr);

	internal:
		CPed* NativePed;
	};

	public ref class IVPed : IVPhysical
	{
	public:
		property bool Dead
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_bDead;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_bDead = value;
			}
		}
		property bool Injured
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_bInjured;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_bInjured = value;
			}
		}
		property bool FatallyInjured
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_bFatallyInjured;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_bFatallyInjured = value;
			}
		}
		property uint8_t pad1
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->pad1;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->pad1 = value;
			}
		}
		property float PedHealth
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0.0F);
				return NativePed->m_fPedHealth;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_fPedHealth = value;
			}
		}
		property uint8_t PlayerIndex
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nPlayerIndex;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPlayerIndex = value;
			}
		}
		property bool IsPlayer
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_bIsPlayer;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_bIsPlayer = value;
			}
		}
		property IVPedDrawableInfo^ DrawableInfo
		{
		public:
			IVPedDrawableInfo^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pDrawableInfo, nullptr);
				return gcnew IVPedDrawableInfo(NativePed->m_pDrawableInfo);
			}
			void set(IVPedDrawableInfo^ value)
			{
				NULLPTR_CHECK(NativePed);
				NULLPTR_CHECK(value);
				NativePed->m_pDrawableInfo = value->NativePedDrawableInfo;
			}
		}
		property UIntPtr PedIntelligence
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pPedIntelligence, UIntPtr::Zero);
				return UIntPtr(NativePed->m_pPedIntelligence);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePed);
				UINTPTR_ZERO_CHECK(value);
				NativePed->m_pPedIntelligence = (CPedIntelligenceNY*)value.ToPointer();
			}
		}
		property IVPlayerInfo^ PlayerInfo
		{
		public:
			IVPlayerInfo^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pPlayerInfo, nullptr);
				return gcnew IVPlayerInfo(NativePed->m_pPlayerInfo);
			}
			void set(IVPlayerInfo^ value)
			{
				NULLPTR_CHECK(NativePed);
				NULLPTR_CHECK(value);
				NativePed->m_pPlayerInfo = value->NativePlayerInfo;
			}
		}
		property UIntPtr PedData
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pPedData, UIntPtr::Zero);
				return UIntPtr(NativePed->m_pPedData);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePed);
				UINTPTR_ZERO_CHECK(value);
				NativePed->m_pPedData = (CPedDataNY*)value.ToPointer();
			}
		}

		property IVPedFlags PedFlags
		{
		public:
			IVPedFlags get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, IVPedFlags());
				return IVPedFlags(NativePed);
			}
		}
		property IVPedFlags2 PedFlags2
		{
		public:
			IVPedFlags2 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, IVPedFlags2());
				return IVPedFlags2(NativePed);
			}
		}

		property float ClimbAnimRate
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0.0F);
				return NativePed->m_fClimbAnimRate;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_fClimbAnimRate = value;
			}
		}
		property IVPedWeapons^ WeaponData
		{
		public:
			IVPedWeapons^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				return gcnew IVPedWeapons(&NativePed->m_pWeaponData);
			}
		}
		property uint8_t ShootRate
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nShootRate;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nShootRate = value;
			}
		}
		property uint8_t Accuracy
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nAccuracy;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nAccuracy = value;
			}
		}
		property IVEntity^ StandingOnEntity
		{
		public:
			IVEntity^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pStandingOnEntity, nullptr);
				return gcnew IVEntity(NativePed->m_pStandingOnEntity);
			}
			void set(IVEntity^ value)
			{
				NULLPTR_CHECK(NativePed);
				NULLPTR_CHECK(value);
				NativePed->m_pStandingOnEntity = value->NativeEntity;
			}
		}
		property uint32_t VoiceHash
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nVoiceHash;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nVoiceHash = value;
			}
		}
		property UIntPtr Collider
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pCollider, UIntPtr::Zero);
				return UIntPtr(NativePed->m_pCollider);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePed);
				UINTPTR_ZERO_CHECK(value);
				NativePed->m_pCollider = (rage::phConstrainedCollider*)value.ToPointer();
			}
		}
		property uint32_t RagdollStatus
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nRagdollStatus;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nRagdollStatus = value;
			}
		}
		property uint32_t RagdollTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nRagdollTime;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nRagdollTime = value;
			}
		}
		property uint8_t WeaponObjectVisible
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nWeaponObjectVisible;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nWeaponObjectVisible = value;
			}
		}
		property uint8_t CreatedBy
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nCreatedBy;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nCreatedBy = value;
			}
		}
		property uint32_t DeathState
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nDeathState;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nDeathState = value;
			}
		}
		property IVPedMoveBlendOnFoot^ PedMoveBlendOnFoot
		{
		public:
			IVPedMoveBlendOnFoot^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pPedMoveBlendOnFoot, nullptr);
				return gcnew IVPedMoveBlendOnFoot(NativePed->m_pPedMoveBlendOnFoot);
			}
			void set(IVPedMoveBlendOnFoot^ value)
			{
				NULLPTR_CHECK(NativePed);
				NULLPTR_CHECK(value);
				NativePed->m_pPedMoveBlendOnFoot = value->NativePedMoveBlendOnFoot;
			}
		}
		property float MaxHealth
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0.0F);
				return NativePed->m_fMaxHealth;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_fMaxHealth = value;
			}
		}
		property float CurrentHeading
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0.0F);
				return NativePed->m_fCurrentHeading;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_fCurrentHeading = value;
			}
		}
		property float DesiredHeading
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0.0F);
				return NativePed->m_fDesiredHeading;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_fDesiredHeading = value;
			}
		}
		property UIntPtr Vehicle
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pVehicle, UIntPtr::Zero);
				return UIntPtr(NativePed->m_pVehicle);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePed);
				UINTPTR_ZERO_CHECK(value);
				NativePed->m_pVehicle = (CVehicle*)value.ToPointer();
			}
		}
		property uint32_t UnkPlayerSettingsRelated
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nUnkPlayerSettingsRelated;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nUnkPlayerSettingsRelated = value;
			}
		}
		property IVPedComponentModels^ ComponentModels
		{
		public:
			IVPedComponentModels^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pComponentModels, nullptr);
				return gcnew IVPedComponentModels(NativePed->m_pComponentModels);
			}
			void set(IVPedComponentModels^ value)
			{
				NULLPTR_CHECK(NativePed);
				NULLPTR_CHECK(value);
				NativePed->m_pComponentModels = value->NativePedComponentModels;
			}
		}

	public:
		static IVPed^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		void ProcessWeaponSwitch();
		IVPad^ GetPadFromPlayer();
		UIntPtr GetVehicle();
		void SetHealth(float health, int unk);
		void AddHealth(float health);
		void ProcessHeading();

	internal:
		IVPed(CPed* nativePtr);

	internal:
		CPed* NativePed;
	};
}