using System;

namespace IVSDKDotNetAPI
{
    public struct Result<T>
    {

        #region Properties
        /// <summary>
        /// The value returned by a API call. If this is null, check the <see cref="Error"/>.
        /// </summary>
        public T Value { get; private set; }

        /// <summary>
        /// If not null, the API call has not succeeded.
        /// </summary>
        public Exception Error { get; private set; }
        #endregion

        #region Constructor
        internal Result(T value, Exception error)
        {
            Value = value;
            Error = error;
        }
        #endregion

        public static Result<T> Empty()
        {
            return default(Result<T>);
        }

    }
}
