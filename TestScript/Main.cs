using System;
using System.Drawing;
using System.Drawing.Drawing2D;
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
        public struct TestNetworkStruct
        {
            public int v;

            public TestNetworkStruct(int value)
            {
                v = value;
            }

            public override string ToString()
            {
                return "Value: " + v.ToString();
            }
        }

        #region Variables
        private int playerPed;
        private Vector3 playerPos;
        private float heading;

        private string text = "Hello world!";

        private float fov = 60f;
        private float rot;

        private int pickup;

        private D3DGraphics gfx;
        private D3DResource testTexture;
        private D3DResource arrowTexture;
        private D3DResource speedBgTexture;
        private D3DResource needleTexture;
        private D3DResource testFont;
        #endregion

        #region Constructor
        public Main()
        {
            OnlyRaiseKeyEventsWhenInGame = true;

            // Subscribe to script events
            Initialized += Main_Initialized;
            Tick += Main_Tick;
            KeyDown += Main_KeyDown;
            ProcessAutomobile += Main_ProcessAutomobile;
            ProcessCamera += Main_ProcessCamera;
            ScriptCommandReceived += Main_ScriptCommandReceived;

            CGame.OnWindowFocusChanged += CGame_OnWindowFocusChanged;
        }
        #endregion

        public Vector2 CoordToScreen(Vector3 pos)
        {
            GET_GAME_VIEWPORT_ID(out int viewportID);
            GET_VIEWPORT_POSITION_OF_COORD(pos, viewportID, out Vector2 screenPos);
            return screenPos;
        }
        public Vector2 SmoothVector(Vector2 v)
        {
            return new Vector2((float)Math.Round(v.X, 0), (float)Math.Round(v.Y, 0));
        }

        private void CGame_OnWindowFocusChanged(bool focused)
        {
            if (focused)
            {
                CGame.Console.PrintWarning("IN FOCUS");
            }
            else
            {
                CGame.Console.PrintError("NOT IN FOCUS");
            }
        }
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

        int intNum;

        // DirectX stuff
        private void Gfx_OnInit(IntPtr device)
        {
            // Try to create texture
            D3DResult r = gfx.CreateD3D9Texture(Properties.Resources.discordTestLogo);
            if (r.Error != null) {
                CGame.Console.PrintError("(TestScript) Error while creating texture: " + r.Error.ToString());
            }
            else {
                testTexture = (D3DResource)r.DXObject;
                CGame.Console.Print(string.Format("(TestScript) Created texture with ID: {0} Handle: {1} Properties: {2}", r.ID.ToString(), testTexture.Handle.ToString(), testTexture.ResourceProperties));
            }

            // Try to create texture
            //r = gfx.CreateD3D9Texture(device, Properties.Resources.arrowUp);
            //if (r.Error != null)
            //{
            //    CGame.Console.PrintError("(TestScript) Error while creating font: " + r.Error.ToString());
            //}
            //else
            //{
            //    arrowTexture = (D3DResource)r.DXObject;
            //    CGame.Console.Print(string.Format("(TestScript) Created font with ID: {0} Handle: {1}", r.ID.ToString(), testFont.Handle.ToString()));
            //}

            // Try to create textures
            speedBgTexture = (D3DResource)gfx.CreateD3D9Texture(Properties.Resources.Bck).DXObject;
            needleTexture = (D3DResource)gfx.CreateD3D9Texture(Properties.Resources.Pin).DXObject;

            // Try to create font
            r = gfx.CreateD3D9Font(D3DFontDescription.Default());
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
            //gfx.DrawTexture(arrowTexture, new RectangleF(CGame.Resolution.Width / 2f, 64f, 32f, 32f), rot);

            string text2 = "TEST!!!!lol";
            Size s = gfx.MeasureText(testFont, text2, eD3DFontDrawFlags.Left).Size;
            gfx.DrawBoxFilled(new Vector2(100f, 100f), new SizeF(s.Width - 10, s.Height), Color.Blue);
            gfx.DrawString(text2, new Rectangle(100, 100, s.Width - 10, s.Height), eD3DFontDrawFlags.Left, Color.Red);

            gfx.DrawString(s.ToString(), new Point(100, 200), Color.Red);
            gfx.DrawString(text, new Point(100, 400), Color.Red);

            return;

            gfx.DrawLine(new Vector2(10f, 10f), new Vector2(50f, 100f), Color.Red, 5f);
            gfx.DrawLine(new Vector2(0f, 232f), new Vector2(300f, 232f), Color.Blue, 1f);
            gfx.DrawString(testFont, text, 100, 60, Color.Red);

            gfx.DrawBox(new Vector2(128f, 128f), new SizeF(64f, 64f), 4f, Color.Red);
            gfx.DrawBoxBordered(new Vector2(300f, 128f), new SizeF(64f, 64f), 4f, Color.FromArgb(100, Color.Blue), Color.Red);
            gfx.DrawBoxFilled(new Vector2(400f, 128f), new SizeF(64f, 64f), Color.Red);
            gfx.DrawBoxRounded(new Vector2(500f, 200f), new SizeF(64f, 64f), 5f, false, Color.FromArgb(100, Color.Blue), Color.Red);
            gfx.DrawBoxRounded(new Vector2(600f, 200f), new SizeF(64f, 64f), 5f, true, Color.FromArgb(100, Color.Blue), Color.Red);
            gfx.DrawCircle(new Vector2(700f, 200f), 16f, 0f, eD3DCircleType.Full, true, 32, Color.Red);
            gfx.DrawCircle(new Vector2(500f, 400f), 16f, 0f, eD3DCircleType.Half, true, 32, Color.Red);
            gfx.DrawCircle(new Vector2(200f, 400f), 16f, 0f, eD3DCircleType.Quarter, true, 32, Color.Red);
            gfx.DrawCircleFilled(new Vector2(600f, 500f), 16f, 0f, eD3DCircleType.Quarter, true, 32, Color.Red);

            // Draw radar rectangle
            RectangleF radar = CGame.GetRadarRectangle();
            gfx.DrawBoxRounded(new Vector2(radar.X, radar.Y), new SizeF(radar.Width, radar.Height), 15f, false, Color.FromArgb(100, Color.Yellow), Color.Red);

            Vector2[] vertices = new Vector2[4] {
                new Vector2(0f, 0f),
                new Vector2(200f, 300f),
                new Vector2(700f, 700f),
                new Vector2(500f, 1000f)
            };
            gfx.DrawLines(vertices, Color.Green, false, 5f);
        }

        // Runs every frame when in-game
        private void Main_Tick(object sender, EventArgs e)
        {
            // The IV-SDK .NET method on how to get the player char and the char coordinates and heading
            CPed playerPedNEW = CPed.FromPointer(CPlayerInfo.FindPlayerPed());
            Vector3 playerPosNEW = playerPedNEW.Matrix.pos;
            heading = playerPedNEW.CurrentHeading;

            CVehicle veh = playerPedNEW.GetVehicle();
            if (veh != null)
            {
                int vehicleHandle = (int)CPools.GetVehiclePool().GetIndex(veh.GetUIntPtr());

                //tHandlingData handlingData2 = tHandlingData.FromPointer(veh.Handling);
                //ShowSubtitleMessage(handlingData2.Name);

                //ShowSubtitleMessage(string.Format("Engine Starting: {0}, Engine On: {1}", veh.TheVehicleFlags.EngineStarting.ToString(), veh.TheVehicleFlags.EngineOn.ToString()));
            }

            // The native method way on how to get the player index, the player char and the char coordinates and heading
            int playerID = CONVERT_INT_TO_PLAYERINDEX(GET_PLAYER_ID());
            GET_PLAYER_CHAR(playerID, out playerPed);
            GET_CHAR_COORDINATES(playerPed, out playerPos);
            GET_CHAR_HEADING(playerPed, out heading);

            // CHandlingDataMgr test
            tHandlingData handlingData = CHandlingDataMgr.GetHandlingData(CHandlingDataMgr.GetHandlingId("BANSHEE")); // Get handling of the BANSHEE
            //ShowSubtitleMessage(string.Format("Name: {0}, HalogenLights: {1}", handlingData.Name, handlingData.TheHandlingFlags.HalogenLights.ToString()));

            // CPlayerInfo test
            CPlayerInfo playerInfo = CPlayerInfo.GetPlayerInfo(GET_PLAYER_ID());
            //ShowSubtitleMessage(string.Format("PID: {0}, Name: {1}, LastRanLightTime: {2}, PlayerPed: {3}, PlayerPed2: {4}", playerInfo.PlayerId.ToString(), playerInfo.Name, playerInfo.LastRanLightTime.ToString(), playerInfo.PlayerPed != UIntPtr.Zero, playerInfo.PlayerPed2 != UIntPtr.Zero));

            // CWeaponInfo test
            CWeaponInfo weaponInfo = CWeaponInfo.GetWeaponInfo((uint)eWeaponType.WEAPON_MP5);
            //ShowSubtitleMessage(string.Format("WeaponType: {0}, Silenced: {1}", (eWeaponType)weaponInfo.WeaponType, weaponInfo.TheWeaponFlags.Silenced.ToString()));

            // CDraw test
            CDraw draw = CDraw.Get();
            if (draw != null)
            {
                //draw.ForceHudWidescreen = 0;
                //ShowSubtitleMessage(string.Format("AspectRatio: {0}, ForceHudWidescreen: {1}", draw.CalculateAspectRatio(true).ToString(), draw.ForceHudWidescreen.ToString()));

                tGlobalScene globalScene = draw.GlobalScene;
                if (globalScene != null)
                {
                    CViewportGame viewportGame = globalScene.ViewportGame;
                    if (viewportGame != null)
                    {
                        tViewportData viewportData = viewportGame.Data;
                        if (viewportData != null)
                        {
                            RectangleF rect = viewportData.Rect;
                            //ShowSubtitleMessage(string.Format("Rect: {0}, Resolution: {1}, Scale: {2}", rect.ToString(), viewportData.Resolution.ToString(), viewportData.Scale.ToString()));
                        }
                    }
                }
            }

            // CPad test
            CPad pad = CPad.GetPad();
            if (pad != null)
            {
                //ShowSubtitleMessage(string.Format("IsUsingKeyboardForAim: {0}, IsUsingKeyboardForHeli: {1}, LastUpdateTime: {2}", pad.IsUsingKeyboardForAim.ToString(), pad.IsUsingKeyboardForHeli.ToString(), pad.LastUpdateTime.ToString()));
            }





            //PedWeaponSlot slot4 = playerPedNEW.m_pWeaponData.Weapons[2];
            //ShowSubtitleMessage(string.Format("Type: {0}, Ammo: {1}, Model loaded: {2}", ((eWeaponType)slot4.Type).ToString(), slot4.Ammo.ToString(), slot4.HasModelLoaded.ToString()));

            //CCam finalCam = CCamera.GetFinalCam();
            //uint finalCamHandle = CPools.GetCameraPool().GetIndex(finalCam.GetUIntPtr());

            //GET_CAM_ROT((int)finalCamHandle, out Vector3 finalCamRot);

            //float direction_to_that_coord = Vector3.Subtract(Vector3.Normalize(Vector3.Subtract(new Vector3(circleOrigin.X, circleOrigin.Y, 11f), finalCam.Matrix.pos)), Helper.RotationToDirection(finalCamRot)).Length();
            //if (direction_to_that_coord > 0.6f)
            //{
            //    rot = direction_to_that_coord * 2f;
            //}
            //else
            //{
            //    rot = -direction_to_that_coord * 2f;
            //}
            //ShowSubtitleMessage(rot.ToString());


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
            //if (IsKeyPressed(Keys.I)) {
            //    Vector3 lightPos = new Vector3(playerPos.X, playerPos.Y, playerPos.Z + 500f);
            //    DRAW_CORONA(lightPos, 1900f, 1, 0f, Color.White); // Just a visualizer how far the light is actually up (It's very far up)
            //    CShadows.StoreStaticShadow(true, lightPos, Color.White, 2f, 800f);
            //}

            // Gets the nearest street node position from the players position
            //if (IsKeyPressed(Keys.U)) {
            //    Vector3 v = CWorld.GetNextPositionOnStreet(playerPos);
            //    DRAW_CHECKPOINT(v, 4f, Color.Green);
            //}

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

            // Teleports all buildings currently in the world to the players position. The physics matrix of the buildings will stay untouched.
            //if (IsKeyPressed(Keys.O)) {
            //    CBuilding[] buildings = CPools.GetAllBuildings();
            //    for (int i = 0; i < buildings.Length; i++) {
            //        CBuilding b = buildings[i];
            //        if (b != null) {
            //            b.Teleport(playerPos, true, true);
            //        }
            //    }
            //}

            ////// CWorld.ProcessLineOfSight Test
            //Vector3 targetLineOfSightPos = Helper.GetPositionInFrontOfEntity(playerPos, Helper.HeadingToDirection(heading), 5f);

            //bool result = CWorld.ProcessLineOfSight(playerPos, targetLineOfSightPos, out tLineOfSightResults r, 2);
            //if (!result) {
            //    DRAW_CHECKPOINT(targetLineOfSightPos, 1f, Color.Red); // Visualize targetLineOfSightPos pos
            //    text = "Processing line of sight failed";
            //}
            //else {
            //    DRAW_CHECKPOINT(targetLineOfSightPos, 1f, Color.Green); // Visualize targetLineOfSightPos pos
            //    text = string.Format("EndPosition: {1}{0}" +
            //                         "UnkFlags: {2}, UnkFlags2: {3}, UnkFlags3: {4}, UnkFlags4: {5}, UnkFlags5: {6}{0}" +
            //                         "UnkFloat1: {7}, UnkFloat2: {8}",
            //                         Environment.NewLine,
            //                         r.EndPosition.ToString(),
            //                         r.UnkFlags.ToString(), r.UnkFlags2.ToString(), r.UnkFlags3.ToString(), r.UnkFlags4.ToString(), r.UnkFlags5.ToString(),
            //                         r.UnkFloat1.ToString(), r.UnkFloat2.ToString());
            //}
        }

        private void Main_ProcessAutomobile(UIntPtr vehPtr)
        {
            CVehicle veh = CVehicle.FromPointer(vehPtr);
            if (veh != null)
            {
                //veh.Alpha = 180; // Sets the alpha property of each vehicle in the world to 180.

                UIntPtr[] pass = veh.Passengers;
                if (pass[0] != UIntPtr.Zero) // Front Left
                {
                    CPed passFL = CPed.FromPointer(pass[0]);
                    Vector3 pos = passFL.Matrix.pos;
                    DRAW_CHECKPOINT(pos, 1f, Color.Red);
                }
                if (pass[1] != UIntPtr.Zero) // Back Right
                {
                    CPed passBR = CPed.FromPointer(pass[1]);
                    Vector3 pos = passBR.Matrix.pos;
                    DRAW_CHECKPOINT(pos, 1f, Color.Green);
                }
                if (pass[2] != UIntPtr.Zero) // Back Left
                {
                    CPed passBL = CPed.FromPointer(pass[2]);
                    Vector3 pos = passBL.Matrix.pos;
                    DRAW_CHECKPOINT(pos, 1f, Color.Blue);
                }
            }
        }
        private void Main_ProcessCamera(object sender, EventArgs e)
        {
            //if (IsKeyPressed(Keys.Add))
            //    fov += 0.5f; // Zooms out
            //if (IsKeyPressed(Keys.Subtract))
            //    fov -= 0.5f; // Zooms in

            //CCam c = CCamera.GetFinalCam();
            //if (c != null)
            //{
            //    c.FOV = fov;
            //}
        }

        // When this script receives a script command
        private void Main_ScriptCommandReceived(Script fromScript, string command)
        {
            CGame.Console.PrintWarning(string.Format("Received a script command from script {0}. Command: {1}", fromScript.GetName(), command));
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

            // CPedFactoryNY Test
            if (e.KeyCode == Keys.B) {
                uint modelHash = RAGE.atStringHash("F_Y_NURSE");
                CModelInfo.GetModelInfo(modelHash, out int index);
                CStreaming.ScriptRequestModel((int)modelHash);
                CStreaming.LoadAllRequestedModels(false);

                GTAMatrix mat = CPed.FromPointer(CPlayerInfo.FindPlayerPed()).Matrix;
                mat.pos.X += 2;

                CPed ped = CPedFactoryNY.CreatePed(tSpawnData.Default(), index, mat, true, true);
                CWorld.Add(ped, false);
            }

            // CVehicleFactoryNY Test
            if (e.KeyCode == Keys.N) {
                uint modelHash = RAGE.atStringHash("admiral");
                CModelInfo.GetModelInfo(modelHash, out int index);
                CStreaming.ScriptRequestModel((int)modelHash);
                CStreaming.LoadAllRequestedModels(false);

                GTAMatrix mat = CPed.FromPointer(CPlayerInfo.FindPlayerPed()).Matrix;
                mat.pos.X += 2;

                CVehicle veh = CVehicleFactoryNY.CreateVehicle(index, (int)eVehicleCreatedBy.RANDOM_VEHICLE, mat, true);
                CWorld.Add(veh, false);
            }

            if (e.KeyCode == Keys.U)
            {
                // IV-SDK Task test
                int playerHandle = (int)CPools.GetPedPool().GetIndex(CPlayerInfo.FindPlayerPed());

                //UIntPtr task = CTaskComplexDie.Create(0, 0, 44, 190, 4.0f, 0.0f, 1);
                //UIntPtr task = CTaskComplexWanderStandard.Create(2, 0f, true, 2.5f, 1);
                //CTheScripts.GivePedScriptedTask(playerHandle, task, 5);

                // The KeyUp and KeyDown events will now get raised from the ProcessPad event which does NOT use the CTheScripts.SetDummyThread(); and CTheScripts.RestorePreviousThread(); method!
                // SO SIMPLY DOING THIS NO LONGER WORKS IN IV-SDK.NET v0.8 AND UP:
                //_TASK_FALL_AND_GET_UP(playerHandle, 1, 1);

                // To get native tasks to work in the KeyUp and KeyDown events you will have to do this:
                CTheScripts.SetDummyThread();
                _TASK_FALL_AND_GET_UP(playerHandle, 1, 1);
                CTheScripts.RestorePreviousThread();


                ShowSubtitleMessage("IV-SDK Task test");

                // Mouse test
                //CGame.Mouse.IsVisible = !CGame.Mouse.IsVisible;

                // Pickup test
                //if (pickup == 0)
                //{
                //    Vector3 posI = IVSDKDotNet.Helper.GetPositionInFrontOfEntity(playerPos, IVSDKDotNet.Helper.HeadingToDirection(heading), 5f);

                //    GET_GROUND_Z_FOR_3D_COORD(posI.X, posI.Y, posI.Z, out float groundZ);

                //    GET_WEAPONTYPE_MODEL((int)eWeaponType.WEAPON_AK47, out uint model);
                //    CREATE_PICKUP_ROTATE(model, 23, 22, posI.X, posI.Y, groundZ, 90f, 0f, 0f, out pickup);
                //}
                //else
                //{
                //    REMOVE_PICKUP(pickup);
                //    pickup = 0;
                //}
            }

        }

    }
}
