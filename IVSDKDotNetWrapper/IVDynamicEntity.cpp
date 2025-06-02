#include "pch.h"
#include "IVDynamicEntity.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVDynamicEntity::IVDynamicEntity(CDynamicEntity* nativePtr) : IVEntity(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeDynEntity = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVMatrix IVDynamicEntity::GetBoneMatrix(int boneID)
	{
		NULLPTR_CHECK_WITH_RETURN(NativeDynEntity, IVMatrix::Zero);

		CMatrix* matrix = NativeDynEntity->GetBoneMatrix(boneID);
		NULLPTR_CHECK_WITH_RETURN(matrix, IVMatrix::Zero);

		return IVMatrix(matrix);
	}
	IVMatrix IVDynamicEntity::GetBoneMatrix2(int boneID)
	{
		NULLPTR_CHECK_WITH_RETURN(NativeDynEntity, IVMatrix::Zero);

		CMatrix* matrix = NativeDynEntity->GetBoneMatrix2(boneID);
		NULLPTR_CHECK_WITH_RETURN(matrix, IVMatrix::Zero);

		return IVMatrix(matrix);
	}

}