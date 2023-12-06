#pragma once

namespace IVSDKDotNet
{
	public value struct IVMatrix
	{
	public:
		IVMatrix(Vector3 right, Vector3 up, Vector3 at, Vector3 pos);

		static IVMatrix Empty();

	public:
		Vector3 Right;
		Vector3 Up;
		Vector3 At;
		Vector3 Pos;

	internal:
		IVMatrix(CMatrix* fromCMatrix);
		IVMatrix(CMatrix fromCMatrix);

	internal:
		CMatrix ToCMatrix();

	};
}