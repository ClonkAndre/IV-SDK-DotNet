#include "ImGuiIncludes.h"
#include "imgui_extensions.h"

namespace ImGui
{

	//------------------------------------------------------------------
	// Helpers
	//------------------------------------------------------------------
	float GetWindowContentRegionWidth()
	{
		ImGuiWindow* window = GImGui->CurrentWindow;
		return window->ContentRegionRect.GetWidth();
	}

	//------------------------------------------------------------------
	// Timeline
	//------------------------------------------------------------------
	const float TIMELINE_RADIUS = 6;

	bool BeginTimeline(const char* str_id, ImVec2 size, ImGuiChildFlags cFlags, ImGuiWindowFlags wFlags)
	{
		return BeginChild(str_id, size, cFlags, wFlags);
	}
	bool Timeline(const char* str_id, float* values, int maxFrames)
	{
		ImGuiWindow* win = GetCurrentWindow();
		const ImU32 inactive_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Button]);
		const ImU32 active_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_ButtonHovered]);
		const ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_ButtonActive]);
		bool changed = false;
		ImVec2 cursor_pos = win->DC.CursorPos;

		for (int i = 0; i < 2; ++i)
		{
			ImVec2 pos = cursor_pos;
			pos.x += win->Size.x * values[i] / maxFrames + TIMELINE_RADIUS;
			pos.y += TIMELINE_RADIUS;

			SetCursorScreenPos(pos - ImVec2(TIMELINE_RADIUS, TIMELINE_RADIUS));
			PushID(i);
			InvisibleButton(str_id, ImVec2(2 * TIMELINE_RADIUS, 2 * TIMELINE_RADIUS));
			if (IsItemActive() || IsItemHovered())
			{
				ImGui::SetTooltip("%f", values[i]);
				ImVec2 a(pos.x, GetWindowContentRegionMin().y + win->Pos.y);
				ImVec2 b(pos.x, GetWindowContentRegionMax().y + win->Pos.y);
				win->DrawList->AddLine(a, b, line_color);
			}
			if (IsItemActive() && IsMouseDragging(0))
			{
				values[i] += GetIO().MouseDelta.x / win->Size.x * maxFrames;
				changed = true;
			}
			PopID();
			win->DrawList->AddCircleFilled(pos, TIMELINE_RADIUS, IsItemActive() || IsItemHovered() ? active_color : inactive_color);
		}

		ImVec2 start = cursor_pos;
		start.x += win->Size.x * values[0] / maxFrames + 2 * TIMELINE_RADIUS;
		start.y += TIMELINE_RADIUS * 0.5f;
		ImVec2 end = start + ImVec2(win->Size.x * (values[1] - values[0]) / maxFrames - 2 * TIMELINE_RADIUS, TIMELINE_RADIUS);

		PushID(-1);
		SetCursorScreenPos(start);
		InvisibleButton(str_id, end - start);
		if (IsItemActive() && IsMouseDragging(0))
		{
			values[0] += GetIO().MouseDelta.x / win->Size.x * maxFrames;
			values[1] += GetIO().MouseDelta.x / win->Size.x * maxFrames;
			changed = true;
		}
		PopID();

		SetCursorScreenPos(cursor_pos + ImVec2(0, GetTextLineHeightWithSpacing()));

		win->DrawList->AddRectFilled(start, end, IsItemActive() || IsItemHovered() ? active_color : inactive_color);

		if (values[0] > values[1])
		{
			float tmp = values[0];
			values[0] = values[1];
			values[1] = tmp;
		}

		if (values[1] > maxFrames)
			values[1] = maxFrames;

		if (values[0] < 0)
			values[0] = 0;

		return changed;
	}
	void EndTimeline(bool drawCurrentFrame, int currentFrame, int maxFrames, bool drawLines, int lineCount, bool drawValues)
	{
		ImGuiWindow* win = GetCurrentWindow();

		ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Border]);
		ImU32 text_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Text]);
		ImU32 currentFrameLineColor = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_PlotLinesHovered]);

		ImVec2 start(GetWindowContentRegionMin().x + win->Pos.x,
			GetWindowContentRegionMax().y - GetTextLineHeightWithSpacing() + win->Pos.y + 3);

		SetCursorScreenPos(start);
		PushItemWidth(GetWindowContentRegionWidth());
		SliderInt("##timelineFrameSlider", &currentFrame, 0, maxFrames, "");

		if (drawCurrentFrame)
		{
			ImVec2 a = GetWindowContentRegionMin() + win->Pos + ImVec2(TIMELINE_RADIUS, 0);
			a.x += currentFrame * GetWindowContentRegionWidth() / maxFrames;
			ImVec2 b = a;
			b.y = start.y;
			win->DrawList->AddLine(a, b, currentFrameLineColor);
		}

		for (int i = 0; i < lineCount; ++i)
		{
			ImVec2 a = GetWindowContentRegionMin() + win->Pos + ImVec2(TIMELINE_RADIUS, 0);
			a.x += i * GetWindowContentRegionWidth() / lineCount;
			ImVec2 b = a;
			b.y = start.y;

			if (drawLines)
				win->DrawList->AddLine(a, b, line_color);

			if (drawValues)
			{
				char tmp[256];
				ImFormatString(tmp, sizeof(tmp), "%i", (int)(i * maxFrames / lineCount));
				win->DrawList->AddText(b, text_color, tmp);
			}
		}

		EndChild();
	}

}