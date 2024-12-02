using System;
using System.Threading;

namespace Manager.Threading
{

    // Modified version of the NetThread from the ScriptHookDotNet project made by HazardX
    // https://github.com/HazardX/gta4_scripthookdotnet

    public class NetThread
    {

        #region Variables and Properties
        // Variables
        private bool isRunning;
        private bool isInLoop;
        private bool isThreadActive;
        private bool justWaitingForCommand;
        private DateTime waitUntil;

        // Thread stuff
        private Thread theThread;
        private AutoResetEvent threadRunFlag;
        private ManualResetEvent threadStopFlag;
        private Dispatcher dispatcher;

        // Properties
        public bool IsRunning
        {
            get => isRunning;
        }
        public bool CanWaitNow
        {
            get => isThreadActive;
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
        #endregion

        #region Constructor
        public NetThread()
        {
            isRunning = false;
            isInLoop = false;
            isThreadActive = false;
            waitUntil = DateTime.MinValue;

            theThread = new Thread(new ThreadStart(MainLoop));
            //theThread.SetApartmentState(ApartmentState.STA);

            threadRunFlag = new AutoResetEvent(false);
            threadStopFlag = new ManualResetEvent(true);
            dispatcher = new Dispatcher(this);
        }
        #endregion

        #region Virtual
        public virtual void OnTick() { }
        public virtual void OnStartup() { }
        public virtual void OnEnd() { }
        public virtual void OnThreadHalt() { }
        public virtual void OnThreadContinue() { }
        #endregion

        #region Methods
        public void Launch()
        {
            if (theThread == null)
                return;
            if (theThread.IsAlive)
                return;

            theThread.Start();
        }
        public void Abort()
        {
            if (theThread == null)
                return;
            if (!theThread.IsAlive)
                return;

            isRunning = false;

            ThreadEnd();

            // Abort thread
            theThread.Abort();
            OnEnd();

            theThread = null;
        }

        private void ThreadBegin()
        {
            isRunning = true;
            isInLoop = true;
            isThreadActive = false;
        }
        private void ThreadWaitForContinue()
        {
            try
            {
                if (isThreadActive)
                {
                    isThreadActive = false;
                    OnThreadHalt();
                }

                threadStopFlag.Set();
                threadRunFlag.WaitOne();

                isThreadActive = true;
                OnThreadContinue();
            }
            catch (Exception ex)
            {
                Helper.WriteToDebugOutput(Priority.High, "Error in Thread {0} 'ThreadWaitForContinue' function! Details: {1}", ThreadId, ex);
            }
        }
        private void ThreadEnd()
        {
            if (isThreadActive)
            {
                isThreadActive = false;
                OnThreadHalt();
            }
            isInLoop = false;
            threadStopFlag.Set();
        }

        public void Wait(int ms)
        {
            isThreadActive = false;
            OnThreadHalt();

            if (ms <= 0)
                waitUntil = DateTime.MinValue;
            else
                waitUntil = DateTime.UtcNow + TimeSpan.FromMilliseconds(ms);

            try
            {
                do
                {
                    threadStopFlag.Set();
                    threadRunFlag.WaitOne();

                    if (!isRunning)
                        Thread.CurrentThread.Abort();

                } while (DateTime.UtcNow < waitUntil);
            }
            catch (Exception ex)
            {
                Helper.WriteToDebugOutput(Priority.High, "Error in Thread {0} 'Wait' function! Details: {1}", ThreadId, ex);
            }

            isThreadActive = true;
            OnThreadContinue();
        }
        private void WaitForCommandResult()
        {
            justWaitingForCommand = true;
            isThreadActive = false;

            threadStopFlag.Set();
            threadRunFlag.WaitOne();

            isThreadActive = true;
        }

        private void TickNow(bool waitForEnd)
        {
            if (!isInLoop)
                return;
            if (isThreadActive)
                return;

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
        #endregion

        #region Functions
        // This is called from the main thread
        public bool TickNowWithState()
        {
            // Process dispatcher
            dispatcher.ProcessQueue();

            // Allow thread to tick
            justWaitingForCommand = false;
            TickNow(true);
            return justWaitingForCommand;
        }

        /// <summary>
        /// Gets the <see cref="Dispatcher"/> of this <see cref="NetThread"/>.
        /// </summary>
        /// <returns>The <see cref="Dispatcher"/> of this <see cref="NetThread"/>.</returns>
        public Dispatcher GetDispatcher()
        {
            return dispatcher;
        }
        #endregion

        private void MainLoop()
        {
            ThreadBegin();
            ThreadWaitForContinue();
            OnStartup();
            while (isRunning)
            {
                ThreadWaitForContinue();
                OnTick();
            }
            OnEnd();
            ThreadEnd();
        }

    }
}
