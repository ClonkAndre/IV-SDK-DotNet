#include "pch.h"
#include "Helper.h"

namespace IVSDKDotNet {

	bool Helper::IsKeyPressedAsync(Keys key)
	{
		return (GetAsyncKeyState((int)key) & 0x8000) != 0;
	}

	bool Helper::StringToBoolean(String^ Input, bool DefaultValue)
	{
		if (String::IsNullOrWhiteSpace(Input))
			return DefaultValue;

		Input = Input->ToLower();
		if (Input == "true")  return true;
		if (Input == "false") return false;
		if (Input == "yes")   return true;
		if (Input == "no")    return false;
		if (Input == "on")    return true;
		if (Input == "off")   return false;
		if (Input == "1")     return true;
		if (Input == "0")     return false;
		return DefaultValue;
	}

	String^ Helper::ToHex(int Input, int Digits)
	{
		return Input.ToString("X" + Digits.ToString());
	}
	String^ Helper::ToHex(int Input)
	{
		return ToHex(Input, 8);
	}
	String^ Helper::ToShortestHex(int Input)
	{
		if (Input < 0) return ToHex(Input, 8);
		if (Input < 256) return ToHex(Input, 2);
		if (Input < 65536) return ToHex(Input, 4);
		if (Input < 16777216) return ToHex(Input, 6);
		return ToHex(Input, 8);
	}
	int Helper::HexToInteger(String^ hex)
	{
		return Convert::ToInt32(hex, 16);
	}

	float Helper::RadianToDegree(float radians)
	{
		return radians * float(180.0 / System::Math::PI);
	}
	float Helper::RadianToDegree(double radians)
	{
		return float(radians * (180.0 / System::Math::PI));
	}
	float Helper::DegreeToRadian(float degrees)
	{
		return degrees * float(System::Math::PI / 180.0);
	}

	Vector3 Helper::GetPositionInFrontOfEntity(Vector3 entityPos, Vector3 entityDir, float multiplier)
	{
		return Vector3::Add(entityPos, Vector3::Multiply(entityDir, multiplier));
	}

	Vector3 Helper::HeadingToDirection(float heading)
	{
		float h = heading * (float)(Math::PI / 180);
		return Vector3((float)-Math::Sin(h), (float)Math::Cos(h), 0.0F);
	}

	float Helper::Vector2Length(float X, float Y)
	{
		return (float)System::Math::Sqrt((X * X) + (Y * Y));
	}

	Keys Helper::RemoveRedundantKeyModifiers(Keys key)
	{
		switch (key & Keys::KeyCode) {
			case Keys::ShiftKey:
			case Keys::LShiftKey:
			case Keys::RShiftKey:
				return key & ~Keys::Shift;
			case Keys::ControlKey:
			case Keys::LControlKey:
			case Keys::RControlKey:
				return key & ~Keys::Control;
			case Keys::Menu:
			case Keys::LMenu:
			case Keys::RMenu:
				return key & ~Keys::Alt;
		}
		return key;
	}
	String^ Helper::KeyCodeToUnicode(Keys key)
	{
		BYTE keyState[256] = {0};
		bool keyboardStateStatus = GetKeyboardState(keyState);

		if (!keyboardStateStatus)
			return String::Empty;

		UINT virtualKeyCode = (UINT)key;
		UINT scanCode = MapVirtualKey(virtualKeyCode, 0);
		HKL inputLocaleIdentifier = GetKeyboardLayout(0);

		WCHAR keyBuffer[5] = {0};
		int result = ToUnicodeEx(virtualKeyCode, scanCode, keyState, keyBuffer, 4, 0, inputLocaleIdentifier);

		switch (result) {
			case 1: return gcnew String(keyBuffer);
			case 2:
			case 3:
			case 4:
				keyBuffer[result] = 0;

				break;
		}

		return String::Empty;
	}

}