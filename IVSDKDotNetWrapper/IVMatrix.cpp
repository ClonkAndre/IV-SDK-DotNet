#include "pch.h"
#include "IVMatrix.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVMatrix::IVMatrix(Vector3 right, Vector3 up, Vector3 at, Vector3 pos)
	{
		Right = right;
		Up = up;
		At = at;
		Pos = pos;
	}
	IVMatrix::IVMatrix(CMatrix* fromCMatrix)
	{
		Right = CVectorPadToVector(fromCMatrix->right);
		Up = CVectorPadToVector(fromCMatrix->up);
		At = CVectorPadToVector(fromCMatrix->at);
		Pos = CVectorPadToVector(fromCMatrix->pos);
	}
	IVMatrix::IVMatrix(CMatrix fromCMatrix)
	{
		Right = CVectorPadToVector(fromCMatrix.right);
		Up =	CVectorPadToVector(fromCMatrix.up);
		At =	CVectorPadToVector(fromCMatrix.at);
		Pos =	CVectorPadToVector(fromCMatrix.pos);
	}

	// - - - Methods / Functions - - -
	IVMatrix IVMatrix::Empty()
	{
		return IVMatrix(Vector3::Zero, Vector3::Zero, Vector3::Zero, Vector3::Zero);
	}
	CMatrix IVMatrix::ToCMatrix()
	{
		CMatrix matrix;
		matrix.right = VectorToCVectorPad(Right);
		matrix.up = VectorToCVectorPad(Up);
		matrix.at = VectorToCVectorPad(At);
		matrix.pos = VectorToCVectorPad(Pos);
		return matrix;
	}

}