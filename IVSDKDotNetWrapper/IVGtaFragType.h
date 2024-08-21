#pragma once

namespace IVSDKDotNet
{
	public ref class IVGtaFragType
	{
	public:
		property IVRmcDrawable^ Drawable
		{
		public:
			IVRmcDrawable^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGtaFragType, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeGtaFragType->m_pDrawable, nullptr);
				return gcnew IVRmcDrawable(NativeGtaFragType->m_pDrawable);
			}
			void set(IVRmcDrawable^ value)
			{
				NULLPTR_CHECK(NativeGtaFragType);
				NULLPTR_CHECK(value);
				NativeGtaFragType->m_pDrawable = value->NativeRmcDrawable;
			}
		}
		property IVPhArchetypeGta^ Archetype
		{
		public:
			IVPhArchetypeGta^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGtaFragType, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeGtaFragType->m_pArchetype, nullptr);
				return gcnew IVPhArchetypeGta(NativeGtaFragType->m_pArchetype);
			}
			void set(IVPhArchetypeGta^ value)
			{
				NULLPTR_CHECK(NativeGtaFragType);
				NULLPTR_CHECK(value);
				NativeGtaFragType->m_pArchetype = value->NativePhArchetypeGta;
			}
		}

	public:
		static IVGtaFragType^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

	internal:
		IVGtaFragType(gtaFragType* nativePtr);

	internal:
		gtaFragType* NativeGtaFragType;
	};
}