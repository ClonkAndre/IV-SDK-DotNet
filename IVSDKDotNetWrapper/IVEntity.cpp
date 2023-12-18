#include "pch.h"
#include "IVEntity.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVObjectDrawable::IVObjectDrawable(tObjectDrawable* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeObjDrawable = nativePtr;
	}
	IVEntity::IVEntity(CEntity* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeEntity = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVEntity^ IVEntity::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVEntity((CEntity*)ptr.ToPointer());
	}
	UIntPtr IVEntity::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativeEntity, UIntPtr::Zero);
		return UIntPtr(NativeEntity);
	}

	void IVEntity::Teleport(IVMatrix^ mat, bool bDontUpdatePhysicsMatrix, bool bImmediately)
	{
		NULLPTR_CHECK(NativeEntity);
		NULLPTR_CHECK(mat);
		NULLPTR_CHECK(mat->NativeMatrix);
		NativeEntity->Teleport(mat->NativeMatrix, bDontUpdatePhysicsMatrix, bImmediately);
	}
	void IVEntity::Teleport(Vector3 v, bool bDontUpdatePhysicsMatrix, bool bImmediately)
	{
		NULLPTR_CHECK(NativeEntity);

		CVector* vec = new CVector();
		vec->x = v.X;
		vec->y = v.Y;
		vec->z = v.Z;

		NativeEntity->Teleport(vec, bDontUpdatePhysicsMatrix, bImmediately);

		delete vec;
	}

	void IVEntity::PreRender(int nUnk, int nUnk2, char alpha, int nUnkNeg1)
	{
		NULLPTR_CHECK(NativeEntity);
		NativeEntity->PreRender(nUnk, nUnk2, alpha, nUnkNeg1);
	}

}