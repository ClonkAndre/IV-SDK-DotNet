#pragma once

namespace IVSDKDotNet
{
	public ref class IVDrawCurvedWindowDC : IVBaseDC
	{
	public:
		// TODO: Test if this function works and if it only needs to be called once. if YES then create a delete method!!!!!!!!
		/// <summary>
		/// Draws a curved window on screen.
		/// </summary>
		/// <param name="pos">The position. Coordinates are ratio of screen (0-1).</param>
		/// <param name="size">The size of the window.</param>
		/// <param name="color">The color of the window. RGB is ignored, only alpha used.</param>
		/// <returns></returns>
		static IVDrawCurvedWindowDC^ Create(Vector2 pos, SizeF size, Color color);

	internal:
		IVDrawCurvedWindowDC(CDrawCurvedWindowDC* nativePtr);

	internal:
		CDrawCurvedWindowDC* NativeDC;
	};
}