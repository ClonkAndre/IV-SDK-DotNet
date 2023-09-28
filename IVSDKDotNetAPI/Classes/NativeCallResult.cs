using System;
using System.Numerics;

namespace IVSDKDotNetAPI.Classes
{
    public class NativeCallResult
    {

        #region Variables
        public object Result;
        public object[] Arguments;
        #endregion

        #region Constructor
        internal NativeCallResult()
        {

        }
        #endregion

        /// <summary>
        /// Gets the result of the called native function, and converts it to the expected return type.
        /// </summary>
        /// <typeparam name="T">The expected return type of the called native function.</typeparam>
        /// <returns>The converted result of the called native function.</returns>
        //public T GetResult<T>()
        //{
        //    if (Result == null)
        //        return default(T);

        //    return (T)Result;
        //}

        public string GetString()
        {
            if (Result.GetType() == typeof(string))
                return Result.ToString();

            return null;
        }

        public int GetInt()
        {
            return Convert.ToInt32(Result);
        }

        public uint GetUInt()
        {
            return Convert.ToUInt32(Result);
        }

        public float GetFloat()
        {
            return Convert.ToSingle(Result);
        }

    }
}
