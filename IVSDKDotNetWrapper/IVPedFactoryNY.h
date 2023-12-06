#pragma once

namespace IVSDKDotNet
{
	public value struct IVSpawnData
	{
	public:
		property uint8_t Flag1
		{
		public:
			uint8_t get()
			{
				return m_nFlag1;
			}
			void set(uint8_t value)
			{
				m_nFlag1 = value;
			}
		}
		property uint8_t Flag2
		{
		public:
			uint8_t get()
			{
				return m_nFlag2;
			}
			void set(uint8_t value)
			{
				m_nFlag2 = value;
			}
		}

	public:
		IVSpawnData(uint8_t flag1, uint8_t flag2);

	public:
		/// <summary>
		/// Returns the default IVSpawnData object with both flags set to 0.
		/// </summary>
		/// <returns>The the default IVSpawnData object.</returns>
		static IVSpawnData Default();

	internal:
		uint8_t m_nFlag1;
		uint8_t m_nFlag2;
	};

	public ref class IVPedFactoryNY
	{
	public:
		static property IVPedFactoryNY^ ThePedFactory
		{
		public:
			IVPedFactoryNY^ get()
			{
				CPedFactoryNY* ptr = PedFactory;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
				return gcnew IVPedFactoryNY(ptr);
			}
		}

	public:
		IVPed^ CreatePed(IVSpawnData pSpawnData, int32_t model, IVMatrix^ mat, bool bNetwork, bool bUnk1);

	internal:
		IVPedFactoryNY(CPedFactoryNY* nativePtr);

	internal:
		CPedFactoryNY* NativePedFactoryNY;
	};
}