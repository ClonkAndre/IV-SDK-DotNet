#pragma once

//class CEntity;
class phInstGta;

struct Native_tLineOfSightResults
{
	phInstGta* m_pInst = nullptr;						// 00-04 phInstGta pointer of hit entity
	uint8_t pad[0xC];									// 04-10
	Native_CVector m_vEndPosition;						// 10-1C where it ended up
	uint32_t m_nUnkFlags;								// 1C-20 0x11
	Native_CVector m_vUnk;								// 20-2C
	uint32_t m_nUnkFlags2;								// 2C-30 0x11
	Native_CVector m_vUnk2;								// 30-3C
	uint32_t m_nUnkFlags3;								// 3C-40 0x11
	float m_fUnk1;										// 40-44
	float m_fUnk2;										// 44-48
	uint32_t m_nUnkFlags4;								// 48-4C 0x4F
	uint32_t m_nUnkFlags5;								// 4C-50 0x20000
	uint32_t m_nUnkFlags6;								// 50-54 0x10001
};
VALIDATE_SIZE(Native_tLineOfSightResults, 0x54);
VALIDATE_OFFSET(Native_tLineOfSightResults, m_pInst, 0x0);
VALIDATE_OFFSET(Native_tLineOfSightResults, m_vEndPosition, 0x10);
VALIDATE_OFFSET(Native_tLineOfSightResults, m_vUnk, 0x20);
VALIDATE_OFFSET(Native_tLineOfSightResults, m_vUnk2, 0x30);

class Native_CWorld
{
public:
	static inline Native_CPlayerInfo** Players = (Native_CPlayerInfo**)AddressSetter::Get(0xDA7008, 0xD00498); // Players[32]
	
	static int32_t	GetPlayerInFocus()				{ return AddressSetter::GetRef<int32_t>(0xB1CC68, 0xB2E0B4); }
	static void		SetPlayerInFocus(int32_t value) { AddressSetter::GetRef<int32_t>(0xB1CC68, 0xB2E0B4) = value; }

	static void Add(Native_CEntity* entity, bool bUnk)
	{
		((void(__cdecl*)(Native_CEntity*, bool))(AddressSetter::Get(0x417350, 0x3CC640)))(entity, bUnk);
	}

	static void Remove(Native_CEntity* entity, bool bUnk)
	{
		((void(__cdecl*)(Native_CEntity*, bool))(AddressSetter::Get(0x4173C0, 0x3CC6B0)))(entity, bUnk);
	}

	static void RemoveFallenPeds()
	{
		((void(__cdecl*)())(AddressSetter::Get(0x419270, 0x3CE740)))();
	}

	static void RemoveFallenCars()
	{
		((void(__cdecl*)())(AddressSetter::Get(0x4194F0, 0x3CE9C0)))();
	}

	static void RemoveFallenObjects()
	{
		((void(__cdecl*)())(AddressSetter::Get(0x419750, 0x3CEC20)))();
	}

	static void RequestModel(int model)
	{
		((void(__cdecl*)(int, int))(AddressSetter::Get(0x76C3D0, 0x7191D0)))(model, 0);
	}

