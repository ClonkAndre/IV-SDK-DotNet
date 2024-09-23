using System;

using static IVSDKDotNet.Native.Natives;

namespace Manager.Classes
{
    internal class Secrittzzz
    {

        #region Variables
        private static bool todayIsGTAIVBirthday;
        private static bool didDoGTAIVBirthdayStuff;
        #endregion

        public static void Init()
        {
            DateTime dtNow = DateTime.UtcNow;

            if (dtNow.Day == 4 && dtNow.Month == 7)
                Logger.Log("Happy birthday to ItsClonkAndre!");
            if (dtNow.Day == 22 && dtNow.Month == 10)
                Logger.Log(string.Format("IV-SDK .NET got {0} years old today!", dtNow.Year - 2022));
            if (dtNow.Day == 29 && dtNow.Month == 4)
            {
                Logger.Log(string.Format("GTA IV got {0} years old today! Big thanks to Rockstar North and Rockstar Toronto for this masterpiece! And happy birthday GTA IV!", dtNow.Year - 2008));
                todayIsGTAIVBirthday = true;
            }
        }

        public static void Process()
        {
            // GTA IV Birthday
            if (todayIsGTAIVBirthday)
            {
                if (!didDoGTAIVBirthdayStuff)
                {
                    TRIGGER_MISSION_COMPLETE_AUDIO(58);

                    int playerIndex = CONVERT_INT_TO_PLAYERINDEX(GET_PLAYER_ID());
                    GET_PLAYER_CHAR(playerIndex, out int playerPed);

                    if (playerPed != 0)
                        _TASK_PLAY_ANIM_FACIAL(playerPed, "plyr_mood_happy", "facials@m_hi", 1f, 1, 0, -1);

                    didDoGTAIVBirthdayStuff = true;
                }
            }
        }

    }
}
