using System;
using System.Collections.Generic;
using System.IO;
using System.Numerics;
using System.Runtime.InteropServices;

using IVSDKDotNet.Native;

using Manager.Extensions;
using Manager.Managers;

namespace Manager.Classes
{
    //public class NativeArg
    //{
    //    #region Variables and Properties

    //    // Variables
    //    private Type type;
    //    private object value;
    //    private bool isOutArgument;
    //    private bool isBeingReused;

    //    // Properties
    //    public Type ArgType
    //    {
    //        get => type;
    //        private set => type = value;
    //    }
    //    public object Value
    //    {
    //        get => value;
    //        private set => this.value = value;
    //    }
    //    public bool IsOutArgument
    //    {
    //        get => isOutArgument;
    //        private set => isOutArgument = value;
    //    }

    //    #endregion

    //    #region Constructor
    //    public NativeArg(Type t, object v)
    //    {
    //        Type = t;
    //        Value = v;
    //        IsOutArgument = false;
    //    }
    //    public NativeArg(bool isOutArgument, Type t)
    //    {
    //        Type = t;
    //        Value = null;
    //        IsOutArgument = isOutArgument;
    //    }
    //    #endregion

    //    #region Methods
    //    public void SetValue(object v)
    //    {
    //        Value = v;
    //    }
    //    #endregion

    //    #region Functions
    //    public T GetValue<T>()
    //    {
    //        if (Value == null)
    //            return default;

    //        return (T)Value;
    //    }

    //    public NativeArg Reuse()
    //    {
    //        IsBeingReused = true;
    //        return this;
    //    }
    //    #endregion

    //    public static NativeArg FromObject(object obj)
    //    {
    //        if (obj is int)
    //            return (NativeArg)(int)obj;
    //        else if (obj is uint)
    //            return (NativeArg)(uint)obj;
    //        else if (obj is float)
    //            return (NativeArg)(float)obj;
    //        else if (obj is double)
    //            return (NativeArg)(double)obj;
    //        else if (obj is bool)
    //            return (NativeArg)(bool)obj;
    //        else if (obj is string)
    //            return (NativeArg)(string)obj;
    //        else if (obj is Vector2)
    //            return (NativeArg)(Vector2)obj;
    //        else if (obj is Vector3)
    //            return (NativeArg)(Vector3)obj;
    //        else if (obj is Vector4)
    //            return (NativeArg)(Vector4)obj;
    //        else if (obj is Quaternion)
    //            return (NativeArg)(Quaternion)obj;

    //        throw new ArgumentException("Unsupported type");
    //    }

    //    public static implicit operator int(NativeArg nativeArgument)
    //    {
    //        return nativeArgument.GetValue<int>();
    //    }
    //    public static implicit operator uint(NativeArg nativeArgument)
    //    {
    //        return nativeArgument.GetValue<uint>();
    //    }
    //    public static implicit operator float(NativeArg nativeArgument)
    //    {
    //        return nativeArgument.GetValue<float>();
    //    }
    //    public static implicit operator double(NativeArg nativeArgument)
    //    {
    //        return nativeArgument.GetValue<float>();
    //    }
    //    public static implicit operator bool(NativeArg nativeArgument)
    //    {
    //        return nativeArgument.GetValue<bool>();
    //    }
    //    public static implicit operator string(NativeArg nativeArgument)
    //    {
    //        return nativeArgument.GetValue<string>();
    //    }

    //    public static explicit operator NativeArg(int value)
    //    {
    //        return new NativeArg(typeof(int), value);
    //    }
    //    public static explicit operator NativeArg(uint value)
    //    {
    //        return new NativeArg(typeof(uint), value);
    //    }
    //    public static explicit operator NativeArg(float value)
    //    {
    //        return new NativeArg(typeof(float), value);
    //    }
    //    public static explicit operator NativeArg(double value)
    //    {
    //        return new NativeArg(typeof(float), (float)value);
    //    }
    //    public static explicit operator NativeArg(bool value)
    //    {
    //        return new NativeArg(typeof(bool), value);
    //    }
    //    public static explicit operator NativeArg(string value)
    //    {
    //        return new NativeArg(typeof(string), value);
    //    }
    //    public static explicit operator NativeArg(Vector2 value)
    //    {
    //        return new NativeArg(typeof(Vector2), value);
    //    }
    //    public static explicit operator NativeArg(Vector3 value)
    //    {
    //        return new NativeArg(typeof(Vector3), value);
    //    }
    //    public static explicit operator NativeArg(Vector4 value)
    //    {
    //        return new NativeArg(typeof(Vector4), value);
    //    }
    //    public static explicit operator NativeArg(Quaternion value)
    //    {
    //        return new NativeArg(typeof(Quaternion), value);
    //    }
    //}

    public static class ManagedNativeCaller
    {

        #region Variables
        private static Dictionary<string, uint> nativeNameToHash;
        private static char[] splitter = { '=' };
        #endregion

        #region Methods
        public static void Init()
        {
            string fileName = Path.Combine(CLR.CLRBridge.IVSDKDotNetDataPath, "natives.txt");

            if (!File.Exists(fileName))
            {
                throw new FileNotFoundException(
                    "Could not initialize the managed native caller because a required file could not be found. " +
                    "Make sure you installed IV-SDK .NET properly.",
                    "natives.txt");
            }

            string[] lines = File.ReadAllLines(fileName);

            nativeNameToHash = new Dictionary<string, uint>(lines.Length);

            for (int i = 0; i < lines.Length; i++)
            {
                string line = lines[i];

                if (string.IsNullOrWhiteSpace(line))
                    continue;
                if (line.StartsWith("//"))
                    continue;

                string[] arr = line.Split(splitter);

                if (arr.Length == 2)
                    nativeNameToHash.Add(arr[0], Convert.ToUInt32(arr[1], 16));
            }
        }

