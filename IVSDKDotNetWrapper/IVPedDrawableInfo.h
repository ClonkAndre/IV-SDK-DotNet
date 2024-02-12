#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedDrawableInfo
	{
	public:
		property array<uint8_t>^ Drawables
		{
		public:
			array<uint8_t>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedDrawableInfo, nullptr);

				uint8_t* ptr = NativePedDrawableInfo->m_nDrawables;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<uint8_t>^ arr = gcnew array<uint8_t>(11);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = ptr[i];

				return arr;
			}
			void set(array<uint8_t>^ value)
			{
				NULLPTR_CHECK(NativePedDrawableInfo);
				NULLPTR_CHECK(value);

				uint8_t* ptr = NativePedDrawableInfo->m_nDrawables;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = value[i];
			}
		}
		property array<uint8_t>^ Textures
		{
		public:
			array<uint8_t>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedDrawableInfo, nullptr);

				uint8_t* ptr = NativePedDrawableInfo->m_nTextures;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<uint8_t>^ arr = gcnew array<uint8_t>(11);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = ptr[i];

				return arr;
			}
			void set(array<uint8_t>^ value)
			{
				NULLPTR_CHECK(NativePedDrawableInfo);
				NULLPTR_CHECK(value);

				uint8_t* ptr = NativePedDrawableInfo->m_nTextures;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = value[i];
			}
		}
		property uint32_t PedType
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedDrawableInfo, 0);
				return NativePedDrawableInfo->m_nPedType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePedDrawableInfo);
				NativePedDrawableInfo->m_nPedType = value;
			}
		}

	public:
		static IVPedDrawableInfo^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

	internal:
		IVPedDrawableInfo(tPedDrawableInfo* nativePtr);

	internal:
		tPedDrawableInfo* NativePedDrawableInfo;
	};
}