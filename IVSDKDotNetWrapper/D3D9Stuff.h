#pragma once

namespace IVSDKDotNet {
	namespace Direct3D9 {

		// Enums
		public enum class eD3D9ResourceType
		{
			/// <summary>
			/// Specifies that the resource is a texture resource.
			/// </summary>
			Texture,
			/// <summary>
			/// Specifies that the resource is a font resource.
			/// </summary>
			Font
		};
		public enum class eD3DFontWeight
		{
			/// <summary>
			/// Use a black weight.
			/// </summary>
			Black = 900,
			/// <summary>
			/// Use a bold weight.
			/// </summary>
			Bold = 700,
			/// <summary>
			/// Use a demi-bold weight.
			/// </summary>
			DemiBold = 600,
			/// <summary>
			/// The font weight doesn't matter.
			/// </summary>
			DoNotCare = 0,
			/// <summary>
			/// Use an extra bold weight.
			/// </summary>
			ExtraBold = 800,
			/// <summary>
			/// Make the font extra light.
			/// </summary>
			ExtraLight = 200,
			/// <summary>
			/// Use a heavy weight.
			/// </summary>
			Heavy = 900,
			/// <summary>
			/// Make the font light.
			/// </summary>
			Light = 300,
			/// <summary>
			/// Use a medium weight.
			/// </summary>
			Medium = 500,
			/// <summary>
			/// Use a normal weight.
			/// </summary>
			Normal = 400,
			/// <summary>
			/// Use a regular weight.
			/// </summary>
			Regular = 400,
			/// <summary>
			/// Use a semi-bold weight.
			/// </summary>
			SemiBold = 600,
			/// <summary>
			/// Make the font thin.
			/// </summary>
			Thin = 100,
			/// <summary>
			/// Use an ultra bold weight.
			/// </summary>
			UltraBold = 800,
			/// <summary>
			/// Make the font ultra light.
			/// </summary>
			UltraLight = 200
		};
		public enum class eD3DFontCharacterSet : Byte
		{
			/// <summary>
			/// The ANSI character set.
			/// </summary>
			Ansi = 0,
			/// <summary>
			/// The Arabic character set.
			/// </summary>
			Arabic = 178,
			/// <summary>
			/// The Baltic character set.
			/// </summary>
			Baltic = 186,
			/// <summary>
			/// The Chinese character set.
			/// </summary>
			ChineseBig5 = 136,
			/// <summary>
			/// The default system character set.
			/// </summary>
			Default = 1,
			/// <summary>
			/// The East Europe character set.
			/// </summary>
			EastEurope = 238,
			/// <summary>
			/// The GB2312 character set.
			/// </summary>
			GB2312 = 134,
			/// <summary>
			/// The Greek character set.
			/// </summary>
			Greek = 161,
			/// <summary>
			/// The Hangul character set.
			/// </summary>
			Hangul = 129,
			/// <summary>
			/// The Hebrew character set.
			/// </summary>
			Hebrew = 177,
			/// <summary>
			/// The Johab character set.
			/// </summary>
			Johab = 130,
			/// <summary>
			/// The Mac character set.
			/// </summary>
			Mac = 77,
			/// <summary>
			/// The OEM character set.
			/// </summary>
			Oem = Byte::MaxValue,
			/// <summary>
			/// The Russian character set.
			/// </summary>
			Russian = 204,
			/// <summary>
			/// The ShiftJIS character set.
			/// </summary>
			ShiftJIS = 0x80,
			/// <summary>
			/// The symbol character set.
			/// </summary>
			Symbol = 2,
			/// <summary>
			/// The Thai character set.
			/// </summary>
			Thai = 222,
			/// <summary>
			/// The Turkish character set.
			/// </summary>
			Turkish = 162,
			/// <summary>
			/// The Vietnamese character set.
			/// </summary>
			Vietnamese = 163
		};
		public enum class eD3DFontPrecision : Byte
		{
			/// <summary>
			/// Default
			/// </summary>
			Default,
			/// <summary>
			/// String
			/// </summary>
			String,
			/// <summary>
			/// Character
			/// </summary>
			Character,
			/// <summary>
			/// Stroke
			/// </summary>
			Stroke,
			/// <summary>
			/// TrueType
			/// </summary>
			TrueType,
			/// <summary>
			/// Device
			/// </summary>
			Device,
			/// <summary>
			/// Raster
			/// </summary>
			Raster,
			/// <summary>
			/// TrueTypeOnly
			/// </summary>
			TrueTypeOnly,
			/// <summary>
			/// Outline
			/// </summary>
			Outline,
			/// <summary>
			/// ScreenOutline
			/// </summary>
			ScreenOutline,
			/// <summary>
			/// PostScriptOnly
			/// </summary>
			PostScriptOnly
		};
		public enum class eD3DFontQuality : Byte
		{
			/// <summary>
			/// Default
			/// </summary>
			Default,
			/// <summary>
			/// Draft
			/// </summary>
			Draft,
			/// <summary>
			/// Proof
			/// </summary>
			Proof,
			/// <summary>
			/// Non antialiased
			/// </summary>
			NonAntialiased,
			/// <summary>
			/// Antialiased
			/// </summary>
			Antialiased,
			/// <summary>
			/// ClearType
			/// </summary>
			ClearType,
			/// <summary>
			/// ClearTypeNatural
			/// </summary>
			ClearTypeNatural
		};
		public enum class eD3DFontPitchAndFamily : Byte
		{
			/// <summary>
			/// Use the Decorative family.
			/// </summary>
			Decorative = 0x50,
			/// <summary>
			/// Default pitch.
			/// </summary>
			Default = 0x0,
			/// <summary>
			/// The font family doesn't matter.
			/// </summary>
			DontCare = 0x0,
			/// <summary>
			/// Fixed pitch.
			/// </summary>
			Fixed = 0x1,
			/// <summary>
			/// Use the Modern family.
			/// </summary>
			Modern = 0x30,
			/// <summary>
			/// Mono pitch.
			/// </summary>
			Mono = 0x8,
			/// <summary>
			/// Use the Roman family.
			/// </summary>
			Roman = 0x10,
			/// <summary>
			/// Use the Script family.
			/// </summary>
			Script = 0x40,
			/// <summary>
			/// Use the Swiss family.
			/// </summary>
			Swiss = 0x20,
			/// <summary>
			/// Variable pitch.
			/// </summary>
			Variable = 0x2
		};
		public enum class eD3DCircleType
		{
			Full = 0,
			Half,
			Quarter
		};
		public enum class eD3DFontDrawFlags
		{
			/// <summary>
			/// Align the text to the bottom.
			/// </summary>
			Bottom = 0x8,
			/// <summary>
			/// Align the text to the center.
			/// </summary>
			Center = 0x1,
			/// <summary>
			/// Expand tab characters.
			/// </summary>
			ExpandTabs = 0x40,
			/// <summary>
			/// Align the text to the left.
			/// </summary>
			Left = 0x0,
			/// <summary>
			/// Don't clip the text.
			/// </summary>
			NoClip = 0x100,
			/// <summary>
			/// Align the text to the right.
			/// </summary>
			Right = 0x2,
			/// <summary>
			/// Rendering the text in right-to-left reading order.
			/// </summary>
			RtlReading = 0x20000,
			/// <summary>
			/// Force all text to a single line.
			/// </summary>
			SingleLine = 0x20,
			/// <summary>
			/// Align the text to the top.
			/// </summary>
			Top = 0x0,
			/// <summary>
			/// Vertically align the text to the center.
			/// </summary>
			VerticalCenter = 0x4,
			/// <summary>
			/// Allow word breaks.
			/// </summary>
			WordBreak = 0x10
		};

