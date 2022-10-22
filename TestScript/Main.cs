using System;
using System.Numerics;
using System.Windows.Forms;

using IVSDKDotNet;
using IVSDKDotNet.Enums;
using static IVSDKDotNet.Native.Natives;

namespace TestScript {
    public class Main : Script {

        #region Constructor
        public Main()
        {
            // Register a custom console command for this script
            CGame.Console.RegisterCommand("Test", (string[] args) => { CGame.Console.PrintWarning("Custom command 'Test' called!"); });

            Tick += Main_Tick;
            KeyDown += Main_KeyDown;
        }
        #endregion

        // Runs every frame when in-game
        private void Main_Tick(object sender, EventArgs e)
        {
            // - - - - Some tests - - - -

            //int index = (int)GET_PLAYER_RADIO_STATION_INDEX();
            //CRadioStation rs = CRadioStation.GetRadioStation(index);

            //if (rs != null) {
            //    ShowSubtitleMessage(string.Format("Name of radio station {0} is: {1}, Frozen: {2}", index.ToString(), rs.Name, rs.IsFrozen.ToString()), 1000);
            //}

            //audRadioAudioEntity r = audRadioAudioEntity.RadioAudioEntity;
            //if (r != null) {
            //    ShowSubtitleMessage(r.CurrentRadioStation.ToString(), 1000);
            //}
        }

        private void Main_KeyDown(object sender, KeyEventArgs e)
        {
            // Creates an explosion infront of the player
            if (e.KeyCode == Keys.NumPad9) {

                // Get player index and get player
                int playerID = CONVERT_INT_TO_PLAYERINDEX(GET_PLAYER_ID());
                GET_PLAYER_CHAR(playerID, out int playerPed);

                // Get player coordinates
                GET_CHAR_COORDINATES(playerPed, out float x, out float y, out float z);

                // Get player heading
                GET_CHAR_HEADING(playerPed, out float heading);

                // Get position infront of player
                Vector3 v = GetPositionInFrontOfPed(new Vector3(x, y, z), HeadingToDirection(heading));

                // Create explosion
                ADD_EXPLOSION(v.X, v.Y, v.Z, (int)eExplosionType.EXPLOSION_TYPE_ROCKET, 10f, true, false, 0.5f);

            }
        }

        // These will later be implemented in IV-SDK .NET so you don't have to add them manually
        public Vector3 GetPositionInFrontOfPed(Vector3 pedPos, Vector3 pedDir, float onFootMultiplier = 12f)
        {
            return Vector3.Add(pedPos, Vector3.Multiply(pedDir, onFootMultiplier));
        }
        public Vector3 HeadingToDirection(float heading)
        {
            float h = heading * (float)(Math.PI / 180);
            return new Vector3((float)-Math.Sin(h), (float)Math.Cos(h), 0f);
        }

    }
}
