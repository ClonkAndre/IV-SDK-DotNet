#pragma once

namespace IVSDKDotNet
{
	public ref class IVCam
	{
	public:
		property IVMatrix Matrix
		{
		public:
			IVMatrix get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCam, IVMatrix::Zero);
				return IVMatrix(&NativeCam->m_mMatrix);
			}
			void set(IVMatrix value)
			{
				NULLPTR_CHECK(NativeCam);
				NativeCam->m_mMatrix = value.ToCMatrix();
			}
		}
		property float FOV
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCam, 0.0F);
				return NativeCam->m_fFOV;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeCam);
				NativeCam->m_fFOV = value;
			}
		}
		property float NearZ
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCam, 0.0F);
				return NativeCam->m_fNearZ;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeCam);
				NativeCam->m_fNearZ = value;
			}
		}
		property float FarZ
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCam, 0.0F);
				return NativeCam->m_fFarZ;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeCam);
				NativeCam->m_fFarZ = value;
			}
		}
		property float NearDOF
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCam, 0.0F);
				return NativeCam->m_fNearDOF;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeCam);
				NativeCam->m_fNearDOF = value;
			}
		}
		property float FarDOF
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCam, 0.0F);
				return NativeCam->m_fFarDOF;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeCam);
				NativeCam->m_fFarDOF = value;
			}
		}

	public:
		static IVCam^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

	public:
		IVCam^ GetCamOfType(int type, int unk);
		IVCam^ Activate();
		bool Process();

	internal:
		IVCam(CCam* nativePtr);

	internal:
		CCam* NativeCam;
	};
}