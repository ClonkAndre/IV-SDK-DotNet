using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

using IVSDKDotNet;
using IVSDKDotNet.Internal;

using Manager.Classes.Scripts;
using Manager.Classes.Threading;

namespace Manager.Managers
{
    internal static class ThreadManager
    {

        #region Variables
        private static bool wasInitialized;

        private static ConcurrentDictionary<int, NetThread> threads;
        private static ConcurrentDictionary<int, UIntPtr> temporaryThreadTlsContextStorage;
        private static ConcurrentDictionary<GameThread, ThreadData> gameThreadDataStorage;

        private static ConcurrentQueue<Action> mainThreadActionQueue;
        private static ConcurrentQueue<Action> renderThreadActionQueue;
        #endregion

        #region Methods

        public static void Init()
        {
            if (wasInitialized)
                return;

            threads = new ConcurrentDictionary<int, NetThread>();
            temporaryThreadTlsContextStorage = new ConcurrentDictionary<int, UIntPtr>();
            gameThreadDataStorage = new ConcurrentDictionary<GameThread, ThreadData>(1, (int)GameThread.COUNT);

            mainThreadActionQueue = new ConcurrentQueue<Action>();
            renderThreadActionQueue = new ConcurrentQueue<Action>();

            wasInitialized = true;
        }
        public static void Shutdown()
        {
            if (!wasInitialized)
                return;

            wasInitialized = false;

            if (threads != null)
            {
                foreach (KeyValuePair<int, NetThread> entry in threads)
                {
                    // Manager needs to shutdown, forcefully abort all threads
                    entry.Value.ForceShutdown();
                }

                threads.Clear();
                threads = null;
            }
            if (temporaryThreadTlsContextStorage != null)
            {
                temporaryThreadTlsContextStorage.Clear();
                temporaryThreadTlsContextStorage = null;
            }
            if (gameThreadDataStorage != null)
            {
                gameThreadDataStorage.Clear();
                gameThreadDataStorage = null;
            }
            if (mainThreadActionQueue != null)
            {
                mainThreadActionQueue = null;
            }
            if (renderThreadActionQueue != null)
            {
                renderThreadActionQueue = null;
            }
        }

        // NEEDS TO BE CALLED FROM THE MAIN THREAD!
        public static void ProcessMainThread()
        {
            if (!wasInitialized)
                return;

            // Process the main thread queue
            while (mainThreadActionQueue.TryDequeue(out Action a))
            {
                a?.Invoke();
            }

            // Process threads
            DateTime dtNow = DateTime.UtcNow;
            foreach (KeyValuePair<int, NetThread> entry in threads)
            {
                // Check if the thread is dead, so we can remove it
                if (!entry.Value.IsThreadAlive)
                {
                    if (threads.TryRemove(entry.Key, out NetThread t))
                        Helper.WriteToDebugOutput(Priority.Default, "Removed thread {0} ({1}) from threads dictionary because it is no longer alive.", entry.Key, entry.Value.ThreadName);

                    continue;
                }

                // Forcefully shut the thread down if it is still alive even tho a shut down was requested
                if (entry.Value.WasShutdownRequested && dtNow > entry.Value.ExpectShutdownAt)
                {
                    // Force abort the thread
                    Helper.WriteToDebugOutput(Priority.Medium, "Forcing thread {0} to shut down because it failed to shut down safely.", entry.Key);
                    entry.Value.ForceShutdown();

                    if (threads.TryRemove(entry.Key, out NetThread t))
                        Helper.WriteToDebugOutput(Priority.Medium, "Removed thread {0} from threads dictionary after it was forcefully shut down.", entry.Key);
                }
            }
        }

        // NEEDS TO BE CALLED FROM THE RENDER THREAD!
        public static void ProcessRenderThread()
        {
            if (!wasInitialized)
                return;

            // Process the render thread queue
            while (renderThreadActionQueue.TryDequeue(out Action a))
            {
                a?.Invoke();
            }
        }

        /// <summary>
        /// Adds something to the main thread queue.
        /// </summary>
        /// <param name="a">The action to execute on the main thread.</param>
        public static void AddToMainThreadQueue(Action a)
        {
            if (!wasInitialized)
                return;

            mainThreadActionQueue.Enqueue(a);
        }
        /// <summary>
        /// Adds something to the render thread queue.
        /// </summary>
        /// <param name="a">The action to execute on the render thread.</param>
        public static void AddToRenderThreadQueue(Action a)
        {
            if (!wasInitialized)
                return;

            renderThreadActionQueue.Enqueue(a);
        }

