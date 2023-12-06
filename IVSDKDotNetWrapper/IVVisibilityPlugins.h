#pragma once

namespace IVSDKDotNet
{
	public ref class IVVisibilityPlugins
	{
	public:
		static property float PedLodDistanceHigh
		{
		public:
			float get()
			{
				return CVisibilityPlugins::m_pedLodDistanceHigh;
			}
			void set(float value)
			{
				CVisibilityPlugins::m_pedLodDistanceHigh = value;
			}
		}
		static property float PedInCarLodDistanceHigh
		{
		public:
			float get()
			{
				return CVisibilityPlugins::m_pedInCarLodDistanceHigh;
			}
			void set(float value)
			{
				CVisibilityPlugins::m_pedInCarLodDistanceHigh = value;
			}
		}
		static property float PedLodDistanceMed
		{
		public:
			float get()
			{
				return CVisibilityPlugins::m_pedLodDistanceMed;
			}
			void set(float value)
			{
				CVisibilityPlugins::m_pedLodDistanceMed = value;
			}
		}
		static property float PedLodDistanceLow
		{
		public:
			float get()
			{
				return CVisibilityPlugins::m_pedLodDistanceLow;
			}
			void set(float value)
			{
				CVisibilityPlugins::m_pedLodDistanceLow = value;
			}
		}
		static property float PedLodDistanceVlow
		{
		public:
			float get()
			{
				return CVisibilityPlugins::m_pedLodDistanceVlow;
			}
			void set(float value)
			{
				CVisibilityPlugins::m_pedLodDistanceVlow = value;
			}
		}
		/// <summary>
		/// All non-mission peds change their modelindex to superlod past this distance.
		/// </summary>
		static property float PedLodDistanceSlod
		{
		public:
			float get()
			{
				return CVisibilityPlugins::m_pedLodDistanceSlod;
			}
			void set(float value)
			{
				CVisibilityPlugins::m_pedLodDistanceSlod = value;
			}
		}
		static property float CarLodDistanceHigh
		{
		public:
			float get()
			{
				return CVisibilityPlugins::m_carLodDistanceHigh;
			}
			void set(float value)
			{
				CVisibilityPlugins::m_carLodDistanceHigh = value;
			}
		}
		static property float CarLodDistanceMed
		{
		public:
			float get()
			{
				return CVisibilityPlugins::m_carLodDistanceMed;
			}
			void set(float value)
			{
				CVisibilityPlugins::m_carLodDistanceMed = value;
			}
		}

		/// <summary>
		/// Gets or sets the path to where the stipple.wtd file is located.
		/// Default: platform:/textures
		/// </summary>
		static property String^ StipplePath
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CVisibilityPlugins::sStipplePath, String::Empty);
				return gcnew String(CVisibilityPlugins::sStipplePath);
			}
			void set(String^ value)
			{
				CHECK_NULL_OR_WHITESPACE_STRING(value);
				
				msclr::interop::marshal_context ctx;
				CVisibilityPlugins::sStipplePath = (char*)ctx.marshal_as<const char*>(value);
			}
		}

	};
}