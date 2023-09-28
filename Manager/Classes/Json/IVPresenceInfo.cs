using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

using IVSDKDotNet;
using IVSDKDotNet.Enums;

namespace Manager.Classes.Json
{
    public class IVPresenceInfo
    {

        #region Variables
        // General
        public bool IsDead;

        public float Health;
        public float Armour;

        public uint WantedLevel;

        public eWeaponType WeaponType;
        public uint Ammo;

        // Vehicle
        public bool InVehicle;

        public string VehicleName;
        public string CurrentRadioStationName;
        #endregion

        #region Constructor
        internal IVPresenceInfo()
        {

        }
        #endregion

    }
}
