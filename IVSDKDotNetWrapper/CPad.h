#pragma once

struct Native_tValueHistoryItem
{
	uint8_t m_nValue;				//0x0
	uint8_t pad[3];					//0x1
	uint32_t m_nLastUpdateTime;		//0x4
};
VALIDATE_SIZE(Native_tValueHistoryItem, 0x8);

class Native_tValueHistory
{
public:
	Native_tValueHistoryItem m_aItems[64];		//0x0
};
VALIDATE_SIZE(Native_tValueHistory, 0x200);

struct Native_tPadValues
{
	uint32_t m_vfTable;					//0x0
	uint8_t m_nUnknown4;				//0x4
	uint8_t m_nContext;					//0x5
	uint8_t m_nCurrentValue;			//0x6
	uint8_t m_nLastValue;				//0x7
	uint8_t m_nHistoryIndex;			//0x8
	uint8_t pad[3];						//0x9
	Native_tValueHistory* m_pHistory;	//0xC
};
VALIDATE_SIZE(Native_tPadValues, 0x10);

class Native_CPad
{
public:
	uint8_t pad[0x2698];						// 0000-328C
	Native_tPadValues m_aValues[187];			// 2698-3248
	uint8_t pad2[0x41];							// 3248-3289
	uint8_t m_bIsUsingKeyboardForAim;			// 3289-328A
	uint8_t pad3[0x3];							// 324A-328D
	uint8_t m_bIsUsingKeyboardForHeli;			// 328D-328E
	uint8_t pad4[0x7DE];						// 328E-3A6C
	uint32_t m_nLastUpdateTime;					// 3A6C-3A70
	uint8_t pad5[0x14];							// 3A70-3A84

	static Native_CPad* GetPad()
	{
		return ((Native_CPad* (__cdecl*)())(AddressSetter::Get(0x3C3900, 0x46A110)))();
	}
};
VALIDATE_SIZE(Native_CPad, 0x3A84);
VALIDATE_OFFSET(Native_CPad, m_bIsUsingKeyboardForAim, 0x3289);
VALIDATE_OFFSET(Native_CPad, m_bIsUsingKeyboardForHeli, 0x328D);
VALIDATE_OFFSET(Native_CPad, m_nLastUpdateTime, 0x3A6C);
VALIDATE_OFFSET(Native_CPad, m_aValues, 0x2698);

Native_CPad* NativePads = (Native_CPad*)AddressSetter::Get(0xCFB818, 0xDD8EA8); // Pads[4]; 0 = player 1, 1 = player 2, 2 = debug, 3 = unknown

namespace IVSDKDotNet {

	public ref class tValueHistoryItem
	{
	public:
		tValueHistoryItem(Native_tValueHistoryItem* nativePtr);

		property uint8_t Value {
			uint8_t	get()				{ return ValueHistoryItemPointer->m_nValue; }
			void	set(uint8_t value)	{ ValueHistoryItemPointer->m_nValue = value; }
		}

		property uint32_t LastUpdateTime {
			uint32_t	get()				{ return ValueHistoryItemPointer->m_nLastUpdateTime; }
			void		set(uint32_t value) { ValueHistoryItemPointer->m_nLastUpdateTime = value; }
		}

		property Native_tValueHistoryItem* ValueHistoryItemPointer {
			public:
				Native_tValueHistoryItem*	get()									{ return m_cNativeValueHistoryItem; }
				void						set(Native_tValueHistoryItem* value)	{ m_cNativeValueHistoryItem = value; }
		}

	private:
		Native_tValueHistoryItem* m_cNativeValueHistoryItem;
	};

	public ref class tValueHistory
	{
	public:
		tValueHistory(Native_tValueHistory* nativePtr);

		property array<tValueHistoryItem^>^ Items {
			array<tValueHistoryItem^>^ get()
			{
				array<tValueHistoryItem^>^ arr = gcnew array<tValueHistoryItem^>(64);

				for (int i = 0; i < arr->Length; i++)
				{
					arr[i] = gcnew tValueHistoryItem(&ValueHistoryPointer->m_aItems[i]);
				}

				return arr;
			}
			void set(array<tValueHistoryItem^>^ value)
			{
				for (int i = 0; i < value->Length; i++)
				{
					ValueHistoryPointer->m_aItems[i] = *value[i]->ValueHistoryItemPointer;
				}
			}
		}

		property Native_tValueHistory* ValueHistoryPointer {
			public:
				Native_tValueHistory*	get()								{ return m_cNativeValueHistory; }
				void					set(Native_tValueHistory* value)	{ m_cNativeValueHistory = value; }
		}

	private:
		Native_tValueHistory* m_cNativeValueHistory;
	};

