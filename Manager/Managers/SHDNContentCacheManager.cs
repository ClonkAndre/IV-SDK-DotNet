using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

using GTA;
using GTAObject = GTA.Object;
using bObject = GTA.@base.Object;

using Manager.Classes.ScriptHookDotNet;

namespace Manager.Managers
{
    internal static class SHDNContentCacheManager
    {

        // We could theoratically also use this caching system for IV-SDK .NET for less GC pressure
        // Tho it would be suited better for ClonksCodingLib.GTAIV because this extension is aimed towards being more like ScriptHookDotNet anyway

        #region Consts
        public const int MAX_FIRES = 100;
        #endregion

        #region Variables
        private static bool wasInitialized;
        private static bool blockCacheProcessing;

        private static ConcurrentDictionary<int, CachedEntity> cachedEntities;
        private static ConcurrentDictionary<int, Player> cachedPlayers;
        private static ConcurrentQueue<Action> deleteQueue;
        #endregion

        #region Methods
        public static void Init()
        {
            if (wasInitialized)
                return;

            cachedEntities = new ConcurrentDictionary<int, CachedEntity>(2, 10_000);
            cachedPlayers = new ConcurrentDictionary<int, Player>(2, 32);
            deleteQueue = new ConcurrentQueue<Action>();

            wasInitialized = true;
        }
        public static void Shutdown()
        {
            if (!wasInitialized)
                return;

            wasInitialized = false;

            if (cachedEntities == null)
            {
                cachedEntities.Clear();
                cachedEntities = null;
            }
            if (cachedPlayers != null)
            {
                cachedPlayers.Clear();
                cachedPlayers = null;
            }
            if (deleteQueue != null)
            {
                deleteQueue = null;
            }
        }

        public static void Process()
        {
            if (!wasInitialized)
                return;

            // Process delete queue
            while (deleteQueue.TryDequeue(out Action deleteAction))
            {
                deleteAction.Invoke();
            }

            if (blockCacheProcessing)
                return;

#if !DEBUG
            try
            {
#endif
            // Remove all non existing entities
            foreach (KeyValuePair<int, CachedEntity> entry in cachedEntities)
            {
                if (!entry.Value.CanBeRemoved())
                    continue;

                bObject obj = entry.Value.TheEntity;

                // Add to delete queue
                deleteQueue.Enqueue(() =>
                {
                    if (cachedEntities.TryRemove(entry.Key, out CachedEntity ent))
                        ent.TryDelete();
                });

                Helper.WriteToDebugOutput(Priority.Default, "Cached {0} (Type: {1}, UID: {2}) will be removed from cache! Reason: {3}", obj.GetType().Name, obj.Type, obj.UID, entry.Value.RemovalReason);
            }

            // Update active players and remove inactive players
            foreach (KeyValuePair<int, Player> entry in cachedPlayers)
            {
                // Make sure the player ped handle is up-to-date
                entry.Value.EnsurePlayerPedHandleIsUpToDate();

                // Dont remove the local player
                if (entry.Value.isLocalPlayer)
                    continue;
                // Dont remove active players
                if (IVSDKDotNet.IVPlayerInfo.IsPlayerActive(entry.Key))
                    continue;

                // Add to delete queue
                deleteQueue.Enqueue(() =>
                {
                    cachedPlayers.TryRemove(entry.Key, out Player player);
                });

                Helper.WriteToDebugOutput(Priority.Default, "Cached Player (ID: {0}) will be removed from cache! Reason: Inactive", entry.Key);
            }

#if !DEBUG
            }
            catch (Exception)
		    {
            }
#endif
        }

        public static void ForceRemoveAll()
        {
            if (!wasInitialized)
                return;

            blockCacheProcessing = true;

            // Delete cached entities
            if (cachedEntities != null)
            {
                foreach (KeyValuePair<int, CachedEntity> entry in cachedEntities)
                {
                    // Add to delete queue
                    deleteQueue.Enqueue(() =>
                    {
                        if (cachedEntities.TryRemove(entry.Key, out CachedEntity ent))
                            ent.TryDelete();
                    });
                }
            }

            // Delete cached players
            if (cachedPlayers != null)
            {
                foreach (KeyValuePair<int, Player> entry in cachedPlayers)
                {
                    // Add to delete queue
                    deleteQueue.Enqueue(() =>
                    {
                        cachedPlayers.TryRemove(entry.Key, out Player player);
                    });
                }
            }

            blockCacheProcessing = false;
        }

        public static void AddEntity(Guid ownerScript, object obj)
        {
            if (!wasInitialized)
                return;
            if (obj == null)
                return;

            // Convert object to a GTA.@base.Object
            bObject ent = obj as bObject;

            // Generate lookup key
            // A unique key made out of the entity type and the handle to avoid handle conflicts
            int lookupKey = ((int)ent.Type * 397) ^ ent.UID;

            if (cachedEntities.ContainsKey(lookupKey))
                return;

            if (cachedEntities.TryAdd(lookupKey, new CachedEntity(ownerScript, ent)))
                Helper.WriteToDebugOutput(Priority.Default, "Added {0} (Handle: {1}, UniqueHandle: {2}) to cache!", ent.Type, ent.UID, lookupKey);
        }
        public static void RemoveEntity(int handle)
        {
            if (!wasInitialized)
                return;
            if (handle == 0)
                return;

            if (cachedEntities.ContainsKey(handle))
            {
                if (cachedEntities.TryRemove(handle, out CachedEntity ent))
                    Helper.WriteToDebugOutput(Priority.Default, "Manually removed {0} (Handle: {1}) from the cache!", ent.TheEntity.Type, ent.TheEntity.UID);
            }
        }
        public static void RemoveEntity(object obj)
        {
            if (!wasInitialized)
                return;
            if (obj == null)
                return;

            // Convert object to a GTA.@base.Object
            bObject ent = obj as bObject;

            RemoveEntity(ent.UID);
        }

