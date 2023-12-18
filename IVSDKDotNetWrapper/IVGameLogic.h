#pragma once

namespace IVSDKDotNet
{
	public ref class IVGameLogic
	{
	public:
		static property bool PenaltyForDeathApplies
		{
		public:
			bool get()
			{
				return CGameLogic::bPenaltyForDeathApplies;
			}
			void set(bool value)
			{
				CGameLogic::bPenaltyForDeathApplies = value;
			}
		}
		static property bool PenaltyForArrestApplies
		{
		public:
			bool get()
			{
				return CGameLogic::bPenaltyForArrestApplies;
			}
			void set(bool value)
			{
				CGameLogic::bPenaltyForArrestApplies = value;
			}
		}

	public:
		static bool Save();
		static bool Load();
		static void RestorePlayerStuffDuringResurrection(IVPed^ pPlayerPed, Vector3 newCoors, float newHeading);
	};
}