using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Windows.Forms;

using CCL.GTAIV;

using IVSDKDotNet;
using IVSDKDotNet.Attributes;
using IVSDKDotNet.Enums;
using static IVSDKDotNet.Native.Natives;

namespace TestScript
{
    public class Main : Script
    {

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

        private Vector3 CamOffsetUp;
        private Vector3 CamOffsetRight;
        private Vector3 CamOffsetPos;
        private Vector3 CamOffsetAt;

        private int checkPointId;

        #region Variables
        private int playerPed;
        public Vector3 playerPos;
        private float heading;

        [Separator("Text")]
        [Tooltip("This is a test tooltip!")]
        public string text = "Hello world!";

        public Color color;

        private float fov = 60f;
        private float rot;

        private int pickup;
        private int ladderObject;

        int intNum;

        private IntPtr discordImagePtr;
        private float rotation;
        private int width, height;

        [Space(10f)]
        public bool ImGuiTestOpen;
        public bool MainMenuOpen = true;
        public bool EnableTestImGuiDraw;

        private int slot;

        bool disable;

        int selectedIndex = 0;

        int ints = 22;
        int[] ints2 = new int[] { 69, 420 };
        int[] ints3 = new int[] { 69, 420, 1337 };
        int[] ints4 = new int[] { 69, 420, 1337, 5000 };

        float floats = 22.2f;
        float[] floats2 = new float[] { 69.2f, 420.1f };
        float[] floats3 = new float[] { 69.2f, 420.1f, 1337.7f };
        float[] floats4 = new float[] { 69.2f, 420.1f, 1337.7f, 5000f };

        private List<int> pedsWhichGotArmor = new List<int>();
        #endregion

        #region Constructor
        public Main()
        {
            OnlyRaiseKeyEventsWhenInGame = true;

            // Subscribe to script events
            Initialized += Main_Initialized;
            Uninitialize += Main_Uninitialize;

            Tick += Main_Tick;
            KeyDown += Main_KeyDown;
            ProcessAutomobile += Main_ProcessAutomobile;
            ProcessCamera += Main_ProcessCamera;
            ScriptCommandReceived += Main_ScriptCommandReceived;
            Drawing += Main_Drawing;
            OnFirstD3D9Frame += Main_OnFirstD3D9Frame;

            // Runs every 3 seconds (3000 milliseconds = 3 seconds)
            WaitTick += Main_WaitTick;
            WaitTickInterval = 3000;

            RAGE.OnWindowFocusChanged += CGame_OnWindowFocusChanged;
            RAGE.OnWndProcMessageReceived += RAGE_OnWndProcMessageReceived;
        }
        #endregion

        #region Functions
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
        #endregion

        #region Methods
        private void ImGuiTest()
        {
            if (ImGuiTestOpen)
            {
                ImGuiIV.Begin("test", ref ImGuiTestOpen, eImGuiWindowFlags.None);

                ImGuiIV.Button("Test122424");

                ImGuiIV.Text("Test Listbox below!");

                if (ImGuiIV.BeginListBox("test"))
                {

                    string[] items = new string[]
                    {
                        "test", "item", "catscmakaro", "test", "test2", "test3", "test4", "test5",
                    };

                    for (int i = 0; i < items.Length; i++)
                    {
                        if (ImGuiIV.Selectable(items[i], selectedIndex == i))
                            selectedIndex = i;
                    }

                    ImGuiIV.EndListBox();
                }

                Vector3 color = Vector3.Zero;
                if (ImGuiIV.ColorEdit3("test2", ref color, eImGuiColorEditFlags.Uint8 | eImGuiColorEditFlags.InputRGB))
                {
                    // color changed, convert to rgb
                }

                ImGuiIV.SeparatorText("DragInts");
                ImGuiIV.DragInt("Test DragInt!", ref ints);
                ImGuiIV.DragInt2("Test DragInt2!", ref ints2);
                ImGuiIV.DragInt3("Test DragInt3!", ref ints3);
                ImGuiIV.DragInt4("Test DragInt4!", ref ints4);

                ImGuiIV.SeparatorText("DragFloats");
                ImGuiIV.DragFloat("Test DragFloat!", ref floats);
                ImGuiIV.DragFloat2("Test DragFloat2!", ref floats2);
                ImGuiIV.DragFloat3("Test DragFloat3!", ref floats3);
                ImGuiIV.DragFloat4("Test DragFloat4!", ref floats4);

                ImGuiIV.SeparatorText("SliderInts");
                ImGuiIV.SliderInt("Test SliderInt!", ref ints, 0, 5000);
                ImGuiIV.SliderInt2("Test SliderInt2!", ref ints2, 0, 5000);
                ImGuiIV.SliderInt3("Test SliderInt3!", ref ints3, 0, 5000);
                ImGuiIV.SliderInt4("Test SliderInt4!", ref ints4, 0, 5000);

                ImGuiIV.SeparatorText("SliderFloats");
                ImGuiIV.SliderFloat("Test SliderFloat!", ref floats, 0f, 5000f);
                ImGuiIV.SliderFloat2("Test SliderFloat2!", ref floats2, 0f, 5000f);
                ImGuiIV.SliderFloat3("Test SliderFloat3!", ref floats3, 0f, 5000f);
                ImGuiIV.SliderFloat4("Test SliderFloat4!", ref floats4, 0f, 5000f);

                ImGuiIV.SeparatorText("Inputs");

                ImGuiIV.InputText("Input text", ref text);

                ImGuiIV.Text("CarLodDistanceHigh: {0}", IVVisibilityPlugins.CarLodDistanceHigh);
                ImGuiIV.Text("CarLodDistanceMed: {0}", IVVisibilityPlugins.CarLodDistanceMed);

                ImGuiIV.Dummy();
                ImGuiIV.Text("PedInCarLodDistanceHigh: {0}", IVVisibilityPlugins.PedInCarLodDistanceHigh);
                ImGuiIV.Dummy();

                ImGuiIV.Text("PedLodDistanceHigh: {0}", IVVisibilityPlugins.PedLodDistanceHigh);
                ImGuiIV.Text("PedLodDistanceMed: {0}", IVVisibilityPlugins.PedLodDistanceMed);
                ImGuiIV.Text("PedLodDistanceLow: {0}", IVVisibilityPlugins.PedLodDistanceLow);

                ImGuiIV.Dummy();
                ImGuiIV.Text("PedLodDistanceSlod: {0}", IVVisibilityPlugins.PedLodDistanceSlod);

                ImGuiIV.End();
            }
        }


