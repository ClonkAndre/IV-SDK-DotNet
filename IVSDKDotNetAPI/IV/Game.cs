using System;
using System.Threading;
using System.Threading.Tasks;

using Riptide;
using Newtonsoft.Json;

using IVSDKDotNetAPI.Classes;

namespace IVSDKDotNetAPI.IV
{
    /// <summary>
    /// Things related to GTA IV
    /// </summary>
    public class Game : APIEndPointBase
    {

        #region Events
        internal override void RemoteClient_MessageReceived(object sender, MessageReceivedEventArgs e)
        {
            switch ((RemoteMessageID)e.MessageId)
            {
                // Game
                case RemoteMessageID.Game_GetSessionInfoResponse:
                    PendingResponses[RemoteMessageID.Game_GetSessionInfoRequest] = new Result<IVSessionInfo>(JsonConvert.DeserializeObject<IVSessionInfo>(e.Message.GetString()), null);
                    break;

                case RemoteMessageID.Game_CallNativeResponse:
                    {
                        bool result = e.Message.GetBool();
                        if (result)
                            PendingResponses[RemoteMessageID.Game_CallNativeRequest] = new Result<NativeCallResult>(JsonConvert.DeserializeObject<NativeCallResult>(e.Message.GetString()), null);
                        else
                            PendingResponses[RemoteMessageID.Game_CallNativeRequest] = new Result<NativeCallResult>(null, new APIExceptions.FeatureDisabledByUserException());
                    }
                    break;
            }
        }
        #endregion

        #region Constructor
        public Game(Connection instance) : base(instance)
        {

        }
        #endregion

        #region Functions
        /// <summary>
        /// Gets the current session info of GTA IV.
        /// <para>This includes: The current game mode, the player count, the current score, the current players and more.</para>
        /// </summary>
        /// <returns>If successful, a <see cref="IVSessionInfo"/> object is returned.</returns>
        public Task<Result<IVSessionInfo>> GetSessionInfo()
        {
            RemoteMessageID messageID = RemoteMessageID.Game_GetSessionInfoRequest;

            if (!ConnectionInstance.IsConnected)
                return Task.FromResult(new Result<IVSessionInfo>(null, new Exception("There is no connection to the IV-SDK .NET Manager.")));

            // If request was already made, return
            if (PendingResponses.ContainsKey(messageID))
                return Task.FromResult(new Result<IVSessionInfo>(null, new APIExceptions.RequestAlreadyMadeException("A request to get the current session info was already made.")));

            // Add to pending responses and message timeouts list
            PendingResponses.Add(messageID, null);
            ConnectionInstance.MessageTimeouts.Add(messageID, DateTime.UtcNow);

            // Send request
            Send(Message.Create(MessageSendMode.Unreliable, messageID));

            // Wait for response
            return Task.Run(() =>
            {

                object responseObject = PendingResponses[messageID];

                // Wait for result or abort if not connected anymore
                while (responseObject == null)
                {
                    if (!ConnectionInstance.IsConnected)
                        break;

                    // See if object is still null
                    responseObject = PendingResponses[messageID];

                    if (responseObject != null)
                        break;

                    // Check timeout
                    if (ConnectionInstance.MessageTimeouts.ContainsKey(messageID))
                    {
                        DateTime dt = ConnectionInstance.MessageTimeouts[messageID];

                        // If after 10 seconds no response arrived, break from loop and return default result
                        if (DateTime.UtcNow > dt.AddSeconds(10))
                            break;
                    }

                    // Wait
                    Thread.Sleep(20);
                }

                // Remove message from pending responses and message timeouts list
                PendingResponses.Remove(messageID);
                ConnectionInstance.MessageTimeouts.Remove(messageID);

                // Return the result
                if (responseObject == null)
                    return Result<IVSessionInfo>.Empty();

                return (Result<IVSessionInfo>)responseObject;
            });
        }

        /// <summary>
        /// Calls a native function of GTA IV by its name and returns the result of it (If there is something to be returned by the called native function).
        /// <para>Note: If the user turned off remote calling native functions, this call fails.</para>
        /// </summary>
        /// <param name="name">The name of the native function to call.</param>
        /// <param name="args">The native function arguments.</param>
        /// <returns>If successful, a <see cref="NativeCallResult"/> object is returned.</returns>
        public Task<Result<NativeCallResult>> CallNativeFunction(string name, params object[] args)
        {
            RemoteMessageID messageID = RemoteMessageID.Game_CallNativeRequest;

            if (!ConnectionInstance.IsConnected)
                return Task.FromResult(new Result<NativeCallResult>(null, new Exception("There is no connection to the IV-SDK .NET Manager.")));

            // Dummy checks
            if (string.IsNullOrWhiteSpace(name))
                return Task.FromResult(new Result<NativeCallResult>(null, new Exception("Invalid native function name!")));

            // If request was already made, return
            if (PendingResponses.ContainsKey(messageID))
                return Task.FromResult(new Result<NativeCallResult>(null, new APIExceptions.RequestAlreadyMadeException("A request to call a native function was already made.")));

            // Add to pending responses and message timeouts list
            PendingResponses.Add(messageID, null);
            ConnectionInstance.MessageTimeouts.Add(messageID, DateTime.UtcNow);

            // Send request
            Message msg = Message.Create(MessageSendMode.Unreliable, messageID);
            msg.AddString(JsonConvert.SerializeObject(new NativeCallContext(name, args)));
            Send(msg);

            // Wait for response
            return Task.Run(() =>
            {

                object responseObject = PendingResponses[messageID];

                // Wait for result or abort if not connected anymore
                while (responseObject == null)
                {
                    if (!ConnectionInstance.IsConnected)
                        break;

                    // See if object is still null
                    responseObject = PendingResponses[messageID];

                    if (responseObject != null)
                        break;

                    // Check timeout
                    if (ConnectionInstance.MessageTimeouts.ContainsKey(messageID))
                    {
                        DateTime dt = ConnectionInstance.MessageTimeouts[messageID];

                        // If after 10 seconds no response arrived, break from loop and return default result
                        if (DateTime.UtcNow > dt.AddSeconds(10))
                            break;
                    }

                    // Wait
                    Thread.Sleep(20);
                }

                // Remove message from pending responses and message timeouts list
                PendingResponses.Remove(messageID);
                ConnectionInstance.MessageTimeouts.Remove(messageID);

                if (responseObject == null)
                    return Result<NativeCallResult>.Empty();

                // Return the result
                return (Result<NativeCallResult>)responseObject;
            });
        }
        #endregion

    }
}
