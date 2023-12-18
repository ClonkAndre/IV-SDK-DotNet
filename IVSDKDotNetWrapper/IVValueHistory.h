#pragma once

namespace IVSDKDotNet
{
	public ref class IVValueHistory
	{
	public:
		property array<IVValueHistoryItem>^ Items
		{
		public:
			array<IVValueHistoryItem>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeValueHistory, nullptr);
				
				array<IVValueHistoryItem>^ arr = gcnew array<IVValueHistoryItem>(64);

				for(int i = 0; i < arr->Length; i++)
				{
					arr[i] = IVValueHistoryItem(&NativeValueHistory->m_aItems[i]);
				}

				return arr;
			}
			void set(array<IVValueHistoryItem>^ value)
			{
				NULLPTR_CHECK(NativeValueHistory);
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					NativeValueHistory->m_aItems[i] = *value[i].NativeValueHistoryItem;
			}
		}

	internal:
		IVValueHistory(tValueHistory* nativePtr);

	internal:
		tValueHistory* NativeValueHistory;
	};
}