        /// <summary>
        /// Forces all registered script threads to tick.
        /// </summary>
        public static void ForceAllScriptThreadsToTick()
        {
            foreach (KeyValuePair<int, NetThread> pairs in threads)
            {
                if (pairs.Value.Type == ThreadType.ScriptThread)
                    pairs.Value.TickNow();
            }
        }

        public static void ForceWaitWhileProcessingWindowMessages(TimeSpan waitTime)
        {
            DateTime waitUntil = DateTime.UtcNow.Add(waitTime);

            do
            {
                IVGrcWindow.ProcessWindowMessage();
                Thread.Sleep(1);
            }
            while (DateTime.UtcNow < waitUntil);
        }

        // - - - GAME THREAD STUFF - - -
        /// <summary>
        /// Stores the data of a game thread such as its ID and its TlsContext that we can retrieve later on by using the <see cref="GetGameThreadData(GameThread)"/> function.
        /// </summary>
        /// <param name="thread">The thread we want to store the ID of.</param>
        public static void StoreGameThreadData(GameThread thread)
        {
            if (!wasInitialized)
                return;

            // Add or update
            if (!gameThreadDataStorage.ContainsKey(thread))
            {
                gameThreadDataStorage.TryAdd(thread, new ThreadData(GetCurrentThreadID(), TlsHelper.GetTlsContext()));
            }
            else
            {
                gameThreadDataStorage[thread].UpdateTlsContext(TlsHelper.GetTlsContext());
            }
        }

        // - - - TLS CONTEXT STUFF - - -
        /// <summary>
        /// Stores the current thread's tls context, sets it to the one of the main thread, then invokes <paramref name="a"/> and finally restores the saved tls.
        /// </summary>
        /// <param name="a">The action to execute on the context of the main thread.</param>
        public static void SetCurrentThreadTlsContextToMainThreadContextAndExecute(Action a)
        {
            if (!wasInitialized)
                return;
            if (a == null)
                return;

            // Store current tls context
            UIntPtr ctx = TlsHelper.GetTlsContext();

            // Set tls context to the main thread's context
            TlsHelper.SetTlsContext(GetGameThreadData(GameThread.MainThread).TlsContext);

            try
            {
                // Now invoke action
                a();
            }
            finally
            {
                // Restore tls context of current thread
                TlsHelper.SetTlsContext(ctx);
            }
        }

        /// <summary>
        /// Gets the tls context of the calling thread and stores it in a list.
        /// </summary>
        public static void StoreCurrentThreadTlsContext()
        {
            if (!wasInitialized)
                return;

            int currentThreadId = GetCurrentThreadID();

            if (!temporaryThreadTlsContextStorage.ContainsKey(currentThreadId))
                temporaryThreadTlsContextStorage.TryAdd(currentThreadId, TlsHelper.GetTlsContext());
        }
        /// <summary>
        /// Sets the tls context of the calling thread to the one of the main thread.
        /// </summary>
        public static void ChangeTlsContextOfCurrentThreadToContextOfTargetThread(GameThread targetThread)
        {
            if (!wasInitialized)
                return;

            ThreadData data = GetGameThreadData(targetThread);

            if (data == null)
            {
                Helper.BreakInDebugger();
                return;
            }

            // Set tls context to the one of the given thread
            TlsHelper.SetTlsContext(GetGameThreadData(targetThread).TlsContext);
        }
        /// <summary>
        /// Sets the tls context of the calling thread to the one of the main thread.
        /// </summary>
        /// <summary>
        /// Retrieves the previously stored tls context of the calling thread and restores it.
        /// </summary>
        public static void RestoreTlsContextForCurrentThread()
        {
            if (!wasInitialized)
                return;

            int currentThreadId = GetCurrentThreadID();

            if (temporaryThreadTlsContextStorage.TryGetValue(currentThreadId, out UIntPtr ctx))
            {
                TlsHelper.SetTlsContext(ctx);
                temporaryThreadTlsContextStorage.TryRemove(currentThreadId, out ctx);
            }
        }

        #endregion

        #region Functions

