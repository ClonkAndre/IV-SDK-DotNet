#include "pch.h"
#include "Direct3D9.h"

namespace IVSDKDotNet {
	namespace Direct3D9 {

		// Constructor / Destructor
		D3DGraphics::D3DGraphics(Script^ createFor)
		{
			if (!createFor)
				throw gcnew NullReferenceException("'createFor' cannot be null.");

			m_createForScript = createFor;
			Scaling = eFontScaling::Pixel;
			Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateNewInstance(this, createFor);
		}
		D3DGraphics::~D3DGraphics()
		{
			Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DisposeInstance(m_createForScript);
			m_createForScript = nullptr;
		}

		// Creation functions
		D3DResult^ D3DGraphics::CreateD3D9Texture(IntPtr device, String^ filePath, Size size)
		{
			if (device == IntPtr::Zero)
				return gcnew D3DResult(gcnew Exception("device is not valid!"));

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateD3D9Texture(m_createForScript, device, filePath, size);
		}
		D3DResult^ D3DGraphics::CreateD3D9Texture(IntPtr device, String^ filePath)
		{
			if (device == IntPtr::Zero)
				return gcnew D3DResult(gcnew Exception("device is not valid!"));

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateD3D9Texture(m_createForScript, device, filePath, Size::Empty);
		}
		D3DResult^ D3DGraphics::CreateD3D9Texture(IntPtr device, array<Byte>^ data, Size size)
		{
			if (device == IntPtr::Zero)
				return gcnew D3DResult(gcnew Exception("device is not valid!"));

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateD3D9Texture(m_createForScript, device, data, size);
		}
		D3DResult^ D3DGraphics::CreateD3D9Texture(IntPtr device, array<Byte>^ data)
		{
			if (device == IntPtr::Zero)
				return gcnew D3DResult(gcnew Exception("device is not valid!"));

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateD3D9Texture(m_createForScript, device, data, Size::Empty);
		}
		Exception^ D3DGraphics::ReleaseD3D9Texture(D3DResource^ resource)
		{
			if (!resource)
				return gcnew NullReferenceException("resource cannot be null!");

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_ReleaseD3D9Texture(m_createForScript, resource);
		}

		D3DResult^ D3DGraphics::CreateD3D9Font(IntPtr device, D3DFontDescription fontDescription)
		{
			if (device == IntPtr::Zero)
				return gcnew D3DResult(gcnew Exception("device is not valid!"));

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_CreateD3D9Font(m_createForScript, device, fontDescription);
		}
		Exception^ D3DGraphics::ReleaseD3D9Font(D3DResource^ resource)
		{
			if (!resource)
				return gcnew NullReferenceException("resource cannot be null!");

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_ReleaseD3D9Font(m_createForScript, resource);
		}

