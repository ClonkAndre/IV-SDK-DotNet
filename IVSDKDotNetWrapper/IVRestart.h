#pragma once

namespace IVSDKDotNet
{
	public ref class IVRestart
	{
	public:
		static property uint32_t NumberOfHospitalRestarts
		{
		public:
			uint32_t get()
			{
				return CRestart::NumberOfHospitalRestarts;
			}
			void set(uint32_t value)
			{
				CRestart::NumberOfHospitalRestarts = value;
			}
		}
		static property uint32_t NumberOfPoliceRestarts
		{
		public:
			uint32_t get()
			{
				return CRestart::NumberOfPoliceRestarts;
			}
			void set(uint32_t value)
			{
				CRestart::NumberOfPoliceRestarts = value;
			}
		}
		static property uint32_t NumberOfSafehouses
		{
		public:
			uint32_t get()
			{
				return CRestart::NumberOfSafehouses;
			}
			void set(uint32_t value)
			{
				CRestart::NumberOfSafehouses = value;
			}
		}

		static property array<Vector3>^ HospitalRestartPoints
		{
		public:
			array<Vector3>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CRestart::HospitalRestartPoints, nullptr);

				array<Vector3>^ arr = gcnew array<Vector3>(NumberOfHospitalRestarts);

				for(int i = 0; i < arr->Length; i++)
				{
					CVector_pad v = CRestart::HospitalRestartPoints[i];
					arr[i] = Vector3(v.x, v.y, v.z);
				}

				return arr;
			}
			void set(array<Vector3>^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(CRestart::HospitalRestartPoints);

				for(int i = 0; i < value->Length; i++)
				{
					Vector3 mVector = value[i];

					CVector_pad v;
					v.x = mVector.X;
					v.y = mVector.Y;
					v.z = mVector.Z;

					CRestart::HospitalRestartPoints[i] = v;
				}
			}
		}
		static property array<float>^ HospitalRestartHeadings
		{
		public:
			array<float>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CRestart::HospitalRestartHeadings, nullptr);

				array<float>^ arr = gcnew array<float>(NumberOfHospitalRestarts);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = CRestart::HospitalRestartHeadings[i];

				return arr;
			}
			void set(array<float>^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(CRestart::HospitalRestartHeadings);

				for(int i = 0; i < value->Length; i++)
					CRestart::HospitalRestartHeadings[i] = value[i];
			}
		}
		static property array<int>^ HospitalRestartWhenToUse
		{
		public:
			array<int>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CRestart::HospitalRestartWhenToUse, nullptr);

				array<int>^ arr = gcnew array<int>(NumberOfHospitalRestarts);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = CRestart::HospitalRestartWhenToUse[i];

				return arr;
			}
			void set(array<int>^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(CRestart::HospitalRestartWhenToUse);

				for(int i = 0; i < value->Length; i++)
					CRestart::HospitalRestartWhenToUse[i] = value[i];
			}
		}

		static property Vector3 PoliceRestartPoints
		{
		public:
			Vector3 get()
			{
				CVector_pad v = CRestart::PoliceRestartPoints;
				return Vector3(v.x, v.y, v.z);
			}
			void set(Vector3 value)
			{
				CVector_pad v;
				v.x = value.X;
				v.y = value.Y;
				v.z = value.Z;

				CRestart::PoliceRestartPoints = v;
			}
		}
		static property float PoliceRestartHeadings
		{
		public:
			float get()
			{
				return CRestart::PoliceRestartHeadings;
			}
			void set(float value)
			{
				CRestart::PoliceRestartHeadings = value;
			}
		}
		static property int PoliceRestartWhenToUse
		{
		public:
			int get()
			{
				return CRestart::PoliceRestartWhenToUse;
			}
			void set(int value)
			{
				CRestart::PoliceRestartWhenToUse = value;
			}
		}

		static property array<IVSafehouse>^ Safehouses
		{
		public:
			array<IVSafehouse>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CRestart::Safehouses, nullptr);

				array<IVSafehouse>^ arr = gcnew array<IVSafehouse>(NumberOfSafehouses);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = IVSafehouse(&CRestart::Safehouses[i]);

				return arr;
			}
			void set(array<IVSafehouse>^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(CRestart::HospitalRestartWhenToUse);

				for(int i = 0; i < value->Length; i++)
					CRestart::Safehouses[i] = *value[i].NativeSafehouse;
			}
		}

		static property bool OverrideRestart
		{
		public:
			bool get()
			{
				return CRestart::bOverrideRestart;
			}
			void set(bool value)
			{
				CRestart::bOverrideRestart = value;
			}
		}
		static property Vector3 OverridePosition
		{
		public:
			Vector3 get()
			{
				CVector_pad c = CRestart::OverridePosition;
				return Vector3(c.x, c.y, c.z);
			}
			void set(Vector3 value)
			{
				CVector_pad c;
				c.x = value.X;
				c.y = value.Y;
				c.z = value.Z;

				CRestart::OverridePosition = c;
			}
		}
		static property float OverrideHeading
		{
		public:
			float get()
			{
				return CRestart::OverrideHeading;
			}
			void set(float value)
			{
				CRestart::OverrideHeading = value;
			}
		}
		static property bool FadeInAfterNextDeath
		{
		public:
			bool get()
			{
				return CRestart::bFadeInAfterNextDeath;
			}
			void set(bool value)
			{
				CRestart::bFadeInAfterNextDeath = value;
			}
		}
		static property Vector3 ExtraHospitalRestartCoors
		{
		public:
			Vector3 get()
			{
				CVector_pad c = CRestart::ExtraHospitalRestartCoors;
				return Vector3(c.x, c.y, c.z);
			}
			void set(Vector3 value)
			{
				CVector_pad c;
				c.x = value.X;
				c.y = value.Y;
				c.z = value.Z;

				CRestart::ExtraHospitalRestartCoors = c;
			}
		}
		static property float ExtraHospitalRestartHeading
		{
		public:
			float get()
			{
				return CRestart::ExtraHospitalRestartHeading;
			}
			void set(float value)
			{
				CRestart::ExtraHospitalRestartHeading = value;
			}
		}
		static property uint32_t ExtraHospitalRestartWhenToUse
		{
		public:
			uint32_t get()
			{
				return CRestart::ExtraHospitalRestartWhenToUse;
			}
			void set(uint32_t value)
			{
				CRestart::ExtraHospitalRestartWhenToUse = value;
			}
		}
		static property Vector3 ExtraPoliceStationRestartCoors
		{
		public:
			Vector3 get()
			{
				CVector_pad c = CRestart::ExtraPoliceStationRestartCoors;
				return Vector3(c.x, c.y, c.z);
			}
			void set(Vector3 value)
			{
				CVector_pad c;
				c.x = value.X;
				c.y = value.Y;
				c.z = value.Z;

				CRestart::ExtraPoliceStationRestartCoors = c;
			}
		}
		static property float ExtraPoliceStationRestartHeading
		{
		public:
			float get()
			{
				return CRestart::ExtraPoliceStationRestartHeading;
			}
			void set(float value)
			{
				CRestart::ExtraPoliceStationRestartHeading = value;
			}
		}
		static property uint32_t ExtraPoliceStationRestartWhenToUse
		{
		public:
			uint32_t get()
			{
				return CRestart::ExtraPoliceStationRestartWhenToUse;
			}
			void set(uint32_t value)
			{
				CRestart::ExtraPoliceStationRestartWhenToUse = value;
			}
		}

	public:
		static bool Save();
		static bool Load();
	};
}