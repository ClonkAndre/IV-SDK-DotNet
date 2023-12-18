#pragma once

namespace IVSDKDotNet
{
	public ref class IVWeather
	{
	public:
		static property uint32_t ForcedWeatherType
		{
		public:
			uint32_t get()
			{
				return CWeather::ForcedWeatherType;
			}
			void set(uint32_t value)
			{
				CWeather::ForcedWeatherType = value;
			}
		}
		static property uint32_t OldWeatherType
		{
		public:
			uint32_t get()
			{
				return CWeather::OldWeatherType;
			}
			void set(uint32_t value)
			{
				CWeather::OldWeatherType = value;
			}
		}
		static property uint32_t NewWeatherType
		{
		public:
			uint32_t get()
			{
				return CWeather::NewWeatherType;
			}
			void set(uint32_t value)
			{
				CWeather::NewWeatherType = value;
			}
		}
		static property float InterpolationValue
		{
		public:
			float get()
			{
				return CWeather::InterpolationValue;
			}
			void set(float value)
			{
				CWeather::InterpolationValue = value;
			}
		}
		static property uint32_t WeatherTypeInList
		{
		public:
			uint32_t get()
			{
				return CWeather::WeatherTypeInList;
			}
			void set(uint32_t value)
			{
				CWeather::WeatherTypeInList = value;
			}
		}
		static property float Rain
		{
		public:
			float get()
			{
				return CWeather::Rain;
			}
			void set(float value)
			{
				CWeather::Rain = value;
			}
		}

	public:
		static void ForceWeatherNow(int type);
	};
}