        public static NetThread[] GetActiveThreads()
        {
            if (!wasInitialized)
                return Array.Empty<NetThread>();

            return threads.Values.ToArray();
        }
        public static int GetActiveThreadsCount()
        {
            if (!wasInitialized)
                return 0;

            return threads.Count;
        }

        public static KeyValuePair<GameThread, ThreadData>[] GetDataOfGameThreads()
        {
            if (!wasInitialized)
                return Array.Empty<KeyValuePair<GameThread, ThreadData>>();

            return gameThreadDataStorage.ToArray();
        }

        public static int GetMainThreadActionQueueCount()
        {
            if (!wasInitialized)
                return 0;

            return mainThreadActionQueue.Count;
        }

        /// <summary>
        /// Determines whether data for the specified game thread is available.
        /// </summary>
        /// <remarks>This method returns <see langword="false"/> if the system has not been initialized 
        /// or if no data exists for the specified game thread.</remarks>
        /// <param name="thread">The game thread to check for available data.</param>
        /// <returns><see langword="true"/> if data for the specified game thread is available;  otherwise, <see langword="false"/>.</returns>
        public static bool IsGameThreadDataAvailable(GameThread thread)
        {
            if (!wasInitialized)
                return false;

            return gameThreadDataStorage.ContainsKey(thread);
        }

        /// <summary>
        /// Retrieves the data of the stored game thread.
        /// </summary>
        /// <param name="thread">The thread we want to retrieve the data of.</param>
        /// <returns>The stored thread data.</returns>
        public static ThreadData GetGameThreadData(GameThread thread)
        {
            if (!wasInitialized)
                return null;
            if (gameThreadDataStorage.ContainsKey(thread))
                return gameThreadDataStorage[thread];

            return null;
        }

        /// <summary>
        /// Gets the managed thread ID of the current thread.
        /// </summary>
        /// <returns>The managed thread ID.</returns>
        public static int GetCurrentThreadID()
        {
            return Thread.CurrentThread.ManagedThreadId;
        }

        /// <summary>
        /// Checks if the current thread is the main thread.
        /// </summary>
        /// <returns><see langword="true"/>if the current thread is the main thread. Otherwise, <see langword="false"/>.</returns>
        public static bool IsCurrentThreadTheMainThread()
        {
            return GetCurrentThreadID() == GetGameThreadData(GameThread.MainThread).ThreadID;
        }
        /// <summary>
        /// Checks if the current thread is the render thread.
        /// </summary>
        /// <returns><see langword="true"/>if the current thread is the main thread. Otherwise, <see langword="false"/>.</returns>
        public static bool IsCurrentThreadTheRenderThread()
        {
            return GetCurrentThreadID() == GetGameThreadData(GameThread.RenderThread).ThreadID;
        }

        /// <summary>
        /// Creates a new script thread, adds it to the global threads list and returns the ID of the new thread.
        /// </summary>
        /// <param name="fs">The script this thread should be created for.</param>
        /// <param name="launchThread">Sets if the thread should be launched after it got created.</param>
        /// <returns>The ID of the new thread. -1 if given script is null.</returns>
        public static int CreateScriptThread(FoundScript fs, bool launchThread = false)
        {
            if (!wasInitialized)
                return -1;
            if (fs == null)
                return -1;

            // Create thread
            ScriptThread thread = new ScriptThread(fs);

            // Try adding thread to the global list
            if (!threads.TryAdd(thread.ThreadId, thread))
            {
                Helper.WriteToDebugOutput(Priority.High, "Failed to add new script thread {0} to global threads list for script {1}. There is already a thread with this ID.", thread.ThreadId, fs.TheFileInfo.FileName);
                thread.Dispose();
                thread = null;
                return -1;
            }

            thread.SetThreadName(fs.TheFileInfo.FileName);

            Helper.WriteToDebugOutput(Priority.Default, "Added new script thread {0} to global threads list for script {1}.", thread.ThreadId, fs.TheFileInfo.FileName);

            if (launchThread)
                thread.Launch();

            // Return ID of the newly created thread
            return thread.ThreadId;
        }

