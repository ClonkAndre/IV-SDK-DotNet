#pragma once

namespace IVSDKDotNet
{
	public ref class IVBaseDC
	{
	public:
		/// <summary>
		/// Undocumented.
		/// </summary>
		void Add();

	internal:
		IVBaseDC(CBaseDC* nativePtr);

	internal:
		CBaseDC* NativeBaseDC;
	};
}