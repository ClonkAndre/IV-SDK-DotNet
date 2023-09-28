using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using IVSDKDotNetAPI;
using IVSDKDotNetAPI.Classes;

namespace APITest
{
    public partial class Form1 : Form
    {

        #region Variables
        private Connection connection;
        #endregion

        #region Methods
        private void Invoke(Action a)
        {
            if (InvokeRequired)
                Invoke(new MethodInvoker(a));
            else
                a();
        }
        private void LogMessage(string text, params object[] args)
        {
            Invoke(() => logLB.Items.Add(string.Format(text, args)));
        }
        #endregion

        #region Events
        private void Connection_ConnectionFailed(object sender, string reason)
        {
            LogMessage("Connection failed! Reason: {0}", reason);
        }
        private void Connection_Disconnected(object sender, EventArgs e)
        {
            LogMessage("Disconnected!");
        }
        private void Connection_Connected(object sender, EventArgs e)
        {
            LogMessage("Connected!");
        }
        #endregion

        #region Constructor
        public Form1()
        {
            InitializeComponent();

            connection = new Connection();
            connection.Connected += Connection_Connected;
            connection.Disconnected += Connection_Disconnected;
            connection.ConnectionFailed += Connection_ConnectionFailed;
        }
        #endregion

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            connection.Dispose();
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void testButton_Click(object sender, EventArgs e)
        {

        }
        private void testButton2_Click(object sender, EventArgs e)
        {

        }

        // Connection
        private void connectButton_Click(object sender, EventArgs e)
        {
            connection.Connect();
        }
        private void disconnectButton_Click(object sender, EventArgs e)
        {
            connection.Disconnect();
        }

        // Manager
        private void ReloadScriptsButton_Click(object sender, EventArgs e)
        {
            connection.Manager.ReloadScripts().ContinueWith(x =>
            {
                if (x.Result.Value)
                    LogMessage("ReloadScripts success!");
                else
                    LogMessage("ReloadScripts failed. Details: {0}", x.Result.Error.Message);
            });
        }
        private void getRunningScriptsButton_Click(object sender, EventArgs e)
        {
            connection.Manager.GetRunningScriptsInfo().ContinueWith(x =>
            {
                List<RunningScriptInfo> scripts = x.Result.Value;

                if (scripts.Count == 0)
                {
                    LogMessage("There are no scripts running.");
                    return;
                }

                for (int i = 0; i < scripts.Count; i++)
                {
                    RunningScriptInfo script = scripts[i];
                    LogMessage("Name: {0}, ScriptID: {1}, IVLauncherWorkshopID: {2}, FullPath: {3}", script.Name, script.ScriptID, script.IVLauncherWorkshopID, script.FullPath);
                }
            });
        }
        private void getActiveScriptsCountButton_Click(object sender, EventArgs e)
        {
            connection.Manager.GetActiveScriptsCount().ContinueWith(x =>
            {
                LogMessage("Active scripts count: {0}", x.Result.Value);
            });
        }
        private void button2_Click(object sender, EventArgs e)
        {
            connection.Manager.IsScriptRunning(scriptNameTextbox.Text).ContinueWith(x =>
            {
                LogMessage("Is script running: {0}", x.Result.Value);
            });
        }
        private void loadScriptButton_Click(object sender, EventArgs e)
        {
            connection.Manager.LoadScript(scriptNameTextbox.Text).ContinueWith(x =>
            {
                Result<byte> result = x.Result;

                switch (result.Value)
                {
                    case 0:
                        LogMessage("No attempt was made to load script!");
                        break;
                    case 1:
                        LogMessage("Script was loaded!");
                        break;
                    case 2:
                        LogMessage("User has disabled remote loading of scripts!");
                        break;
                    case 3:
                        LogMessage("Script was already loaded!");
                        break;
                    case 4:
                        LogMessage("An error occured while trying to load script! Details: {0}", result.Error);
                        break;
                }
            });
        }
        private void abortScriptsButton_Click(object sender, EventArgs e)
        {
            connection.Manager.AbortScript(scriptNameTextbox.Text).ContinueWith(x =>
            {
                Result<byte> result = x.Result;

                switch (result.Value)
                {
                    case 0:
                        LogMessage("No attempt was made to abort script!");
                        break;
                    case 1:
                        LogMessage("Script was aborted!");
                        break;
                    case 2:
                        LogMessage("User has disabled remote aborting of scripts!");
                        break;
                    case 3:
                        LogMessage("Script was not found!");
                        break;
                    case 4:
                        LogMessage("An error occured while trying to abort script! Details: {0}", result.Error);
                        break;
                }
            });
        }

        // Game
        private void getSessionInfoButton_Click(object sender, EventArgs e)
        {
            connection.Game.GetSessionInfo().ContinueWith(x =>
            {
                IVSessionInfo info = x.Result.Value;

                LogMessage("IsNetworkSession: {0}", info.IsNetworkSession);
                LogMessage("IsNetworkSessionStarted: {0}", info.IsNetworkSessionStarted);
                LogMessage("GameMode: {0}", info.GameMode);
                LogMessage("PlayerCount: {0}", info.PlayerCount);
                LogMessage("MaxPlayerCount: {0}", info.MaxPlayerCount);
                LogMessage("Score: {0}", info.Score);
                LogMessage("Players:");

                for (int i = 0; i < info.Players.Count; i++)
                    LogMessage(info.Players[i]);
            });
        }

        private void getPlayerNameNativeButton_Click(object sender, EventArgs e)
        {
            connection.Game.CallNativeFunction("GET_PLAYER_NAME", 0).ContinueWith(x =>
            {
                LogMessage("Name of player 0: {0}", x.Result.Value.GetString());
            });
        }

        private void button1_Click(object sender, EventArgs e)
        {
            connection.Game.CallNativeFunction("GET_PLAYER_ID").ContinueWith(id =>
            {
                Console.WriteLine("GET_PLAYER_ID succeeded");

                connection.Game.CallNativeFunction("CONVERT_INT_TO_PLAYERINDEX", id.Result.Value.GetUInt()).ContinueWith(x =>
                {
                    int playerId = x.Result.Value.GetInt();

                    Console.WriteLine("CONVERT_INT_TO_PLAYERINDEX succeeded");

                    connection.Game.CallNativeFunction("GET_PLAYER_CHAR", playerId, null).ContinueWith(y =>
                    {
                        int playerPed = Convert.ToInt32(y.Result.Value.Arguments[1]);

                        Console.WriteLine("GET_PLAYER_CHAR succeeded");

                        connection.Game.CallNativeFunction("GET_CHAR_COORDINATES", playerPed, null).ContinueWith(z =>
                        {
                            //LogMessage("Coordinates: {0}, {1}, {2}", Convert.ToSingle(z.Result.Value.Arguments[1]), Convert.ToSingle(z.Result.Value.Arguments[2]), Convert.ToSingle(z.Result.Value.Arguments[3]));
                            LogMessage("Coordinates: {0}", (System.Numerics.Vector3)z.Result.Value.Arguments[1]);

                            Console.WriteLine("GET_CHAR_COORDINATES succeeded");
                        });
                    });
                });
            });
        }

    }
}
