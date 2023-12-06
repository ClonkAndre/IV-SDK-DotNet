#pragma once

namespace IVSDKDotNet
{
	public ref class IVPad
	{
	public:
		property array<IVPadValues>^ Values
		{
		public:
			array<IVPadValues>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePad, nullptr);

				array<IVPadValues>^ arr = gcnew array<IVPadValues>(187);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = IVPadValues(&NativePad->m_aValues[i]);

				return arr;
			}
			void set(array<IVPadValues>^ value)
			{
				NULLPTR_CHECK(NativePad);
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					NativePad->m_aValues[i] = *value[i].NativePadValues;
			}
		}
		property bool IsUsingKeyboardForAim
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePad, false);
				return NativePad->m_bIsUsingKeyboardForAim;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePad);
				NativePad->m_bIsUsingKeyboardForAim = value;
			}
		}
		property bool IsUsingKeyboardForHeli
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePad, false);
				return NativePad->m_bIsUsingKeyboardForHeli;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePad);
				NativePad->m_bIsUsingKeyboardForHeli = value;
			}
		}
		property uint32_t LastUpdateTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePad, 0);
				return NativePad->m_bIsUsingKeyboardForHeli;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePad);
				NativePad->m_bIsUsingKeyboardForHeli = value;
			}
		}

	public:
		static IVPad^ GetPad();

	internal:
		IVPad(CPad* nativePtr);

	internal:
		CPad* NativePad;
	};
}