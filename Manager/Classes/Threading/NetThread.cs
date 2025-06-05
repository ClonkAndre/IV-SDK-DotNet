using System;
using System.Threading;

namespace Manager.Classes.Threading
{

    // Modified version of the NetThread from the ScriptHookDotNet project made by HazardX
    // https://github.com/HazardX/gta4_scripthookdotnet

    public abstract class NetThread : IDisposable
    {

        #region Variables and Properties
        // Variables
        private bool wasDisposed;
        private bool isInLoop;
        private bool isThreadAbleToTick;
        private bool isCurrentlyWaiting;
        private bool blockWait;
        private DateTime expectShutdownAt;
        private DateTime waitUntil;
        private ThreadType type;

        // Thread stuff
        private Thread theThread;
        private AutoResetEvent threadRunFlag;
        private ManualResetEvent threadStopFlag;
        private Dispatcher dispatcher;

        private CancellationTokenSource cancellationTokenSource;
        private CancellationToken cancellationToken;

        // Properties
        public bool WasDisposed
        {
            get => wasDisposed;
            private set => wasDisposed = value;
        }

        /// <summary>
        /// Gets the time the thread is expected to shut down.
        /// </summary>
        public DateTime ExpectShutdownAt
        {
            get => expectShutdownAt;
            private set => expectShutdownAt = value;
        }

        /// <summary>
        /// Gets if the underlying thread is alive and if no shutdown was requested.
        /// </summary>
        public bool IsRunning
        {
            get => theThread.IsAlive && !WasShutdownRequested;
        }

        public bool IsInLoop
        {
            get => isInLoop;
            private set => isInLoop = value;
        }
        public bool IsThreadAbleToTick
        {
            get => isThreadAbleToTick;
            private set => isThreadAbleToTick = value;
        }

        public bool IsCurrentlyWaiting
        {
            get => isCurrentlyWaiting;
            private set => isCurrentlyWaiting = value;
        }
        public bool BlockWait
        {
            get => blockWait;
            set => blockWait = value;
        }

        /// <summary>
        /// Gets if a shut down was requested for this thread.
        /// </summary>
        public bool WasShutdownRequested
        {
            get => cancellationToken.IsCancellationRequested;
        }

        /// <summary>
        /// Gets the unique ID of this managed thread.
        /// </summary>
        public int ThreadId
        {
            get
            {
                if (theThread == null)
                    return 0;

                return theThread.ManagedThreadId;
            }
        }

        /// <summary>
        /// Gets if the underlying thread is alive.
        /// </summary>
        public bool IsThreadAlive
        {
            get
            {
                if (WasDisposed)
                    return false;
                if (ThreadState == ThreadState.Unstarted)
                    return true;

                return theThread.IsAlive;
            }
        }

        /// <summary>
        /// Gets the name of this thread.
        /// </summary>
        public string ThreadName
        {
            get
            {
                string name = theThread.Name;

                if (string.IsNullOrEmpty(name))
                    return "NULL";

                return name;
            }
        }

        /// <summary>
        /// Gets the type of this thread.
        /// </summary>
        public ThreadType Type
        {
            get => type;
            private set => type = value;
        }

        /// <summary>
        /// Gets the state of the underlaying thread.
        /// </summary>
        public ThreadState ThreadState
        {
            get
            {
                if (theThread == null)
                    return ThreadState.Aborted;

                return theThread.ThreadState;
            }
        }
        #endregion

        #region Constructor
        public NetThread(ThreadType type)
        {
            IsInLoop = false;
            IsThreadAbleToTick = false;
            waitUntil = DateTime.MinValue;
            Type = type;

            theThread = new Thread(new ThreadStart(ThreadEntryPoint));
            theThread.IsBackground = true;

            threadRunFlag = new AutoResetEvent(false);
            threadStopFlag = new ManualResetEvent(true);
            dispatcher = new Dispatcher(this);

            cancellationTokenSource = new CancellationTokenSource();
            cancellationToken = cancellationTokenSource.Token;
        }
        #endregion

        #region Methods
        /// <summary>
        /// Starts this thread.
        /// </summary>
        public void Launch()
        {
            if (WasDisposed)
                return;

            theThread.Start();
        }

        /// <summary>
        /// Tries to safely shut this thread down.
        /// </summary>
        public void TryShutdown()
        {
            if (!IsRunning)
                return;

            cancellationTokenSource.Cancel();
            ExpectShutdownAt = DateTime.UtcNow.AddSeconds(2.5d);
        }
        /// <summary>
        /// Forces the thread to shut down.
        /// </summary>
        public void ForceShutdown()
        {
            if (!IsRunning)
                return;

            theThread.Abort();
        }

