using System.Numerics;

using IVSDKDotNet;
using IVSDKDotNet.Enums;

using Manager.Classes;

namespace Manager.UI
{
    internal static class UIStyles
    {

        public static void ResetImGuiStyle()
        {
            string selectedImGuiStyle = Config.ImGuiStyle.ToLower();

            if (selectedImGuiStyle == "dark")
                ImGuiIV.StyleColorsDark();
            else if (selectedImGuiStyle == "classic")
                ImGuiIV.StyleColorsClassic();
            else if (selectedImGuiStyle == "light")
                ImGuiIV.StyleColorsLight();
            else
                ImGuiIV.StyleColorsDark();

            ImGuiIV.StyleLayoutDefault();
        }

        public static void SetImGuiPurpleStyle()
        {
            // Purple Comfy style by RegularLunar from ImThemes
            // Slighty modified
            ImGuiIV_Style style = ImGuiIV.GetStyle();

            style.Alpha = 1.0f;
            style.DisabledAlpha = 0.5f;
            style.WindowPadding = new Vector2(8.0f, 8.0f);
            style.WindowRounding = 10.0f;
            style.WindowBorderSize = 1.0f;
            style.WindowMinSize = new Vector2(30.0f, 30.0f);
            style.WindowTitleAlign = new Vector2(0.5f, 0.5f);
            style.WindowMenuButtonPosition = eImGuiDir.Right;
            style.ChildRounding = 5.0f;
            style.ChildBorderSize = 1.0f;
            style.PopupRounding = 10.0f;
            style.PopupBorderSize = 0.0f;
            style.FramePadding = new Vector2(5.0f, 3.5f);
            style.FrameRounding = 5.0f;
            style.FrameBorderSize = 0.0f;
            style.ItemSpacing = new Vector2(5.0f, 4.0f);
            style.ItemInnerSpacing = new Vector2(5.0f, 5.0f);
            style.CellPadding = new Vector2(4.0f, 2.0f);
            style.IndentSpacing = 5.0f;
            style.ColumnsMinSpacing = 5.0f;
            style.ScrollbarSize = 15.0f;
            style.ScrollbarRounding = 9.0f;
            style.GrabMinSize = 15.0f;
            style.GrabRounding = 5.0f;
            style.TabRounding = 5.0f;
            style.TabBorderSize = 0.0f;
            style.TabMinWidthForCloseButton = 0.0f;
            style.ColorButtonPosition = eImGuiDir.Right;
            style.ButtonTextAlign = new Vector2(0.5f, 0.5f);
            style.SelectableTextAlign = new Vector2(0.0f, 0.0f);

            Vector4[] colors = style.Colors;
            colors[(int)eImGuiCol.Text] = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);
            colors[(int)eImGuiCol.TextDisabled] = new Vector4(1.0f, 1.0f, 1.0f, 0.3605149984359741f);
            colors[(int)eImGuiCol.WindowBg] = new Vector4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
            colors[(int)eImGuiCol.ChildBg] = new Vector4(1.0f, 0.0f, 0.0f, 0.0f);
            colors[(int)eImGuiCol.PopupBg] = new Vector4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
            colors[(int)eImGuiCol.Border] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.BorderShadow] = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
            colors[(int)eImGuiCol.FrameBg] = new Vector4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
            colors[(int)eImGuiCol.FrameBgHovered] = new Vector4(0.3803921639919281f, 0.4235294163227081f, 0.572549045085907f, 0.5490196347236633f);
            colors[(int)eImGuiCol.FrameBgActive] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TitleBg] = new Vector4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
            colors[(int)eImGuiCol.TitleBgActive] = new Vector4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
            colors[(int)eImGuiCol.TitleBgCollapsed] = new Vector4(0.2588235437870026f, 0.2588235437870026f, 0.2588235437870026f, 0.55f);
            colors[(int)eImGuiCol.MenuBarBg] = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
            colors[(int)eImGuiCol.ScrollbarBg] = new Vector4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 0.0f);
            colors[(int)eImGuiCol.ScrollbarGrab] = new Vector4(0.2f, 0.2f, 0.2f, 1.0f);
            colors[(int)eImGuiCol.ScrollbarGrabHovered] = new Vector4(0.2352941185235977f, 0.2352941185235977f, 0.2352941185235977f, 1.0f);
            colors[(int)eImGuiCol.ScrollbarGrabActive] = new Vector4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
            colors[(int)eImGuiCol.CheckMark] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.SliderGrab] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.SliderGrabActive] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.Button] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.ButtonHovered] = new Vector4(0.56f, 0.38f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.ButtonActive] = new Vector4(0.44f, 0.22f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.Header] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.HeaderHovered] = new Vector4(0.56f, 0.38f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.HeaderActive] = new Vector4(0.44f, 0.22f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.Separator] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.SeparatorHovered] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.SeparatorActive] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.ResizeGrip] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.ResizeGripHovered] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.ResizeGripActive] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.Tab] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TabHovered] = new Vector4(0.56f, 0.38f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TabActive] = new Vector4(0.44f, 0.22f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TabUnfocused] = new Vector4(0.0f, 0.4509803950786591f, 1.0f, 0.0f);
            colors[(int)eImGuiCol.TabUnfocusedActive] = new Vector4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 0.0f);
            colors[(int)eImGuiCol.PlotLines] = new Vector4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
            colors[(int)eImGuiCol.PlotLinesHovered] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.PlotHistogram] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.PlotHistogramHovered] = new Vector4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TableHeaderBg] = new Vector4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
            colors[(int)eImGuiCol.TableBorderStrong] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TableBorderLight] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.2901960909366608f);
            colors[(int)eImGuiCol.TableRowBg] = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
            colors[(int)eImGuiCol.TableRowBgAlt] = new Vector4(1.0f, 1.0f, 1.0f, 0.03433477878570557f);
            colors[(int)eImGuiCol.TextSelectedBg] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.DragDropTarget] = new Vector4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
            colors[(int)eImGuiCol.NavHighlight] = new Vector4(0.0f, 0.0f, 0.0f, 1.0f);
            colors[(int)eImGuiCol.NavWindowingHighlight] = new Vector4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
            colors[(int)eImGuiCol.NavWindowingDimBg] = new Vector4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
            colors[(int)eImGuiCol.ModalWindowDimBg] = new Vector4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
            style.Colors = colors;
        }

    }
}
