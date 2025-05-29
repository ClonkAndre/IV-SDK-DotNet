using System;
using System.Collections.Generic;

using Manager.Classes;

namespace Manager.Managers
{
    internal static class DelayedActionManager
    {

        #region Variables
        private static List<DelayedAction> delayedActions;
        #endregion

        #region Methods

        public static void Init()
        {
            delayedActions = new List<DelayedAction>();
        }
        public static void Shutdown()
        {
            if (delayedActions != null)
            {
                delayedActions.Clear();
                delayedActions = null;
            }
        }

        // Should normally be called from the main thread but we call it from the render thread for now
        public static void Process()
        {
            DateTime dtNow = DateTime.UtcNow;

            // Execute Delayed Actions if there are any
            for (int i = 0; i < delayedActions.Count; i++)
            {
                DelayedAction dA = delayedActions[i];

                // When reloading the scripts, this could return NULL.
                // I think it could be because a script was starting a Task/Timer which when the script unloads,
                // will also get destroyed and at the end it starts a delayed action to fully get rid of it.
                // For now we just check if that's the case and then we just remove that delayed action entry from the list and continue :cowboy:

                if (dA == null)
                {
                    delayedActions.RemoveAt(i);
                    continue;
                }

                if (dtNow >= dA.ExecuteIn)
                {
                    try
                    {
                        if (dA.ActionToExecute != null)
                        {
                            if (!string.IsNullOrEmpty(dA.Purpose))
                                Logger.LogDebug(string.Format("Delayed Action triggered. Purpose: {0}", dA.Purpose));
                            dA.ActionToExecute.Invoke(dA, dA.Parameter);
                        }
                        delayedActions.RemoveAt(i);
                    }
                    catch (Exception ex)
                    {
                        Logger.LogError(string.Format("An error occured while executing delayed action. DA Purpose: {0}, Details: {1}", dA.Purpose, ex.ToString()));
                        delayedActions.RemoveAt(i);
                    }
                }
            }
        }

        public static void StartDelayedAction(Guid id, string purpose, DateTime executeIn, Action<DelayedAction, object> actionToExecute, object parameter)
        {
            delayedActions.Insert(delayedActions.Count, new DelayedAction(id, purpose, executeIn, actionToExecute, parameter));
        }

        #endregion

        #region Functions
        public static int GetDelayedActionsCount()
        {
            return delayedActions.Count;
        }
        #endregion

    }
}
