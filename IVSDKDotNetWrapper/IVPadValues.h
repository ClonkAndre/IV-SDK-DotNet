#pragma once

namespace IVSDKDotNet
{
	public value struct IVPadValues
	{
	public:
		property uint32_t vfTable
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePadValues, 0);
				return NativePadValues->m_vfTable;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePadValues);
				NativePadValues->m_vfTable = value;
			}
		}
		property uint8_t Unknown4
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePadValues, 0);
				return NativePadValues->m_nUnknown4;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePadValues);
				NativePadValues->m_nUnknown4 = value;
			}
		}
		property uint8_t Context
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePadValues, 0);
				return NativePadValues->m_nContext;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePadValues);
				NativePadValues->m_nContext = value;
			}
		}
		property uint8_t CurrentValue
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePadValues, 0);
				return NativePadValues->m_nCurrentValue;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePadValues);
				NativePadValues->m_nCurrentValue = value;
			}
		}
		property uint8_t LastValue
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePadValues, 0);
				return NativePadValues->m_nLastValue;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePadValues);
				NativePadValues->m_nLastValue = value;
			}
		}
		property uint8_t HistoryIndex
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePadValues, 0);
				return NativePadValues->m_nHistoryIndex;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePadValues);
				NativePadValues->m_nHistoryIndex = value;
			}
		}
		property IVValueHistory^ History
		{
		public:
			IVValueHistory^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePadValues, nullptr);
				return gcnew IVValueHistory(NativePadValues->m_pHistory);
			}
			void set(IVValueHistory^ value)
			{
				NULLPTR_CHECK(NativePadValues);
				NULLPTR_CHECK(value);
				NativePadValues->m_pHistory = value->NativeValueHistory;
			}
		}

	internal:
		IVPadValues(tPadValues* nativePtr);

	internal:
		tPadValues* NativePadValues;
	};
}