using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;

using Newtonsoft.Json;
using Riptide;

using IVSDKDotNetAPI.Classes;

namespace IVSDKDotNetAPI.IV
{
    /// <summary>
    /// Things related to the IV-SDK .NET Manager
    /// </summary>
    public class Manager : APIEndPointBase
    {

        #region Events
        internal override void RemoteClient_MessageReceived(object sender, MessageReceivedEventArgs e)
        {
            switch ((RemoteMessageID)e.MessageId)
            {

                // Manager
                case RemoteMessageID.Manager_ReloadScriptsResponse:
                    {
                        bool result = e.Message.GetBool();
                        if (result)
                            PendingResponses[RemoteMessageID.Manager_ReloadScriptsRequest] = new Result<bool>(result, null);
                        else
                            PendingResponses[RemoteMessageID.Manager_ReloadScriptsRequest] = new Result<bool>(result, new APIExceptions.FeatureDisabledByUserException());
                    }
                    break;

                case RemoteMessageID.Manager_LoadScriptResponse:
                    {

                        bool success = e.Message.GetBool();

                        if (success)
                        {
                            PendingResponses[RemoteMessageID.Manager_LoadScriptRequest] = new Result<byte>(1, null);
                        }
                        else
                        {
                            byte errorId = e.Message.GetByte();

                            switch (errorId)
                            {
                                case 0: // Remote loading of scripts is disabled
                                    PendingResponses[RemoteMessageID.Manager_LoadScriptRequest] = new Result<byte>(2, null);
                                    break;
                                case 1: // Script already loaded
                                    PendingResponses[RemoteMessageID.Manager_LoadScriptRequest] = new Result<byte>(3, null);
                                    break;
                                case 2: // Error while loading script

                                    Exception error = JsonConvert.DeserializeObject<Exception>(e.Message.GetString());
                                    PendingResponses[RemoteMessageID.Manager_LoadScriptRequest] = new Result<byte>(4, error);

                                    break;
                            }
                        }

                    }
                    break;

                case RemoteMessageID.Manager_AbortScriptResponse:
                    {
                        bool success = e.Message.GetBool();

                        if (success)
                        {
                            PendingResponses[RemoteMessageID.Manager_AbortScriptRequest] = new Result<byte>(1, null);
                        }
                        else
                        {
                            byte errorId = e.Message.GetByte();

                            switch (errorId)
                            {
                                case 0: // Remote aborting of scripts is disabled
                                    PendingResponses[RemoteMessageID.Manager_AbortScriptRequest] = new Result<byte>(2, null);
                                    break;
                                case 1: // Failed

                                    Exception error = JsonConvert.DeserializeObject<Exception>(e.Message.GetString());
                                    PendingResponses[RemoteMessageID.Manager_AbortScriptRequest] = new Result<byte>(4, error);

                                    break;
                                case 2: // Script was not found
                                    PendingResponses[RemoteMessageID.Manager_AbortScriptRequest] = new Result<byte>(3, null);
                                    break;
                            }
                        }
                    }
                    break;

                case RemoteMessageID.Manager_GetActiveScriptsInfoResponse:
                    PendingResponses[RemoteMessageID.Manager_GetActiveScriptsInfoRequest] = new Result<List<RunningScriptInfo>>(JsonConvert.DeserializeObject<List<RunningScriptInfo>>(e.Message.GetString()), null);
                    break;

                case RemoteMessageID.Manager_GetActiveScriptsCountResponse:
                    PendingResponses[RemoteMessageID.Manager_GetActiveScriptsCountRequest] = new Result<int>(e.Message.GetInt(), null);
                    break;

                case RemoteMessageID.Manager_IsScriptRunningResponse:
                    PendingResponses[RemoteMessageID.Manager_IsScriptRunningRequest] = new Result<bool>(e.Message.GetBool(), null);
                    break;

                case RemoteMessageID.Manager_SendScriptCommandResponse:
                    {
                        bool success = e.Message.GetBool();

                        if (success)
                        {
                            object result = JsonConvert.DeserializeObject(e.Message.GetString());
                            PendingResponses[RemoteMessageID.Manager_SendScriptCommandRequest] = new Result<object>(result, null);
                        }
                        else
                        {
                            byte errorId = e.Message.GetByte();

                            switch (errorId)
                            {
                                case 0: // Invalid ID
                                    PendingResponses[RemoteMessageID.Manager_SendScriptCommandRequest] = new Result<object>(null, new Exception("Invalid ID!"));
                                    break;
                                case 1: // Script not found
                                    PendingResponses[RemoteMessageID.Manager_SendScriptCommandRequest] = new Result<object>(null, new Exception("Script not found!"));
                                    break;
                                case 2: // SendScriptCommand failed
                                    PendingResponses[RemoteMessageID.Manager_SendScriptCommandRequest] = new Result<object>(null, new Exception("SendScriptCommand failed!"));
                                    break;
                            }
                        }
                    }
                    break;

                case RemoteMessageID.Manager_GetPreferencesResponse:
                    PendingResponses[RemoteMessageID.Manager_GetPreferencesRequest] = new Result<ManagerApiPreferences>(JsonConvert.DeserializeObject<ManagerApiPreferences>(e.Message.GetString()), null);
                    break;

            }
        }
        #endregion

