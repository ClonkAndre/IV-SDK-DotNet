using System;
using System.Collections.Generic;
using System.IO;

using Newtonsoft.Json;
using Riptide;
using Riptide.Transports.Udp;

using Manager.Classes;
using Manager.Classes.Json;

using IVSDKDotNet.Native;
using static IVSDKDotNet.Native.Natives;

namespace Manager.Managers
{
    public class RemoteConnectionManager : IDisposable
    {

        #region Variables and Properties
        // Lists
        private readonly object lockObj = new object();

        private Dictionary<ushort, string> connectionNames;

        // Server
        private Server server;
        
        private ushort serverPort;
        private ushort maxServerClients;

        // Other
        private bool disposed;
        private bool showNotificationOnConnection;
        private bool allowRemoteReloadScripts;
        private bool allowRemoteLoadScripts;
        private bool allowRemoteAbortScripts;
        private bool allowRemoteNativeFunctionCalls;

        // Properties
        public ushort ServerPort
        {
            get { return serverPort; }
            set { serverPort = value; }
        }
        public ushort MaxServerClients
        {
            get { return maxServerClients; }
            set { maxServerClients = value; }
        }
        public bool ShowNotificationOnConnection
        {
            get { return showNotificationOnConnection; }
            set { showNotificationOnConnection = value; }
        }
        public bool AllowRemoteReloadScripts
        {
            get { return allowRemoteReloadScripts; }
            set { allowRemoteReloadScripts = value; }
        }
        public bool AllowRemoteLoadScripts
        {
            get { return allowRemoteLoadScripts; }
            set { allowRemoteLoadScripts = value; }
        }
        public bool AllowRemoteAbortScripts
        {
            get { return allowRemoteAbortScripts; }
            set { allowRemoteAbortScripts = value; }
        }
        public bool AllowRemoteNativeFunctionCalls
        {
            get { return allowRemoteNativeFunctionCalls; }
            set { allowRemoteNativeFunctionCalls = value; }
        }
        #endregion

