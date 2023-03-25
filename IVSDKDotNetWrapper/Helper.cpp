#include "pch.h"
#include "Helper.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ================================== Helper ===============================
	// =========================================================================
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
	Vector3 Helper::RotationToDirection(Vector3 rotation)
	{
		float rotZ = DegreeToRadian(rotation.Z);
		float rotX = DegreeToRadian(rotation.X);
		float multXY = Math::Abs((float)Math::Cos(rotX));
		Vector3 res;
		res.X = float(-Math::Sin(rotZ)) * multXY;
		res.Y = float(Math::Cos(rotZ)) * multXY;
		res.Z = float(Math::Sin(rotX));
		return res;
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

	// =========================================================================
	// ============================= Helper::Drawing ===========================
	// =========================================================================
	float Helper::Drawing::ConvertUnitsToPixelX(float unitsX, float resolutionWidth)
	{
		return (unitsX * resolutionWidth);
	}
	float Helper::Drawing::ConvertUnitsToPixelY(float unitsY, float resolutionHeight)
	{
		return (unitsY * resolutionHeight);
	}

	float Helper::Drawing::ConvertPixelToUnitsX(float pixelX, float resolutionWidth)
	{
		return (pixelX / resolutionWidth);
	}
	float Helper::Drawing::ConvertPixelToUnitsY(float pixelY, float resolutionHeight)
	{
		return (pixelY / resolutionHeight);
	}

	float Helper::Drawing::ConvertFontToUnits(float fontSize)
	{
		return (fontSize * 0.05f);
	}
	float Helper::Drawing::ConvertFontToPixelX(float fontSize, float resolutionWidth)
	{
		return Helper::Drawing::ConvertUnitsToPixelX(Helper::Drawing::ConvertFontToUnits(fontSize), resolutionWidth);
	}
	float Helper::Drawing::ConvertFontToPixelY(float fontSize, float resolutionHeight)
	{
		return Helper::Drawing::ConvertUnitsToPixelY(Helper::Drawing::ConvertFontToUnits(fontSize), resolutionHeight);
	}

	float Helper::Drawing::ConvertUnitsToFont(float units)
	{
		return (units / 0.05f);
	}
	float Helper::Drawing::ConvertPixelToFontX(float pixel, float resolutionWidth)
	{
		return Helper::Drawing::ConvertUnitsToFont(Helper::Drawing::ConvertPixelToUnitsX(pixel, resolutionWidth));
	}
	float Helper::Drawing::ConvertPixelToFontY(float pixel, float resolutionHeight)
	{
		return Helper::Drawing::ConvertUnitsToFont(Helper::Drawing::ConvertPixelToUnitsY(pixel, resolutionHeight));
	}

	float Helper::Drawing::ConvertX(float value, float resolutionWidth, eFontScaling sourceScaling, eFontScaling targetScaling)
	{
		if (sourceScaling == targetScaling) return value;

		switch (sourceScaling) {

			case eFontScaling::ScreenUnits:		switch (targetScaling) {
			case eFontScaling::FontSize:		return Helper::Drawing::ConvertUnitsToFont(value);
			case eFontScaling::Pixel:			return Helper::Drawing::ConvertUnitsToPixelX(value, resolutionWidth);
			default:							return value;
			}

			case eFontScaling::Pixel:			switch (targetScaling) {
			case eFontScaling::FontSize:		return Helper::Drawing::ConvertPixelToFontX(value, resolutionWidth);
			case eFontScaling::ScreenUnits:		return Helper::Drawing::ConvertPixelToUnitsX(value, resolutionWidth);
			default:							return value;
			}

			default:							switch (targetScaling) { // FontSize
			case eFontScaling::ScreenUnits:		return Helper::Drawing::ConvertFontToUnits(value);
			case eFontScaling::Pixel:			return Helper::Drawing::ConvertFontToPixelX(value, resolutionWidth);
			default:							return value;
			}

		}
	}
	float Helper::Drawing::ConvertY(float value, float resolutionHeight, eFontScaling sourceScaling, eFontScaling targetScaling)
	{
		if (sourceScaling == targetScaling) return value;

		switch (sourceScaling) {
				case eFontScaling::ScreenUnits: switch (targetScaling) {
				case eFontScaling::FontSize:	return Helper::Drawing::ConvertUnitsToFont(value);
				case eFontScaling::Pixel:		return Helper::Drawing::ConvertUnitsToPixelY(value, resolutionHeight);
				default:						return value;
			}

			case eFontScaling::Pixel:			switch (targetScaling) {
			case eFontScaling::FontSize:		return Helper::Drawing::ConvertPixelToFontY(value, resolutionHeight);
			case eFontScaling::ScreenUnits:		return Helper::Drawing::ConvertPixelToUnitsY(value, resolutionHeight);
			default:							return value;
			}

			default:							switch (targetScaling) { // FontSize
			case eFontScaling::ScreenUnits:		return Helper::Drawing::ConvertFontToUnits(value);
			case eFontScaling::Pixel:			return Helper::Drawing::ConvertFontToPixelY(value, resolutionHeight);
			default:							return value;
			}

		}
	}

	float Helper::Drawing::ToPixelX(float value, float resolutionWidth, eFontScaling sourceScaling)
	{
		return Helper::Drawing::ConvertX(value, resolutionWidth, sourceScaling, eFontScaling::Pixel);
	}
	float Helper::Drawing::ToPixelY(float value, float resolutionHeight, eFontScaling sourceScaling)
	{
		return Helper::Drawing::ConvertY(value, resolutionHeight, sourceScaling, eFontScaling::Pixel);
	}

	RectangleF	Helper::Drawing::Convert(RectangleF rect,	float resolutionWidth, float resolutionHeight, eFontScaling sourceScaling, eFontScaling targetScaling)
	{
		return RectangleF(
			Helper::Drawing::ConvertX(rect.Left,	resolutionWidth,	sourceScaling,	targetScaling),
			Helper::Drawing::ConvertY(rect.Top,		resolutionHeight,	sourceScaling,	targetScaling),
			Helper::Drawing::ConvertX(rect.Width,	resolutionWidth,	sourceScaling,	targetScaling),
			Helper::Drawing::ConvertY(rect.Height,	resolutionHeight,	sourceScaling,	targetScaling));
	}
	PointF		Helper::Drawing::Convert(PointF pt,			float resolutionWidth, float resolutionHeight, eFontScaling sourceScaling, eFontScaling targetScaling)
	{
		return PointF(Helper::Drawing::ConvertX(pt.X, resolutionWidth, sourceScaling, targetScaling), Helper::Drawing::ConvertY(pt.Y, resolutionHeight, sourceScaling, targetScaling));
	}
	SizeF		Helper::Drawing::Convert(SizeF sz,			float resolutionWidth, float resolutionHeight, eFontScaling sourceScaling, eFontScaling targetScaling)
	{
		return SizeF(Helper::Drawing::ConvertX(sz.Width, resolutionWidth, sourceScaling, targetScaling), Helper::Drawing::ConvertY(sz.Height, resolutionHeight, sourceScaling, targetScaling));
	}

	Drawing::Rectangle	Helper::Drawing::ConvertToPixel(RectangleF rect,	float resolutionWidth, float resolutionHeight, eFontScaling sourceScaling)
	{
		return System::Drawing::Rectangle(
			(int)Helper::Drawing::ConvertX(rect.Left,		resolutionWidth,	sourceScaling,	eFontScaling::Pixel),
			(int)Helper::Drawing::ConvertY(rect.Top,		resolutionHeight,	sourceScaling,	eFontScaling::Pixel),
			(int)Helper::Drawing::ConvertX(rect.Width,		resolutionWidth,	sourceScaling,	eFontScaling::Pixel),
			(int)Helper::Drawing::ConvertY(rect.Height,		resolutionHeight,	sourceScaling,	eFontScaling::Pixel));
	}
	RectangleF			Helper::Drawing::ConvertToPixelF(RectangleF rect,	float resolutionWidth, float resolutionHeight, eFontScaling sourceScaling)
	{
		return RectangleF(
			Helper::Drawing::ConvertX(rect.Left,	resolutionWidth,	sourceScaling,	eFontScaling::Pixel),
			Helper::Drawing::ConvertY(rect.Top,		resolutionHeight,	sourceScaling,	eFontScaling::Pixel),
			Helper::Drawing::ConvertX(rect.Width,	resolutionWidth,	sourceScaling,	eFontScaling::Pixel),
			Helper::Drawing::ConvertY(rect.Height,	resolutionHeight,	sourceScaling,	eFontScaling::Pixel));
	}
	Vector3				Helper::Drawing::ConvertToPixel(Vector3 pos,		float resolutionWidth, float resolutionHeight, eFontScaling sourceScaling)
	{
		return Vector3(Helper::Drawing::ConvertX(pos.X, resolutionWidth, sourceScaling, eFontScaling::Pixel), Helper::Drawing::ConvertY(pos.Y, resolutionHeight, sourceScaling, eFontScaling::Pixel), pos.Z);
	}

	// =========================================================================
	// =============================== Helper::JSON ============================
	// =========================================================================
	String^			Helper::JSON::ConvertObjectToJsonString(System::Object^ obj)
	{
		return Manager::ManagerScript::s_Instance->Helper_JSON_ConvertObjectToJsonString(obj);
	}
	System::Object^ Helper::JSON::ConvertJsonStringToObject(String^ str)
	{
		return Manager::ManagerScript::s_Instance->Helper_JSON_ConvertJsonStringToObject(str);
	}

}