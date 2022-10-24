#pragma once

using namespace System::Numerics;

class Native_CVector
{
public:
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
	unsigned int flags; // ???
};

class Native_CSimpleTransform
{
public:
	Native_CVector m_vPosition;												// 000-00C
	float m_fHeading;														// 00C-010
};
VALIDATE_SIZE(Native_CSimpleTransform, 0x10);

class Native_CMatrix
{
public:
	Native_CVector_pad right;	// 00-10
	Native_CVector_pad up;		// 10-20
	Native_CVector_pad at;		// 20-30
	Native_CVector_pad pos;		// 30-40
};

class Native_CQuaternion
{
public:
	float x, y, z, w;
};