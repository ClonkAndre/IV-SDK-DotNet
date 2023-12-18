using System;
using System.Collections.Generic;
using System.Timers;

using Riptide;

using IVSDKDotNetAPI.IV;

namespace IVSDKDotNetAPI
{
    /// <summary>
    /// Class to establish a connection to the IV-SDK .NET Manager.
    /// </summary>
    public class Connection : IDisposable
    {

        #region Variables and Properties
        // Variables
        internal Client RemoteClient;
        internal Dictionary<RemoteMessageID, DateTime> MessageTimeouts;
        private Timer runCallbackTimer;

        private bool disposed;

        private Manager manager;
        private Game game;

        // Properties
        /// <summary>
        /// Gets if this <see cref="Connection"/> is connected with the IV-SDK .NET Manager.
        /// </summary>
        public bool IsConnected
        {
            get
            {
                if (disposed)
                    return false;
                if (RemoteClient == null)
                    return false;

                return RemoteClient.IsConnected;
            }
        }

        /// <summary>
        /// Gives you access to the IV-SDK .NET Manager.
        /// </summary>
        public Manager Manager
        {
            get { return manager; }
            private set { manager = value; }
        }
        /// <summary>
        /// Giyes you access to GTA IV things.
        /// </summary>
        public Game Game
        {
            get { return game; }
            private set { game = value; }
        }
        #endregion

        #region Events and Delegates

        public delegate void ConnectionFailedDelegate(object sender, string reason);

        // Custom
        public event EventHandler Connected;
        public event ConnectionFailedDelegate ConnectionFailed;
        public event EventHandler Disconnected;

        // Local
        private void RemoteClient_Connected(object sender, EventArgs e)
        {
            Connected?.Invoke(this, e);
        }
        private void RemoteClient_ConnectionFailed(object sender, ConnectionFailedEventArgs e)
        {
            if (runCallbackTimer != null)
                runCallbackTimer.Stop();
            
            if (e.Message != null)
            {
                string reason = e.Message.GetString();
                if (!string.IsNullOrWhiteSpace(reason))
                    ConnectionFailed?.Invoke(this, reason);
                else
                    ConnectionFailed?.Invoke(this, "No reason provided.");
            }
            else
                ConnectionFailed?.Invoke(this, "No reason provided.");
        }
        private void RemoteClient_Disconnected(object sender, DisconnectedEventArgs e)
        {
            if (runCallbackTimer != null)
                runCallbackTimer.Stop();

            Disconnected?.Invoke(this, e);
        }

        // Timer
        private void RunCallbackTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            RunCallbacks();
        }

        #endregion

        #region Constructor
        /// <summary>
        /// Creates a new instance of the <see cref="Connection"/> class.
        /// </summary>
        /// <param name="runAutomaticCallbacks">If set to false, you need to manually call the <see cref="RunCallbacks"/> method in a loop of some sort to keep the API running.</param>
        public Connection(bool runAutomaticCallbacks = true)
        {
            // Client
            RemoteClient = new Client();
            RemoteClient.TimeoutTime = 30000;
            RemoteClient.Connected          += RemoteClient_Connected;
            RemoteClient.ConnectionFailed   += RemoteClient_ConnectionFailed;
            RemoteClient.Disconnected       += RemoteClient_Disconnected;

            // Lists
            MessageTimeouts = new Dictionary<RemoteMessageID, DateTime>();

            // Timer
            if (runAutomaticCallbacks)
            {
                runCallbackTimer = new Timer(100);
                runCallbackTimer.Elapsed += RunCallbackTimer_Elapsed;
            }

            // Create endpoints
            Manager = new Manager(this);
            Game = new Game(this);
        }
        #endregion

        #region Methods
        /// <summary>
        /// Shuts down the connection to the IV-SDK .NET Manager and cleans up everything.
        /// </summary>
        public void Dispose()
        {
            if (disposed)
                return;

            // Client
            RemoteClient.Connected          -= RemoteClient_Connected;
            RemoteClient.ConnectionFailed   -= RemoteClient_ConnectionFailed;
            RemoteClient.Disconnected       -= RemoteClient_Disconnected;
            RemoteClient.Disconnect();
            RemoteClient = null;

            // Timer
            if (runCallbackTimer != null)
            {
                runCallbackTimer.Elapsed -= RunCallbackTimer_Elapsed;
                runCallbackTimer.Stop();
                runCallbackTimer.Dispose();
                runCallbackTimer = null;
            }

            // Lists
            MessageTimeouts.Clear();

            // Cleanup endpoints
            Manager.Cleanup();
            Manager = null;
            Game.Cleanup();
            Game = null;

            disposed = true;
        }

        /// <summary>
        /// This needs to be frequently called in order for this API to process all incoming messages.
        /// </summary>
        public void RunCallbacks()
        {
            if (disposed)
                return;
            if (RemoteClient == null)
                return;

            RemoteClient.Update();
        }

        /// <summary>
        /// Disconnects this <see cref="Connection"/> from the IV-SDK .NET Manager.
        /// </summary>
        public void Disconnect()
        {
            if (disposed)
                return;

            RemoteClient.Disconnect();
        }
        #endregion

        #region Functions
        /// <summary>
        /// Tries to connect to the IV-SDK .NET Manager.
        /// </summary>
        /// <param name="port">The port the IV-SDK .NET Manager is running on. This might vary if the user decided to override the port.</param>
        /// <returns>True if a connection attempt will be made. False if something went wrong while attempting to make a connection attempt.</returns>
        public bool Connect(ushort port = 57315)
        {
            if (disposed)
                return false;
            if (RemoteClient.IsConnected)
                return false;

            // Start callback timer
            if (runCallbackTimer != null)
                runCallbackTimer.Start();

            // Create connect message
            Message connectMessage = Message.Create();
            connectMessage.AddString(Helper.GetNameOfCallingAssembly());

            // Try to connect to the Manager
            return RemoteClient.Connect(string.Format("127.0.0.1:{0}", port), 5, 0, connectMessage);
        }
        #endregion

    }
}
