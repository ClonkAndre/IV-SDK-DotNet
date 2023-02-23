using System;
using System.Drawing;
using System.Numerics;

using SharpDX.Direct3D9;
using SharpDX.Mathematics.Interop;

using IVSDKDotNet.Direct3D9;
using System.Runtime.Remoting.Messaging;

namespace Manager {
    internal static class Extensions {

        // RawColorBGRA
        public static RawColorBGRA ToRawColorBGRA(this Color color)
        {
            return new RawColorBGRA(color.B, color.G, color.R, color.A);
        }

        // RawVector3
        public static RawVector3 ToRawVector3(this PointF pointF)
        {
            return new RawVector3(pointF.X, pointF.Y, 0f);
        }
        public static RawVector3 ToRawVector3(this Vector2 vec)
        {
            return new RawVector3(vec.X, vec.Y, 0f);
        }

        public static RawVector3 ToRawVector3(this Vector3 vec)
        {
            return new RawVector3(vec.X, vec.Y, vec.Z);
        }

        // RawMatrix
        public static float[] GetValues(this RawMatrix m)
        {
            float[] v = new float[16];
            v[0]    = m.M11;
            v[1]    = m.M12;
            v[2]    = m.M13;
            v[3]    = m.M14;
            v[4]    = m.M21;
            v[5]    = m.M22;
            v[6]    = m.M23;
            v[7]    = m.M24;
            v[8]    = m.M31;
            v[9]    = m.M32;
            v[10]   = m.M33;
            v[11]   = m.M34;
            v[12]   = m.M41;
            v[13]   = m.M42;
            v[14]   = m.M43;
            v[15]   = m.M44;
            return v;
        }

        // RawVector2
        public static RawVector2 ToRawVector2(this Vector2 vec)
        {
            return new RawVector2(vec.X, vec.Y);
        }

        // RawRectangle
        public static RawRectangle ToRawRectangle(this Rectangle rect)
        {
            return new RawRectangle(rect.Left, rect.Top, rect.Right, rect.Bottom);
        }

        // SharpDX.Vector2
        public static SharpDX.Vector2 ToSharpDXVector2(this Vector2 vec)
        {
            return new SharpDX.Vector2(vec.X, vec.Y);
        }

        // SharpDX.Vector3
        public static SharpDX.Vector3 ToSharpDXVector3(this Vector3 vec)
        {
            return new SharpDX.Vector3(vec.X, vec.Y, vec.Z);
        }
        public static Vector3 ToVector3(this SharpDX.Vector3 vec)
        {
            return new Vector3(vec.X, vec.Y, vec.Z);
        }

        // PresentParameters
        public static PresentParameters ToSharpDXPresentParameters(this D3DPresentParameters d)
        {
            PresentParameters p = new PresentParameters();
            p.BackBufferWidth = d.BackBufferWidth;
            p.BackBufferHeight = d.BackBufferHeight;
            p.BackBufferFormat = (Format)d.BackBufferFormat;
            p.BackBufferCount = d.BackBufferCount;
            p.MultiSampleType = (MultisampleType)d.MultiSampleType;
            p.MultiSampleQuality = d.MultiSampleQuality;
            p.SwapEffect = (SwapEffect)d.SwapEffect;
            p.DeviceWindowHandle = d.DeviceWindowHandle;
            p.Windowed = d.Windowed;
            p.EnableAutoDepthStencil = d.EnableAutoDepthStencil;
            p.AutoDepthStencilFormat = (Format)d.AutoDepthStencilFormat;
            p.PresentFlags = (PresentFlags)d.PresentFlags;
            p.FullScreenRefreshRateInHz = d.FullScreenRefreshRateInHz;
            p.PresentationInterval = (PresentInterval)d.PresentationInterval;
            return p;
        }
        public static D3DPresentParameters ToD3DPresentParameters(this PresentParameters d)
        {
            D3DPresentParameters p = new D3DPresentParameters();
            p.BackBufferWidth = d.BackBufferWidth;
            p.BackBufferHeight = d.BackBufferHeight;
            p.BackBufferFormat = (int)d.BackBufferFormat;
            p.BackBufferCount = d.BackBufferCount;
            p.MultiSampleType = (int)d.MultiSampleType;
            p.MultiSampleQuality = d.MultiSampleQuality;
            p.SwapEffect = (int)d.SwapEffect;
            p.DeviceWindowHandle = d.DeviceWindowHandle;
            p.Windowed = d.Windowed;
            p.EnableAutoDepthStencil = d.EnableAutoDepthStencil;
            p.AutoDepthStencilFormat = (int)d.AutoDepthStencilFormat;
            p.PresentFlags = (int)d.PresentFlags;
            p.FullScreenRefreshRateInHz = d.FullScreenRefreshRateInHz;
            p.PresentationInterval = (int)d.PresentationInterval;
            return p;
        }

        // FontDescription
        public static FontDescription ToSharpDXFontDescription(this D3DFontDescription d)
        {
            FontDescription f = new FontDescription();
            f.FaceName = d.FaceName;
            f.Width = d.Width;
            f.Height = d.Height;
            f.MipLevels = d.MipLevels;
            f.Italic = d.Italic;
            f.Weight = (FontWeight)d.FontWeight;
            f.Quality = (FontQuality)d.FontQuality;
            f.OutputPrecision = (FontPrecision)d.FontPrecision;
            f.CharacterSet = (FontCharacterSet)d.FontCharSet;
            f.PitchAndFamily = (FontPitchAndFamily)d.FontPitchAndFamily;
            return f;
        }

    }
}