		// Structs
		public value class D3DPresentParameters
		{
		public:
			D3DPresentParameters(int backBufferWidth, int backBufferHeight, int backBufferFormat, int backBufferCount, int multiSampleType, int multiSampleQuality, int swapEffect, IntPtr deviceWindowHandle, bool windowed, bool enableAutoDepthStencil, int autoDepthStencilFormat, int presentFlags, int fullScreenRefreshRateInHz, int presentationInterval);

			/// <summary>
			/// Creates a D3DPresentParameters object with default values.
			/// </summary>
			/// <returns>The D3DPresentParameters object.</returns>
			static D3DPresentParameters Default();

			/// <summary>
			/// Width of the new swap chain's back buffers, in pixels. If Windowed is SharpDX.Result.False
			/// (the presentation is full-screen), this value must equal the width of one of
			/// the enumerated display modes found through EnumAdapterModes. If Windowed is TRUE
			/// and either BackBufferWidth or BackBufferHeight is zero, the corresponding dimension
			/// of the client area of the hDeviceWindow (or the focus window, if hDeviceWindow
			/// is null) is taken.
			/// </summary>
			int BackBufferWidth;

			/// <summary>
			/// Height of the new swap chain's back buffers, in pixels. If Windowed is SharpDX.Result.False
			/// (the presentation is full-screen), this value must equal the height of one of
			/// the enumerated display modes found through EnumAdapterModes. If Windowed is TRUE
			/// and either BackBufferWidth or BackBufferHeight is zero, the corresponding dimension
			/// of the client area of the hDeviceWindow (or the focus window, if hDeviceWindow
			/// is null) is taken.
			/// </summary>
			int BackBufferHeight;

			/// <summary>
			/// The back buffer format. For more information about formats, see SharpDX.Direct3D9.Format.
			/// This value must be one of the render-target formats as validated by CheckDeviceType.
			/// You can use GetDisplayMode to obtain the current format. In fact, SharpDX.Direct3D9.Format.Unknown
			/// can be specified for the BackBufferFormat while in windowed mode. This tells
			/// the runtime to use the current display-mode format and eliminates the need to
			/// call GetDisplayMode. For windowed applications, the back buffer format no longer
			/// needs to match the display-mode format because color conversion can now be done
			/// by the hardware (if the hardware supports color conversion). The set of possible
			/// back buffer formats is constrained, but the runtime will allow any valid back
			/// buffer format to be presented to any desktop format. (There is the additional
			/// requirement that the device be operable in the desktop; devices typically do
			/// not operate in 8 bits per pixel modes.) Full-screen applications cannot do color
			/// conversion.
			/// </summary>
			int BackBufferFormat;

			/// <summary>
			/// This value can be between 0 and SharpDX.Direct3D9.Present.BackBuffersMaximum
			/// (or SharpDX.Direct3D9.Present.BackBuffersMaximumEx when using Direct3D 9Ex).
			/// Values of 0 are treated as 1. If the number of back buffers cannot be created,
			/// the runtime will fail the method call and fill this value with the number of
			/// back buffers that could be created. As a result, an application can call the
			/// method twice with the same SharpDX.Direct3D9.PresentParameters structure and
			/// expect it to work the second time. The method fails if one back buffer cannot
			/// be created. The value of BackBufferCount influences what set of swap effects
			/// are allowed. Specifically, any SharpDX.Direct3D9.SwapEffect.Copy swap effect
			/// requires that there be exactly one back buffer.
			/// </summary>
			int BackBufferCount;

			/// <summary>
			/// Member of the SharpDX.Direct3D9.MultisampleType enumerated type. The value must
			/// be SharpDX.Direct3D9.MultisampleType.None unless SwapEffect has been set to SharpDX.Direct3D9.SwapEffect.Discard.
			/// Multisampling is supported only if the swap effect is SharpDX.Direct3D9.SwapEffect.Discard.
			/// </summary>
			int MultiSampleType;

			/// <summary>
			/// Quality level. The valid range is between zero and one less than the level returned
			/// by pQualityLevels used by CheckDeviceMultiSampleType. Passing a larger value
			/// returns the error SharpDX.Direct3D9.ResultCode.InvalidCall. Paired values of
			/// render targets or of depth stencil surfaces and SharpDX.Direct3D9.MultisampleType
			/// must match.
			/// </summary>
			int MultiSampleQuality;

			/// <summary>
			/// Member of the SharpDX.Direct3D9.SwapEffect enumerated type. The runtime will
			/// guarantee the implied semantics concerning buffer swap behavior; therefore, if
			/// Windowed is TRUE and SwapEffect is set to SharpDX.Direct3D9.SwapEffect.Flip,
			/// the runtime will create one extra back buffer and copy whichever becomes the
			/// front buffer at presentation time. SharpDX.Direct3D9.SwapEffect.Copy requires
			/// that BackBufferCount be set to 1. SharpDX.Direct3D9.SwapEffect.Discard will be
			/// enforced in the debug runtime by filling any buffer with noise after it is presented.
			/// Differences between Direct3D9 and Direct3D9Ex In Direct3D9Ex, SharpDX.Direct3D9.SwapEffect.FlipEx
			/// is added to designate when an application is adopting flip mode. That is, whan
			/// an application's frame is passed in window's mode (instead of copied) to the
			/// Desktop Window Manager(DWM) for composition. Flip mode provides more efficient
			/// memory bandwidth and enables an application to take advantage of full-screen-present
			/// statistics. It does not change full screen behavior. Flip mode behavior is available
			/// beginning with Windows 7. ?
			/// </summary>
			int SwapEffect;

			/// <summary>
			/// The device window determines the location and size of the back buffer on screen.
			/// This is used by Direct3D when the back buffer contents are copied to the front
			/// buffer during Present. For a full-screen application, this is a handle to the
			/// top window (which is the focus window). For applications that use multiple full-screen
			/// devices (such as a multimonitor system), exactly one device can use the focus
			/// window as the device window. All other devices must have unique device windows.
			/// For a windowed-mode application, this handle will be the default target window
			/// for Present. If this handle is null, the focus window will be taken. Note that
			/// no attempt is made by the runtime to reflect user changes in window size. The
			/// back buffer is not implicitly reset when this window is reset. However, the Present
			/// method does automatically track window position changes.
			/// </summary>
			IntPtr DeviceWindowHandle;

			/// <summary>
			/// True if the application runs windowed; False if the application runs full-screen.
			/// </summary>
			bool Windowed;

			/// <summary>
			/// If this value is TRUE, Direct3D will manage depth buffers for the application.
			/// The device will create a depth-stencil buffer when it is created. The depth-stencil
			/// buffer will be automatically set as the render target of the device. When the
			/// device is reset, the depth-stencil buffer will be automatically destroyed and
			/// recreated in the new size. If EnableAutoDepthStencil is TRUE, then AutoDepthStencilFormat
			/// must be a valid depth-stencil format.
			/// </summary>
			bool EnableAutoDepthStencil;

			/// <summary>
			/// Member of the SharpDX.Direct3D9.Format enumerated type. The format of the automatic
			/// depth-stencil surface that the device will create. This member is ignored unless
			/// EnableAutoDepthStencil is TRUE.
			/// </summary>
			int AutoDepthStencilFormat;

			/// <summary>
			/// One of the SharpDX.Direct3D9.PresentFlags constants.
			/// </summary>
			int PresentFlags;

			/// <summary>
			/// The rate at which the display adapter refreshes the screen. The value depends
			/// on the mode in which the application is running: For windowed mode, the refresh
			/// rate must be 0. For full-screen mode, the refresh rate is one of the refresh
			/// rates returned by EnumAdapterModes.
			/// </summary>
			int FullScreenRefreshRateInHz;

			/// <summary>
			/// The maximum rate at which the swap chain's back buffers can be presented to the
			/// front buffer. For a detailed explanation of the modes and the intervals that
			/// are supported, see SharpDX.Direct3D9.Present.
			/// </summary>
			int PresentationInterval;

		};

