using System.Collections.Generic;

using Riptide;

namespace IVSDKDotNetAPI
{
    public abstract class APIEndPointBase
    {

        #region Variables
        internal Connection ConnectionInstance;
        internal Dictionary<RemoteMessageID, object> PendingResponses;
        #endregion

        #region Events
        internal virtual void RemoteClient_MessageReceived(object sender, MessageReceivedEventArgs e)
        {

        }
        #endregion

        #region Constructor
        internal APIEndPointBase(Connection instance)
        {
            // Lists
            PendingResponses = new Dictionary<RemoteMessageID, object>();

            // Reference
            ConnectionInstance = instance;
            ConnectionInstance.RemoteClient.MessageReceived += RemoteClient_MessageReceived;
        }
        #endregion

        #region Methods
        internal void Cleanup()
        {
            PendingResponses.Clear();
        }

        internal void Send(Message msg)
        {
            ConnectionInstance.RemoteClient.Send(msg);
        }
        #endregion

    }
}
