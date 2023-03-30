#include "pch.h"
#include "Direct3D9.h"

namespace IVSDKDotNet {
	namespace Direct3D9 {

		// Constructor / Destructor
		D3DGraphics::D3DGraphics(Script^ createFor)
		{
			if (!createFor)
				throw gcnew NullReferenceException("'createFor' cannot be null.");

			CreatedFor = createFor;
			Scaling = eFontScaling::Pixel;
			Object^ t = (Object^)this;
			Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateNewInstance(t, createFor);
		}
		D3DGraphics::~D3DGraphics()
		{
			Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DisposeInstance(m_createForScript);
			CreatedFor = nullptr;
		}

		// Texture stuff
		D3DResult^ D3DGraphics::CreateD3D9Texture(String^ filePath, Size size)
		{
			if (Device == IntPtr::Zero)
				return gcnew D3DResult(gcnew Exception("Device is not valid!"));

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateD3D9Texture(m_createForScript, Device, filePath, size);
		}
		D3DResult^ D3DGraphics::CreateD3D9Texture(String^ filePath)
		{
			if (Device == IntPtr::Zero)
				return gcnew D3DResult(gcnew Exception("Device is not valid!"));

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateD3D9Texture(m_createForScript, Device, filePath, Size::Empty);
		}
		D3DResult^ D3DGraphics::CreateD3D9Texture(array<Byte>^ data, Size size)
		{
			if (Device == IntPtr::Zero)
				return gcnew D3DResult(gcnew Exception("Device is not valid!"));

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateD3D9Texture(m_createForScript, Device, data, size);
		}
		D3DResult^ D3DGraphics::CreateD3D9Texture(array<Byte>^ data)
		{
			if (Device == IntPtr::Zero)
				return gcnew D3DResult(gcnew Exception("Device is not valid!"));

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateD3D9Texture(m_createForScript, Device, data, Size::Empty);
		}
		Exception^ D3DGraphics::ReleaseD3D9Texture(D3DResource^ textureResource)
		{
			if (!textureResource)
				return gcnew NullReferenceException("textureResource cannot be null!");

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_ReleaseD3D9Texture(m_createForScript, textureResource);
		}

		// Font stuff
		D3DResult^ D3DGraphics::CreateD3D9Font(D3DFontDescription fontDescription)
		{
			if (Device == IntPtr::Zero)
				return gcnew D3DResult(gcnew Exception("Device is not valid!"));

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateD3D9Font(m_createForScript, Device, fontDescription);
		}
		Exception^ D3DGraphics::ReleaseD3D9Font(D3DResource^ fontResource)
		{
			if (!fontResource)
				return gcnew NullReferenceException("fontResource cannot be null!");

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_ReleaseD3D9Font(m_createForScript, fontResource);
		}

		Drawing::Rectangle D3DGraphics::MeasureText(D3DResource^ fontResource, String^ text, Drawing::Rectangle rect, eD3DFontDrawFlags drawFlags)
		{
			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_MeasureText(fontResource, text, rect, drawFlags);
		}
		Drawing::Rectangle D3DGraphics::MeasureText(D3DResource^ fontResource, String^ text, eD3DFontDrawFlags drawFlags)
		{
			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_MeasureText(fontResource, text, Drawing::Rectangle::Empty, drawFlags);
		}
		Drawing::Rectangle D3DGraphics::MeasureText(D3DResource^ fontResource, String^ text)
		{
			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_MeasureText(fontResource, text, Drawing::Rectangle::Empty, eD3DFontDrawFlags::Left);
		}
		Drawing::Rectangle D3DGraphics::MeasureText(String^ text)
		{
			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_MeasureText(nullptr, text, Drawing::Rectangle::Empty, eD3DFontDrawFlags::Left);
		}

