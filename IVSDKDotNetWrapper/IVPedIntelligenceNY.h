#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedIntelligenceNY : public IVPedIntelligence
	{
	public:
		property UIntPtr EventHandler
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedIntelligenceNY, UIntPtr::Zero);
				return UIntPtr(NativePedIntelligenceNY->m_pEventHandler);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				NativePedIntelligenceNY->m_pEventHandler = (uint32_t*)value.ToPointer();
			}
		}
		property UIntPtr EventScanner
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedIntelligenceNY, UIntPtr::Zero);
				return UIntPtr(NativePedIntelligenceNY->m_pEventScanner);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				NativePedIntelligenceNY->m_pEventScanner = (uint32_t*)value.ToPointer();
			}
		}

	public:
		static IVPedIntelligenceNY^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

	internal:
		IVPedIntelligenceNY(CPedIntelligenceNY* nativePedIntelligenceNY);

	internal:
		CPedIntelligenceNY* NativePedIntelligenceNY;
	};
}