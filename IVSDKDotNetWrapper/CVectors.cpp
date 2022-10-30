#include "pch.h"
#include "CVectors.h"

namespace IVSDKDotNet {

	GTAMatrix::GTAMatrix(Native_CMatrix* fromNativeMatrix)
	{
		right = Vector3(fromNativeMatrix->right.x, fromNativeMatrix->right.y, fromNativeMatrix->right.z);
		up = Vector3(fromNativeMatrix->up.x, fromNativeMatrix->up.y, fromNativeMatrix->up.z);
		at = Vector3(fromNativeMatrix->at.x, fromNativeMatrix->at.y, fromNativeMatrix->at.z);
		pos = Vector3(fromNativeMatrix->pos.x, fromNativeMatrix->pos.y, fromNativeMatrix->pos.z);
	}
	GTAMatrix::GTAMatrix(Vector3 vRight, Vector3 vUp, Vector3 vAt, Vector3 vPos)
	{
		right = vRight;
		up = vUp;
		at = vAt;
		pos = vPos;
	}

	CSimpleTransform::CSimpleTransform(Native_CSimpleTransform nativeSimpleTransform)
	{
		Position = Vector3(nativeSimpleTransform.m_vPosition.x, nativeSimpleTransform.m_vPosition.y, nativeSimpleTransform.m_vPosition.z);
		Heading = nativeSimpleTransform.m_fHeading;
	}
	CSimpleTransform::CSimpleTransform(Vector3 pos, float heading)
	{
		Position = pos;
		Heading = heading;
	}

}