		public value class D3DFontDescription
		{
		public:
			D3DFontDescription(String^ faceName, int width, int height, int mipLevels, eD3DFontWeight weight, bool italic, eD3DFontQuality quality, eD3DFontPrecision precision, eD3DFontCharacterSet charSet, eD3DFontPitchAndFamily pitchAndFamily);
			D3DFontDescription(String^ faceName, int width, int height, eD3DFontWeight weight, bool italic, eD3DFontQuality quality, eD3DFontPrecision precision, eD3DFontCharacterSet charSet, eD3DFontPitchAndFamily pitchAndFamily);
			D3DFontDescription(String^ faceName, int width, int height, eD3DFontWeight weight, bool italic, eD3DFontQuality quality, eD3DFontPrecision precision);
			D3DFontDescription(String^ faceName, int height, eD3DFontWeight weight, bool italic, eD3DFontQuality quality);
			D3DFontDescription(String^ faceName, int height, eD3DFontWeight weight, bool italic);
			D3DFontDescription(String^ faceName, int height);

			/// <summary>
			/// Creates a D3DFontDescription object with the font family being Arial, the height being 20 and everything else being the default value.
			/// </summary>
			/// <returns>The D3DFontDescription object.</returns>
			static D3DFontDescription Default();

			/// <summary>
			/// A null-terminated string or characters that specifies the typeface name of the
			/// font. The length of the string must not exceed 32 characters, including the terminating
			/// null character. If FaceName is an empty string, the first font that matches the
			/// other specified attributes will be used. If the compiler settings require Unicode,
			/// the data type TCHAR resolves to WCHAR; otherwise, the data type resolves to CHAR.
			/// See Remarks.
			/// </summary>
			String^ FaceName;

			/// <summary>
			/// Width, in logical units, of characters in the font.
			/// </summary>
			int Width;

			/// <summary>
			/// Height, in logical units, of the font's character cell or character.
			/// </summary>
			int Height;

			/// <summary>
			/// Number of mip levels requested. If this value is zero or D3DX_DEFAULT, a complete
			/// mipmap chain is created. If the value is 1, the texture space is mapped identically
			/// to the screen space.
			/// </summary>
			int MipLevels;

			/// <summary>
			/// Set to TRUE for an Italic font.
			/// </summary>
			bool Italic;

			/// <summary>
			/// Weight of the font in the range from 0 through 1000.
			/// </summary>
			eD3DFontWeight FontWeight;

			/// <summary>
			/// Output quality.
			/// </summary>
			eD3DFontQuality FontQuality;

			/// <summary>
			/// Output precision. The output precision defines how closely the output must match
			/// the requested font height, width, character orientation, escapement, pitch, and
			/// font type.
			/// </summary>
			eD3DFontPrecision FontPrecision;

			/// <summary>
			/// Character set.
			/// </summary>
			eD3DFontCharacterSet FontCharSet;

			/// <summary>
			/// Pitch and family of the font.
			/// </summary>
			eD3DFontPitchAndFamily FontPitchAndFamily;

		};

