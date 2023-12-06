#pragma once

namespace IVSDKDotNet
{
	public ref class IVZone
	{
	public:
		property String^ InfoLabel
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, String::Empty);
				return gcnew String(NativeZone->InfoLabel);
			}
		}
		property String^ TextLabel
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, String::Empty);
				return gcnew String(NativeZone->TextLabel);
			}
		}
		property int16_t MinX
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0);
				return NativeZone->MinX;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativeZone);
				NativeZone->MinX = value;
			}
		}
		property int16_t MinY
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0);
				return NativeZone->MinY;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativeZone);
				NativeZone->MinY = value;
			}
		}
		property int16_t MinZ
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0);
				return NativeZone->MinZ;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativeZone);
				NativeZone->MinZ = value;
			}
		}
		property int16_t MaxX
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0);
				return NativeZone->MaxX;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativeZone);
				NativeZone->MaxX = value;
			}
		}
		property int16_t MaxY
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0);
				return NativeZone->MaxY;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativeZone);
				NativeZone->MaxY = value;
			}
		}
		property int16_t MaxZ
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0);
				return NativeZone->MaxZ;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativeZone);
				NativeZone->MaxZ = value;
			}
		}
		property int16_t Unk1
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0);
				return NativeZone->unk1;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativeZone);
				NativeZone->unk1 = value;
			}
		}
		property int16_t Unk2
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0);
				return NativeZone->unk2;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativeZone);
				NativeZone->unk2 = value;
			}
		}
		property uint8_t PopulationType
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0);
				return NativeZone->PopulationType;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeZone);
				NativeZone->PopulationType = value;
			}
		}
		property uint8_t Scumminess
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0);
				return NativeZone->Scumminess;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeZone);
				NativeZone->Scumminess = value;
			}
		}

	internal:
		IVZone(CZone* nativePtr);

	internal:
		CZone* NativeZone;
	};
}