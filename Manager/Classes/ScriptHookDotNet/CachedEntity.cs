using System;

using Manager.Managers;

using GTA;
using bObject = GTA.@base.Object;

namespace Manager.Classes.ScriptHookDotNet
{
    internal class CachedEntity
    {

        #region Variables and Enums
        // Variables
        public Guid OwnerScriptID;
        public bObject TheEntity;
        public RemoveReason RemovalReason;

        // Enums
        public enum RemoveReason
        {
            NoLongerExists,
            OwnerScriptNoLongerAlive
        }
        #endregion

        #region Constructor
        public CachedEntity(Guid ownerScriptID, bObject ent)
        {
            OwnerScriptID = ownerScriptID;
            TheEntity = ent;
        }
        #endregion

        /// <summary>
        /// Checks if this cached entity can be removed from the cache either because it no longer exists, or because the "owner" script is no longer active.
        /// </summary>
        public bool CanBeRemoved()
        {
            // If the OwnerScriptID is empty, that means the entity does not belong to a script
            if (OwnerScriptID != Guid.Empty && !IsOwnerScriptAlive())
            {
                RemovalReason = RemoveReason.OwnerScriptNoLongerAlive;
                return true;
            }

            if (!TheEntity.Exists())
            {
                RemovalReason = RemoveReason.NoLongerExists;
                return true;
            }

            return false;
        }

        /// <summary>
        /// Tries to delete the entity from the world
        /// </summary>
        public void TryDelete()
        {
            if (!TheEntity.Exists())
                return;

            // Do not delete the player ped
            if (TheEntity.Type == HandleType.Ped
                && TheEntity.UID == Main.Instance.PlayerPedHandle)
                return;

            // Do not delete the player vehicle
            if (TheEntity.Type == HandleType.Vehicle
                && TheEntity.UID == Main.Instance.PlayerVehicleHandle)
                return;

            // Based on the entity type, this will either directly delete the entity, or mark is as no longer needed so its more seamless
            switch (TheEntity.Type)
            {

                // iComplexObject - Mark them as no longer needed
                // Vehicle, Ped, Object
                case HandleType.Vehicle:
                case HandleType.Ped:
                case HandleType.Object:

                    GTA.@base.iRequestable requestable = TheEntity as GTA.@base.iRequestable;
                    requestable.NoLongerNeeded();

                    Helper.WriteToDebugOutput(Priority.Default, "Trying to mark {0} as no longer needed (Handle: {1})!", TheEntity.Type, TheEntity.UID);

                    break;

                // This seems to be the only thing right now which doesn't implement the IDeletable interface so we cant get rid of it yet
                case HandleType.DecisionMaker:
                    // TODO
                    break;

                // Entities which only implement the iDeletable interface
                // Blip, Camera, Group, Pickup, ScriptedFire
                default:

                    GTA.@base.iDeletable deletable = TheEntity as GTA.@base.iDeletable;
                    deletable.Delete();

                    Helper.WriteToDebugOutput(Priority.Default, "Trying to delete {0} (Handle: {1})!", TheEntity.Type, TheEntity.UID);

                    break;

            }
        }

        private bool IsOwnerScriptAlive()
        {
            return ScriptManager.GetFoundScript(OwnerScriptID) != null;
        }

    }
}
