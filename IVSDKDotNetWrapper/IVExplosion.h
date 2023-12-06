#pragma once

namespace IVSDKDotNet
{
	public value struct IVExplosionInfo
	{
	public:
		property float DamageAtCentre
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fDamageAtCentre;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fDamageAtCentre = value;
			}
		}
		property float DamageAtEdge
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fDamageAtEdge;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fDamageAtEdge = value;
			}
		}
		property float NetworkPlayerModifier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fNetworkPlayerModifier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fNetworkPlayerModifier = value;
			}
		}
		property float NetworkPedModifier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fNetworkPedModifier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fNetworkPedModifier = value;
			}
		}
		property float EndRadius
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fEndRadius;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fEndRadius = value;
			}
		}
		property float InitSpeed
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fInitSpeed;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fInitSpeed = value;
			}
		}
		property float DecayFactor
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fDecayFactor;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fDecayFactor = value;
			}
		}
		property float ForceFactor
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fForceFactor;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fForceFactor = value;
			}
		}
		property float RagdollModifier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fRagdollModifier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fRagdollModifier = value;
			}
		}
		property uint32_t FxHash
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0);
				return NativeExplosionInfo->m_nFxHash;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_nFxHash = value;
			}
		}
		property uint32_t FxAirHash
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0);
				return NativeExplosionInfo->m_nFxAirHash;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_nFxAirHash = value;
			}
		}
		property float FxScale
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fFxScale;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fFxScale = value;
			}
		}
		property float DirectedWidth
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fDirectedWidth;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fDirectedWidth = value;
			}
		}
		property float DirectedLife
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fDirectedLife;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fDirectedLife = value;
			}
		}
		property uint32_t NumFiresMin
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0);
				return NativeExplosionInfo->m_nNumFiresMin;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_nNumFiresMin = value;
			}
		}
		property uint32_t NumFiresMax
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0);
				return NativeExplosionInfo->m_nNumFiresMax;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_nNumFiresMax = value;
			}
		}
		property float FireRangeMin
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fFireRangeMin;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fFireRangeMin = value;
			}
		}
		property float FireRangeMax
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fFireRangeMax;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fFireRangeMax = value;
			}
		}
		property float CameraShake
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fCameraShake;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fCameraShake = value;
			}
		}
		property uint32_t WeaponType
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0);
				return NativeExplosionInfo->m_nWeaponType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_nWeaponType = value;
			}
		}
		property uint32_t Infinite
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0);
				return NativeExplosionInfo->m_nInfinite;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_nInfinite = value;
			}
		}
		property float LightsR
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fLightsR;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fLightsR = value;
			}
		}
		property float LightsG
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fLightsG;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fLightsG = value;
			}
		}
		property float LightsB
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fLightsB;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fLightsB = value;
			}
		}
		property float LightsScale
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fLightsScale;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fLightsScale = value;
			}
		}
		property float LightsRange
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fLightsRange;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fLightsRange = value;
			}
		}
		property float LightsTime
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0.0F);
				return NativeExplosionInfo->m_fLightsTime;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_fLightsTime = value;
			}
		}
		property uint32_t Type
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeExplosionInfo, 0);
				return NativeExplosionInfo->m_nType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeExplosionInfo);
				NativeExplosionInfo->m_nType = value;
			}
		}

	internal:
		IVExplosionInfo(tExplosionInfo* nativePtr);

	internal:
		tExplosionInfo* NativeExplosionInfo;
	};

	public ref class IVExplosion
	{
	public:
		static property array<IVExplosionInfo>^ ExplosionInfo
		{
		public:
			array<IVExplosionInfo>^ get()
			{
				tExplosionInfo* info = CExplosion::ms_ExplosionInfo;
				NULLPTR_CHECK_WITH_RETURN(info, nullptr);

				array<IVExplosionInfo>^ arr = gcnew array<IVExplosionInfo>(25);

				for (int i = 0; i < arr->Length; i++)
					arr[i] = IVExplosionInfo(&info[i]);

				return arr;
			}
			void set(array<IVExplosionInfo>^ value)
			{
				NULLPTR_CHECK(value);

				tExplosionInfo* info = CExplosion::ms_ExplosionInfo;
				NULLPTR_CHECK(info);

				for (int i = 0; i < value->Length; i++)
					info[i] = *value[i].NativeExplosionInfo;
			}
		}
	};
}