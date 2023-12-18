#include "pch.h"
#include "IVDrawRectDC.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVDrawRectDC::IVDrawRectDC(CDrawRectDC* nativePtr) : IVBaseDC(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeDC = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVDrawRectDC^ IVDrawRectDC::Create(RectangleF rect, Color color)
	{
		CRect* cRect = new CRect();
		cRect->left = rect.X;
		cRect->right = rect.Right;
		cRect->top = rect.Y;
		cRect->bottom = rect.Bottom;

		CRGBA c = CRGBA();
		c.r = color.R;
		c.g = color.G;
		c.b = color.B;
		c.a = color.A;

		CDrawRectDC* dc = &CDrawRectDC(cRect, c);

		if (!dc)
		{
			delete cRect;
			return nullptr;
		}

		return gcnew IVDrawRectDC(dc);
	}

}