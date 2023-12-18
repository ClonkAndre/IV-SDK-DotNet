#pragma once

namespace IVSDKDotNet
{
	public ref class IVDynamicEntity : public IVEntity
	{
	public:
		/// <summary>
		/// Undocumented.
		/// </summary>
		property UIntPtr Anim
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeDynEntity, UIntPtr::Zero);
				return UIntPtr(NativeDynEntity->m_pAnim);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				NativeDynEntity->m_pAnim = (uint32_t*)value.ToPointer();
			}
		}

	public:
		/// <summary>
		/// Used for reading bone positions e.g. seat locations.
		/// </summary>
		/// <param name="boneID">The id of the bone to get the matrix from.</param>
		/// <returns>The bone matrix.</returns>
		IVMatrix^ GetBoneMatrix(int boneID);
		/// <summary>
		/// Used for transform modifications e.g. popup lights, firetruck/apc cannon but 1:1 identical to the other function.
		/// </summary>
		/// <param name="boneID">The id of the bone to get the matrix from.</param>
		/// <returns>The bone matrix.</returns>
		IVMatrix^ GetBoneMatrix2(int boneID);

	internal:
		IVDynamicEntity(CDynamicEntity* nativePtr);

	internal:
		CDynamicEntity* NativeDynEntity;
	};
}