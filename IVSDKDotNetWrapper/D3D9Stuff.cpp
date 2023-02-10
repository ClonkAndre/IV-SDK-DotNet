#include "pch.h"
#include "D3D9Stuff.h"

namespace IVSDKDotNet {
	namespace Direct3D9 {

		// D3DFontDescription
		D3DFontDescription::D3DFontDescription(String^ faceName, int width, int height, int mipLevels, eD3DFontWeight weight, bool italic, eD3DFontQuality quality, eD3DFontPrecision precision, eD3DFontCharacterSet charSet, eD3DFontPitchAndFamily pitchAndFamily)
		{
			FaceName = faceName;
			Width = width;
			Height = height;
			MipLevels = mipLevels;
			FontWeight = weight;
			Italic = italic;
			FontQuality = quality;
			FontPrecision = precision;
			FontCharSet = charSet;
			FontPitchAndFamily = pitchAndFamily;
		}
		D3DFontDescription::D3DFontDescription(String^ faceName, int width, int height, eD3DFontWeight weight, bool italic, eD3DFontQuality quality, eD3DFontPrecision precision, eD3DFontCharacterSet charSet, eD3DFontPitchAndFamily pitchAndFamily)
		{
			FaceName = faceName;
			Width = width;
			Height = height;
			MipLevels = 1;
			FontWeight = weight;
			Italic = italic;
			FontQuality = quality;
			FontPrecision = precision;
			FontCharSet = charSet;
			FontPitchAndFamily = pitchAndFamily;
		}
		D3DFontDescription::D3DFontDescription(String^ faceName, int width, int height, eD3DFontWeight weight, bool italic, eD3DFontQuality quality, eD3DFontPrecision precision)
		{
			FaceName = faceName;
			Width = width;
			Height = height;
			MipLevels = 1;
			FontWeight = weight;
			Italic = italic;
			FontQuality = quality;
			FontPrecision = precision;
			FontCharSet = eD3DFontCharacterSet::Default;
			FontPitchAndFamily = eD3DFontPitchAndFamily::Default;
		}
		D3DFontDescription::D3DFontDescription(String^ faceName, int height, eD3DFontWeight weight, bool italic, eD3DFontQuality quality)
		{
			FaceName = faceName;
			Width = 0;
			Height = height;
			MipLevels = 1;
			FontWeight = weight;
			Italic = italic;
			FontQuality = quality;
			FontPrecision = eD3DFontPrecision::Default;
			FontCharSet = eD3DFontCharacterSet::Default;
			FontPitchAndFamily = eD3DFontPitchAndFamily::Default;
		}
		D3DFontDescription::D3DFontDescription(String^ faceName, int height, eD3DFontWeight weight, bool italic)
		{
			FaceName = faceName;
			Width = 0;
			Height = height;
			MipLevels = 1;
			FontWeight = weight;
			Italic = italic;
			FontQuality = eD3DFontQuality::Default;
			FontPrecision = eD3DFontPrecision::Default;
			FontCharSet = eD3DFontCharacterSet::Default;
			FontPitchAndFamily = eD3DFontPitchAndFamily::Default;
		}
		D3DFontDescription::D3DFontDescription(String^ faceName, int height)
		{
			FaceName = faceName;
			Width = 0;
			Height = height;
			MipLevels = 1;
			FontWeight = eD3DFontWeight::Normal;
			Italic = false;
			FontQuality = eD3DFontQuality::Default;
			FontPrecision = eD3DFontPrecision::Default;
			FontCharSet = eD3DFontCharacterSet::Default;
			FontPitchAndFamily = eD3DFontPitchAndFamily::Default;
		}

		D3DFontDescription D3DFontDescription::Default()
		{
			D3DFontDescription d;
			d.FaceName = "Arial";
			d.Width = 0;
			d.Height = 20;
			d.MipLevels = 1;
			d.FontWeight = eD3DFontWeight::Normal;
			d.Italic = false;
			d.FontQuality = eD3DFontQuality::Default;
			d.FontPrecision = eD3DFontPrecision::Default;
			d.FontCharSet = eD3DFontCharacterSet::Default;
			d.FontPitchAndFamily = eD3DFontPitchAndFamily::Default;
			return d;
		}

		// D3DPresentParameters
		D3DPresentParameters::D3DPresentParameters(int backBufferWidth, int backBufferHeight, int backBufferFormat, int backBufferCount, int multiSampleType, int multiSampleQuality, int swapEffect, IntPtr deviceWindowHandle, bool windowed, bool enableAutoDepthStencil, int autoDepthStencilFormat, int presentFlags, int fullScreenRefreshRateInHz, int presentationInterval)
		{
			BackBufferWidth = backBufferWidth;
			BackBufferHeight = backBufferHeight;
			BackBufferFormat = backBufferFormat;
			BackBufferCount = backBufferCount;
			MultiSampleType = multiSampleType;
			MultiSampleQuality = multiSampleQuality;
			SwapEffect = swapEffect;
			DeviceWindowHandle = deviceWindowHandle;
			Windowed = windowed;
			EnableAutoDepthStencil = enableAutoDepthStencil;
			AutoDepthStencilFormat = autoDepthStencilFormat;
			PresentFlags = presentFlags;
			FullScreenRefreshRateInHz = fullScreenRefreshRateInHz;
			PresentationInterval = presentationInterval;
		}

		D3DPresentParameters D3DPresentParameters::Default()
		{
			D3DPresentParameters d;
			d.BackBufferWidth = 800;
			d.BackBufferHeight = 600;
			d.BackBufferFormat = 22;
			d.BackBufferCount = 1;
			d.MultiSampleType = 0;
			d.MultiSampleQuality = 1;
			d.SwapEffect = 1;
			d.DeviceWindowHandle = IntPtr::Zero;
			d.Windowed = true;
			d.EnableAutoDepthStencil = true;
			d.AutoDepthStencilFormat = 77;
			d.PresentFlags = 0;
			d.PresentationInterval = int::MinValue;
			return d;
		}

	}
}