#pragma once

namespace ImGui
{

	//------------------------------------------------------------------
	// Helpers
	//------------------------------------------------------------------
	IMGUI_API float GetWindowContentRegionWidth();

	//------------------------------------------------------------------
	// Timeline
	//------------------------------------------------------------------

	// Code is from the LumixEngine project by Mikulas Florek. All credits goes to them! I just modified it a bit.
	// https://github.com/nem0/LumixEngine/blob/timeline_gui/external/imgui/imgui_user.inl#L814
	
	IMGUI_API bool BeginTimeline(const char* str_id, ImVec2 size, ImGuiChildFlags cFlags, ImGuiWindowFlags wFlags);
	IMGUI_API bool Timeline(const char* str_id, float* values, int maxFrames);
	IMGUI_API void EndTimeline(bool drawCurrentFrame, int currentFrame, int maxFrames, bool drawLines, int lineCount, bool drawValues);

}