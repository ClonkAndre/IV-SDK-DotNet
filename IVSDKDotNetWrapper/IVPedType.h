#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedType
	{
	public:

		/// <summary>
		/// Checks if the given type is a player.
		/// If true, the game sets CPedModelInfo::m_bStreamedPed to 1.
		/// </summary>
		/// <param name="type">The ped type to check.</param>
		/// <returns>True if the type is PLAYER1, PLAYER2, PLAYER_NETWORK or PLAYER_UNUSED.</returns>
		static bool IsPedTypePlayer(String^ type);

		/// <summary>
		/// Gets the pedtype id from string.
		/// </summary>
		/// <param name="type">The ped type to get the id from.</param>
		/// <returns>The id from the given type.</returns>
		static int FindPedType(String^ type);

	};
}