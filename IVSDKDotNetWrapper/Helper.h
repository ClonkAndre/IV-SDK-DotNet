#pragma once

namespace IVSDKDotNet {

	public ref class Helper
	{
	public:

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

		ref class JSON
		{
		public:
			static String^ ConvertObjectToJsonString(System::Object^ obj);
			static System::Object^ ConvertJsonStringToObject(String^ str);
		};

		/// <summary> Checks if the specified key is pressed. </summary>
		/// <param name="key">: The key to check if it's pressed.</param>
		/// <returns>True if the key is pressed, otherwise false.</returns>
		static bool IsKeyPressedAsync(Keys key);

		static bool StringToBoolean(String^ Input, bool DefaultValue);

		static String^ ToHex(int Input, int Digits);
		static String^ ToHex(int Input);
		static String^ ToShortestHex(int Input);
		static int HexToInteger(String^ hex);

		static float RadianToDegree(float radians);
		static float RadianToDegree(double radians);
		static float DegreeToRadian(float degrees);

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

		/// <summary>
		/// Returns the length of the given Vector2 values.
		/// </summary>
		/// <param name="X">The Vector2 X.</param>
		/// <param name="Y">The Vector2 Y.</param>
		/// <returns>The length of the given Vector2 values.</returns>
		static float Vector2Length(float X, float Y);

		static Keys RemoveRedundantKeyModifiers(Keys key);
		static String^ KeyCodeToUnicode(Keys key);

	};

}