        private void MainMenu()
        {
            ImGuiIV.Begin("Script Test Window", ref MainMenuOpen, eImGuiWindowFlags.None);

            ImGuiIV.CheckBox("Test ImGui Window Open", ref ImGuiTestOpen);
            ImGuiIV.CheckBox("Enable Test ImGui Drawing", ref EnableTestImGuiDraw);
            
            ImGuiIV.DragFloat3("Offset Up", ref CamOffsetUp);
            ImGuiIV.DragFloat3("Offset Right", ref CamOffsetRight);
            ImGuiIV.DragFloat3("Offset Pos", ref CamOffsetPos);
            ImGuiIV.DragFloat3("Offset At", ref CamOffsetAt);

            ImGuiIV.Text("LastCheckpointId: {0}", checkPointId);

            if (ImGuiIV.Button("Create checkpoint"))
            {
                IVPed playerPedNEW = IVPed.FromUIntPtr(IVPlayerInfo.FindThePlayerPed());
                checkPointId = CREATE_CHECKPOINT(0, playerPedNEW.Matrix.Pos.X, playerPedNEW.Matrix.Pos.Y, playerPedNEW.Matrix.Pos.Z, 0f, 0f);
            }

            ImGuiIV.Dummy(new Vector2(0f, 10f));

            if (ImGuiIV.BeginTabBar("##TestTabBar"))
            {

                if (ImGuiIV.BeginTabItem("Other"))
                {
                    GET_GAME_TIMER(out uint timer);

                    ImGuiIV.Text("GameTimer: {0}", timer);
                    ImGuiIV.Text("FrameCount: {0}", GET_FRAME_COUNT());
                    
                    ImGuiIV.EndTabItem();
                }

                IVGameTab();
                IVRestartTab();
                IVStreamingTab();
                IVVisibilityPluginsTab();
                IVPcSaveTab();
                IVGenericGameStorageTab();
                IVStatsTab();
                IVPlayerInfoTab();

                CurrentVehicleTab(IVPlayerInfo.FindThePlayerPed());

                ImGuiIV.EndTabBar();
            }

            ImGuiIV.End();
        }
        private void IVGameTab()
        {
            if (ImGuiIV.BeginTabItem("IVGame"))
            {
                ImGuiIV.Text("Bounds: {0}", IVGame.Bounds);

                ImGuiIV.EndTabItem();
            }
        }
        private void IVRestartTab()
        {
            if (ImGuiIV.BeginTabItem("IVRestart"))
            {
                if (ImGuiIV.Button("Save"))
                    IVRestart.Save();
                ImGuiIV.SameLine();
                if (ImGuiIV.Button("Load"))
                    IVRestart.Load();

                ImGuiIV.Separator();

                int ExtraPoliceStationRestartWhenToUse = (int)IVRestart.ExtraPoliceStationRestartWhenToUse; ImGuiIV.DragInt("ExtraPoliceStationRestartWhenToUse", ref ExtraPoliceStationRestartWhenToUse, 0, int.MaxValue); IVRestart.ExtraPoliceStationRestartWhenToUse = (uint)ExtraPoliceStationRestartWhenToUse;
                float ExtraPoliceStationRestartHeading = IVRestart.ExtraPoliceStationRestartHeading; ImGuiIV.DragFloat("ExtraPoliceStationRestartHeading", ref ExtraPoliceStationRestartHeading); IVRestart.ExtraPoliceStationRestartHeading = ExtraPoliceStationRestartHeading;
                Vector3 ExtraPoliceStationRestartCoors = IVRestart.ExtraPoliceStationRestartCoors; ImGuiIV.DragFloat3("ExtraPoliceStationRestartCoors", ref ExtraPoliceStationRestartCoors); IVRestart.ExtraPoliceStationRestartCoors = ExtraPoliceStationRestartCoors;

                int ExtraHospitalRestartWhenToUse = (int)IVRestart.ExtraHospitalRestartWhenToUse; ImGuiIV.DragInt("ExtraHospitalRestartWhenToUse", ref ExtraHospitalRestartWhenToUse, 0, int.MaxValue); IVRestart.ExtraHospitalRestartWhenToUse = (uint)ExtraHospitalRestartWhenToUse;
                float ExtraHospitalRestartHeading = IVRestart.ExtraHospitalRestartHeading; ImGuiIV.DragFloat("ExtraHospitalRestartHeading", ref ExtraHospitalRestartHeading); IVRestart.ExtraHospitalRestartHeading = ExtraHospitalRestartHeading;
                Vector3 ExtraHospitalRestartCoors = IVRestart.ExtraHospitalRestartCoors; ImGuiIV.DragFloat3("ExtraHospitalRestartCoors", ref ExtraHospitalRestartCoors); IVRestart.ExtraHospitalRestartCoors = ExtraHospitalRestartCoors;

                bool FadeInAfterNextDeath = IVRestart.FadeInAfterNextDeath; ImGuiIV.CheckBox("FadeInAfterNextDeath", ref FadeInAfterNextDeath); IVRestart.FadeInAfterNextDeath = FadeInAfterNextDeath;
                float OverrideHeading = IVRestart.OverrideHeading; ImGuiIV.DragFloat("OverrideHeading", ref OverrideHeading); IVRestart.OverrideHeading = OverrideHeading;
                Vector3 OverridePosition = IVRestart.OverridePosition; ImGuiIV.DragFloat3("OverridePosition", ref OverridePosition); IVRestart.OverridePosition = OverridePosition;
                bool OverrideRestart = IVRestart.OverrideRestart; ImGuiIV.CheckBox("OverrideRestart", ref OverrideRestart); IVRestart.OverrideRestart = OverrideRestart;

                int PoliceRestartWhenToUse = IVRestart.PoliceRestartWhenToUse; ImGuiIV.DragInt("PoliceRestartWhenToUse", ref PoliceRestartWhenToUse); IVRestart.PoliceRestartWhenToUse = PoliceRestartWhenToUse;
                float PoliceRestartHeadings = IVRestart.PoliceRestartHeadings; ImGuiIV.DragFloat("PoliceRestartHeadings", ref PoliceRestartHeadings); IVRestart.PoliceRestartHeadings = PoliceRestartHeadings;
                Vector3 PoliceRestartPoints = IVRestart.PoliceRestartPoints; ImGuiIV.DragFloat3("PoliceRestartPoints", ref PoliceRestartPoints); IVRestart.PoliceRestartPoints = PoliceRestartPoints;

                int NumberOfSafehouses = (int)IVRestart.NumberOfSafehouses; ImGuiIV.DragInt("NumberOfSafehouses", ref NumberOfSafehouses); IVRestart.NumberOfSafehouses = (uint)NumberOfSafehouses;
                int NumberOfPoliceRestarts = (int)IVRestart.NumberOfPoliceRestarts; ImGuiIV.DragInt("NumberOfPoliceRestarts", ref NumberOfPoliceRestarts); IVRestart.NumberOfPoliceRestarts = (uint)NumberOfPoliceRestarts;
                int NumberOfHospitalRestarts = (int)IVRestart.NumberOfHospitalRestarts; ImGuiIV.DragInt("NumberOfHospitalRestarts", ref NumberOfHospitalRestarts); IVRestart.NumberOfHospitalRestarts = (uint)NumberOfHospitalRestarts;

                if (ImGuiIV.BeginListBox("Hospital Restart Points"))
                {
                    for (int i = 0; i < IVRestart.HospitalRestartPoints.Length; i++)
                    {
                        Vector3 p = IVRestart.HospitalRestartPoints[i];
                        float heading = IVRestart.HospitalRestartHeadings[i];
                        int whenToUse = IVRestart.HospitalRestartWhenToUse[i];

                        ImGuiIV.Text("Pos: {0}, Head: {1}, WhenToUse: {2}", p, heading, whenToUse);
                    }

                    ImGuiIV.EndListBox();
                }
                if (ImGuiIV.BeginListBox("Safehouses"))
                {
                    for (int i = 0; i < IVRestart.Safehouses.Length; i++)
                    {
                        IVSafehouse safehouse = IVRestart.Safehouses[i];
                        ImGuiIV.Text("Name: {0}, Enabled: {1}, Pos: {2}, Head: {3}, WhenToUse: {4}", safehouse.Name, safehouse.Enabled, safehouse.Position, safehouse.Heading, safehouse.WhenToUse);
                    }

                    ImGuiIV.EndListBox();
                }

                ImGuiIV.EndTabItem();
            }
        }
        private void IVStreamingTab()
        {
            if (ImGuiIV.BeginTabItem("IVStreaming"))
            {
                bool DisableStreaming = IVStreaming.DisableStreaming; ImGuiIV.CheckBox("DisableStreaming", ref DisableStreaming); IVStreaming.DisableStreaming = DisableStreaming;
                int PedModelBudget = (int)IVStreaming.PedModelBudget; ImGuiIV.DragInt("PedModelBudget", ref PedModelBudget, 0, int.MaxValue); IVStreaming.PedModelBudget = (uint)PedModelBudget;
                int VehicleModelBudget = (int)IVStreaming.VehicleModelBudget; ImGuiIV.DragInt("VehicleModelBudget", ref VehicleModelBudget, 0, int.MaxValue); IVStreaming.VehicleModelBudget = (uint)VehicleModelBudget;

                ImGuiIV.EndTabItem();
            }
        }
        private void IVVisibilityPluginsTab()
        {
            if (ImGuiIV.BeginTabItem("IVVisibilityPlugins"))
            {
                string StipplePath = IVVisibilityPlugins.StipplePath; 
                
                if (ImGuiIV.InputText("StipplePath", ref StipplePath))
                {
                    IVVisibilityPlugins.StipplePath = StipplePath;
                }
                
                float CarLodDistanceMed = IVVisibilityPlugins.CarLodDistanceMed; ImGuiIV.DragFloat("CarLodDistanceMed", ref CarLodDistanceMed); IVVisibilityPlugins.CarLodDistanceMed = CarLodDistanceMed;
                float CarLodDistanceHigh = IVVisibilityPlugins.CarLodDistanceHigh; ImGuiIV.DragFloat("CarLodDistanceHigh", ref CarLodDistanceHigh); IVVisibilityPlugins.CarLodDistanceHigh = CarLodDistanceHigh;

                float PedLodDistanceSlod = IVVisibilityPlugins.PedLodDistanceSlod; ImGuiIV.DragFloat("PedLodDistanceSlod", ref PedLodDistanceSlod); IVVisibilityPlugins.PedLodDistanceSlod = PedLodDistanceSlod;
                float PedLodDistanceVlow = IVVisibilityPlugins.PedLodDistanceVlow; ImGuiIV.DragFloat("PedLodDistanceVlow", ref PedLodDistanceVlow); IVVisibilityPlugins.PedLodDistanceVlow = PedLodDistanceVlow;
                float PedLodDistanceLow = IVVisibilityPlugins.PedLodDistanceLow; ImGuiIV.DragFloat("PedLodDistanceLow", ref PedLodDistanceLow); IVVisibilityPlugins.PedLodDistanceLow = PedLodDistanceLow;
                float PedLodDistanceMed = IVVisibilityPlugins.PedLodDistanceMed; ImGuiIV.DragFloat("PedLodDistanceMed", ref PedLodDistanceMed); IVVisibilityPlugins.PedLodDistanceMed = PedLodDistanceMed;
                float PedInCarLodDistanceHigh = IVVisibilityPlugins.PedInCarLodDistanceHigh; ImGuiIV.DragFloat("PedInCarLodDistanceHigh", ref PedInCarLodDistanceHigh); IVVisibilityPlugins.PedInCarLodDistanceHigh = PedInCarLodDistanceHigh;
                float PedLodDistanceHigh = IVVisibilityPlugins.PedLodDistanceHigh; ImGuiIV.DragFloat("PedLodDistanceHigh", ref PedLodDistanceHigh); IVVisibilityPlugins.PedLodDistanceHigh = PedLodDistanceHigh;

                ImGuiIV.EndTabItem();
            }
        }
        private void IVPcSaveTab()
        {
            if (ImGuiIV.BeginTabItem("IVPcSave"))
            {

                ImGuiIV.SliderInt("Save Slot", ref slot, 0, 12);

                if (ImGuiIV.Button("Save"))
                    IVPcSave.SaveSlot(slot);
                if (ImGuiIV.Button("Load"))
                    IVPcSave.LoadSlot(slot);

                ImGuiIV.EndTabItem();
            }
        }
        private void IVGenericGameStorageTab()
        {
            if (ImGuiIV.BeginTabItem("IVGenericGameStorage"))
            {
                string s = IVGenericGameStorage.ValidSaveName;

                if (ImGuiIV.InputText("ValidSaveName", ref s))
                {
                    IVGenericGameStorage.ValidSaveName = s;
                }

                ImGuiIV.EndTabItem();
            }
        }
        private void IVStatsTab()
        {
            if (ImGuiIV.BeginTabItem("IVStats"))
            {
                string s = IVStats.LastMissionPassedName;

                ImGuiIV.BeginDisabled();
                ImGuiIV.InputText("LastMissionPassedName", ref s);
                ImGuiIV.EndDisabled();

                ImGuiIV.EndTabItem();
            }
        }
        private void IVPlayerInfoTab()
        {
            if (ImGuiIV.BeginTabItem("IVPlayerInfo"))
            {
                IVPlayerInfo ptr = IVPlayerInfo.GetPlayerInfo(0);

                if (ptr != null)
                    ImGuiIV.Text("Address: {0} ({1})", ptr.GetUIntPtr().ToUInt32().ToString(), ptr.GetUIntPtr().ToUInt32().ToString("X"));

                ImGuiIV.EndTabItem();
            }
        }

