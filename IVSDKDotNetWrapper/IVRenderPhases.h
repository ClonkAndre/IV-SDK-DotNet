#pragma once

namespace IVSDKDotNet
{
	public value struct IVRenderPhases
	{
	public:
		// TODO
		//property array<IVRenderPhases^>^ RenderPhases
		//{
		//public:
		//	array<IVRenderPhases^>^ get()
		//	{
		//		NULLPTR_CHECK_WITH_RETURN(NativeRenderPhases, nullptr);

		//		CRenderPhase** phases = NativeRenderPhases->m_aRenderPhases;
		//		NULLPTR_CHECK_WITH_RETURN(phases, nullptr);

		//		array<IVRenderPhases^>^ arr = gcnew array<IVRenderPhases^>(32);

		//		for (int i = 0; i < 32; i++)
		//			arr[i] = gcnew IVRenderPhases(phases[i]);

		//		return arr;
		//	}
		//	void set(array<IVRenderPhases^>^ value)
		//	{
		//		NULLPTR_CHECK(NativeRenderPhases);
		//		NULLPTR_CHECK(value);
		//		// TODO
		//	}
		//}

	public:
		static IVRenderPhases FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

	internal:
		IVRenderPhases(tRenderPhases* nativePtr);

	internal:
		tRenderPhases* NativeRenderPhases;
	};
}