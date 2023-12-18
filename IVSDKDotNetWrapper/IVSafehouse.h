#pragma once

namespace IVSDKDotNet
{
	public value struct IVSafehouse
	{
	public:
		property Vector3 Position
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSafehouse, Vector3::Zero);

				CVector_pad v = NativeSafehouse->vPos;
				return Vector3(v.x, v.y, v.z);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeSafehouse);

				CVector_pad v;
				v.x = value.X;
				v.y = value.Y;
				v.z = value.Z;
				NativeSafehouse->vPos = v;
			}
		}
		property float Heading
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSafehouse, 0.0F);
				return NativeSafehouse->fHeading;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSafehouse);
				NativeSafehouse->fHeading = value;
			}
		}
		property String^ Name
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSafehouse, String::Empty);
				return gcnew String(NativeSafehouse->sName);
			}
		}
		property uint32_t WhenToUse
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSafehouse, 0);
				return NativeSafehouse->nWhenToUse;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeSafehouse);
				NativeSafehouse->nWhenToUse = value;
			}
		}
		property bool Enabled
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSafehouse, false);
				return NativeSafehouse->bEnabled;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeSafehouse);
				NativeSafehouse->bEnabled = value;
			}
		}

	internal:
		IVSafehouse(CRestart::tSafehouse* nativePtr);

	internal:
		CRestart::tSafehouse* NativeSafehouse;
	};
}