        /// <summary>
        /// Disposes everything.
        /// </summary>
        public void Dispose()
        {
            if (WasDisposed)
                return;

            if (theThread != null)
            {
                theThread = null;
            }
            if (threadRunFlag != null)
            {
                threadRunFlag.Dispose();
                threadRunFlag = null;
            }
            if (threadStopFlag != null)
            {
                threadStopFlag.Dispose();
                threadStopFlag = null;
            }
            if (dispatcher != null)
            {
                dispatcher = null;
            }
            if (cancellationTokenSource != null)
            {
                cancellationTokenSource.Dispose();
                cancellationTokenSource = null;
            }

            WasDisposed = true;
        }

        /// <summary>
        /// Waits in the thread.
        /// </summary>
        /// <param name="ms">The time to wait in milliseconds.</param>
        public void Wait(int ms)
        {
            if (!IsRunning)
                return;
            if (BlockWait)
                return;

            IsThreadAbleToTick = false;
            IsCurrentlyWaiting = true;

            if (ms <= 0)
                waitUntil = DateTime.MinValue;
            else
                waitUntil = DateTime.UtcNow.AddMilliseconds(ms);

            do
            {
                ThreadWaitForContinue();

                if (!IsRunning)
                    break;
            }
            while (DateTime.UtcNow < waitUntil);

            IsCurrentlyWaiting = false;
            IsThreadAbleToTick = true;
        }

        /// <summary>
        /// Allows the thread to do a tick.
        /// <para>This should only be called from the main thread.</para>
        /// </summary>
        /// <param name="waitForEnd"></param>
        public void TickNow(bool waitForEnd = true)
        {
            //if (!IsRunning)
            //    return;
            if (!IsInLoop)
                return;
            if (IsThreadAbleToTick)
                return;

            //threadStopFlag.Reset();

            //if (waitForEnd)
            //{
            //    threadRunFlag.Set();
            //    threadStopFlag.WaitOne();
            //}
            //else
            //{
            //    threadRunFlag.Set();
            //}

            ThreadContinue(waitForEnd);
        }

        /// <summary>
        /// Sets the name of this thread.
        /// <para>This is really only used for debugging purposes.</para>
        /// </summary>
        /// <param name="name">The name of the thread.</param>
        public void SetThreadName(string name)
        {
            if (string.IsNullOrEmpty(name))
                return;

            theThread.Name = name;
        }

        private void ThreadBegin()
        {
            Helper.WriteToDebugOutput(Priority.Default, "Thread {0} ({1}) begins.", ThreadId, ThreadName);
            IsInLoop = true;
            IsThreadAbleToTick = false;
        }
        private void ThreadContinue(bool waitForEnd = true)
        {
            try
            {
                // Signal thread it can continue
                threadStopFlag.Reset();

                if (waitForEnd)
                {
                    threadRunFlag.Set();
                    threadStopFlag.WaitOne();
                }
                else
                {
                    threadRunFlag.Set();
                }
            }
            catch (Exception){}
        }
        private void ThreadWaitForContinue()
        {
            IsThreadAbleToTick = false;

            // Signal thread to wait
            try
            {
                threadStopFlag.Set();
                threadRunFlag.WaitOne();
            }
            catch (Exception){}

            IsThreadAbleToTick = true;
        }
        private void ThreadEnd()
        {
            Helper.WriteToDebugOutput(Priority.Default, "Thread {0} ({1}) ends.", ThreadId, ThreadName);
            IsThreadAbleToTick = false;
            IsInLoop = false;
            threadStopFlag.Set();
        }

        //public void Abort()
        //{
        //    if (theThread == null)
        //        return;
        //    if (!theThread.IsAlive)
        //        return;

        //    isRunning = false;

        //    ThreadEnd();

        //    // Abort thread
        //    theThread.Abort(); // TODO: Replace with a more graceful stopping of the thread. This way COULD corrupt some states
        //    OnEnd();

        //    //theThread = null;
        //}
        #endregion

        #region Functions
        /// <summary>
        /// Gets the <see cref="Dispatcher"/> of this <see cref="NetThread"/>.
        /// </summary>
        /// <returns>The <see cref="Dispatcher"/> of this <see cref="NetThread"/>.</returns>
        public Dispatcher GetDispatcher()
        {
            return dispatcher;
        }
        #endregion

        #region Virtual
        public virtual void OnStartup() { }
        public virtual void OnTick() { }
        public virtual void OnEnd() { }
        #endregion

        /// <summary>
        /// Entry-point of the managed thread.
        /// </summary>
        private void ThreadEntryPoint()
        {
            try
            {
                ThreadBegin();
                OnStartup();

                ThreadWaitForContinue();
                do
                {
                    // Process dispatcher queue
                    dispatcher.ProcessQueue();

                    OnTick();
                    ThreadWaitForContinue();
                }
                while (IsRunning);

                OnEnd();
            }
            catch (ThreadAbortException)
            {
                // Do nothing...
            }
            catch (Exception ex)
            {
                Helper.WriteToDebugOutput(Priority.High, "Exception caught in NetThread entry point! Details: {0}", ex);
            }

            ThreadEnd();
        }

    }
}
