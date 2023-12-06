#pragma once

namespace IVSDKDotNet
{
	public ref class IVPhInstGta : public IVPhInst
	{
	public:
		property UIntPtr UnkImportant
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhInstGta, UIntPtr::Zero);
				return UIntPtr(NativePhInstGta->m_pUnkImportant);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePhInstGta);
				NativePhInstGta->m_pUnkImportant = (uint32_t*)value.ToPointer();
			}
		}
		property IVGtaFragType^ FragType
		{
		public:
			IVGtaFragType^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhInstGta, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePhInstGta->m_pFragType, nullptr);
				return gcnew IVGtaFragType(NativePhInstGta->m_pFragType);
			}
			void set(IVGtaFragType^ value)
			{
				NULLPTR_CHECK(NativePhInstGta);
				NULLPTR_CHECK(value);
				NativePhInstGta->m_pFragType = value->NativeGtaFragType;
			}
		}

	public:
		/// <summary>
		/// This is what's used to detach car parts, groupId is in the same order as groups are in the .oft file.
	    /// Use IVDoor.GroupID for vehicle doors, haven't found a way to see the rest of the bones, or anything for other entity types other than guessing.
		/// </summary>
		/// <param name="groupId">The fragment group id to detach.</param>
		/// <returns>The detached fragment group?</returns>
		IVPhInstGta^ DetachFragmentGroup(uint32_t groupId);

	internal:
		IVPhInstGta(phInstGta* nativePtr);

	internal:
		phInstGta* NativePhInstGta;
	};
}