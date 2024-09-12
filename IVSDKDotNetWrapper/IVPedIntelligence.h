#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedIntelligence
	{
	public:
		property UIntPtr Ped
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedIntelligence, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePedIntelligence->m_pPed, UIntPtr::Zero);
				return UIntPtr(NativePedIntelligence->m_pPed);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				NativePedIntelligence->m_pPed = (CPed*)value.ToPointer();
			}
		}
		property float SenseRange1
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedIntelligence, 0.0F);
				return NativePedIntelligence->m_fSenseRange1;
			}
			void set(float value)
			{
				NativePedIntelligence->m_fSenseRange1 = value;
			}
		}
		property float SenseRange2
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedIntelligence, 0.0F);
				return NativePedIntelligence->m_fSenseRange2;
			}
			void set(float value)
			{
				NativePedIntelligence->m_fSenseRange2 = value;
			}
		}

	internal:
		IVPedIntelligence(CPedIntelligence* nativePedIntelligence);

	internal:
		CPedIntelligence* NativePedIntelligence;
	};
}