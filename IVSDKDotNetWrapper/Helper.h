#pragma once

namespace IVSDKDotNet {

	public ref class Helper
	{
	public:

		/// <summary> Checks if the specified key is pressed. </summary>
		/// <param name="Key">: The key to check if it's pressed.</param>
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
		/// Returns the length of a Vector2.
		/// </summary>
		static float Vector2Length(float X, float Y);

		static Keys RemoveRedundantKeyModifiers(Keys key);
		static String^ KeyCodeToUnicode(Keys key);

	};

}