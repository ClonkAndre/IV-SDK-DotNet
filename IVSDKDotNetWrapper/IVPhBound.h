#pragma once

namespace IVSDKDotNet
{
	public ref class IVPhBound
	{
	internal:
		IVPhBound(rage::phBound* nativePtr);

	internal:
		rage::phBound* NativeBound;
	};

	public ref class IVPhBoundComposite : IVPhBound
	{
	internal:
		IVPhBoundComposite(rage::phBoundComposite* nativePtr);

	internal:
		rage::phBoundComposite* NativeBoundComposite;
	};
}