        #region Constructor
        internal Manager(Connection instance) : base(instance)
        {

        }
        #endregion

        #region Functions
        /// <summary>
        /// Gets the IV-SDK .NET Manager API Preferences.
        /// </summary>
        /// <returns>If successful, the IV-SDK .NET API Preferences is returned.</returns>
        public Task<Result<ManagerApiPreferences>> GetPreferences()
        {
            RemoteMessageID messageID = RemoteMessageID.Manager_GetPreferencesRequest;

            if (!ConnectionInstance.IsConnected)
                return Task.FromResult(new Result<ManagerApiPreferences>(null, new Exception("There is no connection to the IV-SDK .NET Manager.")));

            // If request was already made, return
            if (PendingResponses.ContainsKey(messageID))
                return Task.FromResult(new Result<ManagerApiPreferences>(null, new APIExceptions.RequestAlreadyMadeException("A request to get the preferences was already made.")));

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

                // Return result
                if (responseObject == null)
                    return Result<ManagerApiPreferences>.Empty();

                return (Result<ManagerApiPreferences>)responseObject;
            });
        }

        /// <summary>
        /// Tells the IV-SDK .NET Manager to reload the scripts.
        /// <para>Note: If the user turned off remote reloading of scripts, this call fails.</para>
        /// </summary>
        /// <returns>True if this call was successful, otherwise false.</returns>
        public Task<Result<bool>> ReloadScripts()
        {
            RemoteMessageID messageID = RemoteMessageID.Manager_ReloadScriptsRequest;

            if (!ConnectionInstance.IsConnected)
                return Task.FromResult(new Result<bool>(false, new Exception("There is no connection to the IV-SDK .NET Manager.")));

            // If request was already made, return
            if (PendingResponses.ContainsKey(messageID))
                return Task.FromResult(new Result<bool>(false, new APIExceptions.RequestAlreadyMadeException("A request to reload the scripts was already made.")));

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

                // Return result
                if (responseObject == null)
                    return Result<bool>.Empty();

                return (Result<bool>)responseObject;
            });
        }

        /// <summary>
        /// Tells the IV-SDK .NET Manager to load a single script.
        /// </summary>
        /// <returns>Returns <b>0</b> if no request was made, <b>1</b> if the request was successful, <b>2</b> the user has disabled the remote loading of scripts, <b>3</b> the script is already loaded and <b>4</b> if there is an error occured while trying to load script.</returns>
        public Task<Result<byte>> LoadScript(string scriptFileName)
        {
            RemoteMessageID messageID = RemoteMessageID.Manager_LoadScriptRequest;

            if (!ConnectionInstance.IsConnected)
                return Task.FromResult(new Result<byte>(0, new Exception("There is no connection to the IV-SDK .NET Manager.")));

            // Dummy checks
            if (string.IsNullOrWhiteSpace(scriptFileName))
                return Task.FromResult(new Result<byte>(0, new Exception("Argument cannot be null or whitespace!")));

            // If request was already made, return
            if (PendingResponses.ContainsKey(messageID))
                return Task.FromResult(new Result<byte>(0, new APIExceptions.RequestAlreadyMadeException("A request to load a single script was already made.")));

            // Add to pending responses and message timeouts list
            PendingResponses.Add(messageID, null);
            ConnectionInstance.MessageTimeouts.Add(messageID, DateTime.UtcNow);

            // Send request
            Message msg = Message.Create(MessageSendMode.Unreliable, messageID);
            msg.AddString(scriptFileName);
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

                // Return result
                if (responseObject == null)
                    return Result<byte>.Empty();

                return (Result<byte>)responseObject;
            });
        }

        /// <summary>
        /// Tells the IV-SDK .NET Manager to abort a single script.
        /// </summary>
        /// <returns>Returns <b>0</b> if no request was made, <b>1</b> if the request was successful, <b>2</b> the user has disabled the remote aborting of scripts, <b>3</b> if the script was not found and <b>4</b> if there is an error occured while trying to abort script.</returns>
        public Task<Result<byte>> AbortScript(string scriptFileName)
        {
            RemoteMessageID messageID = RemoteMessageID.Manager_AbortScriptRequest;

            if (!ConnectionInstance.IsConnected)
                return Task.FromResult(new Result<byte>(0, new Exception("There is no connection to the IV-SDK .NET Manager.")));

            // Dummy checks
            if (string.IsNullOrWhiteSpace(scriptFileName))
                return Task.FromResult(new Result<byte>(0, new Exception("Argument cannot be null or whitespace!")));

            // If request was already made, return
            if (PendingResponses.ContainsKey(messageID))
                return Task.FromResult(new Result<byte>(0, new APIExceptions.RequestAlreadyMadeException("A request to abort a single script was already made.")));

            // Add to pending responses and message timeouts list
            PendingResponses.Add(messageID, null);
            ConnectionInstance.MessageTimeouts.Add(messageID, DateTime.UtcNow);

            // Send request
            Message msg = Message.Create(MessageSendMode.Unreliable, messageID);
            msg.AddString(scriptFileName);
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

                // Return result
                if (responseObject == null)
                    return Result<byte>.Empty();

                return (Result<byte>)responseObject;
            });
        }

        /// <summary>
        /// Gets a list of running IV-SDK .NET scripts.
        /// </summary>
        /// <returns>A list of running IV-SDK .NET scripts.</returns>
        public Task<Result<List<RunningScriptInfo>>> GetRunningScriptsInfo()
        {
            RemoteMessageID messageID = RemoteMessageID.Manager_GetActiveScriptsInfoRequest;

            if (!ConnectionInstance.IsConnected)
                return Task.FromResult(new Result<List<RunningScriptInfo>>(null, new Exception("There is no connection to the IV-SDK .NET Manager.")));

            // If request was already made, return
            if (PendingResponses.ContainsKey(messageID))
                return Task.FromResult(new Result<List<RunningScriptInfo>>(null, new APIExceptions.RequestAlreadyMadeException("A request to get the currently running scripts was already made.")));

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

                // Remove message from pending responses list
                PendingResponses.Remove(messageID);
                ConnectionInstance.MessageTimeouts.Remove(messageID);

                // Return result
                if (responseObject == null)
                    return Result<List<RunningScriptInfo>>.Empty();

                return (Result<List<RunningScriptInfo>>)responseObject;
            });
        }

        /// <summary>
        /// Gets how many IV-SDK .NET scripts are currently running.
        /// </summary>
        /// <returns>The number of IV-SDK .NET scripts that are currently running.</returns>
        public Task<Result<int>> GetActiveScriptsCount()
        {
            RemoteMessageID messageID = RemoteMessageID.Manager_GetActiveScriptsCountRequest;

            if (!ConnectionInstance.IsConnected)
                return Task.FromResult(new Result<int>(0, new Exception("There is no connection to the IV-SDK .NET Manager.")));

            // If request was already made, return
            if (PendingResponses.ContainsKey(messageID))
                return Task.FromResult(new Result<int>(0, new APIExceptions.RequestAlreadyMadeException("A request to get the currently running scripts count was already made.")));

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

                // Remove message from pending responses list
                PendingResponses.Remove(messageID);
                ConnectionInstance.MessageTimeouts.Remove(messageID);

                // Return result
                if (responseObject == null)
                    return Result<int>.Empty();

                return (Result<int>)responseObject;
            });
        }

        /// <summary>
        /// Gets if there is a script running with the given <paramref name="name"/>.
        /// </summary>
        /// <param name="name">The name of the script to check for.</param>
        /// <returns>True if the script with the given name was found and is running, otherwise false.</returns>
        public Task<Result<bool>> IsScriptRunning(string name)
        {
            RemoteMessageID messageID = RemoteMessageID.Manager_IsScriptRunningRequest;

            if (!ConnectionInstance.IsConnected)
                return Task.FromResult(new Result<bool>(false, new Exception("There is no connection to the IV-SDK .NET Manager.")));

            // Dummy checks
            if (string.IsNullOrWhiteSpace(name))
                return Task.FromResult(new Result<bool>(false, new Exception("Argument cannot be null or whitespace!")));

            // If request was already made, return
            if (PendingResponses.ContainsKey(messageID))
                return Task.FromResult(new Result<bool>(false, new APIExceptions.RequestAlreadyMadeException("A request to check if the script is running was already made.")));

            // Add to pending responses and message timeouts list
            PendingResponses.Add(messageID, null);
            ConnectionInstance.MessageTimeouts.Add(messageID, DateTime.UtcNow);

            // Send request
            Send(Message.Create(MessageSendMode.Unreliable, messageID).AddString(name));

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

                // Return result
                if (responseObject == null)
                    return Result<bool>.Empty();

                return (Result<bool>)responseObject;
            });
        }

        /// <summary>
        /// Sends a script command to the script with the given <paramref name="id"/>
        /// </summary>
        /// <param name="id">The ID or the Name of the Script that should receive this command.</param>
        /// <param name="command">The command that should be sent to the Script.</param>
        /// <returns>The result <see cref="object"/> the script returned.</returns>
        public Task<Result<object>> SendScriptCommand(string script, string command)
        {
            RemoteMessageID messageID = RemoteMessageID.Manager_SendScriptCommandRequest;

            if (!ConnectionInstance.IsConnected)
                return Task.FromResult(new Result<object>(null, new Exception("There is no connection to the IV-SDK .NET Manager.")));

            // Dummy checks
            if (string.IsNullOrWhiteSpace(script))
                return Task.FromResult(new Result<object>(null, new Exception("script cannot be null or empty!")));
            if (string.IsNullOrWhiteSpace(command))
                return Task.FromResult(new Result<object>(null, new Exception("command cannot be null or empty!")));

            // If request was already made, return
            if (PendingResponses.ContainsKey(messageID))
                return Task.FromResult(new Result<object>(null, new APIExceptions.RequestAlreadyMadeException("A request to check if the script is running was already made.")));

            // Add to pending responses and message timeouts list
            PendingResponses.Add(messageID, null);
            ConnectionInstance.MessageTimeouts.Add(messageID, DateTime.UtcNow);

            // Send request
            Send(Message.Create(MessageSendMode.Unreliable, messageID).AddString(script).AddString(command));

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

                // Return result
                if (responseObject == null)
                    return Result<object>.Empty();

                return (Result<object>)responseObject;
            });
        }
        #endregion

    }
}
