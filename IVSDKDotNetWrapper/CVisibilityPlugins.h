#pragma once

class Native_CVisibilityPlugins
{
public:
	static float	GetPedLodDistanceHigh()					{ return AddressSetter::GetRef<float>(0xB36D8C, 0xB5C98C); }
	static void		SetPedLodDistanceHigh(float value)		{ AddressSetter::GetRef<float>(0xB36D8C, 0xB5C98C) = value; }

	static float	GetPedInCarLodDistanceHigh()			{ return AddressSetter::GetRef<float>(0xB36D90, 0xB5C990); }
	static void		SetPedInCarLodDistanceHigh(float value) { AddressSetter::GetRef<float>(0xB36D90, 0xB5C990) = value; }

	static float	GetPedLodDistanceMed()					{ return AddressSetter::GetRef<float>(0xB36D94, 0xB5C994); }
	static void		SetPedLodDistanceMed(float value)		{ AddressSetter::GetRef<float>(0xB36D94, 0xB5C994) = value; }

	static float	GetPedLodDistanceLow()					{ return AddressSetter::GetRef<float>(0xB36D98, 0xB5C998); }
	static void		SetPedLodDistanceLow(float value)		{ AddressSetter::GetRef<float>(0xB36D98, 0xB5C998) = value; }

	static float	GetPedLodDistanceVlow()					{ return AddressSetter::GetRef<float>(0xB36D9C, 0xB5C99C); }
	static void		SetPedLodDistanceVlow(float value)		{ AddressSetter::GetRef<float>(0xB36D9C, 0xB5C99C) = value; }

	// All non-mission peds change their modelindex to superlod past this distance
	static float	GetPedLodDistanceSlod()					{ return AddressSetter::GetRef<float>(0xB36DA0, 0xB5C9A0); }
	static void		SetPedLodDistanceSlod(float value)		{ AddressSetter::GetRef<float>(0xB36DA0, 0xB5C9A0) = value; }
	
	static float	GetCarLodDistanceHigh()					{ return AddressSetter::GetRef<float>(0xB33A44, 0xB4149C); }
	static void		SetCarLodDistanceHigh(float value)		{ AddressSetter::GetRef<float>(0xB33A44, 0xB4149C) = value; }

	static float	GetCarLodDistanceMed()					{ return AddressSetter::GetRef<float>(0xB33A48, 0xB414A0); }
	static void		SetCarLodDistanceMed(float value)		{ AddressSetter::GetRef<float>(0xB33A48, 0xB414A0) = value; }

	// platform:/textures
	static char*	GetStipplePath()						{ return AddressSetter::GetRef<char*>(0x3DB970, 0x55A920); }
	static void		SetStipplePath(char* value)				{ AddressSetter::GetRef<char*>(0x3DB970, 0x55A920) = value; }

};

namespace IVSDKDotNet {

	public ref class CVisibilityPlugins
	{
	public:

		/// <summary>
		/// Gets or sets the high ped lod distance.
		/// </summary>
		static property float PedLodDistanceHigh {
			public:
				float	get()				{ return Native_CVisibilityPlugins::GetPedLodDistanceHigh(); }
				void	set(float value)	{ Native_CVisibilityPlugins::SetPedLodDistanceHigh(value); }
		}

		/// <summary>
		/// Gets or sets the high ped lod in car distance.
		/// </summary>
		static property float PedInCarLodDistanceHigh {
			public:
				float	get()				{ return Native_CVisibilityPlugins::GetPedInCarLodDistanceHigh(); }
				void	set(float value)	{ Native_CVisibilityPlugins::SetPedInCarLodDistanceHigh(value); }
		}

		/// <summary>
		/// Gets or sets the medium ped lod distance.
		/// </summary>
		static property float PedLodDistanceMed {
			public:
				float	get()				{ return Native_CVisibilityPlugins::GetPedLodDistanceMed(); }
				void	set(float value)	{ Native_CVisibilityPlugins::SetPedLodDistanceMed(value); }
		}

		/// <summary>
		/// Gets or sets the low ped lod distance.
		/// </summary>
		static property float PedLodDistanceLow {
			public:
				float	get()				{ return Native_CVisibilityPlugins::GetPedLodDistanceLow(); }
				void	set(float value)	{ Native_CVisibilityPlugins::SetPedLodDistanceLow(value); }
		}

		/// <summary>
		/// Gets or sets the vlow ped lod distance.
		/// </summary>
		static property float PedLodDistanceVlow {
			public:
				float	get()				{ return Native_CVisibilityPlugins::GetPedLodDistanceVlow(); }
				void	set(float value)	{ Native_CVisibilityPlugins::SetPedLodDistanceVlow(value); }
		}

		/// <summary>
		/// Gets or sets the slod peds lod distance.
		/// All non-mission peds change their modelindex to superlod past this distance.
		/// </summary>
		static property float PedLodDistanceSlod {
			public:
				float	get()				{ return Native_CVisibilityPlugins::GetPedLodDistanceSlod(); }
				void	set(float value)	{ Native_CVisibilityPlugins::SetPedLodDistanceSlod(value); }
		}

		/// <summary>
		/// Gets or sets the high car lod distance.
		/// </summary>
		static property float CarLodDistanceHigh {
			public:
				float	get()				{ return Native_CVisibilityPlugins::GetCarLodDistanceHigh(); }
				void	set(float value)	{ Native_CVisibilityPlugins::SetCarLodDistanceHigh(value); }
		}

		/// <summary>
		/// Gets or sets the medium car lod distance.
		/// </summary>
		static property float CarLodDistanceMed {
			public:
				float	get()				{ return Native_CVisibilityPlugins::GetCarLodDistanceMed(); }
				void	set(float value)	{ Native_CVisibilityPlugins::SetCarLodDistanceMed(value); }
		}

		/// <summary>
		/// Gets or sets the path to platform:/textures
		/// </summary>
		static property String^ StipplePath {
			public:
				String^ get() { return gcnew String(Native_CVisibilityPlugins::GetStipplePath()); }
				void set(String^ value) {
					msclr::interop::marshal_context ctx;
					Native_CVisibilityPlugins::SetStipplePath((char*)ctx.marshal_as<const char*>(value));
				}
		}

	};

}