#pragma once

namespace IVSDKDotNet
{
	public ref class IVGarage
	{
	public:
		property float BaseX
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->BaseX;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->BaseX = value;
			}
		}
		property float BaseY
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->BaseY;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->BaseY = value;
			}
		}
		property float BaseZ
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->BaseZ;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->BaseZ = value;
			}
		}
		property float Delta1X
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->Delta1X;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->Delta1X = value;
			}
		}
		property float Delta1Y
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->Delta1Y;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->Delta1Y = value;
			}
		}
		property float Delta2X
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->Delta2X;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->Delta2X = value;
			}
		}
		property float Delta2Y
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->Delta2Y;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->Delta2Y = value;
			}
		}
		property float CeilingZ
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->CeilingZ;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->CeilingZ = value;
			}
		}
		property float Delta1Length
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->Delta1Length;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->Delta1Length = value;
			}
		}
		property float Delta2Length
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->Delta2Length;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->Delta2Length = value;
			}
		}
		property float MinX
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->MinX;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->MinX = value;
			}
		}
		property float MaxX
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->MaxX;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->MaxX = value;
			}
		}
		property float MinY
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->MinY;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->MinY = value;
			}
		}
		property float MaxY
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0.0F);
				return NativeGarage->MaxY;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->MaxY = value;
			}
		}
		property uint32_t TimeOfNextEvent
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0);
				return NativeGarage->TimeOfNextEvent;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->TimeOfNextEvent = value;
			}
		}
		property UIntPtr CarToCollect
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, UIntPtr::Zero);
				return UIntPtr(NativeGarage->pCarToCollect);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeGarage);
				UINTPTR_ZERO_CHECK(value);
				NativeGarage->pCarToCollect = (CVehicle*)value.ToPointer();
			}
		}
		property uint32_t NameHash
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0);
				return NativeGarage->NameHash;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->NameHash = value;
			}
		}
		property uint8_t Type
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0);
				return NativeGarage->Type;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->Type = value;
			}
		}
		property uint8_t State
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0);
				return NativeGarage->State;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->State = value;
			}
		}
		property uint8_t OriginalType
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0);
				return NativeGarage->OriginalType;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->OriginalType = value;
			}
		}
		property uint8_t Flags
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGarage, 0);
				return NativeGarage->Flags;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeGarage);
				NativeGarage->Flags = value;
			}
		}

	public:
		bool IsPointInsideGarage(Vector3 point);
		void PlayerArrestedOrDied();
		void StoreAndRemoveCarsForThisHideOut(IVStoredCar^ aStoredCars, bool unk); // TODO: This should probably be a array of IVStoredCars
		void TidyUpGarageClose();
		void Update();

	internal:
		IVGarage(CGarage* nativePtr);

	internal:
		CGarage* NativeGarage;
	};
}