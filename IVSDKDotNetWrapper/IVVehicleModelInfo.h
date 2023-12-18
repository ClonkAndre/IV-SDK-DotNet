#pragma once

namespace IVSDKDotNet
{
	public ref class IVVehicleModelInfo : IVBaseModelInfo
	{
	public:
		static property array<Color>^ VehicleColourTable
		{
		public:
			array<Color>^ get()
			{
				CRGBA* ptr = CVehicleModelInfo::ms_vehicleColourTable;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<Color>^ arr = gcnew array<Color>(196);

				for(int i = 0; i < arr->Length; i++)
				{
					CRGBA crgba = ptr[i];
					arr[i] = Color::FromArgb(crgba.a, crgba.r, crgba.g, crgba.b);
				}

				return arr;
			}
			void set(array<Color>^ value)
			{
				NULLPTR_CHECK(value);

				CRGBA* ptr = CVehicleModelInfo::ms_vehicleColourTable;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
				{
					Color color = value[i];

					CRGBA crgba;
					crgba.a = color.A;
					crgba.r = color.R;
					crgba.g = color.G;
					crgba.b = color.B;
					ptr[i] = crgba;
				}
			}
		}

	public:
		property String^ GameName
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleModelInfo, String::Empty);
				return gcnew String(NativeVehicleModelInfo->m_sGameName);
			}
		}
		property uint32_t VehicleType
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleModelInfo, 0);
				return NativeVehicleModelInfo->m_nVehicleType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicleModelInfo);
				NativeVehicleModelInfo->m_nVehicleType = value;
			}
		}
		property uint32_t HandlingId
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleModelInfo, 0);
				return NativeVehicleModelInfo->m_nHandlingId;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicleModelInfo);
				NativeVehicleModelInfo->m_nHandlingId = value;
			}
		}

		property int16_t AnimIndex2
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleModelInfo, 0);
				return NativeVehicleModelInfo->m_nAnimIndex2;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativeVehicleModelInfo);
				NativeVehicleModelInfo->m_nAnimIndex2 = value;
			}
		}
		property IVVehicleStructure^ VehicleStruct
		{
		public:
			IVVehicleStructure^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleModelInfo, nullptr);
				return gcnew IVVehicleStructure(NativeVehicleModelInfo->m_pVehicleStruct);
			}
			void set(IVVehicleStructure^ value)
			{
				NULLPTR_CHECK(NativeVehicleModelInfo);
				NULLPTR_CHECK(value);
				NativeVehicleModelInfo->m_pVehicleStruct = value->NativeVehicleStructure;
			}
		}
		property array<uint32_t>^ LiveryHashes
		{
			public:
				array<uint32_t>^ get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeVehicleModelInfo, nullptr);

					array<uint32_t>^ arr = gcnew array<uint32_t>(4);

					for(int i = 0; i < arr->Length; i++)
						arr[i] = NativeVehicleModelInfo->m_nLiveryHashes[i];

					return arr;
				}
				void set(array<uint32_t>^ value)
				{
					NULLPTR_CHECK(NativeVehicleModelInfo);
					NULLPTR_CHECK(value);

					for(int i = 0; i < value->Length; i++)
						NativeVehicleModelInfo->m_nLiveryHashes[i] = value[i];
				}
		}

	public:
		/// <summary>
		/// Sets the center of mass and mass in the phBound based on the center of mass param and fMass off handling.
		/// </summary>
		/// <param name="pHandling"></param>
		/// <param name="pCenterOfMass"></param>
		void SetHandlingParams(IVHandlingData^ pHandling, Vector3 pCenterOfMass);
		static int GetNumberOfSeats(int modelIndex);
		// TODO
		//void ChooseVehicleColour(uint8_t* color1, uint8_t* color2, uint8_t* color3, uint8_t* color4, int startingColor);
		void SetSecondaryAnimGroup(String^ group);

	internal:
		IVVehicleModelInfo(CVehicleModelInfo* nativePtr);

	internal:
		CVehicleModelInfo* NativeVehicleModelInfo;
	};
}