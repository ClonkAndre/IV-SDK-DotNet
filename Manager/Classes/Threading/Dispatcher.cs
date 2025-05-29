using System;
using System.Collections.Concurrent;
using System.Collections.Generic;

namespace Manager.Classes.Threading
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

        public static DispatchResult Empty()
        {
            return new DispatchResult(null, null);
        }
    }

    public class Dispatcher
    {

        #region Variables
        private NetThread theOwnerThread;
        private ConcurrentQueue<Action> queuedWork;
        private Dictionary<Guid, DispatchResult> dispatchedEventResults;
        #endregion

        #region Constructor
        public Dispatcher(NetThread ownerThread)
        {
            theOwnerThread = ownerThread;
            queuedWork = new ConcurrentQueue<Action>();
            dispatchedEventResults = new Dictionary<Guid, DispatchResult>(32);
        }
        #endregion

        public void ProcessQueue()
        {
            while (queuedWork.Count > 0)
            {
                if (queuedWork.TryDequeue(out Action a))
                {
                    a.Invoke();
                }
            }
        }
        
        /// <summary>
        /// Dispatches a <see cref="Action"/> to this dispatcher without waiting for its results or anything.
        /// </summary>
        /// <param name="a">The action to dispatch.</param>
        public void DispatchAndForget(Action a)
        {
            // Don't allow anything to be added to the queue when the thread is currently waiting to
            // avoid multiple actions being queued up and invoked as soon as the thread no longer waits.
            if (theOwnerThread.IsCurrentlyWaiting)
                return;

            queuedWork.Enqueue(a);
        }

        /// <summary>
        /// Dispatches a <see cref="Action"/> to this dispatcher, waits for the dispatched <see cref="Action"/> to finish and then returns the result.
        /// </summary>
        /// <param name="a">The action to dispatch and wait for.</param>
        /// <returns>The dispatch result containing the exception that might occured while trying to execute the given action.</returns>
        public DispatchResult DispatchWithReturn(Action a)
        {
            // Don't allow anything to be added to the queue when the thread is currently waiting to
            // avoid multiple actions being queued up and invoked as soon as the thread no longer waits.
            if (theOwnerThread.IsCurrentlyWaiting)
                return DispatchResult.Empty();

            Guid eventId = Guid.NewGuid();

            // Add event to queue
            queuedWork.Enqueue(() =>
            {
                try
                {
                    a();
                    dispatchedEventResults.Add(eventId, new DispatchResult(null, null));
                }
                catch (Exception ex)
                {
                    dispatchedEventResults.Add(eventId, new DispatchResult(ex));
                }
            });

            // Wait for result
            while (!dispatchedEventResults.ContainsKey(eventId))
            {
                theOwnerThread.Wait(0);
            }

            // Retrieve the result
            DispatchResult result = dispatchedEventResults[eventId];

            // Remove event result from dict
            dispatchedEventResults.Remove(eventId);

            // Return the result
            return result;
        }
        /// <summary>
        /// Dispatches a <see cref="Func{TResult}"/> to this dispatcher, waits for the dispatched <see cref="Func{TResult}"/> to finish and then returns the result.
        /// </summary>
        /// <param name="func">The function to dispatch and wait for.</param>
        /// <returns>The dispatch result containing the exception that might occured while trying to execute the given function, and the return value of the function.</returns>
        public DispatchResult DispatchWithReturn<T>(Func<T> func)
        {
            // Don't allow anything to be added to the queue when the thread is currently waiting to
            // avoid multiple actions being queued up and invoked as soon as the thread no longer waits.
            if (theOwnerThread.IsCurrentlyWaiting)
                return DispatchResult.Empty();

            Guid eventId = Guid.NewGuid();

            // Add event to queue
            queuedWork.Enqueue(() =>
            {
                try
                {
                    T funcResult = func();
                    dispatchedEventResults.Add(eventId, new DispatchResult(null, funcResult));
                }
                catch (Exception ex)
                {
                    dispatchedEventResults.Add(eventId, new DispatchResult(ex));
                }
            });

            // Wait for result
            while (!dispatchedEventResults.ContainsKey(eventId))
            {
                theOwnerThread.Wait(0);
            }

            // Retrieve the result
            DispatchResult result = dispatchedEventResults[eventId];

            // Remove event result from dict
            dispatchedEventResults.Remove(eventId);

            // Return the result
            return result;
        }

    }
}
