#pragma once

namespace IVSDKDotNet
{
	public ref class IVSaveGarage
	{
	public:
		property uint8_t Type
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0);
				return NativeSaveGarage->Type;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->Type = value;
			}
		}
		property uint8_t State
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0);
				return NativeSaveGarage->State;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->State = value;
			}
		}
		property uint8_t Flags
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0);
				return NativeSaveGarage->Flags;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->Flags = value;
			}
		}
		property uint8_t pad
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0);
				return NativeSaveGarage->pad;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->pad = value;
			}
		}
		property float BaseX
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->BaseX;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->BaseX = value;
			}
		}
		property float BaseY
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->BaseY;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->BaseY = value;
			}
		}
		property float BaseZ
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->BaseZ;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->BaseZ = value;
			}
		}
		property float Delta1X
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->Delta1X;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->Delta1X = value;
			}
		}
		property float Delta1Y
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->Delta1Y;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->Delta1Y = value;
			}
		}
		property float Delta2X
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->Delta2X;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->Delta2X = value;
			}
		}
		property float Delta2Y
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->Delta2Y;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->Delta2Y = value;
			}
		}
		property float CeilingZ
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->CeilingZ;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->CeilingZ = value;
			}
		}
		property float Delta1Length
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->Delta1Length;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->Delta1Length = value;
			}
		}
		property float Delta2Length
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->Delta2Length;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->Delta2Length = value;
			}
		}
		property float MinX
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->MinX;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->MinX = value;
			}
		}
		property float MaxX
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->MaxX;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->MaxX = value;
			}
		}
		property float MinY
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->MinY;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->MinY = value;
			}
		}
		property float MaxY
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0.0F);
				return NativeSaveGarage->MaxY;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->MaxY = value;
			}
		}
		property int32_t TimeOfNextEvent
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0);
				return NativeSaveGarage->TimeOfNextEvent;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->TimeOfNextEvent = value;
			}
		}
		property uint32_t NameHash
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0);
				return NativeSaveGarage->NameHash;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->NameHash = value;
			}
		}
		property uint8_t Unk1
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0);
				return NativeSaveGarage->unk1;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->unk1 = value;
			}
		}
		property uint8_t OriginalType
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSaveGarage, 0);
				return NativeSaveGarage->OriginalType;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeSaveGarage);
				NativeSaveGarage->OriginalType = value;
			}
		}

	public:
		void CopyGarageIntoSaveGarage(IVGarage^ pGarage);
		void CopyGarageOutOfSaveGarage(IVGarage^ pGarage);

	internal:
		IVSaveGarage(CSaveGarage* nativePtr);

	internal:
		CSaveGarage* NativeSaveGarage;
	};
}