#pragma once

namespace IVSDKDotNet
{
	struct sPhoneInfo
	{
		uint32_t State; // 0000 - See ePhoneState enum for possible states
		uint32_t _f180; // 0004 - Always 1000?
		float _f184; // 0008 - Maybe x offset?
		float _f188; // 000C - Has to be y offset
		float _f18C; // 0010
		float _f190; // 0014
		float _f194; // 0018
		uint32_t _f198; // 001C
		float _f19C; // 0020
		float _f1A0; // 0024
		uint32_t _f1A4; // 0028
		uint32_t _f1A8; // 002C
		uint32_t _f1AC; // 0030
		uint32_t _f1B0; // 0034 - 1 when calling
		uint32_t _f1B4; // 0038
		uint32_t _f1B8; // 003C - Is 56 when calling a custom number and 1 when calling a number from the phonebook.
		uint32_t _f1BC; // 0040
		uint32_t _f1C0; // 0044
		uint32_t _f1C4; // 0048
		uint32_t _f1C8; // 004C
		uint32_t _f1CC; // 0050
		uint32_t _f1D0; // 0054
		uint32_t _f1D4; // 0058
		uint32_t _f1D8; // 005C
		uint32_t _f1DC; // 0060 (Hex)
		uint32_t _f1E0; // 0064
		uint32_t _f1E4; // 0068
		uint32_t _f1E8; // 006C - Ringtone? Number of ringtone id
		uint32_t _f1EC; // 0070 - Ringtype? 4 = Ring/Vibrate, 0 = Ring, 3 = Vibrate, 1 = Quiet and 2 = Silent
		uint32_t _f1F0; // 0074
		uint32_t _f1F4; // 0078
		uint32_t _f1F8; // 007C - 1 when calling

		char CurrentNumberInput[10]; // 0080

		uint32_t _f208; // 008C
		char _f20C[7]; // 0090
		uint8_t _f213; // 0097
		uint32_t _f214; // 0098
		uint32_t _f218; // 009C
		char _f21C[5]; // 00A0 - NIKO
		uint8_t _f221; // 00A5
		uint8_t _f222; // 00A6
		uint8_t _f223; // 00A7
		uint32_t _f224; // 00A8
		uint32_t _f228; // 00AC
		char _f22C[6]; // 00B0 - The name of the caller?
		uint16_t _f230; // 00B6
		uint32_t _f232; // 00B8
		uint32_t _f234; // 00BC
		uint32_t _f23C; // 00C0
		uint32_t _f240; // 00C4
		uint32_t _f244; // 00C8
		uint32_t _f248; // 00CC
		uint8_t _f24C; // 00D0
		char _f24D[7]; // 00D1
	};

