#pragma once

namespace IVSDKDotNet
{
	public ref class IVMatrix
	{
	public:
		property Vector3 Right
		{
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeMatrix, Vector3::Zero);
				return CVectorPadToVector(NativeMatrix->right);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeMatrix);
				NativeMatrix->right = VectorToCVectorPad(value);
			}
		}
		property Vector3 Up
		{
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeMatrix, Vector3::Zero);
				return CVectorPadToVector(NativeMatrix->up);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeMatrix);
				NativeMatrix->up = VectorToCVectorPad(value);
			}
		}
		property Vector3 At
		{
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeMatrix, Vector3::Zero);
				return CVectorPadToVector(NativeMatrix->at);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeMatrix);
				NativeMatrix->at = VectorToCVectorPad(value);
			}
		}
		property Vector3 Pos
		{
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeMatrix, Vector3::Zero);
				return CVectorPadToVector(NativeMatrix->pos);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeMatrix);
				NativeMatrix->pos = VectorToCVectorPad(value);
			}
		}

	public:
		//void Set(Vector3 right, Vector3 up, Vector3 at, Vector3 pos);

		/// <summary>
		/// Sets the values of all four fields in this IVMatrix to the values of the fields inside the given matrix.
		/// </summary>
		/// <param name="matrix">The matrix to set all values of the fields in this IVMatrix to.</param>
		void SetFrom(IVMatrix^ matrix);

		void Add(Vector3 right, Vector3 up, Vector3 at, Vector3 pos);
		void Add(IVMatrix^ matrix);

		void Subtract(Vector3 right, Vector3 up, Vector3 at, Vector3 pos);
		void Subtract(IVMatrix^ matrix);

	public:
		IVMatrix(Vector3 right, Vector3 up, Vector3 at, Vector3 pos);
		!IVMatrix();

	internal:
		IVMatrix(CMatrix* nativePtr);

	internal:
		static IVMatrix^ Empty();

	internal:
		CMatrix* NativeMatrix;

	private:
		bool m_bManuallyCreated;

	};
}