	static bool ProcessLineOfSight(Native_CVector* source, Native_CVector* target, uint32_t* pUnk, Native_tLineOfSightResults* pResults, uint32_t nFlags, uint32_t nUnk1, uint32_t nUnk2, uint32_t nSeeThroughShootThrough, uint32_t nUnk4)
	{
		// zmenu uses CWorld::ProcessLineOfSight(v, v2, 0, &ret, 142, 1, 0, 2, 4)
		// see/shoot 1 -> do see through check
		// see/shoot 2 -> do shoot through check
		return ((uint32_t(__cdecl*)(Native_CVector*, Native_CVector*, uint32_t*, Native_tLineOfSightResults*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(AddressSetter::Get(0x596D80, 0x52A400)))(source, target, pUnk, pResults, nFlags, nUnk1, nUnk2, nSeeThroughShootThrough, nUnk4);
	}
};

namespace IVSDKDotNet {

	public value class tLineOfSightResults
	{
	public:
		tLineOfSightResults(Native_tLineOfSightResults native);

		property phInstGta* InstGta {
			public: phInstGta* get() { return m_pInst; }
		}

		property Vector3 EndPosition {
			public: Vector3	get() { return m_vEndPosition; }
		}

		property uint32_t UnkFlags {
			public: uint32_t	get() { return m_nUnkFlags; }
		}

		property Vector3 UnkVector {
			public: Vector3	get() { return m_vUnk; }
		}

		property uint32_t UnkFlags2 {
			public: uint32_t	get() { return m_nUnkFlags2; }
		}

		property Vector3 UnkVector2 {
			public: Vector3	get() { return m_vUnk2; }
		}

		property uint32_t UnkFlags3 {
			public: uint32_t	get() { return m_nUnkFlags3; }
		}

		property float UnkFloat1 {
			public: float	get() { return m_fUnk1; }
		}

		property float UnkFloat2 {
			public: float	get() { return m_fUnk2; }
		}

		property uint32_t UnkFlags4 {
			public: uint32_t	get() { return m_nUnkFlags4; }
		}

		property uint32_t UnkFlags5 {
			public: uint32_t	get() { return m_nUnkFlags5; }
		}

		property uint32_t UnkFlags6 {
			public: uint32_t	get() { return m_nUnkFlags6; }
		}

	private:
		phInstGta* m_pInst;
		Vector3 m_vEndPosition;
		uint32_t m_nUnkFlags;
		Vector3 m_vUnk;
		uint32_t m_nUnkFlags2;
		Vector3 m_vUnk2;
		uint32_t m_nUnkFlags3;
		float m_fUnk1;
		float m_fUnk2;
		uint32_t m_nUnkFlags4;
		uint32_t m_nUnkFlags5;
		uint32_t m_nUnkFlags6;
	};

	// TODO: CWorld class almost done. Things left to add: Players
	public ref class CWorld
	{
	public:

		static void Add(CEntity^ entity, bool bUnk);
		static void Remove(CEntity^ entity, bool bUnk);

		static void RemoveFallenPeds();
		static void RemoveFallenCars();
		static void RemoveFallenObjects();

		/// <summary>
		/// Requests the given model.
		/// </summary>
		/// <param name="model">The model that you want to request.</param>
		static void RequestModel(int model);

		/// <summary>
		/// ProcessLineOfSight function with extended parameters.
		/// ZMenu uses CWorld::ProcessLineOfSight(v, v2, 0, out tLineOfSightResults ret, 142, 1, 0, 2, 4)
		/// </summary>
		/// <param name="source">Source position of the check.</param>
		/// <param name="target">Target position of the check.</param>
		/// <param name="pUnk">Unknown.</param>
		/// <param name="pResults">Returns the line of sight results if the function succeeded.</param>
		/// <param name="nFlags">Unknown.</param>
		/// <param name="nUnk1">Unknown.</param>
		/// <param name="nUnk2">Unknown.</param>
		/// <param name="nSeeThroughShootThrough">1 -> Do see through check. 2 -> Do shoot through check.</param>
		/// <param name="nUnk4">Unknown.</param>
		/// <returns>True if the processing was successful. False if not.</returns>
		static bool ProcessLineOfSight(Vector3 source, Vector3 target, UIntPtr pUnk, [OutAttribute] tLineOfSightResults% pResults, uint32_t nFlags, uint32_t nUnk1, uint32_t nUnk2, uint32_t nSeeThroughShootThrough, uint32_t nUnk4);
		
		/// <summary>
		/// ProcessLineOfSight function with basic parameters.
		/// </summary>
		/// <param name="source">Source position of the check.</param>
		/// <param name="target">Target position of the check.</param>
		/// <param name="pResults">Returns the line of sight results if the function succeeded.</param>
		/// <param name="nSeeThroughShootThrough">1 -> Do see through check. 2 -> Do shoot through check</param>
		/// <returns>True if the processing was successful. False if not.</returns>
		static bool ProcessLineOfSight(Vector3 source, Vector3 target, [OutAttribute] tLineOfSightResults% pResults, uint32_t nSeeThroughShootThrough);

		/// <summary>
		/// Gets the next position on pavement based on the pos parameter.
		/// </summary>
		/// <param name="pos">Any position.</param>
		/// <returns>The next position on pavement.</returns>
		static Vector3 GetNextPositionOnPavement(Vector3 pos);

		/// <summary>
		/// Gets the next position on street based on the pos parameter.
		/// </summary>
		/// <param name="pos">Any position.</param>
		/// <returns>The next position on street.</returns>
		static Vector3 GetNextPositionOnStreet(Vector3 pos);

		/// <summary>
		/// Gets or sets the current player in focus.
		/// </summary>
		static property uint32_t PlayerInFocus {
			public:
				uint32_t	get()				{ return Native_CWorld::GetPlayerInFocus(); }
				void		set(uint32_t value) { Native_CWorld::SetPlayerInFocus(value); }
		}

	};

}