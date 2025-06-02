using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.IO.Compression;
using System.IO;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Linq;
using System.Reflection;

using System.Speech.Synthesis;

using CCL.GTAIV;
using CCL.GTAIV.Extensions;

using IVSDKDotNet;
using IVSDKDotNet.Attributes;
using IVSDKDotNet.Enums;
using IVSDKDotNet.Hooking;
using static IVSDKDotNet.Native.Natives;

namespace TestScript
{
    public class Main : Script
    {

        internal static Main Instance;

        public Queue<Action> MainThreadQueue = new Queue<Action>();

        private Vector3 CamOffsetUp;
        private Vector3 CamOffsetRight;
        private Vector3 CamOffsetPos;
        private Vector3 CamOffsetAt;

        public Vector3 CameraLightOffset = new Vector3(0.200f, -0.570f, 0.115f);

        public Vector3 CCTVCameraLightOffset = new Vector3(0.500f, 0.300f, 2.700f);
        public Vector3 CCTVCameraLightOffset2 = new Vector3(0.100f, 1.300f, 2.700f);
        public Vector3 CCTVCameraLightOffset3 = new Vector3(-0.600f, 0.800f, 2.700f);

        public Vector3 explosionPos;
        public int explosionType;

        [Speed(0.01f)]
        [Range(-1f, 1f)]
        public float explosionRange;

        private int checkPointId;

        private ImGuiIV_HexEditorState hexEditorState;

        #region Variables
        private int playerPed;
        public Vector3 playerPos;
        private float heading;

        [Separator("Text")]
        [HelpMarker("This is a test string!")]
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
        public bool MainMenuOpen = false;
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
        #endregion

        // Works!
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void CGame_showLoadscreenDelegate(
            [MarshalAs(UnmanagedType.I1)] bool a1,
            [MarshalAs(UnmanagedType.I1)] bool a2,
            [MarshalAs(UnmanagedType.I1)] bool a3);

        public CGame_showLoadscreenDelegate hookedShowLoadscreenFunc;
        public CGame_showLoadscreenDelegate originalShowLoadscreenFunc;
        public void CGame_showLoadscreenHook(bool a1, bool a2, bool a3)
        {
            IVGame.Console.PrintWarningEx("CGame_showLoadscreen - a1: {0}, a2: {1}, a3: {2}", a1, a2, a3);
            originalShowLoadscreenFunc(a1, a2, a3);
        }


        [UnmanagedFunctionPointer(CallingConvention.ThisCall)]
        public unsafe delegate bool CEpisodes_IsEpisodeAvailableDelegate(void* pThis, int episodeId);
        public CEpisodes_IsEpisodeAvailableDelegate hookedIsEpisodeAvailableFunc;
        public CEpisodes_IsEpisodeAvailableDelegate originalIsEpisodeAvailableFunc;
        public unsafe bool IsEpisodeAvailableHook(void* pThis, int episodeId)
        {
            return true;
        }

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public unsafe delegate bool ShowMessageDelegate([MarshalAs(UnmanagedType.LPStr)] string msg, char a2, int a3);
        public ShowMessageDelegate hookedShowMessageFunc;
        public ShowMessageDelegate originalShowMessageFunc;
        public unsafe bool HookedShowMessage(string msg, char a2, int a3)
        {
            IVGame.Console.PrintWarningEx("showing message: {0}", msg);

            if (msg == "FE_NODLC2")
                return false;

            return originalShowMessageFunc(msg, a2, a3);
        }


        [UnmanagedFunctionPointer(CallingConvention.ThisCall)]
        public unsafe delegate bool audSpeechAudioEntity_playSpeechDelegate(
            void* pThis,
            [MarshalAs(UnmanagedType.LPStr)] string speechGXT,
            [MarshalAs(UnmanagedType.I1)] bool a3,
            [MarshalAs(UnmanagedType.I1)] bool a4,
            [MarshalAs(UnmanagedType.U4)] uint a5,
            [MarshalAs(UnmanagedType.I4)] int a6,
            void* pEntity,
            [MarshalAs(UnmanagedType.U4)] uint a8,
            [MarshalAs(UnmanagedType.R4)] float a9,
            [MarshalAs(UnmanagedType.U4)] uint a10,
            [MarshalAs(UnmanagedType.I4)] int a11);

        [UnmanagedFunctionPointer(CallingConvention.ThisCall)]
        public unsafe delegate bool CWeaponData_fireSingleBullet(
            void* pThis,
            [MarshalAs(UnmanagedType.I4)] int pShooterPed,
            [MarshalAs(UnmanagedType.I4)] int a3,
            [MarshalAs(UnmanagedType.I4)] int a4,
            [MarshalAs(UnmanagedType.I4)] int a5,
            [MarshalAs(UnmanagedType.I1)] bool a6,
            [MarshalAs(UnmanagedType.I4)] int a7,
            [MarshalAs(UnmanagedType.I4)] int a8,
            [MarshalAs(UnmanagedType.R4)] float a9,
            [MarshalAs(UnmanagedType.R4)] float a10);


        [UnmanagedFunctionPointer(CallingConvention.ThisCall)]
        public unsafe delegate int CreateGunshotEventDelegate(
            void* pThis,
            void* pEntity,
            [MarshalAs(UnmanagedType.I4)] int a1,
            [MarshalAs(UnmanagedType.I4)] int a2,
            [MarshalAs(UnmanagedType.I4)] int a3);

        public static CreateGunshotEventDelegate hookedGunshotEventFunc;
        public static CreateGunshotEventDelegate originalGunshotEventFunc;
        public static unsafe int CreateGunshotEventHook(
            void* pThis,
            void* pEntity,
            int a1,
            int a2,
            int a3)
        {
            UIntPtr ent = new UIntPtr(pEntity);

            if (ent == IVPlayerInfo.FindThePlayerPed()) // This successfully makes peds deaf! Now i just need to change the sound of the gun...
                return 0;

            return originalGunshotEventFunc(pThis, pEntity, a1, a2, a3);
        }


        public static audSpeechAudioEntity_playSpeechDelegate hookedFunc;
        public static audSpeechAudioEntity_playSpeechDelegate originalFunc;
        public static unsafe bool playSpeechHook(
            void* pThis,
            string speechGXT,
            bool a3,
            bool a4,
            uint a5,
            int a6,
            void* pEntity,
            uint a8,
            float a9,
            uint a10,
            int a11)
        {
            //UIntPtr ent = new UIntPtr(pEntity);

            //if (ent != UIntPtr.Zero)
            //{
            //    Logger.LogWarning("ent was not null! this means that some ped said something to the other!");
            //    Logger.LogWarningEx("ent ptr: {0} (is player: {1})", ent.ToUInt32().ToString("X"), ent == IVPlayerInfo.FindThePlayerPed());
            //}

            //Logger.LogWarningEx("played {0} from entity {1} (is player ped: {2})!", speechGXT, ent.ToUInt32().ToString("X"), ent == IVPlayerInfo.FindThePlayerPed());

            // This is awesome! We can detect who spoke, and who this ped spoke to! Immersive speech mod incoming?
            UIntPtr speaker = new UIntPtr((uint)(pThis) - 1408);
            UIntPtr spokeTo = new UIntPtr(pEntity);

            if (speaker == IVPlayerInfo.FindThePlayerPed() && speechGXT == "GENERIC_INSULT")
            {
                if (spokeTo != UIntPtr.Zero)
                {
                    IVPed spokeToPed = IVPed.FromUIntPtr(spokeTo);

                    GET_CURRENT_BASIC_COP_MODEL(out uint m);
                    if (spokeToPed.GetCharModel() == m)
                    {
                        spokeToPed.SayAmbientSpeech("INTIMIDATE");
                        ALTER_WANTED_LEVEL(0, 1);
                        //APPLY_WANTED_LEVEL_CHANGE_NOW(0);
                    }
                }
            }

            return originalFunc(pThis, speechGXT, a3, a4, a5, a6, pEntity, a8, a9, a10, a11);
        }


        public static CWeaponData_fireSingleBullet hookedFireFunc;
        public static CWeaponData_fireSingleBullet originalFireFunc;
        public static unsafe bool fireSingleBulletHook(
            void* pThis,
            int pShooterPed,
            int a3,
            int a4,
            int a5,
            bool a6,
            int a7,
            int a8,
            float a9,
            float a10)
        {
            return originalFireFunc(pThis, pShooterPed, a3, a4, a5, a6, a7, a8, a9, a10);
        }

        // Maybe this loads a sound? - This crashes the game
        //[UnmanagedFunctionPointer(CallingConvention.StdCall)]
        //public unsafe delegate bool MaybeLoadSoundDelegate(
        //    [MarshalAs(UnmanagedType.I4)] int soundName,
        //    int* a2,
        //    [MarshalAs(UnmanagedType.I4)] int a3,
        //    [MarshalAs(UnmanagedType.I4)] int a4,
        //    [MarshalAs(UnmanagedType.I4)] int a5);
        //public static MaybeLoadSoundDelegate hookedLoadSoundFunc;
        //public static MaybeLoadSoundDelegate originalLoadSoundFunc;

        //public static unsafe bool MaybeLoadSoundHook(int soundName, int* a2, int a3, int a4, int a5)
        //{
        //    Logger.LogEx("MaybeLoadSoundHook. soundName: {0}", soundName);
        //    return originalLoadSoundFunc(soundName, a2, a3, a4, a5);
        //}

        // Play sound probably
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public unsafe delegate int MaybePlaySoundDelegate(
            [MarshalAs(UnmanagedType.U4)] uint soundHash,
            [MarshalAs(UnmanagedType.I1)] bool a2,
            [MarshalAs(UnmanagedType.I1)] bool a3,
            [MarshalAs(UnmanagedType.I1)] bool a4,
            [MarshalAs(UnmanagedType.I4)] int a5,
            [MarshalAs(UnmanagedType.I4)] int a6,
            [MarshalAs(UnmanagedType.I4)] int a7,
            [MarshalAs(UnmanagedType.I4)] int a8);
        public static MaybePlaySoundDelegate hookedMaybePlaySoundFunc;
        public static MaybePlaySoundDelegate originalMaybePlaySoundFunc;

        public static unsafe int MaybePlaySoundFunc(uint soundHash, bool a2, bool a3, bool a4, int a5, int a6, int a7, int a8)
        {
            //if (soundHash == HashStringLowercaseFromSeed("PISTOL_SHOT", 0))
            //{
            //    Logger.Log("hash is PISTOL_SHOT");
            //}

            //Logger.LogEx("MaybePlaySoundFunc. soundHash: {0} ({1})", soundHash, soundHash.ToString("X"));

            return originalMaybePlaySoundFunc(soundHash, a2, a3, a4, a5, a6, a7, a8);
        }

        [UnmanagedFunctionPointer(CallingConvention.ThisCall)]
        public unsafe delegate int CTaskSimpleRunNamedAnim_ctor_delegate(
            void* pThis,
            [MarshalAs(UnmanagedType.LPStr)] string a2,
            [MarshalAs(UnmanagedType.LPStr)] string a3,
            int a4,
            int a5,
            int a6,
            int a7,
            bool a8,
            bool a9,
            bool a10,
            int a11,
            bool a12,
            bool a13,
            int a14);
        public static CTaskSimpleRunNamedAnim_ctor_delegate hookedRunNamedAnimFunc;
        public static CTaskSimpleRunNamedAnim_ctor_delegate originalRunNamedAnimFunc;

