using System.Collections.Generic;

namespace Manager.Classes.Json
{
    public class IVSessionInfo
    {

        #region Variables
        public bool IsNetworkSession;
        public bool IsNetworkSessionStarted;
        public bool IsThisMachineTheServer;
        public IVGameMode GameMode;
        public List<string> Players;

        public uint PlayerCount;
        public uint MaxPlayerCount;

        public uint Team;
        public uint Score;
        #endregion

        #region Constructor
        internal IVSessionInfo()
        {
            Players = new List<string>();
        }
        #endregion

    }
}
