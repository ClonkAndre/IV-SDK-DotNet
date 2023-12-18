#pragma once

namespace IVSDKDotNet
{
	public ref class IVBoundBox
	{
	public:
		property Vector3 Min
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeBoundBox, Vector3::Zero);
				CVector_pad v = NativeBoundBox->m_vecMin;
				return Vector3(v.x, v.y, v.z);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeBoundBox);

				CVector_pad v;
				v.x = value.X;
				v.y = value.Y;
				v.z = value.Z;
				NativeBoundBox->m_vecMin = v;
			}
		}
		property Vector3 Max
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeBoundBox, Vector3::Zero);
				CVector_pad v = NativeBoundBox->m_vecMax;
				return Vector3(v.x, v.y, v.z);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeBoundBox);

				CVector_pad v;
				v.x = value.X;
				v.y = value.Y;
				v.z = value.Z;
				NativeBoundBox->m_vecMax = v;
			}
		}

	internal:
		IVBoundBox(CBoundBox* nativePtr);

	internal:
		CBoundBox* NativeBoundBox;
	};
}