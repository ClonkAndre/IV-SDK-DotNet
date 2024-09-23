#include "pch.h"
#include "IVPedTasks.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPedTasks::IVPedTasks(CPedTasks* nativePedTasks)
	{
		NULLPTR_CHECK(nativePedTasks);
		NativePedTasks = nativePedTasks;
	}

	// - - - Methods / Functions - - -
	IVPedTasks^ IVPedTasks::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPedTasks((CPedTasks*)ptr.ToPointer());
	}
	UIntPtr IVPedTasks::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePedTasks, UIntPtr::Zero);
		return UIntPtr(NativePedTasks);
	}

}