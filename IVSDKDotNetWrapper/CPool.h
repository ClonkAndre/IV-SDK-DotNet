#pragma once

template<typename T>
class Native_CPool
{
public:
	uint8_t* m_pObjects;				// 00-04
	uint8_t* m_pFlags;					// 04-08
	uint32_t m_nCount;					// 08-0C
	uint32_t m_nEntrySize;				// 0C-10
	int32_t m_nTop;						// 10-14
	uint32_t m_nUsed;					// 14-18
	uint8_t m_bAllocated;				// 18-19
	uint8_t pad[3];						// 19-1C

	Native_CPool(int size, char* name, int entrySize)
	{
		((void(__thiscall*)(Native_CPool*, int, char*, int))(AddressSetter::Get(0x872F10, 0x3F3DB0)))(this, size, name, entrySize);
	}

	T* GetAt(uint32_t nHandle)
	{
		return ((T * (__thiscall*)(Native_CPool*, uint32_t))(AddressSetter::Get(0x26700, 0x92E00)))(this, nHandle);
	}
	uint32_t GetIndex(T* pObject)
	{
		return ((uint32_t(__thiscall*)(Native_CPool*, void*))(AddressSetter::Get(0x47230, 0xAFF10)))(this, pObject);
	}
	void* New()
	{
		return ((void* (__thiscall*)(Native_CPool*))(AddressSetter::Get(0x39CB0, 0x9F3A0)))(this);
	}

	// helper functions
	bool IsValid(int slot)
	{
		return !(m_pFlags[slot] & 0x80);
	}

	T* Get(int slot)
	{
		if (!IsValid(slot)) return nullptr;
		return (T*)&m_pObjects[m_nEntrySize * slot];
	}
};
VALIDATE_SIZE(Native_CPool<Native_CPed>, 0x1C);

namespace IVSDKDotNet {

	public ref class CPool
	{
	public:
		template<typename T>
		CPool(T* nativePtr, ePool type);

		/// <summary>
		/// Gets a new CPool object from the given type.
		/// </summary>
		static CPool^ GetFromType(ePool type);

		/// <summary>
		/// Gets the maximum number of elements this pool can have in it.
		/// </summary>
		property uint32_t Count {
			public: uint32_t get() { return ((Native_CPool<int>*)m_cNativePool)->m_nCount; }
		}

		/// <summary>
		/// Gets the size of this pool.
		/// </summary>
		property uint32_t EntrySize {
			public: uint32_t get() { return ((Native_CPool<int>*)m_cNativePool)->m_nEntrySize; }
		}

		/// <summary>
		/// Undocumented.
		/// </summary>
		property int32_t Top {
			public: int32_t get() { return ((Native_CPool<int>*)m_cNativePool)->m_nTop; }
		}

		/// <summary>
		/// Gets the amount of things there are currently in the world.
		/// </summary>
		property uint32_t Used {
			public: uint32_t get() { return ((Native_CPool<int>*)m_cNativePool)->m_nUsed; }
		}

		/// <summary>
		/// Gets the amount of pools that are currently allocated of this type?
		/// - I rather think it's a boolean that shows if this pool was allocted.
		/// </summary>
		property uint32_t Allocated {
			public: uint32_t get() { return ((Native_CPool<int>*)m_cNativePool)->m_bAllocated; }
		}

		/// <summary>
		/// Gets or sets the raw pointer of this pool.
		/// </summary>
		property uint32_t* PoolPointer {
			public:
				uint32_t*	get()					{ return m_cNativePool; }
				void		set(uint32_t* value)	{ m_cNativePool = value; }
		}

		/// <summary>
		/// Gets the type of this pool.
		/// </summary>
		property ePool Type {
			public: ePool get() { return m_eType; }
			private: void set(ePool value) { m_eType = value; }
		}

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
		/// Undocumented.
		/// </summary>
		UIntPtr New();

		/// <summary>
		/// Checks if the object at the given slot is valid.
		/// </summary>
		bool IsValid(int slot);

	internal:
		template<typename T>
		Native_CPool<T>* GetNativePool();

	private:
		uint32_t* m_cNativePool;
		ePool m_eType;
	};

}