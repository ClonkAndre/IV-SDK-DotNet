#include "pch.h"
#include "IVMatrix.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVMatrix::IVMatrix()
	{
		// Create new matrix from 4 vectors
		CMatrix* m = new CMatrix();

		m_bManuallyCreated = true;
		NativeMatrix = m;
	}
	IVMatrix::IVMatrix(Vector3 right, Vector3 up, Vector3 at, Vector3 pos)
	{
		// Create new matrix from 4 vectors
		CMatrix* m = new CMatrix();
		m->right = Vector3ToCVectorPad(right);
		m->up = Vector3ToCVectorPad(up);
		m->at = Vector3ToCVectorPad(at);
		m->pos = Vector3ToCVectorPad(pos);

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
	D3DXMATRIX IVMatrix::ToD3DXMATRIX(IVMatrix^ m)
	{
		D3DXMATRIX result;

		result._11 = m->Right.X;
		result._12 = m->Right.Y;
		result._13 = m->Right.Z;
		result._14 = 0.0F;
		result._21 = m->Up.X;
		result._22 = m->Up.Y;
		result._23 = m->Up.Z;
		result._24 = 0.0F;
		result._31 = m->At.X;
		result._32 = m->At.Y;
		result._33 = m->At.Z;
		result._34 = 0.0F;
		result._41 = m->Pos.X;
		result._42 = m->Pos.Y;
		result._43 = m->Pos.Z;
		result._44 = 0.0F;

		return result;
	}
	IVMatrix^ IVMatrix::FromD3DXMATRIX(D3DXMATRIX m)
	{
		IVMatrix^ result = gcnew IVMatrix();

		result->Set(m._11, m._12, m._13,
			m._21, m._22, m._23,
			m._31, m._32, m._33,
			m._41, m._42, m._43);

		return result;
	}

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

	// Reset functions
	void IVMatrix::Identity3x3()
	{
		Right = Vector3(1.0F, 0.0F, 0.0F);
		Up = Vector3(0.0F, 1.0F, 0.0F);
		At = Vector3(0.0F, 0.0F, 1.0F);
	}
	void IVMatrix::Identity()
	{
		Identity3x3();
		Pos = Vector3::Zero;
	}
	void IVMatrix::Zero3x3()
	{
		Right = Vector3::Zero;
		Up = Vector3::Zero;
		At = Vector3::Zero;
	}
	void IVMatrix::Zero()
	{
		Zero3x3();
		Pos = Vector3::Zero;
	}
	void IVMatrix::Set3x3(IVMatrix^ m)
	{
		NULLPTR_CHECK(NativeMatrix);
		NULLPTR_CHECK(m);

		Right = m->Right;
		Up = m->Up;
		At = m->At;
	}
	void IVMatrix::Set(IVMatrix^ m)
	{
		NULLPTR_CHECK(NativeMatrix);
		NULLPTR_CHECK(m);
		
		Right = m->Right;
		Up = m->Up;
		At = m->At;
		Pos = m->Pos;
	}
	void IVMatrix::Set(Vector3 newRight, Vector3 newUp, Vector3 newAt, Vector3 newPos)
	{
		Right = newRight;
		Up = newUp;
		At = newAt;
		Pos = newPos;
	}
	void IVMatrix::Set(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, float dx, float dy, float dz)
	{
		Right = Vector3(ax, ay, az);
		Up = Vector3(bx, by, bz);
		At = Vector3(cx, cy, cz);
		Pos = Vector3(dx, dy, dz);
	}

	// Rotate
	void IVMatrix::RotateX(float t)
	{
		IVMatrix^ mtx = gcnew IVMatrix();
		mtx->MakeRotateX(t);
		Dot3x3(mtx);
	}
	void IVMatrix::RotateY(float t)
	{
		IVMatrix^ mtx = gcnew IVMatrix();
		mtx->MakeRotateY(t);
		Dot3x3(mtx);
	}
	void IVMatrix::RotateZ(float t)
	{
		IVMatrix^ mtx = gcnew IVMatrix();
		mtx->MakeRotateZ(t);
		Dot3x3(mtx);
	}

	void IVMatrix::RotateLocalX(float t)
	{
		float cost = cosf(t);
		float sint = sinf(t);

		Vector3 rotatedB = Up;
		rotatedB = SomeVector3Extensions::Scale(rotatedB, cost);
		rotatedB = SomeVector3Extensions::AddScaled(rotatedB, At, sint);

		At = SomeVector3Extensions::Scale(At, cost);
		At = SomeVector3Extensions::SubtractScaled(At, Up, sint);
		Up = rotatedB;
	}
	void IVMatrix::RotateLocalY(float t)
	{
		float cost = cosf(t);
		float sint = sinf(t);

		Vector3 rotatedA = Right;
		rotatedA = SomeVector3Extensions::Scale(rotatedA, cost);
		rotatedA = SomeVector3Extensions::SubtractScaled(rotatedA, At, sint);

		At = SomeVector3Extensions::Scale(At, cost);
		At = SomeVector3Extensions::AddScaled(At, Right, sint);
		Right = rotatedA;
	}
	void IVMatrix::RotateLocalZ(float t)
	{
		float cost = cosf(t);
		float sint = sinf(t);

		Vector3 rotatedA = Right;
		rotatedA = SomeVector3Extensions::Scale(rotatedA, cost);
		rotatedA = SomeVector3Extensions::AddScaled(rotatedA, Up, sint);

		Up = SomeVector3Extensions::Scale(Up, cost);
		Up = SomeVector3Extensions::SubtractScaled(Up, Right, sint);
		Right = rotatedA;
	}

	void IVMatrix::MakeRotateX(float t)
	{
		float cost = cosf(t);
		float sint = sinf(t);

		Right = Vector3(1.0F, 0.0F, 0.0F);
		Up = Vector3(0.0F, cost, sint);
		At = Vector3(0.0F, -sint, cost);
	}
	void IVMatrix::MakeRotateY(float t)
	{
		float cost = cosf(t);
		float sint = sinf(t);

		Right = Vector3(cost, 0.0F, -sint);
		Up = Vector3(0.0F, 1.0F, 0.0F);
		At = Vector3(sint, 0.0F, cost);
	}
	void IVMatrix::MakeRotateZ(float t)
	{
		float cost = cosf(t);
		float sint = sinf(t);

		Right = Vector3(cost, sint, 0.0F);
		Up = Vector3(-sint, cost, 0.0F);
		At = Vector3(0.0F, 0.0F, 1.0F);
	}

	// Scaling
	void IVMatrix::Scale(float s)
	{
		Scale(s, s, s);
	}
	void IVMatrix::Scale(float x, float y, float z)
	{
		Right = Vector3(Right.X * x, Right.Y * y, Right.Z * z);
		Up = Vector3(Right.X * x, Right.Y * y, Right.Z * z);
		At = Vector3(Right.X * x, Right.Y * y, Right.Z * z);
	}

	void IVMatrix::ScaleFull(float s)
	{
		ScaleFull(s, s, s);
	}
	void IVMatrix::ScaleFull(float x, float y, float z)
	{
		Right = Vector3(Right.X * x, Right.Y * y, Right.Z * z);
		Up = Vector3(Up.X * x, Up.Y * y, Up.Z * z);
		At = Vector3(At.X * x, At.Y * y, At.Z * z);
		Pos = Vector3(Pos.X * x, Pos.Y * y, Pos.Z * z);
	}
	void IVMatrix::ScaleFull(Vector3 v)
	{
		ScaleFull(v.X, v.Y, v.Z);
	}

	void IVMatrix::MakeScale(float s)
	{
		Right = Vector3(s, 0.0F, 0.0F);
		Up = Vector3(0.0F, s, 0.0F);
		At = Vector3(0.0F, 0.0F, s);
	}
	void IVMatrix::MakeScale(float x, float y, float z)
	{
		Right = Vector3(x, 0.0F, 0.0F);
		Up = Vector3(0.0F, y, 0.0F);
		At = Vector3(0.0F, 0.0F, z);
	}
	void IVMatrix::MakeScale(Vector3 v)
	{
		MakeScale(v.X, v.Y, v.Z);
	}

	// Translation
	void IVMatrix::Translate(Vector3 v)
	{
		Pos = Vector3::Add(Pos, v);
	}
	void IVMatrix::Translate(float x, float y, float z)
	{
		Pos = Vector3(Pos.X + x, Pos.Y + y, Pos.Z + z);
	}

	void IVMatrix::MakeTranslate(Vector3 v)
	{
		Pos = v;
	}
	void IVMatrix::MakeTranslate(float x, float y, float z)
	{
		Pos = Vector3(x, y, z);
	}

	// Viewing
	void IVMatrix::LookDown(Vector3 dir, Vector3 up)
	{
		At = dir;
		At = Vector3::Normalize(At);
		Right = Vector3::Cross(up, At);
		Right = Vector3::Normalize(Right);
		Up = Vector3::Cross(At, Right);
	}
	void IVMatrix::LookAt(Vector3 to, Vector3 up)
	{
		LookDown(Vector3::Subtract(Pos, to), up);
	}
	void IVMatrix::LookAt(Vector3 from, Vector3 to, Vector3 up)
	{
		Pos = from;
		LookAt(to, up);
	}

	// Dot Products
	void IVMatrix::Dot3x3(IVMatrix^ m)
	{
		float ax = Right.X * m->Right.X + Right.Y * m->Up.X + Right.Z * m->At.X;
		float ay = Right.X * m->Right.Y + Right.Y * m->Up.Y + Right.Z * m->At.Y;
		float az = Right.X * m->Right.Z + Right.Y * m->Up.Z + Right.Z * m->At.Z;

		float bx = Up.X * m->Right.X + Up.Y * m->Up.X + Up.Z * m->At.X;
		float by = Up.X * m->Right.Y + Up.Y * m->Up.Y + Up.Z * m->At.Y;
		float bz = Up.X * m->Right.Z + Up.Y * m->Up.Z + Up.Z * m->At.Z;

		float cx = At.X * m->Right.X + At.Y * m->Up.X + At.Z * m->At.X;
		float cy = At.X * m->Right.Y + At.Y * m->Up.Y + At.Z * m->At.Y;
		float cz = At.X * m->Right.Z + At.Y * m->Up.Z + At.Z * m->At.Z;

		Right = Vector3(ax, ay, az);
		Up = Vector3(bx, by, bz);
		At = Vector3(cx, cy, cz);
	}

	Vector3 IVMatrix::GetPosition()
	{
		return Pos;
	}
	Vector3 IVMatrix::GetRight()
	{
		return Right;
	}
	Vector3 IVMatrix::GetForward()
	{
		return Up;
	}
	Vector3 IVMatrix::GetUp()
	{
		return At;
	}

}