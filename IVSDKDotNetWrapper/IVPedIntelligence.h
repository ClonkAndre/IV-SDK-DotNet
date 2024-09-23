#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedIntelligence
	{
	public:
		property UIntPtr OwnerPed
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedIntelligence, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePedIntelligence->m_pOwnerPed, UIntPtr::Zero);
				return UIntPtr(NativePedIntelligence->m_pOwnerPed);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				NativePedIntelligence->m_pOwnerPed = (CPed*)value.ToPointer();
			}
		}
		property IVPedTasks^ Tasks
		{
		public:
			IVPedTasks^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedIntelligence, nullptr);
				NULLPTR_CHECK_WITH_RETURN(&NativePedIntelligence->m_Tasks, nullptr);
				return gcnew IVPedTasks(&NativePedIntelligence->m_Tasks);
			}
			void set(IVPedTasks^ value)
			{
				NULLPTR_CHECK(value);
				NativePedIntelligence->m_Tasks = *(CPedTasks*)value->NativePedTasks;
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

	public:
		static IVPedIntelligence^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

	internal:
		IVPedIntelligence(CPedIntelligence* nativePedIntelligence);

	internal:
		CPedIntelligence* NativePedIntelligence;
	};
}