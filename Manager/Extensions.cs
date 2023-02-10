using System;
using System.Drawing;
using System.Numerics;

using SharpDX.Direct3D9;
using SharpDX.Mathematics.Interop;

using IVSDKDotNet.Direct3D9;

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

        // RawVector2
        public static RawVector2 ToRawVector2(this Vector2 vec)
        {
            return new RawVector2(vec.X, vec.Y);
        }

        // SharpDX.Vector2
        public static SharpDX.Vector2 ToSharpDXVector2(this Vector2 vec)
        {
            return new SharpDX.Vector2(vec.X, vec.Y);
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
