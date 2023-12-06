#pragma once

namespace IVSDKDotNet
{
	public ref class IVPopulation
	{
	public:
		property int32_t NumCop
		{
		public:
			int32_t get()
			{
				return CPopulation::ms_nNumCop;
			}
			void set(int32_t value)
			{
				CPopulation::ms_nNumCop = value;
			}
		}
		property int32_t NumEmergency
		{
		public:
			int32_t get()
			{
				return CPopulation::ms_nNumEmergency;
			}
			void set(int32_t value)
			{
				CPopulation::ms_nNumEmergency = value;
			}
		}
		property int32_t AllRandomPedsThisType
		{
		public:
			int32_t get()
			{
				return CPopulation::m_AllRandomPedsThisType;
			}
			void set(int32_t value)
			{
				CPopulation::m_AllRandomPedsThisType = value;
			}
		}

		property float PedDensityMultiplier
		{
		public:
			float get()
			{
				return CPopulation::PedDensityMultiplier;
			}
			void set(float value)
			{
				CPopulation::PedDensityMultiplier = value;
			}
		}
		property float ScenarioPedDensityMultiplier
		{
		public:
			float get()
			{
				return CPopulation::ScenarioPedDensityMultiplier;
			}
			void set(float value)
			{
				CPopulation::ScenarioPedDensityMultiplier = value;
			}
		}
		property float ScenarioPedDensityMultiplier2
		{
		public:
			float get()
			{
				return CPopulation::ScenarioPedDensityMultiplier2;
			}
			void set(float value)
			{
				CPopulation::ScenarioPedDensityMultiplier2 = value;
			}
		}

	public:
		static void Initialise();
		static void RemovePed(IVPed^ pPed, bool unk);
	};
}