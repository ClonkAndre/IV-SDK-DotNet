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
		property float MinX
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0.0F);
				return static_cast<float>(NativeZone->MinX);
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeZone);

				if (value < INT16_MIN)
					value = INT16_MIN;
				if (value > INT16_MAX)
					value = INT16_MAX;

				NativeZone->MinX = static_cast<int16_t>(value);
			}
		}
		property float MinY
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0.0F);
				return static_cast<float>(NativeZone->MinY);
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeZone);

				if (value < INT16_MIN)
					value = INT16_MIN;
				if (value > INT16_MAX)
					value = INT16_MAX;

				NativeZone->MinY = static_cast<int16_t>(value);
			}
		}
		property float MinZ
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0.0F);
				return static_cast<float>(NativeZone->MinZ);
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeZone);

				if (value < INT16_MIN)
					value = INT16_MIN;
				if (value > INT16_MAX)
					value = INT16_MAX;

				NativeZone->MinZ = static_cast<int16_t>(value);
			}
		}
		property float MaxX
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0.0F);
				return static_cast<float>(NativeZone->MaxX);
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeZone);

				if (value < INT16_MIN)
					value = INT16_MIN;
				if (value > INT16_MAX)
					value = INT16_MAX;

				NativeZone->MaxX = static_cast<int16_t>(value);
			}
		}
		property float MaxY
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0.0F);
				return static_cast<float>(NativeZone->MaxY);
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeZone);

				if (value < INT16_MIN)
					value = INT16_MIN;
				if (value > INT16_MAX)
					value = INT16_MAX;

				NativeZone->MaxY = static_cast<int16_t>(value);
			}
		}
		property float MaxZ
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeZone, 0.0F);
				return static_cast<float>(NativeZone->MaxZ);
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeZone);

				if (value < INT16_MIN)
					value = INT16_MIN;
				if (value > INT16_MAX)
					value = INT16_MAX;

				NativeZone->MaxZ = static_cast<int16_t>(value);
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