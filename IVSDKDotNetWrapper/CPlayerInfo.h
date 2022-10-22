#pragma once

class Native_CPlayerInfo
{
public:

	static uint32_t FindPlayerPed()
	{
		return (uint32_t)((uint32_t* (__cdecl*)())(AddressSetter::Get(0x417F40, 0x3CD230)))();
	}
	static uint32_t FindPlayerVehicle()
	{
		return (uint32_t)((uint32_t* (__cdecl*)())(AddressSetter::Get(0x478890, 0x4B52F0)))();
	}

};

namespace IVSDKDotNet {

	public ref class CPlayerInfo
	{
	public:

		static uint32_t FindPlayerPed();
		static uint32_t FindPlayerVehicle();

	};


}
