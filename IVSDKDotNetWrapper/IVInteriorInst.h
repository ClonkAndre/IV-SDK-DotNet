#pragma once

namespace IVSDKDotNet
{
	public ref class IVInteriorInst : IVBuilding
	{
	internal:
		IVInteriorInst(CInteriorInst* nativePtr);

	internal:
		CInteriorInst* NaiveInteriorInst;
	};
}