#pragma once

namespace IVSDKDotNet
{
	public ref class IVObject : IVPhysical
	{
	public:
		/// <summary>
		/// This is set by SET_OBJECT_SCALE but unused.
		/// </summary>
		property float Scale
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeObject, 0.0F);
				return NativeObject->m_fScale;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeObject);
				NativeObject->m_fScale = value;
			}
		}

	public:
		static IVObject^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

	internal:
		IVObject(CObject* nativePtr);

	internal:
		CObject* NativeObject;
	};
}