#include "pch.h"
#include "IVAchievements.h"

namespace IVSDKDotNet
{
	void IVAchievements::AwardAchievement(int32_t id)
	{
		CAchievements::AwardAchievement(id);
	}
	bool IVAchievements::IsAchievementUnlocked(int32_t id)
	{
		return CAchievements::IsAchievementUnlocked(id);
	}
}