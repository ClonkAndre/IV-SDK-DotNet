#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedMoveBlendOnFoot
	{
	public:
		property float MoveState
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedMoveBlendOnFoot, 0.0F);
				return NativePedMoveBlendOnFoot->m_fMoveState;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePedMoveBlendOnFoot);
				NativePedMoveBlendOnFoot->m_fMoveState = value;
			}
		}
		property float MoveLeanAmount
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedMoveBlendOnFoot, 0.0F);
				return NativePedMoveBlendOnFoot->m_fMoveLeanAmount;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePedMoveBlendOnFoot);
				NativePedMoveBlendOnFoot->m_fMoveLeanAmount = value;
			}
		}
		property UIntPtr Ped
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedMoveBlendOnFoot, UIntPtr::Zero);
				return UIntPtr(NativePedMoveBlendOnFoot->m_pPed);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePedMoveBlendOnFoot);
				UINTPTR_ZERO_CHECK(value);
				NativePedMoveBlendOnFoot->m_pPed = (CPed*)value.ToPointer();
			}
		}
		property float MoveTurn
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedMoveBlendOnFoot, 0.0F);
				return NativePedMoveBlendOnFoot->m_fMoveTurn;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePedMoveBlendOnFoot);
				NativePedMoveBlendOnFoot->m_fMoveTurn = value;
			}
		}
		property uint32_t UnkFlags
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedMoveBlendOnFoot, 0);
				return NativePedMoveBlendOnFoot->m_nUnkFlags;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePedMoveBlendOnFoot);
				NativePedMoveBlendOnFoot->m_nUnkFlags = value;
			}
		}
		property float MoveAnimSpeed
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedMoveBlendOnFoot, 0.0F);
				return NativePedMoveBlendOnFoot->m_fMoveAnimSpeed;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePedMoveBlendOnFoot);
				NativePedMoveBlendOnFoot->m_fMoveAnimSpeed = value;
			}
		}
		property float MaxMoveBlendRatio
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedMoveBlendOnFoot, 0.0F);
				return NativePedMoveBlendOnFoot->m_fMaxMoveBlendRatio;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePedMoveBlendOnFoot);
				NativePedMoveBlendOnFoot->m_fMaxMoveBlendRatio = value;
			}
		}

	internal:
		IVPedMoveBlendOnFoot(CPedMoveBlendOnFoot* nativePtr);

	internal:
		CPedMoveBlendOnFoot* NativePedMoveBlendOnFoot;
	};
}