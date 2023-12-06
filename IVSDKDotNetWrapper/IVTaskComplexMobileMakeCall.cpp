#include "pch.h"
#include "IVTaskComplexMobileMakeCall.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVTaskComplexMobileMakeCall::IVTaskComplexMobileMakeCall(CTaskComplexMobileMakeCall* nativePtr) : IVTaskComplex(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeTask = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVTaskComplexMobileMakeCall^ IVTaskComplexMobileMakeCall::Create(String^ speechLine, bool bUnk1, bool bUnk2)
	{
		CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(speechLine, nullptr);

		msclr::interop::marshal_context ctx;
		CTaskComplexMobileMakeCall* ptr = new CTaskComplexMobileMakeCall((char*)ctx.marshal_as<const char*>(speechLine), bUnk1, bUnk2);
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

		return gcnew IVTaskComplexMobileMakeCall(ptr);
	}

}