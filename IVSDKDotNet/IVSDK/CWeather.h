class CWeather
{
public:
	static inline auto& ForcedWeatherType = AddressSetter::GetRef<uint32_t>(0x1239500, 0xF11D64);
	static inline auto& OldWeatherType = AddressSetter::GetRef<uint32_t>(0x1239524, 0xF11D88);
	static inline auto& NewWeatherType = AddressSetter::GetRef<uint32_t>(0x12394D8, 0xF11D3C);
	static inline auto& InterpolationValue = AddressSetter::GetRef<float>(0x123950C, 0xF11D70);
	static inline auto& WeatherTypeInList = AddressSetter::GetRef<uint32_t>(0x1239530, 0xF11D94);
	static inline auto& Rain = AddressSetter::GetRef<float>(0x12394E4, 0xF11D48);

	static void ForceWeatherNow(int Type)
	{
		return ((void(__cdecl*)(int))(AddressSetter::Get(0x5E41D0, 0x5A0910)))(Type);
	}
};