	public ref class IVPhoneInfo
	{
	public:
		static property IVPhoneInfo^ ThePhoneInfo
		{
			IVPhoneInfo^ get()
			{
				uint32_t* ptr = nullptr;

				switch (CGame::m_nCurrentEpisode)
				{
					case 0: // GTA IV
						ptr = &CTheScripts::m_aGlobalVariables[91];
						break;
					case 1: // TLaD
						ptr = &CTheScripts::m_aGlobalVariables[94];
						break;
					case 2: // TBoGT
						ptr = &CTheScripts::m_aGlobalVariables[95];
						break;

					default:
						ptr = &CTheScripts::m_aGlobalVariables[91];
						break;
				}

				if (!ptr)
					return nullptr;

				return gcnew IVPhoneInfo((sPhoneInfo*)ptr);
			}
		}

	public:
		/// <summary>
		/// Current phone state like in which phone menu you currently are or if you are calling someone.
		/// 0 to 29 is the selected game mode when starting a new multiplayer match via the phone.
		/// See ePhoneState enum for possible states.
		/// </summary>
		property uint32_t State
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->State;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->State = value;
			}
		}
		/// <summary>
		/// Always 1000?
		/// </summary>
		property uint32_t _f180
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f180;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f180 = value;
			}
		}
		property float _f184
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0.0F);
				return NativePhoneInfo->_f184;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f184 = value;
			}
		}
		/// <summary>
		/// Has to be the Y offset.
		/// </summary>
		property float _f188
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0.0F);
				return NativePhoneInfo->_f188;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f188 = value;
			}
		}
		property float _f18C
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0.0F);
				return NativePhoneInfo->_f18C;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f18C = value;
			}
		}
		property float _f190
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0.0F);
				return NativePhoneInfo->_f190;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f190 = value;
			}
		}
		property float _f194
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0.0F);
				return NativePhoneInfo->_f194;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f194 = value;
			}
		}
		property uint32_t _f198
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f198;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f198 = value;
			}
		}
		property float _f19C
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0.0F);
				return NativePhoneInfo->_f19C;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f19C = value;
			}
		}
		property float _f1A0
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0.0F);
				return NativePhoneInfo->_f1A0;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1A0 = value;
			}
		}
		property uint32_t _f1A4
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1A4;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1A4 = value;
			}
		}
		property uint32_t _f1A8
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1A8;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1A8 = value;
			}
		}
		property uint32_t _f1AC
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1AC;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1AC = value;
			}
		}
		/// <summary>
		/// 1 when calling.
		/// </summary>
		property uint32_t _f1B0
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1B0;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1B0 = value;
			}
		}
		property uint32_t _f1B4
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1B4;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1B4 = value;
			}
		}
		/// <summary>
		/// 56 when calling a custom number, and 1 when calling a number from the phonebook.
		/// </summary>
		property uint32_t _f1B8
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1B8;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1B8 = value;
			}
		}
		property uint32_t _f1BC
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1BC;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1BC = value;
			}
		}
		property uint32_t _f1C0
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1C0;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1C0 = value;
			}
		}
		property uint32_t _f1C4
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1C4;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1C4 = value;
			}
		}
		property uint32_t _f1C8
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1C8;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1C8 = value;
			}
		}
		property uint32_t _f1CC
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1CC;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1CC = value;
			}
		}
		property uint32_t _f1D0
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1D0;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1D0 = value;
			}
		}
		property uint32_t _f1D4
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1D4;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1D4 = value;
			}
		}
		property uint32_t _f1D8
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1D8;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1D8 = value;
			}
		}
		property uint32_t _f1DC
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1DC;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1DC = value;
			}
		}
		property uint32_t _f1E0
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1E0;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1E0 = value;
			}
		}
		property uint32_t _f1E4
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1E4;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1E4 = value;
			}
		}
		/// <summary>
		/// Selected ringtone id.
		/// </summary>
		property uint32_t RingtoneID
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1E8;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1E8 = value;
			}
		}
		/// <summary>
		/// Selected ringtype.
		/// 4 = Ring/Vibrate, 0 = Ring, 3 = Vibrate, 1 = Quiet and 2 = Silent
		/// </summary>
		property uint32_t Ringtype
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1EC;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1EC = value;
			}
		}
		property uint32_t _f1F0
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1F0;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1F0 = value;
			}
		}
		property uint32_t _f1F4
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1F4;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1F4 = value;
			}
		}
		/// <summary>
		/// 1 when calling.
		/// </summary>
		property uint32_t _f1F8
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f1F8;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f1F8 = value;
			}
		}

		/// <summary>
		/// The currently entered phone number.
		/// </summary>
		property String^ CurrentNumberInput
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, String::Empty);
				return gcnew String(NativePhoneInfo->CurrentNumberInput);
			}
			void set(String^ value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NULLPTR_CHECK(value);

				//if (value->Length > 9)
				//	return;

				msclr::interop::marshal_context ctx;
				strcpy_s(NativePhoneInfo->CurrentNumberInput, 9, ctx.marshal_as<const char*>(value));
			}
		}

		property uint32_t _f208
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f208;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f208 = value;
			}
		}
		property String^ _f20C
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, String::Empty);
				return gcnew String(NativePhoneInfo->_f20C);
			}
			void set(String^ value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NULLPTR_CHECK(value);

				//if (value->Length > 6)
				//	return;

				msclr::interop::marshal_context ctx;
				strcpy_s(NativePhoneInfo->_f20C, 6, ctx.marshal_as<const char*>(value));
			}
		}
		property uint8_t _f213
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f213;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f213 = value;
			}
		}
		property uint32_t _f214
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f214;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f214 = value;
			}
		}
		property uint32_t _f218
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f218;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f218 = value;
			}
		}
		/// <summary>
		/// In GTA IV, this returns "NIKO", in TLaD it returns "JOHNNY" and in TBoGT it returns "LUIS".
		/// </summary>
		property String^ _f21C
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, String::Empty);
				return gcnew String(NativePhoneInfo->_f21C);
			}
			void set(String^ value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NULLPTR_CHECK(value);

				//if (value->Length > 4)
				//	return;

				// Size might be wrong
				msclr::interop::marshal_context ctx;
				strcpy_s(NativePhoneInfo->_f21C, 4, ctx.marshal_as<const char*>(value));
			}
		}
		property uint8_t _f221
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f221;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f221 = value;
			}
		}
		property uint8_t _f222
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f222;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f222 = value;
			}
		}
		property uint8_t _f223
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f223;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f223 = value;
			}
		}
		property uint32_t _f224
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f224;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f224 = value;
			}
		}
		property uint32_t _f228
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f228;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f228 = value;
			}
		}
		/// <summary>
		/// The name of the caller? A gxt entry maybe?
		/// </summary>
		property String^ _f22C
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, String::Empty);
				return gcnew String(NativePhoneInfo->_f22C);
			}
			void set(String^ value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NULLPTR_CHECK(value);

				//if (value->Length > 5)
				//	return;

				msclr::interop::marshal_context ctx;
				strcpy_s(NativePhoneInfo->_f22C, 5, ctx.marshal_as<const char*>(value));
			}
		}
		property uint16_t _f230
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f230;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f230 = value;
			}
		}
		property uint32_t _f232
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f232;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f232 = value;
			}
		}
		property uint32_t _f234
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f234;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f234 = value;
			}
		}
		property uint32_t _f23C
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f23C;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f23C = value;
			}
		}
		property uint32_t _f240
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f240;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f240 = value;
			}
		}
		property uint32_t _f244
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f244;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f244 = value;
			}
		}
		property uint32_t _f248
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f248;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f248 = value;
			}
		}
		property uint8_t _f24C
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, 0);
				return NativePhoneInfo->_f24C;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NativePhoneInfo->_f24C = value;
			}
		}
		property String^ _f24D
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, String::Empty);
				return gcnew String(NativePhoneInfo->_f24D);
			}
			void set(String^ value)
			{
				NULLPTR_CHECK(NativePhoneInfo);
				NULLPTR_CHECK(value);

				//if (value->Length > 6)
				//	return;

				msclr::interop::marshal_context ctx;
				strcpy_s(NativePhoneInfo->_f24D, 6, ctx.marshal_as<const char*>(value));
			}
		}

	internal:
		IVPhoneInfo(sPhoneInfo* nativePtr);

	internal:
		sPhoneInfo* NativePhoneInfo;
	};
}