        private void CurrentVehicleTab(UIntPtr playerPedPtr)
        {
            if (playerPedPtr == UIntPtr.Zero)
                return;

            IVPed playerPed = IVPed.FromUIntPtr(playerPedPtr);

            if (playerPed.GetVehicle() == UIntPtr.Zero)
                return;

            IVVehicle veh = IVVehicle.FromUIntPtr(playerPed.GetVehicle());

            if (ImGuiIV.BeginTabItem("CurrentVehicle"))
            {
                int vehicleHandle = veh.GetHandle();

                ImGuiIV.Text("Address: {0}", veh.GetUIntPtr());
                ImGuiIV.Text("Handle: {0}", vehicleHandle);

                ImGuiIV.Spacing();

                if (ImGuiIV.TreeNode("VehicleFlags"))
                {

                    bool _f0 = veh.VehicleFlags._f0; ImGuiIV.CheckBox("_f0", ref _f0); veh.VehicleFlags._f0 = _f0;
                    bool _f1 = veh.VehicleFlags._f1; ImGuiIV.CheckBox("_f1", ref _f1); veh.VehicleFlags._f1 = _f1;
                    bool _f2 = veh.VehicleFlags._f2; ImGuiIV.CheckBox("_f2", ref _f2); veh.VehicleFlags._f2 = _f2;
                    bool EngineOn = veh.VehicleFlags.EngineOn; ImGuiIV.CheckBox("EngineOn", ref EngineOn); veh.VehicleFlags.EngineOn = EngineOn;
                    bool EngineStarting = veh.VehicleFlags.EngineStarting; ImGuiIV.CheckBox("EngineStarting", ref EngineStarting); veh.VehicleFlags.EngineStarting = EngineStarting;
                    bool _f5 = veh.VehicleFlags._f5; ImGuiIV.CheckBox("_f5", ref _f5); veh.VehicleFlags._f5 = _f5;
                    bool _f6 = veh.VehicleFlags._f6; ImGuiIV.CheckBox("_f6", ref _f6); veh.VehicleFlags._f6 = _f6;
                    bool IsHandbrakeOn = veh.VehicleFlags.IsHandbrakeOn; ImGuiIV.CheckBox("IsHandbrakeOn", ref IsHandbrakeOn); veh.VehicleFlags.IsHandbrakeOn = IsHandbrakeOn;
                    bool LightsOn = veh.VehicleFlags.LightsOn; ImGuiIV.CheckBox("LightsOn", ref LightsOn); veh.VehicleFlags.LightsOn = LightsOn;
                    bool Freebies = veh.VehicleFlags.Freebies; ImGuiIV.CheckBox("Freebies", ref Freebies); veh.VehicleFlags.Freebies = Freebies;
                    bool _fa = veh.VehicleFlags._fa; ImGuiIV.CheckBox("_fa", ref _fa); veh.VehicleFlags._fa = _fa;
                    bool _fb = veh.VehicleFlags._fb; ImGuiIV.CheckBox("_fb", ref _fb); veh.VehicleFlags._fb = _fb;
                    bool BigVehicle = veh.VehicleFlags.BigVehicle; ImGuiIV.CheckBox("BigVehicle", ref BigVehicle); veh.VehicleFlags.BigVehicle = BigVehicle;
                    bool _fd = veh.VehicleFlags._fd; ImGuiIV.CheckBox("_fd", ref _fd); veh.VehicleFlags._fd = _fd;
                    bool _fe = veh.VehicleFlags._fe; ImGuiIV.CheckBox("_fe", ref _fe); veh.VehicleFlags._fe = _fe;
                    bool _ff = veh.VehicleFlags._ff; ImGuiIV.CheckBox("_ff", ref _ff); veh.VehicleFlags._ff = _ff;
                    bool TakesLessDamage = veh.VehicleFlags.TakesLessDamage; ImGuiIV.CheckBox("TakesLessDamage", ref TakesLessDamage); veh.VehicleFlags.TakesLessDamage = TakesLessDamage;
                    bool HasBeenOwnedByPlayer = veh.VehicleFlags.HasBeenOwnedByPlayer; ImGuiIV.CheckBox("HasBeenOwnedByPlayer", ref HasBeenOwnedByPlayer); veh.VehicleFlags.HasBeenOwnedByPlayer = HasBeenOwnedByPlayer;
                    bool NeedsToBeHotWired = veh.VehicleFlags.NeedsToBeHotWired; ImGuiIV.CheckBox("NeedsToBeHotWired", ref NeedsToBeHotWired); veh.VehicleFlags.NeedsToBeHotWired = NeedsToBeHotWired;
                    bool _f14 = veh.VehicleFlags._f14; ImGuiIV.CheckBox("_f14", ref _f14); veh.VehicleFlags._f14 = _f14;
                    bool _f15 = veh.VehicleFlags._f15; ImGuiIV.CheckBox("_f15", ref _f15); veh.VehicleFlags._f15 = _f15;
                    bool _f16 = veh.VehicleFlags._f16; ImGuiIV.CheckBox("_f16", ref _f16); veh.VehicleFlags._f16 = _f16;
                    bool _f17 = veh.VehicleFlags._f17; ImGuiIV.CheckBox("_f17", ref _f17); veh.VehicleFlags._f17 = _f17;
                    bool _f18 = veh.VehicleFlags._f18; ImGuiIV.CheckBox("_f18", ref _f18); veh.VehicleFlags._f18 = _f18;
                    bool PartOfConvoy = veh.VehicleFlags.PartOfConvoy; ImGuiIV.CheckBox("PartOfConvoy", ref PartOfConvoy); veh.VehicleFlags.PartOfConvoy = PartOfConvoy;
                    bool HeliStabiliser = veh.VehicleFlags.HeliStabiliser; ImGuiIV.CheckBox("HeliStabiliser", ref HeliStabiliser); veh.VehicleFlags.HeliStabiliser = HeliStabiliser;
                    bool _f1b = veh.VehicleFlags._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); veh.VehicleFlags._f1b = _f1b;
                    bool IsDead = veh.VehicleFlags.IsDead; ImGuiIV.CheckBox("IsDead", ref IsDead); veh.VehicleFlags.IsDead = IsDead;
                    bool CanBurstTyres = veh.VehicleFlags.CanBurstTyres; ImGuiIV.CheckBox("CanBurstTyres", ref CanBurstTyres); veh.VehicleFlags.CanBurstTyres = CanBurstTyres;
                    bool _f1d = veh.VehicleFlags._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); veh.VehicleFlags._f1d = _f1d;
                    bool _f1e = veh.VehicleFlags._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); veh.VehicleFlags._f1e = _f1e;
                    bool _f1f = veh.VehicleFlags._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); veh.VehicleFlags._f1f = _f1f;

