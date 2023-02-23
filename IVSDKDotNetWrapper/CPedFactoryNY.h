#pragma once

class Native_CPedFactory
{

};

struct Native_tSpawnData
{
	uint8_t m_nFlag1;
	uint8_t m_nFlag2;
};
VALIDATE_SIZE(Native_tSpawnData, 0x2);

class Native_CPedFactoryNY : public Native_CPedFactory
{
public:

	Native_CPed* CreatePed(Native_tSpawnData* pSpawnData, int32_t model, Native_CMatrix* mat, bool bNetwork, bool bUnk1)
	{
		return ((Native_CPed * (__thiscall*)(Native_CPedFactoryNY*, Native_tSpawnData*, int32_t, Native_CMatrix*, bool, bool))(*(void***)this)[5])(this, pSpawnData, model, mat, bNetwork, bUnk1);
	}
};

namespace IVSDKDotNet {

	public value class tSpawnData
	{
	public:
		tSpawnData(uint8_t flag1, uint8_t flag2);

		/// <summary>
		/// Gets the default tSpawnData struct with Flag1 and Flag2 being set to 0.
		/// </summary>
		/// <returns>A new tSpawnData struct initialized with the default values.</returns>
		static tSpawnData Default();

		property uint8_t Flag1 {
			public:		uint8_t	get()			{ return m_nFlag1; }
			private:	void set(uint8_t value) { m_nFlag1 = value; }
		}
		property uint8_t Flag2 {
			public:		uint8_t	get()			{ return m_nFlag2; }
			private:	void set(uint8_t value) { m_nFlag2 = value; }
		}

	private:
		uint8_t m_nFlag1;
		uint8_t m_nFlag2;
	};

	public ref class CPedFactoryNY
	{
	public:
		static CPed^ CreatePed(tSpawnData pSpawnData, int32_t model, GTAMatrix mat, bool bNetwork, bool bUnk1);
	};

}