		// Drawing functions
		bool D3DGraphics::DrawLines(array<Vector2>^ vertices, Color color, bool antialias, int pattern, float patternScale, float thickness)
		{
			if (Device == IntPtr::Zero)
				return false;
			if (vertices == nullptr)
				return false;
			if (vertices == Array::Empty<Vector2>())
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLines(this, Device, vertices, color, antialias, pattern, patternScale, thickness);
		}
		bool D3DGraphics::DrawLines(array<Vector2>^ vertices, Color color, bool antialias, float thickness)
		{
			if (Device == IntPtr::Zero)
				return false;
			if (vertices == nullptr)
				return false;
			if (vertices == Array::Empty<Vector2>())
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLines(this, Device, vertices, color, antialias, -1, 1.0F, thickness);
		}
		bool D3DGraphics::DrawLine(Vector2 point1, Vector2 point2, Color color, bool antialias, int pattern, float patternScale, float thickness)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLine(this, Device, point1, point2, color, antialias, pattern, patternScale, thickness);
		}
		bool D3DGraphics::DrawLine(Vector2 point1, Vector2 point2, Color color, bool antialias, int pattern, float thickness)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLine(this, Device, point1, point2, color, antialias, pattern, 1.0F, thickness);
		}
		bool D3DGraphics::DrawLine(Vector2 point1, Vector2 point2, Color color, bool antialias, float thickness)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLine(this, Device, point1, point2, color, antialias, -1, 1.0F, thickness);
		}
		bool D3DGraphics::DrawLine(Vector2 point1, Vector2 point2, Color color, float thickness)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLine(this, Device, point1, point2, color, false, -1, 1.0F, thickness);
		}

		bool D3DGraphics::DrawCircle(Vector2 pos, float radius, float rotation, eD3DCircleType type, bool smoothing, int resolution, Color color)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawCircle(this, Device, pos, radius, rotation, type, smoothing, resolution, color);
		}
		bool D3DGraphics::DrawCircleFilled(Vector2 pos, float radius, float rotation, eD3DCircleType type, bool smoothing, int resolution, Color color)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawCircleFilled(this, Device, pos, radius, rotation, type, smoothing, resolution, color);
		}

		bool D3DGraphics::DrawBoxFilled(Vector2 pos, SizeF size, Color color)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawBoxFilled(this, Device, pos, size, color);
		}
		bool D3DGraphics::DrawBox(Vector2 pos, SizeF size, float lineWidth, Color color)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawBox(this, Device, pos, size, lineWidth, color);
		}
		bool D3DGraphics::DrawBoxBordered(Vector2 pos, SizeF size, float borderWidth, Color color, Color borderColor)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawBoxBordered(this, Device, pos, size, borderWidth, color, borderColor);
		}
		bool D3DGraphics::DrawBoxRounded(Vector2 pos, SizeF size, float radius, bool smoothing, Color color, Color borderColor)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawBoxRounded(this, Device, pos, size, radius, smoothing, color, borderColor);
		}

		bool D3DGraphics::DrawTexture(D3DResource^ txt, RectangleF rect, float rotation, Color tint)
		{
			if (Device == IntPtr::Zero)
				return false;
			if (!txt)
				return false;
			if (txt->Handle == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawTexture(this, Device, txt, rect, rotation, tint);
		}
		bool D3DGraphics::DrawTexture(D3DResource^ txt, RectangleF rect, Color tint)
		{
			if (Device == IntPtr::Zero)
				return false;
			if (!txt)
				return false;
			if (txt->Handle == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawTexture(this, Device, txt, rect, 0.0F, tint);
		}
		bool D3DGraphics::DrawTexture(D3DResource^ txt, RectangleF rect, float rotation)
		{
			if (Device == IntPtr::Zero)
				return false;
			if (!txt)
				return false;
			if (txt->Handle == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawTexture(this, Device, txt, rect, rotation, Color::White);
		}
		bool D3DGraphics::DrawTexture(D3DResource^ txt, RectangleF rect)
		{
			if (Device == IntPtr::Zero)
				return false;
			if (!txt)
				return false;
			if (txt->Handle == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawTexture(this, Device, txt, rect, 0.0F, Color::White);
		}

		bool D3DGraphics::DrawString(D3DResource^ fontResource, String^ text, Drawing::Rectangle rect, eD3DFontDrawFlags drawFlags, Color color)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawString(this, Device, fontResource, text, rect, drawFlags, color);
		}
		bool D3DGraphics::DrawString(D3DResource^ fontResource, String^ text, Point pos, Color color)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawString(this, Device, fontResource, text, pos, color);
		}
		bool D3DGraphics::DrawString(D3DResource^ fontResource, String^ text, int x, int y, Color color)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawString(this, Device, fontResource, text, Point(x, y), color);
		}

		bool D3DGraphics::DrawString(String^ text, Drawing::Rectangle rect, eD3DFontDrawFlags drawFlags, Color color)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawString(this, Device, nullptr, text, rect, drawFlags, color);
		}
		bool D3DGraphics::DrawString(String^ text, Point pos, Color color)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawString(this, Device, nullptr, text, pos, color);
		}
		bool D3DGraphics::DrawString(String^ text, int x, int y, Color color)
		{
			if (Device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawString(this, Device, nullptr, text, Point(x, y), color);
		}

	}
}