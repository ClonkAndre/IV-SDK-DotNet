#pragma once

namespace IVSDKDotNet
{
	public ref class IVDrawRectDC : IVBaseDC
	{
	public:
		// TODO: Test if this function works and if it only needs to be called once. if YES then create a delete method!!!!!!!!
		
		/// <summary>
		/// Draws a rectangle on screen. Also works in main menu.
		/// </summary>
		/// <param name="rect">The rectangle. Coordinates are in pixels.</param>
		/// <param name="color">The color of the rectangle.</param>
		/// <returns></returns>
		static IVDrawRectDC^ Create(RectangleF rect, Color color);

	internal:
		IVDrawRectDC(CDrawRectDC* nativePtr);

	internal:
		CDrawRectDC* NativeDC;
	};
}