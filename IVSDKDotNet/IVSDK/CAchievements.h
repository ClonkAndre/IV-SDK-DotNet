class CAchievements
{
public:

	static void AwardAchievement(int id)
	{
		return ((void(__cdecl*)(int))(AddressSetter::Get("CAchievements", "AwardAchievement")))(id);
	}
	static bool IsAchievementUnlocked(int id)
	{
		return ((bool(__cdecl*)(int))(AddressSetter::Get("CAchievements", "IsAchievementUnlocked")))(id);
	}
};