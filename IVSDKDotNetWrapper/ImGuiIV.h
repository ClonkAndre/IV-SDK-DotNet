#pragma once

// Modified ImGui code to make it work with GTA IV from the InGameTimecycEditor Mod for GTA IV made by akifle47.
// https://github.com/akifle47/InGameTimecycEditor

// Dear ImGui: An awesome, bloat-free UI Library by ocornut
// https://github.com/ocornut/imgui

extern IMGUI_IMPL_API LONG_PTR ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern IMGUI_IMPL_API void ImGui_ImplWin32_WndProcKeyOnlyHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace IVSDKDotNet
{
	// Some structs
	public value struct ImGuiIV_Viewport
	{
	public:

		/// <summary>
		/// Native Pointer to the ImGuiViewport structure.
		/// </summary>
		property IntPtr ImGuiViewportPtr
		{
		public:
			IntPtr get()
			{
				return IntPtr(m_vMainViewport);
			}
		}

		/// <summary>
		/// Gets if this struct contains valid data.
		/// </summary>
		property bool IsValid
		{
		public:
			bool get()
			{
				return m_bIsValid;
			}
		}

		/// <summary>
		/// Main Area: Position of the viewport (Dear ImGui coordinates are the same as OS desktop/native coordinates).
		/// </summary>
		property Vector2 Pos
		{
		public:
			Vector2 get()
			{
				if (!m_bIsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_vMainViewport->Pos);
			}
		}

		/// <summary>
		/// Main Area: Size of the viewport.
		/// </summary>
		property Vector2 Size
		{
		public:
			Vector2 get()
			{
				if (!m_bIsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_vMainViewport->Size);
			}
		}

		/// <summary>
		/// Work Area: Position of the viewport minus task bars, menus bars, status bars (bigger then Pos).
		/// </summary>
		property Vector2 WorkPos
		{
		public:
			Vector2 get()
			{
				if (!m_bIsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_vMainViewport->WorkPos);
			}
		}

		/// <summary>
		/// Work Area: Size of the viewport minus task bars, menu bars, status bars (smaller then Size).
		/// </summary>
		property Vector2 WorkSize
		{
		public:
			Vector2 get()
			{
				if (!m_bIsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_vMainViewport->WorkSize);
			}
		}

	public:

		/// <summary>
		/// Gets the center position of the main Area.
		/// </summary>
		/// <returns>The center position of the main Area.</returns>
		Vector2 GetCenter()
		{
			if (!m_bIsValid)
				return Vector2::Zero;

			return ImVec2ToVector2(m_vMainViewport->GetCenter());
		}

		/// <summary>
		/// Gets the center position of the work Area.
		/// </summary>
		/// <returns>The center position of the work Area.</returns>
		Vector2 GetWorkCenter()
		{
			if (!m_bIsValid)
				return Vector2::Zero;

			return ImVec2ToVector2(m_vMainViewport->GetWorkCenter());
		}

	internal:
		ImGuiIV_Viewport(ImGuiViewport* vp, bool isValid)
		{
			m_vMainViewport = vp;
			m_bIsValid = isValid;
		}

	private:
		ImGuiViewport* m_vMainViewport;
		bool m_bIsValid;
	};
	public value struct ImGuiIV_Style
	{
	public:

		/// <summary>
		/// Native Pointer to the ImGuiStyle structure.
		/// </summary>
		property IntPtr ImGuiStylePtr
		{
		public:
			IntPtr get()
			{
				return IntPtr(m_style);
			}
		}

		/// <summary>
		/// Gets if this struct contains valid data.
		/// </summary>
		property bool IsValid
		{
		public:
			bool get()
			{
				return m_bIsValid;
			}
		}

		/// <summary>
		/// Global alpha applies to everything in Dear ImGui.
		/// </summary>
		property float Alpha
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->Alpha;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->Alpha = value;
			}
		}
		/// <summary>
		/// Additional alpha multiplier applied by BeginDisabled(). Multiply over current value of Alpha.
		/// </summary>
		property float DisabledAlpha
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->DisabledAlpha;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->DisabledAlpha = value;
			}
		}
		/// <summary>
		/// Padding within a window.
		/// </summary>
		property Vector2 WindowPadding
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->WindowPadding);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->WindowPadding = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Radius of window corners rounding. Set to 0.0f to have rectangular windows. Large values tend to lead to variety of artifacts and are not recommended.
		/// </summary>
		property float WindowRounding
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->WindowRounding;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->WindowRounding = value;
			}
		}
		/// <summary>
		/// Thickness of border around windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
		/// </summary>
		property float WindowBorderSize
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->WindowBorderSize;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->WindowBorderSize = value;
			}
		}
		/// <summary>
		/// Minimum window size. This is a global setting. If you want to constrain individual windows, use SetNextWindowSizeConstraints().
		/// </summary>
		property Vector2 WindowMinSize
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->WindowMinSize);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->WindowMinSize = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Alignment for title bar text. Defaults to (0.0f,0.5f) for left-aligned,vertically centered.
		/// </summary>
		property Vector2 WindowTitleAlign
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->WindowTitleAlign);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->WindowTitleAlign = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Side of the collapsing/docking button in the title bar (None/Left/Right). Defaults to ImGuiDir_Left.
		/// </summary>
		property eImGuiDir WindowMenuButtonPosition
		{
			eImGuiDir get()
			{
				if (!IsValid)
					return eImGuiDir::None;

				return (eImGuiDir)m_style->WindowMenuButtonPosition;
			}
			void set(eImGuiDir value)
			{
				if (!IsValid)
					return;

				m_style->WindowMenuButtonPosition = (ImGuiDir)value;
			}
		}
		/// <summary>
		/// Radius of child window corners rounding. Set to 0.0f to have rectangular windows.
		/// </summary>
		property float ChildRounding
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->ChildRounding;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->ChildRounding = value;
			}
		}
		/// <summary>
		/// Thickness of border around child windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
		/// </summary>
		property float ChildBorderSize
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->ChildBorderSize;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->ChildBorderSize = value;
			}
		}
		/// <summary>
		/// Radius of popup window corners rounding. (Note that tooltip windows use WindowRounding)
		/// </summary>
		property float PopupRounding
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->PopupRounding;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->PopupRounding = value;
			}
		}
		/// <summary>
		/// Thickness of border around popup/tooltip windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
		/// </summary>
		property float PopupBorderSize
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->PopupBorderSize;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->PopupBorderSize = value;
			}
		}
		/// <summary>
		/// Padding within a framed rectangle (used by most widgets).
		/// </summary>
		property Vector2 FramePadding
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->FramePadding);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->FramePadding = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Radius of frame corners rounding. Set to 0.0f to have rectangular frame (used by most widgets).
		/// </summary>
		property float FrameRounding
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->FrameRounding;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->FrameRounding = value;
			}
		}
		/// <summary>
		/// Thickness of border around frames. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
		/// </summary>
		property float FrameBorderSize
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->FrameBorderSize;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->FrameBorderSize = value;
			}
		}
		/// <summary>
		/// Horizontal and vertical spacing between widgets/lines.
		/// </summary>
		property Vector2 ItemSpacing
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->ItemSpacing);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->ItemSpacing = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label).
		/// </summary>
		property Vector2 ItemInnerSpacing
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->ItemInnerSpacing);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->ItemInnerSpacing = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Padding within a table cell. CellPadding.y may be altered between different rows.
		/// </summary>
		property Vector2 CellPadding
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->CellPadding);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->CellPadding = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
		/// </summary>
		property Vector2 TouchExtraPadding
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->TouchExtraPadding);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->TouchExtraPadding = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Horizontal indentation when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
		/// </summary>
		property float IndentSpacing
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->IndentSpacing;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->IndentSpacing = value;
			}
		}
		/// <summary>
		/// Minimum horizontal spacing between two columns. Preferably > (FramePadding.x + 1).
		/// </summary>
		property float ColumnsMinSpacing
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->ColumnsMinSpacing;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->ColumnsMinSpacing = value;
			}
		}
		/// <summary>
		/// Width of the vertical scrollbar, Height of the horizontal scrollbar.
		/// </summary>
		property float ScrollbarSize
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->ScrollbarSize;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->ScrollbarSize = value;
			}
		}
		/// <summary>
		/// Radius of grab corners for scrollbar.
		/// </summary>
		property float ScrollbarRounding
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->ScrollbarRounding;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->ScrollbarRounding = value;
			}
		}
		/// <summary>
		/// Minimum width/height of a grab box for slider/scrollbar.
		/// </summary>
		property float GrabMinSize
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->GrabMinSize;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->GrabMinSize = value;
			}
		}
		/// <summary>
		/// Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
		/// </summary>
		property float GrabRounding
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->GrabRounding;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->GrabRounding = value;
			}
		}
		/// <summary>
		/// The size in pixels of the dead-zone around zero on logarithmic sliders that cross zero.
		/// </summary>
		property float LogSliderDeadzone
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->LogSliderDeadzone;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->LogSliderDeadzone = value;
			}
		}
		/// <summary>
		/// Radius of upper corners of a tab. Set to 0.0f to have rectangular tabs.
		/// </summary>
		property float TabRounding
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->TabRounding;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->TabRounding = value;
			}
		}
		/// <summary>
		/// Thickness of border around tabs.
		/// </summary>
		property float TabBorderSize
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->TabBorderSize;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->TabBorderSize = value;
			}
		}
		/// <summary>
		/// Minimum width for close button to appear on an unselected tab when hovered. Set to 0.0f to always show when hovering, set to FLT_MAX to never show close button unless selected.
		/// </summary>
		property float TabMinWidthForCloseButton
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->TabMinWidthForCloseButton;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->TabMinWidthForCloseButton = value;
			}
		}
		/// <summary>
		/// Thickness of tab-bar separator, which takes on the tab active color to denote focus.
		/// </summary>
		property float TabBarBorderSize
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->TabBarBorderSize;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->TabBarBorderSize = value;
			}
		}
		/// <summary>
		/// Angle of angled headers (supported values range from -50.0f degrees to +50.0f degrees).
		/// </summary>
		property float TableAngledHeadersAngle
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->TableAngledHeadersAngle;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->TableAngledHeadersAngle = value;
			}
		}
		/// <summary>
		/// Side of the color button in the ColorEdit4 widget (left/right). Defaults to ImGuiDir_Right.
		/// </summary>
		property eImGuiDir ColorButtonPosition
		{
			eImGuiDir get()
			{
				if (!IsValid)
					return eImGuiDir::None;

				return (eImGuiDir)m_style->ColorButtonPosition;
			}
			void set(eImGuiDir value)
			{
				if (!IsValid)
					return;

				m_style->ColorButtonPosition = (ImGuiDir)value;
			}
		}
		/// <summary>
		/// Alignment of button text when button is larger than text. Defaults to (0.5f, 0.5f) (centered).
		/// </summary>
		property Vector2 ButtonTextAlign
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->ButtonTextAlign);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->ButtonTextAlign = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Alignment of selectable text. Defaults to (0.0f, 0.0f) (top-left aligned). It's generally important to keep this left-aligned if you want to lay multiple items on a same line.
		/// </summary>
		property Vector2 SelectableTextAlign
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->SelectableTextAlign);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->SelectableTextAlign = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Thickkness of border in SeparatorText()
		/// </summary>
		property float SeparatorTextBorderSize
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->SeparatorTextBorderSize;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->SeparatorTextBorderSize = value;
			}
		}
		/// <summary>
		/// Alignment of text within the separator. Defaults to (0.0f, 0.5f) (left aligned, center).
		/// </summary>
		property Vector2 SeparatorTextAlign
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->SeparatorTextAlign);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->SeparatorTextAlign = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Horizontal offset of text from each edge of the separator + spacing on other axis. Generally small values. .y is recommended to be == FramePadding.y.
		/// </summary>
		property Vector2 SeparatorTextPadding
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->SeparatorTextPadding);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->SeparatorTextPadding = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Window position are clamped to be visible within the display area or monitors by at least this amount. Only applies to regular windows.
		/// </summary>
		property Vector2 DisplayWindowPadding
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->DisplayWindowPadding);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->DisplayWindowPadding = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// If you cannot see the edges of your screen (e.g. on a TV) increase the safe area padding. Apply to popups/tooltips as well regular windows. NB: Prefer configuring your TV sets correctly!
		/// </summary>
		property Vector2 DisplaySafeAreaPadding
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_style->DisplaySafeAreaPadding);
			}
			void set(Vector2 value)
			{
				if (!IsValid)
					return;

				m_style->DisplaySafeAreaPadding = Vector2ToImVec2(value);
			}
		}
		/// <summary>
		/// Thickness of resizing border between docked windows
		/// </summary>
		property float DockingSeparatorSize
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->DockingSeparatorSize;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->DockingSeparatorSize = value;
			}
		}
		/// <summary>
		/// Scale software rendered mouse cursor (when io.MouseDrawCursor is enabled). We apply per-monitor DPI scaling over this scale. May be removed later.
		/// </summary>
		property float MouseCursorScale
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->MouseCursorScale;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->MouseCursorScale = value;
			}
		}
		/// <summary>
		/// Enable anti-aliased lines/borders. Disable if you are really tight on CPU/GPU. Latched at the beginning of the frame (copied to ImDrawList).
		/// </summary>
		property bool AntiAliasedLines
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_style->AntiAliasedLines;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				m_style->AntiAliasedLines = value;
			}
		}
		/// <summary>
		/// Enable anti-aliased lines/borders using textures where possible. Require backend to render with bilinear filtering (NOT point/nearest filtering). Latched at the beginning of the frame (copied to ImDrawList).
		/// </summary>
		property bool AntiAliasedLinesUseTex
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_style->AntiAliasedLinesUseTex;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				m_style->AntiAliasedLinesUseTex = value;
			}
		}
		/// <summary>
		/// Enable anti-aliased edges around filled shapes (rounded rectangles, circles, etc.). Disable if you are really tight on CPU/GPU. Latched at the beginning of the frame (copied to ImDrawList).
		/// </summary>
		property bool AntiAliasedFill
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_style->AntiAliasedFill;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				m_style->AntiAliasedFill = value;
			}
		}
		/// <summary>
		/// Tessellation tolerance when using PathBezierCurveTo() without a specific number of segments. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
		/// </summary>
		property float CurveTessellationTol
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->CurveTessellationTol;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->CurveTessellationTol = value;
			}
		}
		/// <summary>
		/// Maximum error (in pixels) allowed when using AddCircle()/AddCircleFilled() or drawing rounded corner rectangles with no explicit segment count specified. Decrease for higher quality but more geometry.
		/// </summary>
		property float CircleTessellationMaxError
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->CircleTessellationMaxError;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->CircleTessellationMaxError = value;
			}
		}

		property array<Vector4>^ Colors
		{
			array<Vector4>^ get()
			{
				if (!IsValid)
					return nullptr;

				array<Vector4>^ arr = gcnew array<Vector4>(ImGuiCol_COUNT);

				for (int i = 0; i < arr->Length; i++)
					arr[i] = ImVec4ToVector4(m_style->Colors[i]);

				return arr;
			}
			void set(array<Vector4>^ value)
			{
				if (!IsValid)
					return;
				if (value == nullptr)
					return;

				for (int i = 0; i < value->Length; i++)
					m_style->Colors[i] = Vector4ToImVec4(value[i]);
			}
		}

		// Behaviors

		/// <summary>
		/// Delay for IsItemHovered(ImGuiHoveredFlags_Stationary). Time required to consider mouse stationary.
		/// </summary>
		property float HoverStationaryDelay
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->HoverStationaryDelay;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->HoverStationaryDelay = value;
			}
		}
		/// <summary>
		/// Delay for IsItemHovered(ImGuiHoveredFlags_DelayShort). Usually used along with HoverStationaryDelay.
		/// </summary>
		property float HoverDelayShort
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->HoverDelayShort;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->HoverDelayShort = value;
			}
		}
		/// <summary>
		/// Delay for IsItemHovered(ImGuiHoveredFlags_DelayNormal).
		/// </summary>
		property float HoverDelayNormal
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_style->HoverDelayNormal;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_style->HoverDelayNormal = value;
			}
		}
		/// <summary>
		/// Default flags when using IsItemHovered(ImGuiHoveredFlags_ForTooltip) or BeginItemTooltip()/SetItemTooltip() while using mouse.
		/// </summary>
		property eImGuiHoveredFlags HoverFlagsForTooltipMouse
		{
			eImGuiHoveredFlags get()
			{
				if (!IsValid)
					return eImGuiHoveredFlags::None;

				return (eImGuiHoveredFlags)m_style->HoverFlagsForTooltipMouse;
			}
			void set(eImGuiHoveredFlags value)
			{
				if (!IsValid)
					return;
				
				m_style->HoverFlagsForTooltipMouse = (ImGuiHoveredFlags)value;
			}
		}
		/// <summary>
		/// Default flags when using IsItemHovered(ImGuiHoveredFlags_ForTooltip) or BeginItemTooltip()/SetItemTooltip() while using keyboard/gamepad.
		/// </summary>
		property eImGuiHoveredFlags HoverFlagsForTooltipNav
		{
			eImGuiHoveredFlags get()
			{
				if (!IsValid)
					return eImGuiHoveredFlags::None;

				return (eImGuiHoveredFlags)m_style->HoverFlagsForTooltipNav;
			}
			void set(eImGuiHoveredFlags value)
			{
				if (!IsValid)
					return;

				m_style->HoverFlagsForTooltipNav = (ImGuiHoveredFlags)value;
			}
		}

	public:
		void ScaleAllSizes(float scale_factor)
		{
			if (!IsValid)
				return;

			m_style->ScaleAllSizes(scale_factor);
		}

	internal:
		ImGuiIV_Style(ImGuiStyle* style, bool isValid)
		{
			m_style = style;
			m_bIsValid = isValid;
		}

	private:
		ImGuiStyle* m_style;
		bool m_bIsValid;
	};
	public value struct ImGuiIV_Payload
	{
	public:
		/// <summary>
		/// Native Pointer to the ImGuiPayload structure.
		/// </summary>
		property IntPtr ImGuiPayloadPtr
		{
		public:
			IntPtr get()
			{
				return IntPtr(m_payload);
			}
		}

		/// <summary>
		/// Gets if this struct contains valid data.
		/// </summary>
		property bool IsValid
		{
		public:
			bool get()
			{
				return m_bIsValid;
			}
		}

		property IntPtr Data
		{
			IntPtr get()
			{
				if (!IsValid)
					return IntPtr::Zero;

				return IntPtr(m_payload->Data);
			}
		}
		property int DataSize
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return m_payload->DataSize;
			}
		}

	public:
		void Clear()
		{
			if (!IsValid)
				return;

			m_payload->Clear();
		}

		bool IsDataType(String^ type)
		{
			if (!IsValid)
				return false;
			if (String::IsNullOrWhiteSpace(type))
				return false;

			msclr::interop::marshal_context ctx;
			return m_payload->IsDataType(ctx.marshal_as<const char*>(type));
		}
		bool IsPreview()
		{
			if (!IsValid)
				return false;

			return m_payload->IsPreview();
		}
		bool IsDelivery()
		{
			if (!IsValid)
				return false;

			return m_payload->IsDelivery();
		}

	internal:
		ImGuiIV_Payload(ImGuiPayload* ptr, bool isValid)
		{
			m_payload = ptr;
			m_bIsValid = isValid;
		}

	private:
		ImGuiPayload* m_payload;
		bool m_bIsValid;
	};
	public value struct ImGuiIV_InputTextState
	{
	public:

		/// <summary>
		/// Native Pointer to the ImGuiInputTextState structure.
		/// </summary>
		property IntPtr ImGuiInputTextStatePtr
		{
		public:
			IntPtr get()
			{
				return IntPtr(m_InputTextState);
			}
		}

		/// <summary>
		/// Gets if this struct contains valid data.
		/// </summary>
		property bool IsValid
		{
		public:
			bool get()
			{
				return m_bIsValid;
			}
		}

		/// <summary>
		/// Widget id owning the text state.
		/// </summary>
		property ImGuiID ID
		{
			ImGuiID get()
			{
				if (!IsValid)
					return 0;

				return m_InputTextState->ID;
			}
			void set(ImGuiID value)
			{
				if (!IsValid)
					return;

				m_InputTextState->ID = value;
			}
		}

		/// <summary>
		/// Widget id owning the text state.
		/// </summary>
		property float ScrollX
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_InputTextState->ScrollX;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_InputTextState->ScrollX = value;
			}
		}

		/// <summary>
		/// Timer for cursor blink, reset on every user action so the cursor reappears immediately.
		/// </summary>
		property float CursorAnim
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_InputTextState->CursorAnim;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				m_InputTextState->CursorAnim = value;
			}
		}

		/// <summary>
		/// Set when we want scrolling to follow the current cursor position (not always!).
		/// </summary>
		property bool CursorFollow
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_InputTextState->CursorFollow;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				m_InputTextState->CursorFollow = value;
			}
		}

		/// <summary>
		/// After a double-click to select all, we ignore further mouse drags to update selection.
		/// </summary>
		property bool SelectedAllMouseLock
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_InputTextState->SelectedAllMouseLock;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				m_InputTextState->SelectedAllMouseLock = value;
			}
		}

		/// <summary>
		/// Edited this frame.
		/// </summary>
		property bool Edited
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_InputTextState->Edited;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				m_InputTextState->Edited = value;
			}
		}

		/// <summary>
		/// Copy of InputText() flags. may be used to check if e.g. ImGuiInputTextFlags_Password is set.
		/// </summary>
		property eImGuiInputTextFlags Flags
		{
			eImGuiInputTextFlags get()
			{
				if (!IsValid)
					return eImGuiInputTextFlags::None;

				return (eImGuiInputTextFlags)m_InputTextState->Flags;
			}
			void set(eImGuiInputTextFlags value)
			{
				if (!IsValid)
					return;

				m_InputTextState->Flags = (ImGuiInputTextFlags)value;
			}
		}

		/// <summary>
		/// Force a reload of user buf so it may be modified externally. may be automatic in future version.
		/// </summary>
		property bool ReloadUserBuf
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_InputTextState->ReloadUserBuf;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				m_InputTextState->ReloadUserBuf = value;
			}
		}

		/// <summary>
		/// POSITIONS ARE IN IMWCHAR units *NOT* UTF-8 this is why this is not exposed yet.
		/// </summary>
		property int ReloadSelectionStart
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return m_InputTextState->ReloadSelectionStart;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				m_InputTextState->ReloadSelectionStart = value;
			}
		}

		property int ReloadSelectionEnd
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return m_InputTextState->ReloadSelectionEnd;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				m_InputTextState->ReloadSelectionEnd = value;
			}
		}

	public:
		void ClearText()
		{
			if (IsValid)
				m_InputTextState->ClearText();
		}
		void ClearFreeMemory()
		{
			if (IsValid)
				m_InputTextState->ClearFreeMemory();
		}

		int GetUndoAvailCount()
		{
			if (IsValid)
				return m_InputTextState->GetUndoAvailCount();

			return 0;
		}
		int GetRedoAvailCount()
		{
			if (IsValid)
				return m_InputTextState->GetRedoAvailCount();

			return 0;
		}

		void OnKeyPressed(int key)
		{
			if (IsValid)
				m_InputTextState->OnKeyPressed(key);
		}

		// Cursor & Selection
		void CursorAnimReset()
		{
			if (IsValid)
				m_InputTextState->CursorAnimReset();
		}
		void CursorClamp()
		{
			if (IsValid)
				m_InputTextState->CursorClamp();
		}
		bool HasSelection()
		{
			if (IsValid)
				return m_InputTextState->HasSelection();

			return false;
		}
		void ClearSelection()
		{
			if (IsValid)
				m_InputTextState->ClearSelection();
		}
		int GetCursorPos()
		{
			if (IsValid)
				return m_InputTextState->GetCursorPos();

			return 0;
		}
		int GetSelectionStart()
		{
			if (IsValid)
				return m_InputTextState->GetSelectionStart();

			return 0;
		}
		int GetSelectionEnd()
		{
			if (IsValid)
				return m_InputTextState->GetSelectionEnd();

			return 0;
		}
		void SelectAll()
		{
			if (IsValid)
				m_InputTextState->SelectAll();
		}

		// Reload user buf (WIP #2890)
		void ReloadUserBufAndSelectAll()
		{
			if (IsValid)
				m_InputTextState->ReloadUserBufAndSelectAll();
		}
		void ReloadUserBufAndKeepSelection()
		{
			if (IsValid)
				m_InputTextState->ReloadUserBufAndKeepSelection();
		}
		void ReloadUserBufAndMoveToEnd()
		{
			if (IsValid)
				m_InputTextState->ReloadUserBufAndMoveToEnd();
		}

	public:
		ImGuiIV_InputTextState(ImGuiInputTextState* ptr, bool isValid)
		{
			m_InputTextState = ptr;
			m_bIsValid = isValid;
		}

	private:
		ImGuiInputTextState* m_InputTextState;
		bool m_bIsValid;
	};
	public value struct ImGuiIV_IO
	{
	public:

		/// <summary>
		/// Native Pointer to the ImGuiIO structure.
		/// </summary>
		property IntPtr ImGuiIOPtr
		{
		public:
			IntPtr get()
			{
				return IntPtr(m_IO);
			}
		}

		/// <summary>
		/// Gets if this struct contains valid data.
		/// </summary>
		property bool IsValid
		{
		public:
			bool get()
			{
				return m_bIsValid;
			}
		}

		property Vector2 DisplaySize
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_IO->DisplaySize);
			}
		}
		property float DeltaTime
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_IO->DeltaTime;
			}
		}

		/// <summary>
		/// Global scale all fonts.
		/// </summary>
		property float FontGlobalScale
		{
		public:
			float get()
			{
				if (!m_bIsValid)
					return 0.0F;

				return m_IO->FontGlobalScale;
			}
			void set(float value)
			{
				if (!m_bIsValid)
					return;

				m_IO->FontGlobalScale = value;
			}
		}

		//------------------------------------------------------------------
		// Output - Updated by NewFrame() or EndFrame()/Render()
		//------------------------------------------------------------------
		property float Framerate
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_IO->Framerate;
			}
		}
		property Vector2 MouseDelta
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_IO->MouseDelta);
			}
		}

		//------------------------------------------------------------------
		// [Internal] Dear ImGui will maintain those fields. Forward compatibility not guaranteed!
		//------------------------------------------------------------------

		// Main Input State
		property Vector2 MousePos
		{
			Vector2 get()
			{
				if (!IsValid)
					return Vector2::Zero;

				return ImVec2ToVector2(m_IO->MousePos);
			}
		}
		property float MouseWheel
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_IO->MouseWheel;
			}
		}
		property float MouseWheelH
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return m_IO->MouseWheelH;
			}
		}
		property eImGuiMouseSource MouseSource
		{
			eImGuiMouseSource get()
			{
				if (!IsValid)
					return eImGuiMouseSource::Unknown;

				return (eImGuiMouseSource)m_IO->MouseSource;
			}
		}
		property bool KeyCtrl
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_IO->KeyCtrl;
			}
		}
		property bool KeyShift
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_IO->KeyShift;
			}
		}
		property bool KeyAlt
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_IO->KeyAlt;
			}
		}
		property bool KeySuper
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_IO->KeySuper;
			}
		}

		property bool WantCaptureKeyboard
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_IO->WantCaptureKeyboard;
			}
		}
		property bool WantCaptureMouse
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_IO->WantCaptureMouse;
			}
		}
		property bool WantCaptureMouseUnlessPopupClose
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_IO->WantCaptureMouseUnlessPopupClose;
			}
		}
		property bool WantSetMousePos
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_IO->WantSetMousePos;
			}
		}
		property bool WantTextInput
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return m_IO->WantTextInput;
			}
		}

	public:
		ImGuiIV_IO(ImGuiIO* ptr, bool isValid)
		{
			m_IO = ptr;
			m_bIsValid = isValid;
		}

	private:
		ImGuiIO* m_IO;
		bool m_bIsValid;
	};

	public value struct ImGuiIV_HexEditorHighlightRange
	{
	public:
		property int From
		{
			int get()
			{
				return m_iFrom;
			}
		}
		property int To
		{
			int get()
			{
				return m_iTo;
			}
		}
		property eImGuiHexEditorHighlightFlags HighlightFlags
		{
			eImGuiHexEditorHighlightFlags get()
			{
				return m_eFlags;
			}
		}

	internal:
		ImGuiIV_HexEditorHighlightRange(int from, int to, eImGuiHexEditorHighlightFlags flags)
		{
			m_iFrom = from;
			m_iTo = to;
			m_eFlags = flags;
		}

	private:
		int m_iFrom;
		int m_iTo;
		eImGuiHexEditorHighlightFlags m_eFlags;

	};
	public ref class ImGuiIV_HexEditorState : public IDisposable
	{
	public:
		/// <summary>
		/// Native Pointer to the ImGuiHexEditorState structure.
		/// </summary>
		property IntPtr ImGuiHexEditorStatePtr
		{
		public:
			IntPtr get()
			{
				return IntPtr(NativeHexEditorState);
			}
		}

		/// <summary>
		/// Gets if this class contains valid data.
		/// </summary>
		property bool IsValid
		{
		public:
			bool get()
			{
				return m_bIsValid;
			}
		}

		property IntPtr Bytes
		{
			IntPtr get()
			{
				if (!IsValid)
					return IntPtr::Zero;

				return IntPtr(NativeHexEditorState->Bytes);
			}
			void set(IntPtr value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->Bytes = value.ToPointer();
			}
		}
		property int MaxBytes
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return NativeHexEditorState->MaxBytes;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->MaxBytes = value;
			}
		}
		property int BytesPerLine
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return NativeHexEditorState->BytesPerLine;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->BytesPerLine = value;
			}
		}
		property bool ShowPrintable
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return NativeHexEditorState->ShowPrintable;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->ShowPrintable = value;
			}
		}
		property bool LowercaseBytes
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return NativeHexEditorState->LowercaseBytes;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->LowercaseBytes = value;
			}
		}
		property bool RenderZeroesDisabled
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return NativeHexEditorState->RenderZeroesDisabled;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->RenderZeroesDisabled = value;
			}
		}
		property bool ShowAddress
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return NativeHexEditorState->ShowAddress;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->ShowAddress = value;
			}
		}
		property int AddressChars
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return NativeHexEditorState->AddressChars;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->AddressChars = value;
			}
		}
		property bool ShowAscii
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return NativeHexEditorState->ShowAscii;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->ShowAscii = value;
			}
		}
		property bool ReadOnly
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return NativeHexEditorState->ReadOnly;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->ReadOnly = value;
			}
		}
		property int Separators
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return NativeHexEditorState->Separators;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->Separators = value;
			}
		}
		property IntPtr UserData
		{
			IntPtr get()
			{
				if (!IsValid)
					return IntPtr::Zero;

				return IntPtr(NativeHexEditorState->UserData);
			}
			void set(IntPtr value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->UserData = value.ToPointer();
			}
		}
		property array<ImGuiIV_HexEditorHighlightRange>^ HighlightRanges
		{
		public:
			array<ImGuiIV_HexEditorHighlightRange>^ get()
			{
				if (!IsValid)
					return nullptr;

				array<ImGuiIV_HexEditorHighlightRange>^ arr = gcnew array<ImGuiIV_HexEditorHighlightRange>(NativeHexEditorState->HighlightRanges.Size);

				for (int i = 0; i < arr->Length; i++)
				{
					ImGuiHexEditorHighlightRange range = NativeHexEditorState->HighlightRanges[i];
					arr[i] = ImGuiIV_HexEditorHighlightRange(range.From, range.To, (eImGuiHexEditorHighlightFlags)range.Flags);
				}

				return arr;
			}
		}
		property bool EnableClipboard
		{
			bool get()
			{
				if (!IsValid)
					return false;

				return NativeHexEditorState->EnableClipboard;
			}
			void set(bool value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->EnableClipboard = value;
			}
		}
		property eImGuiHexEditorClipboardFlags ClipboardFlags
		{
			eImGuiHexEditorClipboardFlags get()
			{
				if (!IsValid)
					return eImGuiHexEditorClipboardFlags::ImGuiHexEditorClipboardFlags_None;

				return (eImGuiHexEditorClipboardFlags)NativeHexEditorState->ClipboardFlags;
			}
			void set(eImGuiHexEditorClipboardFlags value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->ClipboardFlags = (ImGuiHexEditorClipboardFlags)value;
			}
		}

		property int SelectStartByte
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return NativeHexEditorState->SelectStartByte;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->SelectStartByte = value;
			}
		}
		property int SelectStartSubByte
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return NativeHexEditorState->SelectStartSubByte;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->SelectStartSubByte = value;
			}
		}
		property int SelectEndByte
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return NativeHexEditorState->SelectEndByte;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->SelectEndByte = value;
			}
		}
		property int SelectEndSubByte
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return NativeHexEditorState->SelectEndSubByte;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->SelectEndSubByte = value;
			}
		}
		property int LastSelectedByte
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return NativeHexEditorState->LastSelectedByte;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->LastSelectedByte = value;
			}
		}
		property int SelectDragByte
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return NativeHexEditorState->SelectDragByte;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->SelectDragByte = value;
			}
		}
		property int SelectDragSubByte
		{
			int get()
			{
				if (!IsValid)
					return 0;

				return NativeHexEditorState->SelectDragSubByte;
			}
			void set(int value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->SelectDragSubByte = value;
			}
		}
		property float SelectCursorAnimationTime
		{
			float get()
			{
				if (!IsValid)
					return 0.0F;

				return NativeHexEditorState->SelectCursorAnimationTime;
			}
			void set(float value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->SelectCursorAnimationTime = value;
			}
		}

		property eImGuiHexEditorHighlightFlags SelectionHighlightFlags
		{
			eImGuiHexEditorHighlightFlags get()
			{
				if (!IsValid)
					return eImGuiHexEditorHighlightFlags::ImGuiHexEditorHighlightFlags_None;

				return (eImGuiHexEditorHighlightFlags)NativeHexEditorState->SelectionHighlightFlags;
			}
			void set(eImGuiHexEditorHighlightFlags value)
			{
				if (!IsValid)
					return;

				NativeHexEditorState->SelectionHighlightFlags = (ImGuiHexEditorHighlightFlags)value;
			}
		}

	public:
		/// <summary>
		/// Allocates and returns a new hex editor state which HAS to be deleted once you're done using it.
		/// </summary>
		/// <returns>A new instance of the ImGuiIV_HexEditorState class.</returns>
		static ImGuiIV_HexEditorState^ AllocateNew()
		{
			return gcnew ImGuiIV_HexEditorState(new ImGuiHexEditorState(), true);
		}

		/// <summary>
		/// Deletes the allocated hex editor state and frees its memory.
		/// </summary>
		void Delete()
		{
			if (!m_bIsValid)
				return;

			delete NativeHexEditorState;
			NativeHexEditorState = nullptr;
			m_bIsValid = false;
		}

	internal:
		ImGuiIV_HexEditorState(ImGuiHexEditorState* ptr, bool isValid)
		{
			NativeHexEditorState = ptr;
			m_bIsValid = isValid;
		}
		~ImGuiIV_HexEditorState()
		{
			if (m_bIsDisposed)
				return;

			// Call finalizer
			this->!ImGuiIV_HexEditorState();

			m_bIsDisposed = true;
		}
		!ImGuiIV_HexEditorState()
		{
			// Free unmanaged data
			Delete();
		}

	internal:
		ImGuiHexEditorState* NativeHexEditorState;
		bool m_bIsValid;
		bool m_bIsDisposed;
	};

	public ref class ImTexture
	{
	public:
		/// <summary>
		/// Gets if this texture is still valid.
		/// </summary>
		property bool IsValid
		{
		public:
			bool get()
			{
				return m_bIsValid;
			}
		private:
			void set(bool value)
			{
				m_bIsValid = value;
			}
		}

	public:
		/// <summary>
		/// Tries to release this texture.
		/// </summary>
		/// <returns>true if successful. Otherwise false.</returns>
		bool Release()
		{
			if (!IsValid)
				return false;

			bool result = ManagedD3D9::ReleaseTexture(m_pTexture);
			IsValid = false;

			return result;
		}

		/// <summary>
		/// Gets the pointer to the texture which can be passed to some ImGuiIV functions.
		/// </summary>
		/// <returns>The texture pointer.</returns>
		IntPtr GetTexture()
		{
			if (!IsValid)
				return IntPtr::Zero;

			return m_pTexture;
		}
		/// <summary>
		/// Gets the complete size of this texture.
		/// </summary>
		/// <returns>The size of this texture.</returns>
		Size GetSize()
		{
			if (!IsValid)
				return Size::Empty;

			return m_sSize;
		}

		/// <summary>
		/// Gets the aspect ratio of this texture.
		/// </summary>
		/// <returns>The aspect ratio of this texture.</returns>
		float GetAspectRatio()
		{
			if (!IsValid)
				return 0.0F;

			return (float)(m_sSize.Width / m_sSize.Height);
		}
		/// <summary>
		/// Gets the width of this texture.
		/// </summary>
		/// <returns>The width of this texture.</returns>
		int GetWidth()
		{
			if (!IsValid)
				return 0;

			return m_sSize.Width;
		}
		/// <summary>
		/// Gets the height of this texture.
		/// </summary>
		/// <returns>The height of this texture.</returns>
		int GetHeight()
		{
			if (!IsValid)
				return 0;

			return m_sSize.Height;
		}

	public:
		ImTexture(IntPtr texturePointer, Size textureSize)
		{
			m_pTexture = texturePointer;
			m_sSize = textureSize;
			IsValid = true;
		}

		// Explicit operator
		//static explicit operator IntPtr(ImTexture^ t)
		//{
		//	return t->GetTexture();
		//}

		// Implicit operator
		static operator IntPtr(ImTexture^ t)
		{
			return t->GetTexture();
		}

	internal:
		bool m_bIsValid;
		IntPtr m_pTexture;
		Size m_sSize;
	};

	public ref class ImGuiIV
	{
	internal:
		static ImGuiID DockspaceWindowID;
#if _DEBUG
		static ImGuiID IVSDKDotNetWrapperDebugWindowID;
#endif // _DEBUG

		static array<String^>^ FontNameSplitArray = gcnew array<String^>(1) { "," };

	public:

		/// <summary>
		/// Gets if ImGui was initialized.
		/// </summary>
		static property bool WasImGuiInitialized
		{
		public:
			bool get()
			{
				return m_bWasImGuiInitialized;
			}
		internal:
			void set(bool value)
			{
				m_bWasImGuiInitialized = value;
			}
		}

		/// <summary>
		/// Gets or sets if controller input should be disabled.
		/// </summary>
		static property bool DisableControllerInput
		{
		public:
			bool get()
			{
				return m_bDisableControllerInput;
			}
			void set(bool value)
			{
				m_bDisableControllerInput = value;
			}
		}
		/// <summary>
		/// Gets or sets if mouse input should be disabled.
		/// </summary>
		static property bool DisableMouseInput
		{
		public:
			bool get()
			{
				return m_bDisableMouseInput;
			}
			void set(bool value)
			{
				m_bDisableMouseInput = value;
			}
		}
		/// <summary>
		/// Gets or sets if keyboard input should be disabled.
		/// </summary>
		static property bool DisableKeyboardInput
		{
		public:
			bool get()
			{
				return m_bDisableKeyboardInput;
			}
			void set(bool value)
			{
				m_bDisableKeyboardInput = value;
			}
		}

		/// <summary>
		/// Gets or sets if the cursor is currently forced to be drawn on screen.
		/// </summary>
		static property bool ForceCursor
		{
		public:
			bool get()
			{
				return m_bForceCursor;
			}
			void set(bool value)
			{
				m_bForceCursor = value;
			}
		}

		/// <summary>
		/// Min normalized positive value.
		/// </summary>
		static property float FloatMin
		{
		public:
			float get()
			{
				return -FLT_MIN;
			}
		}

		/// <summary>
		/// Gets the number of active script windows..
		/// </summary>
		static property int ActiveScriptWindows
		{
		public:
			int get()
			{
				return m_iActiveScriptWindows;
			}
		internal:
			void set(int value)
			{
				m_iActiveScriptWindows = value;
			}
		}

		/// <summary>
		/// Can be passed to ImGui Widgets so that they use the full width available. Uses the 'FloatMin' property for the Vector2's 'X' value.
		/// </summary>
		static property Vector2 FullWidth
		{
		public:
			Vector2 get()
			{
				return Vector2(FloatMin, 0.0F);
			}
		}

		/// <summary>
		/// Gets the main Viewport of ImGui.
		/// </summary>
		static property ImGuiIV_Viewport MainViewport
		{
		public:
			ImGuiIV_Viewport get()
			{
				ImGuiViewport* vp = ImGui::GetMainViewport();

				if (vp)
					return ImGuiIV_Viewport(vp, true);

				return ImGuiIV_Viewport(nullptr, false);
			}
		}

		// Resource stuff
	public:

		// Texture
		static bool CreateTextureFromFile(String^ fileName, [OutAttribute] IntPtr% texturePtr, [OutAttribute] int% textureWidth, [OutAttribute] int% textureHeight, [OutAttribute] eResult% result)
		{
			bool success = ManagedD3D9::CreateTextureFromFile(fileName, texturePtr, textureWidth, textureHeight, result);

			if (success)
			{
				// Register texture to script
				Assembly^ callingAssembly = Assembly::GetCallingAssembly();
				if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
					IVSDKDotNet::Manager::ManagerScript::s_Instance->Direct3D9_RegisterScriptTexture(callingAssembly == nullptr ? nullptr : callingAssembly->GetName()->Name->Replace(".ivsdk", ""), texturePtr);
			}

			return success;
		}
		static bool CreateTextureFromFile(String^ fileName, [OutAttribute] ImTexture^% texture, [OutAttribute] eResult% result)
		{
			IntPtr texturePtr;
			int textureWidth;
			int textureHeight;
			bool success = ManagedD3D9::CreateTextureFromFile(fileName, texturePtr, textureWidth, textureHeight, result);

			if (success)
			{
				// Register texture to script
				Assembly^ callingAssembly = Assembly::GetCallingAssembly();
				if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
					IVSDKDotNet::Manager::ManagerScript::s_Instance->Direct3D9_RegisterScriptTexture(callingAssembly == nullptr ? nullptr : callingAssembly->GetName()->Name->Replace(".ivsdk", ""), texturePtr);
			
				texture = gcnew ImTexture(texturePtr, Size(textureWidth, textureHeight));
			}
			else
			{
				texture = nullptr;
			}

			return success;
		}

		static bool CreateTextureFromMemory(array<System::Byte>^ data, [OutAttribute] IntPtr% texturePtr, [OutAttribute] int% textureWidth, [OutAttribute] int% textureHeight, [OutAttribute] eResult% result)
		{
			bool success = ManagedD3D9::CreateTextureFromMemory(data, texturePtr, textureWidth, textureHeight, result);

			if (success)
			{
				// Register texture to script
				Assembly^ callingAssembly = Assembly::GetCallingAssembly();
				if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
					IVSDKDotNet::Manager::ManagerScript::s_Instance->Direct3D9_RegisterScriptTexture(callingAssembly == nullptr ? nullptr : callingAssembly->GetName()->Name->Replace(".ivsdk", ""), texturePtr);
			}

			return success;
		}
		static bool CreateTextureFromMemory(array<System::Byte>^ data, [OutAttribute] ImTexture^% texture, [OutAttribute] eResult% result)
		{
			IntPtr texturePtr;
			int textureWidth;
			int textureHeight;
			bool success = ManagedD3D9::CreateTextureFromMemory(data, texturePtr, textureWidth, textureHeight, result);

			if (success)
			{
				// Register texture to script
				Assembly^ callingAssembly = Assembly::GetCallingAssembly();
				if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
					IVSDKDotNet::Manager::ManagerScript::s_Instance->Direct3D9_RegisterScriptTexture(callingAssembly == nullptr ? nullptr : callingAssembly->GetName()->Name->Replace(".ivsdk", ""), texturePtr);
			
				texture = gcnew ImTexture(texturePtr, Size(textureWidth, textureHeight));
			}
			else
			{
				texture = nullptr;
			}

			return success;
		}
		
		static bool ReleaseTexture(IntPtr% texturePtr)
		{
			return ManagedD3D9::ReleaseTexture(texturePtr);
		}

		static bool IsTextureValid(IntPtr texturePtr)
		{
			return ManagedD3D9::IsTextureValid(texturePtr);
		}

		// Font
		static bool AddFontFromFile(String^ fileName, float sizeInPixel, [OutAttribute] IntPtr% fontPtr, [OutAttribute] eResult% result)
		{
			if (ImGui::GetCurrentContext() == nullptr)
			{
				result = eResult::ImGuiNotInitialized;
				fontPtr = IntPtr::Zero;
				return false;
			}
			if (String::IsNullOrWhiteSpace(fileName))
			{
				result = eResult::InvalidName;
				fontPtr = IntPtr::Zero;
				return false;
			}

			// Get the file name with extension of the font file to be added
			String^ fileNameWithExtension = System::IO::Path::GetFileName(fileName)->ToLower();

			// Get ImGui IO
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			
			// Check if this font is already added with the given size
			for (int i = 0; i < io.Fonts->Fonts.Size; i++)
			{
				ImFont* font = io.Fonts->Fonts[i];
				
				if (!font->ConfigData)
					continue;

				String^ fontName = gcnew String(font->ConfigData->Name);

				if (String::IsNullOrWhiteSpace(fontName))
					continue;

				// Split the string at the comma character which divides the font name from the font size stored in the same char array
				fontName = fontName->Split(FontNameSplitArray, StringSplitOptions::None)[0]->ToLower();

				// Compare the font name and the font size with the one the user is trying to add
				if (fileNameWithExtension == fontName
					&& sizeInPixel == font->ConfigData->SizePixels)
				{
					result = eResult::Already;
					fontPtr = IntPtr::Zero;
					return false;
				}
			}

			msclr::interop::marshal_context ctx;

			// Try add font from file
			ImFont* font = io.Fonts->AddFontFromFileTTF(ctx.marshal_as<const char*>(fileName), sizeInPixel);

			if (font)
			{
				result = eResult::OK;
				fontPtr = IntPtr(font);
				return true;
			}

			result = eResult::Unknown;
			fontPtr = IntPtr::Zero;
			return false;
		}
		static bool AddFontFromMemory(array<System::Byte>^ data, float sizeInPixel, [OutAttribute] IntPtr% fontPtr, [OutAttribute] eResult% result)
		{
			if (ImGui::GetCurrentContext() == nullptr)
			{
				result = eResult::ImGuiNotInitialized;
				fontPtr = IntPtr::Zero;
				return false;
			}
			if (data == nullptr)
			{
				result = eResult::InvalidData;
				fontPtr = IntPtr::Zero;
				return false;
			}

			// Pin managed array
			pin_ptr<System::Byte> pinnedData = &data[0];
			unsigned char* pby = pinnedData;
			void* dataPtr = reinterpret_cast<void*>(pby);

			// Get ImGui IO
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			msclr::interop::marshal_context ctx;

			// Try add font from file
			ImFont* font = io.Fonts->AddFontFromMemoryTTF(dataPtr, data->Length, sizeInPixel);

			if (font)
			{
				result = eResult::OK;
				fontPtr = IntPtr(font);
				return true;
			}

			result = eResult::Unknown;
			fontPtr = IntPtr::Zero;
			return false;
		}

	internal:
		static IntPtr CreateTextureFromMemory(array<System::Byte>^ data)
		{
			// Pin managed array
			pin_ptr<System::Byte> pinnedData = &data[0];
			unsigned char* pby = pinnedData;
			void* dataPtr = reinterpret_cast<void*>(pby);

			msclr::interop::marshal_context ctx;

			// Try create texture
			PDIRECT3DTEXTURE9 texture;
			HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(rage::g_pDirect3DDevice, dataPtr, data->Length, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture);

			if (hr != S_OK)
			{
				WRITE_TO_DEBUG_OUTPUT(String::Format("Failed to create texture from memory via INTERNAL function! HRESULT: {0}", hr));
				return IntPtr::Zero;
			}

			return IntPtr(texture);
		}

		// Some helper
	public:
		static Color FloatRGBToColor(Vector4 vec)
		{
			int r = Convert::ToInt32(vec.X * 255.0F);
			int g = Convert::ToInt32(vec.Y * 255.0F);
			int b = Convert::ToInt32(vec.Z * 255.0F);
			int a = Convert::ToInt32(vec.W * 255.0F);

			// Validate
			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;
			if (a > 255)
				a = 255;

			return Color::FromArgb(a, r, g, b);
		}
		static Color FloatRGBToColor(Vector3 vec)
		{
			int r = Convert::ToInt32(vec.X * 255.0F);
			int g = Convert::ToInt32(vec.Y * 255.0F);
			int b = Convert::ToInt32(vec.Z * 255.0F);

			// Validate
			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			return Color::FromArgb(255, r, g, b);
		}

		static Vector4 ColorToFloatRGB(Color color)
		{
			float r = Convert::ToSingle(color.R / 255.0F);
			float g = Convert::ToSingle(color.G / 255.0F);
			float b = Convert::ToSingle(color.B / 255.0F);
			float a = Convert::ToSingle(color.A / 255.0F);

			// Validate
			if (r > 1.0F)
				r = 1.0F;
			if (r < 0.0F)
				r = 0.0F;

			if (g > 1.0F)
				g = 1.0F;
			if (g < 0.0F)
				g = 0.0F;

			if (b > 1.0F)
				b = 1.0F;
			if (b < 0.0F)
				b = 0.0F;

			if (a > 1.0F)
				a = 1.0F;
			if (a < 0.0F)
				a = 0.0F;

			return Vector4(r, g, b, a);
		}

		static bool DoesAnyWindowHasThisAdditionalFlag(String^ flag)
		{
			if (ImGui::GetCurrentContext() == nullptr)
				return false;

			ImGuiContext* ctx = ImGui::GetCurrentContext();

			for (int i = 0; i < ctx->Windows.Size; i++)
			{
				ImGuiWindow* window = ctx->Windows[i];

				// Skip if this window is the fallback window (Debug##Default)
				if (window->IsFallbackWindow)
					continue;
				// Skip if this window is the dockspace host
				if (window->Flags & ImGuiWindowFlags_DockNodeHost)
					continue;
				// Skip if this window is the dockspace window
				if (window->ID == DockspaceWindowID)
					continue;
#if _DEBUG
				// Skip if this window is the debug window
				if (window->ID == IVSDKDotNetWrapperDebugWindowID)
					continue;
#endif // _DEBUG

				// Get if window is active and a top-level window
				bool isTopLevel = (window->Flags & (ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_Popup | ImGuiWindowFlags_Tooltip)) == 0;

				if (!(isTopLevel && window->Active && !window->Collapsed && !window->Hidden))
					continue;

				ImGuiStorage* windowStorage = &window->StateStorage;

				// Check if window has this additional flag
				msclr::interop::marshal_context ctx;
				if (windowStorage->GetBool(ImGui::GetIDWithSeed(ctx.marshal_as<const char*>("eImGuiWindowFlagsEx_" + flag), nullptr, 0)))
					return true;
			}

			return false;
		}
		static int CountWindowsWhichHaveThisAdditionalFlag(String^ flag)
		{
			if (ImGui::GetCurrentContext() == nullptr)
				return 0;

			int count = 0;
			ImGuiContext* ctx = ImGui::GetCurrentContext();

			for (int i = 0; i < ctx->Windows.Size; i++)
			{
				ImGuiWindow* window = ctx->Windows[i];

				// Skip if this window is the fallback window (Debug##Default)
				if (window->IsFallbackWindow)
					continue;
				// Skip if this window is the dockspace host
				if (window->Flags & ImGuiWindowFlags_DockNodeHost)
					continue;
				// Skip if this window is the dockspace window
				if (window->ID == DockspaceWindowID)
					continue;
#if _DEBUG
				// Skip if this window is the debug window
				if (window->ID == IVSDKDotNetWrapperDebugWindowID)
					continue;
#endif // _DEBUG

				// Get if window is active and a top-level window
				bool isTopLevel = (window->Flags & (ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_Popup | ImGuiWindowFlags_Tooltip)) == 0;

				if (!(isTopLevel && window->Active && !window->Collapsed && !window->Hidden))
					continue;

				ImGuiStorage* windowStorage = &window->StateStorage;

				// Check if window has this additional flag
				msclr::interop::marshal_context ctx;
				if (windowStorage->GetBool(ImGui::GetIDWithSeed(ctx.marshal_as<const char*>("eImGuiWindowFlagsEx_" + flag), nullptr, 0)))
				{
					count++;
				}
			}

			return count;
		}
		static int GetActiveWindowCount()
		{
			if (ImGui::GetCurrentContext() == nullptr)
				return 0;

			int activeWindows = 0;

			ImGuiContext* ctx = ImGui::GetCurrentContext();
			for (int i = 0; i < ctx->Windows.Size; i++)
			{
				ImGuiWindow* window = ctx->Windows[i];

				// Skip if this window is the fallback window (Debug##Default)
				if (window->IsFallbackWindow)
					continue;
				// Skip if this window is the dockspace host
				if (window->Flags & ImGuiWindowFlags_DockNodeHost)
					continue;
				// Skip if this window is the dockspace window
				if (window->ID == DockspaceWindowID)
					continue;
#if _DEBUG
				// Skip if this window is the debug window
				if (window->ID == IVSDKDotNetWrapperDebugWindowID)
					continue;
#endif // _DEBUG

				ImGuiStorage* windowStorage = &window->StateStorage;

				// Check additional flags
				if (windowStorage->GetBool(ImGui::GetIDWithSeed("eImGuiWindowFlagsEx_NoMouseEnable", nullptr, 0)))
					continue;

				// Get if window is a top-level window
				bool isTopLevel = (window->Flags & (ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_Tooltip)) == 0; // ImGuiWindowFlags_Popup

				if (isTopLevel && window->Active && !window->Collapsed && !window->Hidden)
					activeWindows++;
			}

			return activeWindows;
		}
		static bool IsThereAnyActiveWindow()
		{
			return GetActiveWindowCount() != 0;
		}

		static ImGuiIV_InputTextState GetInputTextState(String^ label)
		{
			if (String::IsNullOrWhiteSpace(label))
				return ImGuiIV_InputTextState(nullptr, false);

			ImGuiContext& g = *ImGui::GetCurrentContext();

			ImGuiWindow* window = g.CurrentWindow;

			if (!window)
				return ImGuiIV_InputTextState(nullptr, false);

			msclr::interop::marshal_context ctx;
			ImGuiID id = window->GetID(ctx.marshal_as<const char*>(label));

			return ImGuiIV_InputTextState(ImGui::GetInputTextState(id), true);
		}

		// ImGui stuff
	public:

		//-----------------------------------------------------------------------------
		// [SECTION] MAIN CODE
		//-----------------------------------------------------------------------------
		static void PushID(String^ id)
		{
			if (String::IsNullOrWhiteSpace(id))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::PushID(ctx.marshal_as<const char*>(id));
		}
		static void PushID(String^ id_begin, String^ id_end)
		{
			if (String::IsNullOrWhiteSpace(id_begin))
				return;
			if (String::IsNullOrWhiteSpace(id_end))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::PushID(ctx.marshal_as<const char*>(id_begin), ctx.marshal_as<const char*>(id_end));
		}
		static void PushID(IntPtr ptr_id)
		{
			if (ptr_id == IntPtr::Zero)
				return;

			ImGui::PushID(ptr_id.ToPointer());
		}
		static void PushID(int int_id)
		{
			ImGui::PushID(int_id);
		}
		static void PopID()
		{
			ImGui::PopID();
		}

		static bool IsItemActive()
		{
			return ImGui::IsItemActive();
		}
		static bool IsItemDeactivated()
		{
			return ImGui::IsItemDeactivated();
		}
		static bool IsItemFocused()
		{
			return ImGui::IsItemFocused();
		}

		static bool IsItemHovered(eImGuiHoveredFlags flags)
		{
			return ImGui::IsItemHovered((ImGuiHoveredFlags)flags);
		}
		static bool IsItemHovered()
		{
			return IsItemHovered(eImGuiHoveredFlags::None);
		}
		static bool IsAnyItemHovered()
		{
			return ImGui::IsAnyItemHovered();
		}

		static void SetActiveID(ImGuiID id, IntPtr window)
		{
			if (window == IntPtr::Zero)
				ImGui::SetActiveID(id, nullptr);
			else
				ImGui::SetActiveID(id, (ImGuiWindow*)window.ToPointer());
		}
		static ImGuiID GetActiveID()
		{
			return ImGui::GetActiveID();
		}

		static void PushTabStop(bool tab_stop)
		{
			ImGui::PushTabStop(tab_stop);
		}
		static void PopTabStop()
		{
			ImGui::PopTabStop();
		}

		static Vector2 CalcTextSize(String^ text, String^ textEnd, bool hideTextAfterDoubleHash, float wrapWidth)
		{
			if (String::IsNullOrWhiteSpace(text))
				return Vector2(0.0F, ImGui::GetCurrentContext()->FontSize);

			msclr::interop::marshal_context ctx;
			return ImVec2ToVector2(ImGui::CalcTextSize(
				ctx.marshal_as<const char*>(text),
				String::IsNullOrWhiteSpace(textEnd) ? (const char*)0 : ctx.marshal_as<const char*>(textEnd),
				hideTextAfterDoubleHash,
				wrapWidth));
		}
		static Vector2 CalcTextSize(String^ text)
		{
			return CalcTextSize(text, nullptr, false, -1.0F);
		}

		static ImGuiIV_IO GetIO()
		{
			ImGuiIO* ptr = &ImGui::GetIO();

			if (!ptr)
				return ImGuiIV_IO(nullptr, false);

			return ImGuiIV_IO(ptr, true);
		}

		//-----------------------------------------------------------------------------
		// [SECTION] STYLING
		//-----------------------------------------------------------------------------
		static ImGuiIV_Style GetStyle()
		{
			ImGuiStyle* ptr = &ImGui::GetStyle();

			if (!ptr)
				return ImGuiIV_Style(nullptr, false);

			return ImGuiIV_Style(ptr, true);
		}

		static void StyleColorsDark()
		{
			ImGui::StyleColorsDark();
		}
		static void StyleColorsClassic()
		{
			ImGui::StyleColorsClassic();
		}
		static void StyleColorsLight()
		{
			ImGui::StyleColorsLight();
		}

		static void StyleLayoutDefault()
		{
			ImGuiStyle& style = ImGui::GetStyle();

			style.Alpha = 1.0f;
			style.DisabledAlpha = 0.6000000238418579f;
			style.WindowPadding = ImVec2(8.0f, 8.0f);
			style.WindowRounding = 0.0f;
			style.WindowBorderSize = 1.0f;
			style.WindowMinSize = ImVec2(32.0f, 32.0f);
			style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
			style.WindowMenuButtonPosition = ImGuiDir_Left;
			style.ChildRounding = 0.0f;
			style.ChildBorderSize = 1.0f;
			style.PopupRounding = 0.0f;
			style.PopupBorderSize = 1.0f;
			style.FramePadding = ImVec2(4.0f, 3.0f);
			style.FrameRounding = 0.0f;
			style.FrameBorderSize = 0.0f;
			style.ItemSpacing = ImVec2(8.0f, 4.0f);
			style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
			style.CellPadding = ImVec2(4.0f, 2.0f);
			style.IndentSpacing = 21.0f;
			style.ColumnsMinSpacing = 6.0f;
			style.ScrollbarSize = 14.0f;
			style.ScrollbarRounding = 9.0f;
			style.GrabMinSize = 10.0f;
			style.GrabRounding = 0.0f;
			style.TabRounding = 4.0f;
			style.TabBorderSize = 0.0f;
			style.TabMinWidthForCloseButton = 0.0f;
			style.ColorButtonPosition = ImGuiDir_Right;
			style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
			style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
		}

		//-----------------------------------------------------------------------------
		// [SECTION] WINDOW
		//-----------------------------------------------------------------------------
		static bool Begin(String^ name, bool% open, eImGuiWindowFlags flags, eImGuiWindowFlagsEx additionalFlags)
		{
			if (String::IsNullOrWhiteSpace(name))
				return false;

			msclr::interop::marshal_context ctx;

			bool pOpen = open;

			ImGuiWindowClass wClass;
			wClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingSplit;
			ImGui::SetNextWindowClass(&wClass);

			bool result = ImGui::Begin(ctx.marshal_as<const char*>(name), &pOpen, (ImGuiWindowFlags)flags);

			open = pOpen;

			// Set custom flags if Begin function returned true
			if (result)
			{
				ImGuiStorage* windowStorage = ImGui::GetStateStorage();

				//const char* titleBarContextMenuName = ctx.marshal_as<const char*>(String::Format("{0}##TitleBarPopup", name));

				//if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
				//{
				//	ImRect rect = ImGui::GetCurrentWindow()->TitleBarRect();

				//	if (ImGui::IsMouseHoveringRect(rect.Min, rect.Max, false))
				//	{
				//		ImGui::OpenPopup(titleBarContextMenuName);
				//	}
				//}

				//if (ImGui::BeginPopup(titleBarContextMenuName))
				//{
				//	
				//	if (ImGui::Selectable("Pin"))
				//	{
				//		ImGui::GetCurrentWindow()->DisableInputsFrames = 1000;
				//	}
				//	ImGui::SameLine();
				//	HelpMarker("This will pin the window to the screen at the current location disabling the ");

				//	ImGui::EndPopup();
				//}

				// Check and set flags
				if (additionalFlags.HasFlag(eImGuiWindowFlagsEx::NoMouseEnable)) // NoMouseEnable
					windowStorage->SetBool(ImGui::GetIDWithSeed("eImGuiWindowFlagsEx_NoMouseEnable", nullptr, 0), true);
				if (additionalFlags.HasFlag(eImGuiWindowFlagsEx::DisableControllerInput)) // DisableControllerInput
					windowStorage->SetBool(ImGui::GetIDWithSeed("eImGuiWindowFlagsEx_DisableControllerInput", nullptr, 0), true);
			}

			return result;
		}
		static bool Begin(String^ name, bool% open, eImGuiWindowFlags flags)
		{
			return Begin(name, open, flags, eImGuiWindowFlagsEx::None);
		}
		static bool Begin(String^ name, bool% open)
		{
			return Begin(name, open, eImGuiWindowFlags::None, eImGuiWindowFlagsEx::None);
		}
		static bool Begin(String^ name, eImGuiWindowFlags flags, eImGuiWindowFlagsEx additionalFlags)
		{
			if (String::IsNullOrWhiteSpace(name))
				return false;

			msclr::interop::marshal_context ctx;

			ImGuiWindowClass wClass;
			wClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingSplit;
			ImGui::SetNextWindowClass(&wClass);

			bool result = ImGui::Begin(ctx.marshal_as<const char*>(name), NULL, (ImGuiWindowFlags)flags);

			// Set custom flags if Begin function returned true
			if (result)
			{
				ImGuiStorage* windowStorage = ImGui::GetStateStorage();

				// Check and set flags
				if (additionalFlags.HasFlag(eImGuiWindowFlagsEx::NoMouseEnable)) // NoMouseEnable
					windowStorage->SetBool(ImGui::GetIDWithSeed("eImGuiWindowFlagsEx_NoMouseEnable", nullptr, 0), true);
				if (additionalFlags.HasFlag(eImGuiWindowFlagsEx::DisableControllerInput)) // DisableControllerInput
					windowStorage->SetBool(ImGui::GetIDWithSeed("eImGuiWindowFlagsEx_DisableControllerInput", nullptr, 0), true);
			}

			return result;
		}
		static bool Begin(String^ name, eImGuiWindowFlags flags)
		{
			return Begin(name, flags, eImGuiWindowFlagsEx::None);
		}
		static bool Begin(String^ name)
		{
			return Begin(name, eImGuiWindowFlags::None, eImGuiWindowFlagsEx::None);
		}
		static void End()
		{
			ImGui::End();
		}

		static bool BeginChild(String^ id, Vector2 size, eImGuiChildFlags childFlags, eImGuiWindowFlags windowFlags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			ImGuiWindowClass wClass;
			wClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingSplit;
			ImGui::SetNextWindowClass(&wClass);

			msclr::interop::marshal_context ctx;

			return ImGui::BeginChild(ctx.marshal_as<const char*>(id), Vector2ToImVec2(size), (ImGuiChildFlags)childFlags, (ImGuiWindowFlags)windowFlags);
		}
		static bool BeginChild(String^ id, Vector2 size, eImGuiChildFlags childFlags)
		{
			return BeginChild(id, size, childFlags, eImGuiWindowFlags::None);
		}
		static bool BeginChild(String^ id, Vector2 size)
		{
			return BeginChild(id, size, eImGuiChildFlags::None, eImGuiWindowFlags::None);
		}
		static bool BeginChild(String^ id)
		{
			return BeginChild(id, Vector2::Zero, eImGuiChildFlags::None, eImGuiWindowFlags::None);
		}
		static void EndChild()
		{
			ImGui::EndChild();
		}

		static void SetNextWindowBgAlpha(float alpha)
		{
			ImGui::SetNextWindowBgAlpha(alpha);
		}

		static IntPtr FindWindowById(ImGuiID id)
		{
			return IntPtr(ImGui::FindWindowByID(id));
		}
		static IntPtr FindWindowByName(String^ name)
		{
			if (String::IsNullOrWhiteSpace(name))
				return IntPtr::Zero;

			msclr::interop::marshal_context ctx;
			return IntPtr(ImGui::FindWindowByName(ctx.marshal_as<const char*>(name)));
		}
		static ImGuiIV_DrawingContext GetWindowDrawList()
		{
			ImDrawList* ptr = ImGui::GetWindowDrawList();

			if (!ptr)
				return ImGuiIV_DrawingContext(nullptr, false);

			return ImGuiIV_DrawingContext(ptr, true);
		}
		static ImGuiIV_DrawingContext GetBackgroundDrawList()
		{
			ImDrawList* ptr = ImGui::GetBackgroundDrawList();

			if (!ptr)
				return ImGuiIV_DrawingContext(nullptr, false);

			return ImGuiIV_DrawingContext(ptr, true);
		}
		static ImGuiIV_DrawingContext GetForegroundDrawList()
		{
			ImDrawList* ptr = ImGui::GetForegroundDrawList();

			if (!ptr)
				return ImGuiIV_DrawingContext(nullptr, false);

			return ImGuiIV_DrawingContext(ptr, true);
		}

		static float GetWindowWidth()
		{
			return ImGui::GetWindowWidth();
		}
		static float GetWindowHeight()
		{
			return ImGui::GetWindowHeight();
		}

		static Vector2 GetWindowPos()
		{
			return ImVec2ToVector2(ImGui::GetWindowPos());
		}
		static Vector2 GetWindowSize()
		{
			return ImVec2ToVector2(ImGui::GetWindowSize());
		}

		static void SetNextWindowPos(Vector2 pos, eImGuiCond cond, Vector2 pivot)
		{
			ImGui::SetNextWindowPos(Vector2ToImVec2(pos), (ImGuiCond)cond, Vector2ToImVec2(pivot));
		}
		static void SetNextWindowPos(Vector2 pos, eImGuiCond cond)
		{
			ImGui::SetNextWindowPos(Vector2ToImVec2(pos), (ImGuiCond)cond);
		}
		static void SetNextWindowPos(Vector2 pos)
		{
			SetNextWindowPos(pos, eImGuiCond::None);
		}
		static void SetNextWindowSize(Vector2 size, eImGuiCond cond)
		{
			ImGui::SetNextWindowSize(Vector2ToImVec2(size), (ImGuiCond)cond);
		}
		static void SetNextWindowSize(Vector2 size)
		{
			SetNextWindowSize(size, eImGuiCond::None);
		}

		static void SetWindowPos(String^ name, Vector2 pos, eImGuiCond cond)
		{
			if (String::IsNullOrWhiteSpace(name))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::SetWindowPos(ctx.marshal_as<const char*>(name), Vector2ToImVec2(pos), (ImGuiCond)cond);
		}
		static void SetWindowPos(String^ name, Vector2 pos)
		{
			SetWindowPos(name, pos, eImGuiCond::None);
		}
		static void SetWindowPos(IntPtr window, Vector2 pos, eImGuiCond cond)
		{
			if (window == IntPtr::Zero)
				return;

			ImGui::SetWindowPos((ImGuiWindow*)window.ToPointer(), Vector2ToImVec2(pos), (ImGuiCond)cond);
		}
		static void SetWindowPos(IntPtr window, Vector2 pos)
		{
			SetWindowPos(window, pos, eImGuiCond::None);
		}
		static void SetWindowPos(Vector2 pos, eImGuiCond cond)
		{
			ImGui::SetWindowPos(Vector2ToImVec2(pos), (ImGuiCond)cond);
		}
		static void SetWindowPos(Vector2 pos)
		{
			SetWindowPos(pos, eImGuiCond::None);
		}

		static void SetWindowSize(String^ name, Vector2 size, eImGuiCond cond)
		{
			if (String::IsNullOrWhiteSpace(name))
				return;
			
			msclr::interop::marshal_context ctx;
			ImGui::SetWindowSize(ctx.marshal_as<const char*>(name), Vector2ToImVec2(size), (ImGuiCond)cond);
		}
		static void SetWindowSize(String^ name, Vector2 size)
		{
			SetWindowSize(name, size, eImGuiCond::None);
		}
		static void SetWindowSize(IntPtr window, Vector2 size, eImGuiCond cond)
		{
			if (window == IntPtr::Zero)
				return;

			ImGui::SetWindowSize((ImGuiWindow*)window.ToPointer(), Vector2ToImVec2(size), (ImGuiCond)cond);
		}
		static void SetWindowSize(IntPtr window, Vector2 size)
		{
			SetWindowSize(window, size, eImGuiCond::None);
		}
		static void SetWindowSize(Vector2 size, eImGuiCond cond)
		{
			ImGui::SetWindowSize(Vector2ToImVec2(size), (ImGuiCond)cond);
		}
		static void SetWindowSize(Vector2 size)
		{
			SetWindowSize(size, eImGuiCond::None);
		}

		static void BeginDisabled(bool disabled)
		{
			ImGui::BeginDisabled(disabled);
		}
		static void BeginDisabled()
		{
			BeginDisabled(true);
		}
		static void EndDisabled()
		{
			ImGui::EndDisabled();
		}

		static void GcCompactTransientWindowBuffers(IntPtr windowPtr)
		{
			if (windowPtr == IntPtr::Zero)
				return;

			ImGui::GcCompactTransientWindowBuffers((ImGuiWindow*)windowPtr.ToPointer());
		}

		static IntPtr GetCurrentWindow()
		{
			return IntPtr(ImGui::GetCurrentWindow());
		}

		static bool IsWindowHovered(eImGuiHoveredFlags flags)
		{
			return ImGui::IsWindowHovered((ImGuiHoveredFlags)flags);
		}
		static bool IsWindowHovered()
		{
			return IsWindowHovered(eImGuiHoveredFlags::None);
		}
		static bool IsWindowCollapsed()
		{
			return ImGui::IsWindowCollapsed();
		}
		static bool IsWindowAppearing()
		{
			return ImGui::IsWindowAppearing();
		}

		//-----------------------------------------------------------------------------
		// [SECTION] FOCUS
		//-----------------------------------------------------------------------------
		static void SetWindowFocus(String^ name)
		{
			if (String::IsNullOrWhiteSpace(name))
			{
				ImGui::SetWindowFocus(nullptr);
			}
			else
			{
				msclr::interop::marshal_context ctx;
				ImGui::SetWindowFocus(ctx.marshal_as<const char*>(name));
			}
		}
		static void SetWindowFocus()
		{
			ImGui::SetWindowFocus();
		}
		static void SetNextWindowFocus()
		{
			ImGui::SetNextWindowFocus();
		}
		static void SetKeyboardFocusHere(int offset)
		{
			ImGui::SetKeyboardFocusHere(offset);
		}
		static void SetKeyboardFocusHere()
		{
			SetKeyboardFocusHere(0);
		}

		static void FocusWindow(IntPtr window)
		{
			if (window == IntPtr::Zero)
				return;

			ImGui::FocusWindow((ImGuiWindow*)window.ToPointer());
		}
		static void BringWindowToFocusFront(IntPtr window)
		{
			if (window == IntPtr::Zero)
				return;

			ImGui::BringWindowToFocusFront((ImGuiWindow*)window.ToPointer());
		}

		static bool IsAnyItemFocused()
		{
			return ImGui::IsAnyItemFocused();
		}
		static bool IsWindowFocused(eImGuiFocusedFlags flags)
		{
			return ImGui::IsWindowFocused((ImGuiFocusedFlags)flags);
		}
		static bool IsWindowFocused()
		{
			return IsWindowFocused(eImGuiFocusedFlags::None);
		}

		static ImGuiID GetFocusID()
		{
			return ImGui::GetFocusID();
		}
		static void SetFocusID(ImGuiID id, IntPtr window)
		{
			if (window == IntPtr::Zero)
				return;

			ImGui::SetFocusID(id, (ImGuiWindow*)window.ToPointer());
		}

		//-----------------------------------------------------------------------------
		// [SECTION] STYLE
		//-----------------------------------------------------------------------------
		static void PushStyleVar(eImGuiStyleVar idx, Vector2 value)
		{
			ImGui::PushStyleVar((ImGuiStyleVar)idx, Vector2ToImVec2(value));
		}
		static void PushStyleVar(eImGuiStyleVar idx, float value)
		{
			ImGui::PushStyleVar((ImGuiStyleVar)idx, value);
		}

		static void PushStyleColor(eImGuiCol idx, Vector4 color)
		{
			ImGui::PushStyleColor((ImGuiCol)idx, Vector4ToImVec4(color));
		}
		static void PushStyleColor(eImGuiCol idx, Color color)
		{
			ImGui::PushStyleColor((ImGuiCol)idx, ColorToImU32(color));
		}

		static void PopStyleVar(int count)
		{
			ImGui::PopStyleVar(count);
		}
		static void PopStyleVar()
		{
			PopStyleVar(1);
		}
		static void PopStyleColor(int count)
		{
			ImGui::PopStyleColor(count);
		}
		static void PopStyleColor()
		{
			PopStyleColor(1);
		}

		//-----------------------------------------------------------------------------
		// [SECTION] INPUT
		//-----------------------------------------------------------------------------
		static String^ GetKeyName(eImGuiKey key)
		{
			return gcnew String(ImGui::GetKeyName((ImGuiKey)(int)key));
		}
		static int GetKeyPressedAmount(eImGuiKey key, float repeatDelay, float repeatRate)
		{
			return ImGui::GetKeyPressedAmount((ImGuiKey)(int)key, repeatDelay, repeatRate);
		}

		static bool IsKeyDown(eImGuiKey key, ImGuiID ownerId)
		{
			return ImGui::IsKeyDown((ImGuiKey)(int)key, ownerId);
		}
		static bool IsKeyDown(eImGuiKey key)
		{
			return ImGui::IsKeyDown((ImGuiKey)(int)key);
		}

		static bool IsKeyPressed(eImGuiKey key, ImGuiID ownerId, eImGuiInputFlags flags)
		{
			return ImGui::IsKeyPressed((ImGuiKey)(int)key, ownerId, (ImGuiInputFlags)(int)flags);
		}
		static bool IsKeyPressed(eImGuiKey key, bool repeat)
		{
			return ImGui::IsKeyPressed((ImGuiKey)(int)key, repeat);
		}
		static bool IsKeyPressed(eImGuiKey key)
		{
			return IsKeyPressed(key, true);
		}

		static bool IsKeyReleased(eImGuiKey key)
		{
			return ImGui::IsKeyReleased((ImGuiKey)(int)key);
		}
		static bool IsKeyReleased(eImGuiKey key, ImGuiID ownerId)
		{
			return ImGui::IsKeyReleased((ImGuiKey)(int)key, ownerId);
		}

		static bool IsMouseDown(eImGuiMouseButton button)
		{
			return ImGui::IsMouseDown((ImGuiMouseButton)(int)button);
		}
		static bool IsMouseDown(eImGuiMouseButton button, ImGuiID ownerId)
		{
			return ImGui::IsMouseDown((ImGuiMouseButton)(int)button, ownerId);
		}
		static bool IsMouseClicked(eImGuiMouseButton button)
		{
			return ImGui::IsMouseClicked((ImGuiMouseButton)(int)button);
		}
		static bool IsMouseClicked(eImGuiMouseButton button, ImGuiID ownerId)
		{
			return ImGui::IsMouseClicked((ImGuiMouseButton)(int)button, ownerId);
		}
		static bool IsMouseReleased(eImGuiMouseButton button)
		{
			return ImGui::IsMouseReleased((ImGuiMouseButton)(int)button);
		}
		static bool IsMouseReleased(eImGuiMouseButton button, ImGuiID ownerId)
		{
			return ImGui::IsMouseReleased((ImGuiMouseButton)(int)button, ownerId);
		}
		static bool IsMouseDoubleClicked(eImGuiMouseButton button)
		{
			return ImGui::IsMouseDoubleClicked((ImGuiMouseButton)(int)button);
		}
		static int GetMouseClickedCount(eImGuiMouseButton button)
		{
			return ImGui::GetMouseClickedCount((ImGuiMouseButton)(int)button);
		}

		static bool IsMouseHoveringRect(RectangleF rect, bool clip)
		{
			if (rect == RectangleF::Empty)
				return false;

			return ImGui::IsMouseHoveringRect(ImVec2(rect.X, rect.Y), ImVec2(rect.Right, rect.Bottom), clip);
		}
		static bool IsMouseDragPastThreshold(eImGuiMouseButton button, float lockThreshold)
		{
			return ImGui::IsMouseDragPastThreshold((ImGuiMouseButton)(int)button, lockThreshold);
		}
		static bool IsMouseDragging(eImGuiMouseButton button, float lockThreshold)
		{
			return ImGui::IsMouseDragging((ImGuiMouseButton)(int)button, lockThreshold);
		}

		static bool WantsTextInput()
		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			return io.WantTextInput;
		}

		static Vector2 GetMousePos()
		{
			return ImVec2ToVector2(ImGui::GetMousePos());
		}
		static Vector2 GetMouseDragDelta(ImGuiMouseButton button, float lockThreshold)
		{
			return ImVec2ToVector2(ImGui::GetMouseDragDelta((ImGuiMouseButton)(int)button, lockThreshold));
		}
		static void ResetMouseDragDelta(eImGuiMouseButton button)
		{
			ImGui::ResetMouseDragDelta((ImGuiMouseButton)(int)button);
		}
		static void TeleportMousePos(Vector2 pos)
		{
			ImGui::TeleportMousePos(Vector2ToImVec2(pos));
		}

		static eImGuiMouseCursor GetMouseCursor()
		{
			return (eImGuiMouseCursor)(int)ImGui::GetMouseCursor();
		}
		static void SetMouseCursor(eImGuiMouseCursor type)
		{
			ImGui::SetMouseCursor((ImGuiMouseCursor)(int)type);
		}

		static Vector2 GetCursorScreenPos()
		{
			return ImVec2ToVector2(ImGui::GetCursorScreenPos());
		}
		static void SetCursorScreenPos(Vector2 pos)
		{
			ImGui::SetCursorScreenPos(Vector2ToImVec2(pos));
		}
		static Vector2 GetCursorPos()
		{
			return ImVec2ToVector2(ImGui::GetCursorPos());
		}
		static float GetCursorPosX()
		{
			return ImGui::GetCursorPosX();
		}
		static float GetCursorPosY()
		{
			return ImGui::GetCursorPosY();
		}
		static void SetCursorPos(Vector2 localPos)
		{
			ImGui::SetCursorPos(Vector2ToImVec2(localPos));
		}
		static void SetCursorPosX(float x)
		{
			ImGui::SetCursorPosX(x);
		}
		static void SetCursorPosY(float y)
		{
			ImGui::SetCursorPosY(y);
		}
		static Vector2 GetCursorStartPos()
		{
			return ImVec2ToVector2(ImGui::GetCursorStartPos());
		}

		static void SetItemDefaultFocus()
		{
			ImGui::SetItemDefaultFocus();
		}

		static float GetKeyAnalogValue(eImGuiKey key)
		{
			return ImGui::GetKeyData((ImGuiKey)(int)key)->AnalogValue;
		}

		//-----------------------------------------------------------------------------
		// [SECTION] FONT
		//-----------------------------------------------------------------------------
		static void PushFont(IntPtr fontPtr)
		{
			if (fontPtr == IntPtr::Zero)
				return;

			ImGui::PushFont((ImFont*)fontPtr.ToPointer());
		}
		static void PopFont()
		{
			ImGui::PopFont();
		}

		static IntPtr GetFont()
		{
			return IntPtr(ImGui::GetFont());
		}
		static float GetFontSize()
		{
			return ImGui::GetFontSize();
		}
		static Vector2 GetFontTexUvWhitePixel()
		{
			return ImVec2ToVector2(ImGui::GetFontTexUvWhitePixel());
		}

		static void SetWindowFontScale(float scale)
		{
			if (scale > 0.0F)
				return;

			ImGui::SetWindowFontScale(scale);
		}

		//-----------------------------------------------------------------------------
		// [SECTION] LAYOUT
		//-----------------------------------------------------------------------------
		static void ItemSize(Vector2 size, float textBaselineY)
		{
			ImGui::ItemSize(Vector2ToImVec2(size), textBaselineY);
		}

		static void SameLine(float offsetFromStartX, float spacing)
		{
			ImGui::SameLine(offsetFromStartX, spacing);
		}
		static void SameLine()
		{
			SameLine(0.0F, -1.0F);
		}

		static void Indent(float indentW)
		{
			ImGui::Indent(indentW);
		}
		static void Unindent(float indentW)
		{
			ImGui::Unindent(indentW);
		}

		static void SetNextItemWidth(float width)
		{
			ImGui::SetNextItemWidth(width);
		}

		static void PushTextWrapPos(float wrap_local_pos_x)
		{
			ImGui::PushTextWrapPos(wrap_local_pos_x);
		}
		static void PopTextWrapPos()
		{
			ImGui::PopTextWrapPos();
		}

		static void PushItemWidth(float width)
		{
			ImGui::PushItemWidth(width);
		}
		static void PushMultiItemsWidths(int components, float widthFull)
		{
			ImGui::PushMultiItemsWidths(components, widthFull);
		}
		static void PopItemWidth()
		{
			ImGui::PopItemWidth();
		}

		static float CalcItemWidth()
		{
			return ImGui::CalcItemWidth();
		}
		static Vector2 CalcItemSize(Vector2 size, float defaultW, float defaultH)
		{
			return ImVec2ToVector2(ImGui::CalcItemSize(Vector2ToImVec2(size), defaultW, defaultH));
		}

		static float GetTextLineHeight()
		{
			return ImGui::GetTextLineHeight();
		}
		static float GetTextLineHeightWithSpacing()
		{
			return ImGui::GetTextLineHeightWithSpacing();
		}
		static float GetFrameHeight()
		{
			return ImGui::GetFrameHeight();
		}
		static float GetFrameHeightWithSpacing()
		{
			return ImGui::GetFrameHeightWithSpacing();
		}

		static Vector2 GetContentRegionMax()
		{
			return ImVec2ToVector2(ImGui::GetContentRegionMax());
		}
		static Vector2 GetContentRegionAvail()
		{
			return ImVec2ToVector2(ImGui::GetContentRegionAvail());
		}
		static Vector2 GetWindowContentRegionMin()
		{
			return ImVec2ToVector2(ImGui::GetWindowContentRegionMin());
		}
		static Vector2 GetWindowContentRegionMax()
		{
			return ImVec2ToVector2(ImGui::GetWindowContentRegionMax());
		}

		static Vector2 GetItemRectMin()
		{
			return ImVec2ToVector2(ImGui::GetItemRectMin());
		}
		static Vector2 GetItemRectMax()
		{
			return ImVec2ToVector2(ImGui::GetItemRectMax());
		}
		static Vector2 GetItemRectSize()
		{
			return ImVec2ToVector2(ImGui::GetItemRectSize());
		}

		static void BeginGroup()
		{
			ImGui::BeginGroup();
		}
		static void EndGroup()
		{
			ImGui::EndGroup();
		}

		//-----------------------------------------------------------------------------
		// [SECTION] SCROLLING
		//-----------------------------------------------------------------------------
		static void ScrollToItem(eImGuiScrollFlags flags)
		{
			ImGui::ScrollToItem((ImGuiScrollFlags)flags);
		}

		static float GetScrollX()
		{
			return ImGui::GetScrollX();
		}
		static float GetScrollY()
		{
			return ImGui::GetScrollY();
		}
		static float GetScrollMaxX()
		{
			return ImGui::GetScrollMaxX();
		}
		static float GetScrollMaxY()
		{
			return ImGui::GetScrollMaxY();
		}
		static void SetScrollX(float x)
		{
			ImGui::SetScrollX(x);
		}
		static void SetScrollY(float y)
		{
			ImGui::SetScrollY(y);
		}

		static void SetScrollFromPosX(float localX, float centerXRatio)
		{
			ImGui::SetScrollFromPosX(localX, centerXRatio);
		}
		static void SetScrollFromPosY(float localY, float centerYRatio)
		{
			ImGui::SetScrollFromPosY(localY, centerYRatio);
		}

		static void SetScrollHereX(float centerXRatio)
		{
			ImGui::SetScrollHereX(centerXRatio);
		}
		static void SetScrollHereY(float centerYRatio)
		{
			ImGui::SetScrollHereY(centerYRatio);
		}

		//-----------------------------------------------------------------------------
		// [SECTION] TOOLTIPS
		//-----------------------------------------------------------------------------
		static bool BeginTooltip()
		{
			return ImGui::BeginTooltip();
		}
		static bool BeginItemTooltip()
		{
			return ImGui::BeginItemTooltip();
		}
		static bool BeginTooltipEx(eImGuiTooltipFlags tooltipFlags, eImGuiWindowFlags extraWindowFlags)
		{
			return ImGui::BeginTooltipEx((ImGuiTooltipFlags)tooltipFlags, (ImGuiWindowFlags)extraWindowFlags);
		}
		static void EndTooltip()
		{
			ImGui::EndTooltip();
		}

		static void SetTooltip(String^ text, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(text))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::SetTooltip(ctx.marshal_as<const char*>(String::Format(text, args)));
		}

		static void SetItemTooltip(String^ text, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(text))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::SetItemTooltip(ctx.marshal_as<const char*>(String::Format(text, args)));
		}

		static bool ImagePreviewToolTip(IntPtr txtPtr, Vector2 imageSize, Vector2 cursorScreenPos, float regionSize, float zoom, Color tintColor, Color borderColor)
		{
			if (txtPtr == IntPtr::Zero)
				return false;

			if (BeginItemTooltip())
			{
				ImVec2 mousePos = ImGui::GetIO().MousePos;

				float region_x = mousePos.x - cursorScreenPos.X - regionSize * 0.5f;
				float region_y = mousePos.y - cursorScreenPos.Y - regionSize * 0.5f;

				if (region_x < 0.0f)
					region_x = 0.0f;
				else if (region_x > imageSize.X - regionSize)
					region_x = imageSize.X - regionSize;

				if (region_y < 0.0f)
					region_y = 0.0f;
				else if (region_y > imageSize.Y - regionSize)
					region_y = imageSize.Y - regionSize;

				Vector2 uv0 = Vector2((region_x) / imageSize.X, (region_y) / imageSize.Y);
				Vector2 uv1 = Vector2((region_x + regionSize) / imageSize.X, (region_y + regionSize) / imageSize.Y);
				ImGuiIV::Image(txtPtr, Vector2(regionSize * zoom, regionSize * zoom), uv0, uv1, tintColor, borderColor);

				EndTooltip();
				return true;
			}

			return false;
		}
		static bool ImagePreviewToolTip(IntPtr txtPtr, Vector2 imageSize, Vector2 cursorScreenPos, float regionSize, float zoom)
		{
			return ImagePreviewToolTip(txtPtr, imageSize, cursorScreenPos, regionSize, zoom, Color::White, Color::Transparent);
		}

		//-----------------------------------------------------------------------------
		// [SECTION] POPUPS
		//-----------------------------------------------------------------------------
		static bool IsPopupOpen(ImGuiID id, eImGuiPopupFlags flags)
		{
			return ImGui::IsPopupOpen(id, (ImGuiPopupFlags)flags);
		}
		static bool IsPopupOpen(String^ id, eImGuiPopupFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::IsPopupOpen(ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}
		static bool IsPopupOpen(String^ id)
		{
			return IsPopupOpen(id, eImGuiPopupFlags::None);
		}

		static void OpenPopup(ImGuiID id, eImGuiPopupFlags flags)
		{
			ImGui::OpenPopup(id, (ImGuiPopupFlags)flags);
		}
		static void OpenPopup(String^ id, eImGuiPopupFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::OpenPopup(ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}
		static void OpenPopup(ImGuiID id)
		{
			ImGui::OpenPopup(id);
		}
		static void OpenPopup(String^ id)
		{
			if(String::IsNullOrWhiteSpace(id))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::OpenPopup(ctx.marshal_as<const char*>(id));
		}

		static void OpenPopupEx(ImGuiID id, eImGuiPopupFlags flags)
		{
			return ImGui::OpenPopupEx(id, (ImGuiPopupFlags)flags);
		}

		static void ClosePopupsExceptModals()
		{
			ImGui::ClosePopupsExceptModals();
		}
		static void ClosePopupToLevel(int remaining, bool restoreFocusToWindowUnderPopup)
		{
			ImGui::ClosePopupToLevel(remaining, restoreFocusToWindowUnderPopup);
		}
		static void CloseCurrentPopup()
		{
			ImGui::CloseCurrentPopup();
		}

		static bool BeginPopupEx(ImGuiID id, eImGuiWindowFlags flags)
		{
			return ImGui::BeginPopupEx(id, (ImGuiWindowFlags)flags);
		}
		static bool BeginPopup(String^ id, eImGuiWindowFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopup(ctx.marshal_as<const char*>(id), (ImGuiWindowFlags)flags);
		}
		static bool BeginPopupModal(String^ id, bool% open, eImGuiWindowFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;

			bool pOpen = open;

			bool result = ImGui::BeginPopupModal(ctx.marshal_as<const char*>(id), &pOpen, (ImGuiWindowFlags)flags);

			open = pOpen;
			return result;
		}
		static bool BeginPopupModal(String^ id, eImGuiWindowFlags flags)
		{
			if(String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopupModal(ctx.marshal_as<const char*>(id), NULL, (ImGuiWindowFlags)flags);
		}
		static bool BeginPopupModal(String^ id, bool% open)
		{
			if(String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;

			bool pOpen = open;

			bool result = ImGui::BeginPopupModal(ctx.marshal_as<const char*>(id), &pOpen);

			open = pOpen;
			return result;
		}
		static bool BeginPopupModal(String^ id)
		{
			if(String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopupModal(ctx.marshal_as<const char*>(id));
		}
		static void EndPopup()
		{
			ImGui::EndPopup();
		}

		static void OpenPopupOnItemClick(String^ id, eImGuiPopupFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::OpenPopupOnItemClick(ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}
		static bool BeginPopupContextItem(String^ id, eImGuiPopupFlags flags)
		{
			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopupContextItem(String::IsNullOrWhiteSpace(id) ? (const char*)0 : ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}
		static bool BeginPopupContextItem()
		{
			return BeginPopupContextItem(nullptr, eImGuiPopupFlags::MouseButtonRight);
		}
		static bool BeginPopupContextWindow(String^ id, eImGuiPopupFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopupContextWindow(ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}
		static bool BeginPopupContextVoid(String^ id, eImGuiPopupFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginPopupContextVoid(ctx.marshal_as<const char*>(id), (ImGuiPopupFlags)flags);
		}

		static bool CreateSimplePopupDialog(String^ id, String^ description, Vector2 size, eImGuiWindowFlags flags, bool centerInMiddleOfScreen, bool showButtonOne, bool showButtonTwo, String^ buttonOneName, String^ buttonTwoName, Action^ buttonOneAction, Action^ buttonTwoAction)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;
			if (String::IsNullOrWhiteSpace(description))
				return false;

			if (BeginPopupModal(id, flags))
			{
				ImGui::SetWindowSize(Vector2ToImVec2(size));

				bool result = true;

				Text(description);
				Separator();

				// Button 1
				if (showButtonOne)
				{
					if (Button(buttonOneName, Vector2(120.0F, 0.0F)))
					{
						if (buttonOneAction)
							buttonOneAction();
						CloseCurrentPopup();
						result = false;
					}
				}

				SameLine();

				// Button 2
				if (showButtonTwo)
				{
					if (Button(buttonTwoName, Vector2(120.0F, 0.0F)))
					{
						if (buttonTwoAction)
							buttonTwoAction();
						CloseCurrentPopup();
						result = false;
					}
				}

				EndPopup();

				return result;
			}

			return false;
		}
		static bool CreateSimplePopupDialog(String^ id, String^ description, bool centerInMiddleOfScreen, bool showButtonOne, bool showButtonTwo, String^ buttonOneName, String^ buttonTwoName, Action^ buttonOneAction, Action^ buttonTwoAction)
		{
			return CreateSimplePopupDialog(id, description, Vector2::Zero, eImGuiWindowFlags::AlwaysAutoResize, centerInMiddleOfScreen, showButtonOne, showButtonTwo, buttonOneName, buttonTwoName, buttonOneAction, buttonTwoAction);
		}

		static RectangleF GetPopupAllowedExtentRect(IntPtr window)
		{
			if (window == IntPtr::Zero)
				return RectangleF::Empty;

			return ImRectToRectangleF(ImGui::GetPopupAllowedExtentRect((ImGuiWindow*)window.ToPointer()));
		}
		static Vector2 FindBestWindowPosForPopup(IntPtr window)
		{
			if (window == IntPtr::Zero)
				return Vector2::Zero;

			return ImVec2ToVector2(ImGui::FindBestWindowPosForPopup((ImGuiWindow*)window.ToPointer()));
		}

		//-----------------------------------------------------------------------------
		// [SECTION] DRAG AND DROP
		//-----------------------------------------------------------------------------
		static bool IsDragDropActive()
		{
			return ImGui::IsDragDropActive();
		}
		static void ClearDragDrop()
		{
			ImGui::ClearDragDrop();
		}

		static bool BeginDragDropSource(eImGuiDragDropFlags flags)
		{
			return ImGui::BeginDragDropSource((ImGuiDragDropFlags)flags);
		}
		static void EndDragDropSource()
		{
			ImGui::EndDragDropSource();
		}

		static bool SetDragDropPayload(String^ type, IntPtr data, uint32_t dataSize, eImGuiCond cond)
		{
			if (String::IsNullOrWhiteSpace(type))
				return false;
			if (data == IntPtr::Zero)
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::SetDragDropPayload(ctx.marshal_as<const char*>(type), data.ToPointer(), dataSize, (ImGuiCond)cond);
		}

		static bool BeginDragDropTargetCustom(RectangleF bb, ImGuiID id)
		{
			return ImGui::BeginDragDropTargetCustom(RectangleFToImRect(bb), id);
		}
		static bool BeginDragDropTarget()
		{
			return ImGui::BeginDragDropTarget();
		}

		static bool IsDragDropPayloadBeingAccepted()
		{
			return ImGui::IsDragDropPayloadBeingAccepted();
		}

		static ImGuiIV_Payload AcceptDragDropPayload(String^ type, eImGuiDragDropFlags flags)
		{
			if (String::IsNullOrWhiteSpace(type))
				return ImGuiIV_Payload(nullptr, false);

			msclr::interop::marshal_context ctx;
			const ImGuiPayload* ptr = ImGui::AcceptDragDropPayload(ctx.marshal_as<const char*>(type), (ImGuiDragDropFlags)flags);

			if (!ptr)
				return ImGuiIV_Payload(nullptr, false);

			return ImGuiIV_Payload(const_cast<ImGuiPayload*>(ptr), true);
		}
		static ImGuiIV_Payload AcceptDragDropPayload(String^ type)
		{
			return AcceptDragDropPayload(type, eImGuiDragDropFlags::None);
		}

		static ImGuiIV_Payload GetDragDropPayload()
		{
			const ImGuiPayload* ptr = ImGui::GetDragDropPayload();

			if (!ptr)
				return ImGuiIV_Payload(nullptr, false);

			return ImGuiIV_Payload(const_cast<ImGuiPayload*>(ptr), true);
		}

		static void RenderDragDropTargetRect(RectangleF bb, RectangleF itemClipRect)
		{
			ImGui::RenderDragDropTargetRect(RectangleFToImRect(bb), RectangleFToImRect(itemClipRect));
		}
		static void EndDragDropTarget()
		{
			ImGui::EndDragDropTarget();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: Text, etc.
		//-------------------------------------------------------------------------
		static void Text(String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::Text(ctx.marshal_as<const char*>(String::Format(str, args)));
		}
		static void TextUnformatted(String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::TextUnformatted(ctx.marshal_as<const char*>(String::Format(str, args)));
		}
		static void TextDisabled(String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::TextDisabled(ctx.marshal_as<const char*>(String::Format(str, args)));
		}
		static void TextWrapped(String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;
			
			msclr::interop::marshal_context ctx;
			ImGui::TextWrapped(ctx.marshal_as<const char*>(String::Format(str, args)));
		}
		static void TextColored(Color color, String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::TextColored(ColorToImVec4(color, true), ctx.marshal_as<const char*>(String::Format(str, args)));
		}
		static void TextWithInlineColors(String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;
			
			msclr::interop::marshal_context ctx;
			ImGui::TextWithInlineColors(ctx.marshal_as<const char*>(String::Format(str, args)));
		}

		static void BulletText(String^ str, ...array<System::Object^>^ args)
		{
			if (String::IsNullOrWhiteSpace(str))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::BulletText(ctx.marshal_as<const char*>(String::Format(str, args)));
		}

		//-----------------------------------------------------------------------------
		// [SECTION] Helpers
		//-----------------------------------------------------------------------------
		static void HelpMarker(String^ text)
		{
			if (String::IsNullOrWhiteSpace(text))
				return;

			ImGui::TextDisabled("(?)");
			if (ImGui::BeginItemTooltip())
			{
				msclr::interop::marshal_context ctx;
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(ctx.marshal_as<const char*>(text));
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: Main
		//-------------------------------------------------------------------------
		static bool ButtonEx(String^ name, Vector2 size, eImGuiButtonFlags flags)
		{
			if (String::IsNullOrWhiteSpace(name))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::ButtonEx(
				ctx.marshal_as<const char*>(name),
				Vector2ToImVec2(size),
				(ImGuiButtonFlags)flags);
		}
		static bool Button(String^ name, Vector2 size)
		{
			return ButtonEx(
				name,
				size,
				eImGuiButtonFlags::None);
		}
		static bool Button(String^ name)
		{
			return ButtonEx(
				name,
				Vector2::Zero,
				eImGuiButtonFlags::None);
		}

		static bool SmallButton(String^ name)
		{
			if (String::IsNullOrWhiteSpace(name))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::SmallButton(ctx.marshal_as<const char*>(name));
		}

		static bool InvisibleButton(String^ name, Vector2 size, eImGuiButtonFlags flags)
		{
			if (String::IsNullOrWhiteSpace(name))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::InvisibleButton(
				ctx.marshal_as<const char*>(name),
				Vector2ToImVec2(size),
				(ImGuiButtonFlags)flags);
		}

		static bool ArrowButtonEx(String^ id, eImGuiDir dir, Vector2 size, eImGuiButtonFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::ArrowButtonEx(
				ctx.marshal_as<const char*>(id),
				(ImGuiDir)dir,
				Vector2ToImVec2(size),
				(ImGuiButtonFlags)flags);
		}
		static bool ArrowButton(String^ id, eImGuiDir dir)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::ArrowButton(ctx.marshal_as<const char*>(id), (ImGuiDir)dir);
		}

		static bool CloseButton(ImGuiID id, Vector2 pos)
		{
			return ImGui::CloseButton(id, Vector2ToImVec2(pos));
		}
		static bool CollapseButton(ImGuiID id, Vector2 pos)
		{
			return ImGui::CollapseButton(id, Vector2ToImVec2(pos), ImGui::GetWindowDockNode());
		}

		static void Scrollbar(eImGuiAxis axis)
		{
			ImGui::Scrollbar((ImGuiAxis)axis);
		}

		static void Image(IntPtr textureId, Vector2 size, Vector2 uv0, Vector2 uv1, Color tintColor, Color borderColor)
		{
			if (textureId == IntPtr::Zero)
				return;

			ImGui::Image(
				(ImTextureID)textureId.ToPointer(),
				Vector2ToImVec2(size),
				Vector2ToImVec2(uv0),
				Vector2ToImVec2(uv1),
				ColorToImVec4(tintColor, true),
				ColorToImVec4(borderColor, true));
		}
		static void Image(IntPtr textureId, Vector2 size)
		{
			Image(
				textureId,
				size,
				Vector2(0.0F, 0.0F),
				Vector2(1.0F, 1.0F),
				Color::White,
				Color::FromArgb(0, 0, 0, 0));
		}

		static bool ImageButtonEx(ImGuiID id, IntPtr textureId, Vector2 size, Vector2 uv0, Vector2 uv1, Color bgColor, Color tintColor, eImGuiButtonFlags flags)
		{
			if (textureId == IntPtr::Zero)
				return false;

			return ImGui::ImageButtonEx(
				id,
				(ImTextureID)textureId.ToPointer(),
				Vector2ToImVec2(size),
				Vector2ToImVec2(uv0),
				Vector2ToImVec2(uv1),
				ColorToImVec4(bgColor, true),
				ColorToImVec4(tintColor, true),
				(ImGuiButtonFlags)flags);
		}
		static bool ImageButton(String^ id, IntPtr textureId, Vector2 size, Vector2 uv0, Vector2 uv1, Color bgColor, Color tintColor)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;
			if (textureId == IntPtr::Zero)
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::ImageButton(
				ctx.marshal_as<const char*>(id),
				(ImTextureID)textureId.ToPointer(),
				Vector2ToImVec2(size),
				Vector2ToImVec2(uv0),
				Vector2ToImVec2(uv1),
				ColorToImVec4(bgColor, true),
				ColorToImVec4(tintColor, true));
		}

		static bool CheckBox(String^ text, bool% value)
		{
			if (String::IsNullOrWhiteSpace(text))
				return false;

			msclr::interop::marshal_context ctx;

			bool v = value;

			bool result = ImGui::Checkbox(ctx.marshal_as<const char*>(text), &v);

			value = v;
			return result;
		}
		static bool RadioButton(String^ text, int% selectedButton, int buttonIndex)
		{
			if (String::IsNullOrWhiteSpace(text))
				return false;

			msclr::interop::marshal_context ctx;

			int sb = selectedButton;
			bool result = ImGui::RadioButton(ctx.marshal_as<const char*>(text), &sb, buttonIndex);
			selectedButton = sb;

			return result;
		}
		static bool RadioButton(String^ text, bool active)
		{
			if (String::IsNullOrWhiteSpace(text))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::RadioButton(ctx.marshal_as<const char*>(text), active);
		}

		static void IndeterminateProgressBar(Vector2 size)
		{
			ImGuiContext& g = *GImGui;
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems)
				return;

			ImGuiStyle& style = g.Style;
			ImVec2 size2 = ImGui::CalcItemSize(Vector2ToImVec2(size), CalcItemWidth(), g.FontSize + style.FramePadding.y * 2.0f);
			ImVec2 pos = window->DC.CursorPos;
			ImRect bb(pos.x, pos.y, pos.x + size2.x, pos.y + size2.y);
			ImGui::ItemSize(size2);
			if (!ImGui::ItemAdd(bb, 0))
				return;

			const float speed = g.FontSize * 0.05f;
			const float phase = ImFmod((float)g.Time * speed, 1.0f);
			const float width_normalized = 0.2f;
			float t0 = phase * (1.0f + width_normalized) - width_normalized;
			float t1 = t0 + width_normalized;

			ImGui::RenderFrame(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);
			bb.Expand(ImVec2(-style.FrameBorderSize, -style.FrameBorderSize));
			ImGui::RenderRectFilledRangeH(window->DrawList, bb, ImGui::GetColorU32(ImGuiCol_PlotHistogram), t0, t1, style.FrameRounding);
		}
		static void IndeterminateProgressBar()
		{
			IndeterminateProgressBar(Vector2(-FLT_MIN, 0.0F));
		}
		static void ProgressBar(float fraction, Vector2 size, String^ overlay)
		{
			msclr::interop::marshal_context ctx;
			ImGui::ProgressBar(fraction, Vector2ToImVec2(size), String::IsNullOrWhiteSpace(overlay) ? (const char*)0 : ctx.marshal_as<const char*>(overlay));
		}
		static void ProgressBar(float fraction)
		{
			ProgressBar(fraction, Vector2(-FLT_MIN, 0.0F), nullptr);
		}

		static void Bullet()
		{
			ImGui::Bullet();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: Low-level Layout helpers
		//-------------------------------------------------------------------------
		static void Spacing(int n)
		{
			while (n--)
				ImGui::Spacing();
		}
		static void Spacing()
		{
			ImGui::Spacing();
		}
		static void Dummy(Vector2 size)
		{
			ImGui::Dummy(Vector2ToImVec2(size));
		}
		static void Dummy()
		{
			Dummy(Vector2::Zero);
		}
		static void NewLine()
		{
			ImGui::NewLine();
		}
		static void AlignTextToFramePadding()
		{
			ImGui::AlignTextToFramePadding();
		}

		static void SeparatorEx(eImGuiSeparatorFlags flags, float thickness)
		{
			ImGui::SeparatorEx((ImGuiSeparatorFlags)flags, thickness);
		}
		static void SeparatorEx(eImGuiSeparatorFlags flags)
		{
			SeparatorEx(flags, 1.0F);
		}
		static void Separator()
		{
			ImGui::Separator();
		}
		static void SeparatorTextEx(ImGuiID id, String^ text, String^ textEnd, float extraW)
		{
			if (String::IsNullOrWhiteSpace(text))
				return;
			if (String::IsNullOrWhiteSpace(textEnd))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::SeparatorTextEx(id, ctx.marshal_as<const char*>(text), ctx.marshal_as<const char*>(textEnd), extraW);
		}
		static void SeparatorText(String^ text)
		{
			if (String::IsNullOrWhiteSpace(text))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::SeparatorText(ctx.marshal_as<const char*>(text));
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: ComboBox
		//-------------------------------------------------------------------------
		static bool Combo(String^ label, int% selectedIndex, array<String^>^ items)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			int index = selectedIndex;

			// Copy managed stuff over to unmanaged stuff
			std::vector<const char*> arr;
			arr.resize(items->Length);

			for (int i = 0; i < items->Length; i++)
				arr[i] = ctx.marshal_as<const char*>(items[i]);
			
			bool result = ImGui::Combo(ctx.marshal_as<const char*>(label), &index, arr.data(), items->Length);

			selectedIndex = index;
			return result;
		}

		static bool BeginCombo(String^ text, String^ previewValue, eImGuiComboFlags flags)
		{
			if (String::IsNullOrWhiteSpace(text))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginCombo(ctx.marshal_as<const char*>(text), String::IsNullOrWhiteSpace(previewValue) ? "" : ctx.marshal_as<const char*>(previewValue), (ImGuiComboFlags)flags);
		}
		static bool BeginCombo(String^ text, String^ previewValue)
		{
			return BeginCombo(text, previewValue, eImGuiComboFlags::None);
		}
		static void EndCombo()
		{
			ImGui::EndCombo();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: DragScalar, DragFloat, DragInt, etc.
		//-------------------------------------------------------------------------
		static bool DragFloat(String^ label, float% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value = v;
			bool result = ImGui::DragFloat(ctx.marshal_as<const char*>(label), &value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = value;
			return result;
		}
		static bool DragFloat(String^ label, float% v, float speed, float min, float max)
		{
			return DragFloat(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat(String^ label, float% v, float min, float max)
		{
			return DragFloat(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat(String^ label, float% v, float speed)
		{
			return DragFloat(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat(String^ label, float% v)
		{
			return DragFloat(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat2(String^ label, array<float>^% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[2] = { v[0], v[1] };
			bool result = ImGui::DragFloat2(ctx.marshal_as<const char*>(label), (float*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(2) { value[0], value[1] };
			return result;
		}
		static bool DragFloat2(String^ label, array<float>^% v, float speed, float min, float max)
		{
			return DragFloat2(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, array<float>^% v, float min, float max)
		{
			return DragFloat2(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, array<float>^% v, float speed)
		{
			return DragFloat2(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, array<float>^% v)
		{
			return DragFloat2(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat2(String^ label, Vector2% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			array<float>^ arr = gcnew array<float>(2) { v.X, v.Y };
			bool result = DragFloat2(label, arr, speed, min, max, format, flags);
			v = Vector2(arr[0], arr[1]);
			return result;
		}
		static bool DragFloat2(String^ label, Vector2% v, float speed, float min, float max)
		{
			return DragFloat2(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, Vector2% v, float min, float max)
		{
			return DragFloat2(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, Vector2% v, float speed)
		{
			return DragFloat2(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat2(String^ label, Vector2% v)
		{
			return DragFloat2(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat3(String^ label, array<float>^% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[3] = { v[0], v[1], v[2] };
			bool result = ImGui::DragFloat3(ctx.marshal_as<const char*>(label), (float*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(3) { value[0], value[1], value[2] };
			return result;
		}
		static bool DragFloat3(String^ label, array<float>^% v, float speed, float min, float max)
		{
			return DragFloat3(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, array<float>^% v, float min, float max)
		{
			return DragFloat3(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, array<float>^% v, float speed)
		{
			return DragFloat3(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, array<float>^% v)
		{
			return DragFloat3(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat3(String^ label, Vector3% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			array<float>^ arr = gcnew array<float>(3) { v.X, v.Y, v.Z };
			bool result = DragFloat3(label, arr, speed, min, max, format, flags);
			v = Vector3(arr[0], arr[1], arr[2]);
			return result;
		}
		static bool DragFloat3(String^ label, Vector3% v, float speed, float min, float max)
		{
			return DragFloat3(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, Vector3% v, float min, float max)
		{
			return DragFloat3(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, Vector3% v, float speed)
		{
			return DragFloat3(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat3(String^ label, Vector3% v)
		{
			return DragFloat3(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat4(String^ label, array<float>^% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[4] = { v[0], v[1], v[2], v[3]};
			bool result = ImGui::DragFloat4(ctx.marshal_as<const char*>(label), (float*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(4) { value[0], value[1], value[2], value[3] };
			return result;
		}
		static bool DragFloat4(String^ label, array<float>^% v, float speed, float min, float max)
		{
			return DragFloat4(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, array<float>^% v, float min, float max)
		{
			return DragFloat4(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, array<float>^% v, float speed)
		{
			return DragFloat4(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, array<float>^% v)
		{
			return DragFloat4(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragFloat4(String^ label, Vector4% v, float speed, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			array<float>^ arr = gcnew array<float>(4) { v.X, v.Y, v.Z, v.W };
			bool result = DragFloat4(label, arr, speed, min, max, format, flags);
			v = Vector4(arr[0], arr[1], arr[2], arr[3]);
			return result;
		}
		static bool DragFloat4(String^ label, Vector4% v, float speed, float min, float max)
		{
			return DragFloat4(label, v, speed, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, Vector4% v, float min, float max)
		{
			return DragFloat4(label, v, 0.1F, min, max, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, Vector4% v, float speed)
		{
			return DragFloat4(label, v, speed, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}
		static bool DragFloat4(String^ label, Vector4% v)
		{
			return DragFloat4(label, v, 0.1F, 0.0F, 0.0F, "%.3f", eImGuiSliderFlags::None);
		}

		static bool DragInt(String^ label, int% v, float speed, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value = v;
			bool result = ImGui::DragInt(ctx.marshal_as<const char*>(label), &value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = value;
			return result;
		}
		static bool DragInt(String^ label, int% v, float speed, int min, int max)
		{
			return DragInt(label, v, speed, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt(String^ label, int% v, int min, int max)
		{
			return DragInt(label, v, 1.0F, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt(String^ label, int% v, float speed)
		{
			return DragInt(label, v, speed, 0, 0, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt(String^ label, int% v)
		{
			return DragInt(label, v, 1.0F, 0, 0, "%d", eImGuiSliderFlags::None);
		}

		static bool DragInt2(String^ label, array<int>^% v, float speed, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[2] = { v[0], v[1] };
			bool result = ImGui::DragInt2(ctx.marshal_as<const char*>(label), (int*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(2) { value[0], value[1] };
			return result;
		}
		static bool DragInt2(String^ label, array<int>^% v, float speed, int min, int max)
		{
			return DragInt2(label, v, speed, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt2(String^ label, array<int>^% v, int min, int max)
		{
			return DragInt2(label, v, 1.0F, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt2(String^ label, array<int>^% v, float speed)
		{
			return DragInt2(label, v, speed, 0, 0, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt2(String^ label, array<int>^% v)
		{
			return DragInt2(label, v, 1.0F, 0, 0, "%d", eImGuiSliderFlags::None);
		}

		static bool DragInt3(String^ label, array<int>^% v, float speed, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[3] = { v[0], v[1], v[2]};
			bool result = ImGui::DragInt3(ctx.marshal_as<const char*>(label), (int*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(3) { value[0], value[1], value[2] };
			return result;
		}
		static bool DragInt3(String^ label, array<int>^% v, float speed, int min, int max)
		{
			return DragInt3(label, v, speed, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt3(String^ label, array<int>^% v, int min, int max)
		{
			return DragInt3(label, v, 1.0F, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt3(String^ label, array<int>^% v, float speed)
		{
			return DragInt3(label, v, speed, 0, 0, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt3(String^ label, array<int>^% v)
		{
			return DragInt3(label, v, 1.0F, 0, 0, "%d", eImGuiSliderFlags::None);
		}

		static bool DragInt4(String^ label, array<int>^% v, float speed, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[4] = { v[0], v[1], v[2], v[3] };
			bool result = ImGui::DragInt4(ctx.marshal_as<const char*>(label), (int*)&value, speed, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(4) { value[0], value[1], value[2], value[3] };
			return result;
		}
		static bool DragInt4(String^ label, array<int>^% v, float speed, int min, int max)
		{
			return DragInt4(label, v, speed, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt4(String^ label, array<int>^% v, int min, int max)
		{
			return DragInt4(label, v, 1.0F, min, max, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt4(String^ label, array<int>^% v, float speed)
		{
			return DragInt4(label, v, speed, 0, 0, "%d", eImGuiSliderFlags::None);
		}
		static bool DragInt4(String^ label, array<int>^% v)
		{
			return DragInt4(label, v, 1.0F, 0, 0, "%d", eImGuiSliderFlags::None);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: SliderScalar, SliderFloat, SliderInt, etc.
		//-------------------------------------------------------------------------
		static bool SliderFloat(String^ label, float% v, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value = v;
			bool result = ImGui::SliderFloat(ctx.marshal_as<const char*>(label), &value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = value;
			return result;
		}
		static bool SliderFloat(String^ label, float% v, float min, float max)
		{
			return SliderFloat(label, v, min, max, "%.3f", eImGuiSliderFlags::None);
		}

		static bool SliderFloat2(String^ label, array<float>^% v, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[2] = { v[0], v[1] };
			bool result = ImGui::SliderFloat2(ctx.marshal_as<const char*>(label), (float*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(2) { value[0], value[1] };
			return result;
		}
		static bool SliderFloat2(String^ label, array<float>^% v, float min, float max)
		{
			return SliderFloat2(label, v, min, max, "%.3f", eImGuiSliderFlags::None);
		}

		static bool SliderFloat3(String^ label, array<float>^% v, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[3] = { v[0], v[1], v[2] };
			bool result = ImGui::SliderFloat3(ctx.marshal_as<const char*>(label), (float*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(3) { value[0], value[1], value[2] };
			return result;
		}
		static bool SliderFloat3(String^ label, array<float>^% v, float min, float max)
		{
			return SliderFloat3(label, v, min, max, "%.3f", eImGuiSliderFlags::None);
		}

		static bool SliderFloat4(String^ label, array<float>^% v, float min, float max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			float value[4] = { v[0], v[1], v[2], v[3] };
			bool result = ImGui::SliderFloat4(ctx.marshal_as<const char*>(label), (float*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<float>(4) { value[0], value[1], value[2], value[3] };
			return result;
		}
		static bool SliderFloat4(String^ label, array<float>^% v, float min, float max)
		{
			return SliderFloat4(label, v, min, max, "%.3f", eImGuiSliderFlags::None);
		}


		static bool SliderInt(String^ label, int% v, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value = v;
			bool result = ImGui::SliderInt(ctx.marshal_as<const char*>(label), &value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = value;
			return result;
		}
		static bool SliderInt(String^ label, int% v, int min, int max)
		{
			return SliderInt(label, v, min, max, "%d", eImGuiSliderFlags::None);
		}

		static bool SliderInt2(String^ label, array<int>^% v, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[2] = { v[0], v[1] };
			bool result = ImGui::SliderInt2(ctx.marshal_as<const char*>(label), (int*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(2) { value[0], value[1] };
			return result;
		}
		static bool SliderInt2(String^ label, array<int>^% v, int min, int max)
		{
			return SliderInt2(label, v, min, max, "%d", eImGuiSliderFlags::None);
		}

		static bool SliderInt3(String^ label, array<int>^% v, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[3] = { v[0], v[1], v[2] };
			bool result = ImGui::SliderInt3(ctx.marshal_as<const char*>(label), (int*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(3) { value[0], value[1], value[2] };
			return result;
		}
		static bool SliderInt3(String^ label, array<int>^% v, int min, int max)
		{
			return SliderInt3(label, v, min, max, "%d", eImGuiSliderFlags::None);
		}

		static bool SliderInt4(String^ label, array<int>^% v, int min, int max, String^ format, eImGuiSliderFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(format))
				return false;

			msclr::interop::marshal_context ctx;

			int value[4] = { v[0], v[1], v[2], v[3] };
			bool result = ImGui::SliderInt4(ctx.marshal_as<const char*>(label), (int*)&value, min, max, ctx.marshal_as<const char*>(format), (ImGuiSliderFlags)flags);

			v = gcnew array<int>(4) { value[0], value[1], value[2], value[3] };
			return result;
		}
		static bool SliderInt4(String^ label, array<int>^% v, int min, int max)
		{
			return SliderInt4(label, v, min, max, "%d", eImGuiSliderFlags::None);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: InputScalar, InputFloat, InputInt, etc.
		//-------------------------------------------------------------------------
		// todo

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: InputText, InputTextMultiline, InputTextWithHint
		//-------------------------------------------------------------------------
		static bool InputText(String^ label, String^% input, eImGuiInputFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			if (String::IsNullOrEmpty(input))
			{
				std::string* str = new std::string("");

				bool result = ImGui::InputText(ctx.marshal_as<const char*>(label), str, (ImGuiInputFlags)flags);

				input = gcnew String(str->c_str());
				delete str;

				return result;
			}
			
			std::string* str = new std::string(ctx.marshal_as<const char*>(input));

			bool result = ImGui::InputText(ctx.marshal_as<const char*>(label), str, (ImGuiInputFlags)flags);

			input = gcnew String(str->c_str());
			delete str;

			return result;
		}
		static bool InputText(String^ label, String^% input)
		{
			return InputText(label, input, eImGuiInputFlags::None);
		}

		static bool InputTextMultiline(String^ label, String^% input, Vector2 size, eImGuiInputFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			std::string* str = new std::string(ctx.marshal_as<const char*>(input));

			bool result = ImGui::InputTextMultiline(ctx.marshal_as<const char*>(label), str, Vector2ToImVec2(size), (ImGuiInputFlags)flags);

			input = gcnew String(str->c_str());
			delete str;

			return result;
		}
		static bool InputTextMultiline(String^ label, String^% input)
		{
			return InputTextMultiline(label, input, Vector2::Zero, eImGuiInputFlags::None);
		}

		static bool InputTextWithHint(String^ label, String^ hint, String^% input, eImGuiInputFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(hint))
				return false;

			msclr::interop::marshal_context ctx;

			std::string* str = new std::string(ctx.marshal_as<const char*>(input));

			bool result = ImGui::InputTextWithHint(ctx.marshal_as<const char*>(label), ctx.marshal_as<const char*>(hint), str, (ImGuiInputFlags)flags);

			input = gcnew String(str->c_str());
			delete str;

			return result;
		}
		static bool InputTextWithHint(String^ label, String^ hint, String^% input)
		{
			return InputTextWithHint(label, hint, input, eImGuiInputFlags::None);
		}

		static bool TempInputIsActive(ImGuiID id)
		{
			return ImGui::TempInputIsActive(id);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: ColorEdit, ColorPicker, ColorButton, etc.
		//-------------------------------------------------------------------------
		static bool ColorEdit3(String^ label, Vector3% color, eImGuiColorEditFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			
			msclr::interop::marshal_context ctx;
			
			ImVec4 vec = ImVec4(color.X, color.Y, color.Z, 0.0F);
			bool result = ImGui::ColorEdit3(ctx.marshal_as<const char*>(label), (float*)&vec, (ImGuiColorEditFlags)flags);

			color = Vector3(vec.x, vec.y, vec.z);
			return result;
		}
		static bool ColorPicker3(String^ label, Vector3% color, eImGuiColorEditFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			ImVec4 vec = ImVec4(color.X, color.Y, color.Z, 0.0F);
			bool result = ImGui::ColorPicker3(ctx.marshal_as<const char*>(label), (float*)&vec, (ImGuiColorEditFlags)flags);

			color = Vector3(vec.x, vec.y, vec.z);
			return result;
		}

		static bool ColorEdit4(String^ label, Vector4% color, eImGuiColorEditFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			ImVec4 vec = ImVec4(color.X, color.Y, color.Z, color.W);
			bool result = ImGui::ColorEdit4(ctx.marshal_as<const char*>(label), (float*)&vec, (ImGuiColorEditFlags)flags);

			color = Vector4(vec.x, vec.y, vec.z, vec.w);
			return result;
		}
		static bool ColorPicker4(String^ label, Vector4% color, eImGuiColorEditFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			ImVec4 vec = ImVec4(color.X, color.Y, color.Z, color.W);
			bool result = ImGui::ColorPicker4(ctx.marshal_as<const char*>(label), (float*)&vec, (ImGuiColorEditFlags)flags);

			color = Vector4(vec.x, vec.y, vec.z, vec.w);
			return result;
		}

		static void ColorTooltip(String^ label, Vector4 color, eImGuiColorEditFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;

			ImVec4 vec = ImVec4(color.X, color.Y, color.Z, color.W);
			ImGui::ColorTooltip(ctx.marshal_as<const char*>(label), (float*)&vec, (ImGuiColorEditFlags)flags);
		}

		static void SetColorEditOptions(eImGuiColorEditFlags flags)
		{
			ImGui::SetColorEditOptions((ImGuiColorEditFlags)flags);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: TreeNode, CollapsingHeader, etc.
		//-------------------------------------------------------------------------
		static bool TreeNode(String^ label)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::TreeNode(ctx.marshal_as<const char*>(label));
		}
		static bool TreeNodeEx(String^ label, eImGuiTreeNodeFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::TreeNodeEx(ctx.marshal_as<const char*>(label), (ImGuiTreeNodeFlags)flags);
		}
		static bool TreeNodeEx(String^ label)
		{
			return TreeNodeEx(label, eImGuiTreeNodeFlags::None);
		}
		static void TreePop()
		{
			ImGui::TreePop();
		}

		static void TreePush(String^ id)
		{
			if (String::IsNullOrWhiteSpace(id))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::TreePush(ctx.marshal_as<const char*>(id));
		}
		static void TreePush(IntPtr ptrId)
		{
			if (ptrId == IntPtr::Zero)
				return;

			ImGui::TreePush(ptrId.ToPointer());
		}
		static void TreePushOverrideID(ImGuiID id)
		{
			ImGui::TreePushOverrideID(id);
		}

		static bool CollapsingHeader(String^ label, bool% visible, eImGuiTreeNodeFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			bool pVisible = visible;

			bool result = ImGui::CollapsingHeader(ctx.marshal_as<const char*>(label), &pVisible, (ImGuiTreeNodeFlags)flags);

			visible = pVisible;

			return result;
		}
		static bool CollapsingHeader(String^ label, bool% visible)
		{
			return CollapsingHeader(label, visible, eImGuiTreeNodeFlags::None);
		}

		static bool CollapsingHeader(String^ label, eImGuiTreeNodeFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::CollapsingHeader(ctx.marshal_as<const char*>(label), (ImGuiTreeNodeFlags)flags);
		}
		static bool CollapsingHeader(String^ label)
		{
			return CollapsingHeader(label, eImGuiTreeNodeFlags::None);
		}

		static void SetNextItemOpen(bool isOpen, eImGuiCond cond)
		{
			ImGui::SetNextItemOpen(isOpen, (ImGuiCond)cond);
		}
		static void SetNextItemOpen(bool isOpen)
		{
			SetNextItemOpen(isOpen, eImGuiCond::None);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: Selectable
		//-------------------------------------------------------------------------
		static bool Selectable(String^ label, bool selected, eImGuiSelectableFlags flags, Vector2 size)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::Selectable(ctx.marshal_as<const char*>(label), selected, (ImGuiSelectableFlags)flags, Vector2ToImVec2(size));
		}
		static bool Selectable(String^ label, bool selected)
		{
			return Selectable(label, selected, eImGuiSelectableFlags::None, Vector2::Zero);
		}
		static bool Selectable(String^ label)
		{
			return Selectable(label, false, eImGuiSelectableFlags::None, Vector2::Zero);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: ListBox
		//-------------------------------------------------------------------------
		static bool BeginListBox(String^ label, Vector2 size)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginListBox(ctx.marshal_as<const char*>(label), Vector2ToImVec2(size));
		}
		static bool BeginListBox(String^ label)
		{
			return BeginListBox(label, Vector2::Zero);
		}
		static void EndListBox()
		{
			ImGui::EndListBox();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: PlotLines, PlotHistogram
		//-------------------------------------------------------------------------
		static void PlotLines(String^ label, array<float>^ data)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			pin_ptr<float> pinnedData = &data[0];
			float* pby = pinnedData;
			const float* dataPtr = reinterpret_cast<const float*>(pby);

			msclr::interop::marshal_context ctx;
			ImGui::PlotLines(ctx.marshal_as<const char*>(label), dataPtr, data->Length);
		}
		static void PlotHistogram(String^ label, array<float>^ data)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			pin_ptr<float> pinnedData = &data[0];
			float* pby = pinnedData;
			const float* dataPtr = reinterpret_cast<const float*>(pby);

			msclr::interop::marshal_context ctx;
			ImGui::PlotHistogram(ctx.marshal_as<const char*>(label), dataPtr, data->Length);
		}

		//-------------------------------------------------------------------------
		// [SECTION] MenuItem, BeginMenu, EndMenu, etc.
		//-------------------------------------------------------------------------
		static bool BeginMenuBar()
		{
			return ImGui::BeginMenuBar();
		}
		static void EndMenuBar()
		{
			ImGui::EndMenuBar();
		}

		static bool BeginMainMenuBar()
		{
			return ImGui::BeginMainMenuBar();
		}
		static void EndMainMenuBar()
		{
			ImGui::EndMainMenuBar();
		}

		static bool BeginMenuEx(String^ label, String^ icon, bool enabled)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(icon))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginMenuEx(ctx.marshal_as<const char*>(label), ctx.marshal_as<const char*>(icon), enabled);
		}
		static bool BeginMenuEx(String^ label, String^ icon)
		{
			return BeginMenuEx(label, icon, true);
		}
		static bool BeginMenu(String^ label, bool enabled)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginMenu(ctx.marshal_as<const char*>(label), enabled);
		}
		static bool BeginMenu(String^ label)
		{
			return BeginMenu(label, true);
		}
		static void EndMenu()
		{
			ImGui::EndMenu();
		}

		static bool MenuItemEx(String^ label, String^ icon, String^ shortcut, bool selected, bool enabled)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (String::IsNullOrWhiteSpace(icon))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::MenuItemEx(
				ctx.marshal_as<const char*>(label),
				ctx.marshal_as<const char*>(icon),
				String::IsNullOrWhiteSpace(shortcut) ? (const char*)0 : ctx.marshal_as<const char*>(shortcut),
				selected,
				enabled);
		}
		static bool MenuItemEx(String^ label, String^ icon)
		{
			return MenuItemEx(label, icon, nullptr, false, true);
		}
		static bool MenuItem(String^ label, String^ shortcut, bool selected, bool enabled)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::MenuItem(
				ctx.marshal_as<const char*>(label),
				String::IsNullOrWhiteSpace(shortcut) ? (const char*)0 : ctx.marshal_as<const char*>(shortcut),
				selected,
				enabled);
		}
		static bool MenuItem(String^ label)
		{
			return MenuItem(label, nullptr, false, true);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: BeginTabBar, EndTabBar, etc.
		//-------------------------------------------------------------------------
		static bool BeginTabBar(String^ id, eImGuiTabBarFlags flags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginTabBar(ctx.marshal_as<const char*>(id), (ImGuiTabBarFlags)flags);
		}
		static bool BeginTabBar(String^ id)
		{
			return BeginTabBar(id, eImGuiTabBarFlags::None);
		}
		static void EndTabBar()
		{
			ImGui::EndTabBar();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Widgets: BeginTabItem, EndTabItem, etc.
		//-------------------------------------------------------------------------
		static bool BeginTabItem(String^ label, bool% open, eImGuiTabItemFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;

			bool pOpen = open;

			bool result = ImGui::BeginTabItem(ctx.marshal_as<const char*>(label), &pOpen, (ImGuiTabItemFlags)flags);

			open = pOpen;
			return result;
		}
		static bool BeginTabItem(String^ label, bool% open)
		{
			return BeginTabItem(label, open, eImGuiTabItemFlags::None);
		}
		static bool BeginTabItem(String^ label)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginTabItem(ctx.marshal_as<const char*>(label));
		}
		static void EndTabItem()
		{
			ImGui::EndTabItem();
		}

		static bool TabItemButton(String^ label, eImGuiTabItemFlags flags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			
			msclr::interop::marshal_context ctx;
			return ImGui::TabItemButton(ctx.marshal_as<const char*>(label), (ImGuiTabItemFlags)flags);
		}

		//-----------------------------------------------------------------------------
		// [SECTION] Tables: BeginTable, EndTable.
		//-----------------------------------------------------------------------------
		static bool BeginTable(String^ label, int columns_count, eImGuiTableFlags flags, Vector2 outer_size, float inner_width)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginTable(ctx.marshal_as<const char*>(label), columns_count, (ImGuiTableFlags) flags, Vector2ToImVec2(outer_size), inner_width);
		}
		static bool BeginTable(String^ label, int columns_count, eImGuiTableFlags flags)
		{
			return BeginTable(label, columns_count, flags, Vector2(0.0F), 0.0F);
		}
		static bool BeginTable(String^ label, int columns_count)
		{
			return BeginTable(label, columns_count, eImGuiTableFlags::None, Vector2(0.0F), 0.0F);
		}
		static void EndTable()
		{
			ImGui::EndTable();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Tables: Row changes
		//-------------------------------------------------------------------------
		static int TableGetRowIndex()
		{
			return ImGui::TableGetRowIndex();
		}
		static void TableNextRow(eImGuiTableRowFlags row_flags, float row_min_height)
		{
			ImGui::TableNextRow((ImGuiTableRowFlags) row_flags, row_min_height);
		}
		static void TableNextRow()
		{
			TableNextRow(eImGuiTableRowFlags::None, 0.0F);
		}

		static void TableHeadersRow()
		{
			ImGui::TableHeadersRow();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Tables: Columns changes
		//-------------------------------------------------------------------------
		static int TableGetColumnIndex()
		{
			return ImGui::TableGetColumnIndex();
		}
		static bool TableSetColumnIndex(int column_n)
		{
			return ImGui::TableSetColumnIndex(column_n);
		}

		static bool TableNextColumn(int n)
		{
			bool b;
			while (n--)
				b = ImGui::TableNextColumn();
			return b;
		}
		static bool TableNextColumn()
		{
			return ImGui::TableNextColumn();
		}

		static void TableSetupColumn(String^ label, eImGuiTableColumnFlags flags, float init_width_or_weight, ImGuiID userId)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImGui::TableSetupColumn(ctx.marshal_as<const char*>(label), (ImGuiTableColumnFlags)flags, init_width_or_weight, userId);
		}
		static void TableSetupColumn(String^ label, eImGuiTableColumnFlags flags, float init_width_or_weight)
		{
			TableSetupColumn(label, flags, init_width_or_weight, 0U);
		}
		static void TableSetupColumn(String^ label, eImGuiTableColumnFlags flags)
		{
			TableSetupColumn(label, flags, 0.0F, 0U);
		}
		static void TableSetupColumn(String^ label)
		{
			TableSetupColumn(label, eImGuiTableColumnFlags::None, 0.0F, 0U);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Extension: Timeline
		//-------------------------------------------------------------------------
		static bool BeginTimeline(String^ label, Vector2 size, eImGuiChildFlags childFlags, eImGuiWindowFlags windowFlags)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginTimeline(ctx.marshal_as<const char*>(label), Vector2ToImVec2(size), (ImGuiChildFlags)childFlags, (ImGuiWindowFlags)windowFlags);
		}
		static bool BeginTimeline(String^ label, Vector2 size, eImGuiChildFlags childFlags)
		{
			return BeginTimeline(label, size, childFlags, eImGuiWindowFlags::None);
		}
		static bool BeginTimeline(String^ label, Vector2 size)
		{
			return BeginTimeline(label, size, eImGuiChildFlags::None, eImGuiWindowFlags::None);
		}
		static bool BeginTimeline(String^ label)
		{
			return BeginTimeline(label, Vector2::Zero, eImGuiChildFlags::None, eImGuiWindowFlags::None);
		}

		static bool Timeline(String^ label, array<float>^% values, int maxFrames)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;
			if (!values)
				return false;
			if (values->Length > 2)
				return false;

			msclr::interop::marshal_context ctx;

			float v[2] = { values[0], values[1] };
			bool result = ImGui::Timeline(ctx.marshal_as<const char*>(label), (float*)&v, maxFrames);

			values[0] = v[0];
			values[1] = v[1];

			return result;
		}
		static bool Timeline(String^ label, Vector2% values, int maxFrames)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			array<float>^ arr = gcnew array<float>(2)
			{
				values.X, values.Y
			};

			bool result = Timeline(label, arr, maxFrames);

			values = Vector2(arr[0], arr[1]);

			return result;
		}
		static void EndTimeline(bool drawCurrentFrame, int currentFrame, int maxFrames, bool drawLines, int lineCount, bool drawValues)
		{
			ImGui::EndTimeline(drawCurrentFrame, currentFrame, maxFrames, drawLines, lineCount, drawValues);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Extension: Hex Editor - https://github.com/Teselka/imgui_hex_editor
		//-------------------------------------------------------------------------
		static bool BeginHexEditor(String^ id, ImGuiIV_HexEditorState^ state, Vector2 size, eImGuiChildFlags childFlags, eImGuiWindowFlags windowFlags)
		{
			if (String::IsNullOrWhiteSpace(id))
				return false;
			if (!state)
				return false;

			msclr::interop::marshal_context ctx;
			return ImGui::BeginHexEditor(ctx.marshal_as<const char*>(id), state->NativeHexEditorState, Vector2ToImVec2(size), (ImGuiChildFlags)childFlags, (ImGuiWindowFlags)windowFlags);
		}
		static bool BeginHexEditor(String^ id, ImGuiIV_HexEditorState^ state, Vector2 size, eImGuiChildFlags childFlags)
		{
			return BeginHexEditor(id, state, size, childFlags, eImGuiWindowFlags::None);
		}
		static bool BeginHexEditor(String^ id, ImGuiIV_HexEditorState^ state, Vector2 size)
		{
			return BeginHexEditor(id, state, size, eImGuiChildFlags::None, eImGuiWindowFlags::None);
		}
		static bool BeginHexEditor(String^ id, ImGuiIV_HexEditorState^ state)
		{
			return BeginHexEditor(id, state, Vector2::Zero, eImGuiChildFlags::None, eImGuiWindowFlags::None);
		}
		static void EndHexEditor()
		{
			ImGui::EndHexEditor();
		}

		//-------------------------------------------------------------------------
		// [SECTION] Extension: Knobs - https://github.com/altschuler/imgui-knobs
		//-------------------------------------------------------------------------
		static bool Knob(String^ label, float% value, float min, float max, float speed, String^ format, eImGuiKnobVariant variant, float size, eImGuiKnobFlags flags, int steps, float angleMin, float angleMax)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			float v = value;

			msclr::interop::marshal_context ctx;
			bool result = ImGuiKnobs::Knob(ctx.marshal_as<const char*>(label), &v, min, max, speed, ctx.marshal_as<const char*>(format), (ImGuiKnobVariant)variant, size, (ImGuiKnobFlags)flags, steps, angleMin, angleMax);

			value = v;
			return result;
		}
		static bool Knob(String^ label, float% value, float min, float max, float speed, String^ format, eImGuiKnobVariant variant, float size, eImGuiKnobFlags flags, int steps)
		{
			return Knob(label, value, min, max, speed, format, variant, size, flags, steps, -1.0F, -1.0F);
		}
		static bool Knob(String^ label, float% value, float min, float max, float speed, String^ format, eImGuiKnobVariant variant, float size, eImGuiKnobFlags flags)
		{
			return Knob(label, value, min, max, speed, format, variant, size, flags, 10, -1.0F, -1.0F);
		}
		static bool Knob(String^ label, float% value, float min, float max, float speed, String^ format, eImGuiKnobVariant variant, float size)
		{
			return Knob(label, value, min, max, speed, format, variant, size, eImGuiKnobFlags::None, 10, -1.0F, -1.0F);
		}
		static bool Knob(String^ label, float% value, float min, float max, float speed, String^ format, eImGuiKnobVariant variant)
		{
			return Knob(label, value, min, max, speed, format, variant, 0.0F, eImGuiKnobFlags::None, 10, -1.0F, -1.0F);
		}
		static bool Knob(String^ label, float% value, float min, float max, float speed, String^ format)
		{
			return Knob(label, value, min, max, speed, format, eImGuiKnobVariant::Tick, 0.0F, eImGuiKnobFlags::None, 10, -1.0F, -1.0F);
		}
		static bool Knob(String^ label, float% value, float min, float max, float speed)
		{
			return Knob(label, value, min, max, speed, "%.3f", eImGuiKnobVariant::Tick, 0.0F, eImGuiKnobFlags::None, 10, -1.0F, -1.0F);
		}
		static bool Knob(String^ label, float% value, float min, float max)
		{
			return Knob(label, value, min, max, 0.0F, "%.3f", eImGuiKnobVariant::Tick, 0.0F, eImGuiKnobFlags::None, 10, -1.0F, -1.0F);
		}

		static bool KnobInt(String^ label, int% value, int min, int max, float speed, String^ format, eImGuiKnobVariant variant, float size, eImGuiKnobFlags flags, int steps, float angleMin, float angleMax)
		{
			if (String::IsNullOrWhiteSpace(label))
				return false;

			int v = value;

			msclr::interop::marshal_context ctx;
			bool result = ImGuiKnobs::KnobInt(ctx.marshal_as<const char*>(label), &v, min, max, speed, ctx.marshal_as<const char*>(format), (ImGuiKnobVariant)variant, size, (ImGuiKnobFlags)flags, steps, angleMin, angleMax);

			value = v;
			return result;
		}
		static bool KnobInt(String^ label, int% value, int min, int max, float speed, String^ format, eImGuiKnobVariant variant, float size, eImGuiKnobFlags flags, int steps)
		{
			return KnobInt(label, value, min, max, speed, format, variant, size, flags, steps, -1.0F, -1.0F);
		}
		static bool KnobInt(String^ label, int% value, int min, int max, float speed, String^ format, eImGuiKnobVariant variant, float size, eImGuiKnobFlags flags)
		{
			return KnobInt(label, value, min, max, speed, format, variant, size, flags, 10, -1.0F, -1.0F);
		}
		static bool KnobInt(String^ label, int% value, int min, int max, float speed, String^ format, eImGuiKnobVariant variant, float size)
		{
			return KnobInt(label, value, min, max, speed, format, variant, size, eImGuiKnobFlags::None, 10, -1.0F, -1.0F);
		}
		static bool KnobInt(String^ label, int% value, int min, int max, float speed, String^ format, eImGuiKnobVariant variant)
		{
			return KnobInt(label, value, min, max, speed, format, variant, 0.0F, eImGuiKnobFlags::None, 10, -1.0F, -1.0F);
		}
		static bool KnobInt(String^ label, int% value, int min, int max, float speed, String^ format)
		{
			return KnobInt(label, value, min, max, speed, format, eImGuiKnobVariant::Tick, 0.0F, eImGuiKnobFlags::None, 10, -1.0F, -1.0F);
		}
		static bool KnobInt(String^ label, int% value, int min, int max, float speed)
		{
			return KnobInt(label, value, min, max, speed, "%i", eImGuiKnobVariant::Tick, 0.0F, eImGuiKnobFlags::None, 10, -1.0F, -1.0F);
		}
		static bool KnobInt(String^ label, int% value, int min, int max)
		{
			return KnobInt(label, value, min, max, 0.0F, "%i", eImGuiKnobVariant::Tick, 0.0F, eImGuiKnobFlags::None, 10, -1.0F, -1.0F);
		}

		//-------------------------------------------------------------------------
		// [SECTION] Extension: Spinner - https://github.com/dalerank/imspinner
		//-------------------------------------------------------------------------
		static void SpinnerBounceDots(String^ label, float radius, float thickness, Color color, float speed, size_t dots, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerBounceDots(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, dots, mode);
		}
		static void SpinnerFadeDots(String^ label, float radius, float thickness, Color color, float speed, int It, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerFadeDots(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, It, mode);
		}
		static void SpinnerScaleDots(String^ label, float radius, float thickness, Color color, float speed, int It)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerScaleDots(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, It);
		}
		static void SpinnerMovingDots(String^ label, float radius, float thickness, Color color, float speed, size_t dots)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerMovingDots(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, dots);
		}
		static void SpinnerRotateDots(String^ label, float radius, float thickness, Color color, float speed, int dots, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerRotateDots(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, dots, mode);
		}
		static void SpinnerTwinAng(String^ label, float radius1, float radius2, float thickness, Color color1, Color color2, float speed, float angle, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerTwinAng(ctx.marshal_as<const char*>(label), radius1, radius2, thickness, ColorToImU32(color1), ColorToImU32(color2), speed, angle, mode);
		}
		static void SpinnerClock(String^ label, float radius, float thickness, Color color, Color bg, float speed)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerClock(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), ColorToImU32(bg), speed);
		}
		static void SpinnerIngYang(String^ label, float radius, float thickness, bool reverse, float yang_delta_r, Color color1, Color color2, float speed, float angle)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerIngYang(ctx.marshal_as<const char*>(label), radius, thickness, reverse, yang_delta_r, ColorToImU32(color1), ColorToImU32(color2), speed, angle);
		}
		static void SpinnerBarChartSine(String^ label, float radius, float thickness, Color color, float speed, int bars, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerBarChartSine(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, bars, mode);
		}
		static void SpinnerTwinAng180(String^ label, float radius1, float radius2, float thickness, Color color1, Color color2, float speed, float angle, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerTwinAng180(ctx.marshal_as<const char*>(label), radius1, radius2, thickness, ColorToImU32(color1), ColorToImU32(color2), speed, angle, mode);
		}
		static void SpinnerIncDots(String^ label, float radius, float thickness, Color color, float speed, size_t dots)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerIncDots(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, dots);
		}
		static void SpinnerDots(String^ label, float% nextDot, float radius, float thickness, Color color, float speed, size_t dots, float minth, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			float nd = nextDot;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerDots(ctx.marshal_as<const char*>(label), &nd, radius, thickness, ColorToImU32(color), speed, dots, minth, mode);

			nextDot = nd;
		}
		static void SpinnerIncScaleDots(String^ label, float radius, float thickness, Color color, float speed, size_t dots, float angle, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerIncScaleDots(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, dots, angle, mode);
		}
		static void SpinnerAng(String^ label, float radius, float thickness, Color color, Color bg, float speed, float angle, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerAng(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), ColorToImU32(bg), speed, angle, mode);
		}
		static void SpinnerFadeBars(String^ label, float w, Color color, float speed, size_t bars, bool scale)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerFadeBars(ctx.marshal_as<const char*>(label), w, ColorToImU32(color), speed, bars, scale);
		}
		static void SpinnerPulsar(String^ label, float radius, float thickness, Color bg, float speed, bool sequence, float angle, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerPulsar(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(bg), speed, sequence, angle, mode);
		}
		static void SpinnerBarChartRainbow(String^ label, float radius, float thickness, Color bg, float speed, int bars, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerBarChartRainbow(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(bg), speed, bars, mode);
		}
		static void SpinnerBarsRotateFade(String^ label, float rMin, float rMax, float thickness, Color color, float speed, size_t bars)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerBarsRotateFade(ctx.marshal_as<const char*>(label), rMin, rMax, thickness, ColorToImU32(color), speed, bars);
		}
		static void SpinnerBarsScaleMiddle(String^ label, float w, Color color, float speed, size_t bars)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerBarsScaleMiddle(ctx.marshal_as<const char*>(label), w, ColorToImU32(color), speed, bars);
		}
		static void SpinnerAngTwin(String^ label, float radius1, float radius2, float thickness, Color color, Color bg, float speed, float angle, size_t arcs, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerAngTwin(ctx.marshal_as<const char*>(label), radius1, radius2, thickness, ColorToImU32(color), ColorToImU32(bg), speed, angle, arcs, mode);
		}
		static void SpinnerTwinPulsar(String^ label, float radius, float thickness, Color color, float speed, int rings, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerTwinPulsar(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, rings, mode);
		}
		static void SpinnerBlocks(String^ label, float radius, float thickness, Color color, Color bg, float speed)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerBlocks(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(bg), ColorToImU32(color), speed);
		}
		static void SpinnerTwinBall(String^ label, float radius1, float radius2, float thickness, float b_thickness, Color ball, Color bg, float speed, size_t balls)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerTwinBall(ctx.marshal_as<const char*>(label), radius1, radius2, thickness, b_thickness, ColorToImU32(ball), ColorToImU32(bg), speed, balls);
		}
		static void SpinnerAngTriple(String^ label, float radius1, float radius2, float radius3, float thickness, Color c1, Color c2, Color c3, float speed, float angle)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerAngTriple(ctx.marshal_as<const char*>(label), radius1, radius2, radius3, thickness, ColorToImU32(c1), ColorToImU32(c2), ColorToImU32(c3), speed, angle);
		}
		static void SpinnerIncFullDots(String^ label, float radius, float thickness, Color color, float speed, size_t dots)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerIncFullDots(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, dots);
		}
		static void SpinnerGooeyBalls(String^ label, float radius, Color color, float speed, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerGooeyBalls(ctx.marshal_as<const char*>(label), radius, ColorToImU32(color), speed, mode);
		}
		static void SpinnerRotateGooeyBalls(String^ label, float radius, float thickness, Color color, float speed, int balls, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerRotateGooeyBalls(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, balls, mode);
		}
		static void SpinnerMoonLine(String^ label, float radius, float thickness, Color color, Color bg, float speed, float angle)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerMoonLine(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), ColorToImU32(bg), speed, angle);
		}
		static void SpinnerArcRotation(String^ label, float radius, float thickness, Color color, float speed, size_t arcs, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerArcRotation(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, arcs, mode);
		}
		static void SpinnerFluid(String^ label, float radius, Color color, float speed, int bars)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerFluid(ctx.marshal_as<const char*>(label), radius, ColorToImU32(color), speed, bars);
		}
		static void SpinnerArcFade(String^ label, float radius, float thickness, Color color, float speed, size_t arcs, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerArcFade(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, arcs, mode);
		}
		static void SpinnerFilling(String^ label, float radius, float thickness, Color color1, Color color2, float speed)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerFilling(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color1), ColorToImU32(color2), speed);
		}
		static void SpinnerTopup(String^ label, float radius1, float radius2, Color color, Color fg, Color bg, float speed)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerTopup(ctx.marshal_as<const char*>(label), radius1, radius2, ColorToImU32(color), ColorToImU32(fg), ColorToImU32(bg), speed);
		}
		static void SpinnerFadePulsar(String^ label, float radius, Color color, float speed, int rings, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerFadePulsar(ctx.marshal_as<const char*>(label), radius, ColorToImU32(color), speed, rings, mode);
		}
		static void SpinnerDoubleFadePulsar(String^ label, float radius, Color color, float speed)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerDoubleFadePulsar(ctx.marshal_as<const char*>(label), radius, ColorToImU32(color), speed);
		}
		static void SpinnerFilledArcFade(String^ label, float radius, Color color, float speed, size_t arcs, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerFilledArcFade(ctx.marshal_as<const char*>(label), radius, ColorToImU32(color), speed, arcs, mode);
		}
		static void SpinnerFilledArcColor(String^ label, float radius, Color color, Color bg, float speed, size_t arcs)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerFilledArcColor(ctx.marshal_as<const char*>(label), radius, ColorToImU32(color), ColorToImU32(bg), speed, arcs);
		}
		static void SpinnerCircleDrop(String^ label, float radius, float thickness, float thickness_drop, Color color, Color bg, float speed, float angle)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerCircleDrop(ctx.marshal_as<const char*>(label), radius, thickness, thickness_drop, ColorToImU32(color), ColorToImU32(bg), speed, angle);
		}
		static void SpinnerSurroundedIndicator(String^ label, float radius, float thickness, Color color, Color bg, float speed)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerSurroundedIndicator(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), ColorToImU32(bg), speed);
		}
		static void SpinnerTrianglesSelector(String^ label, float radius, float thickness, Color color, Color bg, float speed, size_t bars)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerTrianglesSelector(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), ColorToImU32(bg), speed, bars);
		}
		static void SpinnerFlowingGradient(String^ label, float radius, float thickness, Color color, Color bg, float speed, float angle)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerFlowingGradient(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), ColorToImU32(bg), speed, angle);
		}
		static void SpinnerRotateSegments(String^ label, float radius, float thickness, Color color, float speed, size_t arcs, size_t layers, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerRotateSegments(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, arcs, layers, mode);
		}
		static void SpinnerLemniscate(String^ label, float radius, float thickness, Color color, float speed, float angle)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerLemniscate(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, angle);
		}
		static void SpinnerRotateGear(String^ label, float radius, float thickness, Color color, float speed, size_t pins)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerRotateGear(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, pins);
		}
		static void SpinnerRotatedAtom(String^ label, float radius, float thickness, Color color, float speed, int elipses, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerRotatedAtom(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, elipses, mode);
		}
		static void SpinnerAtom(String^ label, float radius, float thickness, Color color, float speed, int elipses)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerAtom(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, elipses);
		}
		static void SpinnerRainbowBalls(String^ label, float radius, float thickness, Color color, float speed, int balls, int mode)
		{
			if (String::IsNullOrWhiteSpace(label))
				return;

			msclr::interop::marshal_context ctx;
			ImSpinner::SpinnerRainbowBalls(ctx.marshal_as<const char*>(label), radius, thickness, ColorToImU32(color), speed, balls, mode);
		}

	private:
		static bool m_bWasImGuiInitialized;
		static bool m_bDisableControllerInput;
		static bool m_bDisableMouseInput;
		static bool m_bDisableKeyboardInput;
		static bool m_bForceCursor;
		static int m_iActiveScriptWindows;
	};

}

class ImGuiDraw
{
public:
	static bool OnWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static void EnableControllerNavigation(ImGuiIO& io);
	static void DisableControllerNavigation(ImGuiIO& io);

	static void OnBeforeD3D9DeviceEndScene(IDirect3DDevice9* d3d9Device);

	static void OnAfterD3D9DeviceBeginScene(IDirect3DDevice9* d3d9Device);

	static void OnBeforeD3D9DeviceReset(IDirect3DDevice9* d3d9Device);
	static void OnAfterD3D9DeviceReset();

	static void UninitializeImGui();

private:
	static void InitializeImGui(IDirect3DDevice9* d3d9Device);
	static void DoDockspace();

private:
	static inline bool m_bDidResetInputStates;
};