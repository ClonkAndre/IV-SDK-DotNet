using System;
using System.Numerics;
using System.Runtime.InteropServices;

namespace Manager.Extensions
{
    public static class IntPtrExtensions
    {

        public static T ToGeneric<T>(this IntPtr ptr)
        {
            // Perform conversion based on the type of T
            if (typeof(T) == typeof(bool))
            {
                return (T)(object)BitConverter.ToBoolean(BitConverter.GetBytes(ptr.ToInt32()), 0);
            }
            else if (typeof(T) == typeof(byte))
            {
                return (T)(object)(byte)ptr.ToInt32();
            }
            else if (typeof(T) == typeof(sbyte))
            {
                return (T)(object)(sbyte)ptr.ToInt32();
            }
            else if (typeof(T) == typeof(char))
            {
                return (T)(object)(char)ptr.ToInt32();
            }
            else if (typeof(T) == typeof(double))
            {
                return (T)(object)BitConverter.ToDouble(BitConverter.GetBytes(ptr.ToInt64()), 0);
            }
            else if (typeof(T) == typeof(float))
            {
                return (T)(object)BitConverter.ToSingle(BitConverter.GetBytes(ptr.ToInt32()), 0);
            }
            else if (typeof(T) == typeof(int))
            {
                return (T)(object)ptr.ToInt32();
            }
            else if (typeof(T) == typeof(uint))
            {
                return (T)(object)(uint)ptr.ToInt32();
            }
            else if (typeof(T) == typeof(short))
            {
                return (T)(object)(short)ptr.ToInt32();
            }
            else if (typeof(T) == typeof(ushort))
            {
                return (T)(object)(ushort)ptr.ToInt32();
            }
            else if (typeof(T) == typeof(Vector2)
                || typeof(T) == typeof(Vector3)
                || typeof(T) == typeof(Vector4)
                || typeof(T) == typeof(Quaternion))
            {
                return (T)Marshal.PtrToStructure(ptr, typeof(T));
            }
            else if (typeof(T) == typeof(string))
            {
                return (T)(object)Marshal.PtrToStringAnsi(ptr);
            }
            else
            {
                throw new NotSupportedException(string.Format("Type {0} is not supported.", typeof(T)));
            }
        }
        public static T ToPrimitive<T>(this IntPtr ptr) where T : struct
        {
            // Ensure that T is a primitive type
            if (!typeof(T).IsPrimitive)
                throw new ArgumentException("T must be a primitive type");

            return ToGeneric<T>(ptr);
        }

    }
}
