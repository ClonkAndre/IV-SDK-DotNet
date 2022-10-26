using System;
using System.Drawing;
using System.Globalization;
using System.Numerics;
using System.Windows.Forms;

using IVSDKDotNet;
using IVSDKDotNet.Enums;
using static IVSDKDotNet.Native.Natives;

namespace TestScript {
    public class Main : Script {

        #region Variables
        private int playerPed;
        #endregion

        #region Constructor
        public Main()
        {
            // Subscribe to script events
            Initialized += Main_Initialized;
            Tick += Main_Tick;
            KeyDown += Main_KeyDown;
        }
        #endregion

        private void Main_Initialized(object sender, EventArgs e)
        {
            // Register a custom console command for this script
            CGame.Console.RegisterCommand(this, "Test", (string[] args) => { CGame.Console.PrintWarning("Custom command 'Test' called!"); });
            
            // Read TestScripts settings file (TestScript.ini)
            if (Settings != null) {
                CGame.Console.PrintWarning("bool: "    + Settings.GetBoolean("Section1", "bool", false).ToString());
                CGame.Console.PrintWarning("int: "     + Settings.GetInteger("Section1", "int", -1).ToString());
                CGame.Console.PrintWarning("float: "   + Settings.GetFloat("Section1", "float", -1.0f).ToString(CultureInfo.InvariantCulture));
                CGame.Console.PrintWarning("quat: "    + Settings.GetQuaternion("Section1", "quat", Quaternion.Identity).ToString());
                CGame.Console.PrintWarning("vec2: "    + Settings.GetVector2("Section1", "vec2", Vector2.Zero).ToString());
                CGame.Console.PrintWarning("vec3: "    + Settings.GetVector3("Section1", "vec3", Vector3.Zero).ToString());
                CGame.Console.PrintWarning("vec4: "    + Settings.GetVector4("Section1", "vec4", Vector4.Zero).ToString());
                CGame.Console.PrintWarning("color: "   + Settings.GetColor("Section1", "color", Color.FromArgb(0, 0, 0, 0)).ToString());
                CGame.Console.PrintWarning("key: "     + Settings.GetKey("Section1", "key", Keys.None).ToString());

                // Add a new section to the ini
                if (Settings.AddSection("TEST_SECTION")) { // Section got added

                    Settings.AddKeyToSection("TEST_SECTION", "New_Key"); // Add key to added section
                    Settings.Save(); // Save changes

                }
            }
        }

        // Runs every frame when in-game
        private void Main_Tick(object sender, EventArgs e)
        {
            // Get player index and get player char
            int playerID = CONVERT_INT_TO_PLAYERINDEX(GET_PLAYER_ID());
            GET_PLAYER_CHAR(playerID, out playerPed);

            // - - - - - - - Some tests - - - - - - -

            //int index = (int)GET_PLAYER_RADIO_STATION_INDEX();
            //CRadioStation rs = CRadioStation.GetRadioStation(index);

            //if (rs != null) {
            //    ShowSubtitleMessage(string.Format("Name of radio station {0} is: {1}, Frozen: {2}", index.ToString(), rs.Name, rs.IsFrozen.ToString()), 1000);
            //}

            //audRadioAudioEntity r = audRadioAudioEntity.RadioAudioEntity;
            //if (r != null) {
            //    ShowSubtitleMessage(r.CurrentRadioStation.ToString(), 1000);
            //}

            //ShowSubtitleMessage(string.Format("Minute: {0}", MemoryAccess.GetRef<uint>(0xDD52FC, 0xD51690).ToString()));
        }

        private void Main_KeyDown(object sender, KeyEventArgs e)
        {

            // Creates an explosion infront of the player
            if (e.KeyCode == Keys.NumPad9) {

                // Get player coordinates
                GET_CHAR_COORDINATES(playerPed, out Vector3 pos);

                // Get player heading
                GET_CHAR_HEADING(playerPed, out float heading);

                // Get position infront of player
                Vector3 v = Helper.GetPositionInFrontOfEntity(pos, Helper.HeadingToDirection(heading), 12f);

                // Create explosion
                ADD_EXPLOSION(v.X, v.Y, v.Z, (int)eExplosionType.EXPLOSION_TYPE_ROCKET, 10f, true, false, 0.5f);

            }

            // Ped pool test
            if (e.KeyCode == Keys.NumPad7) {

                // Explodes every ped except the player
                int[] peds = CPools.GetAllPedHandles();
                for (int i = 0; i < peds.Length; i++) {
                    int ped = peds[i];
                    if (ped != 0 && ped != playerPed) {
                        if (!IS_CHAR_DEAD(ped)) {

                            // Get ped coordinates
                            GET_CHAR_COORDINATES(ped, out Vector3 pos);

                            // Create explosion
                            ADD_EXPLOSION(pos.X, pos.Y, pos.Z, (int)eExplosionType.EXPLOSION_TYPE_ROCKET, 10f, true, false, 0.5f);

                        }
                    }
                }

            }

            // Vehicle pool test
            if (e.KeyCode == Keys.NumPad3) {

                // Explodes every vehicle
                int[] vehicles = CPools.GetAllVehicleHandles();
                for (int i = 0; i < vehicles.Length; i++) {
                    int veh = vehicles[i];
                    if (veh != 0) {
                        if (!IS_CAR_DEAD(veh)) {

                            // Get vehicle coordinates
                            GET_CAR_COORDINATES(veh, out Vector3 pos);

                            // Create explosion
                            ADD_EXPLOSION(pos.X, pos.Y, pos.Z, (int)eExplosionType.EXPLOSION_TYPE_ROCKET, 10f, true, false, 0.5f);

                        }
                    }
                }

            }

            // Object pool test
            if (e.KeyCode == Keys.NumPad1) {

                // Create explosion at object position
                int[] objects = CPools.GetAllObjectHandles();
                for (int i = 0; i < objects.Length; i++) {
                    int obj = objects[i];
                    if (obj != 0) {

                        // Get object coordinates
                        GET_OBJECT_COORDINATES(obj, out Vector3 pos);

                        // Create explosion
                        ADD_EXPLOSION(pos.X, pos.Y, pos.Z, (int)eExplosionType.EXPLOSION_TYPE_ROCKET, 10f, true, false, 0.5f);

                    }
                }

            }

        }

    }
}
