#include "pch.h"
#include "CVectors.h"

namespace IVSDKDotNet {

	CVector::CVector(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	CVector2D::CVector2D(float x, float y)
	{
		X = x;
		Y = y;
	}

	CVector_pad::CVector_pad(unsigned int flags, float x, float y, float z) 
	{
		Flags = flags;
		X = x;
		Y = y;
		Z = z;
	}

}