		// Drawing functions
		bool D3DGraphics::DrawLines(IntPtr device, array<Vector2>^ vertices, Color color, bool antialias, int pattern, float patternScale, float thickness)
		{
			if (device == IntPtr::Zero)
				return false;
			if (vertices == nullptr)
				return false;
			if (vertices == Array::Empty<Vector2>())
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLines(this, device, vertices, color, antialias, pattern, patternScale, thickness);
		}
		bool D3DGraphics::DrawLines(IntPtr device, array<Vector2>^ vertices, Color color, bool antialias, float thickness)
		{
			if (device == IntPtr::Zero)
				return false;
			if (vertices == nullptr)
				return false;
			if (vertices == Array::Empty<Vector2>())
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLines(this, device, vertices, color, antialias, -1, 1.0F, thickness);
		}
		bool D3DGraphics::DrawLine(IntPtr device, Vector2 point1, Vector2 point2, Color color, bool antialias, int pattern, float patternScale, float thickness)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLine(this, device, point1, point2, color, antialias, pattern, patternScale, thickness);
		}
		bool D3DGraphics::DrawLine(IntPtr device, Vector2 point1, Vector2 point2, Color color, bool antialias, int pattern, float thickness)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLine(this, device, point1, point2, color, antialias, pattern, 1.0F, thickness);
		}
		bool D3DGraphics::DrawLine(IntPtr device, Vector2 point1, Vector2 point2, Color color, bool antialias, float thickness)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLine(this, device, point1, point2, color, antialias, -1, 1.0F, thickness);
		}
		bool D3DGraphics::DrawLine(IntPtr device, Vector2 point1, Vector2 point2, Color color, float thickness)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawLine(this, device, point1, point2, color, false, -1, 1.0F, thickness);
		}

		bool D3DGraphics::DrawCircle(IntPtr device, Vector2 pos, float radius, float rotation, eD3DCircleType type, bool smoothing, int resolution, Color color)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawCircle(this, device, pos, radius, rotation, type, smoothing, resolution, color);
		}
		bool D3DGraphics::DrawCircleFilled(IntPtr device, Vector2 pos, float radius, float rotation, eD3DCircleType type, bool smoothing, int resolution, Color color)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawCircleFilled(this, device, pos, radius, rotation, type, smoothing, resolution, color);
		}

		bool D3DGraphics::DrawBoxFilled(IntPtr device, Vector2 pos, SizeF size, Color color)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawBoxFilled(this, device, pos, size, color);
		}
		bool D3DGraphics::DrawBox(IntPtr device, Vector2 pos, SizeF size, float lineWidth, Color color)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawBox(this, device, pos, size, lineWidth, color);
		}
		bool D3DGraphics::DrawBoxBordered(IntPtr device, Vector2 pos, SizeF size, float borderWidth, Color color, Color borderColor)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawBoxBordered(this, device, pos, size, borderWidth, color, borderColor);
		}
		bool D3DGraphics::DrawBoxRounded(IntPtr device, Vector2 pos, SizeF size, float radius, bool smoothing, Color color, Color borderColor)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawBoxRounded(this, device, pos, size, radius, smoothing, color, borderColor);
		}

		bool D3DGraphics::DrawTexture(IntPtr device, D3DResource^ txt, RectangleF rect, float rotation, Color tint)
		{
			if (device == IntPtr::Zero)
				return false;
			if (!txt)
				return false;
			if (txt->Handle == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawTexture(this, device, txt, rect, rotation, tint);
		}
		bool D3DGraphics::DrawTexture(IntPtr device, D3DResource^ txt, RectangleF rect, Color tint)
		{
			if (device == IntPtr::Zero)
				return false;
			if (!txt)
				return false;
			if (txt->Handle == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawTexture(this, device, txt, rect, 0.0F, tint);
		}
		bool D3DGraphics::DrawTexture(IntPtr device, D3DResource^ txt, RectangleF rect, float rotation)
		{
			if (device == IntPtr::Zero)
				return false;
			if (!txt)
				return false;
			if (txt->Handle == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawTexture(this, device, txt, rect, rotation, Color::White);
		}
		bool D3DGraphics::DrawTexture(IntPtr device, D3DResource^ txt, RectangleF rect)
		{
			if (device == IntPtr::Zero)
				return false;
			if (!txt)
				return false;
			if (txt->Handle == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawTexture(this, device, txt, rect, 0.0F, Color::White);
		}

		bool D3DGraphics::DrawString(IntPtr device, D3DResource^ fontResource, String^ text, Point pos, Color color)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawString(this, device, fontResource, text, pos, color);
		}
		bool D3DGraphics::DrawString(IntPtr device, D3DResource^ fontResource, String^ text, int x, int y, Color color)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawString(this, device, fontResource, text, Point(x, y), color);
		}
		bool D3DGraphics::DrawString(IntPtr device, String^ text, Point pos, Color color)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawString(this, device, nullptr, text, pos, color);
		}
		bool D3DGraphics::DrawString(IntPtr device, String^ text, int x, int y, Color color)
		{
			if (device == IntPtr::Zero)
				return false;

			return Manager::ManagerScript::s_Instance->Direct3D9_Graphics_DrawString(this, device, nullptr, text, Point(x, y), color);
		}

	}
}