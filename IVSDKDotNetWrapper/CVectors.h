#pragma once

class Native_CVector
{
public:
	Native_CVector()
	{
		x = 0.0F;
		y = 0.0F;
		z = 0.0F;
	}
	Native_CVector(float vX, float vY, float vZ)
	{
		x = vX;
		y = vY;
		z = vZ;
	}

	float x, y, z;
};
class Native_CVector2D
{
public:
	float x, y;
};

class Native_CVector_pad : public Native_CVector
{
public:
	Native_CVector_pad()
	{
		flags = 0;
	}
	Native_CVector_pad(unsigned int flag, float vX, float vY, float vZ) : Native_CVector(vX, vY, vZ)
	{
		flags = flag;
	}

	unsigned int flags; // ???
};

class Native_CSimpleTransform
{
public:
	Native_CSimpleTransform(float x, float y, float z, float heading)
	{
		m_vPosition = Native_CVector(x, y, z);
		m_fHeading = heading;
	}
	Native_CSimpleTransform();

	Native_CVector m_vPosition;												// 000-00C
	float m_fHeading;														// 00C-010
};
VALIDATE_SIZE(Native_CSimpleTransform, 0x10);

class Native_CMatrix
{
public:
	Native_CMatrix(Vector3 vRight, Vector3 vUp, Vector3 vAt, Vector3 vPos)
	{
		right = Native_CVector_pad(0, vRight.X, vRight.Y, vRight.Z);
		up = Native_CVector_pad(0, vUp.X, vUp.Y, vUp.Z);
		at = Native_CVector_pad(0, vAt.X, vAt.Y, vAt.Z);
		pos = Native_CVector_pad(0, vPos.X, vPos.Y, vPos.Z);
	}
	Native_CMatrix();

	Native_CVector_pad right;	// 00-10
	Native_CVector_pad up;		// 10-20
	Native_CVector_pad at;		// 20-30
	Native_CVector_pad pos;		// 30-40
};

class Native_CQuaternion
{
public:
	Native_CQuaternion()
	{
		x = 0.0F;
		y = 0.0F;
		z = 0.0F;
		w = 0.0F;
	}
	Native_CQuaternion(float vX, float vY, float vZ, float vW)
	{
		x = vX;
		y = vY;
		z = vZ;
		w = vW;
	}

	float x, y, z, w;
};

namespace IVSDKDotNet {

	public value class GTAMatrix
	{
	public:
		GTAMatrix(Native_CMatrix* fromNativeMatrix);
		GTAMatrix(Vector3 vRight, Vector3 vUp, Vector3 vAt, Vector3 vPos);

		virtual String^ ToString() override
		{
			return String::Format("<right: {0}, up: {1}, at: {2}, pos: {3}>", right.ToString(), up.ToString(), at.ToString(), pos.ToString());
		}

		Vector3 right;
		Vector3 up;
		Vector3 at;
		Vector3 pos;
	};

	public value class CSimpleTransform
	{
	public:
		CSimpleTransform(Native_CSimpleTransform nativeSimpleTransform);
		CSimpleTransform(Vector3 pos, float heading);

		virtual String^ ToString() override
		{
			return String::Format("<X: {0}, Y: {1}, Z: {2}, H: {3}>", Position.X.ToString(), Position.Y.ToString(), Position.Z.ToString(), Heading.ToString());
		}

		Vector3 Position;
		float Heading;
	};

}