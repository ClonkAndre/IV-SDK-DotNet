#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedTasks
	{
	public:
		property array<IVTask^>^ PrimaryTasks
		{
		public:
			array<IVTask^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedTasks, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePedTasks->m_pPrimaryTasks, nullptr);

				array<IVTask^>^ arr = gcnew array<IVTask^>(5);

				for (int i = 0; i < arr->Length; i++)
				{
					CTask* task = NativePedTasks->m_pPrimaryTasks[i];

					if (!task)
						continue;

					arr[i] = gcnew IVTask(task);
				}

				return arr;
			}
			void set(array<IVTask^>^ value)
			{
				NULLPTR_CHECK(NativePedTasks);
				NULLPTR_CHECK(value);

				for (int i = 0; i < value->Length; i++)
				{
					IVTask^ task = value[i];

					if (!task)
						continue;

					NativePedTasks->m_pPrimaryTasks[i] = task->NativeBaseTask;
				}
			}
		}
		property array<IVTask^>^ SecondaryTasks
		{
		public:
			array<IVTask^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedTasks, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePedTasks->m_pSecondaryTasks, nullptr);

				array<IVTask^>^ arr = gcnew array<IVTask^>(6);

				for (int i = 0; i < arr->Length; i++)
				{
					CTask* task = NativePedTasks->m_pSecondaryTasks[i];

					if (!task)
						continue;

					arr[i] = gcnew IVTask(task);
				}

				return arr;
			}
			void set(array<IVTask^>^ value)
			{
				NULLPTR_CHECK(NativePedTasks);
				NULLPTR_CHECK(value);

				for (int i = 0; i < value->Length; i++)
				{
					IVTask^ task = value[i];

					if (!task)
						continue;

					NativePedTasks->m_pSecondaryTasks[i] = task->NativeBaseTask;
				}
			}
		}
		property array<IVTask^>^ MovementTasks
		{
		public:
			array<IVTask^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedTasks, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePedTasks->m_pMovementTasks, nullptr);

				array<IVTask^>^ arr = gcnew array<IVTask^>(3);

				for (int i = 0; i < arr->Length; i++)
				{
					CTask* task = NativePedTasks->m_pMovementTasks[i];

					if (!task)
						continue;

					arr[i] = gcnew IVTask(task);
				}

				return arr;
			}
			void set(array<IVTask^>^ value)
			{
				NULLPTR_CHECK(NativePedTasks);
				NULLPTR_CHECK(value);

				for (int i = 0; i < value->Length; i++)
				{
					IVTask^ task = value[i];

					if (!task)
						continue;

					NativePedTasks->m_pMovementTasks[i] = task->NativeBaseTask;
				}
			}
		}
		property UIntPtr OwnerPed
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedTasks, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePedTasks->m_pOwnerPed, UIntPtr::Zero);
				return UIntPtr(NativePedTasks->m_pOwnerPed);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				NativePedTasks->m_pOwnerPed = (CPed*)value.ToPointer();
			}
		}

	public:
		static IVPedTasks^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		void AssignTask(IVTask^ task, int unk1)
		{
			NULLPTR_CHECK(NativePedTasks);
			NativePedTasks->AssignTask(task == nullptr ? nullptr : task->NativeBaseTask, unk1);
		}

	internal:
		IVPedTasks(CPedTasks* nativePedTasks);

	internal:
		CPedTasks* NativePedTasks;

	};
}