        /// <summary>
        /// Creates a new generic thread, adds it to the global threads list and returns the ID of the new thread.
        /// </summary>
        /// <param name="launchThread">Sets if the thread should be launched after it got created.</param>
        /// <returns>The thread if successful. Otherwise, <see langword="null"/>.</returns>
        public static GenericThread CreateGenericThread(Action onTick, Action onStartup = null, Action onEnd = null, string threadName = null, bool launchThread = false)
        {
            if (!wasInitialized)
                return null;

            // Create thread
            GenericThread thread = new GenericThread(onTick, onStartup, onEnd);

            // Try adding thread to the global list
            if (!threads.TryAdd(thread.ThreadId, thread))
            {
                Helper.WriteToDebugOutput(Priority.High, "Failed to add new generic thread {0} to global threads list for IV-SDK .NET. There is already a thread with this ID.", thread.ThreadId);
                thread.Dispose();
                thread = null;
                return null;
            }

            thread.SetThreadName(threadName);

            Helper.WriteToDebugOutput(Priority.Default, "Added new generic thread {0} to global threads list for IV-SDK .NET.", thread.ThreadId);

            if (launchThread)
                thread.Launch();

            // Return the thread
            return thread;
        }

        /// <summary>
        /// Tries to get the thread by the given ID.
        /// </summary>
        /// <param name="threadId">The ID of the target thread to get.</param>
        /// <param name="thread">Returns the thread if found.</param>
        /// <returns><see langword="true"/> if the thread was found. Otherwise, <see langword="false"/>.</returns>
        public static bool TryGetThread(int threadId, out NetThread thread)
        {
            if (!wasInitialized)
            {
                thread = null;
                return false;
            }
            if (threadId < 0)
            {
                thread = null;
                return false;
            }

            return threads.TryGetValue(threadId, out thread);
        }

        /// <summary>
        /// Gets the thread with the given ID, and tries to cast it to the given type.
        /// </summary>
        /// <typeparam name="T">The type to cast the thread to.</typeparam>
        /// <param name="threadId">The ID of the target thread to get.</param>
        /// <returns>The thread if found and castable. Otherwise, <see langword="null"/>.</returns>
        public static T GetThreadAs<T>(int threadId) where T : NetThread
        {
            if (!wasInitialized)
                return default;
            if (threadId < 0)
                return default;

            if (threads.TryGetValue(threadId, out NetThread thread))
            {
                return thread as T;
            }

            return default;
        }

        /// <summary>
        /// Checks if the thread with the given ID is of the given type.
        /// </summary>
        /// <param name="threadId">The type to cast the thread to.</param>
        /// <param name="type">The type to check.</param>
        /// <returns><see langword="true"/> if the thread is of the given type. Otherwise, <see langword="false"/>.</returns>
        public static bool IsThreadOfType(int threadId, ThreadType type)
        {
            if (!wasInitialized)
                return false;
            if (threadId < 0)
                return false;

            if (threads.TryGetValue(threadId, out NetThread thread))
            {
                return thread.Type == type;
            }

            return false;
        }

        /// <summary>
        /// Tries to wait in the thread with the given ID.
        /// </summary>
        /// <param name="threadId">The ID of the target thread to wait in.</param>
        /// <param name="milliseconds">How long the thread should wait.</param>
        /// <returns><see langword="true"/> if the thread was found. Otherwise, <see langword="false"/>.</returns>
        public static bool WaitInThread(int threadId, int milliseconds)
        {
            if (!wasInitialized)
                return false;
            if (threadId < 0)
                return false;

            if (threads.TryGetValue(threadId, out NetThread thread))
            {
                thread.Wait(milliseconds);
                return true;
            }

            return false;
        }

        /// <summary>
        /// Tries to launch the thread with the given ID.
        /// </summary>
        /// <param name="threadId">The ID of the target thread to try launching.</param>
        /// <returns><see langword="true"/> if the thread was found. Otherwise, <see langword="false"/>.</returns>
        public static bool LaunchThread(int threadId)
        {
            if (!wasInitialized)
                return false;
            if (threadId < 0)
                return false;

            if (threads.TryGetValue(threadId, out NetThread thread))
            {
                thread.Launch();
                return true;
            }

            return false;
        }

        /// <summary>
        /// Tries to abort a thread with the given ID.
        /// </summary>
        /// <param name="threadId">The ID of the target thread to abort.</param>
        /// <returns><see langword="true"/> if the thread was found. Otherwise, <see langword="false"/>.</returns>
        public static bool TryShutdownThread(int threadId)
        {
            if (!wasInitialized)
                return false;
            if (threadId < 0)
                return false;

            if (threads.TryGetValue(threadId, out NetThread thread))
            {
                thread.TryShutdown();
                return true;
            }

            return false;
        }

        #endregion

    }
}
