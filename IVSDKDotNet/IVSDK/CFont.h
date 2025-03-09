class CFont
{
public:
	static void Initialise()
	{
		((void(__cdecl*)())(AddressSetter::Get("CFont", "Initialise")))();
	}
	static void SetScale(float x, float y)
	{
		((void(__cdecl*)(float, float))(AddressSetter::Get("CFont", "SetScale")))(x, y);
	}
	static void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		((void(__cdecl*)(uint8_t, uint8_t, uint8_t, uint8_t))(AddressSetter::Get("CFont", "SetColor")))(r, g, b, a);
	}
};