#pragma once

namespace IVSDKDotNet
{
	public value struct IVViewportData
	{
	public:
		property IVMatrix^ ProjectionMatrix
		{
		public:
			IVMatrix^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeData, IVMatrix::Empty());
				return gcnew IVMatrix(&NativeData->m_mProjectionMatrix);
			}
			void set(IVMatrix^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(value->NativeMatrix);
				NativeData->m_mProjectionMatrix = *value->NativeMatrix;
			}
		}
		property RectangleF Rect
		{
		public:
			RectangleF get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeData, RectangleF());
				return RectangleF(NativeData->m_fLeft, NativeData->m_fTop, NativeData->m_fRight, NativeData->m_fBottom);
			}
			void set(RectangleF value)
			{
				NativeData->m_fLeft = value.X;
				NativeData->m_fTop = value.Y;
				NativeData->m_fRight = value.Right;
				NativeData->m_fBottom = value.Bottom;
			}
		}
		property Size Resolution
		{
		public:
			Size get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeData, Size::Empty);
				return Size(Convert::ToInt32(NativeData->m_nResX), Convert::ToInt32(NativeData->m_nResY));
			}
			void set(Size value)
			{
				NativeData->m_nResX = Convert::ToUInt32(value.Width);
				NativeData->m_nResY = Convert::ToUInt32(value.Height);
			}
		}

		property float FOV
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeData, 0.0F);
				return NativeData->m_fFOV;
			}
			void set(float value)
			{
				NativeData->m_fFOV = value;
			}
		}
		property float Aspect
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeData, 0.0F);
				return NativeData->m_fAspect;
			}
			void set(float value)
			{
				NativeData->m_fAspect = value;
			}
		}
		property float NearClip
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeData, 0.0F);
				return NativeData->m_fNearClip;
			}
			void set(float value)
			{
				NativeData->m_fNearClip = value;
			}
		}
		property float FarClip
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeData, 0.0F);
				return NativeData->m_fFarClip;
			}
			void set(float value)
			{
				NativeData->m_fFarClip = value;
			}
		}

		property PointF Scale
		{
		public:
			PointF get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeData, PointF::Empty);
				return PointF(NativeData->m_fScaleX, NativeData->m_fScaleY);
			}
			void set(PointF value)
			{
				NativeData->m_fScaleX = value.X;
				NativeData->m_fScaleY = value.Y;
			}
		}

	internal:
		IVViewportData(tViewportData* nativePtr);

	internal:
		tViewportData* NativeData;
	};
}