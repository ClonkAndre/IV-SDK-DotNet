#pragma once

namespace IVSDKDotNet {

	public ref class Helper
	{
	public:

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