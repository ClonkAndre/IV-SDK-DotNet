#pragma once

namespace IVSDKDotNet
{
	public value struct IVUnkColliderParams2
	{
	public:
		property IVMatrix^ Matrix
		{
		public:
			IVMatrix^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeColliderParams2, IVMatrix::Empty());
				return gcnew IVMatrix(NativeColliderParams2->m_mMatrix);
			}
			void set(IVMatrix^ value)
			{
				NULLPTR_CHECK(NativeColliderParams2);
				NativeColliderParams2->m_mMatrix = value->ToCMatrix();
			}
		}
		property Vector3 Unk
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeColliderParams2, Vector3::Zero);
				return CVectorPadToVector(NativeColliderParams2->m_vUnk);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeColliderParams2);
				NativeColliderParams2->m_vUnk = VectorToCVectorPad(value);
			}
		}
		property Vector3 Unk2
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeColliderParams2, Vector3::Zero);
				return CVectorPadToVector(NativeColliderParams2->m_vUnk2);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeColliderParams2);
				NativeColliderParams2->m_vUnk2 = VectorToCVectorPad(value);
			}
		}
		property Vector3 Velocity
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeColliderParams2, Vector3::Zero);
				return CVectorPadToVector(NativeColliderParams2->m_vVelocity);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeColliderParams2);
				NativeColliderParams2->m_vVelocity = VectorToCVectorPad(value);
			}
		}
		property Vector3 RotationVelocity
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeColliderParams2, Vector3::Zero);
				return CVectorPadToVector(NativeColliderParams2->m_vRotationVelocity);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeColliderParams2);
				NativeColliderParams2->m_vRotationVelocity = VectorToCVectorPad(value);
			}
		}

	internal:
		IVUnkColliderParams2(rage::tUnkColliderParams2* nativePtr);

	internal:
		rage::tUnkColliderParams2* NativeColliderParams2;
	};

	public value struct IVUnkColliderParams
	{
	public:
		property IVUnkColliderParams2 Params2
		{
		public:
			IVUnkColliderParams2 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeColliderParams, IVUnkColliderParams2());
				NULLPTR_CHECK_WITH_RETURN(NativeColliderParams->m_pParams2, IVUnkColliderParams2());
				return IVUnkColliderParams2(NativeColliderParams->m_pParams2);
			}
			void set(IVUnkColliderParams2 value)
			{
				NULLPTR_CHECK(NativeColliderParams);
				NativeColliderParams->m_pParams2 = value.NativeColliderParams2;
			}
		}

	internal:
		IVUnkColliderParams(rage::tUnkColliderParams* nativePtr);

	internal:
		rage::tUnkColliderParams* NativeColliderParams;
	};
}