#pragma once

namespace IVSDKDotNet
{
	public ref class IVVehicleDoor
	{
	public:
		/// <summary>
		/// In the order from IVVehicleStruct.
		/// </summary>
		property uint32_t m_nBoneID
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0);
				return NativeVehicleDoor->m_nBoneID;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->m_nBoneID = value;
			}
		}
		property uint8_t _f4
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0);
				return NativeVehicleDoor->_f4;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->_f4 = value;
			}
		}
		/// <summary>
		/// Group for detach, needs to be higher than 0.
		/// </summary>
		property uint8_t m_nGroupID
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0);
				return NativeVehicleDoor->m_nGroupID;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->m_nGroupID = value;
			}
		}
		property float _f8
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0.0F);
				return NativeVehicleDoor->_f8;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->_f8 = value;
			}
		}
		property uint8_t _f10
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0);
				return NativeVehicleDoor->_f10;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->_f10 = value;
			}
		}
		/// <summary>
		/// 1 = closed, 4 = open?
		/// </summary>
		property uint8_t _f11
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0);
				return NativeVehicleDoor->_f11;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->_f11 = value;
			}
		}
		property uint8_t _f12
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0);
				return NativeVehicleDoor->_f12;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->_f12 = value;
			}
		}
		/// <summary>
		/// Door is moved?
		/// </summary>
		property uint8_t _f13
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0);
				return NativeVehicleDoor->_f13;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->_f13 = value;
			}
		}
		property float _f14
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0.0F);
				return NativeVehicleDoor->_f14;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->_f14 = value;
			}
		}
		property float _f18
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0.0F);
				return NativeVehicleDoor->_f18;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->_f18 = value;
			}
		}
		property float _f1c
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0.0F);
				return NativeVehicleDoor->_f1c;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->_f1c = value;
			}
		}
		property float _f24
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0.0F);
				return NativeVehicleDoor->_f24;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->_f24 = value;
			}
		}
		property float _f28
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleDoor, 0.0F);
				return NativeVehicleDoor->_f28;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleDoor);
				NativeVehicleDoor->_f28 = value;
			}
		}

	internal:
		IVVehicleDoor(CVehicleDoor* nativePtr);

	internal:
		CVehicleDoor* NativeVehicleDoor;
	};
}