        #region Events
        private void Server_HandleConnection(Connection pendingConnection, Message connectMessage)
        {
            try
            {
                // Reject connection if there is no connect message
                if (connectMessage == null)
                {
                    server.Reject(pendingConnection);
                    Main.Instance.Console.PrintDebug(string.Format("[RemoteConnectionManager] (1) Rejected API connection."));
                    return;
                }

                string connectionName = connectMessage.GetString();

                connectionNames.Add(pendingConnection.Id, connectionName);
                Main.Instance.Console.PrintDebug(string.Format("[RemoteConnectionManager] API Connection {0} (ID {1}) added to list.", connectionName, pendingConnection.Id));

                server.Accept(pendingConnection);
            }
            catch (Exception ex)
            {
                Main.Instance.Console.PrintError(string.Format("[RemoteConnectionManager] An error occured while handling API connection. Details: {0}", ex));
                
                server.Reject(pendingConnection);
                Main.Instance.Console.PrintDebug(string.Format("[RemoteConnectionManager] (2) Rejected API connection."));
            }
        }
        private void Server_ClientConnected(object sender, ServerConnectedEventArgs e)
        {
            try
            {
                string connectionAddress = ((UdpConnection)e.Client).RemoteEndPoint.ToString();

                ushort id = (ushort)(e.Client.Id - 1);
                Main.Instance.Console.PrintDebug(string.Format("[RemoteConnectionManager] Trying to get name of API connection from {0}", id));

                if (!connectionNames.ContainsKey(id))
                {
                    server.DisconnectClient(e.Client.Id);
                    Main.Instance.Console.PrintWarning(string.Format("[RemoteConnectionManager] Could not find id {0} in the list of connected API clients! Disconnecting client {1}.", id, connectionAddress));
                    return;
                }

                string connectionName = connectionNames[id];

                // Log connection
                Main.Instance.Console.PrintWarning(string.Format("[RemoteConnectionManager] '{0}' ({1}) has connected to IV-SDK .NET!", connectionName, connectionAddress));

                // Show connect information to user
                if (ShowNotificationOnConnection)
                    Main.Instance.Notification.ShowNotification(NotificationType.Default, DateTime.UtcNow.AddSeconds(6), "New API Connection", string.Format("'{0}' has connected to IV-SDK .NET!", connectionName), null);
            }
            catch (Exception ex)
            {
                Main.Instance.Console.PrintError(string.Format("[RemoteConnectionManager] An error occured in the client connected event. Details: {0}", ex));
            }
        }
        private void Server_ClientDisconnected(object sender, ServerDisconnectedEventArgs e)
        {
            try
            {
                string connectionAddress = ((UdpConnection)e.Client).RemoteEndPoint.ToString();

                ushort id = (ushort)(e.Client.Id - 1);

                if (!connectionNames.ContainsKey(id))
                    return;
                
                string connectionName = connectionNames[id];
                connectionNames.Remove(id);

                // Log connection disconnect
                Main.Instance.Console.PrintWarning(string.Format("[RemoteConnectionManager] '{0}' ({1}) has disconnected from IV-SDK .NET!", connectionName, connectionAddress));
            }
            catch (Exception ex)
            {
                Main.Instance.Console.PrintError(string.Format("[RemoteConnectionManager] An error occured in the client disconnected event. Details: {0}", ex));
            }
        }
        private void Server_MessageReceived(object sender, MessageReceivedEventArgs e)
        {
            try
            {
                switch ((RemoteMessageID)e.MessageId)
                {

                    // Manager Requests
                    case RemoteMessageID.Manager_ReloadScriptsRequest:
                        {
                            if (AllowRemoteReloadScripts)
                            {
                                Main.Instance.LoadScripts();

                                // Send response
                                server.Send(Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_ReloadScriptsResponse).AddBool(true), e.FromConnection);
                            }
                            else
                            {
                                // Send response
                                server.Send(Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_ReloadScriptsResponse).AddBool(false), e.FromConnection);
                            }
                        }
                        break;

                    case RemoteMessageID.Manager_LoadScriptRequest:
                        {

                            // Can load scripts remotely?
                            if (!AllowRemoteLoadScripts)
                            {
                                Message msg = Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_LoadScriptResponse);
                                msg.AddBool(false); // Request failed
                                msg.AddByte(0); // Error ID
                                server.Send(msg, e.FromConnection);
                                return;
                            }

                            // Try to load script
                            try
                            {
                                string scriptFileName = e.Message.GetString();

                                // Try get script by name
                                FoundScript fs = Main.Instance.GetFoundScript(scriptFileName);

                                // Check if script exists or not
                                if (fs == null)
                                    // Not loaded
                                {

                                    // Get path to script file
                                    string scriptPath = string.Format("{0}\\{1}", Main.Instance.ScriptsPath, scriptFileName);

                                    // Load assembly
                                    if (Main.Instance.LoadAssembly(scriptPath, true))
                                    {
                                        server.Send(Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_LoadScriptResponse).AddBool(true), e.FromConnection);
                                        // TODO: Log which API Client has loaded this script.
                                        Main.Instance.Console.Print(string.Format("An API Client has loaded script {0}!", scriptFileName));
                                    }

                                }
                                else
                                    // Loaded
                                {
                                    Message msg = Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_LoadScriptResponse);
                                    msg.AddBool(false); // Request failed
                                    msg.AddByte(1); // Error ID
                                    server.Send(msg, e.FromConnection);
                                }
                            }
                            catch (Exception ex)
                            {
                                Message msg = Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_LoadScriptResponse);
                                msg.AddBool(false); // Request failed
                                msg.AddByte(2); // Error ID
                                msg.AddString(JsonConvert.SerializeObject(ex)); // Error Object
                                server.Send(msg, e.FromConnection);
                            }

                        }
                        break;

                    case RemoteMessageID.Manager_AbortScriptRequest:
                        {

                            // Can abort scripts remotely?
                            if (!AllowRemoteAbortScripts)
                            {
                                Message msg = Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_AbortScriptResponse);
                                msg.AddBool(false); // Request failed
                                msg.AddByte(0); // Error ID
                                server.Send(msg, e.FromConnection);
                                return;
                            }

                            string scriptName = e.Message.GetString();

                            // Try get script by name
                            FoundScript fs = Main.Instance.GetFoundScript(scriptName);

                            if (fs != null)
                                // Script was found
                            {

                                // Abort script
                                fs.Abort(true, true);

                                if (fs.AbortError == null)
                                    // Success
                                {
                                    server.Send(Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_AbortScriptResponse).AddBool(true), e.FromConnection);
                                }
                                else
                                    // Failed
                                {
                                    Message msg = Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_AbortScriptResponse);
                                    msg.AddBool(false); // Request failed
                                    msg.AddByte(1); // Error ID
                                    msg.AddString(JsonConvert.SerializeObject(fs.AbortError)); // Error Object
                                    server.Send(msg, e.FromConnection);
                                }

                                // Remove script from list of active scripts
                                Main.Instance.ActiveScripts.Remove(fs);

                            }
                            else
                                // Script was not found
                            {
                                Message msg = Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_AbortScriptResponse);
                                msg.AddBool(false); // Request failed
                                msg.AddByte(2); // Error ID
                                server.Send(msg, e.FromConnection);
                            }

                        }
                        break;

                    case RemoteMessageID.Manager_GetActiveScriptsInfoRequest:
                        {
                            List<RunningScriptInfo> runningScriptInfo = new List<RunningScriptInfo>();

                            // Populate runningScriptInfo list
                            for (int i = 0; i < Main.Instance.ActiveScripts.Count; i++)
                            {
                                FoundScript fs = Main.Instance.ActiveScripts[i];

                                if (fs == null)
                                    continue;

                                runningScriptInfo.Add(new RunningScriptInfo(fs.Name, fs.FullPath, fs.ID, fs.Script.IVLauncherWorkshopID));
                            }

                            // Send response
                            server.Send(Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_GetActiveScriptsInfoResponse).AddString(JsonConvert.SerializeObject(runningScriptInfo)), e.FromConnection);
                        }
                        break;

                    case RemoteMessageID.Manager_GetActiveScriptsCountRequest:
                        server.Send(Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_GetActiveScriptsCountResponse).AddInt(Main.Instance.GetActiveScriptsCount()), e.FromConnection);
                        break;

                    case RemoteMessageID.Manager_IsScriptRunningRequest:
                        server.Send(Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Manager_IsScriptRunningResponse).AddBool(Main.Instance.IsScriptRunning(e.Message.GetString())), e.FromConnection);
                        break;

                    // Game Requests
                    case RemoteMessageID.Game_GetSessionInfoRequest:
                        {
                            IVSessionInfo info = new IVSessionInfo();
                            info.IsNetworkSession = IS_NETWORK_SESSION();

                            if (info.IsNetworkSession)
                            {
                                uint playerId = GET_PLAYER_ID();

                                info.IsNetworkSessionStarted = NETWORK_IS_SESSION_STARTED();
                                info.IsThisMachineTheServer = IS_THIS_MACHINE_THE_SERVER();
                                info.PlayerCount = GET_NUMBER_OF_PLAYERS();
                                info.GameMode = (IVGameMode)NETWORK_GET_GAME_MODE();
                                info.MaxPlayerCount = NETWORK_GET_MAX_SLOTS();
                                info.Team = GET_PLAYER_TEAM((int)playerId);

                                // Get player score
                                STORE_SCORE(CONVERT_INT_TO_PLAYERINDEX(playerId), out uint score);
                                info.Score = score;

                                // Get all players
                                for (int i = 0; i < info.PlayerCount; i++)
                                {
                                    if (IS_PLAYER_PLAYING(i))
                                        info.Players.Add(GET_PLAYER_NAME(i));
                                }
                            }

                            // Send response
                            server.Send(Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Game_GetSessionInfoResponse).AddString(JsonConvert.SerializeObject(info)), e.FromConnection);
                        }
                        break;

                    case RemoteMessageID.Game_CallNativeRequest:
                        {
                            if (AllowRemoteNativeFunctionCalls)
                            {
                                // Get native call context
                                NativeCallContext context = JsonConvert.DeserializeObject<NativeCallContext>(e.Message.GetString());

                                // Convert all arguments to target type
                                if (context.ArgumentTypes != null)
                                {
                                    for (int i = 0; i < context.ArgumentTypes.Length; i++)
                                    {
                                        // Argument might be used for an out parameter
                                        if (context.Arguments[i] == null)
                                            continue;

                                        Type currentType = context.Arguments[i].GetType();
                                        Type targetType = context.ArgumentTypes[i];

                                        // Only try to convert is there is a missmatch
                                        if (currentType != targetType)
                                        {
                                            // Convert Int64 to Int32
                                            if (currentType == typeof(Int64) && targetType == typeof(Int32))
                                            {
                                                Main.Instance.Console.PrintDebug("Converting Int64 value to Int32");
                                                context.Arguments[i] = Convert.ToInt32(context.Arguments[i]);
                                            }

                                            // Convert Int64 to UInt32
                                            if (currentType == typeof(Int64) && targetType == typeof(UInt32))
                                            {
                                                Main.Instance.Console.PrintDebug("Converting Int64 value to UInt32");
                                                context.Arguments[i] = Convert.ToUInt32(context.Arguments[i]);
                                            }
                                        }
                                    }
                                }

                                // Call native
                                object result = Function.Call<object>(context.Name, context.Arguments);

                                // Return result
                                Message msg = Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Game_CallNativeResponse);
                                msg.AddBool(true);
                                msg.AddString(JsonConvert.SerializeObject(new NativeCallResult(result, context.Arguments)));
                                server.Send(msg, e.FromConnection);
                            }
                            else
                            {
                                // Send response
                                server.Send(Message.Create(MessageSendMode.Unreliable, RemoteMessageID.Game_CallNativeResponse).AddBool(false), e.FromConnection);
                            }
                        }
                        break;

                }
            }
            catch (Exception ex)
            {
                Main.Instance.Console.PrintError(string.Format("[RemoteConnectionManager] Error while handling message {0}! Details: {1}", e.MessageId, ex));
            }
        }
        #endregion

        #region Constructor
        public RemoteConnectionManager()
        {
            // Lists
            connectionNames = new Dictionary<ushort, string>();

            // Server
            server = new Server();
            server.TimeoutTime = 30000;
            server.HandleConnection     += Server_HandleConnection;
            server.ClientConnected      += Server_ClientConnected;
            server.ClientDisconnected   += Server_ClientDisconnected;
            server.MessageReceived      += Server_MessageReceived;
        }
        #endregion

        #region Methods
        public void Dispose()
        {
            if (disposed)
                return;

            // Do cleanup
            if (server != null)
            {
                server.HandleConnection -= Server_HandleConnection;
                server.MessageReceived  -= Server_MessageReceived;

                if (server.IsRunning)
                {
                    server.Stop();
                    Main.Instance.Console.Print("[RemoteConnectionManager] Stopped.");
                }
            }

            connectionNames.Clear();

            disposed = true;
        }

        public void Start()
        {
            if (disposed)
                return;

            // Start server
            server.Start(ServerPort, MaxServerClients);

            // Log message if server got started
            if (server.IsRunning)
                Main.Instance.Console.Print("[RemoteConnectionManager] Started.");
        }
        public void Update()
        {
            if (disposed)
                return;

            server.Update();
        }
        #endregion

    }
}
