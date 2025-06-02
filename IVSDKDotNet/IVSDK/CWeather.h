class CWeather
{
public:
	static inline auto& ForcedWeatherType = AddressSetter::GetRef<int32_t>("CWeather", "ForcedWeatherType");
	static inline auto& OldWeatherType = AddressSetter::GetRef<int32_t>("CWeather", "OldWeatherType");
	static inline auto& NewWeatherType = AddressSetter::GetRef<int32_t>("CWeather", "NewWeatherType");
	static inline auto& InterpolationValue = AddressSetter::GetRef<float>("CWeather", "InterpolationValue");
	static inline auto& WeatherTypeInList = AddressSetter::GetRef<int32_t>("CWeather", "WeatherTypeInList");
	static inline auto& Rain = AddressSetter::GetRef<float>("CWeather", "Rain");
	static inline auto& ForcedWind = AddressSetter::GetRef<float>("CWeather", "ForcedWind");

	static void ForceWeatherNow(int Type)
	{
		return ((void(__cdecl*)(int))(AddressSetter::Get("CWeather", "ForceWeatherNow")))(Type);
	}
};