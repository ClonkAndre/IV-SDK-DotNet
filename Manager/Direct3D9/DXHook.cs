using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using SharpDX;
using SharpDX.Mathematics.Interop;
using SharpDX.Direct3D9;

using EasyHook;
using IVSDKDotNet;

namespace Manager.Direct3D9
{
    public class DXHook : IDisposable
    {

        #region Variables and Enums
        // Variables
        private List<IntPtr> d3d9DeviceVTable;
        private LocalHook endSceneHooker, resetHooker;
        private bool firstCall = true, disposedValue;
        public IntPtr DevicePtr;

        private VertexShader vertexShader;
        private PixelShader pixelShader;

        // Enums
        public enum Direct3DDevice9FunctionOrdinals : short
        {
            QueryInterface = 0,
            AddRef = 1,
            Release = 2,
            TestCooperativeLevel = 3,
            GetAvailableTextureMem = 4,
            EvictManagedResources = 5,
            GetDirect3D = 6,
            GetDeviceCaps = 7,
            GetDisplayMode = 8,
            GetCreationParameters = 9,
            SetCursorProperties = 10,
            SetCursorPosition = 11,
            ShowCursor = 12,
            CreateAdditionalSwapChain = 13,
            GetSwapChain = 14,
            GetNumberOfSwapChains = 15,
            Reset = 16,
            Present = 17,
            GetBackBuffer = 18,
            GetRasterStatus = 19,
            SetDialogBoxMode = 20,
            SetGammaRamp = 21,
            GetGammaRamp = 22,
            CreateTexture = 23,
            CreateVolumeTexture = 24,
            CreateCubeTexture = 25,
            CreateVertexBuffer = 26,
            CreateIndexBuffer = 27,
            CreateRenderTarget = 28,
            CreateDepthStencilSurface = 29,
            UpdateSurface = 30,
            UpdateTexture = 31,
            GetRenderTargetData = 32,
            GetFrontBufferData = 33,
            StretchRect = 34,
            ColorFill = 35,
            CreateOffscreenPlainSurface = 36,
            SetRenderTarget = 37,
            GetRenderTarget = 38,
            SetDepthStencilSurface = 39,
            GetDepthStencilSurface = 40,
            BeginScene = 41,
            EndScene = 42,
            Clear = 43,
            SetTransform = 44,
            GetTransform = 45,
            MultiplyTransform = 46,
            SetViewport = 47,
            GetViewport = 48,
            SetMaterial = 49,
            GetMaterial = 50,
            SetLight = 51,
            GetLight = 52,
            LightEnable = 53,
            GetLightEnable = 54,
            SetClipPlane = 55,
            GetClipPlane = 56,
            SetRenderState = 57,
            GetRenderState = 58,
            CreateStateBlock = 59,
            BeginStateBlock = 60,
            EndStateBlock = 61,
            SetClipStatus = 62,
            GetClipStatus = 63,
            GetTexture = 64,
            SetTexture = 65,
            GetTextureStageState = 66,
            SetTextureStageState = 67,
            GetSamplerState = 68,
            SetSamplerState = 69,
            ValidateDevice = 70,
            SetPaletteEntries = 71,
            GetPaletteEntries = 72,
            SetCurrentTexturePalette = 73,
            GetCurrentTexturePalette = 74,
            SetScissorRect = 75,
            GetScissorRect = 76,
            SetSoftwareVertexProcessing = 77,
            GetSoftwareVertexProcessing = 78,
            SetNPatchMode = 79,
            GetNPatchMode = 80,
            DrawPrimitive = 81,
            DrawIndexedPrimitive = 82,
            DrawPrimitiveUP = 83,
            DrawIndexedPrimitiveUP = 84,
            ProcessVertices = 85,
            CreateVertexDeclaration = 86,
            SetVertexDeclaration = 87,
            GetVertexDeclaration = 88,
            SetFVF = 89,
            GetFVF = 90,
            CreateVertexShader = 91,
            SetVertexShader = 92,
            GetVertexShader = 93,
            SetVertexShaderConstantF = 94,
            GetVertexShaderConstantF = 95,
            SetVertexShaderConstantI = 96,
            GetVertexShaderConstantI = 97,
            SetVertexShaderConstantB = 98,
            GetVertexShaderConstantB = 99,
            SetStreamSource = 100,
            GetStreamSource = 101,
            SetStreamSourceFreq = 102,
            GetStreamSourceFreq = 103,
            SetIndices = 104,
            GetIndices = 105,
            CreatePixelShader = 106,
            SetPixelShader = 107,
            GetPixelShader = 108,
            SetPixelShaderConstantF = 109,
            GetPixelShaderConstantF = 110,
            SetPixelShaderConstantI = 111,
            GetPixelShaderConstantI = 112,
            SetPixelShaderConstantB = 113,
            GetPixelShaderConstantB = 114,
            DrawRectPatch = 115,
            DrawTriPatch = 116,
            DeletePatch = 117,
            CreateQuery = 118,
        }
        #endregion

