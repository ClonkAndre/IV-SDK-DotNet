#include "pch.h"
#include "IVDrawCurvedWindowDC.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVDrawCurvedWindowDC::IVDrawCurvedWindowDC(CDrawCurvedWindowDC* nativePtr) : IVBaseDC(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeDC = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVDrawCurvedWindowDC^ IVDrawCurvedWindowDC::Create(Vector2 pos, SizeF size, Color color)
	{
		CVector2D* vec = new CVector2D();
		vec->x = pos.X;
		vec->y = pos.Y;

		CRGBA c = CRGBA();
		c.r = color.R;
		c.g = color.G;
		c.b = color.B;
		c.a = color.A;

		CDrawCurvedWindowDC* dc = &CDrawCurvedWindowDC(vec, size.Width, size.Height, c);
		
		if (!dc)
		{
			delete vec;
			return nullptr;
		}

		return gcnew IVDrawCurvedWindowDC(dc);
	}

}