        public static void AddPlayer(object obj)
        {
            if (!wasInitialized)
                return;
            if (obj == null)
                return;

            // Convert object to a GTA.Player
            Player player = obj as Player;

            if (cachedPlayers.ContainsKey(player.ID))
                return;

            if (cachedPlayers.TryAdd(player.ID, player))
                Helper.WriteToDebugOutput(Priority.Default, "Added Player (ID: {0}) to cache!", player.ID);
        }
        public static void RemovePlayer(int id)
        {
            if (!wasInitialized)
                return;
            if (id < 0)
                return;

            if (cachedPlayers.ContainsKey(id))
            {
                if (cachedPlayers.TryRemove(id, out Player player))
                    Helper.WriteToDebugOutput(Priority.Default, "Manually removed Player (ID: {0}) from the cache!", player.ID);
            }
        }
        public static void RemovePlayer(object obj)
        {
            if (!wasInitialized)
                return;
            if (obj == null)
                return;

            // Convert object to a GTA.Player
            Player player = obj as Player;

            RemovePlayer(player.ID);
        }
        #endregion

        #region Functions

        public static CachedEntity[] GetCachedEntities()
        {
            if (!wasInitialized)
                return Array.Empty<CachedEntity>();

            return cachedEntities.Values.ToArray();
        }
        public static int GetCachedEntityCount()
        {
            if (!wasInitialized)
                return 0;

            return cachedEntities.Count;
        }

        public static Player[] GetCachedPlayers()
        {
            if (!wasInitialized)
                return null;

            return cachedPlayers.Values.ToArray();
        }
        public static int GetCachedPlayersCount()
        {
            if (!wasInitialized)
                return 0;

            return cachedPlayers.Count;
        }

        public static object GetEntity(int handle, int requestedType, Guid ownerScript)
        {
            if (!wasInitialized)
                return null;
            if (handle == 0)
                return null;

            // Generate lookup key
            int lookupKey = (requestedType * 397) ^ handle;

            // Try return entity from cache
            if (cachedEntities.TryGetValue(lookupKey, out CachedEntity ent))
            {
                // Check if the type of the entity is actually the same as the requested type
                if ((int)ent.TheEntity.Type != requestedType)
                {
                    Helper.WriteToDebugOutput(Priority.Default, "Cached {0} (Handle: {1}, UniqueHandle: {2}) is not the requested type ({3})!", ent.TheEntity.Type, ent.TheEntity.UID, lookupKey, requestedType);
                    return null;
                }

                //Helper.WriteToDebugOutput(Priority.Default, "Found requested {0} (Handle: {1}) in cache!", ent.TheEntity.Type, ent.TheEntity.UID);
                return ent.TheEntity;
            }

            // Create new entity, add it to cache and return it
            bObject obj = null;

            switch ((HandleType)requestedType)
            {
                case HandleType.Blip:
                    obj = new Blip(handle);
                    break;
                case HandleType.Camera:
                    obj = new Camera(handle);
                    break;
                case HandleType.DecisionMaker:
                    obj = new DecisionMaker(handle);
                    break;
                case HandleType.Group:
                    obj = new Group(handle);
                    break;
                case HandleType.Object:
                    obj = new GTAObject(handle);
                    break;
                case HandleType.Ped:
                    obj = new Ped(handle);
                    break;
                case HandleType.Pickup:
                    obj = new Pickup(handle);
                    break;
                case HandleType.ScriptedFire:
                    obj = new ScriptedFire(handle);
                    break;
                case HandleType.Vehicle:
                    obj = new Vehicle(handle);
                    break;
            }

            if (obj == null)
                return null;

            if (cachedEntities.TryAdd(lookupKey, new CachedEntity(ownerScript, obj)))
                Helper.WriteToDebugOutput(Priority.Default, "Added {0} (Handle: {1}, UniqueHandle: {2}) to cache because it was requested and did not exist yet!", obj.Type, obj.UID, lookupKey);

            return obj;
        }
        public static object GetPlayer(int id)
        {
            if (!wasInitialized)
                return null;
            if (id < 0)
                return null;

            // Try return player from cache
            if (cachedPlayers.TryGetValue(id, out Player player))
            {
                //Helper.WriteToDebugOutput(Priority.Default, "Player (ID: {0}) was found in the cache!", player.ID);
                return player;
            }

            // Create player, add to cache and return
            player = new Player(id);

            if (cachedPlayers.TryAdd(id, player))
                Helper.WriteToDebugOutput(Priority.Default, "Added Player (ID: {0}) to cache because it was requested and did not exist yet!", id);

            return player;
        }

        #endregion

    }
}
