#pragma once

namespace IVSDKDotNet
{
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
		IVPed^ CreatePed(IVControlledByInfo info, int32_t model, IVMatrix mat, bool bNetwork, bool bUnk1);
		IVPed^ CreatePed(IVControlledByInfo info, int32_t model, Vector3 pos, bool bNetwork, bool bUnk1);
		int DeletePed(IVPed^ ped);

	internal:
		IVPedFactoryNY(CPedFactoryNY* nativePtr);

	internal:
		CPedFactoryNY* NativePedFactoryNY;
	};
}