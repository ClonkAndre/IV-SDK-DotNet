using System;

namespace IVSDKDotNetAPI
{
    /// <summary>
    /// All exceptions that can occur in this API
    /// </summary>
    public class APIExceptions
    {

        [Serializable]
        public class RequestAlreadyMadeException : Exception
        {
            internal RequestAlreadyMadeException() { }
            internal RequestAlreadyMadeException(string message) : base(message) { }
            internal RequestAlreadyMadeException(string message, Exception inner) : base(message, inner) { }
        }

        [Serializable]
        public class FeatureDisabledByUserException : Exception
        {
            internal FeatureDisabledByUserException() : base("This feature got disabled by the user.") { }
            internal FeatureDisabledByUserException(string message) : base(message) { }
            internal FeatureDisabledByUserException(string message, Exception inner) : base(message, inner) { }

        }

    }
}
