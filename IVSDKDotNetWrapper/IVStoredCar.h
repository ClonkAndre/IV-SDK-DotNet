#pragma once

namespace IVSDKDotNet
{
	public ref class IVStoredCar
	{
	public:
		property float CoorX
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0.0F);
				return NativeStoredCar->CoorX;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->CoorX = value;
			}
		}
		property float CoorY
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0.0F);
				return NativeStoredCar->CoorY;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->CoorY = value;
			}
		}
		property float CoorZ
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0.0F);
				return NativeStoredCar->CoorZ;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->CoorZ = value;
			}
		}
		property uint32_t FlagsLocal
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->FlagsLocal;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->FlagsLocal = value;
			}
		}
		property uint16_t ModelIndex
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->ModelIndex;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->ModelIndex = value;
			}
		}
		property uint16_t Bits
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->Bits;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->Bits = value;
			}
		}
		property uint8_t Colour1
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->Colour1;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->Colour1 = value;
			}
		}
		property uint8_t Colour2
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->Colour2;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->Colour2 = value;
			}
		}
		property uint8_t Colour3
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->Colour3;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->Colour3 = value;
			}
		}
		property uint8_t Colour4
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->Colour4;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->Colour4 = value;
			}
		}
		property uint32_t Extras
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->Extras;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->Extras = value;
			}
		}
		property uint32_t PaintJob
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->PaintJob;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->PaintJob = value;
			}
		}
		property uint8_t Unk2
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->unk2;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->unk2 = value;
			}
		}
		property int8_t FrontX
		{
		public:
			int8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->iFrontX;
			}
			void set(int8_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->iFrontX = value;
			}
		}
		property int8_t FrontY
		{
		public:
			int8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->iFrontY;
			}
			void set(int8_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->iFrontY = value;
			}
		}
		property int8_t FrontZ
		{
		public:
			int8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStoredCar, 0);
				return NativeStoredCar->iFrontZ;
			}
			void set(int8_t value)
			{
				NULLPTR_CHECK(NativeStoredCar);
				NativeStoredCar->iFrontZ = value;
			}
		}

	public:
		void StoreCar(UIntPtr pCar);
		void RestoreCar();

	internal:
		IVStoredCar(CStoredCar* nativePtr);

	internal:
		CStoredCar* NativeStoredCar;
	};
}

