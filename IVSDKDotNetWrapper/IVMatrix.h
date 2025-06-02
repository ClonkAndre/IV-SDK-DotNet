//
// Copyright (C) 2007-2010 SlimDX Group
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
// OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

// This is a modified version of the 4x4 matrix from SlimDX to fit within this project.

#pragma once

#include "pch.h"

namespace IVSDKDotNet
{
    /// <summary>
    /// Defines a 4x4 matrix.
    /// </summary>
    [System::Serializable]
    [System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential, Pack = 4)]
    public value struct IVMatrix : System::IEquatable<IVMatrix>, System::IFormattable
    {
    public:
        float M11; float M12; float M13; float M14; // right
        float M21; float M22; float M23; float M24; // up
        float M31; float M32; float M33; float M34; // at
        float M41; float M42; float M43; float M44; // pos

        property System::Numerics::Vector4 Row1
        {
            System::Numerics::Vector4 get()
            {
                return System::Numerics::Vector4(M11, M12, M13, M14);
            }
            void set(System::Numerics::Vector4 value)
            {
                M11 = value.X; M12 = value.Y; M13 = value.Z; M14 = value.W;
            }
        }
        property System::Numerics::Vector4 Row2
        {
            System::Numerics::Vector4 get()
            {
                return System::Numerics::Vector4(M21, M22, M23, M24);
            }
            void set(System::Numerics::Vector4 value)
            {
                M21 = value.X; M22 = value.Y; M23 = value.Z; M24 = value.W;
            }
        }
        property System::Numerics::Vector4 Row3
        {
            System::Numerics::Vector4 get()
            {
                return System::Numerics::Vector4(M31, M32, M33, M34);
            }
            void set(System::Numerics::Vector4 value)
            {
                M31 = value.X; M32 = value.Y; M33 = value.Z; M34 = value.W;
            }
        }
        property System::Numerics::Vector4 Row4
        {
            System::Numerics::Vector4 get()
            {
                return System::Numerics::Vector4(M41, M42, M43, M44);
            }
            void set(System::Numerics::Vector4 value)
            {
                M41 = value.X; M42 = value.Y; M43 = value.Z; M44 = value.W;
            }
        }

        property System::Numerics::Vector3 Right
        {
            System::Numerics::Vector3 get()
            {
                return System::Numerics::Vector3(M11, M12, M13);
            }
            void set(System::Numerics::Vector3 value)
            {
                M11 = value.X; M12 = value.Y; M13 = value.Z; M14 = 0.0F;
            }
        }
        property System::Numerics::Vector3 Up
        {
            System::Numerics::Vector3 get()
            {
                return System::Numerics::Vector3(M21, M22, M23);
            }
            void set(System::Numerics::Vector3 value)
            {
                M21 = value.X; M22 = value.Y; M23 = value.Z; M24 = 0.0F;
            }
        }
        property System::Numerics::Vector3 At
        {
            System::Numerics::Vector3 get()
            {
                return System::Numerics::Vector3(M31, M32, M33);
            }
            void set(System::Numerics::Vector3 value)
            {
                M31 = value.X; M32 = value.Y; M33 = value.Z; M34 = 0.0F;
            }
        }
        property System::Numerics::Vector3 Pos
        {
            System::Numerics::Vector3 get()
            {
                return System::Numerics::Vector3(M41, M42, M43);
            }
            void set(System::Numerics::Vector3 value)
            {
                M41 = value.X; M42 = value.Y; M43 = value.Z; M44 = 1.0F;
            }
        }

        property float default[int]
        {
            float get(int index)
            {
                switch (index)
                {
                    case 0: return M11; case 1: return M12; case 2: return M13; case 3: return M14;
                    case 4: return M21; case 5: return M22; case 6: return M23; case 7: return M24;
                    case 8: return M31; case 9: return M32; case 10: return M33; case 11: return M34;
                    case 12: return M41; case 13: return M42; case 14: return M43; case 15: return M44;
                    default: throw gcnew System::ArgumentOutOfRangeException("index", "Indices for IVMatrix run from 0 to 15, inclusive.");
                }
            }
            void set(int index, float value)
            {
                switch (index)
                {
                    case 0: M11 = value; break; case 1: M12 = value; break; case 2: M13 = value; break; case 3: M14 = value; break;
                    case 4: M21 = value; break; case 5: M22 = value; break; case 6: M23 = value; break; case 7: M24 = value; break;
                    case 8: M31 = value; break; case 9: M32 = value; break; case 10: M33 = value; break; case 11: M34 = value; break;
                    case 12: M41 = value; break; case 13: M42 = value; break; case 14: M43 = value; break; case 15: M44 = value; break;
                    default: throw gcnew System::ArgumentOutOfRangeException("index", "Indices for IVMatrix run from 0 to 15, inclusive.");
                }
            }
        }
        property float default[int, int]
        {
            float get(int row, int column)
            {
                if (row < 0 || row > 3)
                    throw gcnew System::ArgumentOutOfRangeException("row", "Rows for matrices run from 0 to 3, inclusive.");
                if (column < 0 || column > 3)
                    throw gcnew System::ArgumentOutOfRangeException("column", "Columns for matrices run from 0 to 3, inclusive.");
                return default[(row * 4) + column]; // Calls the 1D indexer
            }
            void set(int row, int column, float value)
            {
                if (row < 0 || row > 3)
                    throw gcnew System::ArgumentOutOfRangeException("row", "Rows for matrices run from 0 to 3, inclusive.");
                if (column < 0 || column > 3)
                    throw gcnew System::ArgumentOutOfRangeException("column", "Columns for matrices run from 0 to 3, inclusive.");
                default[(row * 4) + column] = value; // Calls the 1D indexer
            }
        }
        
        property bool IsIdentity
        {
            bool get()
            {
                return Equals(Identity);
            }
        }
        property bool HasInverse
        {
            bool get()
            {
                return Determinant() != 0.0f;
            }
        }


    public:
        /// <summary>
        /// Initializes a new instance of the IVMatrix structure from the given float array.
        /// </summary>
        IVMatrix(array<float>^ values)
        {
            if (values == nullptr)
            {
                throw gcnew System::ArgumentNullException("values");
            }
            if (values->Length != 16)
            {
                throw gcnew System::ArgumentOutOfRangeException("values", "There must be sixteen and only sixteen input values for IVMatrix.");
            }
            M11 = values[0]; M12 = values[1]; M13 = values[2]; M14 = values[3];
            M21 = values[4]; M22 = values[5]; M23 = values[6]; M24 = values[7];
            M31 = values[8]; M32 = values[9]; M33 = values[10]; M34 = values[11];
            M41 = values[12]; M42 = values[13]; M43 = values[14]; M44 = values[15];
        }
        /// <summary>
        /// Initializes a new instance of the IVMatrix structure from the given floats.
        /// </summary>
        IVMatrix(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44)
        {
            M11 = m11; M12 = m12; M13 = m13; M14 = m14;
            M21 = m21; M22 = m22; M23 = m23; M24 = m24;
            M31 = m31; M32 = m32; M33 = m33; M34 = m34;
            M41 = m41; M42 = m42; M43 = m43; M44 = m44;
        }
        /// <summary>
        /// Initializes a new instance of the IVMatrix structure from the given Vector3's.
        /// </summary>
        IVMatrix(Vector3 right, Vector3 up, Vector3 at, Vector3 pos)
        {
            M11 = right.X;   M12 = right.Y;   M13 = right.Z;   M14 = 0.0F;
            M21 = up.X;      M22 = up.Y;      M23 = up.Z;      M24 = 0.0F;
            M31 = at.X;      M32 = at.Y;      M33 = at.Z;      M34 = 0.0F;
            M41 = pos.X;     M42 = pos.Y;     M43 = pos.Z;     M44 = 1.0F;
        }
        /// <summary>
        /// Initializes a new instance of the IVMatrix structure from the given Vector4's.
        /// </summary>
        IVMatrix(Vector4 right, Vector4 up, Vector4 at, Vector4 pos)
        {
            M11 = right.X;   M12 = right.Y;   M13 = right.Z;   M14 = right.W;
            M21 = up.X;      M22 = up.Y;      M23 = up.Z;      M24 = up.W;
            M31 = at.X;      M32 = at.Y;      M33 = at.Z;      M34 = at.W;
            M41 = pos.X;     M42 = pos.Y;     M43 = pos.Z;     M44 = pos.W;
        }
        /// <summary>
        /// Initializes a new instance of the IVMatrix structure from a native matrix.
        /// </summary>
        IVMatrix(CMatrix& m)
        {
            M11 = m.right.x;    M12 = m.right.y;    M13 = m.right.z;    M14 = m.right.w;
            M21 = m.up.x;       M22 = m.up.y;       M23 = m.up.z;       M24 = m.up.w;
            M31 = m.at.x;       M32 = m.at.y;       M33 = m.at.z;       M34 = m.at.w;
            M41 = m.pos.x;      M42 = m.pos.y;      M43 = m.pos.z;      M44 = m.pos.w;
        }
        /// <summary>
        /// Initializes a new instance of the IVMatrix structure from a native matrix.
        /// </summary>
        IVMatrix(CMatrix* m)
        {
            M11 = m->right.x;   M12 = m->right.y;   M13 = m->right.z;   M14 = m->right.w;
            M21 = m->up.x;      M22 = m->up.y;      M23 = m->up.z;      M24 = m->up.w;
            M31 = m->at.x;      M32 = m->at.y;      M33 = m->at.z;      M34 = m->at.w;
            M41 = m->pos.x;     M42 = m->pos.y;     M43 = m->pos.z;     M44 = m->pos.w;
        }

        static property IVMatrix Zero
        {
            IVMatrix get()
            {
                return IVMatrix();
            }
        }
        static property IVMatrix Identity
        {
            IVMatrix get()
            {
                IVMatrix result = IVMatrix();
                result.M11 = 1.0f; result.M22 = 1.0f;
                result.M33 = 1.0f; result.M44 = 1.0f;
                return result;
            }
        }

    internal:
        CMatrix ToCMatrix()
        {
            return CMatrix(
                CVector4(M11, M12, M13, M14),
                CVector4(M21, M22, M23, M24),
                CVector4(M31, M32, M33, M34),
                CVector4(M41, M42, M43, M44));
        }

    public:
        System::Numerics::Vector3 GetRight()
        {
            return System::Numerics::Vector3(M11, M12, M13);
        }
        System::Numerics::Vector3 GetForward()
        {
            return System::Numerics::Vector3(M21, M22, M23);
        }
        System::Numerics::Vector3 GetUp()
        {
            return System::Numerics::Vector3(M31, M32, M33);
        }
        System::Numerics::Vector3 GetPosition()
        {
            return System::Numerics::Vector3(M41, M42, M43);
        }

        IVMatrix SetRight(System::Numerics::Vector3 v)
        {
            M11 = v.X;
            M12 = v.Y;
            M13 = v.Z;
            return *this;
        }
        IVMatrix SetForward(System::Numerics::Vector3 v)
        {
            M21 = v.X;
            M22 = v.Y;
            M23 = v.Z;
            return *this;
        }
        IVMatrix SetUp(System::Numerics::Vector3 v)
        {
            M31 = v.X;
            M32 = v.Y;
            M33 = v.Z;
            return *this;
        }
        IVMatrix SetPosition(System::Numerics::Vector3 v)
        {
            M41 = v.X;
            M42 = v.Y;
            M43 = v.Z;
            return *this;
        }

        System::Numerics::Vector3 GetScaleVector(float tolerance)
        {
            System::Numerics::Vector3 scale = System::Numerics::Vector3::Zero;
            float squareSum;

            // Row 0 for scale.X
            squareSum = (default[0, 0] * default[0, 0]) + (default[0, 1] * default[0, 1]) + (default[0, 2] * default[0, 2]);
            if (squareSum > tolerance) scale.X = static_cast<float>(std::sqrt(squareSum)); else scale.X = 0.0f;

            // Row 1 for scale.Y
            squareSum = (default[1, 0] * default[1, 0]) + (default[1, 1] * default[1, 1]) + (default[1, 2] * default[1, 2]);
            if (squareSum > tolerance) scale.Y = static_cast<float>(std::sqrt(squareSum)); else scale.Y = 0.0f;

            // Row 2 for scale.Z
            squareSum = (default[2, 0] * default[2, 0]) + (default[2, 1] * default[2, 1]) + (default[2, 2] * default[2, 2]);
            if (squareSum > tolerance) scale.Z = static_cast<float>(std::sqrt(squareSum)); else scale.Z = 0.0f;

            return scale;
        }
        System::Numerics::Vector3 GetScaleVector()
        {
            return GetScaleVector(F32Epsilon);
        }

        float Determinant()
        {
            float temp1 = (M33 * M44) - (M34 * M43);
            float temp2 = (M32 * M44) - (M34 * M42);
            float temp3 = (M32 * M43) - (M33 * M42);
            float temp4 = (M31 * M44) - (M34 * M41);
            float temp5 = (M31 * M43) - (M33 * M41);
            float temp6 = (M31 * M42) - (M32 * M41);

            return ((((M11 * (((M22 * temp1) - (M23 * temp2)) + (M24 * temp3))) - (M12 * (((M21 * temp1) -
                (M23 * temp4)) + (M24 * temp5)))) + (M13 * (((M21 * temp2) - (M22 * temp4)) + (M24 * temp6)))) -
                (M14 * (((M21 * temp3) - (M22 * temp5)) + (M23 * temp6))));
        }

    public:
        IVMatrix Invert()
        {
            float det = Determinant();
            if (det == 0.0f) return Zero;

            float invDet = 1.0f / det;
            IVMatrix temp;

            temp.M11 = Det3x3(M22, M23, M24, M32, M33, M34, M42, M43, M44) * invDet;
            temp.M21 = -Det3x3(M21, M23, M24, M31, M33, M34, M41, M43, M44) * invDet;
            temp.M31 = Det3x3(M21, M22, M24, M31, M32, M34, M41, M42, M44) * invDet;
            temp.M41 = -Det3x3(M21, M22, M23, M31, M32, M33, M41, M42, M43) * invDet;

            temp.M12 = -Det3x3(M12, M13, M14, M32, M33, M34, M42, M43, M44) * invDet;
            temp.M22 = Det3x3(M11, M13, M14, M31, M33, M34, M41, M43, M44) * invDet;
            temp.M32 = -Det3x3(M11, M12, M14, M31, M32, M34, M41, M42, M44) * invDet;
            temp.M42 = Det3x3(M11, M12, M13, M31, M32, M33, M41, M42, M43) * invDet;

            temp.M13 = Det3x3(M12, M13, M14, M22, M23, M24, M42, M43, M44) * invDet;
            temp.M23 = -Det3x3(M11, M13, M14, M21, M23, M24, M41, M43, M44) * invDet;
            temp.M33 = Det3x3(M11, M12, M14, M21, M22, M24, M41, M42, M44) * invDet;
            temp.M43 = -Det3x3(M11, M12, M13, M21, M22, M23, M41, M42, M43) * invDet;

            temp.M14 = -Det3x3(M12, M13, M14, M22, M23, M24, M32, M33, M34) * invDet;
            temp.M24 = Det3x3(M11, M13, M14, M21, M23, M24, M31, M33, M34) * invDet;
            temp.M34 = -Det3x3(M11, M12, M14, M21, M22, M24, M31, M32, M34) * invDet;
            temp.M44 = Det3x3(M11, M12, M13, M21, M22, M23, M31, M32, M33) * invDet;

            *this = temp;
            return temp;
        }

        IVMatrix Inverse()
        {
            IVMatrix res = *this;
            res.Invert();
            return res;
        }
        IVMatrix FastInverse()
        {
            IVMatrix res = IVMatrix();
            res.M11 = M11; res.M21 = M12; res.M31 = M13;
            res.M12 = M21; res.M22 = M22; res.M32 = M23;
            res.M13 = M31; res.M23 = M32; res.M33 = M33;

            res.M41 = ((M13 * M43) + (M11 * M41) + (M12 * M42)) * -1.0f;
            res.M42 = ((M23 * M43) + (M21 * M41) + (M22 * M42)) * -1.0f;
            res.M43 = ((M33 * M43) + (M31 * M41) + (M32 * M42)) * -1.0f;

            res.M14 = 0.0f; res.M24 = 0.0f; res.M34 = 0.0f;
            res.M44 = 1.0f;

            return res;
        }

        System::Numerics::Vector3 TransformPoint(System::Numerics::Vector3 point)
        {
            // Manual transformation as System.Numerics.Vector3.Transform expects System.Numerics.Matrix4x4
            float x = (point.X * M11) + (point.Y * M21) + (point.Z * M31) + M41;
            float y = (point.X * M12) + (point.Y * M22) + (point.Z * M32) + M42;
            float z = (point.X * M13) + (point.Y * M23) + (point.Z * M33) + M43;
            float w = (point.X * M14) + (point.Y * M24) + (point.Z * M34) + M44;

            if (w == 0.0f) return System::Numerics::Vector3(x, y, z); // Or handle error
            return System::Numerics::Vector3(x / w, y / w, z / w);
        }
        System::Numerics::Vector3 InverseTransformPoint(System::Numerics::Vector3 point)
        {
            return InverseTransformVector(point - System::Numerics::Vector3(M41, M42, M43));
        }
        System::Numerics::Vector3 TransformVector(System::Numerics::Vector3 vector)
        {
            // Manual transformation (ignores translation M41,M42,M43 and perspective M14,M24,M34,M44)
            float x = (vector.X * M11) + (vector.Y * M21) + (vector.Z * M31);
            float y = (vector.X * M12) + (vector.Y * M22) + (vector.Z * M32);
            float z = (vector.X * M13) + (vector.Y * M23) + (vector.Z * M33);
            return System::Numerics::Vector3(x, y, z);
        }
        System::Numerics::Vector3 InverseTransformVector(System::Numerics::Vector3 vector)
        {
            float scaleXSquared = (System::Numerics::Vector3(M11, M12, M13)).LengthSquared();
            float scaleYSquared = (System::Numerics::Vector3(M21, M22, M23)).LengthSquared();
            float scaleZSquared = (System::Numerics::Vector3(M31, M32, M33)).LengthSquared();

            if (std::abs(1.0f - scaleXSquared) > F32Epsilon ||
                std::abs(1.0f - scaleYSquared) > F32Epsilon ||
                std::abs(1.0f - scaleZSquared) > F32Epsilon)
            {
                return InverseTransformVectorWithScale(vector, scaleXSquared, scaleYSquared, scaleZSquared);
            }

            System::Numerics::Quaternion inverseRotation = ToQuaternion(*this); // Using helper
            inverseRotation = System::Numerics::Quaternion::Inverse(inverseRotation);

            return System::Numerics::Vector3::Transform(vector, inverseRotation);
        }
        System::Numerics::Vector3 TransformDirection(System::Numerics::Vector3 direction)
        {
            IVMatrix matrixNoScaling = GetMatrixWithoutScale();
            System::Numerics::Quaternion rotation = ToQuaternion(matrixNoScaling); // Using helper
            return System::Numerics::Vector3::Transform(direction, rotation);
        }
        System::Numerics::Vector3 InverseTransformDirection(System::Numerics::Vector3 direction)
        {
            IVMatrix matrixNoScaling = GetMatrixWithoutScale();
            System::Numerics::Quaternion inverseRotation = ToQuaternion(matrixNoScaling); // Using helper
            inverseRotation = System::Numerics::Quaternion::Inverse(inverseRotation);
            // System.Numerics.Quaternion.Inverse on a normalized quaternion also normalizes.
            return System::Numerics::Vector3::Transform(direction, inverseRotation);
        }

        IVMatrix ApplyScale(float scale)
        {
            return Scaling(System::Numerics::Vector3(scale, scale, scale)) * (*this);
        }
        IVMatrix ApplyScale(System::Numerics::Vector3 scale)
        {
            return Scaling(scale) * (*this);
        }

        IVMatrix GetMatrixWithoutScale()
        {
            IVMatrix r = *this; r.RemoveScaling(F32Epsilon); return r;
        }
        IVMatrix GetMatrixWithoutScale(float tolerance)
        {
            IVMatrix r = *this; r.RemoveScaling(tolerance); return r;
        }

        IVMatrix Translate(System::Numerics::Vector3 amount)
        {
            IVMatrix r = *this; r.M41 = amount.X; r.M42 = amount.Y; r.M43 = amount.Z; return r;
        }
        IVMatrix RemoveTranslation()
        {
            IVMatrix r = *this; r.M41 = 0.0f; r.M42 = 0.0f; r.M43 = 0.0f; return r;
        }

        void RemoveScaling()
        {
            RemoveScaling(F32Epsilon);
        }
        void RemoveScaling(float tolerance)
        {
            // Row 0
            System::Numerics::Vector3 row0(M11, M12, M13);
            float scaleXSquared = row0.LengthSquared();
            if (std::abs(1.0f - scaleXSquared) > tolerance && scaleXSquared > F32Epsilon) // Check scaleXSquared > 0 to avoid NaN from sqrt(0)
            {
                float invScaleX = 1.0f / static_cast<float>(std::sqrt(scaleXSquared));
                M11 *= invScaleX; M12 *= invScaleX; M13 *= invScaleX;
            }
            // Row 1
            System::Numerics::Vector3 row1(M21, M22, M23);
            float scaleYSquared = row1.LengthSquared();
            if (std::abs(1.0f - scaleYSquared) > tolerance && scaleYSquared > F32Epsilon)
            {
                float invScaleY = 1.0f / static_cast<float>(std::sqrt(scaleYSquared));
                M21 *= invScaleY; M22 *= invScaleY; M23 *= invScaleY;
            }
            // Row 2
            System::Numerics::Vector3 row2(M31, M32, M33);
            float scaleZSquared = row2.LengthSquared();
            if (std::abs(1.0f - scaleZSquared) > tolerance && scaleZSquared > F32Epsilon)
            {
                float invScaleZ = 1.0f / static_cast<float>(std::sqrt(scaleZSquared));
                M31 *= invScaleZ; M32 *= invScaleZ; M33 *= invScaleZ;
            }
        }

    public:
        static IVMatrix Add(IVMatrix left, IVMatrix right)
        {
            IVMatrix result;
            result.M11 = left.M11 + right.M11; result.M12 = left.M12 + right.M12; result.M13 = left.M13 + right.M13; result.M14 = left.M14 + right.M14;
            result.M21 = left.M21 + right.M21; result.M22 = left.M22 + right.M22; result.M23 = left.M23 + right.M23; result.M24 = left.M24 + right.M24;
            result.M31 = left.M31 + right.M31; result.M32 = left.M32 + right.M32; result.M33 = left.M33 + right.M33; result.M34 = left.M34 + right.M34;
            result.M41 = left.M41 + right.M41; result.M42 = left.M42 + right.M42; result.M43 = left.M43 + right.M43; result.M44 = left.M44 + right.M44;
            return result;
        }
        static IVMatrix Subtract(IVMatrix left, IVMatrix right)
        {
            IVMatrix result;
            result.M11 = left.M11 - right.M11; result.M12 = left.M12 - right.M12; result.M13 = left.M13 - right.M13; result.M14 = left.M14 - right.M14;
            result.M21 = left.M21 - right.M21; result.M22 = left.M22 - right.M22; result.M23 = left.M23 - right.M23; result.M24 = left.M24 - right.M24;
            result.M31 = left.M31 - right.M31; result.M32 = left.M32 - right.M32; result.M33 = left.M33 - right.M33; result.M34 = left.M34 - right.M34;
            result.M41 = left.M41 - right.M41; result.M42 = left.M42 - right.M42; result.M43 = left.M43 - right.M43; result.M44 = left.M44 - right.M44;
            return result;
        }
        static IVMatrix Multiply(IVMatrix left, IVMatrix right)
        {
            IVMatrix result;
            result.M11 = (left.M11 * right.M11) + (left.M12 * right.M21) + (left.M13 * right.M31) + (left.M14 * right.M41);
            result.M12 = (left.M11 * right.M12) + (left.M12 * right.M22) + (left.M13 * right.M32) + (left.M14 * right.M42);
            result.M13 = (left.M11 * right.M13) + (left.M12 * right.M23) + (left.M13 * right.M33) + (left.M14 * right.M43);
            result.M14 = (left.M11 * right.M14) + (left.M12 * right.M24) + (left.M13 * right.M34) + (left.M14 * right.M44);
            result.M21 = (left.M21 * right.M11) + (left.M22 * right.M21) + (left.M23 * right.M31) + (left.M24 * right.M41);
            result.M22 = (left.M21 * right.M12) + (left.M22 * right.M22) + (left.M23 * right.M32) + (left.M24 * right.M42);
            result.M23 = (left.M21 * right.M13) + (left.M22 * right.M23) + (left.M23 * right.M33) + (left.M24 * right.M43);
            result.M24 = (left.M21 * right.M14) + (left.M22 * right.M24) + (left.M23 * right.M34) + (left.M24 * right.M44);
            result.M31 = (left.M31 * right.M11) + (left.M32 * right.M21) + (left.M33 * right.M31) + (left.M34 * right.M41);
            result.M32 = (left.M31 * right.M12) + (left.M32 * right.M22) + (left.M33 * right.M32) + (left.M34 * right.M42);
            result.M33 = (left.M31 * right.M13) + (left.M32 * right.M23) + (left.M33 * right.M33) + (left.M34 * right.M43);
            result.M34 = (left.M31 * right.M14) + (left.M32 * right.M24) + (left.M33 * right.M34) + (left.M34 * right.M44);
            result.M41 = (left.M41 * right.M11) + (left.M42 * right.M21) + (left.M43 * right.M31) + (left.M44 * right.M41);
            result.M42 = (left.M41 * right.M12) + (left.M42 * right.M22) + (left.M43 * right.M32) + (left.M44 * right.M42);
            result.M43 = (left.M41 * right.M13) + (left.M42 * right.M23) + (left.M43 * right.M33) + (left.M44 * right.M43);
            result.M44 = (left.M41 * right.M14) + (left.M42 * right.M24) + (left.M43 * right.M34) + (left.M44 * right.M44);
            return result;
        }
        static IVMatrix Multiply(IVMatrix left, float right)
        {
            IVMatrix result;
            result.M11 = left.M11 * right; result.M12 = left.M12 * right; result.M13 = left.M13 * right; result.M14 = left.M14 * right;
            result.M21 = left.M21 * right; result.M22 = left.M22 * right; result.M23 = left.M23 * right; result.M24 = left.M24 * right;
            result.M31 = left.M31 * right; result.M32 = left.M32 * right; result.M33 = left.M33 * right; result.M34 = left.M34 * right;
            result.M41 = left.M41 * right; result.M42 = left.M42 * right; result.M43 = left.M43 * right; result.M44 = left.M44 * right;
            return result;
        }
        static IVMatrix Divide(IVMatrix left, IVMatrix right)
        {
            IVMatrix result;
            result.M11 = left.M11 / right.M11; result.M12 = left.M12 / right.M12; result.M13 = left.M13 / right.M13; result.M14 = left.M14 / right.M14;
            // ... and so on for all 16 components
            result.M21 = left.M21 / right.M21; result.M22 = left.M22 / right.M22; result.M23 = left.M23 / right.M23; result.M24 = left.M24 / right.M24;
            result.M31 = left.M31 / right.M31; result.M32 = left.M32 / right.M32; result.M33 = left.M33 / right.M33; result.M34 = left.M34 / right.M34;
            result.M41 = left.M41 / right.M41; result.M42 = left.M42 / right.M42; result.M43 = left.M43 / right.M43; result.M44 = left.M44 / right.M44;
            return result;
        }
        static IVMatrix Divide(IVMatrix left, float right)
        {
            float inv = 1.0f / right; return Multiply(left, inv);
        }
        static IVMatrix Negate(IVMatrix matrix)
        {
            IVMatrix result;
            result.M11 = -matrix.M11; result.M12 = -matrix.M12; result.M13 = -matrix.M13; result.M14 = -matrix.M14;
            // ... and so on for all 16 components
            result.M21 = -matrix.M21; result.M22 = -matrix.M22; result.M23 = -matrix.M23; result.M24 = -matrix.M24;
            result.M31 = -matrix.M31; result.M32 = -matrix.M32; result.M33 = -matrix.M33; result.M34 = -matrix.M34;
            result.M41 = -matrix.M41; result.M42 = -matrix.M42; result.M43 = -matrix.M43; result.M44 = -matrix.M44;
            return result;
        }
        static IVMatrix Invert(IVMatrix matrix)
        {
            matrix.Invert(); return matrix;
        }
        static IVMatrix Lerp(IVMatrix start, IVMatrix end, float amount)
        {
            IVMatrix result;
            result.M11 = start.M11 + ((end.M11 - start.M11) * amount); // ... and so on for all 16
            result.M12 = start.M12 + ((end.M12 - start.M12) * amount);
            result.M13 = start.M13 + ((end.M13 - start.M13) * amount);
            result.M14 = start.M14 + ((end.M14 - start.M14) * amount);
            result.M21 = start.M21 + ((end.M21 - start.M21) * amount);
            result.M22 = start.M22 + ((end.M22 - start.M22) * amount);
            result.M23 = start.M23 + ((end.M23 - start.M23) * amount);
            result.M24 = start.M24 + ((end.M24 - start.M24) * amount);
            result.M31 = start.M31 + ((end.M31 - start.M31) * amount);
            result.M32 = start.M32 + ((end.M32 - start.M32) * amount);
            result.M33 = start.M33 + ((end.M33 - start.M33) * amount);
            result.M34 = start.M34 + ((end.M34 - start.M34) * amount);
            result.M41 = start.M41 + ((end.M41 - start.M41) * amount);
            result.M42 = start.M42 + ((end.M42 - start.M42) * amount);
            result.M43 = start.M43 + ((end.M43 - start.M43) * amount);
            result.M44 = start.M44 + ((end.M44 - start.M44) * amount);
            return result;
        }

        static IVMatrix RotationX(float angle)
        {
            IVMatrix result = Identity;
            float cosAngle = static_cast<float>(std::cos(angle));
            float sinAngle = static_cast<float>(std::sin(angle));
            result.M22 = cosAngle; result.M23 = sinAngle;
            result.M32 = -sinAngle; result.M33 = cosAngle;
            return result;
        }
        static IVMatrix RotationY(float angle)
        {
            IVMatrix result = Identity;
            float cosAngle = static_cast<float>(std::cos(angle));
            float sinAngle = static_cast<float>(std::sin(angle));
            result.M11 = cosAngle; result.M13 = -sinAngle; // Note: SharpDX M13 is +sin, M31 is -sin for LH
            result.M31 = sinAngle; result.M33 = cosAngle; // This matches original code which is likely RH
            return result;
        }
        static IVMatrix RotationZ(float angle)
        {
            IVMatrix result = Identity;
            float cosAngle = static_cast<float>(std::cos(angle));
            float sinAngle = static_cast<float>(std::sin(angle));
            result.M11 = cosAngle; result.M12 = sinAngle;
            result.M21 = -sinAngle; result.M22 = cosAngle;
            return result;
        }

        static IVMatrix RotationAxis(System::Numerics::Vector3 axis, float angle)
        {
            if (axis.LengthSquared() != 1.0f) axis = System::Numerics::Vector3::Normalize(axis);
            
            IVMatrix result = Identity;
            float x = axis.X, y = axis.Y, z = axis.Z;
            float cosAngle = static_cast<float>(std::cos(angle));
            float sinAngle = static_cast<float>(std::sin(angle));
            float xx = x * x, yy = y * y, zz = z * z;
            float xy = x * y, xz = x * z, yz = y * z;

            result.M11 = xx + (cosAngle * (1.0f - xx));
            result.M12 = (xy - (cosAngle * xy)) + (sinAngle * z);
            result.M13 = (xz - (cosAngle * xz)) - (sinAngle * y);
            result.M21 = (xy - (cosAngle * xy)) - (sinAngle * z);
            result.M22 = yy + (cosAngle * (1.0f - yy));
            result.M23 = (yz - (cosAngle * yz)) + (sinAngle * x);
            result.M31 = (xz - (cosAngle * xz)) + (sinAngle * y);
            result.M32 = (yz - (cosAngle * yz)) - (sinAngle * x);
            result.M33 = zz + (cosAngle * (1.0f - zz));
            return result;
        }

        static IVMatrix RotationQuaternion(System::Numerics::Quaternion rotation)
        {
            IVMatrix result = Identity;
            float xx = rotation.X * rotation.X, yy = rotation.Y * rotation.Y, zz = rotation.Z * rotation.Z;
            float xy = rotation.X * rotation.Y, zw = rotation.Z * rotation.W;
            float zx = rotation.Z * rotation.X, yw = rotation.Y * rotation.W;
            float yz = rotation.Y * rotation.Z, xw = rotation.X * rotation.W;

            result.M11 = 1.0f - (2.0f * (yy + zz));
            result.M12 = 2.0f * (xy + zw);
            result.M13 = 2.0f * (zx - yw);
            result.M21 = 2.0f * (xy - zw);
            result.M22 = 1.0f - (2.0f * (zz + xx));
            result.M23 = 2.0f * (yz + xw);
            result.M31 = 2.0f * (zx + yw);
            result.M32 = 2.0f * (yz - xw);
            result.M33 = 1.0f - (2.0f * (yy + xx));
            return result;
        }

        static IVMatrix RotationYawPitchRoll(float yaw, float pitch, float roll)
        {
            return RotationQuaternion(System::Numerics::Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll));
        }

        static IVMatrix Scaling(float x, float y, float z)
        {
            IVMatrix result = Identity; result.M11 = x; result.M22 = y; result.M33 = z; return result;
        }
        static IVMatrix Scaling(System::Numerics::Vector3 scale)
        {
            return Scaling(scale.X, scale.Y, scale.Z);
        }

        static IVMatrix Translation(float x, float y, float z)
        {
            IVMatrix result = Identity; result.M41 = x; result.M42 = y; result.M43 = z; return result;
        }
        static IVMatrix Translation(System::Numerics::Vector3 amount)
        {
            return Translation(amount.X, amount.Y, amount.Z);
        }

        static IVMatrix Transpose(IVMatrix matrix)
        {
            IVMatrix result;
            result.M11 = matrix.M11; result.M12 = matrix.M21; result.M13 = matrix.M31; result.M14 = matrix.M41;
            result.M21 = matrix.M12; result.M22 = matrix.M22; result.M23 = matrix.M32; result.M24 = matrix.M42;
            result.M31 = matrix.M13; result.M32 = matrix.M23; result.M33 = matrix.M33; result.M34 = matrix.M43;
            result.M41 = matrix.M14; result.M42 = matrix.M24; result.M43 = matrix.M34; result.M44 = matrix.M44;
            return result;
        }

    public:
        // Overrides
        array<float>^ ToArray()
        {
            array<float>^ arr = gcnew array<float>(16);
            for (int i = 0; i < 16; ++i) arr[i] = default[i]; // Use 1D indexer
            return arr;
        }

        virtual System::String^ ToString() override
        {
            return ToString(nullptr, System::Globalization::CultureInfo::CurrentCulture);
        }
        System::String^ ToString(System::String^ format)
        {
            return ToString(format, System::Globalization::CultureInfo::CurrentCulture);
        }
        virtual System::String^ ToString(System::String^ format, System::IFormatProvider^ provider) sealed = System::IFormattable::ToString
        {
            return System::String::Format(provider,
                "[M11:{0} M12:{1} M13:{2} M14:{3}] [M21:{4} M22:{5} M23:{6} M24:{7}] " +
                "[M31:{8} M32:{9} M33:{10} M34:{11}] [M41:{12} M42:{13} M43:{14} M44:{15}]",
                M11.ToString(format, provider), M12.ToString(format, provider), M13.ToString(format, provider), M14.ToString(format, provider),
                M21.ToString(format, provider), M22.ToString(format, provider), M23.ToString(format, provider), M24.ToString(format, provider),
                M31.ToString(format, provider), M32.ToString(format, provider), M33.ToString(format, provider), M34.ToString(format, provider),
                M41.ToString(format, provider), M42.ToString(format, provider), M43.ToString(format, provider), M44.ToString(format, provider)
            );
        }
        virtual int GetHashCode() override
        {
            int hashCode = M11.GetHashCode();
            hashCode = (hashCode * 397) ^ M12.GetHashCode(); hashCode = (hashCode * 397) ^ M13.GetHashCode(); hashCode = (hashCode * 397) ^ M14.GetHashCode();
            hashCode = (hashCode * 397) ^ M21.GetHashCode(); hashCode = (hashCode * 397) ^ M22.GetHashCode(); hashCode = (hashCode * 397) ^ M23.GetHashCode(); hashCode = (hashCode * 397) ^ M24.GetHashCode();
            hashCode = (hashCode * 397) ^ M31.GetHashCode(); hashCode = (hashCode * 397) ^ M32.GetHashCode(); hashCode = (hashCode * 397) ^ M33.GetHashCode(); hashCode = (hashCode * 397) ^ M34.GetHashCode();
            hashCode = (hashCode * 397) ^ M41.GetHashCode(); hashCode = (hashCode * 397) ^ M42.GetHashCode(); hashCode = (hashCode * 397) ^ M43.GetHashCode(); hashCode = (hashCode * 397) ^ M44.GetHashCode();
            return hashCode;
        }
        virtual bool Equals(System::Object^ obj) override
        {
            if (obj == nullptr || obj->GetType() != GetType()) return false;
            return Equals(safe_cast<IVMatrix>(obj));
        }
        virtual bool Equals(IVMatrix other) sealed = System::IEquatable<IVMatrix>::Equals
        {
            return (M11 == other.M11 && M12 == other.M12 && M13 == other.M13 && M14 == other.M14 &&
                    M21 == other.M21 && M22 == other.M22 && M23 == other.M23 && M24 == other.M24 &&
                    M31 == other.M31 && M32 == other.M32 && M33 == other.M33 && M34 == other.M34 &&
                    M41 == other.M41 && M42 == other.M42 && M43 == other.M43 && M44 == other.M44);
        }

    public:
        // Operators
        static IVMatrix operator - (IVMatrix matrix)
        {
            return Negate(matrix);
        }
        static IVMatrix operator + (IVMatrix left, IVMatrix right)
        {
            return Add(left, right);
        }
        static IVMatrix operator - (IVMatrix left, IVMatrix right)
        {
            return Subtract(left, right);
        }
        static IVMatrix operator / (IVMatrix left, IVMatrix right)
        {
            return Divide(left, right);
        }
        static IVMatrix operator / (IVMatrix left, float right)
        {
            return Divide(left, right);
        }
        static IVMatrix operator * (IVMatrix left, IVMatrix right)
        {
            return Multiply(left, right);
        }
        static IVMatrix operator * (IVMatrix left, float right)
        {
            return Multiply(left, right);
        }
        static IVMatrix operator * (float left, IVMatrix right)
        {
            return Multiply(right, left);
        }
        static bool operator == (IVMatrix left, IVMatrix right)
        {
            return left.Equals(right);
        }
        static bool operator != (IVMatrix left, IVMatrix right)
        {
            return !left.Equals(right);
        }

    private:
        float Det3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
        {
            return m11 * (m22 * m33 - m23 * m32) - m12 * (m21 * m33 - m23 * m31) + m13 * (m21 * m32 - m22 * m31);
        }
        float GetSafeScaleReciprocal(float scale, float tolerance)
        {
            return (std::abs(scale) <= tolerance) ? 0.0f : (1.0f / scale);
        }
        float GetSafeScaleReciprocal(float scale)
        {
            return GetSafeScaleReciprocal(scale, F32Epsilon);
        }

        System::Numerics::Vector3 InverseTransformVectorWithScale(System::Numerics::Vector3 vector, float squaredScaleX, float squaredScaleY, float squaredScaleZ)
        {
            float safeScaleX = GetSafeScaleReciprocal(static_cast<float>(std::sqrt(squaredScaleX)));
            float safeScaleY = GetSafeScaleReciprocal(static_cast<float>(std::sqrt(squaredScaleY)));
            float safeScaleZ = GetSafeScaleReciprocal(static_cast<float>(std::sqrt(squaredScaleZ)));

            IVMatrix matrixNoScaling = GetMatrixWithoutScale();
            System::Numerics::Quaternion inverseRotation = ToQuaternion(matrixNoScaling); // Using helper
            inverseRotation = System::Numerics::Quaternion::Inverse(inverseRotation);
            inverseRotation = System::Numerics::Quaternion::Normalize(inverseRotation);

            System::Numerics::Vector3 vectorUnrotated = System::Numerics::Vector3::Transform(vector, inverseRotation);

            return System::Numerics::Vector3(vectorUnrotated.X * safeScaleX, vectorUnrotated.Y * safeScaleY, vectorUnrotated.Z * safeScaleZ);
        }

        // Helper to convert this IVMatrix's rotation part to System::Numerics::Quaternion
        static System::Numerics::Quaternion ToQuaternion(IVMatrix% matrix)
        {
            float trace = matrix.M11 + matrix.M22 + matrix.M33;
            System::Numerics::Quaternion q;

            if (trace > 0.0f)
            {
                float s = static_cast<float>(std::sqrt(trace + 1.0f)) * 2.0f;
                q.W = 0.25f * s;
                q.X = (matrix.M23 - matrix.M32) / s;
                q.Y = (matrix.M31 - matrix.M13) / s;
                q.Z = (matrix.M12 - matrix.M21) / s;
            }
            else if ((matrix.M11 > matrix.M22) && (matrix.M11 > matrix.M33))
            {
                float s = static_cast<float>(std::sqrt(1.0f + matrix.M11 - matrix.M22 - matrix.M33)) * 2.0f;
                q.W = (matrix.M23 - matrix.M32) / s;
                q.X = 0.25f * s;
                q.Y = (matrix.M12 + matrix.M21) / s;
                q.Z = (matrix.M13 + matrix.M31) / s;
            }
            else if (matrix.M22 > matrix.M33)
            {
                float s = static_cast<float>(std::sqrt(1.0f + matrix.M22 - matrix.M11 - matrix.M33)) * 2.0f;
                q.W = (matrix.M31 - matrix.M13) / s;
                q.X = (matrix.M12 + matrix.M21) / s;
                q.Y = 0.25f * s;
                q.Z = (matrix.M23 + matrix.M32) / s;
            }
            else
            {
                float s = static_cast<float>(std::sqrt(1.0f + matrix.M33 - matrix.M11 - matrix.M22)) * 2.0f;
                q.W = (matrix.M12 - matrix.M21) / s;
                q.X = (matrix.M13 + matrix.M31) / s;
                q.Y = (matrix.M23 + matrix.M32) / s;
                q.Z = 0.25f * s;
            }
            return q;
        }

    private:
        literal float F32Epsilon = 1.1920929e-7f; // System.Single.Epsilon is different
    };
}