		// Classes
		public ref class D3DResult
		{
		public:
			D3DResult(Exception^ ex, Guid id, Object^ dxObj)
			{
				Error = ex;
				ID = id;
				DXObject = dxObj;
			}
			D3DResult(Exception^ ex, Guid id)
			{
				Error = ex;
				ID = id;
				DXObject = nullptr;
			}
			D3DResult(Exception^ ex)
			{
				Error = ex;
				ID = Guid::Empty;
				DXObject = nullptr;
			}

			property Exception^ Error {
				public:		Exception^ get() { return m_error; }
				private:	void		set(Exception^ value) { m_error = value; }
			}

			property Guid ID {
				public:		Guid get() { return m_id; }
				private:	void set(Guid value) { m_id = value; }
			}

			property Object^ DXObject {
				public:		Object^ get() { return m_obj; }
				private:	void set(Object^ value) { m_obj = value; }
			}

		private:
			Exception^ m_error;
			Guid m_id;
			Object^ m_obj;
		};

		public ref class D3DResource
		{
		public:
			D3DResource(Guid id, eD3D9ResourceType type, String^ resourceProperties, IntPtr handle)
			{
				ID = id;
				DXType = type;
				m_resourceProperties = resourceProperties;
				Handle = handle;
			}

			property Guid ID {
				public:		Guid get()							{ return m_id; }
				private:	void set(Guid value)				{ m_id = value; }
			}

			property eD3D9ResourceType DXType {
				public:		eD3D9ResourceType get()				{ return m_resourceType; }
				private:	void set(eD3D9ResourceType value)	{ m_resourceType = value; }
			}

			property String^ ResourceProperties {
				public:		String^ get()						{ return m_resourceProperties; }
				private:	void set(String^ value)				{ m_resourceProperties = value; }
			}

			property IntPtr Handle {
				public:		IntPtr get()						{ return m_handle; }
				private:	void set(IntPtr value)				{ m_handle = value; }
			}

		private:
			Guid m_id;
			eD3D9ResourceType m_resourceType;
			String^ m_resourceProperties;
			IntPtr m_handle;
		};

	}
}