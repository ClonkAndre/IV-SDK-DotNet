﻿using System;
using System.Drawing;
using System.Globalization;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Windows.Forms;

using IVSDKDotNet;
using IVSDKDotNet.Direct3D9;
using IVSDKDotNet.Enums;
using static IVSDKDotNet.Native.Natives;

namespace TestScript {
    public class Main : Script {

        [StructLayout(LayoutKind.Sequential)]
        private struct POINT {
            public int X;
            public int Y;

            public override string ToString()
            {
                return string.Format("[X: {0}, Y: {1}]", X.ToString(), Y.ToString());
            }
        }

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool GetCursorPos(out POINT point);

        #region Variables
        private int playerPed;

        private Vector2 mousePos;
        private string text = "-";

        private D3DGraphics gfx;
        private D3DResource testTexture;
        private D3DResource testFont;
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
            // 2 ways to register a custom console command for this script
            RegisterConsoleCommand("Test1",                 (string[] args) => { CGame.Console.PrintWarning("Custom command 'Test1' called!"); });
            CGame.Console.RegisterCommand(this, "Test2",    (string[] args) => { CGame.Console.PrintWarning("Custom command 'Test2' called!"); });

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

            // Init graphics object
            gfx = new D3DGraphics(this);
            gfx.OnInit += Gfx_OnInit;
            gfx.OnDeviceEndScene += Gfx_OnDeviceEndScene;
        }

        // DirectX stuff
        private void Gfx_OnInit(IntPtr device)
        {
            // Try to create texture
            D3DResult r = gfx.CreateD3D9Texture(device, Properties.Resources.discordTestLogo);
            if (r.Error != null) {
                CGame.Console.PrintError("(TestScript) Error while creating texture: " + r.Error.ToString());
            }
            else {
                testTexture = (D3DResource)r.DXObject;
                CGame.Console.Print(string.Format("(TestScript) Created texture with ID: {0} Handle: {1} Properties: {2}", r.ID.ToString(), testTexture.Handle.ToString(), testTexture.ResourceProperties));
            }

            // Try to create font
            r = gfx.CreateD3D9Font(device, D3DFontDescription.Default());
            if (r.Error != null) {
                CGame.Console.PrintError("(TestScript) Error while creating font: " + r.Error.ToString());
            }
            else {
                testFont = (D3DResource)r.DXObject;
                CGame.Console.Print(string.Format("(TestScript) Created font with ID: {0} Handle: {1}", r.ID.ToString(), testFont.Handle.ToString()));
            }
        }
        private void Gfx_OnDeviceEndScene(IntPtr device)
        {
            gfx.DrawLine(device, new Vector2(10f, 10f), new Vector2(50f, 100f), Color.Red, 5f);
            gfx.DrawTexture(device, testTexture, mousePos, Size.Empty, new Vector2(0.2f, 0.2f), Color.White);
            gfx.DrawString(device, testFont, text, 50, 50, Color.Red);

            gfx.DrawBox(device, new Vector2(128f, 128f), new SizeF(64f, 64f), 4f, Color.Red);
            gfx.DrawBoxBordered(device, new Vector2(300f, 128f), new SizeF(64f, 64f), 4f, Color.FromArgb(100, Color.Blue), Color.Red);
            gfx.DrawBoxFilled(device, new Vector2(400f, 128f), new SizeF(64f, 64f), Color.Red);
            gfx.DrawBoxRounded(device, new Vector2(500f, 200f), new SizeF(64f, 64f), 5f, false, Color.FromArgb(100, Color.Blue), Color.Red);
            gfx.DrawBoxRounded(device, new Vector2(600f, 200f), new SizeF(64f, 64f), 5f, true, Color.FromArgb(100, Color.Blue), Color.Red);
            gfx.DrawCircle(device, new Vector2(700f, 200f), 16f, 0f, eD3DCircleType.Full, true, 32, Color.Red);
            gfx.DrawCircle(device, new Vector2(500f, 400f), 16f, 0f, eD3DCircleType.Half, true, 32, Color.Red);
            gfx.DrawCircle(device, new Vector2(200f, 400f), 16f, 0f, eD3DCircleType.Quarter, true, 32, Color.Red);
            gfx.DrawCircleFilled(device, new Vector2(600f, 500f), 16f, 0f, eD3DCircleType.Quarter, true, 32, Color.Red);

            Vector2[] vertices = new Vector2[4] {
                new Vector2(0f, 0f),
                new Vector2(200f, 300f),
                new Vector2(700f, 700f),
                new Vector2(500f, 1000f)
            };
            gfx.DrawLines(device, vertices, Color.Green, false, 5f);
        }

        // Runs every frame when in-game
        private void Main_Tick(object sender, EventArgs e)
        {
            bool leftMouseButton = IsKeyPressed(Keys.LButton);
            bool rightMouseButton = IsKeyPressed(Keys.RButton);

            if (GetCursorPos(out POINT p)) {
                mousePos = new Vector2(p.X, p.Y);
            }

            GET_MOUSE_WHEEL(out int wheel);
            text = string.Format("leftMouseButton: {0}, rightMouseButton: {1}, Wheel: {2}, Pos: {3}", leftMouseButton.ToString(), rightMouseButton.ToString(), wheel.ToString(), p.ToString());

            // Get player index, get player char and get char coordinates
            int playerID = CONVERT_INT_TO_PLAYERINDEX(GET_PLAYER_ID());
            GET_PLAYER_CHAR(playerID, out playerPed);
            GET_CHAR_COORDINATES(playerPed, out Vector3 playerPos);

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

            // Place light that casts shadows far above the player
            if (IsKeyPressed(Keys.I)) {
                Vector3 lightPos = new Vector3(playerPos.X, playerPos.Y, playerPos.Z + 500f);
                DRAW_CORONA(lightPos, 1900f, 1, 0f, Color.White); // Just a visualizer how far the light is actually up (It's very far up)
                CShadows.StoreStaticShadow(true, lightPos, Color.White, 2f, 800f);
            }

            // Gets the nearest street node position from the players position
            if (IsKeyPressed(Keys.U)) {
                Vector3 v = CWorld.GetNextPositionOnStreet(playerPos);
                DRAW_CHECKPOINT(v, 4f, Color.Green);
            }

            //if (IsKeyPressed(Keys.K)) {
            //    CVehicle[] vehicles = CPools.GetAllVehicles();
            //    for (int i = 0; i < vehicles.Length; i++) {
            //        CVehicle vehicle = vehicles[i];
            //        if (vehicle != null) {
            //            vehicle.PrimaryColor = (byte)rnd.Next(0, 255);
            //            vehicle.SecondaryColor = (byte)rnd.Next(0, 255);
            //        }
            //    }
            //}

            // Teleports all objects currently in the world to the players position. The physics matrix of the objects will stay untouched.
            //if (IsKeyPressed(Keys.O)) {
            //    CObject[] objs = CPools.GetAllObjects();
            //    for (int i = 0; i < objs.Length; i++) {
            //        CObject obj = objs[i];
            //        if (obj != null) {
            //            obj.Teleport(pos, true, true);
            //        }
            //    }
            //}
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

            // Ped handle pool test
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

            // Vehicle handle pool test
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

            // Object handle pool test
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
