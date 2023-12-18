#include "pch.h"
#include "IVValueHistoryItem.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVValueHistoryItem::IVValueHistoryItem(tValueHistoryItem* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeValueHistoryItem = nativePtr;
	}
}