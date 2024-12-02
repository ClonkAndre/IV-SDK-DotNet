using System;
using System.Collections.Generic;
using System.Numerics;
using System.Runtime.InteropServices;

using IVSDKDotNet.Native;

using Manager.Extensions;

namespace Manager.Classes
{
    public class NativeArg
    {
        #region Variables
        public Type Type;
        public object Value;
        public bool IsOutArgument;
        public bool IsBeingReused;
        #endregion

        #region Constructor
        public NativeArg(Type t, object v)
        {
            Type = t;
            Value = v;
            IsOutArgument = false;
        }
        public NativeArg(Type t)
        {
            Type = t;
            Value = null;
            IsOutArgument = false;
        }
        public NativeArg(bool isOutArgument, Type t)
        {
            Type = t;
            Value = null;
            IsOutArgument = isOutArgument;
        }
        #endregion

        #region Methods
        public void SetValue(object v)
        {
            Value = v;
        }
        #endregion

        #region Functions
        public T GetValue<T>()
        {
            if (Value == null)
                return default;

            return (T)Value;
        }

        public NativeArg Reuse()
        {
            IsBeingReused = true;
            return this;
        }
        #endregion

        public static implicit operator int(NativeArg nativeArgument)
        {
            return nativeArgument.GetValue<int>();
        }
        public static implicit operator uint(NativeArg nativeArgument)
        {
            return nativeArgument.GetValue<uint>();
        }
        public static implicit operator float(NativeArg nativeArgument)
        {
            return nativeArgument.GetValue<float>();
        }
        public static implicit operator double(NativeArg nativeArgument)
        {
            return nativeArgument.GetValue<float>();
        }
        public static implicit operator bool(NativeArg nativeArgument)
        {
            return nativeArgument.GetValue<bool>();
        }
        public static implicit operator string(NativeArg nativeArgument)
        {
            return nativeArgument.GetValue<string>();
        }

        public static explicit operator NativeArg(int value)
        {
            return new NativeArg(typeof(int), value);
        }
        public static explicit operator NativeArg(uint value)
        {
            return new NativeArg(typeof(uint), value);
        }
        public static explicit operator NativeArg(float value)
        {
            return new NativeArg(typeof(float), value);
        }
        public static explicit operator NativeArg(double value)
        {
            return new NativeArg(typeof(float), (float)value);
        }
        public static explicit operator NativeArg(bool value)
        {
            return new NativeArg(typeof(bool), value);
        }
        public static explicit operator NativeArg(string value)
        {
            return new NativeArg(typeof(string), value);
        }
        public static explicit operator NativeArg(Vector2 value)
        {
            return new NativeArg(typeof(Vector2), value);
        }
        public static explicit operator NativeArg(Vector3 value)
        {
            return new NativeArg(typeof(Vector3), value);
        }
        public static explicit operator NativeArg(Vector4 value)
        {
            return new NativeArg(typeof(Vector4), value);
        }
        public static explicit operator NativeArg(Quaternion value)
        {
            return new NativeArg(typeof(Quaternion), value);
        }
    }

    public class NativeCaller
    {

        public static T Call<T>(uint hash, params NativeArg[] args)
        {
            T result = default;

            int outArgCount = 0;
            Dictionary<int, IntPtr> outArguments = new Dictionary<int, IntPtr>(args.Length);

            try
            {
                // Allocate new native context object
                using (IVNativeContext context = IVNativeContext.AllocateNew())
                {
                    // Push args to native context for native call
                    if (args != null)
                    {
                        for (int i = 0; i < args.Length; i++)
                        {
                            NativeArg arg = args[i];

                            // If argument is an object then that means it should be an out parameter
                            if (arg.IsOutArgument && !arg.IsBeingReused)
                            {
                                if (context.PushOut(Marshal.SizeOf(arg.Type), out IntPtr outArg))
                                {
                                    outArguments.Add(i, outArg);
                                    outArgCount++;
                                }
                                continue;
                            }

                            arg.IsBeingReused = false;

                            // Figure out type of argument
                            if (arg.Type == typeof(bool))
                            {
                                context.Push(Convert.ToBoolean(arg.Value));
                            }
                            else if (arg.Type == typeof(byte))
                            {
                                context.Push(Convert.ToByte(arg.Value));
                            }
                            else if (arg.Type == typeof(sbyte))
                            {
                                context.Push(Convert.ToSByte(arg.Value));
                            }
                            else if (arg.Type == typeof(char))
                            {
                                context.Push(Convert.ToChar(arg.Value));
                            }
                            else if (arg.Type == typeof(float))
                            {
                                context.Push(Convert.ToSingle(arg.Value));
                            }
                            else if (arg.Type == typeof(int))
                            {
                                context.Push(Convert.ToInt32(arg.Value));
                            }
                            else if (arg.Type == typeof(uint))
                            {
                                context.Push(Convert.ToUInt32(arg.Value));
                            }
                            else if (arg.Type == typeof(short))
                            {
                                context.Push(Convert.ToInt16(arg.Value));
                            }
                            else if (arg.Type == typeof(ushort))
                            {
                                context.Push(Convert.ToUInt16(arg.Value));
                            }
                            else if (arg.Type == typeof(Vector2))
                            {
                                context.Push((Vector2)arg.Value);
                            }
                            else if (arg.Type == typeof(Vector3))
                            {
                                context.Push((Vector3)arg.Value);
                            }
                            else if (arg.Type == typeof(Quaternion))
                            {
                                context.Push((Quaternion)arg.Value);
                            }
                            else if (arg.Type == typeof(string))
                            {
                                context.Push(Convert.ToString(arg.Value));
                            }
                        }
                    }

                    // Invoke the native with the given context
                    IVNativeInvoke.Invoke(hash, context);

                    // Get the result of the native invokation
                    context.GetResult(out IntPtr resultPtr);
                    result = resultPtr.ToGeneric<T>();

                    // After the native was invoked, we can set the out arguments
                    if (outArgCount != 0)
                    {
                        foreach (var item in outArguments)
                        {
                            args[item.Key].SetValue(Marshal.PtrToStructure(item.Value, args[item.Key].Type));
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Helper.WriteToDebugOutput(Priority.High, "Failed to call native function '{0}'! Details: {1}", hash, ex);
            }
            finally
            {
                // Free memory
                foreach (var item in outArguments)
                {
                    Marshal.FreeHGlobal(item.Value);
                }
                outArguments.Clear();
                outArguments = null;
            }

            return result;
        }
        public static void Call(uint hash, params NativeArg[] args)
        {
            Call<uint>(hash, args);
        }

        public static T Call<T>(eNativeHash hash, params NativeArg[] args)
        {
            return Call<T>((uint)hash, args);
        }
        public static void Call(eNativeHash hash, params NativeArg[] args)
        {
            Call<uint>((uint)hash, args);
        }

    }
}
