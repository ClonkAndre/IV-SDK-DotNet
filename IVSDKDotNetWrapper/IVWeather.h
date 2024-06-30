#pragma once

namespace IVSDKDotNet
{
	public ref class IVWeather
	{
	public:
		static property int32_t ForcedWeatherType
		{
		public:
			int32_t get()
			{
				return CWeather::ForcedWeatherType;
			}
			void set(int32_t value)
			{
				CWeather::ForcedWeatherType = value;
			}
		}
		static property int32_t OldWeatherType
		{
		public:
			int32_t get()
			{
				return CWeather::OldWeatherType;
			}
			void set(int32_t value)
			{
				CWeather::OldWeatherType = value;
			}
		}
		static property int32_t NewWeatherType
		{
		public:
			int32_t get()
			{
				return CWeather::NewWeatherType;
			}
			void set(int32_t value)
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
		static property int32_t WeatherTypeInList
		{
		public:
			int32_t get()
			{
				return CWeather::WeatherTypeInList;
			}
			void set(int32_t value)
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
		static property float ForcedWind
		{
		public:
			float get()
			{
				return CWeather::ForcedWind;
			}
			void set(float value)
			{
				CWeather::ForcedWind = value;
			}
		}

	public:
		static void ForceWeatherNow(int type);
	};
}