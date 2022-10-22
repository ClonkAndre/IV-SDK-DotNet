#pragma once

class Native_CPedType
{
public:

	// Takes pedtype string and returns 1 if PLAYER1, PLAYER2, PLAYER_NETWORK or PLAYER_UNUSED
	// If true the game sets CPedModelInfo::m_bStreamedPed to 1
	static bool IsPedTypePlayer(char* type)
	{
		return ((bool(__cdecl*)(char*))(AddressSetter::Get(0x7CB880, 0x806D60)))(type);
	}
	// returns pedtype id from string
	static int FindPedType(char* type)
	{
		return ((int(__cdecl*)(char*))(AddressSetter::Get(0x7CB8E0, 0x806DC0)))(type);
	}
};

namespace IVSDKDotNet {

	public ref class CPedType
	{
	public:

		/// <summary> Takes pedtype string and returns 1 if PLAYER1, PLAYER2, PLAYER_NETWORK or PLAYER_UNUSED. </summary>
		/// <param name="type">Pedtype string</param>
		/// <returns>If true the game sets CPedModelInfo::m_bStreamedPed to 1.</returns>
		static bool IsPedTypePlayer(String^ type);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="type">The pedtype.</param>
		/// <returns>The pedtype id from string.</returns>
		static int  FindPedType(String^ type);

	};

}