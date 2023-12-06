#pragma once

namespace IVSDKDotNet
{
	public ref class IVBuilding : public IVEntity
	{
	public:
		void ReplaceWithNewModel(int32_t index);

	internal:
		IVBuilding(CBuilding* nativePtr);

	internal:
		CBuilding* NativeBuilding;
	};
}