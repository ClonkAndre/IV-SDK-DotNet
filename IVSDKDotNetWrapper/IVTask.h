#pragma once

namespace IVSDKDotNet
{
	public ref class IVTask
	{
	public:
		IVTask^ Clone()
		{
			if (!NativeBaseTask)
				return nullptr;

			CTask* task = NativeBaseTask->Clone();
			
			if (task)
				return gcnew IVTask(task);

			return nullptr;
		}

		/// <summary>
		/// Gets if this is a simple, or a complex task.
		/// </summary>
		/// <returns>true if this is a simple task. Otherwise, false for a complex task.</returns>
		bool IsSimple()
		{
			if (!NativeBaseTask)
				return false;

			return NativeBaseTask->IsSimple();
		}

		/// <summary>
		/// Gets the type of this Task. Check out the "eTask" enum for all types.
		/// </summary>
		/// <returns>The type of this Task.</returns>
		int GetTaskType()
		{
			if (!NativeBaseTask)
				return 0;

			return NativeBaseTask->GetType();
		}

	internal:
		IVTask(CTask* nativePtr);

	internal:
		CTask* NativeBaseTask;
	};

	public ref class IVTaskComplex : IVTask
	{
	internal:
		IVTaskComplex(CTaskComplex* nativePtr);

	internal:
		CTaskComplex* NativeComplexTask;
	};

	public ref class IVTaskSimple : IVTask
	{
	internal:
		IVTaskSimple(CTaskSimple* nativePtr);

	internal:
		CTaskSimple* NativeSimpleTask;
	};
}