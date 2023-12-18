using System.Collections.Generic;

namespace IVSDKDotNetAPI.Classes
{
    public class IVSessionInfo
    {

        #region Variables
        public bool IsNetworkSession;
        public bool IsNetworkSessionStarted;
        public bool IsLANSession;
        public bool IsThisMachineTheServer;
        public IVGameMode GameMode;
        public List<string> Players;

        public uint PlayerCount;
        public uint MaxPlayerCount;

        public uint Team;
        public uint Score;

        public string ServerName;
        public int ServerID;
        #endregion

        #region Constructor
        internal IVSessionInfo()
        {
            Players = new List<string>();
        }
        #endregion

    }
}