                    ImGuiIV.TreePop();
                }
                if (ImGuiIV.TreeNode("VehicleFlags2"))
                {

                    bool _f0 = veh.VehicleFlags2._f0; ImGuiIV.CheckBox("_f0", ref _f0); veh.VehicleFlags2._f0 = _f0;
                    bool _f1 = veh.VehicleFlags2._f1; ImGuiIV.CheckBox("_f1", ref _f1); veh.VehicleFlags2._f1 = _f1;
                    bool _f2 = veh.VehicleFlags2._f2; ImGuiIV.CheckBox("_f2", ref _f2); veh.VehicleFlags2._f2 = _f2;
                    bool _f3 = veh.VehicleFlags2._f3; ImGuiIV.CheckBox("_f3", ref _f3); veh.VehicleFlags2._f3 = _f3;
                    bool _f4 = veh.VehicleFlags2._f4; ImGuiIV.CheckBox("_f4", ref _f4); veh.VehicleFlags2._f4 = _f4;
                    bool AlwaysCreateSkids = veh.VehicleFlags2.AlwaysCreateSkids; ImGuiIV.CheckBox("AlwaysCreateSkids", ref AlwaysCreateSkids); veh.VehicleFlags2.AlwaysCreateSkids = AlwaysCreateSkids;
                    bool CanBeTargetted = veh.VehicleFlags2.CanBeTargetted; ImGuiIV.CheckBox("CanBeTargetted", ref CanBeTargetted); veh.VehicleFlags2.CanBeTargetted = CanBeTargetted;
                    bool CanBeTargetedByHSmmissile = veh.VehicleFlags2.CanBeTargetedByHSmmissile; ImGuiIV.CheckBox("CanBeTargetedByHSmmissile", ref CanBeTargetedByHSmmissile); veh.VehicleFlags2.CanBeTargetedByHSmmissile = CanBeTargetedByHSmmissile;
                    bool LongLight = veh.VehicleFlags2.LongLight; ImGuiIV.CheckBox("LongLight", ref LongLight); veh.VehicleFlags2.LongLight = LongLight;
                    bool _fa = veh.VehicleFlags2._fa; ImGuiIV.CheckBox("_fa", ref _fa); veh.VehicleFlags2._fa = _fa;
                    bool _fb = veh.VehicleFlags2._fb; ImGuiIV.CheckBox("_fb", ref _fb); veh.VehicleFlags2._fb = _fb;
                    bool SirenSwitchedOn = veh.VehicleFlags2.SirenSwitchedOn; ImGuiIV.CheckBox("SirenSwitchedOn", ref SirenSwitchedOn); veh.VehicleFlags2.SirenSwitchedOn = SirenSwitchedOn;
                    bool SirenRelated = veh.VehicleFlags2.SirenRelated; ImGuiIV.CheckBox("SirenRelated", ref SirenRelated); veh.VehicleFlags2.SirenRelated = SirenRelated;
                    bool _fe = veh.VehicleFlags2._fe; ImGuiIV.CheckBox("_fe", ref _fe); veh.VehicleFlags2._fe = _fe;
                    bool _ff = veh.VehicleFlags2._ff; ImGuiIV.CheckBox("_ff", ref _ff); veh.VehicleFlags2._ff = _ff;
                    bool _f10 = veh.VehicleFlags2._f10; ImGuiIV.CheckBox("_f10", ref _f10); veh.VehicleFlags2._f10 = _f10;
                    bool _f11 = veh.VehicleFlags2._f11; ImGuiIV.CheckBox("_f11", ref _f11); veh.VehicleFlags2._f11 = _f11;
                    bool BikeRiderWillPutDownFootWhenStopped = veh.VehicleFlags2.BikeRiderWillPutDownFootWhenStopped; ImGuiIV.CheckBox("BikeRiderWillPutDownFootWhenStopped", ref BikeRiderWillPutDownFootWhenStopped); veh.VehicleFlags2.BikeRiderWillPutDownFootWhenStopped = BikeRiderWillPutDownFootWhenStopped;
                    bool ProvideCover = veh.VehicleFlags2.ProvideCover; ImGuiIV.CheckBox("ProvideCover", ref ProvideCover); veh.VehicleFlags2.ProvideCover = ProvideCover;
                    bool _f15 = veh.VehicleFlags2._f15; ImGuiIV.CheckBox("_f15", ref _f15); veh.VehicleFlags2._f15 = _f15;
                    bool _f16 = veh.VehicleFlags2._f16; ImGuiIV.CheckBox("_f16", ref _f16); veh.VehicleFlags2._f16 = _f16;
                    bool VehicleIsConsideredByPlayer = veh.VehicleFlags2.VehicleIsConsideredByPlayer; ImGuiIV.CheckBox("VehicleIsConsideredByPlayer", ref VehicleIsConsideredByPlayer); veh.VehicleFlags2.VehicleIsConsideredByPlayer = VehicleIsConsideredByPlayer;
                    bool PetrolTankWeakpoint = veh.VehicleFlags2.PetrolTankWeakpoint; ImGuiIV.CheckBox("PetrolTankWeakpoint", ref PetrolTankWeakpoint); veh.VehicleFlags2.PetrolTankWeakpoint = PetrolTankWeakpoint;
                    bool _f19 = veh.VehicleFlags2._f19; ImGuiIV.CheckBox("_f19", ref _f19); veh.VehicleFlags2._f19 = _f19;
                    bool CarBeenResprayed = veh.VehicleFlags2.CarBeenResprayed; ImGuiIV.CheckBox("CarBeenResprayed", ref CarBeenResprayed); veh.VehicleFlags2.CarBeenResprayed = CarBeenResprayed;
                    bool _f1b = veh.VehicleFlags2._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); veh.VehicleFlags2._f1b = _f1b;
                    bool _f1c = veh.VehicleFlags2._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); veh.VehicleFlags2._f1c = _f1c;
                    bool _f1d = veh.VehicleFlags2._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); veh.VehicleFlags2._f1d = _f1d;
                    bool _f1e = veh.VehicleFlags2._f1e; ImGuiIV.CheckBox("_f0", ref _f1e); veh.VehicleFlags2._f1e = _f1e;

                    ImGuiIV.TreePop();
                }
                if (ImGuiIV.TreeNode("VehicleFlags3"))
                {

                    bool LeftIndicator = veh.VehicleFlags3.LeftIndicator; ImGuiIV.CheckBox("LeftIndicator", ref LeftIndicator); veh.VehicleFlags3.LeftIndicator = LeftIndicator;
                    bool RightIndicator = veh.VehicleFlags3.RightIndicator; ImGuiIV.CheckBox("RightIndicator", ref RightIndicator); veh.VehicleFlags3.RightIndicator = RightIndicator;
                    bool HazardLights = veh.VehicleFlags3.HazardLights; ImGuiIV.CheckBox("HazardLights", ref HazardLights); veh.VehicleFlags3.HazardLights = HazardLights;
                    bool IndicatorLights = veh.VehicleFlags3.IndicatorLights; ImGuiIV.CheckBox("IndicatorLights", ref IndicatorLights); veh.VehicleFlags3.IndicatorLights = IndicatorLights;
                    bool _f3 = veh.VehicleFlags3._f3; ImGuiIV.CheckBox("_f3", ref _f3); veh.VehicleFlags3._f3 = _f3;
                    bool InteriorLights = veh.VehicleFlags3.InteriorLights; ImGuiIV.CheckBox("InteriorLights", ref InteriorLights); veh.VehicleFlags3.InteriorLights = InteriorLights;
                    bool VehicleIsHot = veh.VehicleFlags3.VehicleIsHot; ImGuiIV.CheckBox("VehicleIsHot", ref VehicleIsHot); veh.VehicleFlags3.VehicleIsHot = VehicleIsHot;
                    bool _f6 = veh.VehicleFlags3._f6; ImGuiIV.CheckBox("_f6", ref _f6); veh.VehicleFlags3._f6 = _f6;
                    bool _f7 = veh.VehicleFlags3._f7; ImGuiIV.CheckBox("_f7", ref _f7); veh.VehicleFlags3._f7 = _f7;
                    bool _f8 = veh.VehicleFlags3._f8; ImGuiIV.CheckBox("_f8", ref _f8); veh.VehicleFlags3._f8 = _f8;
                    bool _f9 = veh.VehicleFlags3._f9; ImGuiIV.CheckBox("_f9", ref _f9); veh.VehicleFlags3._f9 = _f9;
                    bool Deleted = veh.VehicleFlags3.Deleted; ImGuiIV.CheckBox("Deleted", ref Deleted); veh.VehicleFlags3.Deleted = Deleted;
                    bool _fb = veh.VehicleFlags3._fb; ImGuiIV.CheckBox("_fb", ref _fb); veh.VehicleFlags3._fb = _fb;
                    bool TiresIsDestroyed = veh.VehicleFlags3.TiresIsDestroyed; ImGuiIV.CheckBox("TiresIsDestroyed", ref TiresIsDestroyed); veh.VehicleFlags3.TiresIsDestroyed = TiresIsDestroyed;
                    bool PretendOccupants = veh.VehicleFlags3.PretendOccupants; ImGuiIV.CheckBox("PretendOccupants", ref PretendOccupants); veh.VehicleFlags3.PretendOccupants = PretendOccupants;
                    bool _fe = veh.VehicleFlags3._fe; ImGuiIV.CheckBox("_fe", ref _fe); veh.VehicleFlags3._fe = _fe;
                    bool _ff = veh.VehicleFlags3._ff; ImGuiIV.CheckBox("_ff", ref _ff); veh.VehicleFlags3._ff = _ff;
                    bool _f10 = veh.VehicleFlags3._f10; ImGuiIV.CheckBox("_f10", ref _f10); veh.VehicleFlags3._f10 = _f10;
                    bool _f11 = veh.VehicleFlags3._f11; ImGuiIV.CheckBox("_f11", ref _f11); veh.VehicleFlags3._f11 = _f11;
                    bool _f12 = veh.VehicleFlags3._f12; ImGuiIV.CheckBox("_f12", ref _f12); veh.VehicleFlags3._f12 = _f12;
                    bool _f13 = veh.VehicleFlags3._f13; ImGuiIV.CheckBox("_f13", ref _f13); veh.VehicleFlags3._f13 = _f13;
                    bool _f14 = veh.VehicleFlags3._f14; ImGuiIV.CheckBox("_f14", ref _f14); veh.VehicleFlags3._f14 = _f14;
                    bool HaveSiren = veh.VehicleFlags3.HaveSiren; ImGuiIV.CheckBox("HaveSiren", ref HaveSiren); veh.VehicleFlags3.HaveSiren = HaveSiren;
                    bool PoliceFocusWillTrackCar = veh.VehicleFlags3.PoliceFocusWillTrackCar; ImGuiIV.CheckBox("PoliceFocusWillTrackCar", ref PoliceFocusWillTrackCar); veh.VehicleFlags3.PoliceFocusWillTrackCar = PoliceFocusWillTrackCar;
                    bool _f17 = veh.VehicleFlags3._f17; ImGuiIV.CheckBox("_f17", ref _f17); veh.VehicleFlags3._f17 = _f17;
                    bool _f18 = veh.VehicleFlags3._f18; ImGuiIV.CheckBox("_f18", ref _f18); veh.VehicleFlags3._f18 = _f18;
                    bool SetBlipThrottleRandomly = veh.VehicleFlags3.SetBlipThrottleRandomly; ImGuiIV.CheckBox("SetBlipThrottleRandomly", ref SetBlipThrottleRandomly); veh.VehicleFlags3.SetBlipThrottleRandomly = SetBlipThrottleRandomly;
                    bool _f1a = veh.VehicleFlags3._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); veh.VehicleFlags3._f1a = _f1a;
                    bool InCutscene = veh.VehicleFlags3.InCutscene; ImGuiIV.CheckBox("InCutscene", ref InCutscene); veh.VehicleFlags3.InCutscene = InCutscene;
                    bool _f1c = veh.VehicleFlags3._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); veh.VehicleFlags3._f1c = _f1c;
                    bool PoliceVehicle = veh.VehicleFlags3.PoliceVehicle; ImGuiIV.CheckBox("PoliceVehicle", ref PoliceVehicle); veh.VehicleFlags3.PoliceVehicle = PoliceVehicle;
                    bool EmergencyServicesVehicle = veh.VehicleFlags3.EmergencyServicesVehicle; ImGuiIV.CheckBox("EmergencyServicesVehicle", ref EmergencyServicesVehicle); veh.VehicleFlags3.EmergencyServicesVehicle = EmergencyServicesVehicle;
                    bool _f1f = veh.VehicleFlags3._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); veh.VehicleFlags3._f1f = _f1f;

                    ImGuiIV.TreePop();
                }
                if (ImGuiIV.TreeNode("VehicleFlags4"))
                {

                    bool _f0 = veh.VehicleFlags4._f0; ImGuiIV.CheckBox("_f0", ref _f0); veh.VehicleFlags4._f0 = _f0;
                    bool _f1 = veh.VehicleFlags4._f1; ImGuiIV.CheckBox("_f1", ref _f1); veh.VehicleFlags4._f1 = _f1;
                    bool CanBeVisiblyDamaged = veh.VehicleFlags4.CanBeVisiblyDamaged; ImGuiIV.CheckBox("CanBeVisiblyDamaged", ref CanBeVisiblyDamaged); veh.VehicleFlags4.CanBeVisiblyDamaged = CanBeVisiblyDamaged;
                    bool HasStrongAxles = veh.VehicleFlags4.HasStrongAxles; ImGuiIV.CheckBox("HasStrongAxles", ref HasStrongAxles); veh.VehicleFlags4.HasStrongAxles = HasStrongAxles;
                    bool _f4 = veh.VehicleFlags4._f4; ImGuiIV.CheckBox("_f4", ref _f4); veh.VehicleFlags4._f4 = _f4;
                    bool _f5 = veh.VehicleFlags4._f5; ImGuiIV.CheckBox("_f5", ref _f5); veh.VehicleFlags4._f5 = _f5;
                    bool _f6 = veh.VehicleFlags4._f6; ImGuiIV.CheckBox("_f6", ref _f6); veh.VehicleFlags4._f6 = _f6;
                    bool _f7 = veh.VehicleFlags4._f7; ImGuiIV.CheckBox("_f7", ref _f7); veh.VehicleFlags4._f7 = _f7;
                    bool _f8 = veh.VehicleFlags4._f8; ImGuiIV.CheckBox("_f8", ref _f8); veh.VehicleFlags4._f8 = _f8;
                    bool _f9 = veh.VehicleFlags4._f9; ImGuiIV.CheckBox("_f9", ref _f9); veh.VehicleFlags4._f9 = _f9;
                    bool Nitro = veh.VehicleFlags4.Nitro; ImGuiIV.CheckBox("Nitro", ref Nitro); veh.VehicleFlags4.Nitro = Nitro;
                    bool OldCarExhaustFX = veh.VehicleFlags4.OldCarExhaustFX; ImGuiIV.CheckBox("OldCarExhaustFX", ref OldCarExhaustFX); veh.VehicleFlags4.OldCarExhaustFX = OldCarExhaustFX;
                    bool _fc = veh.VehicleFlags4._fc; ImGuiIV.CheckBox("_fc", ref _fc); veh.VehicleFlags4._fc = _fc;
                    bool _fd = veh.VehicleFlags4._fd; ImGuiIV.CheckBox("_fd", ref _fd); veh.VehicleFlags4._fd = _fd;
                    bool _fe = veh.VehicleFlags4._fe; ImGuiIV.CheckBox("_fe", ref _fe); veh.VehicleFlags4._fe = _fe;
                    bool _ff = veh.VehicleFlags4._ff; ImGuiIV.CheckBox("_ff", ref _ff); veh.VehicleFlags4._ff = _ff;
                    bool _f10 = veh.VehicleFlags4._f10; ImGuiIV.CheckBox("_f10", ref _f10); veh.VehicleFlags4._f10 = _f10;
                    bool _f11 = veh.VehicleFlags4._f11; ImGuiIV.CheckBox("_f11", ref _f11); veh.VehicleFlags4._f11 = _f11;
                    bool _f12 = veh.VehicleFlags4._f12; ImGuiIV.CheckBox("_f12", ref _f12); veh.VehicleFlags4._f12 = _f12;
                    bool _f13 = veh.VehicleFlags4._f13; ImGuiIV.CheckBox("_f13", ref _f13); veh.VehicleFlags4._f13 = _f13;
                    bool _f14 = veh.VehicleFlags4._f14; ImGuiIV.CheckBox("_f14", ref _f14); veh.VehicleFlags4._f14 = _f14;
                    bool _f15 = veh.VehicleFlags4._f15; ImGuiIV.CheckBox("_f15", ref _f15); veh.VehicleFlags4._f15 = _f15;
                    bool _f16 = veh.VehicleFlags4._f16; ImGuiIV.CheckBox("_f16", ref _f16); veh.VehicleFlags4._f16 = _f16;
                    bool _f17 = veh.VehicleFlags4._f17; ImGuiIV.CheckBox("_f17", ref _f17); veh.VehicleFlags4._f17 = _f17;
                    bool _f18 = veh.VehicleFlags4._f18; ImGuiIV.CheckBox("_f18", ref _f18); veh.VehicleFlags4._f18 = _f18;
                    bool _f19 = veh.VehicleFlags4._f19; ImGuiIV.CheckBox("_f19", ref _f19); veh.VehicleFlags4._f19 = _f19;
                    bool _f1a = veh.VehicleFlags4._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); veh.VehicleFlags4._f1a = _f1a;
                    bool _f1b = veh.VehicleFlags4._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); veh.VehicleFlags4._f1b = _f1b;
                    bool _f1c = veh.VehicleFlags4._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); veh.VehicleFlags4._f1c = _f1c;
                    bool _f1d = veh.VehicleFlags4._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); veh.VehicleFlags4._f1d = _f1d;
                    bool _f1e = veh.VehicleFlags4._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); veh.VehicleFlags4._f1e = _f1e;
                    bool _f1f = veh.VehicleFlags4._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); veh.VehicleFlags4._f1f = _f1f;

                    ImGuiIV.TreePop();
                }

                ImGuiIV.EndTabItem();
            }
        }
        #endregion

        private void Main_Drawing(object sender, EventArgs e)
        {

        }

        private void CGame_OnWindowFocusChanged(bool focused)
        {
            if (focused)
            {
                IVGame.Console.PrintWarning("IN FOCUS");
            }
            else
            {
                IVGame.Console.PrintError("NOT IN FOCUS");
            }
        }
        private void Main_Initialized(object sender, EventArgs e)
        {
            // 2 ways to register a custom console command for this script
            RegisterConsoleCommand("Test1",                 (string[] args) => { IVGame.Console.PrintWarning("Custom command 'Test1' called!"); });
            IVGame.Console.RegisterCommand(this, "Test2",    (string[] args) => { IVGame.Console.PrintWarning("Custom command 'Test2' called!"); });

            // Read TestScripts settings file (TestScript.ini)
            if (Settings != null)
            {
                IVGame.Console.PrintWarning("bool: "    + Settings.GetBoolean("Section1", "bool", false).ToString());
                IVGame.Console.PrintWarning("int: "     + Settings.GetInteger("Section1", "int", -1).ToString());
                IVGame.Console.PrintWarning("float: "   + Settings.GetFloat("Section1", "float", -1.0f).ToString(CultureInfo.InvariantCulture));
                IVGame.Console.PrintWarning("quat: "    + Settings.GetQuaternion("Section1", "quat", Quaternion.Identity).ToString());
                IVGame.Console.PrintWarning("vec2: " + Settings.GetVector2("Section1", "vec2", Vector2.Zero).ToString());
                IVGame.Console.PrintWarning("vec3: " + Settings.GetVector3("Section1", "vec3", Vector3.Zero).ToString());
                IVGame.Console.PrintWarning("vec4: " + Settings.GetVector4("Section1", "vec4", Vector4.Zero).ToString());
                IVGame.Console.PrintWarning("color: " + Settings.GetColor("Section1", "color", Color.FromArgb(0, 0, 0, 0)).ToString());
                IVGame.Console.PrintWarning("key: " + Settings.GetKey("Section1", "key", Keys.None).ToString());

                // Add a new section to the ini
                if (Settings.AddSection("TEST_SECTION"))
                    // Section got added
                {

                    Settings.InsertAt(0, "; hello"); // Add "hello" comment at the beginning of the file

                    Settings.AddKeyToSection("TEST_SECTION", "New_Key"); // Add key to added section

                    Settings.InsertAt(Settings.GetTotalLineCount(), "; bye"); // Add "bye" comment at the end of the file

                    Settings.Save(); // Save changes

                }

                IVGame.Console.PrintWarning(string.Format("There are {0} total lines in the ini file.", Settings.GetTotalLineCount()));
                IVGame.Console.PrintWarning(Settings.ToString());
            }
        }
        private void Main_Uninitialize(object sender, EventArgs e)
        {

        }

        private void Main_OnFirstD3D9Frame(object sender, EventArgs e)
        {
            // Try create image
            if (ImGuiIV.CreateTextureFromMemory(this, Properties.Resources.discordTestLogo, out IntPtr ptr, out int imageWidth, out int imageHeight))
            {
                discordImagePtr = ptr;
                width = imageWidth;
                height = imageHeight;
            }

            // Draw ImGui stuff
            ImGuiIV.AddDrawCommand(this, () =>
            {
                ImGuiTest();

                if (MainMenuOpen)
                    MainMenu();

                if (!EnableTestImGuiDraw)
                    return;

                // Drawing test
                if (ImGuiIV.BeginCanvas(this, out ImGuiIV_DrawingContext ctx))
                {

                    ctx.AddLine(new Vector2(0f, 0f), new Vector2(800f, 800f), Color.Red, 1f);
                    ctx.AddRectFilled(new Vector2(20f, 20f), new Vector2(40f, 40f), Color.Blue, 0f, eImDrawFlags.None);
                    ctx.AddImageRotated(discordImagePtr, new RectangleF(new PointF(10f, 10f), new SizeF(width, height)), rotation, Color.White);
                    ctx.AddText(new Vector2(500f, 200f), Color.Red, "Hello World!");

                    ImGuiIV.EndCanvas();
                }
            });
        }

        private void RAGE_OnWndProcMessageReceived(IntPtr hWnd, uint msg, UIntPtr wParam, IntPtr lParam)
        {
            // Received a windows message
        }

        // Runs every frame when in-game
        private void Main_WaitTick(object sender, EventArgs e)
        {
            IVGame.Console.Print("Tick from WaitTick event!");
        }
        private void Main_Tick(object sender, EventArgs e)
        {
            // The IV-SDK .NET method on how to get the player char and the char coordinates and heading
            IVPed playerPedNEW = IVPed.FromUIntPtr(IVPlayerInfo.FindThePlayerPed());

            if (playerPedNEW.WeaponData.WeaponObject != null)
            {
                //ShowSubtitleMessage("ok");
                //NativeCheckpoint.DrawCheckpoint(playerPedNEW.WeaponData.WeaponObject.Matrix.pos, 1f, Color.Red);
            }

            Vector3 playerPosNEW = playerPedNEW.Matrix.Pos;
            heading = playerPedNEW.CurrentHeading;

            // Spawn vehicle at player position test
            // TODO: Change to not use CCL.GTAIV!
            if (IsKeyPressed(Keys.N))
            {
                // Not good if you accidentaly press it
                //IVMatrix mat = IVPed.FromUIntPtr(IVPlayerInfo.FindThePlayerPed()).Matrix;
                //CCL.GTAIV.NativeWorld.SpawnVehicle("police2", mat.Pos, out int vehHandle);
            }

            IVVehicle veh = IVVehicle.FromUIntPtr(playerPedNEW.GetVehicle());
            if (veh != null)
            {
                int vehicleHandle = (int)IVPools.GetVehiclePool().GetIndex(veh.GetUIntPtr());

                if (IsKeyPressed(Keys.Right))
                {
                    veh.VehicleFlags3.RightIndicator = !veh.VehicleFlags3.RightIndicator;
                }

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
            IVHandlingData handlingData = IVHandlingDataMgr.GetHandlingData(IVHandlingDataMgr.GetHandlingId("BANSHEE")); // Get handling of the BANSHEE
            //ShowSubtitleMessage(string.Format("Name: {0}, HalogenLights: {1}", handlingData.Name, handlingData.TheHandlingFlags.HalogenLights.ToString()));

            // CPlayerInfo test
            IVPlayerInfo playerInfo = IVPlayerInfo.GetPlayerInfo(GET_PLAYER_ID());
            //ShowSubtitleMessage(string.Format("PID: {0}, Name: {1}, LastRanLightTime: {2}, PlayerPed: {3}, PlayerPed2: {4}", playerInfo.PlayerId.ToString(), playerInfo.Name, playerInfo.LastRanLightTime.ToString(), playerInfo.PlayerPed != UIntPtr.Zero, playerInfo.PlayerPed2 != UIntPtr.Zero));

            // CWeaponInfo test
            IVWeaponInfo weaponInfo = IVWeaponInfo.GetWeaponInfo((uint)eWeaponType.WEAPON_MP5);
            //ShowSubtitleMessage(string.Format("WeaponType: {0}, Silenced: {1}", (eWeaponType)weaponInfo.WeaponType, weaponInfo.TheWeaponFlags.Silenced.ToString()));

            // CDraw test
            IVDraw draw = IVDraw.TheScene;
            if (draw != null)
            {
                //draw.ForceHudWidescreen = 0;
                //ShowSubtitleMessage(string.Format("AspectRatio: {0}, ForceHudWidescreen: {1}", draw.CalculateAspectRatio(true).ToString(), draw.ForceHudWidescreen.ToString()));

                IVGlobalScene globalScene = IVGlobalScene.FromUIntPtr(draw.GlobalScene);

                IVViewportGame viewportGame = globalScene.GameViewport;
                if (viewportGame != null)
                {
                    IVViewportData viewportData = viewportGame.Data;
                    RectangleF rect = viewportData.Rect;
                    //ShowSubtitleMessage(string.Format("Rect: {0}, Resolution: {1}, Scale: {2}", rect.ToString(), viewportData.Resolution.ToString(), viewportData.Scale.ToString()));
                }
            }

            // CPad test
            IVPad pad = IVPad.GetPad();
            if (pad != null)
            {
                //ShowSubtitleMessage(string.Format("IsUsingKeyboardForAim: {0}, IsUsingKeyboardForHeli: {1}, LastUpdateTime: {2}", pad.IsUsingKeyboardForAim.ToString(), pad.IsUsingKeyboardForHeli.ToString(), pad.LastUpdateTime.ToString()));
            }


            // - - - Add armor to cop peds but only once - - -

            // Get the current basic cop model (There should always be a cop model in memory to use)
            GET_CURRENT_BASIC_COP_MODEL(out uint currentCopModel);

            // Loop through all peds in the world
            IVPool pedPool = IVPools.GetPedPool();

            for (int i = 0; i < pedPool.Count; i++)
            {
                UIntPtr pedPtr = pedPool.Get(i);

                if (pedPtr != UIntPtr.Zero)
                {
                    // Ignore player ped
                    if (pedPtr == IVPlayerInfo.FindThePlayerPed())
                        continue; // continue means we continue with the next item in the for loop and skip everything that would come after the continue

                    // Get the handle of the ped
                    int pedHandle = (int)pedPool.GetIndex(pedPtr);

                    // Check if this ped already got armor
                    if (pedsWhichGotArmor.Contains(pedHandle))
                        continue;

                    // Check if ped is dead
                    if (IS_CHAR_DEAD(pedHandle))
                        continue;

                    // Check if this ped is a mission ped (Maybe not skip this ped if it's a mission ped idk)
                    if (IS_PED_A_MISSION_PED(pedHandle))
                        continue;

                    // Get the current model of the ped
                    GET_CHAR_MODEL(pedHandle, out uint pedModel);

                    // Check if ped model is a cop model
                    if (pedModel != currentCopModel)
                        continue;

                    // Ped is a cop so we can increase their armor and add them to the list of peds that got armor
                    ADD_ARMOUR_TO_CHAR(pedHandle, 100);
                    pedsWhichGotArmor.Add(pedHandle);
                }
            }

            // Loop through the list of peds that already got armor and check if we can delete them from the list
            for (int i = 0; i < pedsWhichGotArmor.Count; i++)
            {
                int pedHandle = pedsWhichGotArmor[i];

                // Check if ped still exists
                if (!DOES_CHAR_EXIST(pedHandle))
                    pedsWhichGotArmor.RemoveAt(i); // Remove ped from list because they dont exists anymore
            }

            // Manual Native Caller Test
            //ShowSubtitleMessage(IVSDKDotNet.Native.Function.Call<string>("GET_PLAYER_NAME", 0));

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
            IVVehicle veh = IVVehicle.FromUIntPtr(vehPtr);

            if (veh != null)
            {
                //veh.Alpha = 180; // Sets the alpha property of each vehicle in the world to 180.

                UIntPtr[] pass = veh.Passengers;

                if (pass == null)
                    return;

                if (pass[0] != UIntPtr.Zero) // Front Left
                {
                    IVPed passFL = IVPed.FromUIntPtr(pass[0]);
                    Vector3 pos = passFL.Matrix.Pos;
                    DRAW_CHECKPOINT(pos, 1f, Color.Red);
                }
                if (pass[1] != UIntPtr.Zero) // Back Right
                {
                    IVPed passBR = IVPed.FromUIntPtr(pass[1]);
                    Vector3 pos = passBR.Matrix.Pos;
                    DRAW_CHECKPOINT(pos, 1f, Color.Green);
                }
                if (pass[2] != UIntPtr.Zero) // Back Left
                {
                    IVPed passBL = IVPed.FromUIntPtr(pass[2]);
                    Vector3 pos = passBL.Matrix.Pos;
                    DRAW_CHECKPOINT(pos, 1f, Color.Blue);
                }
            }
        }
        private void Main_ProcessCamera(object sender, EventArgs e)
        {
            IVCam c = IVCamera.TheFinalCam;

            //if (IsKeyPressed(Keys.Add))
            //    fov += 0.5f; // Zooms out
            //if (IsKeyPressed(Keys.Subtract))
            //    fov -= 0.5f; // Zooms in

            if (c != null)
            {
                //c.FOV = fov;

                // Add an offset to the camera
                c.Matrix.Add(CamOffsetRight, CamOffsetUp, CamOffsetAt, CamOffsetPos);
            }
        }

        // When this script receives a script command
        private object Main_ScriptCommandReceived(Script fromScript, string command)
        {
            IVGame.Console.PrintWarning(string.Format("Received a script command from script {0}. Command: {1}", fromScript.GetName(), command));
            return "I received the command!";
        }

        private void Main_KeyDown(object sender, KeyEventArgs e)
        {
            // Creates an explosion infront of the player
            if (e.KeyCode == Keys.NumPad9)
            {

                //UNPAUSE_GAME();

                // Get player coordinates
                GET_CHAR_COORDINATES(playerPed, out Vector3 pos);

                // Get player heading
                GET_CHAR_HEADING(playerPed, out float heading);

                // Get position infront of player
                Vector3 v = Helper.GetPositionInFrontOfEntity(pos, Helper.HeadingToDirection(heading), 12f);

                // Create explosion
                ADD_EXPLOSION(v.X, v.Y, v.Z, (int)eExplosionType.EXPLOSION_TYPE_ROCKET, 10f, true, false, 0.5f);

            }

            if (e.KeyCode == Keys.B)
            {
                // Load model
                uint modelHash = RAGE.AtStringHash("nj04ladder04");
                //IVModelInfo.GetModelInfo(modelHash, out int index);
                IVStreaming.ScriptRequestModel((int)modelHash);
                IVStreaming.LoadAllRequestedModels(false);

                // Spawn ladder at pos
                CREATE_OBJECT((int)modelHash, new Vector3(-543.246f, 1430.262f, 13.5f), out ladderObject, false);
                SET_OBJECT_HEADING(ladderObject, 0.08588995f);
                SET_OBJECT_ROTATION(ladderObject, -10f, 0f, 0f);

                //IVObject o = IVObject.FromUIntPtr(IVPools.GetObjectPool().GetAt((uint)obj));
                //o.
            }
            if (e.KeyCode == Keys.N)
            {
                if (ladderObject != 0)
                    DELETE_OBJECT(ref ladderObject);
            }

            if (e.KeyCode == Keys.U)
            {
                // IV-SDK Task test
                int playerHandle = (int)IVPools.GetPedPool().GetIndex(IVPlayerInfo.FindThePlayerPed());

                //UIntPtr task = CTaskComplexDie.Create(0, 0, 44, 190, 4.0f, 0.0f, 1);
                //UIntPtr task = CTaskComplexWanderStandard.Create(2, 0f, true, 2.5f, 1);
                //CTheScripts.GivePedScriptedTask(playerHandle, task, 5);

                // The KeyUp and KeyDown events will now get raised from the ProcessPad event which does NOT use the CTheScripts.SetDummyThread(); and CTheScripts.RestorePreviousThread(); method!
                // SO SIMPLY DOING THIS NO LONGER WORKS IN IV-SDK.NET v0.8 AND UP:
                //_TASK_FALL_AND_GET_UP(playerHandle, 1, 1);

                // To get native tasks to work in the KeyUp and KeyDown events you will have to do this:
                IVTheScripts.SetDummyThread();
                _TASK_FALL_AND_GET_UP(playerHandle, 1, 1);
                IVTheScripts.RestorePreviousThread();

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

            if (e.KeyCode == Keys.NumPad4)
            {
                // Opens the ImGui test window
                // ImGuiTestOpen = true;
            }
            if (e.KeyCode == Keys.NumPad6)
            {
                if (ladderObject != 0)
                {
                    //IVTheScripts.SetDummyThread();

                    IVTask task = IVTaskComplexClimbLadder.Create(IVObject.FromUIntPtr(IVPools.GetObjectPool().GetAt((uint)ladderObject)), 0, 1);
                    IVTheScripts.GivePedScriptedTask((int)IVPools.GetPedPool().GetIndex(IVPlayerInfo.FindThePlayerPed()), task, 0);

                    //_TASK_CLIMB_LADDER((int)IVPools.GetPedPool().GetIndex(IVPlayerInfo.FindThePlayerPed()), ladderObject);
                    //IVTheScripts.RestorePreviousThread();
                }
            }

            // Test send script command to this script and get result
            //if (e.KeyCode == Keys.K)
            //{
            //    SendScriptCommand(this, "TEST_COMMAND!", out object result);
            //    CGame.Console.PrintWarning(string.Format("Result Type: {0}, Value: {1}", result.GetType().Name, result.ToString()));
            //}

        }

    }
}
