#pragma once

namespace IVSDKDotNet
{
	public ref class IVStreaming
	{
	public:
		// <summary>
		// Use with: IVFiPackfile.FromPointer(...);
		// </summary>
		//static property UIntPtr PlayerPackfile
		//{
		//public:
		//	UIntPtr get()
		//	{
		//		NULLPTR_CHECK_WITH_RETURN(CStreaming::m_pPlayerPackfile, UIntPtr::Zero);
		//		return UIntPtr(CStreaming::m_pPlayerPackfile);
		//	}
		//	void set(UIntPtr value)
		//	{
		//		UINTPTR_ZERO_CHECK(value);
		//		CStreaming::m_pPlayerPackfile = (rage::fiPackfile*)value.ToPointer();
		//	}
		//}
		static property uint32_t PedModelBudget
		{
		public:
			uint32_t get()
			{
				return CStreaming::m_nPedModelBudget;
			}
			void set(uint32_t value)
			{
				CStreaming::m_nPedModelBudget = value;
			}
		}
		static property uint32_t VehicleModelBudget
		{
		public:
			uint32_t get()
			{
				return CStreaming::m_nVehicleModelBudget;
			}
			void set(uint32_t value)
			{
				CStreaming::m_nVehicleModelBudget = value;
			}
		}
		static property bool DisableStreaming
		{
		public:
			bool get()
			{
				return CStreaming::ms_disableStreaming;
			}
			void set(bool value)
			{
				CStreaming::ms_disableStreaming = value;
			}
		}

	public:
		static bool IsStreamingDisabled();
		/// <summary>
		/// Requests a model with the given hash. This is easier to use until 'RequestModel' is fully documented.
		/// </summary>
		/// <param name="nHash">The model hash to request.</param>
		/// <param name="pRunningThread">Undocumented.</param>
		static void ScriptRequestModel(int32_t nHash, UIntPtr pRunningThread);
		/// <summary>
		/// Requests a model with the given hash. This is easier to use until 'RequestModel' is fully documented.
		/// </summary>
		/// <param name="nHash">The model hash to request.</param>
		static void ScriptRequestModel(int32_t nHash);
		static void RequestModel(int32_t modelIndex, int32_t unk1, int32_t nFlags);
		static void LoadAllRequestedModels(bool priorityOnly);
		static void AddImageList(String^ fileName);

		/// <summary>
		/// Use with: IVFiPackfile.FromUIntPtr(...);
		/// </summary>
		static UIntPtr GetPlayerPackfile();
		static void ClosePlayerPackfile();
	};
}