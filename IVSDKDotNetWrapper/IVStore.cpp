#include "pch.h"
#include "IVStore.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVStore::IVStore(uint32_t* nativePtr, eStoreType storeType)
	{
		NULLPTR_CHECK(nativePtr);
		NativeStore = nativePtr;
		StoreType = storeType;
	}

	// - - - Methods / Functions - - -

	template<typename T>
	CStore<T>* IVStore::GetNativeStore()
	{
		return (CStore<T>*)NativeStore;
	}

}