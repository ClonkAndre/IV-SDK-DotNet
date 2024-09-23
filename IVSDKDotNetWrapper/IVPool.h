#pragma once

namespace IVSDKDotNet
{
	public ref class IVPool
	{
	public:
		property uint32_t Count
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePool, 0);
				return GetNativePool<uint32_t>()->m_nCount;
			}
		}
		property uint32_t EntrySize
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePool, 0);
				return GetNativePool<uint32_t>()->m_nEntrySize;
			}
		}
		property int32_t Top
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePool, 0);
				return GetNativePool<uint32_t>()->m_nTop;
			}
		}
		property uint32_t Used
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePool, 0);
				return GetNativePool<uint32_t>()->m_nUsed;
			}
		}
		property bool Allocated
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePool, false);
				return GetNativePool<uint32_t>()->m_bAllocated;
			}
		}

	public:
		/// <summary>
		/// Gets a pointer to an object from this slot in the pool.
		/// </summary>
		UIntPtr Get(int slot);

		/// <summary>
		/// Gets a pointer to an object from this handle.
		/// </summary>
		UIntPtr GetAt(uint32_t nHandle);

		/// <summary>
		/// Gets the handle of an object.
		/// </summary>
		uint32_t GetIndex(UIntPtr pObject);

		/// <summary>
		/// I assume this allocates a new object in this pool.
		/// </summary>
		UIntPtr New();

		/// <summary>
		/// Checks if the object at the given slot is valid.
		/// </summary>
		bool IsValid(int slot);

	public:
		/// <summary>
		/// Gets a IVPool object from the given type.
		/// </summary>
		static IVPool^ GetFromType(ePool type);

	internal:
		template<typename T>
		IVPool(T* nativePtr, ePool type);

		template<typename T>
		CPool<T>* GetNativePool();

	internal:
		uint32_t* NativePool;
		ePool PoolType;
	};
}