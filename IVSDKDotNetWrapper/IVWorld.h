#pragma once

namespace IVSDKDotNet
{
	public ref class IVWorld
	{
	public:
		static property array<IVPlayerInfo^>^ Players
		{
		public:
			array<IVPlayerInfo^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CWorld::Players, nullptr);

				array<IVPlayerInfo^>^ arr = gcnew array<IVPlayerInfo^>(32);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVPlayerInfo(CWorld::Players[i]);

				return arr;
			}
			void set(array<IVPlayerInfo^>^ value)
			{
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					CWorld::Players[i] = value[i]->NativePlayerInfo;
			}
		}
		static property int32_t PlayerInFocus
		{
		public:
			int32_t get()
			{
				return CWorld::PlayerInFocus;
			}
			void set(int32_t value)
			{
				CWorld::PlayerInFocus = value;
			}
		}

	public:
		static void Add(UIntPtr entity, bool bUnk);
		static void Remove(UIntPtr entity, bool bUnk);
		static void RemoveFallenPeds();
		static void RemoveFallenCars();
		static void RemoveFallenObjects();

		/// <summary>
		/// ProcessLineOfSight function with extended parameters.
		/// ZMenu uses IVWorld.ProcessLineOfSight(v, v2, 0, out IVLineOfSightResults ret, 142, 1, 0, 2, 4)
		/// </summary>
		/// <param name="source">Source position of the check.</param>
		/// <param name="target">Target position of the check.</param>
		/// <param name="pUnk">Unknown.</param>
		/// <param name="pResults">Returns the line of sight results if the function succeeded.</param>
		/// <param name="nFlags">Unknown.</param>
		/// <param name="nUnk1">Unknown.</param>
		/// <param name="nUnk2">Unknown.</param>
		/// <param name="nSeeThroughShootThrough">1 -> Do see through check. 2 -> Do shoot through check.</param>
		/// <param name="nUnk4">Unknown.</param>
		/// <returns>True if the processing was successful. False if not.</returns>
		static bool ProcessLineOfSight(Vector3 source, Vector3 target, UIntPtr pUnk, [OutAttribute] IVLineOfSightResults% pResults, uint32_t nFlags, uint32_t nUnk1, uint32_t nUnk2, uint32_t nSeeThroughShootThrough, uint32_t nUnk4);

		/// <summary>
		/// ProcessLineOfSight function with basic parameters.
		/// </summary>
		/// <param name="source">Source position of the check.</param>
		/// <param name="target">Target position of the check.</param>
		/// <param name="pResults">Returns the line of sight results if the function succeeded.</param>
		/// <param name="nSeeThroughShootThrough">1 -> Do see through check. 2 -> Do shoot through check</param>
		/// <returns>True if the processing was successful. False if not.</returns>
		static bool ProcessLineOfSight(Vector3 source, Vector3 target, [OutAttribute] IVLineOfSightResults% pResults, uint32_t nSeeThroughShootThrough);

	};
}