        public static unsafe int HookedRunNamedAnim(
            void* pThis,
            string a2,
            string a3,
            int a4,
            int a5,
            int a6,
            int a7,
            bool a8,
            bool a9,
            bool a10,
            int a11,
            bool a12,
            bool a13,
            int a14)
        {
            Logger.LogWarningEx("a2: {0}, a3: {1}", a2, a3);
            return originalRunNamedAnimFunc(pThis, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
        }

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public unsafe delegate void AssignScriptCommandToPedDelegate(int handle, void* task, int id);
        public static AssignScriptCommandToPedDelegate hookedAssignFunc;
        public static AssignScriptCommandToPedDelegate originalAssignFunc;
        public static unsafe void HookedAssignScriptCommandToPed(int handle, void* task, int id)
        {
            Logger.LogWarningEx("Task: {0}", (eTask)id);
            originalAssignFunc(handle, task, id);
        }




        #region Constructor
        public Main()
        {
            Instance = this;

            // AssignScriptCommandToPed
            //unsafe
            //{
            //    IntPtr originalFuncPtr;

            //    hookedAssignFunc = new AssignScriptCommandToPedDelegate(HookedAssignScriptCommandToPed);

            //    Logger.LogWarningEx("CreateHook result: {0}", ManagedMinHook.CreateHook(MemoryAccess.BaseAddress + 0x4B0DF0, hookedAssignFunc, out originalFuncPtr));

            //    originalAssignFunc = Marshal.GetDelegateForFunctionPointer<AssignScriptCommandToPedDelegate>(originalFuncPtr);

            //    Logger.LogWarningEx("EnableHook result: {0}", ManagedMinHook.EnableHook(MemoryAccess.BaseAddress + 0x4B0DF0));
            //}

            // run named anim
            //unsafe
            //{
            //    IntPtr originalFuncPtr;

            //    hookedRunNamedAnimFunc = new CTaskSimpleRunNamedAnim_ctor_delegate(HookedRunNamedAnim);

            //    Logger.LogWarningEx("CreateHook result: {0}", ManagedMinHook.CreateHook(MemoryAccess.BaseAddress + 0x889B60, hookedRunNamedAnimFunc, out originalFuncPtr));

            //    originalRunNamedAnimFunc = Marshal.GetDelegateForFunctionPointer<CTaskSimpleRunNamedAnim_ctor_delegate>(originalFuncPtr);

            //    Logger.LogWarningEx("EnableHook result: {0}", ManagedMinHook.EnableHook(MemoryAccess.BaseAddress + 0x889B60));
            //}

            unsafe
            {
                IntPtr originalFuncPtr;
                hookedFunc = new audSpeechAudioEntity_playSpeechDelegate(playSpeechHook);
                ManagedMinHook.CreateHook(MemoryAccess.BaseAddress + 0x438AD0, hookedFunc, out originalFuncPtr);
                originalFunc = Marshal.GetDelegateForFunctionPointer<audSpeechAudioEntity_playSpeechDelegate>(originalFuncPtr);

                //Delegate d = hookedFunc;
                //Logger.LogEx("Name: {0}", d.Method.Name);
                //Logger.LogEx("ReturnType: {0}", d.Method.ReturnType.FullName);
                //ParameterInfo[] ps = d.Method.GetParameters();
                //for (int i = 0; i < ps.Length; i++)
                //{
                //    ParameterInfo p = ps[i];
                //    Logger.LogEx("Param {0}: {1}", i, p.ParameterType.FullName);
                //}


                ManagedMinHook.EnableHook(MemoryAccess.BaseAddress + 0x438AD0);
            }

            // fireSingleBulletHook
            //unsafe
            //{
            //    IntPtr originalFuncPtr;
            //    hookedFireFunc = new CWeaponData_fireSingleBullet(fireSingleBulletHook);
            //    Logger.LogWarningEx("CreateHook result: {0}", ManagedMinHook.CreateHook(MemoryAccess.BaseAddress + 0x5D5D50, hookedFireFunc, out originalFuncPtr));
            //    originalFireFunc = Marshal.GetDelegateForFunctionPointer<CWeaponData_fireSingleBullet>(originalFuncPtr);

            //    Logger.LogWarningEx("EnableHook result: {0}", ManagedMinHook.EnableHook(MemoryAccess.BaseAddress + 0x5D5D50));
            //}

            // This might load a sound - crashes the game
            //unsafe
            //{
            //    IntPtr originalFuncPtr;
            //    hookedLoadSoundFunc = new MaybeLoadSoundDelegate(MaybeLoadSoundHook);
            //    Logger.LogWarningEx("CreateHook result: {0}", ManagedMinHook.CreateHook(MemoryAccess.BaseAddress + 0x93AFC0, hookedLoadSoundFunc, out originalFuncPtr));
            //    originalLoadSoundFunc = Marshal.GetDelegateForFunctionPointer<MaybeLoadSoundDelegate>(originalFuncPtr);

            //    Logger.LogWarningEx("EnableHook MaybeLoadSoundHook result: {0}", ManagedMinHook.EnableHook(MemoryAccess.BaseAddress + 0x93AFC0));
            //}

            // Deffo something for playing a sound
            //unsafe
            //{
            //    IntPtr originalFuncPtr;
            //    hookedMaybePlaySoundFunc = new MaybePlaySoundDelegate(MaybePlaySoundFunc);
            //    Logger.LogWarningEx("CreateHook result: {0}", ManagedMinHook.CreateHook(MemoryAccess.BaseAddress + 0x3EB850, hookedMaybePlaySoundFunc, out originalFuncPtr));
            //    originalMaybePlaySoundFunc = Marshal.GetDelegateForFunctionPointer<MaybePlaySoundDelegate>(originalFuncPtr);

            //    Logger.LogWarningEx("EnableHook result: {0}", ManagedMinHook.EnableHook(MemoryAccess.BaseAddress + 0x3EB850));
            //}

            // CreateGunshotEventHook - can be used to make peds no longer react to gunshots
            //unsafe
            //{
            //    IntPtr originalFuncPtr;
            //    hookedGunshotEventFunc = new CreateGunshotEventDelegate(CreateGunshotEventHook);
            //    Logger.LogWarningEx("CreateHook result: {0}", ManagedMinHook.CreateHook(MemoryAccess.BaseAddress + 0x5D0B80, hookedGunshotEventFunc, out originalFuncPtr));
            //    originalGunshotEventFunc = Marshal.GetDelegateForFunctionPointer<CreateGunshotEventDelegate>(originalFuncPtr);

            //    Logger.LogWarningEx("EnableHook result: {0}", ManagedMinHook.EnableHook(MemoryAccess.BaseAddress + 0x5D0B80));
            //}



            {
                // Hook CGame::ShowLoadscreen
                IntPtr originalPtr;
                hookedShowLoadscreenFunc = new CGame_showLoadscreenDelegate(CGame_showLoadscreenHook);
                ManagedMinHook.CreateHook(MemoryAccess.BaseAddress + 0xA2CB0, hookedShowLoadscreenFunc, out originalPtr);
                originalShowLoadscreenFunc = Marshal.GetDelegateForFunctionPointer<CGame_showLoadscreenDelegate>(originalPtr);
                ManagedMinHook.EnableHook(MemoryAccess.BaseAddress + 0xA2CB0);
            }

            unsafe
            {
                // Hook CEpisode::IsEpisodeAvailable
                IntPtr originalPtr;
                hookedIsEpisodeAvailableFunc = new CEpisodes_IsEpisodeAvailableDelegate(IsEpisodeAvailableHook);
                ManagedMinHook.CreateHook(MemoryAccess.BaseAddress + 0x490970, hookedIsEpisodeAvailableFunc, out originalPtr);
                originalIsEpisodeAvailableFunc = Marshal.GetDelegateForFunctionPointer<CEpisodes_IsEpisodeAvailableDelegate>(originalPtr);
                ManagedMinHook.EnableHook(MemoryAccess.BaseAddress + 0x490970);
            }

            unsafe
            {
                // Hook ShowMessage
                IntPtr originalPtr;
                hookedShowMessageFunc = new ShowMessageDelegate(HookedShowMessage);
                ManagedMinHook.CreateHook(MemoryAccess.BaseAddress + 0x469160, hookedShowMessageFunc, out originalPtr);
                originalShowMessageFunc = Marshal.GetDelegateForFunctionPointer<ShowMessageDelegate>(originalPtr);
                ManagedMinHook.EnableHook(MemoryAccess.BaseAddress + 0x469160);
            }




            OnlyRaiseKeyEventsWhenInGame = true;

            TheDelayedCaller = new DelayedCalling();

            // Subscribe to script events
            Initialized += Main_Initialized;
            Uninitialize += Main_Uninitialize;

            Tick += Main_Tick;
            KeyDown += Main_KeyDown;
            ProcessPad += Main_ProcessPad;
            ProcessAutomobile += Main_ProcessAutomobile;
            ProcessCamera += Main_ProcessCamera;
            ScriptCommandReceived += Main_ScriptCommandReceived;
            OnFirstD3D9Frame += Main_OnFirstD3D9Frame;
            GameLoad += Main_GameLoad;
            GameLoadPriority += Main_GameLoadPriority;

            IngameStartup += Main_IngameStartup;

            // Runs every 3 seconds (3000 milliseconds = 3 seconds)
            WaitTick += Main_WaitTick;
            WaitTickInterval = 3000;

            OnImGuiRendering += Main_OnImGuiRendering;

            RAGE.OnWindowFocusChanged += CGame_OnWindowFocusChanged;
            RAGE.OnWndProcMessageReceived += RAGE_OnWndProcMessageReceived;

            GameHooks.OnIsNetworkGameRunning += GameHooks_OnIsNetworkGameRunning;
            //GameHooks.OnIsThisMachineTheServer += GameHooks_OnIsThisMachineTheServer;
            GameHooks.OnDoPickupGlow += GameHooks_OnDoPickupGlow;
        }

        private void Main_GameLoad(object sender, EventArgs e)
        {
            IVGame.Console.Print("GameLoad called!");
        }
        private void Main_GameLoadPriority(object sender, EventArgs e)
        {
            IVGame.Console.Print("GameLoadPriority called!");
        }

        private HookCallback<int> GameHooks_OnDoPickupGlow()
        {
            return new HookCallback<int>(disablePickupGlow);
        }

        private void Main_IngameStartup(object sender, EventArgs e)
        {
            IVGame.Console.Print("IngameStartup called!");
        }

        public bool isNetworkSession = false;
        private HookCallback<bool> GameHooks_OnIsNetworkGameRunning()
        {
            return new HookCallback<bool>(true, isNetworkSession);
        }
        //private HookCallback<bool> GameHooks_OnIsThisMachineTheServer()
        //{
        //    return new HookCallback<bool>(true, !isNetworkSession);
        //}
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
        private float Lerp(float a, float b, float t)
        {
            // Clamp t between 0 and 1
            t = Math.Max(0.0f, Math.Min(1.0f, t));

            return a + (b - a) * t;
        }
        #endregion

        private List<int> scriptFire = new List<int>();

        private int objH;

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

        private int index;
        private int offset = 5;
        private bool vp;
        private string soundNameInput;
        private List<string> soundNames = new List<string>();
        private int selectedMissionCompleteAudioIndex;

        // Pickup
        private float tempPickupBlipsRange = 50f;
        private int tempPickupBlipsType;
        private bool createBlipForPickup;
        private string pickupModel = "amb_pickaxe";
        private int handleOfLastCreatedPickup = -1;
        private Vector3 pickupRotation;
        private int pickupType;
        private int selectedPickupIndexToCreateTempBlipFor;

        // ImgFiles

        private float spinnerRadius = 1f;
        private int spinnerBars = 5;
        private float knobValue;
        private void MainMenu(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
        {
            if (!MainMenuOpen)
                return;

            ImGuiIV.Begin("Script Test Window", ref MainMenuOpen, eImGuiWindowFlags.None);

            if (ImGuiIV.Button("launch in test network session"))
            {
                MainThreadQueue.Enqueue(() =>
                {

                    //IVGame.Idk(0, 0, 0, 1);
                });
            }


            //unsafe
            //{
            //// Change the RadPerDeg value which could mess up the game!
            //    float v = *(float*)(MemoryAccess.BaseAddress + 0xCDF4EC);
            //    ImGuiIV.DragFloat("radtodeg", ref v);
            //    *(float*)(MemoryAccess.BaseAddress + 0xCDF4EC) = v;
            //}

            ImGuiIV.DragFloat("radius", ref spinnerRadius, 0.1f);
            ImGuiIV.DragInt("bars", ref spinnerBars, 0.1f);
            ImGuiIV.SpinnerFluid("testspinner", spinnerRadius, Color.White, 2f, spinnerBars);
            ImGuiIV.Knob("testknob", ref knobValue, 0f, 10f);

            ImGuiIV.InputText("Enter sound name to add to sound task list", ref soundNameInput);
            if (ImGuiIV.Button("Add to task list"))
            {
                soundNames.Add(soundNameInput);
            }
            ImGuiIV.SameLine();
            if (ImGuiIV.Button("Clear task list"))
            {
                soundNames.Clear();
            }
            ImGuiIV.TextUnformatted("Sounds in task list: {0}", soundNames.Count);

            if (ImGuiIV.Button("Play sounds from task list in order"))
            {
                for (int i = 0; i < soundNames.Count; i++)
                {
                    string soundName = soundNames[i];

                    TheDelayedCaller.Add(TimeSpan.FromSeconds((i + 1) * 0.1d), "Main", () =>
                    {
                        //PLAY_SOUND_FROM_POSITION(-1, soundName, playerPos);
                        PLAY_SOUND_FRONTEND(-1, soundName);
                    });
                }
            }

            //// ZMenu FirstPerson
            //bool zmenuFpEnabled = CCL.GTAIV.Mods.ZMenuIV.FirstPersonViewEnabled;
            //if (ImGuiIV.CheckBox("zmenuFpEnabled", ref zmenuFpEnabled))
            //    CCL.GTAIV.Mods.ZMenuIV.FirstPersonViewEnabled = zmenuFpEnabled;

            //if (ImGuiIV.Button("toggle fp"))
            //    CCL.GTAIV.Mods.ZMenuIV.ToggleFirstPersonView();

            // ZMenu GTA V Hud
            //bool zmenuGTAVRadarEnabled = CCL.GTAIV.Mods.ZMenuIV.GTAVRadarEnabled;
            //if (ImGuiIV.CheckBox("zmenuGTAVRadarEnabled", ref zmenuGTAVRadarEnabled))
            //    CCL.GTAIV.Mods.ZMenuIV.GTAVRadarEnabled = zmenuGTAVRadarEnabled;
            //ImGuiIV.Text(CCL.GTAIV.Mods.ZMenuIV.GTAVRadarEnabled.ToString());

            //ImGuiIV.SliderInt("index", ref index, 0, 100);
            //ImGuiIV.SliderInt("offset", ref offset, 0, 100);

            //UIntPtr ptr = Patterns.GetAddress(CCL.GTAIV.Win32.Win32Natives.GetModuleHandle("ZMenuIV.asi"),
            //    "e0 ? f3 01",
            //    (uint)index,
            //    (uint)offset);

            //ImGuiIV.Text(ptr.ToUInt32().ToString("X"));
            //ImGuiIV.CheckBox("Do VP", ref vp);
            //ImGuiIV.Text(MemoryAccess.ReadMemory(ptr, vp).ToString());

            //if (ImGuiIV.Button("toggle gta v radar"))
            //    TheDelayedCaller.Add(TimeSpan.FromSeconds(0.1d), "l", () => CCL.GTAIV.Mods.ZMenuIV.ToggleGTAVRadar());

            //int zmenuSelVHudStyle = CCL.GTAIV.Mods.ZMenuIV.SelectedGTAVHudStyle;
            //if (ImGuiIV.SliderInt("zmenuSelVHudStyle", ref zmenuSelVHudStyle, 0, 2))
            //    CCL.GTAIV.Mods.ZMenuIV.SelectedGTAVHudStyle = (byte)zmenuSelVHudStyle;

            //if (ImGuiIV.Button("toggle next gta v hud style"))
            //    TheDelayedCaller.Add(TimeSpan.FromSeconds(0.1d), "l", () => CCL.GTAIV.Mods.ZMenuIV.ToggleNextGTAVRadarStyle());

            //if (CCL.GTAIV.Mods.ZMenuIV.GetZMenuVersion(out uint major, out uint minor))
            //{
            //    ImGuiIV.Text("Major: {0}, Minor: {1}", major, minor);
            //}

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
                checkPointId = CREATE_CHECKPOINT(0, playerPedNEW.Matrix.Pos.X, playerPedNEW.Matrix.Pos.Y, playerPedNEW.Matrix.Pos.Z, 0f, 0f, 0f, 1f);
            }
            if (ImGuiIV.Button("set position for explosion"))
            {
                IVPed playerPedNEW = IVPed.FromUIntPtr(IVPlayerInfo.FindThePlayerPed());
                explosionPos = playerPedNEW.Matrix.Pos;
            }
            ImGuiIV.Combo("explosion type", ref explosionType, Consts.EXPLOSION_TYPES);
            ImGuiIV.DragFloat("explosion range", ref explosionRange);
            if (ImGuiIV.Button("spawn explosion"))
            {
                NativeWorld.AddExplosion(explosionPos, (eExplosion)explosionType, explosionRange);
            }

            if (ImGuiIV.Button("spawn fire"))
            {
                IVPed playerPedNEW = IVPed.FromUIntPtr(IVPlayerInfo.FindThePlayerPed());
                scriptFire.Add(START_SCRIPT_FIRE(NativeWorld.GetGroundPosition(playerPedNEW.Matrix.Pos), 25, 3));
            }
            if (ImGuiIV.Button("despawn all fires"))
            {
                for (int i = 0; i < scriptFire.Count; i++)
                {
                    REMOVE_SCRIPT_FIRE(scriptFire[i]);
                }
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
                IVTimerTab();
                IVWeatherTab();
                IVPickupsTab();
                IVPhoneTab();
                IVPadTab();
                IVPoolsTab();

                CurrentPlayerPed(IVPlayerInfo.FindThePlayerPed());
                CurrentVehicleTab(IVPlayerInfo.FindThePlayerPed());

                DummyPedFlagsTab();

                FiFileTest();
                ImgFilesTest();
                HexEditorTest();

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
        private void IVTimerTab()
        {
            if (ImGuiIV.BeginTabItem("IVTimer"))
            {
                ImGuiIV.Text("CodePause: {0}", IVTimer.CodePause);
                ImGuiIV.Text("UserPause: {0}", IVTimer.UserPause);
                ImGuiIV.Text("FrameCounter: {0}", IVTimer.FrameCounter);
                ImGuiIV.Text("TimeInMilliseconds: {0}", IVTimer.TimeInMilliseconds);
                ImGuiIV.Text("MinTimeStep: {0}", IVTimer.MinTimeStep);
                ImGuiIV.Text("MaxTimeStep: {0}", IVTimer.MaxTimeStep);
                ImGuiIV.Text("TimeStep: {0}", IVTimer.TimeStep);
                ImGuiIV.Text("TimeStepNonClipped: {0}", IVTimer.TimeStepNonClipped);
                ImGuiIV.Text("TimeScale: {0}", IVTimer.TimeScale);
                ImGuiIV.Text("TimeScale2: {0}", IVTimer.TimeScale2);
                ImGuiIV.Text("TimeScale3: {0}", IVTimer.TimeScale3);
                ImGuiIV.Text("IsPaused: {0}", IVTimer.GetIsPaused());

                ImGuiIV.EndTabItem();
            }
        }
        private void IVWeatherTab()
        {
            if (ImGuiIV.BeginTabItem("IVWeather"))
            {
                int ForcedWeatherType = IVWeather.ForcedWeatherType; ImGuiIV.DragInt("ForcedWeatherType", ref ForcedWeatherType); IVWeather.ForcedWeatherType = ForcedWeatherType;
                int OldWeatherType = IVWeather.OldWeatherType; ImGuiIV.DragInt("OldWeatherType", ref OldWeatherType); IVWeather.OldWeatherType = OldWeatherType;
                int NewWeatherType = IVWeather.NewWeatherType; ImGuiIV.DragInt("NewWeatherType", ref NewWeatherType); IVWeather.NewWeatherType = NewWeatherType;
                float InterpolationValue = IVWeather.InterpolationValue; ImGuiIV.DragFloat("InterpolationValue", ref InterpolationValue); IVWeather.InterpolationValue = InterpolationValue;
                int WeatherTypeInList = IVWeather.WeatherTypeInList; ImGuiIV.DragInt("WeatherTypeInList", ref WeatherTypeInList); IVWeather.WeatherTypeInList = WeatherTypeInList;
                float Rain = IVWeather.Rain; ImGuiIV.DragFloat("Rain", ref Rain); IVWeather.Rain = Rain;

                ImGuiIV.EndTabItem();
            }
        }

        private bool disablePickupGlow;
        private void IVPickupsTab()
        {
            if (ImGuiIV.BeginTabItem("IVPickups"))
            {
                ImGuiIV.SeparatorText("Main");
                if (ImGuiIV.Button("Shutdown"))
                    IVPickups.Shutdown();
                if (ImGuiIV.Button("Reset"))
                    IVPickups.Reset();

                ImGuiIV.CheckBox("Disable Pickup Glow Effect", ref disablePickupGlow);

                ImGuiIV.Spacing();
                ImGuiIV.SeparatorText("Debug");
                ImGuiIV.CheckBox("Show pickups in range", ref ShowPickups);
                ImGuiIV.DragFloat("Range", ref ShowPickupsAtDistance);


                ImGuiIV.Spacing();
                ImGuiIV.SeparatorText("Temporary Radar Blips For Pickups In Area");

                ImGuiIV.TextDisabled("Create temp pickup radar blips options");
                ImGuiIV.DragFloat("Range", ref tempPickupBlipsRange);
                ImGuiIV.SliderInt("Type", ref tempPickupBlipsType, 0, 20);

                if (ImGuiIV.Button("Create"))
                    IVPickups.CreateTemporaryRadarBlipsForPickupsInArea(playerPos, tempPickupBlipsRange, tempPickupBlipsType);
                ImGuiIV.SameLine();
                if (ImGuiIV.Button("Remove"))
                    IVPickups.RemoveTemporaryRadarBlipsForPickups();


                ImGuiIV.Spacing();
                ImGuiIV.SeparatorText("Temporary Radar Blip For Pickup");

                ImGuiIV.TextDisabled("Create temp pickup radar blips options");
                ImGuiIV.DragInt("SelectedPickupIndexToCreateTempBlipFor", ref selectedPickupIndexToCreateTempBlipFor);

                if (ImGuiIV.Button("Create temp blip"))
                {
                    IVPickup p = IVPickups.Pickups[selectedPickupIndexToCreateTempBlipFor];

                    int tempBlipHandle = IVPickups.CreateTemporaryRadarBlipForPickup(p.Position, selectedPickupIndexToCreateTempBlipFor);
                    IVGame.Console.PrintWarning("CreateTemporaryRadarBlipForPickup returned: " + tempBlipHandle.ToString());
                    p.Blip = tempBlipHandle;
                }

                ImGuiIV.Spacing();
                ImGuiIV.SeparatorText("Pickups");

                ImGuiIV.TextDisabled("Create new pickup options");
                ImGuiIV.DragFloat3("Rotation", ref pickupRotation);
                ImGuiIV.SliderInt("Type", ref pickupType, 0, 50);
                ImGuiIV.InputText("Model", ref pickupModel);
                ImGuiIV.CheckBox("MaybeBlipRelated", ref createBlipForPickup);

                if (ImGuiIV.Button("Create new"))
                {
                    uint hash = RAGE.AtStringHash(pickupModel);
                    IVModelInfo.GetModelInfo(hash, out int index);

                    handleOfLastCreatedPickup = IVPickups.CreatePickup(playerPos + new Vector3(4f, 0f, 0f), pickupRotation, index, pickupType, true, false, createBlipForPickup, 0, 1, 0);
                    IVGame.Console.PrintWarning("CreatePickup returned: " + handleOfLastCreatedPickup);

                    if (handleOfLastCreatedPickup != -1)
                        IVGame.Console.PrintWarning("Does pickup exist: " + DOES_PICKUP_EXIST(handleOfLastCreatedPickup).ToString());
                }
                if (handleOfLastCreatedPickup != -1)
                {
                    if (ImGuiIV.Button(string.Format("Remove last created pickup by its handle ({0})", handleOfLastCreatedPickup)))
                    {
                        IVGame.Console.PrintWarning("RemovePickup returned: " + IVPickups.RemovePickup(handleOfLastCreatedPickup));
                        handleOfLastCreatedPickup = -1;
                    }
                }

                ImGuiIV.EndTabItem();
            }
        }
        private void IVPhoneTab()
        {
            if (ImGuiIV.BeginTabItem("IVPhone"))
            {
                IVPhoneInfo info = IVPhoneInfo.ThePhoneInfo;

                ImGuiIV.Text("PTR: {0}", info.GetUIntPtr().ToUInt32().ToString("X"));

                ImGuiIV.Text("State: {0}", info.State);
                ImGuiIV.Text("_f180: {0}", info._f180);
                ImGuiIV.Text("_f184: {0}", info._f184);
                ImGuiIV.Text("_f188: {0}", info._f188);
                ImGuiIV.Text("_f18C: {0}", info._f18C);
                ImGuiIV.Text("_f190: {0}", info._f190);
                ImGuiIV.Text("_f194: {0}", info._f194);
                ImGuiIV.Text("_f198: {0}", info._f198);
                ImGuiIV.Text("_f19C: {0}", info._f19C);
                ImGuiIV.Text("_f1A0: {0}", info._f1A0);
                ImGuiIV.Text("PhoneType: {0}", info.PhoneType);
                ImGuiIV.Text("_f1A8: {0}", info._f1A8);
                ImGuiIV.Text("_f1AC: {0}", info._f1AC);
                ImGuiIV.Text("_f1B0: {0}", info._f1B0);
                ImGuiIV.Text("_f1B4: {0}", info._f1B4);
                ImGuiIV.Text("_f1B8: {0}", info._f1B8);
                ImGuiIV.Text("_f1BC: {0}", info._f1BC);
                ImGuiIV.Text("_f1C0: {0}", info._f1C0);
                ImGuiIV.Text("_f1C4: {0}", info._f1C4);
                ImGuiIV.Text("_f1C8: {0}", info._f1C8);
                ImGuiIV.Text("_f1CC: {0}", info._f1CC);
                ImGuiIV.Text("_f1D0: {0}", info._f1D0);
                ImGuiIV.Text("_f1D4: {0}", info._f1D4);
                ImGuiIV.Text("_f1D8: {0}", info._f1D8);
                ImGuiIV.Text("_f1DC: {0}", info._f1DC);
                ImGuiIV.Text("_f1E0: {0}", info._f1E0);
                ImGuiIV.Text("DisablePhone: {0}", info.DisablePhone);
                ImGuiIV.Text("RingtoneID: {0}", info.RingtoneID);
                ImGuiIV.Text("Ringtype: {0}", info.Ringtype);
                ImGuiIV.Text("_f1F0: {0}", info._f1F0);
                ImGuiIV.Text("_f1F4: {0}", info._f1F4);
                ImGuiIV.Text("_f1F8: {0}", info._f1F8);
                ImGuiIV.Text("_f208: {0}", info._f208);
                ImGuiIV.Text("_f213: {0}", info._f213);
                ImGuiIV.Text("_f214: {0}", info._f214);
                ImGuiIV.Text("_f218: {0}", info._f218);
                ImGuiIV.Text("_f221: {0}", info._f221);
                ImGuiIV.Text("_f222: {0}", info._f222);
                ImGuiIV.Text("_f223: {0}", info._f223);
                ImGuiIV.Text("_f224: {0}", info._f224);
                ImGuiIV.Text("_f228: {0}", info._f228);
                ImGuiIV.Text("_f230: {0}", info._f230);
                ImGuiIV.Text("_f232: {0}", info._f232);
                ImGuiIV.Text("_f234: {0}", info._f234);
                ImGuiIV.Text("_f23C: {0}", info._f23C);
                ImGuiIV.Text("_f240: {0}", info._f240);
                ImGuiIV.Text("_f244: {0}", info._f244);
                ImGuiIV.Text("_f248: {0}", info._f248);
                ImGuiIV.Text("_f24C: {0}", info._f24C);
                ImGuiIV.Text("SleepMode: {0}", info.SleepMode);

                ImGuiIV.EndTabItem();
            }
        }
        private void IVPadTab()
        {
            if (ImGuiIV.BeginTabItem("IVPad"))
            {
                IVPad pad = IVPad.GetPad();

                for (int i = 0; i < pad.Values.Length; i++)
                {
                    IVPadValues values = pad.Values[i];
                    ePadControls e = (ePadControls)i;

                    ImGuiIV.TextUnformatted("{0} ({1}): {2}", i, e, values.CurrentValue);
                }

                ImGuiIV.EndTabItem();
            }
        }
        private void IVPoolsTab()
        {
            if (ImGuiIV.BeginTabItem("IVPools"))
            {
                if (ImGuiIV.TreeNode("PedIntelligence Pool"))
                {
                    IVPool pool = IVPools.GetPedIntelligencePool();
                    for (int i = 0; i < pool.Count; i++)
                    {
                        UIntPtr ptr = pool.Get(i);

                        if (ptr == UIntPtr.Zero)
                            continue;

                        if (ImGuiIV.TreeNode(string.Format("{0}##PedIntelligencePool", i)))
                        {
                            IVPedIntelligence pedIntelligence = IVPedIntelligence.FromUIntPtr(ptr);
                            ImGuiIV.TextUnformatted("OwnerPed: {0}", pedIntelligence.OwnerPed.ToUInt32().ToString("X"));
                            ImGuiIV.TextUnformatted("SenseRange1: {0}", pedIntelligence.SenseRange1);
                            ImGuiIV.TextUnformatted("SenseRange2: {0}", pedIntelligence.SenseRange2);

                            IVPedTasks tasks = pedIntelligence.Tasks;
                            if (tasks != null)
                            {
                                if (ImGuiIV.TreeNode(string.Format("Tasks##PedIntelligenceTasksPool_{0}", i)))
                                {
                                    // Primary Tasks
                                    ImGuiIV.SeparatorText("Primary Tasks");
                                    IVTask[] primaryTasks = tasks.PrimaryTasks;
                                    for (int t = 0; t < primaryTasks.Length; t++)
                                    {
                                        IVTask task = primaryTasks[t];

                                        if (task != null)
                                            ImGuiIV.TextUnformatted("{0} - IsSimple: {1}, Type: {2}", t, task.IsSimple(), task.GetTaskType());
                                    }

                                    // Secondary Tasks
                                    ImGuiIV.SeparatorText("Secondary Tasks");
                                    IVTask[] secondaryTasks = tasks.SecondaryTasks;
                                    for (int t = 0; t < secondaryTasks.Length; t++)
                                    {
                                        IVTask task = secondaryTasks[t];

                                        if (task != null)
                                            ImGuiIV.TextUnformatted("{0} - IsSimple: {1}, Type: {2}", t, task.IsSimple(), task.GetTaskType());
                                    }

                                    // Movement Tasks
                                    ImGuiIV.SeparatorText("Movement Tasks");
                                    IVTask[] movementTasks = tasks.MovementTasks;
                                    for (int t = 0; t < movementTasks.Length; t++)
                                    {
                                        IVTask task = movementTasks[t];

                                        if (task != null)
                                            ImGuiIV.TextUnformatted("{0} - IsSimple: {1}, Type: {2}", t, task.IsSimple(), task.GetTaskType());
                                    }

                                    ImGuiIV.TreePop();
                                }
                            }

                            ImGuiIV.TreePop();
                        }
                    }

                    ImGuiIV.TreePop();
                }

                ImGuiIV.EndTabItem();
            }
        }
        private void CurrentPlayerPed(UIntPtr playerPedPtr)
        {
            if (playerPedPtr == UIntPtr.Zero)
                return;

            IVPed playerPed = IVPed.FromUIntPtr(playerPedPtr);

            if (ImGuiIV.BeginTabItem("CurrentPlayerPed"))
            {
                ImGuiIV.Text("PTR: {0}", playerPedPtr.ToUInt32().ToString("X"));

                //if (playerPed.StandingOnEntity != null)
                //{
                //    if (ImGuiIV.TreeNode("StandingOnEntity"))
                //    {
                //        if (ImGuiIV.TreeNode("EntityFlags2"))
                //        {
                //            bool _f0 = playerPed.StandingOnEntity.EntityFlags2._f0; ImGuiIV.CheckBox("_f0", ref _f0); playerPed.StandingOnEntity.EntityFlags2._f0 = _f0;
                //            bool _f1 = playerPed.StandingOnEntity.EntityFlags2._f1; ImGuiIV.CheckBox("_f1", ref _f1); playerPed.StandingOnEntity.EntityFlags2._f1 = _f1;
                //            bool _f2 = playerPed.StandingOnEntity.EntityFlags2._f2; ImGuiIV.CheckBox("_f2", ref _f2); playerPed.StandingOnEntity.EntityFlags2._f2 = _f2;
                //            bool _f3 = playerPed.StandingOnEntity.EntityFlags2._f3; ImGuiIV.CheckBox("_f3", ref _f3); playerPed.StandingOnEntity.EntityFlags2._f3 = _f3;
                //            bool _f4 = playerPed.StandingOnEntity.EntityFlags2._f4; ImGuiIV.CheckBox("_f4", ref _f4); playerPed.StandingOnEntity.EntityFlags2._f4 = _f4;
                //            bool _f5 = playerPed.StandingOnEntity.EntityFlags2._f5; ImGuiIV.CheckBox("_f5", ref _f5); playerPed.StandingOnEntity.EntityFlags2._f5 = _f5;
                //            bool _f6 = playerPed.StandingOnEntity.EntityFlags2._f6; ImGuiIV.CheckBox("_f6", ref _f6); playerPed.StandingOnEntity.EntityFlags2._f6 = _f6;
                //            bool _f7 = playerPed.StandingOnEntity.EntityFlags2._f7; ImGuiIV.CheckBox("_f7", ref _f7); playerPed.StandingOnEntity.EntityFlags2._f7 = _f7;
                //            bool _f8 = playerPed.StandingOnEntity.EntityFlags2._f8; ImGuiIV.CheckBox("_f8", ref _f8); playerPed.StandingOnEntity.EntityFlags2._f8 = _f8;
                //            bool _f9 = playerPed.StandingOnEntity.EntityFlags2._f9; ImGuiIV.CheckBox("_f9", ref _f9); playerPed.StandingOnEntity.EntityFlags2._f9 = _f9;
                //            bool _fa = playerPed.StandingOnEntity.EntityFlags2._fa; ImGuiIV.CheckBox("_fa", ref _fa); playerPed.StandingOnEntity.EntityFlags2._fa = _fa;
                //            bool _fb = playerPed.StandingOnEntity.EntityFlags2._fb; ImGuiIV.CheckBox("_fb", ref _fb); playerPed.StandingOnEntity.EntityFlags2._fb = _fb;
                //            bool _fc = playerPed.StandingOnEntity.EntityFlags2._fc; ImGuiIV.CheckBox("_fc", ref _fc); playerPed.StandingOnEntity.EntityFlags2._fc = _fc;
                //            bool _fd = playerPed.StandingOnEntity.EntityFlags2._fd; ImGuiIV.CheckBox("_fd", ref _fd); playerPed.StandingOnEntity.EntityFlags2._fd = _fd;
                //            bool _fe = playerPed.StandingOnEntity.EntityFlags2._fe; ImGuiIV.CheckBox("_fe", ref _fe); playerPed.StandingOnEntity.EntityFlags2._fe = _fe;
                //            bool _ff = playerPed.StandingOnEntity.EntityFlags2._ff; ImGuiIV.CheckBox("_ff", ref _ff); playerPed.StandingOnEntity.EntityFlags2._ff = _ff;
                //            bool _f10 = playerPed.StandingOnEntity.EntityFlags2._f10; ImGuiIV.CheckBox("_f10", ref _f10); playerPed.StandingOnEntity.EntityFlags2._f10 = _f10;
                //            bool _f11 = playerPed.StandingOnEntity.EntityFlags2._f11; ImGuiIV.CheckBox("_f11", ref _f11); playerPed.StandingOnEntity.EntityFlags2._f11 = _f11;
                //            bool _f12 = playerPed.StandingOnEntity.EntityFlags2._f12; ImGuiIV.CheckBox("_f12", ref _f12); playerPed.StandingOnEntity.EntityFlags2._f12 = _f12;
                //            bool _f13 = playerPed.StandingOnEntity.EntityFlags2._f13; ImGuiIV.CheckBox("_f13", ref _f13); playerPed.StandingOnEntity.EntityFlags2._f13 = _f13;
                //            bool _f14 = playerPed.StandingOnEntity.EntityFlags2._f14; ImGuiIV.CheckBox("_f14", ref _f14); playerPed.StandingOnEntity.EntityFlags2._f14 = _f14;
                //            bool _f15 = playerPed.StandingOnEntity.EntityFlags2._f15; ImGuiIV.CheckBox("_f15", ref _f15); playerPed.StandingOnEntity.EntityFlags2._f15 = _f15;
                //            bool _f16 = playerPed.StandingOnEntity.EntityFlags2._f16; ImGuiIV.CheckBox("_f16", ref _f16); playerPed.StandingOnEntity.EntityFlags2._f16 = _f16;
                //            bool _f17 = playerPed.StandingOnEntity.EntityFlags2._f17; ImGuiIV.CheckBox("_f17", ref _f17); playerPed.StandingOnEntity.EntityFlags2._f17 = _f17;
                //            bool _f18 = playerPed.StandingOnEntity.EntityFlags2._f18; ImGuiIV.CheckBox("_f18", ref _f18); playerPed.StandingOnEntity.EntityFlags2._f18 = _f18;
                //            bool _f19 = playerPed.StandingOnEntity.EntityFlags2._f19; ImGuiIV.CheckBox("_f19", ref _f19); playerPed.StandingOnEntity.EntityFlags2._f19 = _f19;
                //            bool _f1a = playerPed.StandingOnEntity.EntityFlags2._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); playerPed.StandingOnEntity.EntityFlags2._f1a = _f1a;
                //            bool _f1b = playerPed.StandingOnEntity.EntityFlags2._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); playerPed.StandingOnEntity.EntityFlags2._f1b = _f1b;
                //            bool _f1c = playerPed.StandingOnEntity.EntityFlags2._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); playerPed.StandingOnEntity.EntityFlags2._f1c = _f1c;
                //            bool _f1d = playerPed.StandingOnEntity.EntityFlags2._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); playerPed.StandingOnEntity.EntityFlags2._f1d = _f1d;
                //            bool _f1e = playerPed.StandingOnEntity.EntityFlags2._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); playerPed.StandingOnEntity.EntityFlags2._f1e = _f1e;
                //            bool _f1f = playerPed.StandingOnEntity.EntityFlags2._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); playerPed.StandingOnEntity.EntityFlags2._f1f = _f1f;

                //            ImGuiIV.TreePop();
                //        }

                //        ImGuiIV.TreePop();
                //    }
                //}

                //if (ImGuiIV.TreeNode("EntityFlags2"))
                //{
                //    bool _f0 = playerPed.EntityFlags2._f0; ImGuiIV.CheckBox("_f0", ref _f0); playerPed.EntityFlags2._f0 = _f0;
                //    bool _f1 = playerPed.EntityFlags2._f1; ImGuiIV.CheckBox("_f1", ref _f1); playerPed.EntityFlags2._f1 = _f1;
                //    bool _f2 = playerPed.EntityFlags2._f2; ImGuiIV.CheckBox("_f2", ref _f2); playerPed.EntityFlags2._f2 = _f2;
                //    bool _f3 = playerPed.EntityFlags2._f3; ImGuiIV.CheckBox("_f3", ref _f3); playerPed.EntityFlags2._f3 = _f3;
                //    bool _f4 = playerPed.EntityFlags2._f4; ImGuiIV.CheckBox("_f4", ref _f4); playerPed.EntityFlags2._f4 = _f4;
                //    bool _f5 = playerPed.EntityFlags2._f5; ImGuiIV.CheckBox("_f5", ref _f5); playerPed.EntityFlags2._f5 = _f5;
                //    bool _f6 = playerPed.EntityFlags2._f6; ImGuiIV.CheckBox("_f6", ref _f6); playerPed.EntityFlags2._f6 = _f6;
                //    bool _f7 = playerPed.EntityFlags2._f7; ImGuiIV.CheckBox("_f7", ref _f7); playerPed.EntityFlags2._f7 = _f7;
                //    bool _f8 = playerPed.EntityFlags2._f8; ImGuiIV.CheckBox("_f8", ref _f8); playerPed.EntityFlags2._f8 = _f8;
                //    bool _f9 = playerPed.EntityFlags2._f9; ImGuiIV.CheckBox("_f9", ref _f9); playerPed.EntityFlags2._f9 = _f9;
                //    bool _fa = playerPed.EntityFlags2._fa; ImGuiIV.CheckBox("_fa", ref _fa); playerPed.EntityFlags2._fa = _fa;
                //    bool _fb = playerPed.EntityFlags2._fb; ImGuiIV.CheckBox("_fb", ref _fb); playerPed.EntityFlags2._fb = _fb;
                //    bool _fc = playerPed.EntityFlags2._fc; ImGuiIV.CheckBox("_fc", ref _fc); playerPed.EntityFlags2._fc = _fc;
                //    bool _fd = playerPed.EntityFlags2._fd; ImGuiIV.CheckBox("_fd", ref _fd); playerPed.EntityFlags2._fd = _fd;
                //    bool _fe = playerPed.EntityFlags2._fe; ImGuiIV.CheckBox("_fe", ref _fe); playerPed.EntityFlags2._fe = _fe;
                //    bool _ff = playerPed.EntityFlags2._ff; ImGuiIV.CheckBox("_ff", ref _ff); playerPed.EntityFlags2._ff = _ff;
                //    bool _f10 = playerPed.EntityFlags2._f10; ImGuiIV.CheckBox("_f10", ref _f10); playerPed.EntityFlags2._f10 = _f10;
                //    bool _f11 = playerPed.EntityFlags2._f11; ImGuiIV.CheckBox("_f11", ref _f11); playerPed.EntityFlags2._f11 = _f11;
                //    bool _f12 = playerPed.EntityFlags2._f12; ImGuiIV.CheckBox("_f12", ref _f12); playerPed.EntityFlags2._f12 = _f12;
                //    bool _f13 = playerPed.EntityFlags2._f13; ImGuiIV.CheckBox("_f13", ref _f13); playerPed.EntityFlags2._f13 = _f13;
                //    bool _f14 = playerPed.EntityFlags2._f14; ImGuiIV.CheckBox("_f14", ref _f14); playerPed.EntityFlags2._f14 = _f14;
                //    bool _f15 = playerPed.EntityFlags2._f15; ImGuiIV.CheckBox("_f15", ref _f15); playerPed.EntityFlags2._f15 = _f15;
                //    bool _f16 = playerPed.EntityFlags2._f16; ImGuiIV.CheckBox("_f16", ref _f16); playerPed.EntityFlags2._f16 = _f16;
                //    bool _f17 = playerPed.EntityFlags2._f17; ImGuiIV.CheckBox("_f17", ref _f17); playerPed.EntityFlags2._f17 = _f17;
                //    bool _f18 = playerPed.EntityFlags2._f18; ImGuiIV.CheckBox("_f18", ref _f18); playerPed.EntityFlags2._f18 = _f18;
                //    bool _f19 = playerPed.EntityFlags2._f19; ImGuiIV.CheckBox("_f19", ref _f19); playerPed.EntityFlags2._f19 = _f19;
                //    bool _f1a = playerPed.EntityFlags2._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); playerPed.EntityFlags2._f1a = _f1a;
                //    bool _f1b = playerPed.EntityFlags2._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); playerPed.EntityFlags2._f1b = _f1b;
                //    bool _f1c = playerPed.EntityFlags2._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); playerPed.EntityFlags2._f1c = _f1c;
                //    bool _f1d = playerPed.EntityFlags2._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); playerPed.EntityFlags2._f1d = _f1d;
                //    bool _f1e = playerPed.EntityFlags2._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); playerPed.EntityFlags2._f1e = _f1e;
                //    bool _f1f = playerPed.EntityFlags2._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); playerPed.EntityFlags2._f1f = _f1f;

                //    ImGuiIV.TreePop();
                //}

                if (ImGuiIV.TreeNode("PedFlags"))
                {
                    bool _f0 = playerPed.PedFlags._f0;      ImGuiIV.CheckBox("_f0", ref _f0);       playerPed.PedFlags._f0 = _f0;
                    bool _f1 = playerPed.PedFlags._f1;      ImGuiIV.CheckBox("_f1", ref _f1);       playerPed.PedFlags._f1 = _f1;
                    bool NoHeadshots = playerPed.PedFlags.NoHeadshots;      ImGuiIV.CheckBox("NoHeadshots", ref NoHeadshots);       playerPed.PedFlags.NoHeadshots = NoHeadshots;
                    bool _f3 = playerPed.PedFlags._f3;      ImGuiIV.CheckBox("_f3", ref _f3);       playerPed.PedFlags._f3 = _f3;
                    bool _f4 = playerPed.PedFlags._f4;      ImGuiIV.CheckBox("_f4", ref _f4);       playerPed.PedFlags._f4 = _f4;
                    bool _f5 = playerPed.PedFlags._f5;      ImGuiIV.CheckBox("_f5", ref _f5);       playerPed.PedFlags._f5 = _f5;
                    bool _f6 = playerPed.PedFlags._f6;      ImGuiIV.CheckBox("_f6", ref _f6);       playerPed.PedFlags._f6 = _f6;
                    bool _f7 = playerPed.PedFlags._f7;      ImGuiIV.CheckBox("_f7", ref _f7);       playerPed.PedFlags._f7 = _f7;
                    bool _f8 = playerPed.PedFlags._f8;      ImGuiIV.CheckBox("_f8", ref _f8);       playerPed.PedFlags._f8 = _f8;
                    bool _f9 = playerPed.PedFlags._f9;      ImGuiIV.CheckBox("_f9", ref _f9);       playerPed.PedFlags._f9 = _f9;
                    bool _fa = playerPed.PedFlags._fa;      ImGuiIV.CheckBox("_fa", ref _fa);       playerPed.PedFlags._fa = _fa;
                    bool _fb = playerPed.PedFlags._fb;      ImGuiIV.CheckBox("_fb", ref _fb);       playerPed.PedFlags._fb = _fb;
                    bool _fc = playerPed.PedFlags._fc;      ImGuiIV.CheckBox("_fc", ref _fc);       playerPed.PedFlags._fc = _fc;
                    bool _fd = playerPed.PedFlags._fd;      ImGuiIV.CheckBox("_fd", ref _fd);       playerPed.PedFlags._fd = _fd;
                    bool _fe = playerPed.PedFlags._fe;      ImGuiIV.CheckBox("_fe", ref _fe);       playerPed.PedFlags._fe = _fe;
                    bool _ff = playerPed.PedFlags._ff;      ImGuiIV.CheckBox("_ff", ref _ff);       playerPed.PedFlags._ff = _ff;
                    bool _f10 = playerPed.PedFlags._f10;    ImGuiIV.CheckBox("_f10", ref _f10);     playerPed.PedFlags._f10 = _f10;
                    bool _f11 = playerPed.PedFlags._f11;    ImGuiIV.CheckBox("_f11", ref _f11);     playerPed.PedFlags._f11 = _f11;
                    bool _f12 = playerPed.PedFlags._f12;    ImGuiIV.CheckBox("_f12", ref _f12);     playerPed.PedFlags._f12 = _f12;
                    bool _f13 = playerPed.PedFlags._f13;    ImGuiIV.CheckBox("_f13", ref _f13);     playerPed.PedFlags._f13 = _f13;
                    bool IsBleeding = playerPed.PedFlags.IsBleeding;    ImGuiIV.CheckBox("IsBleeding", ref IsBleeding);     playerPed.PedFlags.IsBleeding = IsBleeding;
                    bool _f15 = playerPed.PedFlags._f15;    ImGuiIV.CheckBox("_f15", ref _f15);     playerPed.PedFlags._f15 = _f15;
                    bool _f16 = playerPed.PedFlags._f16;    ImGuiIV.CheckBox("_f16", ref _f16);     playerPed.PedFlags._f16 = _f16;
                    bool _f17 = playerPed.PedFlags._f17;    ImGuiIV.CheckBox("_f17", ref _f17);     playerPed.PedFlags._f17 = _f17;
                    bool _f18 = playerPed.PedFlags._f18;    ImGuiIV.CheckBox("_f18", ref _f18);     playerPed.PedFlags._f18 = _f18;
                    bool _f19 = playerPed.PedFlags._f19;    ImGuiIV.CheckBox("_f19", ref _f19);     playerPed.PedFlags._f19 = _f19;
                    bool _f1a = playerPed.PedFlags._f1a;    ImGuiIV.CheckBox("_f1a", ref _f1a);     playerPed.PedFlags._f1a = _f1a;
                    bool _f1b = playerPed.PedFlags._f1b;    ImGuiIV.CheckBox("_f1b", ref _f1b);     playerPed.PedFlags._f1b = _f1b;
                    bool _f1c = playerPed.PedFlags._f1c;    ImGuiIV.CheckBox("_f1c", ref _f1c);     playerPed.PedFlags._f1c = _f1c;
                    bool _f1d = playerPed.PedFlags._f1d;    ImGuiIV.CheckBox("_f1d", ref _f1d);     playerPed.PedFlags._f1d = _f1d;
                    bool _f1e = playerPed.PedFlags._f1e;    ImGuiIV.CheckBox("_f1e", ref _f1e);     playerPed.PedFlags._f1e = _f1e;
                    bool _f1f = playerPed.PedFlags._f1f;    ImGuiIV.CheckBox("_f1f", ref _f1f);     playerPed.PedFlags._f1f = _f1f;

                    ImGuiIV.TreePop();
                }
                if (ImGuiIV.TreeNode("PedFlags2"))
                {
                    bool _f0 = playerPed.PedFlags2._f0; ImGuiIV.CheckBox("_f0", ref _f0); playerPed.PedFlags2._f0 = _f0;
                    bool _f1 = playerPed.PedFlags2._f1; ImGuiIV.CheckBox("_f1", ref _f1); playerPed.PedFlags2._f1 = _f1;
                    bool _f2 = playerPed.PedFlags2._f2; ImGuiIV.CheckBox("_f2", ref _f2); playerPed.PedFlags2._f2 = _f2;
                    bool IsWantedByPolice = playerPed.PedFlags2.IsWantedByPolice; ImGuiIV.CheckBox("IsWantedByPolice", ref IsWantedByPolice); playerPed.PedFlags2.IsWantedByPolice = IsWantedByPolice;
                    bool _f4 = playerPed.PedFlags2._f4; ImGuiIV.CheckBox("_f4", ref _f4); playerPed.PedFlags2._f4 = _f4;
                    bool IsDruggedUp = playerPed.PedFlags2.IsDruggedUp; ImGuiIV.CheckBox("IsDruggedUp", ref IsDruggedUp); playerPed.PedFlags2.IsDruggedUp = IsDruggedUp;
                    bool _f6 = playerPed.PedFlags2._f6; ImGuiIV.CheckBox("_f6", ref _f6); playerPed.PedFlags2._f6 = _f6;
                    bool _f7 = playerPed.PedFlags2._f7; ImGuiIV.CheckBox("_f7", ref _f7); playerPed.PedFlags2._f7 = _f7;
                    bool _f8 = playerPed.PedFlags2.WillFlyThroughWindscreen; ImGuiIV.CheckBox("WillFlyThroughWindscreen", ref _f8); playerPed.PedFlags2.WillFlyThroughWindscreen = _f8;
                    bool _f9 = playerPed.PedFlags2._f9; ImGuiIV.CheckBox("_f9", ref _f9); playerPed.PedFlags2._f9 = _f9;
                    bool _fa = playerPed.PedFlags2._fa; ImGuiIV.CheckBox("_fa", ref _fa); playerPed.PedFlags2._fa = _fa;
                    bool _fb = playerPed.PedFlags2._fb; ImGuiIV.CheckBox("_fb", ref _fb); playerPed.PedFlags2._fb = _fb;
                    bool _fc = playerPed.PedFlags2._fc; ImGuiIV.CheckBox("_fc", ref _fc); playerPed.PedFlags2._fc = _fc;
                    bool _fd = playerPed.PedFlags2._fd; ImGuiIV.CheckBox("_fd", ref _fd); playerPed.PedFlags2._fd = _fd;
                    bool _fe = playerPed.PedFlags2._fe; ImGuiIV.CheckBox("_fe", ref _fe); playerPed.PedFlags2._fe = _fe;
                    bool _ff = playerPed.PedFlags2._ff; ImGuiIV.CheckBox("_ff", ref _ff); playerPed.PedFlags2._ff = _ff;
                    bool _f10 = playerPed.PedFlags2._f10; ImGuiIV.CheckBox("_f10", ref _f10); playerPed.PedFlags2._f10 = _f10;
                    bool _f11 = playerPed.PedFlags2._f11; ImGuiIV.CheckBox("_f11", ref _f11); playerPed.PedFlags2._f11 = _f11;
                    bool _f12 = playerPed.PedFlags2._f12; ImGuiIV.CheckBox("_f12", ref _f12); playerPed.PedFlags2._f12 = _f12;
                    bool _f13 = playerPed.PedFlags2.IsEnemy; ImGuiIV.CheckBox("IsEnemy", ref _f13); playerPed.PedFlags2.IsEnemy = _f13;
                    bool _f14 = playerPed.PedFlags2._f14; ImGuiIV.CheckBox("_f14", ref _f14); playerPed.PedFlags2._f14 = _f14;
                    bool _f15 = playerPed.PedFlags2._f15; ImGuiIV.CheckBox("_f15", ref _f15); playerPed.PedFlags2._f15 = _f15;
                    bool _f16 = playerPed.PedFlags2._f16; ImGuiIV.CheckBox("_f16", ref _f16); playerPed.PedFlags2._f16 = _f16;
                    bool _f17 = playerPed.PedFlags2._f17; ImGuiIV.CheckBox("_f17", ref _f17); playerPed.PedFlags2._f17 = _f17;
                    bool _f18 = playerPed.PedFlags2._f18; ImGuiIV.CheckBox("_f18", ref _f18); playerPed.PedFlags2._f18 = _f18;
                    bool _f19 = playerPed.PedFlags2._f19; ImGuiIV.CheckBox("_f19", ref _f19); playerPed.PedFlags2._f19 = _f19;
                    bool _f1a = playerPed.PedFlags2._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); playerPed.PedFlags2._f1a = _f1a;
                    bool _f1b = playerPed.PedFlags2._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); playerPed.PedFlags2._f1b = _f1b;
                    bool _f1c = playerPed.PedFlags2._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); playerPed.PedFlags2._f1c = _f1c;
                    bool _f1d = playerPed.PedFlags2._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); playerPed.PedFlags2._f1d = _f1d;
                    bool _f1e = playerPed.PedFlags2._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); playerPed.PedFlags2._f1e = _f1e;
                    bool _f1f = playerPed.PedFlags2._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); playerPed.PedFlags2._f1f = _f1f;

