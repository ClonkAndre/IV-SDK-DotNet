#pragma once

class Native_CRadioStation
{
public:
	uint8_t pad[0x17FC];								// 0000-17FC
	char m_sName[32];									// 17FC-181C
	uint8_t pad2[0x10B];								// 181C-1927
	uint8_t m_bFrozen;									// 1927-1928
	uint8_t pad3[0xC];									// 1928-1934

	static Native_CRadioStation* GetRadioStation(int id)				{ return ((Native_CRadioStation* (__cdecl*)(int))(AddressSetter::Get(0x6C4CC0, 0x3D6E30)))(id);			}
	static Native_CRadioStation* GetRadioStationByName(char* name)		{ return ((Native_CRadioStation* (__cdecl*)(char*))(AddressSetter::Get(0x6C5F00, 0x3D8070)))(name);		}
	static Native_CRadioStation* GetRadioStationByHash(uint32_t hash)	{ return ((Native_CRadioStation* (__cdecl*)(uint32_t))(AddressSetter::Get(0x6C4C60, 0x3D6DD0)))(hash);	}
	void ForceTrack(char* trackName, int nUnk1, int nUnk2)
	{
		((void(__thiscall*)(char*, int, int))(AddressSetter::Get(0x6C4700, 0x3D6820)))(trackName, nUnk1, nUnk2);
	}
};
VALIDATE_SIZE(Native_CRadioStation, 0x1934);
VALIDATE_OFFSET(Native_CRadioStation, m_sName, 0x17FC);
VALIDATE_OFFSET(Native_CRadioStation, m_bFrozen, 0x1927);

class Native_audRadioAudioEntity
{
public:

	uint8_t pad[0x78];								// 00-78
	uint32_t m_nCurrentRadioStation;				// 78-7C

	static Native_audRadioAudioEntity GetRadioAudioEntity() { return AddressSetter::GetRef<Native_audRadioAudioEntity>(0xDA3700, 0xD71F48); }
};
VALIDATE_OFFSET(Native_audRadioAudioEntity, m_nCurrentRadioStation, 0x78);

namespace IVSDKDotNet {

	public ref class CRadioStation
	{
	public:
		
		static CRadioStation^ GetRadioStation(int id)
		{
			Native_CRadioStation* r = Native_CRadioStation::GetRadioStation(id);
			
			if (r)
				return gcnew CRadioStation(r);

			return nullptr;
		}
		static CRadioStation^ GetRadioStationByName(String^ name)
		{
			msclr::interop::marshal_context ctx;
			Native_CRadioStation* r = Native_CRadioStation::GetRadioStationByName((char*)ctx.marshal_as<const char*>(name));

			if (r)
				return gcnew CRadioStation(r);

			return nullptr;
		}
		static CRadioStation^ GetRadioStationByHash(uint32_t hash)
		{
			Native_CRadioStation* r = Native_CRadioStation::GetRadioStationByHash(hash);

			if (r)
				return gcnew CRadioStation(r);

			return nullptr;
		}

		void ForceTrack(String^ trackName, int nUnk1, int nUnk2)
		{
			msclr::interop::marshal_context ctx;
			m_cUnmanagedRadioStation->ForceTrack((char*)ctx.marshal_as<const char*>(trackName), nUnk1, nUnk2);
		}

		/// <summary>
		/// Gets the name of the radio station.
		/// </summary>
		property String^ Name {
			public:		String^ get()			{ return m_sName; }
			private:	void set(String^ value) { m_sName = value; }
		}

		/// <summary>
		/// Gets if the radio station is frozen.
		/// </summary>
		property bool IsFrozen {
			public:		bool get()				{ return m_bFrozen; }
			private:	void set(bool value)	{ m_bFrozen = value; }
		}

	private:
		CRadioStation(Native_CRadioStation* unmanagedRadioStation);

		Native_CRadioStation* m_cUnmanagedRadioStation;
		String^ m_sName;
		bool m_bFrozen;
	};

	public ref class audRadioAudioEntity
	{
	public:

		static property audRadioAudioEntity^ RadioAudioEntity {
			public:
				audRadioAudioEntity^ get() { return gcnew audRadioAudioEntity(Native_audRadioAudioEntity::GetRadioAudioEntity()); }
		}

		/// <summary>
		/// Gets the current radio station index.
		/// </summary>
		property uint32_t CurrentRadioStation {
			public:		uint32_t get()				{ return m_nCurrentRadioStation; }
			internal:	void set(uint32_t value)	{ m_nCurrentRadioStation = value; }
		}

	private:
		audRadioAudioEntity(Native_audRadioAudioEntity unmanagedRadioAudioEntity);

		uint32_t m_nCurrentRadioStation;
	};

}