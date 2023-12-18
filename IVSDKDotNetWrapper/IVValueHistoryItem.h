#pragma once

namespace IVSDKDotNet
{
	public value struct IVValueHistoryItem
	{
	public:
		property uint8_t Value
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeValueHistoryItem, 0);
				return NativeValueHistoryItem->m_nValue;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeValueHistoryItem);
				NativeValueHistoryItem->m_nValue = value;
			}
		}
		property uint32_t LastUpdateTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeValueHistoryItem, 0);
				return NativeValueHistoryItem->m_nLastUpdateTime;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeValueHistoryItem);
				NativeValueHistoryItem->m_nLastUpdateTime = value;
			}
		}

	internal:
		IVValueHistoryItem(tValueHistoryItem* nativePtr);

	internal:
		tValueHistoryItem* NativeValueHistoryItem;
	};
}