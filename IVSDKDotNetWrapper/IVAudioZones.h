#pragma once

namespace IVSDKDotNet
{
	public ref class IVAudioZones
	{
	public:
		static property uint32_t NumSpheres
		{
		public:
			uint32_t get()
			{
				return CAudioZones::m_NumSpheres;
			}
			void set(uint32_t value)
			{
				CAudioZones::m_NumSpheres = value;
			}
		}
		static property int32_t ActiveSpheres
		{
		public:
			int32_t get()
			{
				throw gcnew NotImplementedException();
				return 0;
			}
			void set(int32_t value)
			{
				throw gcnew NotImplementedException();
			}
		}
		static property uint32_t NumActiveSpheres
		{
		public:
			uint32_t get()
			{
				return CAudioZones::m_NumActiveSpheres;
			}
			void set(uint32_t value)
			{
				CAudioZones::m_NumActiveSpheres = value;
			}
		}
		static property uint32_t NumBoxes
		{
		public:
			uint32_t get()
			{
				return CAudioZones::m_NumBoxes;
			}
			void set(uint32_t value)
			{
				CAudioZones::m_NumBoxes = value;
			}
		}
		static property int32_t ActiveBoxes
		{
		public:
			int32_t get()
			{
				throw gcnew NotImplementedException();
				return 0;
			}
			void set(int32_t value)
			{
				throw gcnew NotImplementedException();
			}
		}
		static property uint32_t NumActiveBoxes
		{
		public:
			uint32_t get()
			{
				return CAudioZones::m_NumActiveBoxes;
			}
			void set(uint32_t value)
			{
				CAudioZones::m_NumActiveBoxes = value;
			}
		}

	public:
		static void Update(bool bForceUpdate, Vector3 TestCoors);
	};
}