	public ref class tPadValues
	{
	public:
		tPadValues(Native_tPadValues* nativePtr);

		property uint32_t vfTable {
			uint32_t	get()				{ return PadValuePointer->m_vfTable; }
			void		set(uint32_t value) { PadValuePointer->m_vfTable = value; }
		}

		property uint8_t Unknown4 {
			uint8_t	get()				{ return PadValuePointer->m_nUnknown4; }
			void	set(uint8_t value)	{ PadValuePointer->m_nUnknown4 = value; }
		}

		property uint8_t Context {
			uint8_t	get()				{ return PadValuePointer->m_nContext; }
			void	set(uint8_t value)	{ PadValuePointer->m_nContext = value; }
		}

		property uint8_t CurrentValue {
			uint8_t	get()				{ return PadValuePointer->m_nCurrentValue; }
			void	set(uint8_t value)	{ PadValuePointer->m_nCurrentValue = value; }
		}

		property uint8_t LastValue {
			uint8_t	get()				{ return PadValuePointer->m_nLastValue; }
			void	set(uint8_t value)	{ PadValuePointer->m_nLastValue = value; }
		}

		property uint8_t HistoryIndex {
			uint8_t	get()				{ return PadValuePointer->m_nHistoryIndex; }
			void	set(uint8_t value)	{ PadValuePointer->m_nHistoryIndex = value; }
		}

		property tValueHistory^ History {
			tValueHistory^ get() { 
				Native_tValueHistory* ptr = PadValuePointer->m_pHistory;

				if (ptr)
					return gcnew tValueHistory(ptr);

				return nullptr;
			}
			void set(tValueHistory^ value) { PadValuePointer->m_pHistory = value->ValueHistoryPointer; }
		}

		property Native_tPadValues* PadValuePointer {
			public:
				Native_tPadValues*	get()							{ return m_cNativePadValues; }
				void				set(Native_tPadValues* value)	{ m_cNativePadValues = value; }
		}

	private:
		Native_tPadValues* m_cNativePadValues;
	};

	public ref class CPad
	{
	public:
		CPad(Native_CPad* nativePtr);

		static CPad^ FromPointer(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		static CPad^ GetPad();

		/// <summary>
		/// 0 = Player 1, 1 = Player 2, 2 = Debug, 3 = Unknown.
		/// </summary>
		property static array<CPad^>^ Pads {
			array<CPad^>^ get()
			{
				array<CPad^>^ arr = gcnew array<CPad^>(4);

				for (int i = 0; i < arr->Length; i++)
				{
					arr[i] = gcnew CPad(&NativePads[i]);
				}

				return arr;
			}
			void set(array<CPad^>^ value)
			{
				for (int i = 0; i < value->Length; i++)
				{
					NativePads[i] = *value[i]->PadPointer;
				}
			}
		}

		property array<tPadValues^>^ Values {
			array<tPadValues^>^ get()
			{
				array<tPadValues^>^ arr = gcnew array<tPadValues^>(187);

				for (int i = 0; i < arr->Length; i++)
				{
					arr[i] = gcnew tPadValues(&PadPointer->m_aValues[i]);
				}

				return arr;
			}
			void set(array<tPadValues^>^ value)
			{
				for (int i = 0; i < value->Length; i++)
				{
					PadPointer->m_aValues[i] = *value[i]->PadValuePointer;
				}
			}
		}

		property bool IsUsingKeyboardForAim {
			bool get()				{ return PadPointer->m_bIsUsingKeyboardForAim; }
			void set(bool value)	{ PadPointer->m_bIsUsingKeyboardForAim = value; }
		}

		property bool IsUsingKeyboardForHeli {
			bool get() { return PadPointer->m_bIsUsingKeyboardForHeli; }
			void set(bool value) { PadPointer->m_bIsUsingKeyboardForHeli = value; }
		}

		property uint32_t LastUpdateTime {
			uint32_t	get()				{ return PadPointer->m_nLastUpdateTime; }
			void		set(uint32_t value) { PadPointer->m_nLastUpdateTime = value; }
		}

		property Native_CPad* PadPointer {
			public:
				Native_CPad*	get()					{ return m_cNativePad; }
				void			set(Native_CPad* value) { m_cNativePad = value; }
		}

	private:
		Native_CPad* m_cNativePad;
	};

}