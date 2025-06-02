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
		IVMatrix GetBoneMatrix(int boneID);
		/// <summary>
		/// Used for transform modifications e.g. popup lights, firetruck/apc cannon but 1:1 identical to the other function.
		/// </summary>
		/// <param name="boneID">The id of the bone to get the matrix from.</param>
		/// <returns>The bone matrix.</returns>
		IVMatrix GetBoneMatrix2(int boneID);

		/// <summary>
		/// Plays an animation on the dynamic entity and returns a pointer to the animation instance.
		/// </summary>
		/// <param name="animGroupId">The id of the animation group.</param>
		/// <param name="animId">The id of the specific animation within the group.</param>
		/// <param name="flags">Flags that control animation playback behavior.</param>
		/// <param name="unkMaybeBlendData">An unknown parameter, possibly related to blend data.</param>
		/// <param name="unk1">An unknown floating-point parameter. Mostly set to either 30.0f or 1000.0f.</param>
		/// <returns>A pointer to the animation instance created or played.</returns>
		IntPtr PlayAnimation(int animGroupId, int animId, int flags, int unkMaybeBlendData, float unk1)
		{
			return IntPtr(NativeDynEntity->PlayAnimation(animGroupId, animId, flags, unkMaybeBlendData, unk1));
		}

	internal:
		IVDynamicEntity(CDynamicEntity* nativePtr);

	internal:
		CDynamicEntity* NativeDynEntity;
	};
}