#pragma once

namespace IVSDKDotNet
{
	private ref class SomeVector3Extensions
	{
	public:
		static Vector3 Scale(Vector3 vec, float factor)
		{
			return vec * factor;
		}
		static Vector3 AddScaled(Vector3 vec, Vector3 vec2, float s)
		{
			return Vector3(vec.X += s * vec2.X, vec.Y += s * vec2.Y, vec.Z += s * vec2.Z);
		}
		static Vector3 SubtractScaled(Vector3 vec, Vector3 vec2, float s)
		{
			return Vector3(vec.X -= s * vec2.X, vec.Y -= s * vec2.Y, vec.Z -= s * vec2.Z);
		}
	};

	/// <summary>
	/// Represents a 3x4-matrix with 3 columns and 4 rows where the first 3 rows are used for orientation and the last for position.
	/// </summary>
	public ref class IVMatrix
	{
	public:
		/// <summary>A</summary>
		property Vector3 Right
		{
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeMatrix, Vector3::Zero);
				return CVectorPadToVector3(NativeMatrix->right);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeMatrix);
				NativeMatrix->right = Vector3ToCVectorPad(value);
			}
		}
		/// <summary>B</summary>
		property Vector3 Up
		{
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeMatrix, Vector3::Zero);
				return CVectorPadToVector3(NativeMatrix->up);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeMatrix);
				NativeMatrix->up = Vector3ToCVectorPad(value);
			}
		}
		/// <summary>C</summary>
		property Vector3 At
		{
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeMatrix, Vector3::Zero);
				return CVectorPadToVector3(NativeMatrix->at);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeMatrix);
				NativeMatrix->at = Vector3ToCVectorPad(value);
			}
		}
		/// <summary>D</summary>
		property Vector3 Pos
		{
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeMatrix, Vector3::Zero);
				return CVectorPadToVector3(NativeMatrix->pos);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeMatrix);
				NativeMatrix->pos = Vector3ToCVectorPad(value);
			}
		}

	internal:
		static D3DXMATRIX ToD3DXMATRIX(IVMatrix^ m);
		static IVMatrix^ FromD3DXMATRIX(D3DXMATRIX m);

	public:
		// TODO: REMOVE OLD STUFF AND REPLACE WITH NEW STUFF
		//void Set(Vector3 right, Vector3 up, Vector3 at, Vector3 pos);

		/// <summary>
		/// Sets the values of all four fields in this IVMatrix to the values of the fields inside the given matrix.
		/// </summary>
		/// <param name="matrix">The matrix to set all values of the fields in this IVMatrix to.</param>
		void SetFrom(IVMatrix^ matrix);

		void Add(Vector3 right, Vector3 up, Vector3 at, Vector3 pos);
		void Add(IVMatrix^ matrix);

		void Subtract(Vector3 right, Vector3 up, Vector3 at, Vector3 pos);
		void Subtract(IVMatrix^ matrix);

		// Reset functions
		/// <summary>
		/// Set the 3x3 part of the current matrix to the identity matrix.
		/// </summary>
		void Identity3x3();
		/// <summary>
		/// Set the current matrix to the identity matrix.
		/// </summary>
		void Identity();
		/// <summary>
		/// Zero the 3x3 part of the current matrix.
		/// </summary>
		void Zero3x3();
		/// <summary>
		/// Zero the current matrix (i.e. set all of its elements to zero).
		/// </summary>
		void Zero();
		/// <summary>
		/// Set the 3x3 part of the current matrix to the 3x3 part of another matrix.
		/// </summary>
		/// <param name="m">The matrix containing the 3x3 part to be copied.</param>
		void Set3x3(IVMatrix^ m);
		/// <summary>
		/// Set the value of the current matrix to the value of another matrix.
		/// </summary>
		/// <param name="m">The matrix containing the new value for the current matrix.</param>
		void Set(IVMatrix^ m);
		/// <summary>
		/// Set the elements of the current matrix to the given elements.
		/// </summary>
		/// <param name="newRight">New value for the right-vector of the current matrix.</param>
		/// <param name="newUp">New value for the up-vector of the current matrix.</param>
		/// <param name="newAt">New value for the at-vector of the current matrix.</param>
		/// <param name="newPos">Optional new value for the pos-vector of the current matrix; default is Vector3.Zero</param>
		void Set(Vector3 newRight, Vector3 newUp, Vector3 newAt, Vector3 newPos);
		/// <summary>
		/// Set the elements of the current matrix to the given elements.
		/// </summary>
		/// <param name="ax">The new value for the right-vector of the current matrix.</param>
		/// <param name="ay">The new value for the right-vector of the current matrix.</param>
		/// <param name="az">The new value for the right-vector of the current matrix.</param>
		/// <param name="bx">The new value for the up-vector of the current matrix.</param>
		/// <param name="by">The new value for the up-vector of the current matrix.</param>
		/// <param name="bz">The new value for the up-vector of the current matrix.</param>
		/// <param name="cx">The new value for the at-vector of the current matrix.</param>
		/// <param name="cy">The new value for the at-vector of the current matrix.</param>
		/// <param name="cz">The new value for the at-vector of the current matrix.</param>
		/// <param name="dx">The new value for the pos-vector of the current matrix. Default is 0.0f</param>
		/// <param name="dy">The new value for the pos-vector of the current matrix. Default is 0.0f</param>
		/// <param name="dz">The new value for the pos-vector of the current matrix. Default is 0.0f</param>
		void Set(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, float dx, float dy, float dz);

		// Rotate
		/// <summary>
		/// Rotate the 3x3 part of the current matrix, along the world's +X axis, by the given angle.
		/// </summary>
		/// <param name="t">The angle of rotation, in radians.</param>
		void RotateX(float t);
		/// <summary>
		/// Rotate the 3x3 part of the current matrix, along the world's +Y axis, by the given angle.
		/// </summary>
		/// <param name="t">The angle of rotation, in radians.</param>
		void RotateY(float t);
		/// <summary>
		/// Rotate the 3x3 part of the current matrix, along the world's +Z axis, by the given angle.
		/// </summary>
		/// <param name="t">The angle of rotation, in radians.</param>
		void RotateZ(float t);

		void RotateLocalX(float t);
		void RotateLocalY(float t);
		void RotateLocalZ(float t);

		/// <summary>
		/// Rotate the 3x3 part of the current matrix, along the world's +X axis, by the given angle.
		/// </summary>
		/// <param name="t">The angle of rotation, in radians.</param>
		void MakeRotateX(float t);
		/// <summary>
		/// Rotate the 3x3 part of the current matrix, along the world's +Y axis, by the given angle.
		/// </summary>
		/// <param name="t">The angle of rotation, in radians.</param>
		void MakeRotateY(float t);
		/// <summary>
		/// Rotate the 3x3 part of the current matrix, along the world's +Z axis, by the given angle.
		/// </summary>
		/// <param name="t">The angle of rotation, in radians.</param>
		void MakeRotateZ(float t);

		// Scaling
		/// <summary>
		/// Scale the 3x3 part of the current matrix by a given factor.
		/// </summary>
		/// <param name="s">The scaling factor for the matrix.</param>
		void Scale(float s);
		/// <summary>
		/// Scale the 3x3 part of the current matrix by three given factors.
		/// </summary>
		/// <param name="x">The x scaling factor for the matrix.</param>
		/// <param name="y">The y scaling factor for the matrix.</param>
		/// <param name="z">The z scaling factor for the matrix.</param>
		void Scale(float x, float y, float z);

		/// <summary>
		/// Scale the current matrix by a given factor.
		/// </summary>
		/// <param name="s">The scaling factor for the matrix.</param>
		void ScaleFull(float s);
		/// <summary>
		/// Scale the current matrix by three given factors.
		/// </summary>
		/// <param name="x">The x scaling factor for the matrix.</param>
		/// <param name="y">The y scaling factor for the matrix.</param>
		/// <param name="z">The z scaling factor for the matrix.</param>
		void ScaleFull(float x, float y, float z);
		/// <summary>
		/// Scale the current matrix by three given factors taken from a vector.
		/// </summary>
		/// <param name="v">The vector containing the three scaling factors for the matrix.</param>
		void ScaleFull(Vector3 v);

		/// <summary>
		/// Set the 3x3 part of the current matrix to a scaling matrix.
		/// </summary>
		/// <param name="s">The scaling factor for the matrix.</param>
		void MakeScale(float s);
		/// <summary>
		/// Set the 3x3 part of the current matrix to a scaling matrix.
		/// </summary>
		/// <param name="x">The x scaling factor for the matrix.</param>
		/// <param name="y">The y scaling factor for the matrix.</param>
		/// <param name="z">The z scaling factor for the matrix.</param>
		void MakeScale(float x, float y, float z);
		/// <summary>
		/// Set the 3x3 part of the current matrix to a scaling matrix.
		/// </summary>
		/// <param name="v">The vector containing the three scaling factors for the matrix.</param>
		void MakeScale(Vector3 v);

		// Translation
		/// <summary>
		/// Translate the position of the current matrix by a vector.
		/// </summary>
		/// <param name="v">The vector to translate by.</param>
		void Translate(Vector3 v);
		/// <summary>
		/// Translate the position of the current matrix by a vector.
		/// </summary>
		/// <param name="x">The x component to translate the position by.</param>
		/// <param name="y">The y component to translate the position by.</param>
		/// <param name="z">The z component to translate the position by.</param>
		void Translate(float x, float y, float z);

		/// <summary>
		/// Set the position of the current matrix by a vector.
		/// </summary>
		/// <param name="v">The vector to set the position of the matrix to.</param>
		void MakeTranslate(Vector3 v);
		/// <summary>
		/// Set the position of the current matrix.
		/// </summary>
		/// <param name="x">The x component to set the position of the matrix to.</param>
		/// <param name="y">The y component to set the position of the matrix to.</param>
		/// <param name="z">The z component to set the position of the matrix to.</param>
		void MakeTranslate(float x, float y, float z);

		// Viewing
		/// <summary>
		/// Set the current matrix to one that looks from the current position in the direction 'dir'.
		/// </summary>
		/// <param name="dir">The direction to look.</param>
		/// <param name="up">Usually Vector3.UnitY</param>
		void LookDown(Vector3 dir, Vector3 up);
		/// <summary>
		/// Set the current matrix to one that looks from the current position toward the point 'to'.
		/// </summary>
		/// <param name="to">The point to look towards.</param>
		/// <param name="up">Usually Vector3.UnitY</param>
		void LookAt(Vector3 to, Vector3 up);
		/// <summary>
		/// Set the current matrix to one that looks from the point 'from' toward the point 'to'.
		/// </summary>
		/// <param name="from">The point to look from.</param>
		/// <param name="to">The point to look towards.</param>
		void LookAt(Vector3 from, Vector3 to, Vector3 up);

		/// <summary>
		/// Transform the 3x3 part of the current matrix by the 3x3 part of another matrix.
		/// </summary>
		/// <param name="m">The matrix that transforms the current matrix.</param>
		void Dot3x3(IVMatrix^ m);

	public:
		Vector3 GetPosition();
		Vector3 GetRight();
		Vector3 GetForward();
		Vector3 GetUp();

	public:
		IVMatrix();
		IVMatrix(Vector3 right, Vector3 up, Vector3 at, Vector3 pos);
		!IVMatrix();

	internal:
		IVMatrix(CMatrix* nativePtr);

	internal:
		static IVMatrix^ Empty();

	internal:
		CMatrix* NativeMatrix;

	private:
		bool m_bManuallyCreated;

	};
}