                    ImGuiIV.TreePop();
                }
                if (ImGuiIV.TreeNode("PedFlags3"))
                {
                    bool _f0 = playerPed.PedFlags3._f0; ImGuiIV.CheckBox("_f0", ref _f0); playerPed.PedFlags3._f0 = _f0;
                    bool _f1 = playerPed.PedFlags3._f1; ImGuiIV.CheckBox("_f1", ref _f1); playerPed.PedFlags3._f1 = _f1;
                    bool _f2 = playerPed.PedFlags3._f2; ImGuiIV.CheckBox("_f2", ref _f2); playerPed.PedFlags3._f2 = _f2;
                    bool _f3 = playerPed.PedFlags3.InCar; ImGuiIV.CheckBox("InCar", ref _f3); playerPed.PedFlags3.InCar = _f3;
                    bool _f4 = playerPed.PedFlags3._f4; ImGuiIV.CheckBox("_f4", ref _f4); playerPed.PedFlags3._f4 = _f4;
                    bool _f5 = playerPed.PedFlags3._f5; ImGuiIV.CheckBox("_f5", ref _f5); playerPed.PedFlags3._f5 = _f5;
                    bool _f6 = playerPed.PedFlags3._f6; ImGuiIV.CheckBox("_f6", ref _f6); playerPed.PedFlags3._f6 = _f6;
                    bool _f7 = playerPed.PedFlags3._f7; ImGuiIV.CheckBox("_f7", ref _f7); playerPed.PedFlags3._f7 = _f7;
                    bool _f8 = playerPed.PedFlags3._f8; ImGuiIV.CheckBox("_f8", ref _f8); playerPed.PedFlags3._f8 = _f8;
                    bool _f9 = playerPed.PedFlags3._f9; ImGuiIV.CheckBox("_f9", ref _f9); playerPed.PedFlags3._f9 = _f9;
                    bool _fa = playerPed.PedFlags3._fa; ImGuiIV.CheckBox("_fa", ref _fa); playerPed.PedFlags3._fa = _fa;
                    bool _fb = playerPed.PedFlags3._fb; ImGuiIV.CheckBox("_fb", ref _fb); playerPed.PedFlags3._fb = _fb;
                    bool _fc = playerPed.PedFlags3._fc; ImGuiIV.CheckBox("_fc", ref _fc); playerPed.PedFlags3._fc = _fc;
                    bool _fd = playerPed.PedFlags3.InAir; ImGuiIV.CheckBox("InAir", ref _fd); playerPed.PedFlags3.InAir = _fd;
                    bool _fe = playerPed.PedFlags3._fe; ImGuiIV.CheckBox("_fe", ref _fe); playerPed.PedFlags3._fe = _fe;
                    bool _ff = playerPed.PedFlags3._ff; ImGuiIV.CheckBox("_ff", ref _ff); playerPed.PedFlags3._ff = _ff;
                    bool _f10 = playerPed.PedFlags3._f10; ImGuiIV.CheckBox("_f10", ref _f10); playerPed.PedFlags3._f10 = _f10;
                    bool _f11 = playerPed.PedFlags3._f11; ImGuiIV.CheckBox("_f11", ref _f11); playerPed.PedFlags3._f11 = _f11;
                    bool _f12 = playerPed.PedFlags3._f12; ImGuiIV.CheckBox("_f12", ref _f12); playerPed.PedFlags3._f12 = _f12;
                    bool _f13 = playerPed.PedFlags3._f13; ImGuiIV.CheckBox("_f13", ref _f13); playerPed.PedFlags3._f13 = _f13;
                    bool _f14 = playerPed.PedFlags3._f14; ImGuiIV.CheckBox("_f14", ref _f14); playerPed.PedFlags3._f14 = _f14;
                    bool _f15 = playerPed.PedFlags3._f15; ImGuiIV.CheckBox("_f15", ref _f15); playerPed.PedFlags3._f15 = _f15;
                    bool _f16 = playerPed.PedFlags3._f16; ImGuiIV.CheckBox("_f16", ref _f16); playerPed.PedFlags3._f16 = _f16;
                    bool _f17 = playerPed.PedFlags3._f17; ImGuiIV.CheckBox("_f17", ref _f17); playerPed.PedFlags3._f17 = _f17;
                    bool _f18 = playerPed.PedFlags3._f18; ImGuiIV.CheckBox("_f18", ref _f18); playerPed.PedFlags3._f18 = _f18;
                    bool _f19 = playerPed.PedFlags3._f19; ImGuiIV.CheckBox("_f19", ref _f19); playerPed.PedFlags3._f19 = _f19;
                    bool _f1a = playerPed.PedFlags3._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); playerPed.PedFlags3._f1a = _f1a;
                    bool _f1b = playerPed.PedFlags3._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); playerPed.PedFlags3._f1b = _f1b;
                    bool _f1c = playerPed.PedFlags3._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); playerPed.PedFlags3._f1c = _f1c;
                    bool _f1d = playerPed.PedFlags3._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); playerPed.PedFlags3._f1d = _f1d;
                    bool _f1e = playerPed.PedFlags3._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); playerPed.PedFlags3._f1e = _f1e;
                    bool _f1f = playerPed.PedFlags3._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); playerPed.PedFlags3._f1f = _f1f;

                    ImGuiIV.TreePop();
                }
                if (ImGuiIV.TreeNode("PedFlags4"))
                {
                    bool IsDrunk = playerPed.PedFlags4.IsDrunk; ImGuiIV.CheckBox("IsDrunk", ref IsDrunk); playerPed.PedFlags4.IsDrunk = IsDrunk;
                    bool _f1 = playerPed.PedFlags4._f1; ImGuiIV.CheckBox("_f1", ref _f1); playerPed.PedFlags4._f1 = _f1;
                    bool _f2 = playerPed.PedFlags4._f2; ImGuiIV.CheckBox("_f2", ref _f2); playerPed.PedFlags4._f2 = _f2;
                    bool _f3 = playerPed.PedFlags4._f3; ImGuiIV.CheckBox("_f3", ref _f3); playerPed.PedFlags4._f3 = _f3;
                    bool _f4 = playerPed.PedFlags4._f4; ImGuiIV.CheckBox("_f4", ref _f4); playerPed.PedFlags4._f4 = _f4;
                    bool _f5 = playerPed.PedFlags4._f5; ImGuiIV.CheckBox("_f5", ref _f5); playerPed.PedFlags4._f5 = _f5;
                    bool _f6 = playerPed.PedFlags4._f6; ImGuiIV.CheckBox("_f6", ref _f6); playerPed.PedFlags4._f6 = _f6;
                    bool _f7 = playerPed.PedFlags4._f7; ImGuiIV.CheckBox("_f7", ref _f7); playerPed.PedFlags4._f7 = _f7;
                    bool _f8 = playerPed.PedFlags4._f8; ImGuiIV.CheckBox("_f8", ref _f8); playerPed.PedFlags4._f8 = _f8;
                    bool _f9 = playerPed.PedFlags4._f9; ImGuiIV.CheckBox("_f9", ref _f9); playerPed.PedFlags4._f9 = _f9;
                    bool _fa = playerPed.PedFlags4._fa; ImGuiIV.CheckBox("_fa", ref _fa); playerPed.PedFlags4._fa = _fa;
                    bool _fb = playerPed.PedFlags4._fb; ImGuiIV.CheckBox("_fb", ref _fb); playerPed.PedFlags4._fb = _fb;
                    bool _fc = playerPed.PedFlags4._fc; ImGuiIV.CheckBox("_fc", ref _fc); playerPed.PedFlags4._fc = _fc;
                    bool _fd = playerPed.PedFlags4._fd; ImGuiIV.CheckBox("_fd", ref _fd); playerPed.PedFlags4._fd = _fd;
                    bool _fe = playerPed.PedFlags4._fe; ImGuiIV.CheckBox("_fe", ref _fe); playerPed.PedFlags4._fe = _fe;
                    bool _ff = playerPed.PedFlags4._ff; ImGuiIV.CheckBox("_ff", ref _ff); playerPed.PedFlags4._ff = _ff;
                    bool _f10 = playerPed.PedFlags4._f10; ImGuiIV.CheckBox("_f10", ref _f10); playerPed.PedFlags4._f10 = _f10;
                    bool _f11 = playerPed.PedFlags4._f11; ImGuiIV.CheckBox("_f11", ref _f11); playerPed.PedFlags4._f11 = _f11;
                    bool _f12 = playerPed.PedFlags4._f12; ImGuiIV.CheckBox("_f12", ref _f12); playerPed.PedFlags4._f12 = _f12;
                    bool _f13 = playerPed.PedFlags4._f13; ImGuiIV.CheckBox("_f13", ref _f13); playerPed.PedFlags4._f13 = _f13;
                    bool _f14 = playerPed.PedFlags4._f14; ImGuiIV.CheckBox("_f14", ref _f14); playerPed.PedFlags4._f14 = _f14;
                    bool _f15 = playerPed.PedFlags4._f15; ImGuiIV.CheckBox("_f15", ref _f15); playerPed.PedFlags4._f15 = _f15;
                    bool _f16 = playerPed.PedFlags4._f16; ImGuiIV.CheckBox("_f16", ref _f16); playerPed.PedFlags4._f16 = _f16;
                    bool _f17 = playerPed.PedFlags4._f17; ImGuiIV.CheckBox("_f17", ref _f17); playerPed.PedFlags4._f17 = _f17;
                    bool _f18 = playerPed.PedFlags4._f18; ImGuiIV.CheckBox("_f18", ref _f18); playerPed.PedFlags4._f18 = _f18;
                    bool _f19 = playerPed.PedFlags4._f19; ImGuiIV.CheckBox("_f19", ref _f19); playerPed.PedFlags4._f19 = _f19;
                    bool _f1a = playerPed.PedFlags4._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); playerPed.PedFlags4._f1a = _f1a;
                    bool _f1b = playerPed.PedFlags4._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); playerPed.PedFlags4._f1b = _f1b;
                    bool _f1c = playerPed.PedFlags4._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); playerPed.PedFlags4._f1c = _f1c;
                    bool _f1d = playerPed.PedFlags4._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); playerPed.PedFlags4._f1d = _f1d;
                    bool _f1e = playerPed.PedFlags4._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); playerPed.PedFlags4._f1e = _f1e;
                    bool _f1f = playerPed.PedFlags4._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); playerPed.PedFlags4._f1f = _f1f;

                    ImGuiIV.TreePop();
                }

                if (ImGuiIV.TreeNode("Tasks"))
                {
                    if (ImGuiIV.TreeNode("MovementTasks"))
                    {
                        IVTask[] tasks = playerPed.PedIntelligence.Tasks.MovementTasks;
                        for (int i = 0; i < tasks.Length; i++)
                        {
                            IVTask task = tasks[i];

                            if (task == null)
                                continue;

                            if (ImGuiIV.TreeNode(string.Format("Movement Task #{0}", i)))
                            {
                                ImGuiIV.TextUnformatted("IsSimple: {0}", task.IsSimple());
                                ImGuiIV.TextUnformatted("Type: {0} ({1})", task.GetTaskType(), (eTask)task.GetTaskType());
                                ImGuiIV.TreePop();
                            }
                        }

                        ImGuiIV.TreePop();
                    }
                    if (ImGuiIV.TreeNode("SecondaryTasks"))
                    {
                        IVTask[] tasks = playerPed.PedIntelligence.Tasks.SecondaryTasks;
                        for (int i = 0; i < tasks.Length; i++)
                        {
                            IVTask task = tasks[i];

                            if (task == null)
                                continue;

                            if (ImGuiIV.TreeNode(string.Format("Secondary Task #{0}", i)))
                            {
                                ImGuiIV.TextUnformatted("IsSimple: {0}", task.IsSimple());
                                ImGuiIV.TextUnformatted("Type: {0} ({1})", task.GetTaskType(), (eTask)task.GetTaskType());
                                ImGuiIV.TreePop();
                            }
                        }

                        ImGuiIV.TreePop();
                    }
                    if (ImGuiIV.TreeNode("PrimaryTasks"))
                    {
                        IVTask[] tasks = playerPed.PedIntelligence.Tasks.PrimaryTasks;
                        for (int i = 0; i < tasks.Length; i++)
                        {
                            IVTask task = tasks[i];

                            if (task == null)
                                continue;

                            if (ImGuiIV.TreeNode(string.Format("Primary Task #{0}", i)))
                            {
                                ImGuiIV.TextUnformatted("IsSimple: {0}", task.IsSimple());
                                ImGuiIV.TextUnformatted("Type: {0} ({1})", task.GetTaskType(), (eTask)task.GetTaskType());
                                ImGuiIV.TreePop();
                            }
                        }

                        ImGuiIV.TreePop();
                    }

                    ImGuiIV.TreePop();
                }

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

                //if (ImGuiIV.TreeNode("EntityFlags2"))
                //{
                //    bool _f0 = veh.EntityFlags2._f0; ImGuiIV.CheckBox("_f0", ref _f0); veh.EntityFlags2._f0 = _f0;
                //    bool _f1 = veh.EntityFlags2._f1; ImGuiIV.CheckBox("_f1", ref _f1); veh.EntityFlags2._f1 = _f1;
                //    bool _f2 = veh.EntityFlags2._f2; ImGuiIV.CheckBox("_f2", ref _f2); veh.EntityFlags2._f2 = _f2;
                //    bool _f3 = veh.EntityFlags2._f3; ImGuiIV.CheckBox("_f3", ref _f3); veh.EntityFlags2._f3 = _f3;
                //    bool _f4 = veh.EntityFlags2._f4; ImGuiIV.CheckBox("_f4", ref _f4); veh.EntityFlags2._f4 = _f4;
                //    bool _f5 = veh.EntityFlags2._f5; ImGuiIV.CheckBox("_f5", ref _f5); veh.EntityFlags2._f5 = _f5;
                //    bool _f6 = veh.EntityFlags2._f6; ImGuiIV.CheckBox("_f6", ref _f6); veh.EntityFlags2._f6 = _f6;
                //    bool _f7 = veh.EntityFlags2._f7; ImGuiIV.CheckBox("_f7", ref _f7); veh.EntityFlags2._f7 = _f7;
                //    bool _f8 = veh.EntityFlags2._f8; ImGuiIV.CheckBox("_f8", ref _f8); veh.EntityFlags2._f8 = _f8;
                //    bool _f9 = veh.EntityFlags2._f9; ImGuiIV.CheckBox("_f9", ref _f9); veh.EntityFlags2._f9 = _f9;
                //    bool _fa = veh.EntityFlags2._fa; ImGuiIV.CheckBox("_fa", ref _fa); veh.EntityFlags2._fa = _fa;
                //    bool _fb = veh.EntityFlags2._fb; ImGuiIV.CheckBox("_fb", ref _fb); veh.EntityFlags2._fb = _fb;
                //    bool _fc = veh.EntityFlags2._fc; ImGuiIV.CheckBox("_fc", ref _fc); veh.EntityFlags2._fc = _fc;
                //    bool _fd = veh.EntityFlags2._fd; ImGuiIV.CheckBox("_fd", ref _fd); veh.EntityFlags2._fd = _fd;
                //    bool _fe = veh.EntityFlags2._fe; ImGuiIV.CheckBox("_fe", ref _fe); veh.EntityFlags2._fe = _fe;
                //    bool _ff = veh.EntityFlags2._ff; ImGuiIV.CheckBox("_ff", ref _ff); veh.EntityFlags2._ff = _ff;
                //    bool _f10 = veh.EntityFlags2._f10; ImGuiIV.CheckBox("_f10", ref _f10); veh.EntityFlags2._f10 = _f10;
                //    bool _f11 = veh.EntityFlags2._f11; ImGuiIV.CheckBox("_f11", ref _f11); veh.EntityFlags2._f11 = _f11;
                //    bool _f12 = veh.EntityFlags2._f12; ImGuiIV.CheckBox("_f12", ref _f12); veh.EntityFlags2._f12 = _f12;
                //    bool _f13 = veh.EntityFlags2._f13; ImGuiIV.CheckBox("_f13", ref _f13); veh.EntityFlags2._f13 = _f13;
                //    bool _f14 = veh.EntityFlags2._f14; ImGuiIV.CheckBox("_f14", ref _f14); veh.EntityFlags2._f14 = _f14;
                //    bool _f15 = veh.EntityFlags2._f15; ImGuiIV.CheckBox("_f15", ref _f15); veh.EntityFlags2._f15 = _f15;
                //    bool _f16 = veh.EntityFlags2._f16; ImGuiIV.CheckBox("_f16", ref _f16); veh.EntityFlags2._f16 = _f16;
                //    bool _f17 = veh.EntityFlags2._f17; ImGuiIV.CheckBox("_f17", ref _f17); veh.EntityFlags2._f17 = _f17;
                //    bool _f18 = veh.EntityFlags2._f18; ImGuiIV.CheckBox("_f18", ref _f18); veh.EntityFlags2._f18 = _f18;
                //    bool _f19 = veh.EntityFlags2._f19; ImGuiIV.CheckBox("_f19", ref _f19); veh.EntityFlags2._f19 = _f19;
                //    bool _f1a = veh.EntityFlags2._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); veh.EntityFlags2._f1a = _f1a;
                //    bool _f1b = veh.EntityFlags2._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); veh.EntityFlags2._f1b = _f1b;
                //    bool _f1c = veh.EntityFlags2._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); veh.EntityFlags2._f1c = _f1c;
                //    bool _f1d = veh.EntityFlags2._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); veh.EntityFlags2._f1d = _f1d;
                //    bool _f1e = veh.EntityFlags2._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); veh.EntityFlags2._f1e = _f1e;
                //    bool _f1f = veh.EntityFlags2._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); veh.EntityFlags2._f1f = _f1f;

                //    ImGuiIV.TreePop();
                //}

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

        private void DummyPedFlagsTab()
        {
            if (dummyPed == null)
                return;

            if (ImGuiIV.BeginTabItem("DummyPedFlags"))
            {
                if (ImGuiIV.Button("Set as mission char"))
                {
                    SET_CHAR_AS_MISSION_CHAR(dummyPed.GetHandle());
                }
                if (ImGuiIV.Button("no longer needed"))
                {
                    MARK_CHAR_AS_NO_LONGER_NEEDED(dummyPed.GetHandle());
                }

                if (ImGuiIV.TreeNode("PedFlags"))
                {
                    bool _f0 = dummyPed.PedFlags._f0; ImGuiIV.CheckBox("_f0", ref _f0); dummyPed.PedFlags._f0 = _f0;
                    bool _f1 = dummyPed.PedFlags._f1; ImGuiIV.CheckBox("_f1", ref _f1); dummyPed.PedFlags._f1 = _f1;
                    bool NoHeadshots = dummyPed.PedFlags.NoHeadshots; ImGuiIV.CheckBox("NoHeadshots", ref NoHeadshots); dummyPed.PedFlags.NoHeadshots = NoHeadshots;
                    bool _f3 = dummyPed.PedFlags._f3; ImGuiIV.CheckBox("_f3", ref _f3); dummyPed.PedFlags._f3 = _f3;
                    bool _f4 = dummyPed.PedFlags._f4; ImGuiIV.CheckBox("_f4", ref _f4); dummyPed.PedFlags._f4 = _f4;
                    bool _f5 = dummyPed.PedFlags._f5; ImGuiIV.CheckBox("_f5", ref _f5); dummyPed.PedFlags._f5 = _f5;
                    bool _f6 = dummyPed.PedFlags._f6; ImGuiIV.CheckBox("_f6", ref _f6); dummyPed.PedFlags._f6 = _f6;
                    bool _f7 = dummyPed.PedFlags._f7; ImGuiIV.CheckBox("_f7", ref _f7); dummyPed.PedFlags._f7 = _f7;
                    bool _f8 = dummyPed.PedFlags._f8; ImGuiIV.CheckBox("_f8", ref _f8); dummyPed.PedFlags._f8 = _f8;
                    bool _f9 = dummyPed.PedFlags._f9; ImGuiIV.CheckBox("_f9", ref _f9); dummyPed.PedFlags._f9 = _f9;
                    bool _fa = dummyPed.PedFlags._fa; ImGuiIV.CheckBox("_fa", ref _fa); dummyPed.PedFlags._fa = _fa;
                    bool _fb = dummyPed.PedFlags._fb; ImGuiIV.CheckBox("_fb", ref _fb); dummyPed.PedFlags._fb = _fb;
                    bool _fc = dummyPed.PedFlags._fc; ImGuiIV.CheckBox("_fc", ref _fc); dummyPed.PedFlags._fc = _fc;
                    bool _fd = dummyPed.PedFlags._fd; ImGuiIV.CheckBox("_fd", ref _fd); dummyPed.PedFlags._fd = _fd;
                    bool _fe = dummyPed.PedFlags._fe; ImGuiIV.CheckBox("_fe", ref _fe); dummyPed.PedFlags._fe = _fe;
                    bool _ff = dummyPed.PedFlags._ff; ImGuiIV.CheckBox("_ff", ref _ff); dummyPed.PedFlags._ff = _ff;
                    bool _f10 = dummyPed.PedFlags._f10; ImGuiIV.CheckBox("_f10", ref _f10); dummyPed.PedFlags._f10 = _f10;
                    bool _f11 = dummyPed.PedFlags._f11; ImGuiIV.CheckBox("_f11", ref _f11); dummyPed.PedFlags._f11 = _f11;
                    bool _f12 = dummyPed.PedFlags._f12; ImGuiIV.CheckBox("_f12", ref _f12); dummyPed.PedFlags._f12 = _f12;
                    bool _f13 = dummyPed.PedFlags._f13; ImGuiIV.CheckBox("_f13", ref _f13); dummyPed.PedFlags._f13 = _f13;
                    bool IsBleeding = dummyPed.PedFlags.IsBleeding; ImGuiIV.CheckBox("IsBleeding", ref IsBleeding); dummyPed.PedFlags.IsBleeding = IsBleeding;
                    bool _f15 = dummyPed.PedFlags._f15; ImGuiIV.CheckBox("_f15", ref _f15); dummyPed.PedFlags._f15 = _f15;
                    bool _f16 = dummyPed.PedFlags._f16; ImGuiIV.CheckBox("_f16", ref _f16); dummyPed.PedFlags._f16 = _f16;
                    bool _f17 = dummyPed.PedFlags._f17; ImGuiIV.CheckBox("_f17", ref _f17); dummyPed.PedFlags._f17 = _f17;
                    bool _f18 = dummyPed.PedFlags._f18; ImGuiIV.CheckBox("_f18", ref _f18); dummyPed.PedFlags._f18 = _f18;
                    bool _f19 = dummyPed.PedFlags._f19; ImGuiIV.CheckBox("_f19", ref _f19); dummyPed.PedFlags._f19 = _f19;
                    bool _f1a = dummyPed.PedFlags._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); dummyPed.PedFlags._f1a = _f1a;
                    bool _f1b = dummyPed.PedFlags._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); dummyPed.PedFlags._f1b = _f1b;
                    bool _f1c = dummyPed.PedFlags._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); dummyPed.PedFlags._f1c = _f1c;
                    bool _f1d = dummyPed.PedFlags._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); dummyPed.PedFlags._f1d = _f1d;
                    bool _f1e = dummyPed.PedFlags._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); dummyPed.PedFlags._f1e = _f1e;
                    bool _f1f = dummyPed.PedFlags._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); dummyPed.PedFlags._f1f = _f1f;

                    ImGuiIV.TreePop();
                }
                if (ImGuiIV.TreeNode("PedFlags2"))
                {
                    bool _f0 = dummyPed.PedFlags2._f0; ImGuiIV.CheckBox("_f0", ref _f0); dummyPed.PedFlags2._f0 = _f0;
                    bool _f1 = dummyPed.PedFlags2._f1; ImGuiIV.CheckBox("_f1", ref _f1); dummyPed.PedFlags2._f1 = _f1;
                    bool _f2 = dummyPed.PedFlags2._f2; ImGuiIV.CheckBox("_f2", ref _f2); dummyPed.PedFlags2._f2 = _f2;
                    bool IsWantedByPolice = dummyPed.PedFlags2.IsWantedByPolice; ImGuiIV.CheckBox("IsWantedByPolice", ref IsWantedByPolice); dummyPed.PedFlags2.IsWantedByPolice = IsWantedByPolice;
                    bool _f4 = dummyPed.PedFlags2._f4; ImGuiIV.CheckBox("_f4", ref _f4); dummyPed.PedFlags2._f4 = _f4;
                    bool IsDruggedUp = dummyPed.PedFlags2.IsDruggedUp; ImGuiIV.CheckBox("IsDruggedUp", ref IsDruggedUp); dummyPed.PedFlags2.IsDruggedUp = IsDruggedUp;
                    bool _f6 = dummyPed.PedFlags2._f6; ImGuiIV.CheckBox("_f6", ref _f6); dummyPed.PedFlags2._f6 = _f6;
                    bool _f7 = dummyPed.PedFlags2._f7; ImGuiIV.CheckBox("_f7", ref _f7); dummyPed.PedFlags2._f7 = _f7;
                    bool _f8 = dummyPed.PedFlags2.WillFlyThroughWindscreen; ImGuiIV.CheckBox("WillFlyThroughWindscreen", ref _f8); dummyPed.PedFlags2.WillFlyThroughWindscreen = _f8;
                    bool _f9 = dummyPed.PedFlags2._f9; ImGuiIV.CheckBox("_f9", ref _f9); dummyPed.PedFlags2._f9 = _f9;
                    bool _fa = dummyPed.PedFlags2._fa; ImGuiIV.CheckBox("_fa", ref _fa); dummyPed.PedFlags2._fa = _fa;
                    bool _fb = dummyPed.PedFlags2._fb; ImGuiIV.CheckBox("_fb", ref _fb); dummyPed.PedFlags2._fb = _fb;
                    bool _fc = dummyPed.PedFlags2._fc; ImGuiIV.CheckBox("_fc", ref _fc); dummyPed.PedFlags2._fc = _fc;
                    bool _fd = dummyPed.PedFlags2._fd; ImGuiIV.CheckBox("_fd", ref _fd); dummyPed.PedFlags2._fd = _fd;
                    bool _fe = dummyPed.PedFlags2._fe; ImGuiIV.CheckBox("_fe", ref _fe); dummyPed.PedFlags2._fe = _fe;
                    bool _ff = dummyPed.PedFlags2._ff; ImGuiIV.CheckBox("_ff", ref _ff); dummyPed.PedFlags2._ff = _ff;
                    bool _f10 = dummyPed.PedFlags2._f10; ImGuiIV.CheckBox("_f10", ref _f10); dummyPed.PedFlags2._f10 = _f10;
                    bool _f11 = dummyPed.PedFlags2._f11; ImGuiIV.CheckBox("_f11", ref _f11); dummyPed.PedFlags2._f11 = _f11;
                    bool _f12 = dummyPed.PedFlags2._f12; ImGuiIV.CheckBox("_f12", ref _f12); dummyPed.PedFlags2._f12 = _f12;
                    bool _f13 = dummyPed.PedFlags2.IsEnemy; ImGuiIV.CheckBox("IsEnemy", ref _f13); dummyPed.PedFlags2.IsEnemy = _f13;
                    bool _f14 = dummyPed.PedFlags2._f14; ImGuiIV.CheckBox("_f14", ref _f14); dummyPed.PedFlags2._f14 = _f14;
                    bool _f15 = dummyPed.PedFlags2._f15; ImGuiIV.CheckBox("_f15", ref _f15); dummyPed.PedFlags2._f15 = _f15;
                    bool _f16 = dummyPed.PedFlags2._f16; ImGuiIV.CheckBox("_f16", ref _f16); dummyPed.PedFlags2._f16 = _f16;
                    bool _f17 = dummyPed.PedFlags2._f17; ImGuiIV.CheckBox("_f17", ref _f17); dummyPed.PedFlags2._f17 = _f17;
                    bool _f18 = dummyPed.PedFlags2._f18; ImGuiIV.CheckBox("_f18", ref _f18); dummyPed.PedFlags2._f18 = _f18;
                    bool _f19 = dummyPed.PedFlags2._f19; ImGuiIV.CheckBox("_f19", ref _f19); dummyPed.PedFlags2._f19 = _f19;
                    bool _f1a = dummyPed.PedFlags2._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); dummyPed.PedFlags2._f1a = _f1a;
                    bool _f1b = dummyPed.PedFlags2._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); dummyPed.PedFlags2._f1b = _f1b;
                    bool _f1c = dummyPed.PedFlags2._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); dummyPed.PedFlags2._f1c = _f1c;
                    bool _f1d = dummyPed.PedFlags2._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); dummyPed.PedFlags2._f1d = _f1d;
                    bool _f1e = dummyPed.PedFlags2._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); dummyPed.PedFlags2._f1e = _f1e;
                    bool _f1f = dummyPed.PedFlags2._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); dummyPed.PedFlags2._f1f = _f1f;

                    ImGuiIV.TreePop();
                }
                if (ImGuiIV.TreeNode("PedFlags3"))
                {
                    bool _f0 = dummyPed.PedFlags3._f0; ImGuiIV.CheckBox("_f0", ref _f0); dummyPed.PedFlags3._f0 = _f0;
                    bool _f1 = dummyPed.PedFlags3._f1; ImGuiIV.CheckBox("_f1", ref _f1); dummyPed.PedFlags3._f1 = _f1;
                    bool _f2 = dummyPed.PedFlags3._f2; ImGuiIV.CheckBox("_f2", ref _f2); dummyPed.PedFlags3._f2 = _f2;
                    bool _f3 = dummyPed.PedFlags3.InCar; ImGuiIV.CheckBox("InCar", ref _f3); dummyPed.PedFlags3.InCar = _f3;
                    bool _f4 = dummyPed.PedFlags3._f4; ImGuiIV.CheckBox("_f4", ref _f4); dummyPed.PedFlags3._f4 = _f4;
                    bool _f5 = dummyPed.PedFlags3._f5; ImGuiIV.CheckBox("_f5", ref _f5); dummyPed.PedFlags3._f5 = _f5;
                    bool _f6 = dummyPed.PedFlags3._f6; ImGuiIV.CheckBox("_f6", ref _f6); dummyPed.PedFlags3._f6 = _f6;
                    bool _f7 = dummyPed.PedFlags3._f7; ImGuiIV.CheckBox("_f7", ref _f7); dummyPed.PedFlags3._f7 = _f7;
                    bool _f8 = dummyPed.PedFlags3._f8; ImGuiIV.CheckBox("_f8", ref _f8); dummyPed.PedFlags3._f8 = _f8;
                    bool _f9 = dummyPed.PedFlags3._f9; ImGuiIV.CheckBox("_f9", ref _f9); dummyPed.PedFlags3._f9 = _f9;
                    bool _fa = dummyPed.PedFlags3._fa; ImGuiIV.CheckBox("_fa", ref _fa); dummyPed.PedFlags3._fa = _fa;
                    bool _fb = dummyPed.PedFlags3._fb; ImGuiIV.CheckBox("_fb", ref _fb); dummyPed.PedFlags3._fb = _fb;
                    bool _fc = dummyPed.PedFlags3._fc; ImGuiIV.CheckBox("_fc", ref _fc); dummyPed.PedFlags3._fc = _fc;
                    bool _fd = dummyPed.PedFlags3.InAir; ImGuiIV.CheckBox("InAir", ref _fd); dummyPed.PedFlags3.InAir = _fd;
                    bool _fe = dummyPed.PedFlags3._fe; ImGuiIV.CheckBox("_fe", ref _fe); dummyPed.PedFlags3._fe = _fe;
                    bool _ff = dummyPed.PedFlags3._ff; ImGuiIV.CheckBox("_ff", ref _ff); dummyPed.PedFlags3._ff = _ff;
                    bool _f10 = dummyPed.PedFlags3._f10; ImGuiIV.CheckBox("_f10", ref _f10); dummyPed.PedFlags3._f10 = _f10;
                    bool _f11 = dummyPed.PedFlags3._f11; ImGuiIV.CheckBox("_f11", ref _f11); dummyPed.PedFlags3._f11 = _f11;
                    bool _f12 = dummyPed.PedFlags3._f12; ImGuiIV.CheckBox("_f12", ref _f12); dummyPed.PedFlags3._f12 = _f12;
                    bool _f13 = dummyPed.PedFlags3._f13; ImGuiIV.CheckBox("_f13", ref _f13); dummyPed.PedFlags3._f13 = _f13;
                    bool _f14 = dummyPed.PedFlags3._f14; ImGuiIV.CheckBox("_f14", ref _f14); dummyPed.PedFlags3._f14 = _f14;
                    bool _f15 = dummyPed.PedFlags3._f15; ImGuiIV.CheckBox("_f15", ref _f15); dummyPed.PedFlags3._f15 = _f15;
                    bool _f16 = dummyPed.PedFlags3._f16; ImGuiIV.CheckBox("_f16", ref _f16); dummyPed.PedFlags3._f16 = _f16;
                    bool _f17 = dummyPed.PedFlags3._f17; ImGuiIV.CheckBox("_f17", ref _f17); dummyPed.PedFlags3._f17 = _f17;
                    bool _f18 = dummyPed.PedFlags3._f18; ImGuiIV.CheckBox("_f18", ref _f18); dummyPed.PedFlags3._f18 = _f18;
                    bool _f19 = dummyPed.PedFlags3._f19; ImGuiIV.CheckBox("_f19", ref _f19); dummyPed.PedFlags3._f19 = _f19;
                    bool _f1a = dummyPed.PedFlags3._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); dummyPed.PedFlags3._f1a = _f1a;
                    bool _f1b = dummyPed.PedFlags3._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); dummyPed.PedFlags3._f1b = _f1b;
                    bool _f1c = dummyPed.PedFlags3._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); dummyPed.PedFlags3._f1c = _f1c;
                    bool _f1d = dummyPed.PedFlags3._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); dummyPed.PedFlags3._f1d = _f1d;
                    bool _f1e = dummyPed.PedFlags3._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); dummyPed.PedFlags3._f1e = _f1e;
                    bool _f1f = dummyPed.PedFlags3._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); dummyPed.PedFlags3._f1f = _f1f;

                    ImGuiIV.TreePop();
                }
                if (ImGuiIV.TreeNode("PedFlags4"))
                {
                    bool IsDrunk = dummyPed.PedFlags4.IsDrunk; ImGuiIV.CheckBox("IsDrunk", ref IsDrunk); dummyPed.PedFlags4.IsDrunk = IsDrunk;
                    bool _f1 = dummyPed.PedFlags4._f1; ImGuiIV.CheckBox("_f1", ref _f1); dummyPed.PedFlags4._f1 = _f1;
                    bool _f2 = dummyPed.PedFlags4._f2; ImGuiIV.CheckBox("_f2", ref _f2); dummyPed.PedFlags4._f2 = _f2;
                    bool _f3 = dummyPed.PedFlags4._f3; ImGuiIV.CheckBox("_f3", ref _f3); dummyPed.PedFlags4._f3 = _f3;
                    bool _f4 = dummyPed.PedFlags4._f4; ImGuiIV.CheckBox("_f4", ref _f4); dummyPed.PedFlags4._f4 = _f4;
                    bool _f5 = dummyPed.PedFlags4._f5; ImGuiIV.CheckBox("_f5", ref _f5); dummyPed.PedFlags4._f5 = _f5;
                    bool _f6 = dummyPed.PedFlags4._f6; ImGuiIV.CheckBox("_f6", ref _f6); dummyPed.PedFlags4._f6 = _f6;
                    bool _f7 = dummyPed.PedFlags4._f7; ImGuiIV.CheckBox("_f7", ref _f7); dummyPed.PedFlags4._f7 = _f7;
                    bool _f8 = dummyPed.PedFlags4._f8; ImGuiIV.CheckBox("_f8", ref _f8); dummyPed.PedFlags4._f8 = _f8;
                    bool _f9 = dummyPed.PedFlags4._f9; ImGuiIV.CheckBox("_f9", ref _f9); dummyPed.PedFlags4._f9 = _f9;
                    bool _fa = dummyPed.PedFlags4._fa; ImGuiIV.CheckBox("_fa", ref _fa); dummyPed.PedFlags4._fa = _fa;
                    bool _fb = dummyPed.PedFlags4._fb; ImGuiIV.CheckBox("_fb", ref _fb); dummyPed.PedFlags4._fb = _fb;
                    bool _fc = dummyPed.PedFlags4._fc; ImGuiIV.CheckBox("_fc", ref _fc); dummyPed.PedFlags4._fc = _fc;
                    bool _fd = dummyPed.PedFlags4._fd; ImGuiIV.CheckBox("_fd", ref _fd); dummyPed.PedFlags4._fd = _fd;
                    bool _fe = dummyPed.PedFlags4._fe; ImGuiIV.CheckBox("_fe", ref _fe); dummyPed.PedFlags4._fe = _fe;
                    bool _ff = dummyPed.PedFlags4._ff; ImGuiIV.CheckBox("_ff", ref _ff); dummyPed.PedFlags4._ff = _ff;
                    bool _f10 = dummyPed.PedFlags4._f10; ImGuiIV.CheckBox("_f10", ref _f10); dummyPed.PedFlags4._f10 = _f10;
                    bool _f11 = dummyPed.PedFlags4._f11; ImGuiIV.CheckBox("_f11", ref _f11); dummyPed.PedFlags4._f11 = _f11;
                    bool _f12 = dummyPed.PedFlags4._f12; ImGuiIV.CheckBox("_f12", ref _f12); dummyPed.PedFlags4._f12 = _f12;
                    bool _f13 = dummyPed.PedFlags4._f13; ImGuiIV.CheckBox("_f13", ref _f13); dummyPed.PedFlags4._f13 = _f13;
                    bool _f14 = dummyPed.PedFlags4._f14; ImGuiIV.CheckBox("_f14", ref _f14); dummyPed.PedFlags4._f14 = _f14;
                    bool _f15 = dummyPed.PedFlags4._f15; ImGuiIV.CheckBox("_f15", ref _f15); dummyPed.PedFlags4._f15 = _f15;
                    bool _f16 = dummyPed.PedFlags4._f16; ImGuiIV.CheckBox("_f16", ref _f16); dummyPed.PedFlags4._f16 = _f16;
                    bool _f17 = dummyPed.PedFlags4._f17; ImGuiIV.CheckBox("_f17", ref _f17); dummyPed.PedFlags4._f17 = _f17;
                    bool _f18 = dummyPed.PedFlags4._f18; ImGuiIV.CheckBox("_f18", ref _f18); dummyPed.PedFlags4._f18 = _f18;
                    bool _f19 = dummyPed.PedFlags4._f19; ImGuiIV.CheckBox("_f19", ref _f19); dummyPed.PedFlags4._f19 = _f19;
                    bool _f1a = dummyPed.PedFlags4._f1a; ImGuiIV.CheckBox("_f1a", ref _f1a); dummyPed.PedFlags4._f1a = _f1a;
                    bool _f1b = dummyPed.PedFlags4._f1b; ImGuiIV.CheckBox("_f1b", ref _f1b); dummyPed.PedFlags4._f1b = _f1b;
                    bool _f1c = dummyPed.PedFlags4._f1c; ImGuiIV.CheckBox("_f1c", ref _f1c); dummyPed.PedFlags4._f1c = _f1c;
                    bool _f1d = dummyPed.PedFlags4._f1d; ImGuiIV.CheckBox("_f1d", ref _f1d); dummyPed.PedFlags4._f1d = _f1d;
                    bool _f1e = dummyPed.PedFlags4._f1e; ImGuiIV.CheckBox("_f1e", ref _f1e); dummyPed.PedFlags4._f1e = _f1e;
                    bool _f1f = dummyPed.PedFlags4._f1f; ImGuiIV.CheckBox("_f1f", ref _f1f); dummyPed.PedFlags4._f1f = _f1f;

                    ImGuiIV.TreePop();
                }

                if (ImGuiIV.TreeNode("Tasks"))
                {
                    if (ImGuiIV.TreeNode("MovementTasks"))
                    {
                        IVTask[] tasks = dummyPed.PedIntelligence.Tasks.MovementTasks;
                        for (int i = 0; i < tasks.Length; i++)
                        {
                            IVTask task = tasks[i];

                            if (task == null)
                                continue;

                            if (ImGuiIV.TreeNode(string.Format("Movement Task #{0}", i)))
                            {
                                ImGuiIV.TextUnformatted("IsSimple: {0}", task.IsSimple());
                                ImGuiIV.TextUnformatted("Type: {0} ({1})", task.GetTaskType(), (eTask)task.GetTaskType());
                                ImGuiIV.TreePop();
                            }
                        }

                        ImGuiIV.TreePop();
                    }
                    if (ImGuiIV.TreeNode("SecondaryTasks"))
                    {
                        IVTask[] tasks = dummyPed.PedIntelligence.Tasks.SecondaryTasks;
                        for (int i = 0; i < tasks.Length; i++)
                        {
                            IVTask task = tasks[i];

                            if (task == null)
                                continue;

                            if (ImGuiIV.TreeNode(string.Format("Secondary Task #{0}", i)))
                            {
                                ImGuiIV.TextUnformatted("IsSimple: {0}", task.IsSimple());
                                ImGuiIV.TextUnformatted("Type: {0} ({1})", task.GetTaskType(), (eTask)task.GetTaskType());
                                ImGuiIV.TreePop();
                            }
                        }

                        ImGuiIV.TreePop();
                    }
                    if (ImGuiIV.TreeNode("PrimaryTasks"))
                    {
                        IVTask[] tasks = dummyPed.PedIntelligence.Tasks.PrimaryTasks;
                        for (int i = 0; i < tasks.Length; i++)
                        {
                            IVTask task = tasks[i];

                            if (task == null)
                                continue;

                            if (ImGuiIV.TreeNode(string.Format("Primary Task #{0}", i)))
                            {
                                ImGuiIV.TextUnformatted("IsSimple: {0}", task.IsSimple());
                                ImGuiIV.TextUnformatted("Type: {0} ({1})", task.GetTaskType(), (eTask)task.GetTaskType());
                                ImGuiIV.TreePop();
                            }
                        }

                        ImGuiIV.TreePop();
                    }

                    ImGuiIV.TreePop();
                }

                ImGuiIV.EndTabItem();
            }
        }

        private void ImgFilesTest()
        {
            if (ImGuiIV.BeginTabItem("ImgFile"))
            {
                for (int i = 0; i < 255; i++)
                {
                    int handle = IVCDStream.GetImageFileHandle(i);

                    if (ImGuiIV.TreeNode(string.Format("{0}##ImgFile", i)))
                    {
                        ImGuiIV.TextUnformatted("Handle: {0}", handle);

                        ImGuiIV.TreePop();
                    }
                }

                ImGuiIV.EndTabItem();
            }
        }
        private void FiFileTest()
        {
            //if (ImGuiIV.BeginTabItem("FiFile"))
            //{
            //    for (int i = 0; i < 64; i++)
            //    {
            //        IVFiFile file = IVFiFile.GetFile(i);

            //        if (file == null)
            //            continue;

            //        if (ImGuiIV.TreeNode(string.Format("{0} (FileHandle: {1})##FiFile", i, file.unk2)))
            //        {
            //            if (ImGuiIV.Button("Close"))
            //                file.Close();
            //            ImGuiIV.SameLine();
            //            if (ImGuiIV.Button("GetLength"))
            //                IVGame.Console.PrintEx("Length of fiFile at index {0} is: {1}", i, file.GetLength());
            //            ImGuiIV.SameLine();
            //            if (ImGuiIV.Button("Flush"))
            //                file.Flush();

            //            //ImGuiIV.TextUnformatted("Device: {0}", file.Device.ToUInt32().ToString("X"));
            //            //ImGuiIV.TextUnformatted("FileHandle: {0}", file.FileHandle);

            //            ImGuiIV.TextColored(Color.Yellow, "MemAddr: {0}", file.GetUIntPtr().ToUInt32().ToString("X"));
            //            ImGuiIV.TextUnformatted("Unk1: {0}", file.unk1);
            //            ImGuiIV.TextUnformatted("Unk2: {0}", file.unk2);
            //            ImGuiIV.TextUnformatted("Unk3: {0}", file.unk3);
            //            ImGuiIV.TextUnformatted("Unk4: {0}", file.unk4);
            //            ImGuiIV.TextUnformatted("Unk5: {0}", file.unk5);
            //            ImGuiIV.TextUnformatted("Unk6: {0}", file.unk6);
            //            ImGuiIV.TextUnformatted("Unk7: {0}", file.unk7);

            //            ImGuiIV.TreePop();
            //        }
            //    }

            //    ImGuiIV.EndTabItem();
            //}
        }
        private void HexEditorTest()
        {
            if (ImGuiIV.BeginTabItem("HexEditor"))
            {
                hexEditorState.Bytes = ImGuiIV.GetIO().ImGuiIOPtr;
                hexEditorState.MaxBytes = Marshal.SizeOf<ImGuiIV_IO>() + 0x1000;

                ImGuiIV.BeginHexEditor("test", hexEditorState);
                ImGuiIV.EndHexEditor();

                ImGuiIV.EndTabItem();
            }
        }
        #endregion

        public class TestClass
        {
            public float TestFloat;

            [ExcludeFromJsonSerialization()]
            public string TestString;

            public int TestInt;

            public TestClass()
            {
                TestFloat = 69.420f;
                TestString = "abc";
                TestInt = 1;
            }
        }

        public static DelayedCalling TheDelayedCaller;
        public class DelayedCalling
        {
            #region Variables
            private List<DelayedCall> delayedCalls;
            #endregion

            #region Classes
            private class DelayedCall
            {
                #region Variables
                public DateTime CallIn;
                public Action TheAction;
                public string CallerName;
                #endregion

                #region Constructor
                public DelayedCall(DateTime time, Action a, string callerName)
                {
                    CallIn = time;
                    TheAction = a;
                    CallerName = callerName;
                }
                #endregion
            }
            #endregion

            #region Constructor
            public DelayedCalling()
            {
                delayedCalls = new List<DelayedCall>();
            }
            #endregion

            public void Process()
            {
                for (int i = 0; i < delayedCalls.Count; i++)
                {
                    DelayedCall delayedCall = delayedCalls[i];
                    DateTime now = DateTime.UtcNow;

                    if (now > delayedCall.CallIn)
                    {
                        try
                        {
                            // Execute the delayed call
                            delayedCall.TheAction?.Invoke();
                        }
                        catch (Exception ex)
                        {
                            // TODO: Maybe replace with your own logging method
                            IVGame.Console.PrintError(string.Format("An error occured while processing delayed calling queue for {0}! Details: {1}", delayedCall.CallerName, ex));
                        }

                        delayedCalls.RemoveAt(i);
                        i--;
                    }
                }
            }
            public void Add(TimeSpan executeIn, string className, Action actionToCall)
            {
                if (actionToCall == null)
                    return;

                delayedCalls.Add(new DelayedCall(DateTime.UtcNow.Add(executeIn), actionToCall, className));
            }
            public void ClearAll()
            {
                delayedCalls.Clear();
            }
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
            hexEditorState = ImGuiIV_HexEditorState.AllocateNew();

            // 2 ways to register a custom console command for this script (Both do the same)
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

            RegisterPhoneNumber("125-658-5374", () =>
            {
                ShowSubtitleMessage("OK!");
            });
        }
        private void Main_Uninitialize(object sender, EventArgs e)
        {
            hexEditorState.Delete();

            // It's a good pratice to unsubscribe from events that are not owned by the "Script" class
            RAGE.OnWindowFocusChanged -= CGame_OnWindowFocusChanged;
            RAGE.OnWndProcMessageReceived -= RAGE_OnWndProcMessageReceived;
        }

        private Vector2 values = new Vector2(1337f, 1500f);

        int tickThreadId;
        int renderThreadId;
        int processCameraThreadId;
        int processVehicleThreadId;

        public bool ShowPickups;
        public float ShowPickupsAtDistance = 50f;
        private void ShowPickupsInWorld(ImGuiIV_DrawingContext ctx)
        {
            IVPickup[] arr = IVPickups.Pickups;

            for (int i = 0; i < arr.Length; i++)
            {
                IVPickup pickup = arr[i];

                // Check distance
                if (Vector3.Distance(playerPos, pickup.Position) > ShowPickupsAtDistance)
                    continue;

                Vector2 screenPos = NativeDrawing.CoordToScreen(pickup.Position);

                ImGuiIV.SetNextWindowPos(screenPos);
                if (ImGuiIV.Begin(string.Format("Pickup {0}", i), eImGuiWindowFlags.AlwaysAutoResize, eImGuiWindowFlagsEx.NoMouseEnable))
                {
                    if (ImGuiIV.Button("Destroy"))
                    {
                        IVGame.Console.PrintWarning(string.Format("Pickup {0} Destroy returned: {1} (MemAddr: {2})", i, pickup.Destroy(), pickup.GetUIntPtr()));
                        ImGuiIV.End();
                        continue;
                    }

                    ImGuiIV.TextColored(Color.Yellow, "MemAddr: {0}", pickup.GetUIntPtr().ToUInt32().ToString("X"));

                    pickup.field_0 = 69;

                    ImGuiIV.TextUnformatted("field_0: {0}", pickup.field_0);
                    ImGuiIV.TextUnformatted("WorldObject: {0}", pickup.WorldObject);
                    ImGuiIV.TextUnformatted("field_8: {0}", pickup.field_8);
                    ImGuiIV.TextUnformatted("RoomKey: {0}", pickup.RoomKey);
                    ImGuiIV.TextUnformatted("Blip: {0}", pickup.Blip);
                    ImGuiIV.TextUnformatted("Position: {0}", pickup.Position);
                    ImGuiIV.TextUnformatted("Type: {0} ({1})", pickup.Type, (ePickupType)pickup.Type);

                    byte type = IVPickups.GetTypeOfPickup(i);
                    ImGuiIV.TextUnformatted("Type (Gotten from function): {0} ({1})", type, (ePickupType)type);


                    ImGuiIV.End();
                }

            }
        }

        public float Alpha = 50f;
        private bool wasOnMission;
        private bool completedMission;
        private bool failedMission;

        private int storedPassedMissions;
        private int storedFailedMissions;

        private static object animsListLockObj = new object();
        List<AnimDetails> anims;
        private void Main_OnImGuiRendering(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
        {
            ImGuiTest();

            lock (animsListLockObj)
            {
                if (anims != null)
                {
                    for (int i = 0; i < anims.Count; i++)
                    {
                        AnimDetails animDetails = anims[i];

                        string str = string.Format("AnimGroupId: {0}, AnimId: {1}, Off12: {2}, Off16: {3}, BlendData: {4} Off88: {5}, CurrentAnimTime: {6} ({7})", animDetails.AnimGroupId, animDetails.AnimId, animDetails.Offset12, animDetails.Offset16, animDetails.BlendDelta, animDetails.Offset88, animDetails.CurrentAnimTime, animDetails.CurrentAnimTimeNormalized);
                        ctx.AddText(new Vector2(64f, 64f + 16f * i), Color.Red, str);
                    }
                }

            }

            if (completedMission)
            {
                float orgFringeScale = ctx.FringeScale;

                ctx.FringeScale = Alpha;

                Vector2 screenSize = ImGuiIV.MainViewport.Size;

                ctx.AddRect(Vector2.Zero,
                    screenSize,
                    Color.Black,
                    0f, eImDrawFlags.None, 1f);

                ctx.FringeScale = orgFringeScale;

                string missionCompleteText = GET_STRING_FROM_TEXT_FILE("MISSION_PASSED");

                if (failedMission)
                    missionCompleteText = GET_STRING_FROM_TEXT_FILE("MISSION_FAILED");

                Vector2 textSize = ImGuiIV.CalcTextSize(missionCompleteText);

                ctx.AddText((screenSize * 0.5f) - (textSize * 0.5f), Color.DarkGreen, missionCompleteText);

            }

            if (ShowPickups)
                ShowPickupsInWorld(ctx);
            
            renderThreadId = Thread.CurrentThread.ManagedThreadId;

            //ImGuiIV.BeginTimeline("test");
            //ImGuiIV.Timeline("testTL1", ref values, 2000);
            //ImGuiIV.EndTimeline(true, 0, 2000, true, 7, true);

            //IVPad pad = IVPad.GetPad();

            //ctx.AddText(new Vector2(100f), Color.Red,
            //    string.Format("INPUT_MOUSE_UD: {1}{0}" +
            //                  "INPUT_MOUSE_LR: {2}{0}" +
            //                  "INPUT_FE_MOUSE_UD: {3}{0}" +
            //                  "INPUT_FE_MOUSE_LR: {4}",
            //    Environment.NewLine,
            //    pad.Values[(int)ePadControls.INPUT_MOUSE_UD].CurrentValue,
            //    pad.Values[(int)ePadControls.INPUT_MOUSE_LR].CurrentValue,
            //    pad.Values[(int)ePadControls.INPUT_FE_MOUSE_UD].CurrentValue,
            //    pad.Values[(int)ePadControls.INPUT_FE_MOUSE_LR].CurrentValue));

            if (MainMenuOpen)
                MainMenu(devicePtr, ctx);

            if (!EnableTestImGuiDraw)
                return;

            ImGuiIV.Begin("Timeline Test Script");

            ImGuiIV.Text("tickThreadId: {0}", tickThreadId);
            ImGuiIV.Text("renderThreadId: {0}", renderThreadId);
            ImGuiIV.Text("processCameraThreadId: {0}", processCameraThreadId);
            ImGuiIV.Text("processVehicleThreadId: {0}", processVehicleThreadId);

            ImGuiIV.End();

            // Drawing test
            ctx.AddLine(new Vector2(0f, 0f), new Vector2(800f, 800f), Color.Red, 1f);
            ctx.AddRectFilled(new Vector2(20f, 20f), new Vector2(40f, 40f), Color.Blue, 0f, eImDrawFlags.None);
            ctx.AddImageRotated(discordImagePtr, new RectangleF(new PointF(10f, 10f), new SizeF(width, height)), rotation, Color.White);
            ctx.AddText(new Vector2(300f, 200f), Color.Red, "Hello world!");
        }
        private void Main_OnFirstD3D9Frame(IntPtr devicePtr)
        {
            // Try create image
            if (ImGuiIV.CreateTextureFromMemory(Properties.Resources.discordTestLogo, out IntPtr ptr, out int imageWidth, out int imageHeight, out eResult result))
            {
                discordImagePtr = ptr;
                width = imageWidth;
                height = imageHeight;
            }
        }

        private void RAGE_OnWndProcMessageReceived(IntPtr hWnd, uint msg, UIntPtr wParam, IntPtr lParam)
        {
            // Received a windows message
        }

        bool lightActive;

        int playerChar;
        bool called;

        // Host
        [StructLayout(LayoutKind.Sequential)]
        public class sSyncedSettings
        {
            public bool SpawnLightning;
            public float SpawnPosX;
            public float SpawnPosY;
            public float SpawnPosZ;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 24)]
            public char[] Arr; // Example: array of size 24

            public Vector3 Pos;
        };
        sSyncedSettings SyncedSettings;
        GCHandle SyncedSettingsHandle;

        public unsafe void SetString(string txt)
        {
            SyncedSettings.Arr = new char[24];

            for (int i = 0; i < txt.Length; i++)
            {
                SyncedSettings.Arr[i] = txt[i];
            }
        }

        // Client
        [StructLayout(LayoutKind.Sequential)]
        public struct sClientSyncedSettings
        {
            public int someValue;
        };
        [StructLayout(LayoutKind.Sequential)]
        public struct SyncedClientSettings
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public sClientSyncedSettings[] ClientSyncedSettings;
        };
        SyncedClientSettings ClientSettings;
        GCHandle ClientSettingsHandle;

        private bool wasSpawned;

        // flashlight test
        public float Intensity = 15.1f;
        public float Range = 40.0f;

        public float innerConeAngle = 1f;
        public float volConeAngle = 15.0f;
        public float volScale = 15.0f;

        public float volIntensity = 40f;
        public float flashlightTargetVolIntensity = 10f;

        public bool enablePlayerFlashlight = true;
        public bool debugCorona;

        public Vector3 AnnhiOffset = new Vector3();
        public Vector3 target = new Vector3(10f, -0.6f, 0f);

        private int flashlightTxd;

        private int planeObj;

        private bool a;

        private uint GetModelHashFromIndex(int modelIndex)
        {
            if (modelIndex >= 0 && modelIndex < 30999)
                return IVModelInfo.ModelInfos[modelIndex].Hash;

            return 0;
        }

        int missionTrain1;
        int eddieLowChar;
        NativeTaskSequence eddieTaskSequence;
        NativeTaskSequence playerTaskSequence;
        bool skipDamageBoneCheck;
        NativeCamera eddieCamera;

        IVPed testPed;
        int level1_limo;

        public float pickupRange = 100f;

        private List<int> missionTrains = new List<int>();

        //private void Test(int player, out IntPtr ptr)
        //{
        //    // Allocate new native context object
        //    IVNativeContext context = IVNativeContext.AllocateNew();

        //    // Push args to native call context
        //    context.Push(player);
        //    context.PushOut(out ptr);

        //    // Invoke the native with the given context
        //    IVNativeInvoke.Invoke((uint)eNativeHash.NATIVE_GET_INTERIOR_FROM_CHAR, context);

        //    // TODO: READ RESULT FROM NATIVE HERE
        //    context.GetResult();

        //    // Cleanup
        //    context.Delete();
        //}


        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct ClientSyncStruct
        {
            public int Value;
        }
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public unsafe struct ClientSyncStructs
        {
            public int ClientSyncSize;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public ClientSyncStruct[] ClientSync;
        }
        public ClientSyncStructs ClientTransmission;
        public GCHandle ClientTransmissionHandle;
        public bool didNetworkStuff;

        int dict;
        int l_U2117;

        IVPed dummyPed;

        // Runs every frame when in-game
        private void Main_WaitTick(object sender, EventArgs e)
        {
            // Prints "Tick from WaitTick event!" every 3000 milliseconds (3 seconds) as set in the constructor of this script
            // IVGame.Console.Print("Tick from WaitTick event!");
        }

        // This is the same rockstar uses for the RAGE.AtStringHash function
        public static class Joaat
        {
            public static uint Compute(string input)
            {
                if (input == null)
                    throw new ArgumentNullException(nameof(input));

                uint hash = 0;
                foreach (char c in input.ToLowerInvariant())
                {
                    hash += c;
                    hash += (hash << 10);
                    hash ^= (hash >> 6);
                }

                hash += (hash << 3);
                hash ^= (hash >> 11);
                hash += (hash << 15);

                return hash;
            }
            public static uint Compute2(string input)
            {
                uint hash = 0;
                foreach (char c in input)
                {
                    hash += c;
                    hash += (hash << 10);
                    hash ^= (hash >> 6);
                }
                hash += (hash << 3);
                hash ^= (hash >> 11);
                hash += (hash << 15);
                return hash;
            }
        }

        /// <summary>
        /// Rockstar’s custom hash: runs the “lowercase, slash‐normalize, mix” loop,
        /// then the final 32769 * ((9*x) ^ ((9*x)>>11)) step.
        /// </summary>
        /// <param name="input">The string to hash (no extra quotes).</param>
        /// <param name="seed">Initial accumulator; for native‐hashing, this is
        /// your script’s seed (see below).</param>
        public static uint Compute(string input, uint seed)
        {
            uint h = seed;
            int i = 0;

            // If it starts with a quote, skip it
            if (input.Length > 0 && input[0] == '"')
                i = 1;

            for (; i < input.Length; i++)
            {
                char c = input[i];
                // If we started with a quote, stop at the closing one
                if (input[0] == '"' && c == '"')
                    break;

                // uppercase A–Z → lowercase
                if (c >= 'A' && c <= 'Z')
                    c = (char)(c + 32);

                // backslash → forward slash
                if (c == '\\')
                    c = '/';

                // mix it in
                uint mix = 1025 * (h + (byte)c);
                h = (mix >> 6) ^ mix;
            }

            // final avalanche
            uint f = 9 * h;
            return 32769 * (f ^ (f >> 11));
        }
        public static uint HashStringLowercaseFromSeed(string input, uint seed)
        {
            int index = 0;
            if (!string.IsNullOrEmpty(input) && input[0] == '"')
                index = 1;

            while (index < input.Length)
            {
                char ch = input[index];

                if (input[0] == '"' && ch == '"')
                    break;

                if (ch >= 'A' && ch <= 'Z')
                {
                    ch = (char)(ch + 32); // convert to lowercase
                }
                else if (ch == '\\')
                {
                    ch = '/';
                }

                seed = ((1025u * (seed + ch)) >> 6) ^ (1025u * (seed + ch));
                index++;
            }

            uint result = 32769u * ((9u * seed) ^ ((9u * seed) >> 11));
            return result;
        }

        public static uint Compute(string name)
        {
            if (string.IsNullOrEmpty(name))
                throw new ArgumentNullException(nameof(name));

            bool quotes = name[0] == '"';
            int index = quotes ? 1 : 0;
            uint key = 0;

            while (index < name.Length && (!quotes || name[index] != '"'))
            {
                char character = name[index++];

                if (character >= 'A' && character <= 'Z')
                    character = (char)(character + ('a' - 'A'));  // to lowercase
                else if (character == '\\')
                    character = '/';  // normalize slashes

                key += character;
                key += (key << 10);
                key ^= (key >> 6);
            }

            key += (key << 3);
            key ^= (key >> 11);
            key += (key << 15);

            // disallow 0 and 1 (reserved by engine)
            if (key < 2)
                key += 2;

            return key;
        }
        public static unsafe uint JenkinsOneAtATimeHash(string key)
        {
            if (key == null) throw new ArgumentNullException(nameof(key));

            uint hash = 0;
            fixed (char* pKey = key)
            {
                byte* p = (byte*)pKey;
                // Each C# char is 2 bytes (UTF-16). We only want the low byte (ASCII).
                // So we step by sizeof(char) = 2 bytes at a time.
                for (int i = 0; i < key.Length; i++, p += 2)
                {
                    hash += *p;
                    hash += (hash << 10);
                    hash ^= (hash >> 6);
                }
            }

            hash += (hash << 3);
            hash ^= (hash >> 11);
            hash += (hash << 15);

            return hash;
        }


        //private unsafe void* GetFirstMatchingAnimation(void* ptr, int min, int max)
        //{

        //}
        //private unsafe void* PlayAnimation(void* ptr)
        //{

        //}
        //private unsafe void CopyAnimations(IVPed source, IVPed target, float speed)
        //{
        //    if (speed >= 0.0f)
        //        speed = -8.0f;

        //    void* sourceAnim = GetFirstMatchingAnimation(target.Anim.ToPointer(), 0, 3);

        //    while (sourceAnim != null)
        //    {
        //        uint animGroupId = *(uint*)((uint)sourceAnim + 0x10);
        //        uint animId = *(uint*)((uint)sourceAnim + 0x14);
        //        uint flags = *(uint*)((uint)sourceAnim + 0x18) | 0x2000000;
        //        float blendDelta = *(float*)((uint)sourceAnim + 0x1C);

        //        void* newAnim = PlayAnimation();
        //    }
        //}

        //private unsafe int CopyAnimations(uint pedHandle, uint pedNextHandle, float speed)
        //{
        //    // Resolve both peds using atHandle(pedPool, handle)
        //    IVPed ped1 = IVPed.FromUIntPtr(IVPools.GetPedPool().GetAt(pedHandle));
        //    IVPed ped2 = IVPed.FromUIntPtr(IVPools.GetPedPool().GetAt(pedNextHandle));

        //    if (speed >= 0.0f)
        //        speed = -8.0f;

        //    // Get first animation: sub_9D4AC0(animHierarchy, 0, 3)
        //    IntPtr anim = (IntPtr)sub_9D4AC0(ped2.Anim, 0, 3);

        //    while (anim != IntPtr.Zero)
        //    {
        //        // Access fields in anim structure
        //        int animGroup = *(int*)((byte*)anim + 20);
        //        int animId = *(int*)((byte*)anim + 24);
        //        uint flags = *(uint*)((byte*)anim + 4) | 0x2000000;
        //        float blendDelta = *(float*)((byte*)anim + 8);

        //        // Get anim list from target ped (offset 0x78 == [30 * 4])
        //        void* animList = *(void*)((byte*)ped1.GetUIntPtr() + 0x78); // 30 * 4 = 0x78

        //        // Play animation: sub_9D8A40(animList, animGroup, animId, flags, blendDelta, 1000.0f)
        //        IntPtr newAnim = (IntPtr)sub_9D8A40((void*)animList, animGroup, animId, flags, blendDelta, 1000.0f);

        //        if (newAnim != IntPtr.Zero)
        //        {
        //            float playbackTime = sub_A79F20((void*)anim);
        //            sub_A7B680(*(int*)&playbackTime);
        //            sub_A79FB0(*(float*)((byte*)anim + 88));
        //            sub_A7B700(*(int*)&speed);

        //            // Copy animation timing: currentTime (offset 12), totalTime (offset 16)
        //            *(int*)((byte*)newAnim + 12) = *(int*)((byte*)anim + 12);
        //            *(int*)((byte*)newAnim + 16) = *(int*)((byte*)anim + 16);
        //        }

        //        anim = (IntPtr)sub_9D4B50(0, 3);
        //    }

        //    return 0; // Like the original return (last result unused)
        //}

        int pedNext;

        private void Main_Tick(object sender, EventArgs e)
        {
            while (MainThreadQueue.Count != 0)
            {
                MainThreadQueue.Dequeue()?.Invoke();
            }

            // get player id
            uint playerId = GET_PLAYER_ID();

            // get player index
            int index = CONVERT_INT_TO_PLAYERINDEX(playerId);

            // get player char
            GET_PLAYER_CHAR(index, out playerChar);

            // Get player coordinates
            GET_CHAR_COORDINATES(playerChar, out playerPos);


            // Try get animations from player ped
            // BOOM IT WORKS! PERFECT FOR GTA IV ONLINE ANIMATION SYNC!
            // Just need to cleanup the code
            IVPed playerPed33 = IVPed.FromUIntPtr(IVPlayerInfo.FindThePlayerPed());

            lock (animsListLockObj)
            {
                anims = playerPed33.TryGetAnimations();
            }

            if (pedNext != 0)
            {
                // Copy the player ped anims to this test ped
                //COPY_ANIMATIONS(pedNext, playerChar, 1.0f);
                IVPed p = NativeWorld.GetPedInstanceFromHandle(pedNext);
                p.CurrentHeading = playerPed33.CurrentHeading;

                for (int i = 0; i < anims.Count; i++)
                {
                    AnimDetails animDetails = anims[i];

                    p.PlayAnimationFromAnimDetails(animDetails);

                    //IntPtr anim = p.PlayAnimation((int)animDetails.AnimGroupId, (int)animDetails.AnimId, (int)animDetails.Flags, (int)animDetails.BlendDelta, 1000.0F);

                    //if (anim != IntPtr.Zero)
                    //{
                    //    p.sub_A7B680(anim, animDetails.CurrentAnimTime);
                    //    p.sub_A79FB0(anim, animDetails.Offset88);
                    //    p.sub_A7B700(anim, -8.0f);
                    //    p.idk(anim, animDetails.Offset12, animDetails.Offset16);
                    //}
                }
            }





            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_K, false))
            {
                //playerPed33.Teleport(IVMatrix.Add(playerPed33.Matrix, IVMatrix.Zero.SetPosition(new Vector3(5f, 0f, 0f))), false, true);

                // Jup this works
                //IVHandlingDataMgr.LoadHandlingData("driftingHandling.dat");



                CREATE_CHAR((int)ePedType.PED_TYPE_CIV_MALE, (int)RAGE.AtStringHash("SUPERLOD"), playerPos + new Vector3(2f, 0f, 0f), out pedNext, true);
                SET_CHAR_AS_MISSION_CHAR(pedNext);
                UNLOCK_RAGDOLL(pedNext, false);



                // We can actually specify which speech variant to use using the audSpeechAudioEntity::playSpeech function!!!
                // Below is a test where the player insults a nearby cop which results in a wanted level
                //GET_CURRENT_BASIC_COP_MODEL(out uint m);
                //IVPed foundPed = null;
                //IVPool pp = IVPools.GetPedPool();
                //for (int i = 0; i < pp.Count; i++)
                //{
                //    UIntPtr ptr = pp.Get(i);

                //    if (ptr == UIntPtr.Zero || ptr == IVPlayerInfo.FindThePlayerPed())
                //        continue;

                //    IVPed ped = IVPed.FromUIntPtr(ptr);

                //    // Check distance
                //    if (Vector3.Distance(playerPed33.Matrix.Pos, ped.Matrix.Pos) > 15f)
                //        continue;

                //    if (ped.GetCharModel() == m)
                //    {
                //        foundPed = ped;
                //        break;
                //    }
                //}

                //unsafe
                //{
                //    audSpeechAudioEntity_playSpeechDelegate d = Marshal.GetDelegateForFunctionPointer<audSpeechAudioEntity_playSpeechDelegate>(new IntPtr(MemoryAccess.GetValue(0x0, 0x438AD0)));
                //    d.Invoke((void*)(IVPlayerInfo.FindThePlayerPed().ToUInt32() + 1408), "GENERIC_INSULT", true, false, 0, -1, foundPed == null ? null : foundPed.GetUIntPtr().ToPointer(), 0,  1.0f, 0, 6);
                //}





                //// Benchmark old native caller
                //Stopwatch stopwatch = Stopwatch.StartNew();
                //Function.Call("PRINT_STRING_WITH_LITERAL_STRING_NOW", "STRING", "Cool it works!", 1000, true);
                //stopwatch.Stop();
                //Logger.LogWarningEx("[BENCHMARK] Old native caller: {0}", stopwatch.Elapsed);

                //// Benchmark new native caller
                //stopwatch = Stopwatch.StartNew();
                //FunctionV2.Call(eNativeHash.NATIVE_PRINT_STRING_WITH_LITERAL_STRING_NOW, "STRING", "cool it works!", 1000, true);
                //stopwatch.Stop();
                //Logger.LogWarningEx("[BENCHMARK] NEW native caller: {0}", stopwatch.Elapsed);

                //Logger.LogWarningEx("ManagedMinHook: {0}", ManagedMinHook.DisableHook(MemoryAccess.BaseAddress + 0x438AD0));
            }

            // New native caller test - WORKS
            //uint playerIdTest = FunctionV2.Call<uint>(eNativeHash.NATIVE_GET_PLAYER_ID);
            //int playerIndexTest = FunctionV2.Call<int>(eNativeHash.NATIVE_CONVERT_INT_TO_PLAYERINDEX, playerIdTest);

            //NativeArg playerCharTest = new NativeArg(true, typeof(int));
            //FunctionV2.Call(eNativeHash.NATIVE_GET_PLAYER_CHAR, (NativeArg)playerIdTest, playerCharTest);

            //FunctionV2.Call(eNativeHash.NATIVE_PRINT_STRING_WITH_LITERAL_STRING_NOW,
            //    "STRING",
            //    "",
            //    1000,
            //    true);



            //string str3 = "";

            //if (iVPlayerInfo.PlayerPed != UIntPtr.Zero)
            //    str3 += " PlayerPed ";
            //if (iVPlayerInfo.PlayerPed2 != UIntPtr.Zero)
            //    str3 += " PlayerPed2 ";

            //ShowSubtitleMessage(str3);

            if (IS_CHAR_DEAD(playerChar))
            {
                DRAW_RECT(0.5f, 0.5f, 1f, 1f, 0, 0, 0, 255);
                MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV(true);
            }
            else
            {
                MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV(false);
            }

            return;

            uint trackId = GET_AUDIBLE_MUSIC_TRACK_TEXT_ID();

            if (trackId > 1)
            {
                string label = string.Format("TM_82_{0}", trackId);

                if (DOES_TEXT_LABEL_EXIST(label))
                    ShowSubtitleMessage(GET_STRING_FROM_TEXT_FILE(label));
            }

            GET_PLAYER_MAX_ARMOUR((int)GET_PLAYER_ID(), out uint maxArmour);
            ShowSubtitleMessage(maxArmour.ToString());

            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_N, false))
            {

                //IVNativeContext ctx = IVNativeContext.AllocateNew();

                //ctx.Push(Marshal.StringToHGlobalAnsi(Helper.ConvertObjectToJsonString(new TestClass(), false)).ToInt32());

                //IVNativeInvoke.Invoke(RAGE.AtStringHash("UPDATE_SESSION"), ctx);

                //ctx.GetResult(out int resul);
                //ctx.Delete();



                // log peds
                IVGame.Console.Print("- - - - PEDS - - - -");
                IVPool ivpedpool = IVPools.GetPedPool();
                for (int i = 0; i < ivpedpool.Count; i++)
                {
                    UIntPtr ptr = ivpedpool.Get(i);

                    if (ptr == UIntPtr.Zero)
                        continue;

                    if (ptr == IVPlayerInfo.FindThePlayerPed())
                        IVGame.Console.PrintEx("Handle: {0} (PLAYER)", ivpedpool.GetIndex(ptr));
                    else
                        IVGame.Console.PrintEx("Handle: {0}", ivpedpool.GetIndex(ptr));
                }


                //SKIP_RADIO_FORWARD();

                //isNetworkSession = true;
                //SET_MISSION_FLAG(false);
                //SWITCH_RANDOM_TRAINS(false);

                //CLEAR_AREA(playerPos, 1000f, true);
            }

            if (isNetworkSession)
            {
                for (int i = 0; i < NativeGame.IV_GameScripts.Length; i++)
                {
                    string name = NativeGame.IV_GameScripts[i];

                    if (GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(name) != 0)
                        TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(name);
                }

                SET_THIS_MACHINE_RUNNING_SERVER_SCRIPT(false);

                if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_M, false))
                {
                    if (dummyPed == null)
                    {
                        dummyPed = NativeWorld.SpawnPed("M_Y_GTRI_LO_02", playerPos + new Vector3(3f, 0f, 0f), out int h, false);
                        GIVE_WEAPON_TO_CHAR(h, (int)eWeaponType.WEAPON_PISTOL, 9999, true);
                    }
                    else
                    {
                        _TASK_AIM_GUN_AT_COORD(dummyPed.GetHandle(), playerPos.X, playerPos.Y, playerPos.Z + 20f, 1000);
                    }
                }
            }

            if (IVNetwork.IsNetworkGameRunning())
            {
                int networkKillerOfPlayer = FIND_NETWORK_KILLER_OF_PLAYER((int)GET_PLAYER_ID());

                if (networkKillerOfPlayer != (int)GET_PLAYER_ID())
                {
                    if (IS_PLAYER_DEAD((int)GET_PLAYER_ID()))
                        ShowSubtitleMessage("{0} killed you!", GET_PLAYER_NAME(networkKillerOfPlayer));
                }
            }

            // TODO: Try to create a ped stuck check which checks if the ped is playing that goofy gta san andreas wall animation idk for a specific amount of time

            // - - - PARAMEDIC DESPAWN FIX TEST: FAILED - - -
            //IVPool pedPool5 = IVPools.GetPedPool();
            //for (int i = 0; i < pedPool5.Count; i++)
            //{
            //    UIntPtr ptr = pedPool5.Get(i);

            //    if (ptr == UIntPtr.Zero)
            //        continue;
            //    if (ptr == IVPlayerInfo.FindThePlayerPed())
            //        continue;

            //    int handle = (int)pedPool5.GetIndex(ptr);

            //    GET_PED_TYPE(handle, out uint type);

            //    if ((ePedType)type != ePedType.PED_TYPE_PARAMEDIC)
            //        continue;
            //    //if (IS_CHAR_IN_ANY_CAR(handle))
            //    //    continue;

            //    IVPed ped = IVPed.FromUIntPtr(ptr);
            //    IVTask medicTask = ped.PedIntelligence.Tasks.PrimaryTasks.Where(t => t != null && t.GetTaskType() == (int)eTask.TASK_COMPLEX_MEDIC_TREAT_INJURED_PED).FirstOrDefault();

            //    if (medicTask != null)
            //    {
            //        if (!IS_PED_A_MISSION_PED(handle))
            //        {
            //            // Let's clone all tasks
            //            List<IVTask> clonedTasks = new List<IVTask>();

            //            for (int c = 0; c < ped.PedIntelligence.Tasks.PrimaryTasks.Length; c++)
            //            {
            //                IVTask task = ped.PedIntelligence.Tasks.PrimaryTasks[c];

            //                if (task != null)
            //                    clonedTasks.Add(task.Clone());
            //            }
            //            for (int c = 0; c < ped.PedIntelligence.Tasks.SecondaryTasks.Length; c++)
            //            {
            //                IVTask task = ped.PedIntelligence.Tasks.SecondaryTasks[c];

            //                if (task != null)
            //                    clonedTasks.Add(task.Clone());
            //            }
            //            for (int c = 0; c < ped.PedIntelligence.Tasks.MovementTasks.Length; c++)
            //            {
            //                IVTask task = ped.PedIntelligence.Tasks.MovementTasks[c];

            //                if (task != null)
            //                    clonedTasks.Add(task.Clone());
            //            }

            //            // Set the char as a mission char so he doesn't despawn
            //            // This will clear his tasks
            //            SET_CHAR_KEEP_TASK(handle, true);
            //            SET_CHAR_AS_MISSION_CHAR(handle);
            //            //CLEAR_CHAR_TASKS_IMMEDIATELY(handle);

            //            // Give the char the cloned tasks back
            //            for (int c = 0; c < clonedTasks.Count; c++)
            //            {
            //                //IVTheScripts.GivePedScriptedTask(handle, clonedTasks[c], clonedTasks[c].GetTaskType());
            //                ped.PedIntelligence.Tasks.AssignTask(clonedTasks[c], 4);
            //            }
            //        }

            //        ShowSubtitleMessage("ped has task");
            //    }
            //}

            //if (dict == 0)
            //    dict = LOAD_TXD("bowling");

            //// Draw stuff to rendertarget
            //if (l_U2117 != 0)
            //{

            //}

            // GET_SCRIPT_RENDERTARGET_RENDER_ID(out int rt);

            //int l_U1390 = GET_TEXTURE(dict, "SCOREBOARD");

            //SET_TEXT_FONT(0);
            //SET_TEXT_RENDER_ID((uint)rt);
            ////DRAW_SPRITE((uint)l_U1390, 0.5f, 0.5f, 1f, 1f, 0.00000000f, 255, 255, 255, 255);
            //SET_TEXT_DROPSHADOW(false, 255, 255, 255, 255);
            //SET_TEXT_COLOUR(255, 255, 255, 255);
            //SET_TEXT_SCALE(0.75000000f, 3.50000000f);
            //SET_TEXT_PROPORTIONAL(true);
            //DISPLAY_TEXT_WITH_FLOAT(0.59000000f, 0.75000000f, "TEN_PIN_26", 1f, 2);
            //DRAW_RECT(0.1f, 0.1f, 0.3f, 0.3f, 255, 0, 0, 255);


            if (GET_MISSION_FLAG())
            {
                wasOnMission = true;
                storedPassedMissions = GET_INT_STAT((int)eIntStatistic.STAT_MISSIONS_PASSED);
                storedFailedMissions = GET_INT_STAT((int)eIntStatistic.STAT_MISSIONS_FAILED);
            }
            else
            {
                if (wasOnMission)
                {
                    completedMission = true;

                    if (storedFailedMissions != GET_INT_STAT((int)eIntStatistic.STAT_MISSIONS_FAILED))
                        failedMission = true;
                }
                else
                {
                    // Reset all
                    wasOnMission = false;
                    completedMission = false;
                    failedMission = false;
                }
            }

            IVPed ppn = IVPed.FromUIntPtr(IVPlayerInfo.FindThePlayerPed());
            if (ppn.Vehicle != UIntPtr.Zero)
            {
                IVVehicle v = IVVehicle.FromUIntPtr(ppn.Vehicle);

                ShowSubtitleMessage("{0} - {1}", v.GetUIntPtr().ToUInt32().ToString("X"), (v.GetUIntPtr().ToUInt32() + 8).ToString("X"));

                //ShowSubtitleMessage(v.PetrolTankHealth.ToString());

                //DRAW_CHECKPOINT(v.Matrix.Pos, 3f, Color.Green);
            }


            // player flashlight AND lazer pointer
            if (ppn.WeaponData.WeaponObject != null)
            {
                int weaponObjHandle = ppn.WeaponData.WeaponObject.GetHandle();

                GET_OBJECT_MODEL(weaponObjHandle, out uint weaponObjModel);
                GET_MODEL_DIMENSIONS(weaponObjModel, out Vector3 min, out Vector3 max);

                GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(weaponObjHandle, new Vector3(max.X - 0.085f, 0f, max.Z / 2f), out Vector3 offset1);
                GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(weaponObjHandle, target, out Vector3 offset2);

                if (debugCorona)
                {
                    DRAW_CORONA(offset1, 20f, 0, 0f, Color.Red);
                    DRAW_CORONA(offset2, 20f, 0, 0f, Color.Blue);
                }

                //float volumetricScale = 1f;

                //if (IVWorld.ProcessLineOfSight(offset1, offset2, out IVLineOfSightResults res, 2))
                //    volumetricScale = Vector3.Distance(offset1, res.EndPosition) / target.X;

                GET_INTERIOR_FROM_CHAR(playerChar, out int inter);

                LightHelper.DrawLightCone(offset1, Vector3.Normalize(offset2 - offset1), Color.Red, Intensity, Range * 1f, innerConeAngle, volConeAngle, volIntensity, volScale, 0, 0, inter, ppn.GetUIntPtr().ToUInt32());
            }


            //uint m1 = RAGE.AtStringHash("lev6wallpat04");

            //if (!HAS_MODEL_LOADED((int)m1))
            //    REQUEST_MODEL((int)m1);

            return;

            if (IVNetwork.IsNetworkGameRunning())
            {
                if (!didNetworkStuff)
                {
                    // Register network struct
                    if (!ClientTransmissionHandle.IsAllocated)
                    {
                        ClientTransmission = new ClientSyncStructs()
                        {
                            ClientSyncSize = 32,
                            ClientSync = new ClientSyncStruct[32]
                        };

                        for (int i = 0; i < ClientTransmission.ClientSync.Length; i++)
                        {
                            ClientTransmission.ClientSync[i] = new ClientSyncStruct { Value = 0 };
                        }

                        int size = Marshal.SizeOf(ClientTransmission);
                        IVGame.Console.PrintErrorEx("ClientTransmission Size: {0}", size);
                        byte[] buffer = new byte[size];

                        // TOOD: Try with Marshal.AllocHGlobal instead of GCHandle

                        ClientTransmissionHandle = GCHandle.Alloc(buffer, GCHandleType.Pinned);

                        Marshal.StructureToPtr(ClientTransmission, ClientTransmissionHandle.AddrOfPinnedObject(), false);
                        REGISTER_CLIENT_BROADCAST_VARIABLES(ClientTransmissionHandle.AddrOfPinnedObject(), size / 4, 5);
                    }

                    didNetworkStuff = true;
                }
            }

            // Project Thunder Blackout update: No radio on blackout test
            if (IVAudRadioAudioEntity.TheRadioAudioEntity.RadioState == 1 || IVAudRadioAudioEntity.TheRadioAudioEntity.RadioState == 2)
            {
                IVAudRadioAudioEntity.TheRadioAudioEntity.RadioState = 4;
                //IVAudRadioAudioEntity.TheRadioAudioEntity.RadioState2 = 4;
                IVAudRadioAudioEntity.TheRadioAudioEntity.CurrentRadioStationIndexPriority = 254;
                IVAudRadioAudioEntity.TheRadioAudioEntity.CurrentRadioStationIndex = 254;
                IVAudRadioAudioEntity.TheRadioAudioEntity.StationIndex = 254;
            }

            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_K, false))
            {
                if (IVNetwork.IsNetworkGameRunning())
                {
                    // Register network struct
                    if (!ClientTransmissionHandle.IsAllocated)
                    {
                        ClientTransmission = new ClientSyncStructs();
                        ClientTransmission.ClientSyncSize = 32;
                        ClientTransmission.ClientSync = new ClientSyncStruct[32];

                        int size = Marshal.SizeOf(ClientTransmission);
                        IVGame.Console.PrintErrorEx("ClientTransmission Size: {0}", size);
                        byte[] buffer = new byte[size];

                        ClientTransmissionHandle = GCHandle.Alloc(buffer, GCHandleType.Pinned);

                        Marshal.StructureToPtr(ClientTransmission, ClientTransmissionHandle.AddrOfPinnedObject(), false);
                        REGISTER_CLIENT_BROADCAST_VARIABLES(ClientTransmissionHandle.AddrOfPinnedObject(), size / 4, 29);
                    }

                    ShowSubtitleMessage("registered client struct");
                }
                else
                {
                    ShowSubtitleMessage("cannot register client struct: network game not running");
                }
            }
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_L, false))
            {
                // Free allocated network memory
                if (ClientTransmissionHandle.IsAllocated)
                {
                    ClientTransmissionHandle.Free();
                    ShowSubtitleMessage("freed allocated client struct");
                }
                else
                {
                    ShowSubtitleMessage("client struct already freed");
                }
            }
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_N, false))
            {
                if (ClientTransmissionHandle.IsAllocated)
                {
                    ClientTransmission.ClientSync[GET_PLAYER_ID()].Value = 69;

                    // Update the internally registered structure
                    Marshal.StructureToPtr(ClientTransmission, ClientTransmissionHandle.AddrOfPinnedObject(), true);

                    IVGame.ShowSubtitleMessageEx("set value 69 at index {0} in client struct", GET_PLAYER_ID());
                }
                else
                {
                    ShowSubtitleMessage("cannot set value: client struct is not allocated");
                }

                //wasReloadForced = true;

                    // 0, 1, 0, 0 = Crash
                    // 0, 0, 0, 1 = Does NOT do a complete reload. It only starts a new game
                    // 0, 0, 1, 0 = This does do a complete reload! And then it starts a new game
                    //IVGame.Idk(0, 0, 1, 0);
            }

            if (ClientTransmissionHandle.IsAllocated)
            {
                // Read the values of the struct in memory and update our managed struct
                ClientTransmission = Marshal.PtrToStructure<ClientSyncStructs>(ClientTransmissionHandle.AddrOfPinnedObject());

                string str = "";
                for (int i = 0; i < 32; i++)
                {
                    int value = ClientTransmission.ClientSync[i].Value;

                    str += value.ToString() + ", ";
                }
                ShowSubtitleMessage(str);
            }

            //IVPool ssPool = IVPools.GetScriptStorePool();
            //UIntPtr slotZero = ssPool.Get(0);
            //ShowSubtitleMessage("{0}/{1} - Slot 0: {2}", ssPool.Used, ssPool.Count, slotZero.ToUInt32().ToString("X"));

            // Managed native caller test - Works
            //using (IVNativeContext ctx = IVNativeContext.AllocateNew())
            //{
            //    //ctx.Push("NAME");
            //    IVNativeInvoke.Invoke(0x670E3DE2, ctx);

            //    ctx.GetResult(out int res);
            //    ShowSubtitleMessage(res.ToString());
            //}

            //ShowSubtitleMessage(IVAudRadioAudioEntity.TheRadioAudioEntity.GetUIntPtr().ToUInt32().ToString("X"));

            // - - - This stops the player from getting a wanted level when they shoot - - -
            //START_FIRING_AMNESTY();

            // MANAGED NATIVE CALLER WORKS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            //Test(playerChar, out IntPtr ptr2);
            //IVGame.ShowSubtitleMessageEx("interior: {0} ({1})", Marshal.ReadInt32(ptr2), interior);
            //Marshal.FreeHGlobal(ptr2);

            // The IV-SDK .NET method on how to get the player char
            IVPed playerPedNEW = IVPed.FromUIntPtr(IVPlayerInfo.FindThePlayerPed());

            return;

            if (IVNetwork.IsNetworkGameRunning())
            {

                if (!called)
                {

                    // Host
                    {
                        // Definitely much more laborious then when doing it in C++ but it worked!
                        SyncedSettings = new sSyncedSettings
                        {
                            SpawnLightning = false,
                            SpawnPosX = 0.0f,
                            SpawnPosY = 0.0f,
                            SpawnPosZ = 0.0f
                        };

                        int size = Marshal.SizeOf(SyncedSettings);
                        byte[] buffer = new byte[size];

                        // Allocate and pin memory for the struct using GCHandle
                        //SyncedSettingsHandle = GCHandle.Alloc(SyncedSettings, GCHandleType.Pinned);
                        SyncedSettingsHandle = GCHandle.Alloc(buffer, GCHandleType.Pinned);

                        //sSyncedSettings empty = new sSyncedSettings();
                        //Marshal.StructureToPtr(empty, SyncedSettingsHandle.AddrOfPinnedObject(), false);
                        Marshal.StructureToPtr(SyncedSettings, SyncedSettingsHandle.AddrOfPinnedObject(), false);

                        // Call the unmanaged function
                        REGISTER_HOST_BROADCAST_VARIABLES(SyncedSettingsHandle.AddrOfPinnedObject(), Marshal.SizeOf(typeof(sSyncedSettings)) / 4, 5);
                    }

                    // Client
                    {
                        ClientSettings = new SyncedClientSettings
                        {
                            ClientSyncedSettings = new sClientSyncedSettings[32]
                        };

                        int size = Marshal.SizeOf(ClientSettings);
                        byte[] buffer = new byte[size];

                        // Allocate and pin memory for the struct using GCHandle
                        //ClientSettingsHandle = GCHandle.Alloc(ClientSettings, GCHandleType.Pinned);
                        ClientSettingsHandle = GCHandle.Alloc(buffer, GCHandleType.Pinned);

                        //SyncedClientSettings empty = new SyncedClientSettings();
                        //Marshal.StructureToPtr(empty, ClientSettingsHandle.AddrOfPinnedObject(), false);
                        Marshal.StructureToPtr(ClientSettings, ClientSettingsHandle.AddrOfPinnedObject(), false);

                        // Call the unmanaged function
                        REGISTER_CLIENT_BROADCAST_VARIABLES(ClientSettingsHandle.AddrOfPinnedObject(), size / 4, 5);
                    }

                    called = true;
                }

                // Set new host value
                if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_K, false))
                {
                    // Modify value of struct
                    SyncedSettings.SpawnLightning = true;
                    SyncedSettings.SpawnPosX = 2.65f;
                    SyncedSettings.SpawnPosY = 9.99f;
                    SyncedSettings.SpawnPosZ = 57.57f;

                    SetString("192.168.2.138:8000");

                    SyncedSettings.Pos = Vector3.One;

                    // Copy the struct to the allocated unmanaged memory
                    Marshal.StructureToPtr(SyncedSettings, SyncedSettingsHandle.AddrOfPinnedObject(), false);
                }
                if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_J, false))
                {
                    // Modify value of struct
                    SyncedSettings.SpawnLightning = false;

                    // Copy the struct to the allocated unmanaged memory
                    Marshal.StructureToPtr(SyncedSettings, SyncedSettingsHandle.AddrOfPinnedObject(), false);
                }

                // Set new client values
                if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_L, false))
                {
                    // Modify all client variables
                    for (int i = 0; i < 32; i++)
                    {
                        unsafe { ClientSettings.ClientSyncedSettings[i].someValue = 69; }
                    }

                    // Copy the struct to the allocated unmanaged memory
                    Marshal.StructureToPtr(ClientSettings, ClientSettingsHandle.AddrOfPinnedObject(), false);

                    SEND_CLIENT_BROADCAST_VARIABLES_NOW();
                }
                // reset client values
                if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_M, false))
                {
                    // Modify all client variables
                    for (int i = 0; i < 32; i++)
                    {
                        unsafe { ClientSettings.ClientSyncedSettings[i].someValue = 0; }
                    }

                    // Copy the struct to the allocated unmanaged memory
                    Marshal.StructureToPtr(ClientSettings, ClientSettingsHandle.AddrOfPinnedObject(), false);

                    SEND_CLIENT_BROADCAST_VARIABLES_NOW();
                }

                // Get host value
                sSyncedSettings retrievedHostStruct = Marshal.PtrToStructure<sSyncedSettings>(SyncedSettingsHandle.AddrOfPinnedObject());
                SyncedClientSettings retrievedClientStruct = Marshal.PtrToStructure<SyncedClientSettings>(ClientSettingsHandle.AddrOfPinnedObject());

                unsafe
                {
                    //ShowSubtitleMessage("Spawn: {0}, X: {1}, Y: {2}, Z: {3}, Arr: {4}, Pos: {5}", retrievedHostStruct.SpawnLightning, retrievedHostStruct.SpawnPosX, retrievedHostStruct.SpawnPosY, retrievedHostStruct.SpawnPosZ, new string(retrievedHostStruct.Arr), SyncedSettings.Pos);
                    //ShowSubtitleMessage(retrievedHostStruct.SpawnLightning.ToString());
                    //ShowSubtitleMessage("Client 11: {0}", retrievedClientStruct.ClientSyncedSettings[11].someValue);

                    if (retrievedHostStruct.SpawnLightning)
                    {
                        if (!wasSpawned)
                        {
                            ShowSubtitleMessage("SPAWN NOW!");
                            wasSpawned = true;
                        }
                    }
                    else
                    {
                        wasSpawned = false;
                    }
                }

            }
            else
            {
                if (SyncedSettingsHandle.IsAllocated)
                    SyncedSettingsHandle.Free();
                if (ClientSettingsHandle.IsAllocated)
                    ClientSettingsHandle.Free();
                called = false;
            }

            //ShowSubtitleMessage(IVSDKDotNet.Hooking.Patterns.GetAddress("55 8B EC 83 E4 F0 81 EC B4 00 00 00 F3 0F 10 45 08", 0, 0).ToString("X"));

            //UIntPtr ptr2 = playerPedNEW.WeaponData.GetUIntPtr();
            //ShowSubtitleMessage("Player: {0}, WeaponData: {1} ({2})", playerPedNEW.GetUIntPtr().ToString(), ptr2.ToString(), ptr2.ToUInt32().ToString("X"));

            if (playerPedNEW.Vehicle != UIntPtr.Zero)
            {
                IVVehicle v = IVVehicle.FromUIntPtr(playerPedNEW.Vehicle);

                //DRAW_CHECKPOINT(v.Matrix.Pos, 3f, Color.Green);
            }

            TheDelayedCaller.Process();

            // good battle royale "plane" model: ec_jet4

            // 1: X: 1239.474 Y: 2650.522 Z: 450
            // 2: X: -2077.526 Y: -1058.722 Z: 450

            // - - - - - ANNIHILATOR SPOTLIGHT TEST - - - - - - -

            //if (IS_CHAR_IN_ANY_CAR(playerChar))
            //{
            //    GET_CAR_CHAR_IS_USING(playerChar, out int annhi);
            //    GET_CAR_MODEL(annhi, out uint annhiModel);

            //    if (IS_THIS_MODEL_A_HELI(annhiModel))
            //    {
            //        GET_MODEL_DIMENSIONS(annhiModel, out Vector3 annhiModelMin, out Vector3 annhiModelMax);
            //        GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(annhi, AnnhiOffset, out Vector3 o1);

            //        CCL.GTAIV.LightHelper.AddSpotLight(o1, NativeWorld.GetGroundPosition(o1), Color.White, Intensity, Range, innerConeAngle, volConeAngle, volIntensity, 1f, playerPedNEW.GetUIntPtr());
            //    }
            //}

            // - - - - - ANNIHILATOR SPOTLIGHT TEST END - - - - - - -


            // - - - - - KILL ALL DRIVERS TEST - - - - -

            //if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_G, false))
            //{
            //    IVPool pool = IVPools.GetVehiclePool();
            //    for (int i = 0; i < pool.Count; i++)
            //    {
            //        UIntPtr ptr = pool.Get(i);

            //        if (ptr == UIntPtr.Zero)
            //            continue;

            //        int handle = (int)pool.GetIndex(ptr);

            //        GET_DRIVER_OF_CAR(handle, out int vehDriver);

            //        if (vehDriver == 0)
            //            continue;

            //        GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(vehDriver, new Vector3(0f, 2f, 0.65f), out Vector3 vStart);
            //        GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(vehDriver, new Vector3(0f, -1f, 0.65f), out Vector3 vEnd);
            //        FIRE_SINGLE_BULLET(vStart, vEnd, 10);
            //    }
            //}

            // - - - - - KILL ALL DRIVERS TEST END - - - - -



            // - - - - - FLASHLIGHT TEST - - - - - - -

            //if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_O, false))
            //{
            //    //FORCE_WEATHER((uint)eWeather.WEATHER_FOGGY);

            //    //TestClass testClass = new TestClass();
            //    //IVGame.Console.PrintError(Helper.ConvertObjectToJsonString(testClass, false));
            //}

            // Load flashlight txd
            int slot = IVTxdStore.FindTxdSlot("flashlight");
            if (flashlightTxd == 0)
                flashlightTxd = LOAD_TXD("flashlight");

            float volumetricLightIntensity = 0f;

            eWeather oldWeatherType = (eWeather)IVWeather.OldWeatherType;
            eWeather newWeatherType = (eWeather)IVWeather.NewWeatherType;

            if (oldWeatherType == eWeather.WEATHER_FOGGY && newWeatherType == eWeather.WEATHER_FOGGY)
            {
                // Weather is currently foggy
                volumetricLightIntensity = flashlightTargetVolIntensity;
            }
            else
            {
                // Weather is not currently foggy. Check if fogginess is going away or coming.
                if (oldWeatherType != eWeather.WEATHER_FOGGY && newWeatherType == eWeather.WEATHER_FOGGY)
                {
                    // fog is coming
                    volumetricLightIntensity = Lerp(0f, flashlightTargetVolIntensity, IVWeather.InterpolationValue);
                }
                else if (oldWeatherType == eWeather.WEATHER_FOGGY && newWeatherType != eWeather.WEATHER_FOGGY)
                {
                    // fog is going away
                    volumetricLightIntensity = Lerp(flashlightTargetVolIntensity, 0f, IVWeather.InterpolationValue);
                }
            }

            // flashlight for cops
            IVPool pedPool = IVPools.GetPedPool();
            for (int i = 0; i < pedPool.Count; i++)
            {
                UIntPtr ptr = pedPool.Get(i);

                if (ptr == UIntPtr.Zero)
                    continue;
                if (ptr == playerPedNEW.GetUIntPtr())
                    continue;

                IVPed ped = IVPed.FromUIntPtr(ptr);

                if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_O, false))
                {
                    IVGame.Console.PrintWarning("Trying to remove ped " + ptr.ToString() + ". RemovePed func returned: " + IVPedFactoryNY.ThePedFactory.DeletePed(ped));
                    continue;
                }

                if (ped.GetPedType() != ePedType.PED_TYPE_COP)
                    continue;

                if (ped.WeaponData.WeaponObject != null)
                {
                    int weaponObjHandle = ped.WeaponData.WeaponObject.GetHandle();

                    if (weaponObjHandle != 0)
                    {
                        if (DOES_OBJECT_EXIST(weaponObjHandle))
                        {
                            GET_OBJECT_MODEL(weaponObjHandle, out uint weaponObjModel);
                            GET_MODEL_DIMENSIONS(weaponObjModel, out Vector3 min, out Vector3 max);

                            GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(weaponObjHandle, new Vector3(max.X, 0f, 0f), out Vector3 offset1);
                            GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(weaponObjHandle, target, out Vector3 offset2);

                            float volumetricScale = 1f;

                            if (IVWorld.ProcessLineOfSight(offset1, offset2, out IVLineOfSightResults res, 2))
                                volumetricScale = Vector3.Distance(offset1, res.EndPosition) / target.X;

                            GET_INTERIOR_AT_COORDS(offset1, out int inter);

                            LightHelper.DrawLightCone(offset1, Vector3.Normalize(offset2 - offset1), Color.White, Intensity, Range, innerConeAngle, volConeAngle, volumetricLightIntensity, volumetricScale, slot, (int)RAGE.AtStringHash("torch2"), inter, ptr.ToUInt32());
                        }
                    }
                }
            }

            // player flashlight AND lazer pointer
            if (playerPedNEW.WeaponData.WeaponObject != null && enablePlayerFlashlight)
            {
                int weaponObjHandle = playerPedNEW.WeaponData.WeaponObject.GetHandle();

                GET_OBJECT_MODEL(weaponObjHandle, out uint weaponObjModel);
                GET_MODEL_DIMENSIONS(weaponObjModel, out Vector3 min, out Vector3 max);

                GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(weaponObjHandle, new Vector3(max.X - 0.085f, 0f, max.Z / 2f), out Vector3 offset1);
                GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(weaponObjHandle, target, out Vector3 offset2);

                if (debugCorona)
                {
                    DRAW_CORONA(offset1, 20f, 0, 0f, Color.Red);
                    DRAW_CORONA(offset2, 20f, 0, 0f, Color.Blue);
                }
  
                float volumetricScale = 1f;

                if (IVWorld.ProcessLineOfSight(offset1, offset2, out IVLineOfSightResults res, 2))
                    volumetricScale = Vector3.Distance(offset1, res.EndPosition) / target.X;

                GET_INTERIOR_FROM_CHAR(playerChar, out int inter);

                LightHelper.DrawLightCone(offset1, Vector3.Normalize(offset2 - offset1), Color.White, Intensity, Range * volumetricScale, innerConeAngle, volConeAngle, volumetricLightIntensity, volumetricScale, slot, (int)RAGE.AtStringHash("torch2"), inter, playerPedNEW.GetUIntPtr().ToUInt32());
            }

            // - - - - - FLASHLIGHT TEST END - - - - - - -

            // Get name of current mission
            //ShowSubtitleMessage(GET_STRING_FROM_TEXT_FILE(IVTheScripts.GetGlobalString(9926)));

            // - - - - - BATTLE ROYALE TEST - - - - - - -
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_J, false))
            {

                // - - - - - - - - - - - - BINOCULAR TEST - - - - - - - - - - - - - - -
                //uint model2 = RAGE.AtStringHash("csbinocular");
                //IVModelInfo.GetModelInfo(model2, out int modelIndex2);
                //IVStreaming.ScriptRequestModel((int)model2);
                //IVStreaming.LoadAllRequestedModels(false);

                //CREATE_OBJECT((int)model2, playerPos, out level1_limo, false);
                //MARK_OBJECT_AS_NO_LONGER_NEEDED(level1_limo);

                //FORCE_GAME_TELESCOPE_CAM(true);
                // - - - - - - - - - - - - BINOCULAR TEST END - - - - - - - - - - - - - - -

                return;

                if (testPed == null)
                {                
                    // Create ped from factory
                    uint model = RAGE.AtStringHash("level1_limo");
                    IVModelInfo.GetModelInfo(model, out int modelIndex);
                    IVStreaming.ScriptRequestModel((int)model);
                    IVStreaming.LoadAllRequestedModels(false);

                    REQUEST_COLLISION_FOR_MODEL(model);
                    CREATE_OBJECT((int)model, playerPos, out level1_limo, false);
                }

                // COLLISIONS_COLLISIONS_WIREFENCE_1_AW2
                // COLLISIONS_COLLISIONS_WIREFENCE_1_Bt2
                // COLLISIONS_COLLISIONS_WIREFENCE_1_C
                // COLLISIONS_COLLISIONS_WIREFENCE_1_D
                // COLLISIONS_COLLISIONS_WIREFENCE_1_E
                // COLLISIONS_COLLISIONS_WIREFENCE_1_F
                // COLLISIONS_COLLISIONS_WIREFENCE_2_A
                // COLLISIONS_COLLISIONS_WIREFENCE_2_B
                // COLLISIONS_COLLISIONS_WIREFENCE_2_C
                // COLLISIONS_COLLISIONS_WIREFENCE_2_D
                // COLLISIONS_COLLISIONS_WIREFENCE_2_Ey3
                // COLLISIONS_COLLISIONS_WIREFENCE_2_F
                // COLLISIONS_COLLISIONS_WIREFENCE_3_A
                // COLLISIONS_COLLISIONS_WIREFENCE_3_B
                // COLLISIONS_COLLISIONS_WIREFENCE_3_C
                // COLLISIONS_COLLISIONS_WIREFENCE_3_D
                // COLLISIONS_COLLISIONS_WIREFENCE_3_E
                // COLLISIONS_COLLISIONS_WIREFENCE_3_FD4

                //if (planeObj == 0)
                //{
                //    int hash = (int)RAGE.AtStringHash("ec_jet4");
                //    IVStreaming.ScriptRequestModel(hash);
                //    IVStreaming.LoadAllRequestedModels(false);

                //    Vector3 spawnPos = new Vector3(1239.474f, 2650.522f, 450f);
                //    CREATE_OBJECT(hash, spawnPos, out planeObj, true);

                //    if (planeObj != 0)
                //    {

                //        Vector3 targetPos = new Vector3(-2077.526f, -1058.722f, 450f);

                //        // Calculate direction
                //        Vector3 dir = Vector3.Normalize(spawnPos - targetPos);
                //        SET_OBJECT_HEADING(planeObj, Helper.DirectionToHeading(dir));

                //        ShowSubtitleMessage("spawned");
                //    }
                //    else
                //        ShowSubtitleMessage("could not spawn plane");
                //}
                //else
                //{
                //    ShowSubtitleMessage("already spawned");
                //}
            }
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_K, false))
            {
                if (level1_limo != 0)
                {
                    MARK_OBJECT_AS_NO_LONGER_NEEDED(level1_limo);
                    DELETE_OBJECT(ref level1_limo);
                }

                //if (planeObj != 0)
                //{
                //    DELETE_OBJECT(ref planeObj);
                //}

                PLAY_SOUND_FRONTEND(-1, "GENERAL_GPS_BONG");

                StartNewTask(() =>
                {
                    using (SpeechSynthesizer synthesizer = new SpeechSynthesizer())
                    {
                        synthesizer.SetOutputToDefaultAudioDevice();
                        //synthesizer.SelectVoice("Microsoft David Desktop"); // Needs "English (United States)" language installed on the system
                        synthesizer.SelectVoice("Microsoft Zira Desktop"); // Needs "English (United States)" language installed on the system

                        InstalledVoice[] voices = synthesizer.GetInstalledVoices().ToArray();
                        for (int i = 0; i < voices.Length; i++)
                        {
                            InstalledVoice voice = voices[i];
                            IVGame.Console.Print(string.Format("Name: {0}, Gender: {1}, Age: {2}", voice.VoiceInfo.Name, voice.VoiceInfo.Gender, voice.VoiceInfo.Age));
                        }

                        synthesizer.Volume = 80;

                        string streetName = NativeWorld.GetStreetName(playerPos).Replace("St", "Street").Replace("Ave", "Avenue").Replace("RD", "Road");
                        synthesizer.Speak(string.Format("We're approaching the last stop, please make sure you have all your belongings.", streetName));
                        synthesizer.Speak(string.Format("The next stop is, {0}.", streetName));
                    }

                    return null;
                });


            }

            //GET_CHAR_HEADING(playerChar, out float h);
            //ShowSubtitleMessage(h.ToString());

            bool isPlayerInStartArea =      IS_CHAR_IN_AREA_3D(playerChar, -507.9793f, 324.5941f, 6f, -503.9132f, 318.3172f, 10f, false);
            bool isPlayerInTriggerArea =    IS_CHAR_IN_AREA_3D(playerChar, -502.9015f, 320.2921f, 6f, -501.8107f, 317.7676f, 10f, false);

            if (isPlayerInStartArea)
            {
                // Tell player to walk to position automatically for scripted sequence
                if (playerTaskSequence == null)
                {
                    playerTaskSequence = new NativeTaskSequence();
                    playerTaskSequence.AddTask.GoTo(new Vector3(-504.1197f, 319.4015f, 6.97764f), true);
                    playerTaskSequence.AddTask.GoTo(new Vector3(-496.4236f, 319.3172f, 7.066974f), true);
                    playerTaskSequence.Perform(playerPedNEW);
                }

                // Create camera
                if (eddieCamera == null)
                {
                    eddieCamera = NativeCamera.Create();
                    eddieCamera.Position = new Vector3(-506.511f, 326.005f, 7.235f);
                    eddieCamera.Rotation = new Vector3(-1.611f, 0f, -154.030f);
                    eddieCamera.FOV = 45f;
                }

                if (!HAVE_ANIMS_LOADED("amb@shock_events"))
                    REQUEST_ANIMS("amb@shock_events");
                if (!HAVE_ANIMS_LOADED("reaction@male_flee"))
                    REQUEST_ANIMS("reaction@male_flee");
            }
            else
            {
                if (isPlayerInTriggerArea)
                {
                    // Player reached trigger area, now do eddie low stuff
                    if (eddieLowChar == 0)
                    {
                        CLEAR_CHAR_LAST_DAMAGE_BONE(playerChar);
                        skipDamageBoneCheck = false;

                        // Get offset positions of player
                        GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(playerChar, new Vector3(0f, -1.1f, 0f), out Vector3 playerBehindPos);

                        // Load models
                        int trainModel = (int)RAGE.AtStringHash("SUBWAY_HI");
                        int eddieModel = (int)RAGE.AtStringHash("IG_EDDIELOW");
                        IVStreaming.ScriptRequestModel(trainModel);
                        IVStreaming.ScriptRequestModel(eddieModel);
                        IVStreaming.LoadAllRequestedModels(false);

                        // Create eddie low char
                        Vector3 eddieSpawnPos = new Vector3(-505.9756f, 324.373f, 6.760248f);
                        CREATE_CHAR((int)ePedType.PED_TYPE_CIV_MALE, eddieModel, eddieSpawnPos, out eddieLowChar, false);

                        if (eddieLowChar == 0)
                            return;

                        // Eddie was spawned, make a audable fence noise which makes the player suspicious
                        playerPedNEW.GetTaskController().ClearAll();
                        PLAY_SOUND_FROM_POSITION(-1, "COLLISIONS_COLLISIONS_WIREFENCE_1_F", eddieSpawnPos);
                        playerPedNEW.GetAnimationController().Play("amb@shock_events", "look_over_shoulder", 4f, AnimationFlags.PlayInUpperBodyWithWalk);

                        eddieCamera.Activate();

                        GIVE_WEAPON_TO_CHAR(eddieLowChar, (int)eWeaponType.WEAPON_BASEBALLBAT, 1, true);

                        UNLOCK_RAGDOLL(eddieLowChar, false);
                        SET_CHAR_AS_MISSION_CHAR(eddieLowChar);
                        SET_CHAR_HEADING(eddieLowChar, 200f);

                        // Create task controller for this ped
                        PedTaskController eddieTaskController = PedTaskController.FromHandle(eddieLowChar);

                        // Tell eddie to go behind the player
                        eddieTaskSequence = new NativeTaskSequence();
                        eddieTaskSequence.AddTask.RunTo(playerBehindPos, true);
                        eddieTaskSequence.AddTask.TurnTo(playerPedNEW);
                        eddieTaskSequence.AddTask.FightAgainst(playerPedNEW, 2100);
                        eddieTaskSequence.Perform(eddieLowChar);

                        // reset // 25
                        TheDelayedCaller.Add(TimeSpan.FromSeconds(25d), "Main", () =>
                        {
                            // Delete train
                            if (missionTrain1 != 0)
                            {
                                MARK_MISSION_TRAIN_AS_NO_LONGER_NEEDED(missionTrain1);
                                DELETE_MISSION_TRAIN(ref missionTrain1);
                            }

                            // Delete eddie
                            if (eddieLowChar != 0)
                            {
                                MARK_CHAR_AS_NO_LONGER_NEEDED(eddieLowChar);
                                DELETE_CHAR(ref eddieLowChar);
                            }

                            SWITCH_RANDOM_TRAINS(true);
                        });
                    }
                }
            }


            if (eddieLowChar != 0 && eddieTaskSequence != null)
            {
                int progress = eddieTaskSequence.GetProgress();

                if (progress == 1)
                {
                    SAY_AMBIENT_SPEECH(eddieLowChar, "WAIT_FOR_ME", false, true, 0);

                    eddieCamera.Position = new Vector3(-497.451f, 323.285f, 8.083f);
                    eddieCamera.Rotation = new Vector3(-8.540f, 0f, 125.387f);

                    // Play look back anim
                    PedAnimationController playerAnimController = playerPedNEW.GetAnimationController();

                    if (!playerAnimController.IsPlaying("reaction@male_flee", "back"))
                        playerAnimController.Play("reaction@male_flee", "back", 2.5f);

                    //SAY_AMBIENT_SPEECH(playerChar, "SHOOT", true, true, 0);
                }

                if (!skipDamageBoneCheck && GET_CHAR_LAST_DAMAGE_BONE(playerChar, out int boneIndex))
                {
                    SWITCH_PED_TO_RAGDOLL(playerChar, 10000, -1, false, true, true, false);
                    playerPedNEW.ApplyForce(new Vector3(0, 0f, -1f));

                    DO_SCREEN_FADE_OUT(600);

                    if (!HAVE_ANIMS_LOADED("injured"))
                        REQUEST_ANIMS("injured");

                    TheDelayedCaller.Add(TimeSpan.FromSeconds(3d), "Main", () =>
                    {
                        eddieCamera.Deactivate();

                        SWITCH_PED_TO_ANIMATED(playerChar, true);

                        REMOVE_WEAPON_FROM_CHAR(eddieLowChar, (int)eWeaponType.WEAPON_BASEBALLBAT);

                        // Create train
                        CREATE_MISSION_TRAIN(0, -482.9662f, 499.6726f, -8.851006f, 0, out missionTrain1); // Left train track
                        SWITCH_RANDOM_TRAINS(false);

                        // Teleport player onto ledge and face in the right direction
                        playerPedNEW.Teleport(new Vector3(-482.8688f, 320.8487f, 11.09488f), false, true);
                        playerPedNEW.SetHeading(280f);

                        // This is just to get the player to lay on the ledge as if he was being carried on there
                        playerPedNEW.GetAnimationController().Play("injured", "inj_back_idle", 1f);

                        // Teleport eddie next to the ledge for the push down
                        SET_CHAR_COORDINATES(eddieLowChar, new Vector3(-482.7609f, 320.2921f, 10.13823f));
                        SET_CHAR_HEADING(eddieLowChar, 0f);

                        // After 1 second we activate ragdoll so player is actually laying on the ledge and is not playing an animation.
                        // This has the advantage of being able to use the awesome physics of GTA IV, to make it look like the player is being pushed down.
                        TheDelayedCaller.Add(TimeSpan.FromSeconds(1d), "Main", () =>
                        {
                            playerPedNEW.ActivateDrunkRagdoll(5000);
                            NativeCamera.GetGameCam().SetDrunkEffect(0.8f, 10000);
                            DO_SCREEN_FADE_IN(1700);
                        });

                        // After 2 seconds we push the player down and tell the train to start driving
                        TheDelayedCaller.Add(TimeSpan.FromSeconds(2.3d), "Main", () =>
                        {
                            SAY_AMBIENT_SPEECH(eddieLowChar, "TARGET", true, true, 0);

                            PedTaskController.FromHandle(eddieLowChar).PlayAnimation("ped", "open_door_shove", 2.5f, AnimationFlags.PlayInUpperBodyOnly);

                            playerPedNEW.ApplyForce(new Vector3(0f, 2.35f, 0f));

                            SET_TRAIN_CRUISE_SPEED(missionTrain1, 20f);
                            SET_TRAIN_SPEED(missionTrain1, 20f);
                        });

                        // Player should say something
                        TheDelayedCaller.Add(TimeSpan.FromSeconds(6d), "Main", () =>
                        {
                            SET_PLAYER_MOOD_PISSED_OFF((int)GET_PLAYER_ID(), 150);
                            playerPedNEW.SayAmbientSpeech("MISSION_FAIL_RAGE");
                        });

                        // Now eddie should say something and run away
                        TheDelayedCaller.Add(TimeSpan.FromSeconds(7.1d), "Main", () =>
                        {
                            SAY_AMBIENT_SPEECH(eddieLowChar, "SHOOT_AT_ENEMY", true, true, 0);
                            PedTaskController.FromHandle(eddieLowChar).RunTo(new Vector3(-464.9517f, 319.2708f, 12.83579f), true);
                        });

                    });

                    CLEAR_CHAR_LAST_DAMAGE_BONE(playerChar);
                    skipDamageBoneCheck = true;
                }
            }

            //if (planeObj != 0)
            //{
            //    GET_OBJECT_COORDINATES(planeObj, out Vector3 planeCoords);

            //    Vector3 targetPos = new Vector3(-2077.526f, -1058.722f, 450f);

            //    if (planeCoords != targetPos)
            //    {
            //        planeCoords = planeCoords.MoveTowards(targetPos, 0.5f); // 0.5f = Speed
            //        SET_OBJECT_COORDINATES(planeObj, planeCoords);
            //        playerPedNEW.Teleport(planeCoords + new Vector3(0f, 0f, 4f), false, true);
            //    }


            //}

            // - - - - - BATTLE ROYALE TEST END - - - - - - -

            return;

            if (!called)
            {

                //// get player id
                //uint playerId = GET_PLAYER_ID();

                //// get player index
                //int index = CONVERT_INT_TO_PLAYERINDEX(playerId);

                //// get player char
                //GET_PLAYER_CHAR(index, out playerChar);


                // IV-SDK "TxdExample" Example
                //IVTxdStore.PushCurrentTxd();
                //int slot = IVTxdStore.FindTxdSlot(RAGE.AtStringHash("buttons"));
                //IVTxdStore.SetCurrentTxd(slot);

                //IVSprite2D.FromUIntPtr(IVRadar.RadarRingBack).SetTexture("B_BUTT");

                //IVTxdStore.PushCurrentTxd();
                //slot = IVTxdStore.AddTxdSlot("net");
                //IVTxdStore.AddRef(slot);
                //if (IVTxdStore.LoadTxd(slot, "platform:/textures/network"))
                //{
                //    IVTxdStore.SetCurrentTxd(slot);
                //    IVSprite2D.FromUIntPtr(IVRadar.RadarRingFront).SetTexture("icon_gta");
                //}
                //IVTxdStore.PopCurrentTxd();

                called = true;
            }

            tickThreadId = Thread.CurrentThread.ManagedThreadId;

            //ShowSubtitleMessage(IVPlayerInfo.GetPlayerInfo(0).GetUIntPtr().ToUInt32().ToString("X"));

            if (playerPedNEW.WeaponData.WeaponObject != null)
            {
                //ShowSubtitleMessage("ok");
                //NativeCheckpoint.DrawCheckpoint(playerPedNEW.WeaponData.WeaponObject.Matrix.pos, 1f, Color.Red);
            }
            
            uint camHash = RAGE.AtStringHash("bm_securitycam_01a");
            uint cctvCamHash = RAGE.AtStringHash("p_cctv_1");

            uint r = GET_FRAME_COUNT();

            if (r % 100 == 0)
                lightActive = true;
            else if (r % 300 == 1)
                lightActive = false;

            // Process the queue
            TheDelayedCaller.Process();

            // Add a test delayed action to the queue which executes after 3 seconds
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_N, false))
            {
                // TimeSpan.FromSeconds(3) = Creates a "TimeSpan" object from the given seconds
                // "Main" = The name of the class that wants to add something to the queue. Useful for debugging errors.
                TheDelayedCaller.Add(TimeSpan.FromSeconds(3), "Main", () =>
                {
                    // in here do what you want
                    ShowSubtitleMessage("ok!");
                });
            }

            IVPool objPool = IVPools.GetObjectPool();
            for (int i = 0; i < objPool.Count; i++)
            {
                UIntPtr ptr = objPool.Get(i);

                if (ptr == UIntPtr.Zero)
                    continue;

                int handle = (int)objPool.GetIndex(ptr);

                GET_OBJECT_MODEL(handle, out uint model);

                // bm_securitycam_01a
                if (model == camHash)
                {
                    GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(handle, CameraLightOffset, out Vector3 pos);

                    if (lightActive)
                        DRAW_CORONA(pos, 8f, 1, 1, Color.Green);
                }

                // p_cctv_1
                if (model == cctvCamHash)
                {
                    GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(handle, CCTVCameraLightOffset, out Vector3 pos);
                    GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(handle, CCTVCameraLightOffset2, out Vector3 pos2);
                    GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(handle, CCTVCameraLightOffset3, out Vector3 pos3);


                    if (lightActive)
                    {
                        DRAW_CORONA(pos, 8f, 1, 1, Color.Green);
                        DRAW_CORONA(pos2, 8f, 1, 1, Color.Green);
                        DRAW_CORONA(pos3, 8f, 1, 1, Color.Green);
                    }
                }

            }

            Vector3 playerPosNEW = playerPedNEW.Matrix.Pos;
            heading = playerPedNEW.CurrentHeading;

            // Spawn vehicle at player position test
            // TODO: Change to not use CCL.GTAIV!
            if (IsKeyPressed(Keys.N))
            {

                //SET_LOCAL_PLAYER_VOICE("M_M_CRACKHEAD");
                //SET_LOCAL_PLAYER_PAIN_VOICE("PAIN_MALE_EXTRAS");
                //SET_PLAYER_PAIN_ROOT_BANK_NAME("PAIN_MALE");

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

        private void Main_ProcessPad(UIntPtr padPtr)
        {

        }
        private void Main_ProcessAutomobile(UIntPtr vehPtr)
        {

            return;
            IVVehicle veh = IVVehicle.FromUIntPtr(vehPtr);


            processVehicleThreadId = Thread.CurrentThread.ManagedThreadId;

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

            processCameraThreadId = Thread.CurrentThread.ManagedThreadId;

            //if (IsKeyPressed(Keys.Add))
            //    fov += 0.5f; // Zooms out
            //if (IsKeyPressed(Keys.Subtract))
            //    fov -= 0.5f; // Zooms in

            if (c != null)
            {
                //c.FOV = fov;

                // Add an offset to the camera
                // CamOffsetRight, CamOffsetUp, CamOffsetAt, CamOffsetPos
                //c.Matrix = IVMatrix.Add(c.Matrix, IVMatrix.Zero.SetPosition(CamOffsetPos));
            }
        }

        // When this script receives a script command
        private object Main_ScriptCommandReceived(Script fromScript, object[] args, string command)
        {
            IVGame.Console.PrintWarning(string.Format("Received a script command from script {0}. Command: {1}", fromScript.GetName(), command));
            return "I received the command!";
        }

        private void Main_KeyDown(object sender, KeyEventArgs e)
        {
            // Creates an explosion infront of the player
            if (e.KeyCode == Keys.NumPad9)
            {

                // Get player coordinates
                GET_CHAR_COORDINATES(playerPed, out Vector3 pos);

                // Get player heading
                GET_CHAR_HEADING(playerPed, out float heading);

                // Get position infront of player
                Vector3 v = Helper.GetPositionInFrontOfEntity(pos, Helper.HeadingToDirection(heading), 12f);

                // Create explosion
                ADD_EXPLOSION(v.X, v.Y, v.Z, (int)eExplosion.EXPLOSION_ROCKET, 10f, true, false, 0.5f);

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

                //IVPed playerPedNEW = IVPed.FromUIntPtr(IVPlayerInfo.FindThePlayerPed());

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

            if (e.KeyCode == Keys.J)
            {

            }
            if (e.KeyCode == Keys.K)
            {

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
