using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

using SharpDX.Direct3D9;

using IVSDKDotNet;
using IVSDKDotNet.Native;
using Manager.Direct3D9;

namespace Manager.Classes
{
    internal class Mouse : IDisposable
    {
        #region DllImports
        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool GetCursorPos(out POINT point);

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool SetCursorPos(int x, int y);
        #endregion

        #region Variables and Properties
        // Variables
        private bool disposed;
        private bool isVisible;

        private Texture cursorTexture;
        private Size cursorSize = new Size(16, 21);

        // Properties
        public bool IsDisposed
        {
            get { return disposed; }
        }
        public bool IsVisible
        {
            get
            {
                if (IsDisposed)
                    return false;

                return isVisible;
            }
            set
            {
                if (IsDisposed)
                    return;

                if (value)
                    Position = new Point(CGame.Resolution.Width / 2, CGame.Resolution.Height / 2);

                isVisible = value;
            }
        }

        public bool LeftButtonDown
        {
            get
            {
                if (IsDisposed)
                    return false;

                return IVSDKDotNet.Helper.IsKeyPressedAsync(Keys.LButton);
            }
        }
        public bool RightButtonDown
        {
            get
            {
                if (IsDisposed)
                    return false;

                return IVSDKDotNet.Helper.IsKeyPressedAsync(Keys.RButton);
            }
        }
        public bool XButton1Down
        {
            get
            {
                if (IsDisposed)
                    return false;

                return IVSDKDotNet.Helper.IsKeyPressedAsync(Keys.XButton1);
            }
        }
        public bool XButton2Down
        {
            get
            {
                if (IsDisposed)
                    return false;

                return IVSDKDotNet.Helper.IsKeyPressedAsync(Keys.XButton2);
            }
        }

        public int MouseWheel
        {
            get
            {
                if (IsDisposed)
                    return 0;

                Natives.GET_MOUSE_WHEEL(out int v);
                return v;
            }
        }

        public Size CursorSize
        {
            get
            {
                if (IsDisposed)
                    return Size.Empty;

                return cursorSize;
            }
            set
            {
                if (IsDisposed)
                    return;
                if (value == Size.Empty)
                    return;
                if (value.Width < 16 && value.Height < 16)
                    return;

                cursorSize = value;
            }
        }
        public Point Position
        {
            get
            {
                if (IsDisposed)
                    return Point.Empty;
                if (GetCursorPos(out POINT pos))
                    return new Point(pos.X, pos.Y);

                return Point.Empty;
            }
            set
            {
                if (IsDisposed)
                    return;
                if (!Main.Instance.IsGTAIVWindowInFocus)
                    return;

                SetCursorPos(value.X, value.Y);
            }
        }
        #endregion

        #region Structs
        [StructLayout(LayoutKind.Sequential)]
        private struct POINT
        {
            public int X;
            public int Y;

            public override string ToString()
            {
                return string.Format("<X: {0}, Y: {1}>", X.ToString(), Y.ToString());
            }
        }
        #endregion

        #region Constructor
        public Mouse(IntPtr device)
        {
            try
            {
                cursorTexture = Texture.FromMemory((Device)device, Properties.Resources.cursor, -2, -2, 1, Usage.None, Format.A8R8G8B8, Pool.Managed, Filter.Default, Filter.Default, 0);
            }
            catch (Exception ex)
            {
                Main.Instance.Console.PrintError(string.Format("An error occured while trying to create cursor texture. Mouse cursor will not be available. Details: {0}", ex.ToString()));
                Dispose();
            }
        }
        #endregion

        #region Disposing
        protected virtual void Dispose(bool disposing)
        {
            if (!disposed)
            {
                if (disposing)
                {
                    // TODO: dispose managed state (managed objects)
                }

                // Free unmanaged resources (unmanaged objects)
                if (cursorTexture != null)
                {
                    cursorTexture.Dispose();
                    cursorTexture = null;
                }

                disposed = true;
            }
        }
        public void Dispose()
        {
            // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }
        #endregion

        #region Functions
        /// <summary>
        /// Bypasses the in focus check otherwise same as <see cref="Position"/>. 
        /// </summary>
        /// <param name="pos">The new cursor pos.</param>
        /// <returns>True if successful. Otherwise, false.</returns>
        public bool ForceSetCursorPos(Point pos)
        {
            if (IsDisposed)
                return false;

            return SetCursorPos(pos.X, pos.Y);
        }

        public bool IntersectsWith(Rectangle rect)
        {
            if (IsVisible)
                return new Rectangle(Position, CursorSize).IntersectsWith(rect);

            return false;
        }
        #endregion

        public void Draw(IntPtr device)
        {
            if (IsDisposed)
                return;
            if (!IsVisible)
                return;

            Drawing.DrawTexture(null, device, cursorTexture.NativePointer, new RectangleF(Position, CursorSize), 0f, Color.White);
        }

    }
}
