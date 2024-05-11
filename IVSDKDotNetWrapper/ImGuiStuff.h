#pragma once
#include "pch.h"

using namespace IVSDKDotNet::Enums;

namespace ImGuiStates
{
	// Initialized State
	static bool s_bIsImGuiInitialized;
	static bool s_bWasImGuiInitializedSuccessfully;
	static bool s_bWasImGuiUnitialized;

	static bool s_bStopTryingToInitializeImGui;

	// Sets s_bIsImGuiInitialized to false, s_bWasImGuiUnitialized to true and s_bStopTryingToInitializeImGui to true.
	static void SetImGuiStatusAsWasUninitialized()
	{
		s_bIsImGuiInitialized = false;
		s_bWasImGuiUnitialized = true;
		s_bStopTryingToInitializeImGui = true;
	}

	// Input State
	static bool s_bReactivateKeyboardInputs;
	static bool s_bImGuiWantsMouseDisabled;
	static bool s_bImGuiWantsKeyboardDisabled;
}

namespace IVSDKDotNet
{
	public value struct ImGuiIV_DrawingContext
	{
	public:

		/// <summary>
		/// Native Pointer to the ImDrawList structure.
		/// </summary>
		property IntPtr ImDrawListPtr
		{
		public:
			IntPtr get()
			{
				return IntPtr(canvasDrawList);
			}
		}

	public:
		ImGuiIV_DrawingContext(IntPtr drawListPtr)
		{
			if (drawListPtr == IntPtr::Zero)
			{
				throw gcnew ArgumentNullException("drawListPtr");
				return;
			}

			canvasDrawList = (ImDrawList*)drawListPtr.ToPointer();
		}

	internal:
		ImGuiIV_DrawingContext(ImDrawList* drawList)
		{
			canvasDrawList = drawList;
		}

	public:

		// Clip Rectangle
		void PushClipRect(RectangleF rect, bool intersectWithCurrentClipRect)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->PushClipRect(
				Vector2ToImVec2(Vector2(rect.X, rect.Y)),
				Vector2ToImVec2(Vector2(rect.Right, rect.Bottom)),
				intersectWithCurrentClipRect);
		}
		void PushClipRectFullScreen()
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->PushClipRectFullScreen();
		}
		void PopClipRect()
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->PopClipRect();
		}

		// Texture
		void PushTextureID(IntPtr textureId)
		{
			if (!canvasDrawList)
				return;
			if (textureId == IntPtr::Zero)
				return;

			canvasDrawList->PushTextureID(textureId.ToPointer());
		}
		void PopTextureID()
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->PopTextureID();
		}

		// Line
		void AddLine(Vector2 p1, Vector2 p2, Color color, float thickness)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddLine(
				Vector2ToImVec2(p1),
				Vector2ToImVec2(p2),
				ColorToImU32(color),
				thickness);
		}

		// Rectangle
		void AddRect(Vector2 min, Vector2 max, Color color, float rounding, eImDrawFlags flags, float thickness)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddRect(
				Vector2ToImVec2(min),
				Vector2ToImVec2(max),
				ColorToImU32(color),
				rounding,
				(ImDrawFlags)flags,
				thickness);
		}
		void AddRectFilled(Vector2 min, Vector2 max, Color color, float rounding, eImDrawFlags flags)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddRectFilled(
				Vector2ToImVec2(min),
				Vector2ToImVec2(max),
				ColorToImU32(color),
				rounding,
				(ImDrawFlags)flags);
		}
		void AddRectFilledMultiColor(Vector2 min, Vector2 max, Color upperLeft, Color upperRight, Color bottomLeft, Color bottomRight)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddRectFilledMultiColor(
				Vector2ToImVec2(min),
				Vector2ToImVec2(max),
				ColorToImU32(upperLeft),
				ColorToImU32(upperRight),
				ColorToImU32(bottomRight),
				ColorToImU32(bottomLeft));
		}

		// Quad
		void AddQuad(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Color color, float thickness)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddQuad(
				Vector2ToImVec2(p1),
				Vector2ToImVec2(p2),
				Vector2ToImVec2(p3),
				Vector2ToImVec2(p4),
				ColorToImU32(color),
				thickness);
		}
		void AddQuadFilled(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Color color)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddQuadFilled(
				Vector2ToImVec2(p1),
				Vector2ToImVec2(p2),
				Vector2ToImVec2(p3),
				Vector2ToImVec2(p4),
				ColorToImU32(color));
		}

		// Triangle
		void AddTriangle(Vector2 p1, Vector2 p2, Vector2 p3, Color color, float thickness)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddTriangle(
				Vector2ToImVec2(p1),
				Vector2ToImVec2(p2),
				Vector2ToImVec2(p3),
				ColorToImU32(color),
				thickness);
		}
		void AddTriangleFilled(Vector2 p1, Vector2 p2, Vector2 p3, Color color)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddTriangleFilled(
				Vector2ToImVec2(p1),
				Vector2ToImVec2(p2),
				Vector2ToImVec2(p3),
				ColorToImU32(color));
		}

		// Circle
		void AddCircle(Vector2 center, float radius, Color color, int numSegments, float thickness)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddCircle(
				Vector2ToImVec2(center),
				radius,
				ColorToImU32(color),
				numSegments,
				thickness);
		}
		void AddCircleFilles(Vector2 center, float radius, Color color, int numSegments)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddCircleFilled(
				Vector2ToImVec2(center),
				radius,
				ColorToImU32(color),
				numSegments);
		}

		// Ngon
		void AddNgon(Vector2 center, float radius, Color color, int numSegments, float thickness)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddNgon(
				Vector2ToImVec2(center),
				radius,
				ColorToImU32(color),
				numSegments,
				thickness);
		}
		void AddNgonFilled(Vector2 center, float radius, Color color, int numSegments)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddNgonFilled(
				Vector2ToImVec2(center),
				radius,
				ColorToImU32(color),
				numSegments);
		}

		// Ellipse
		void AddEllipse(Vector2 center, Vector2 radius, Color color, float rotation, int numSegments, float thickness)
		{
			canvasDrawList->AddEllipse(
				Vector2ToImVec2(center),
				radius.X,
				radius.Y,
				ColorToImU32(color),
				rotation,
				numSegments,
				thickness);
		}
		void AddEllipseFilled(Vector2 center, Vector2 radius, Color color, float rotation, int numSegments)
		{
			canvasDrawList->AddEllipseFilled(
				Vector2ToImVec2(center),
				radius.X,
				radius.Y,
				ColorToImU32(color),
				rotation,
				numSegments);
		}

		// Bezier
		void AddBezierCubic(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Color color, float thickness, int numSegments)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddBezierCubic(
				Vector2ToImVec2(p1),
				Vector2ToImVec2(p2),
				Vector2ToImVec2(p3),
				Vector2ToImVec2(p4),
				ColorToImU32(color),
				thickness,
				numSegments);
		}

		// Quadratic Bezier
		void AddBezierQuadratic(Vector2 p1, Vector2 p2, Vector2 p3, Color color, float thickness, int numSegments)
		{
			if (!canvasDrawList)
				return;

			canvasDrawList->AddBezierQuadratic(
				Vector2ToImVec2(p1),
				Vector2ToImVec2(p2),
				Vector2ToImVec2(p3),
				ColorToImU32(color),
				thickness,
				numSegments);
		}

		// Text
		void AddText(IntPtr fontPtr, float fontSize, Vector2 pos, Color color, String^ textBegin, String^ textEnd, float wrapWidth)
		{
			if (!canvasDrawList)
				return;
			if (String::IsNullOrWhiteSpace(textBegin))
				return;

			msclr::interop::marshal_context ctx;

			const char* _textBegin = ctx.marshal_as<const char*>(textBegin);
			const char* _textEnd = (const char*)0;

			if (!String::IsNullOrWhiteSpace(textEnd))
				_textEnd = ctx.marshal_as<const char*>(textEnd);

			ImFont* imFont = fontPtr == IntPtr::Zero ? nullptr : (ImFont*)fontPtr.ToPointer();

			if (imFont)
				ImGui::PushFont(imFont);

			canvasDrawList->AddText(
				imFont,
				fontSize,
				Vector2ToImVec2(pos),
				ColorToImU32(color),
				_textBegin,
				_textEnd,
				wrapWidth,
				nullptr);

			if (imFont)
				ImGui::PopFont();
		}
		void AddText(float fontSize, Vector2 pos, Color color, String^ textBegin, String^ textEnd, float wrapWidth)
		{
			AddText(IntPtr::Zero, fontSize, pos, color, textBegin, textEnd, wrapWidth);
		}

		void AddText(IntPtr fontPtr, Vector2 pos, Color color, float fontSize, String^ textBegin)
		{
			if (!canvasDrawList)
				return;
			if (String::IsNullOrWhiteSpace(textBegin))
				return;

			msclr::interop::marshal_context ctx;

			const char* _textBegin = ctx.marshal_as<const char*>(textBegin);
			const char* _textEnd = (const char*)0;

			ImFont* imFont = fontPtr == IntPtr::Zero ? nullptr : (ImFont*)fontPtr.ToPointer();

			if (imFont)
				ImGui::PushFont(imFont);

			canvasDrawList->AddText(
				imFont,
				fontSize,
				Vector2ToImVec2(pos),
				ColorToImU32(color),
				_textBegin,
				_textEnd,
				0.0F,
				nullptr);

			if (imFont)
				ImGui::PopFont();
		}
		void AddText(Vector2 pos, Color color, float fontSize, String^ textBegin)
		{
			if (!canvasDrawList)
				return;
			if (String::IsNullOrWhiteSpace(textBegin))
				return;

			msclr::interop::marshal_context ctx;

			const char* _textBegin = ctx.marshal_as<const char*>(textBegin);
			const char* _textEnd = (const char*)0;

			canvasDrawList->AddText(
				nullptr,
				fontSize,
				Vector2ToImVec2(pos),
				ColorToImU32(color),
				_textBegin,
				_textEnd,
				0.0F,
				nullptr);
		}
		
		void AddText(IntPtr fontPtr, Vector2 pos, Color color, String^ textBegin, String^ textEnd)
		{
			if (!canvasDrawList)
				return;
			if (String::IsNullOrWhiteSpace(textBegin))
				return;

			msclr::interop::marshal_context ctx;

			const char* _textBegin = ctx.marshal_as<const char*>(textBegin);
			const char* _textEnd = (const char*)0;

			if (!String::IsNullOrWhiteSpace(textEnd))
				_textEnd = ctx.marshal_as<const char*>(textEnd);

			ImFont* imFont = fontPtr == IntPtr::Zero ? nullptr : (ImFont*)fontPtr.ToPointer();

			if (imFont)
				ImGui::PushFont(imFont);

			canvasDrawList->AddText(
				imFont,
				0.0F,
				Vector2ToImVec2(pos),
				ColorToImU32(color),
				_textBegin,
				_textEnd,
				0.0F,
				nullptr);

			if (imFont)
				ImGui::PopFont();
		}
		void AddText(Vector2 pos, Color color, String^ textBegin, String^ textEnd)
		{
			AddText(IntPtr::Zero, pos, color, textBegin, textEnd);

			//if (!canvasDrawList)
			//	return;
			//if (String::IsNullOrWhiteSpace(textBegin))
			//	return;

			//msclr::interop::marshal_context ctx;

			//const char* _textBegin = ctx.marshal_as<const char*>(textBegin);
			//const char* _textEnd = (const char*)0;

			//if (!String::IsNullOrWhiteSpace(textEnd))
			//	_textEnd = ctx.marshal_as<const char*>(textEnd);

			//canvasDrawList->AddText(
			//	Vector2ToImVec2(pos),
			//	ColorToImU32(color),
			//	_textBegin,
			//	_textEnd);
		}

		void AddText(IntPtr fontPtr, Vector2 pos, Color color, String^ textBegin)
		{
			AddText(fontPtr, pos, color, textBegin, nullptr);
		}
		void AddText(Vector2 pos, Color color, String^ textBegin)
		{
			AddText(pos, color, textBegin, nullptr);
		}

		// Image
		void AddImage(IntPtr texturePtr, Vector2 min, Vector2 max, Vector2 uvMin, Vector2 uvMax, Color color)
		{
			if (!canvasDrawList)
				return;
			if (texturePtr == IntPtr::Zero)
				return;

			canvasDrawList->AddImage(
				(ImTextureID)texturePtr,
				Vector2ToImVec2(min),
				Vector2ToImVec2(max),
				Vector2ToImVec2(uvMin),
				Vector2ToImVec2(uvMax),
				ColorToImU32(color));
		}
		void AddImage(IntPtr texturePtr, RectangleF rect, Color color)
		{
			if (!canvasDrawList)
				return;
			if (rect == RectangleF::Empty)
				return;

			AddImage(texturePtr, Vector2(rect.Left, rect.Top), Vector2(rect.Right, rect.Bottom), Vector2::Zero, Vector2::One, color);
		}

		void AddImageQuad(IntPtr texturePtr, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2 uv1, Vector2 uv2, Vector2 uv3, Vector2 uv4, Color color)
		{
			if (!canvasDrawList)
				return;
			if (texturePtr == IntPtr::Zero)
				return;

			canvasDrawList->AddImageQuad(
				(ImTextureID)texturePtr,
				Vector2ToImVec2(p1),
				Vector2ToImVec2(p2),
				Vector2ToImVec2(p3),
				Vector2ToImVec2(p4),
				Vector2ToImVec2(uv1),
				Vector2ToImVec2(uv2),
				Vector2ToImVec2(uv3),
				Vector2ToImVec2(uv4),
				ColorToImU32(color));
		}
		void AddImageRounded(IntPtr texturePtr, Vector2 min, Vector2 max, Vector2 uvMin, Vector2 uvMax, Color color, float rounding, eImDrawFlags flags)
		{
			if (!canvasDrawList)
				return;
			if (texturePtr == IntPtr::Zero)
				return;

			canvasDrawList->AddImageRounded(
				(ImTextureID)texturePtr,
				Vector2ToImVec2(min),
				Vector2ToImVec2(max),
				Vector2ToImVec2(uvMin),
				Vector2ToImVec2(uvMax),
				ColorToImU32(color),
				rounding,
				(int)flags);
		}

		void AddImageRotated(IntPtr texturePtr, RectangleF rect, Vector2 center, float angle, Color color)
		{
			if (!canvasDrawList)
				return;
			if (texturePtr == IntPtr::Zero)
				return;
			if (rect == RectangleF::Empty)
				return;

			// Get size and position of image
			ImVec2 size = Vector2ToImVec2(center);
			ImVec2 pos = ImVec2(rect.X + size.x, rect.Y + size.y);

			// Calculate sin and cos of given angle
			float aSin = sinf(angle);
			float aCos = cosf(angle);

			// Handle rotation
			ImVec2 points[4] =
			{
				Add(pos, ImRotate(ImVec2(-size.x, -size.y), aCos, aSin)),
				Add(pos, ImRotate(ImVec2(+size.x, -size.y), aCos, aSin)),
				Add(pos, ImRotate(ImVec2(+size.x, +size.y), aCos, aSin)),
				Add(pos, ImRotate(ImVec2(-size.x, +size.y), aCos, aSin))
			};

			// Draw image
			canvasDrawList->AddImageQuad(
				(ImTextureID)texturePtr,
				points[0],
				points[1],
				points[2],
				points[3],
				ImVec2(0.0F, 0.0F),
				ImVec2(1.0F, 0.0F),
				ImVec2(1.0F, 1.0F),
				ImVec2(0.0F, 1.0F),
				ColorToImU32(color));
		}
		void AddImageRotated(IntPtr texturePtr, RectangleF rect, float angle, Color color)
		{
			AddImageRotated(texturePtr, rect, Vector2(rect.Width * 0.5F, rect.Height * 0.5F), angle, color);
		}

	private:
		ImDrawList* canvasDrawList;
	};
}