        public static void Call(uint hash, params NativeArg[] args)
        {
            Call<uint>(hash, args);
        }
        public static void Call(eNativeHash hash, params NativeArg[] args)
        {
            Call<uint>((uint)hash, args);
        }
        public static void Call(string name, params NativeArg[] args)
        {
            if (!nativeNameToHash.ContainsKey(name))
            {
                throw new IVSDKDotNet.Exceptions.NativeNotFoundException(name);
            }

            Call<uint>(nativeNameToHash[name], args);
        }
        #endregion

        #region Functions
        public static unsafe T Call<T>(uint hash, params NativeArg[] args)
        {
            T result = default;

            int outArgCount = 0;
            Dictionary<int, IntPtr> outArguments = new Dictionary<int, IntPtr>(args.Length);

            List<IntPtr> allocatedMemoryList = new List<IntPtr>();
            List<GCHandle> allocatedGCHandles = new List<GCHandle>();

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
                            if (arg.IsOutArgument /*&& !arg.IsBeingReused*/)
                            {
                                if (context.PushOut(Marshal.SizeOf(arg.Type), out IntPtr outArg))
                                {
                                    outArguments.Add(i, outArg);
                                    outArgCount++;
                                }
                                continue;
                            }

                            //arg.IsBeingReused = false;

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

                                // TRYING TO GET THIS TO WORK HERE!
                                // TODO: Maybe create a second, temporary IVNativeContext which is only used to store the value (or address?)
                                // of the pushed value. Check again how ScriptHookDotNet does it.

                                //int[] v = new int[] { Convert.ToInt32(arg.Value) };
                                //int size = sizeof(int);
                                //IntPtr hGlobal = Marshal.AllocHGlobal(size);
                                //allocatedMemoryList.Add(hGlobal);

                                //Marshal.WriteInt32(hGlobal, v[0]);

                                ////context.Push(hGlobal);
                                //IVSDKDotNet.Internal.UnsafeMemory.MemoryCopy(
                                //    new IntPtr(context.GetTempStack().ToInt32() + 4 * context.ArgCount),
                                //    hGlobal,
                                //    sizeof(int));
                                //context.ArgCount++;




                                //context.PushOut(Marshal.SizeOf(arg.Value), out IntPtr ptr);
                                //allocatedMemoryList.Add(ptr);
                                //Marshal.WriteInt32(ptr, Convert.ToInt32(arg.Value));

                                //int[] value = new int[] { Convert.ToInt32(arg.Value) };
                                //GCHandle handle = GCHandle.Alloc(value, GCHandleType.Pinned);
                                //allocatedGCHandles.Add(handle);

                                //*(int*)(context.GetTempStack().ToInt32() + 4 * context.ArgCount) = handle.AddrOfPinnedObject().ToPointer();
                                //context.ArgCount++;

                                //IVSDKDotNet.Internal.UnsafeMemory.MemoryCopy(
                                //    new IntPtr(context.GetTempStack().ToInt32() + 4 * context.ArgCount),
                                //    new IntPtr((int*)handle.AddrOfPinnedObject()),
                                //    sizeof(int));
                                //context.ArgCount++;

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
                                string str = Convert.ToString(arg.Value);

                                byte[] bytes = System.Text.Encoding.ASCII.GetBytes(str + "\0"); // Convert to ASCII, add null terminator
                                IntPtr hGlobal = Marshal.AllocHGlobal(bytes.Length);
                                allocatedMemoryList.Add(hGlobal);

                                fixed (byte* ptr = bytes)
                                {
                                    Buffer.MemoryCopy(ptr, (void*)hGlobal, bytes.Length, bytes.Length);
                                }

                                context.Push(hGlobal);
                            }
                        }
                    }

                    // Invoke the native with the given context
                    if (ThreadManager.IsCurrentThreadTheMainThread())
                        IVNativeInvoke.Invoke(hash, context);
                    else
                        ThreadManager.SetCurrentThreadTlsContextToMainThreadContextAndExecute(() => IVNativeInvoke.Invoke(hash, context));

                    // Get the result of the native invokation
                    context.GetResult(out IntPtr resultPtr);
                    result = resultPtr.ToGeneric<T>();

                    // After the native was invoked, we can set the out arguments
                    if (outArgCount != 0)
                    {
                        foreach (KeyValuePair<int, IntPtr> item in outArguments)
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

                for (int i = 0; i < allocatedMemoryList.Count; i++)
                {
                    Marshal.FreeHGlobal(allocatedMemoryList[i]);
                }
                allocatedMemoryList.Clear();
                allocatedMemoryList = null;

                for (int i = 0; i < allocatedGCHandles.Count; i++)
                {
                    allocatedGCHandles[i].Free();
                }
                allocatedGCHandles.Clear();
                allocatedGCHandles = null;
            }

            return result;
        }
        public static T Call<T>(eNativeHash hash, params NativeArg[] args)
        {
            return Call<T>((uint)hash, args);
        }
        public static T Call<T>(string name, params NativeArg[] args)
        {
            if (!nativeNameToHash.ContainsKey(name))
            {
                throw new IVSDKDotNet.Exceptions.NativeNotFoundException(name);
            }

            return Call<T>(nativeNameToHash[name], args);
        }

        public static bool TryGetNativeHashFromString(string name, out uint hash)
        {
            return nativeNameToHash.TryGetValue(name, out hash);
        }
        #endregion

    }
}
