#pragma once

namespace IVSDKDotNet
{
	public ref class IVPhArchetypeGta
	{
	public:
		property IVPhBound^ Bounds
		{
		public:
			IVPhBound^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhArchetypeGta, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePhArchetypeGta->m_pBounds, nullptr);
				return gcnew IVPhBound(NativePhArchetypeGta->m_pBounds);
			}
			void set(IVPhBound^ value)
			{
				NULLPTR_CHECK(NativePhArchetypeGta);
				NULLPTR_CHECK(value);
				NativePhArchetypeGta->m_pBounds = value->NativeBound;
			}
		}
		property float Mass
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhArchetypeGta, 0.0F);
				return NativePhArchetypeGta->m_fMass;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePhArchetypeGta);
				NativePhArchetypeGta->m_fMass = value;
			}
		}
		property float MaxSpeed
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhArchetypeGta, 0.0F);
				return NativePhArchetypeGta->m_fMaxSpeed;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePhArchetypeGta);
				NativePhArchetypeGta->m_fMaxSpeed = value;
			}
		}

	internal:
		IVPhArchetypeGta(phArchetypeGta* nativePtr);

	internal:
		phArchetypeGta* NativePhArchetypeGta;
	};
}