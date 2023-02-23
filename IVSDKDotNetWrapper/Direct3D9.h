#pragma once

namespace IVSDKDotNet {
	namespace Direct3D9 {

		public ref class D3DGraphics
		{
		public:

			delegate void D3D9DeviveDelegate(IntPtr device);
			delegate void D3D9DeviveResetDelegate(IntPtr device, D3DPresentParameters presentParameters);

			// Constructor / Destructor
			D3DGraphics(Script^ createFor);
			~D3DGraphics();

			// Events / Raisers

			/// <summary>
			/// Gets called on the very first EndScene call so you can initialize all your stuff in here like textures or fonts.
			/// </summary>
			event D3D9DeviveDelegate^	OnInit;

			/// <summary>
			/// Gets called everytime EndScene is about to get called. Perfect to draw your stuff.
			/// </summary>
			event D3D9DeviveDelegate^	OnDeviceEndScene;

			/// <summary>
			/// Gets called before a device reset is about to happen.
			/// </summary>
			event D3D9DeviveResetDelegate^	OnBeforeDeviceReset;

			/// <summary>
			/// Gets called after the device got reset.
			/// </summary>
			event D3D9DeviveDelegate^	OnAfterDeviceReset;

			void RaiseOnInit(IntPtr device)															{ OnInit(device); Device = device; }
			void RaiseOnDeviceEndScene(IntPtr device)												{ OnDeviceEndScene(device); Device = device; }
			void RaiseOnBeforeDeviceReset(IntPtr device, D3DPresentParameters presentParameters)	{ OnBeforeDeviceReset(device, presentParameters); }
			void RaiseOnAfterDeviceReset(IntPtr device)												{ OnAfterDeviceReset(device); }

			// TODO: Remove comment when property has more purposes.
			/// <summary>
			/// Does not do much currently.
			/// </summary>
			property eFontScaling Scaling {
				public:
					eFontScaling	get()					{ return m_eScaling; }
					void			set(eFontScaling value) { m_eScaling = value; }
			}

			property IntPtr Device {
				public:		IntPtr get()			{ return m_pDevice; }
				private:	void set(IntPtr value)	{ m_pDevice = value; }
			}

#pragma region Measurement Properties
			/// <summary>
			/// Gets how much time the OnInit event took to execute.
			/// </summary>
			property TimeSpan OnInitEventExecutionTime {
				public:
					TimeSpan	get()				{ return m_sOnInitEventExecutionTime; }
					void		set(TimeSpan value) { m_sOnInitEventExecutionTime = value; }
			}
			/// <summary>
			/// Gets how much time the OnDeviceEndScene event took to execute.
			/// </summary>
			property TimeSpan OnDeviceEndSceneEventExecutionTime {
				public:
					TimeSpan	get()				{ return m_sOnEndSceneEventExecutionTime; }
					void		set(TimeSpan value) { m_sOnEndSceneEventExecutionTime = value; }
			}
			/// <summary>
			/// Gets how much time the OnBeforeDeviceReset event took to execute.
			/// </summary>
			property TimeSpan OnBeforeDeviceResetEventExecutionTime {
				public:
					TimeSpan	get()				{ return m_sOnBeforeResetEventExecutionTime; }
					void		set(TimeSpan value) { m_sOnBeforeResetEventExecutionTime = value; }
			}
			/// <summary>
			/// Gets how much time the OnAfterDeviceReset event took to execute.
			/// </summary>
			property TimeSpan OnAfterDeviceResetEventExecutionTime {
				public:
					TimeSpan	get()				{ return m_sOnAfterResetEventExecutionTime; }
					void		set(TimeSpan value) { m_sOnAfterResetEventExecutionTime = value; }
			}
#pragma endregion

			// Creation functions
			D3DResult^ CreateD3D9Texture(IntPtr device, String^ filePath, Size size);
			D3DResult^ CreateD3D9Texture(IntPtr device, String^ filePath);
			D3DResult^ CreateD3D9Texture(IntPtr device, array<Byte>^ data, Size size);
			D3DResult^ CreateD3D9Texture(IntPtr device, array<Byte>^ data);

			Exception^ ReleaseD3D9Texture(D3DResource^ resource);

			D3DResult^ CreateD3D9Font(IntPtr device, D3DFontDescription fontDescription);
			Exception^ ReleaseD3D9Font(D3DResource^ resource);

			// Drawing functions
			bool DrawLines(IntPtr device, array<Vector2>^ vertices, Color color, bool antialias, int pattern, float patternScale, float thickness);
			bool DrawLines(IntPtr device, array<Vector2>^ vertices, Color color, bool antialias, float thickness);
			bool DrawLine(IntPtr device, Vector2 point1, Vector2 point2, Color color, bool antialias, int pattern, float patternScale, float thickness);
			bool DrawLine(IntPtr device, Vector2 point1, Vector2 point2, Color color, bool antialias, int pattern, float thickness);
			bool DrawLine(IntPtr device, Vector2 point1, Vector2 point2, Color color, bool antialias, float thickness);
			bool DrawLine(IntPtr device, Vector2 point1, Vector2 point2, Color color, float thickness);

			bool DrawCircle(IntPtr device, Vector2 pos, float radius, float rotation, eD3DCircleType type, bool smoothing, int resolution, Color color);
			bool DrawCircleFilled(IntPtr device, Vector2 pos, float radius, float rotation, eD3DCircleType type, bool smoothing, int resolution, Color color);

			bool DrawBoxFilled(IntPtr device, Vector2 pos, SizeF size, Color color);
			bool DrawBox(IntPtr device, Vector2 pos, SizeF size, float lineWidth, Color color);
			bool DrawBoxBordered(IntPtr device, Vector2 pos, SizeF size, float borderWidth, Color color, Color borderColor);
			bool DrawBoxRounded(IntPtr device, Vector2 pos, SizeF size, float radius, bool smoothing, Color color, Color borderColor);

			bool DrawTexture(IntPtr device, D3DResource^ txt, RectangleF rect, float rotation, Color tint);
			bool DrawTexture(IntPtr device, D3DResource^ txt, RectangleF rect, Color tint);
			bool DrawTexture(IntPtr device, D3DResource^ txt, RectangleF rect, float rotation);
			bool DrawTexture(IntPtr device, D3DResource^ txt, RectangleF rect);

			bool DrawString(IntPtr device, D3DResource^ fontResource, String^ text, Point pos, Color color);
			bool DrawString(IntPtr device, D3DResource^ fontResource, String^ text, int x, int y, Color color);

			bool DrawString(IntPtr device, String^ text, Point pos, Color color);
			bool DrawString(IntPtr device, String^ text, int x, int y, Color color);

		private:
			Script^ m_createForScript;
			eFontScaling m_eScaling;
			IntPtr m_pDevice;

			// Measurements
			TimeSpan m_sOnInitEventExecutionTime;
			TimeSpan m_sOnEndSceneEventExecutionTime;
			TimeSpan m_sOnBeforeResetEventExecutionTime;
			TimeSpan m_sOnAfterResetEventExecutionTime;
		};

	}
}