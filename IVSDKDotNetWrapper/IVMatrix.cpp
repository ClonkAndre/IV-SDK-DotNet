#include "pch.h"
#include "IVMatrix.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVMatrix::IVMatrix(Vector3 right, Vector3 up, Vector3 at, Vector3 pos)
	{
		// Create new matrix from 4 vectors
		CMatrix* m = new CMatrix();
		m->right = VectorToCVectorPad(right);
		m->up = VectorToCVectorPad(up);
		m->at = VectorToCVectorPad(at);
		m->pos = VectorToCVectorPad(pos);

		m_bManuallyCreated = true;
		NativeMatrix = m;
	}
	IVMatrix::IVMatrix(CMatrix* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		m_bManuallyCreated = false;
		NativeMatrix = nativePtr;
	}
	IVMatrix::!IVMatrix()
	{
		if (m_bManuallyCreated)
		{
			if (NativeMatrix)
				delete NativeMatrix;
		}
	}

	// - - - Methods / Functions - - -
	IVMatrix^ IVMatrix::Empty()
	{
		return gcnew IVMatrix(nullptr);
	}
	void IVMatrix::SetFrom(IVMatrix^ matrix)
	{
		NULLPTR_CHECK(NativeMatrix);
		NULLPTR_CHECK(matrix);
		Right = matrix->Right;
		Up = matrix->Up;
		At = matrix->At;
		Pos = matrix->Pos;
	}

	void IVMatrix::Add(Vector3 right, Vector3 up, Vector3 at, Vector3 pos)
	{
		NULLPTR_CHECK(NativeMatrix);
		Right = Vector3::Add(Right, right);
		Up = Vector3::Add(Up, up);
		At = Vector3::Add(At, at);
		Pos = Vector3::Add(Pos, pos);
	}
	void IVMatrix::Add(IVMatrix^ matrix)
	{
		NULLPTR_CHECK(matrix);
		Add(matrix->Right, matrix->Up, matrix->At, matrix->Pos);
	}

	void IVMatrix::Subtract(Vector3 right, Vector3 up, Vector3 at, Vector3 pos)
	{
		NULLPTR_CHECK(NativeMatrix);
		Right = Vector3::Subtract(Right, right);
		Up = Vector3::Subtract(Up, up);
		At = Vector3::Subtract(At, at);
		Pos = Vector3::Subtract(Pos, pos);
	}
	void IVMatrix::Subtract(IVMatrix^ matrix)
	{
		NULLPTR_CHECK(matrix);
		Subtract(matrix->Right, matrix->Up, matrix->At, matrix->Pos);
	}

}