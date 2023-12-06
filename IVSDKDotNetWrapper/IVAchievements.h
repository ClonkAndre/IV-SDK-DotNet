#pragma once

namespace IVSDKDotNet
{
	public ref class IVAchievements
	{
	public:
		/// <summary>
		/// Awards an achievement with the given id.
		/// </summary>
		/// <param name="id">The id of the achievement.</param>
		static void AwardAchievement(int32_t id);
		/// <summary>
		/// Checks if a specific award is unlocked.
		/// </summary>
		/// <param name="id">The id of the achievement.</param>
		/// <returns>True if the achievement is unlocked. Otherwise, false.</returns>
		static bool IsAchievementUnlocked(int32_t id);
	};
}