        #region Delegates and Events

        #region Delegates
        // Hooking Delegates
        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Unicode, SetLastError = true)]
        private delegate int EndSceneHookDelegate(IntPtr devicePtr);

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Unicode, SetLastError = true)]
        private delegate int ResetHookDelegate(IntPtr devicePtr, IntPtr pPresentParameters);

        // Other
        public delegate void D3D9DeviveDelegate(IntPtr device);
        public delegate void D3D9DeviveResetDelegate(IntPtr device, IntPtr presentParameters);
        #endregion

        #region Events
        public event EventHandler OnDispose;
        public event EventHandler OnDisposed;

        public event D3D9DeviveDelegate OnInit;
        public event D3D9DeviveDelegate OnEndScene;
        public event D3D9DeviveResetDelegate OnBeforeReset;
        public event D3D9DeviveDelegate OnAfterReset;
        #endregion

        #endregion

        #region Constructor
        public DXHook()
        {
            d3d9DeviceVTable = new List<IntPtr>();
        }
        #endregion

        #region Disposing
        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue) {
                OnDispose?.Invoke(this, EventArgs.Empty);

                if (disposing) {
                    if (d3d9DeviceVTable != null) {
                        d3d9DeviceVTable.Clear();
                        d3d9DeviceVTable = null;
                    }
                    if (endSceneHooker != null) {
                        endSceneHooker.Dispose();
                        endSceneHooker = null;
                    }
                    if (resetHooker != null) {
                        resetHooker.Dispose();
                        resetHooker = null;
                    }
                }

                disposedValue = true;

                OnDisposed?.Invoke(this, EventArgs.Empty);
            }
        }

        public void Dispose()
        {
            // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }
        #endregion

        #region Methods
        /// <summary>
        /// Initializes the Direct3D9 Hook.
        /// </summary>
        /// <param name="hWnd">The hWnd pointer of GTA IV.</param>
        /// <exception cref="ObjectDisposedException">Thrown when the <see cref="DXHook"/> class was disposed.</exception>
        /// <exception cref="NullReferenceException">Thrown when the hWnd pointer received is null.</exception>
        /// <exception cref="Exception">Thrown when the hWnd pointer received is <see cref="IntPtr.Zero"/>.</exception>
        public void Init(IntPtr hWnd)
        {
            if (disposedValue)
                throw new ObjectDisposedException("This class was disposed.");

            // Validate hWnd pointer
            if (hWnd == null)
                throw new NullReferenceException("hWnd pointer is null.");
            if (hWnd == IntPtr.Zero)
                throw new Exception("hWnd pointer is invalid.");

            // Create dummy window, to get a dummy device, so we can get the vtable from that device.
            Main.Instance.Console.PrintDebug("[DXHook] Getting Device VTable.");
            using (Direct3D d3d = new Direct3D())
            {
                using (System.Windows.Forms.Form renderForm = new System.Windows.Forms.Form())
                {
                    using (Device tempDevice = new Device(d3d, 0, DeviceType.NullReference, IntPtr.Zero, CreateFlags.HardwareVertexProcessing, new PresentParameters() { BackBufferWidth = 1, BackBufferHeight = 1, DeviceWindowHandle = renderForm.Handle }))
                    {
                        d3d9DeviceVTable.AddRange(GetVTblAddresses(tempDevice.NativePointer, 119));
                    }
                }
            }

            //d3d9DeviceVTable.AddRange(GetVTblAddresses(RAGE.GetDirect3DDevice9(), 119));

            //CreateShaders();

            // Hooking stuff.
            Main.Instance.Console.PrintDebug("[DXHook] Hooking EndScene.");
            endSceneHooker = LocalHook.Create(d3d9DeviceVTable[(int)Direct3DDevice9FunctionOrdinals.EndScene], new EndSceneHookDelegate(EndSceneHook), this);
            endSceneHooker.ThreadACL.SetExclusiveACL(new int[1]);

            Main.Instance.Console.PrintDebug("[DXHook] Hooking Reset.");
            resetHooker = LocalHook.Create(d3d9DeviceVTable[(int)Direct3DDevice9FunctionOrdinals.Reset], new ResetHookDelegate(ResetHook), this);
            resetHooker.ThreadACL.SetExclusiveACL(new int[1]);

            // Log
            Main.Instance.Console.PrintDebug("[DXHook] Done!");
        }

        public void CreateShaders()
        {
            Device d = (Device)RAGE.GetDirect3DDevice9();

            // Vertex Shader
            string vertexShaderSource =
                @"uniform float4x4 Projection : register(c0);\
                struct VSIn\
                {\
                	float3 Position : POSITION;\
                	float4 Color : COLOR;\
                	float2 UV : TEXCOORD0;\
                };\
                struct VSOut\
                {\
                    float4 Position : POSITION;\
                    float4 Color : COLOR;\
                    float2 UV : TEXCOORD0;\
                };\
                \
                VSOut main(VSIn vsIn)\
                {\
                    VSOut vsOut;\
                    vsOut.Position = mul(Projection, float4(vsIn.Position.xyz, 1.0));\
                    vsOut.Color = vsIn.Color;\
                    vsOut.UV = vsIn.UV;\
                    \
                    return vsOut;\
                }
                ";

            CompilationResult vertexShaderCompResult = ShaderBytecode.Compile(vertexShaderSource, "main", "vs_3_0", ShaderFlags.None, null, null);
            vertexShader = new VertexShader(d, vertexShaderCompResult.Bytecode);

            // Pixel shader
            string pixelShaderSource =
                @"uniform sampler2D TextureSampler : register(s0);\
                \
                struct PSIn\
                {\
                    float4 Color : COLOR;\
                    float2 UV : TEXCOORD0;\
                };\
                \
                float4 main(PSIn psIn) : COLOR\
                {\
                    float4 outColor = tex2D(TextureSampler, psIn.UV) * psIn.Color;\
                    return outColor;\
                }";

            CompilationResult pixelShaderCompResult = ShaderBytecode.Compile(pixelShaderSource, "main", "ps_3_0", ShaderFlags.None, null, null);
            pixelShader = new PixelShader(d, pixelShaderCompResult.Bytecode);

            // VertexDeclaration
            VertexElement[] vertexDeclElements = new VertexElement[4] {

                new VertexElement(0, 0, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.Position, 0),
                new VertexElement(0, 12, DeclarationType.Color, DeclarationMethod.Default, DeclarationUsage.Color, 0),
                new VertexElement(0, 16, DeclarationType.Float2, DeclarationMethod.Default, DeclarationUsage.TextureCoordinate, 0),
                VertexElement.VertexDeclarationEnd

            };
            VertexDeclaration vertexDeclaration = new VertexDeclaration(d, vertexDeclElements);
        }
        public void SetupDeviceRenderState()
        {
            Device d = (Device)RAGE.GetDirect3DDevice9();
            d.VertexShader = vertexShader;
            d.PixelShader = pixelShader;
            d.SetRenderState(RenderState.ZWriteEnable, false);
            d.SetRenderState(RenderState.AlphaTestEnable, false);
            d.SetRenderState(RenderState.CullMode, Cull.None);
            d.SetRenderState(RenderState.ZEnable, false);
            d.SetRenderState(RenderState.AlphaBlendEnable, true);
            d.SetRenderState(RenderState.BlendOperation, BlendOperation.Add);
            d.SetRenderState(RenderState.SourceBlend, Blend.SourceAlpha);
            d.SetRenderState(RenderState.DestinationBlend, Blend.InverseSourceAlpha);
            d.SetRenderState(RenderState.SeparateAlphaBlendEnable, true);
            d.SetRenderState(RenderState.SourceBlendAlpha, Blend.One);
            d.SetRenderState(RenderState.DestinationBlendAlpha, Blend.InverseSourceAlpha);
            d.SetRenderState(RenderState.ScissorTestEnable, true);
            d.SetSamplerState(0, SamplerState.MinFilter, TextureFilter.Linear);
            d.SetSamplerState(0, SamplerState.MagFilter, TextureFilter.Linear);
        }
        #endregion

        #region Functions
        private IntPtr[] GetVTblAddresses(IntPtr pointer, int numberOfMethods)
        {
            if (disposedValue)
                throw new ObjectDisposedException("This class was disposed.");

            List<IntPtr> vtblAddresses = new List<IntPtr>();
            IntPtr vTable = Marshal.ReadIntPtr(pointer);
            for (int i = 0; i < numberOfMethods; i++)
                vtblAddresses.Add(Marshal.ReadIntPtr(vTable, i * IntPtr.Size));
            return vtblAddresses.ToArray();
        }
        #endregion

        #region Hooks
        private int EndSceneHook(IntPtr devicePtr)
        {
            DevicePtr = devicePtr;
            Device dev = (Device)devicePtr;

            if (firstCall)
            {
                OnInit?.Invoke(devicePtr);
                firstCall = false;
            }

            OnEndScene?.Invoke(devicePtr);

            dev.EndScene();
            return Result.Ok.Code;
        }
        private int ResetHook(IntPtr devicePtr, IntPtr pPresentParameters)
        {
            Device dev = (Device)devicePtr;

            OnBeforeReset?.Invoke(devicePtr, pPresentParameters);
            dev.Reset(Marshal.PtrToStructure<PresentParameters>(pPresentParameters));
            OnAfterReset?.Invoke(devicePtr);

            return Result.Ok.Code;
        }
        #endregion

    }

}
