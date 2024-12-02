using System;
using System.Collections.Generic;
using System.Collections.Concurrent;

namespace Manager.Threading
{
    public struct DispatchResult
    {
        #region Variables
        public object Result;
        public Exception Error;
        #endregion

        #region Constructor
        public DispatchResult(Exception error, object result)
        {
            Result = result;
            Error = error;
        }
        public DispatchResult(Exception error)
        {
            Result = null;
            Error = error;
        }
        #endregion
    }

    public class Dispatcher
    {

        #region Variables
        public NetThread TargetThread;
        public ConcurrentQueue<Action> QueuedWork;
        public Dictionary<Guid, DispatchResult> DispatchedEventResults;
        #endregion

        #region Constructor
        public Dispatcher(NetThread targetThread)
        {
            TargetThread = targetThread;
            QueuedWork = new ConcurrentQueue<Action>();
            DispatchedEventResults = new Dictionary<Guid, DispatchResult>(32);
        }
        #endregion

        public void ProcessQueue()
        {
            while (QueuedWork.Count > 0)
            {
                if (QueuedWork.TryDequeue(out Action a))
                {
                    a.Invoke();
                }
            }
        }

        public void Dispatch(Action action)
        {
            Guid eventId = Guid.NewGuid();
            
            // Add event to queue
            QueuedWork.Enqueue(() =>
            {
                try
                {
                    action();
                    DispatchedEventResults.Add(eventId, new DispatchResult());
                }
                catch (Exception ex)
                {
                    DispatchedEventResults.Add(eventId, new DispatchResult(ex));
                }
            });

            // Wait for result
            while (!DispatchedEventResults.ContainsKey(eventId))
            {
                Helper.WriteToDebugOutput(Priority.Default, "waiting..........................");
                TargetThread.Wait(0);
            }

            Helper.WriteToDebugOutput(Priority.Default, "FINISHED WAITING");

            // Remove event result from dict
            DispatchedEventResults.Remove(eventId);
        }
        public DispatchResult DispatchWithReturn<T>(Func<T> func)
        {
            Guid eventId = Guid.NewGuid();

            // Add event to queue
            QueuedWork.Enqueue(() =>
            {
                try
                {
                    T funcResult = func();
                    DispatchedEventResults.Add(eventId, new DispatchResult(null, funcResult));
                }
                catch (Exception ex)
                {
                    DispatchedEventResults.Add(eventId, new DispatchResult(ex));
                }
            });

            // Wait for result
            while (!DispatchedEventResults.ContainsKey(eventId))
            {
                TargetThread.Wait(1);
            }

            // Retrieve the result
            DispatchResult result = DispatchedEventResults[eventId];

            // Remove event result from dict
            DispatchedEventResults.Remove(eventId);

            // Return the result
            return result;
        }

    }
}
