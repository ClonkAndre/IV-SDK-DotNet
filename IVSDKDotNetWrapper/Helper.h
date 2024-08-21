#pragma once

namespace IVSDKDotNet
{
	public ref class Helper
	{
	public:

		// Some code in here is from the ScriptHookDotNet source. Credits goes to HazardX!

		ref class Drawing
		{
		public:
			static float Helper::Drawing::ConvertUnitsToPixelX(float unitsX, float resolutionWidth);
			static float Helper::Drawing::ConvertUnitsToPixelY(float unitsY, float resolutionHeight);

			static float Helper::Drawing::ConvertPixelToUnitsX(float pixelX, float resolutionWidth);
			static float Helper::Drawing::ConvertPixelToUnitsY(float pixelY, float resolutionHeight);

			static float Helper::Drawing::ConvertFontToUnits(float fontSize);
			static float Helper::Drawing::ConvertFontToPixelX(float fontSize, float resolutionWidth);
			static float Helper::Drawing::ConvertFontToPixelY(float fontSize, float resolutionHeight);

			static float Helper::Drawing::ConvertUnitsToFont(float units);
			static float Helper::Drawing::ConvertPixelToFontX(float pixel, float resolutionWidth);
			static float Helper::Drawing::ConvertPixelToFontY(float pixel, float resolutionHeight);

			static float Helper::Drawing::ConvertX(float value, float resolutionWidth,	IVSDKDotNet::Enums::eFontScaling sourceScaling, IVSDKDotNet::Enums::eFontScaling targetScaling);
			static float Helper::Drawing::ConvertY(float value, float resolutionHeight, IVSDKDotNet::Enums::eFontScaling sourceScaling, IVSDKDotNet::Enums::eFontScaling targetScaling);

			static float Helper::Drawing::ToPixelX(float value, float resolutionWidth,	IVSDKDotNet::Enums::eFontScaling sourceScaling);
			static float Helper::Drawing::ToPixelY(float value, float resolutionHeight, IVSDKDotNet::Enums::eFontScaling sourceScaling);

			static RectangleF	Helper::Drawing::Convert(RectangleF rect,	float resolutionWidth, float resolutionHeight, IVSDKDotNet::Enums::eFontScaling sourceScaling, IVSDKDotNet::Enums::eFontScaling targetScaling);
			static PointF		Helper::Drawing::Convert(PointF pt,			float resolutionWidth, float resolutionHeight, IVSDKDotNet::Enums::eFontScaling sourceScaling, IVSDKDotNet::Enums::eFontScaling targetScaling);
			static SizeF		Helper::Drawing::Convert(SizeF sz,			float resolutionWidth, float resolutionHeight, IVSDKDotNet::Enums::eFontScaling sourceScaling, IVSDKDotNet::Enums::eFontScaling targetScaling);

			static System::Drawing::Rectangle	Helper::Drawing::ConvertToPixel(RectangleF rect,	float resolutionWidth, float resolutionHeight, IVSDKDotNet::Enums::eFontScaling sourceScaling);
			static RectangleF					Helper::Drawing::ConvertToPixelF(RectangleF rect,	float resolutionWidth, float resolutionHeight, IVSDKDotNet::Enums::eFontScaling sourceScaling);
			static Vector3						Helper::Drawing::ConvertToPixel(Vector3 pos,		float resolutionWidth, float resolutionHeight, IVSDKDotNet::Enums::eFontScaling sourceScaling);
		};

		/// <summary>
		/// Checks if the specified key is pressed.
		/// </summary>
		/// <param name="key">: The key to check if it's pressed.</param>
		/// <returns>True if the key is pressed, otherwise false.</returns>
		static bool IsKeyPressedAsync(Keys key);

		/// <summary>
		/// Tries to convert the string to a boolean.
		/// </summary>
		/// <param name="Input">The given string.</param>
		/// <param name="DefaultValue">If the conversion fails, use this value.</param>
		/// <returns>The converted value.</returns>
		static bool StringToBoolean(String^ Input, bool DefaultValue);

		static String^ ToHex(int Input, int Digits);
		static String^ ToHex(int Input);
		static String^ ToShortestHex(int Input);
		static int HexToInteger(String^ hex);

		static float RadianToDegree(float radians);
		static float RadianToDegree(double radians);
		static float DegreeToRadian(float degrees);
		static float DirectionToHeading(Vector3 dir);

		/// <summary>
		/// Gets the position in front of the given position based on the direction.
		/// </summary>
		/// <param name="entityPos">The current position.</param>
		/// <param name="entityDir">The current direction.</param>
		/// <param name="multiplier">The distance of the in front position.</param>
		/// <returns>The position in front of the given position.</returns>
		static Vector3 GetPositionInFrontOfEntity(Vector3 entityPos, Vector3 entityDir, float multiplier);

		static Vector3 HeadingToDirection(float heading);
		static Vector3 RotationToDirection(Vector3 rotation);

		static Keys RemoveRedundantKeyModifiers(Keys key);
		static String^ CleanPhoneNumber(String^ number);
		static String^ KeyCodeToUnicode(Keys key);

		static Random^ GetRandom();

		/// <summary>
		/// Gets if the given type is a numeric type.
		/// </summary>
		/// <param name="o">The type to check.</param>
		/// <returns>True if this type is a numeric type. Otherwise, false.</returns>
		static bool IsNumericType(Type^ o);

		/// <summary>
		/// Converts an object to a json string.
		/// </summary>
		/// <param name="obj">The object to be converted to a string.</param>
		/// <param name="useFormatting">Set this to true if you want to make the string look sexy. False, if you don't care about the style.</param>
		/// <returns>The object as a string representation.</returns>
		static String^ ConvertObjectToJsonString(Object^ obj, bool useFormatting);

		/// <summary>
		/// Converts a json string to a object of the target type.
		/// </summary>
		/// <typeparam name="T">The type the object should be converted to.</typeparam>
		/// <param name="str">The json string to convert to an object.</param>
		/// <returns>The object converted from a json string.</returns>
		generic <typename T>
		static T ConvertJsonStringToObject(String^ str);

	private:
		static Random^ m_rnd = gcnew Random();
	};
}