using System;

namespace Manager.Classes.Threading
{
    internal class ThreadData
    {

        #region Variables
        public int ThreadID;
        public UIntPtr TlsContext;
        #endregion

        #region Constructor
        public ThreadData(int threadId, UIntPtr tlsContext)
        {
            ThreadID = threadId;
            TlsContext = tlsContext;
        }
        #endregion

        public void UpdateTlsContext(UIntPtr newContext)
        {
            TlsContext = newContext;
        }

    }
}
