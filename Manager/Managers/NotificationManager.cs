using System;
using System.Collections.Generic;
using System.Drawing;
using System.Numerics;

using IVSDKDotNet.Native;
using IVSDKDotNet.Direct3D9;

using Manager.Classes;
using Manager.Direct3D9;

namespace Manager.Managers
{
    public class NotificationManager
    {

        #region Variables
        public List<NotificationItem> Items;
        public bool UseOldDrawingSystem;
        #endregion

        #region Classes
        public class NotificationItem
        {
            #region Variables
            public NotificationType Type;
            public string Title;
            public string Description;
            public string Tag;

            // Animation stuff
            public bool FadeIn;
            public bool FadeOut;
            public int TextAlpha;
            public uint BackgroundAlpha;
            #endregion

            #region Constructor
            public NotificationItem(NotificationType type, string title, string description, string tag)
            {
                Type = type;
                Title = title;
                Description = description;
                Tag = tag;
                FadeIn = true;
                FadeOut = false;
                TextAlpha = 0;
                BackgroundAlpha = 0;
            }
            #endregion
        }
        #endregion

        #region Methods
        private void DrawText(string str, PointF pos, SizeF scale, Color color)
        {
            Natives.SET_TEXT_SCALE(scale.Width, scale.Height);
            Natives.SET_TEXT_COLOUR(color.R, color.G, color.B, color.A);
            Natives.SET_TEXT_DROPSHADOW(false, 0, 0, 0, 0);
            Natives.DISPLAY_TEXT_WITH_LITERAL_STRING(pos.X, pos.Y, "NF_SERVER_NAME", str);
        }
        #endregion

        #region Functions
        public bool ShowNotification(NotificationType type, DateTime showTime, string title, string description, string tag)
        {
            if (!string.IsNullOrEmpty(tag))
            {
                if (DoesNotificationExistsWithTag(tag))
                    return false;
            }

            string correctedTitle = title;
            string correctedDesc = description;

            if (correctedTitle.Length > 62)
            {
                correctedTitle = correctedTitle.Remove(59);
                correctedTitle += "...";
            }
            if (correctedDesc.Length > 63)
            {
                correctedDesc = correctedDesc.Remove(59);
                correctedDesc += "...";
            }

            // Add notification to list
            NotificationItem item = new NotificationItem(type, correctedTitle, correctedDesc, tag);
            Items.Add(item);

            // Start delayed action to remove the notification item
            Main.Instance.StartDelayedAction(Guid.NewGuid(), "Removing notification", showTime, (DelayedAction dA, object obj) => {
                ((NotificationItem)obj).FadeOut = true;
            }, item);

            return true;
        }
        private bool DoesNotificationExistsWithTag(string tag)
        {
            for (int i = 0; i < Items.Count; i++)
            {
                if (Items[i].Tag == tag)
                    return true;
            }

            return false;
        }

        private Color GetColorFromNotificationType(int alpha, NotificationType type)
        {
            switch (type)
            {
                case NotificationType.Default:  return Color.FromArgb(alpha, Color.White);
                case NotificationType.Error:    return Color.FromArgb(alpha, 255, 80, 80);
                default:                        return Color.FromArgb(alpha, Color.White);
            }
        }
        #endregion

        #region Constructor
        internal NotificationManager()
        {
            Items = new List<NotificationItem>();
        }
        #endregion

        public void Draw(IntPtr device)
        {
            for (int i = 0; i < Items.Count; i++)
            {
                NotificationItem item = Items[i];

                // Animation
                if (item.FadeIn)
                {
                    if (!(item.BackgroundAlpha >= 150))
                        item.BackgroundAlpha += 12;
                    if (!(item.TextAlpha >= 255))
                        item.TextAlpha += 13;

                    if (item.TextAlpha > 255)
                        item.TextAlpha = 255;
                }
                if (item.FadeOut)
                {
                    if (!(item.BackgroundAlpha <= 0))
                        item.BackgroundAlpha -= 12;
                    if (!(item.TextAlpha <= 0))
                        item.TextAlpha -= 14;

                    if (item.BackgroundAlpha < 0)
                        item.BackgroundAlpha = 0;
                    if (item.TextAlpha < 0)
                        item.TextAlpha = 0;
                }

                // Check fade in
                if (item.FadeIn && item.BackgroundAlpha >= 150 && item.TextAlpha >= 255)
                    item.FadeIn = false;

                // Remove from list
                if (item.FadeOut && item.BackgroundAlpha <= 0 && item.TextAlpha <= 0)
                {
                    Items.RemoveAt(i);
                    continue;
                }

                if (UseOldDrawingSystem)
                {
                    Natives.DRAW_CURVED_WINDOW(.019f, .028f + i * .06f, .35f, .057f, item.BackgroundAlpha);

                    DrawText(item.Title, new PointF(.027f, .0375f + i * .06f), new SizeF(.210f, .28f), GetColorFromNotificationType(item.TextAlpha, item.Type));
                    DrawText(item.Description, new PointF(.027f, .0587f + i * .06f), new SizeF(.203f, .21f), Color.FromArgb(item.TextAlpha, 255, 255, 255));
                }
                else
                {
                    Rectangle rect = new Rectangle(Main.Instance.Console.IsConsoleVisible ? 10 : 38, (Main.Instance.Console.IsConsoleVisible ? Main.Instance.Console.ConsoleHeight + 10 : 32) + i * 60, 670, 60);

                    Drawing.DrawBoxRounded(null, device, new Vector2(rect.X, rect.Y), new SizeF(rect.Width, rect.Height), 6f, false, Color.FromArgb((int)item.BackgroundAlpha, Color.Black), Color.White);

                    IntPtr fontPtr = Main.Instance.LocalD3D9Font.NativePointer;
                    Drawing.DrawString(null, fontPtr, item.Title, new Rectangle(rect.X + 8, rect.Y + 6, rect.Width, rect.Height).ToRawRectangle(), eD3DFontDrawFlags.Left, GetColorFromNotificationType(item.TextAlpha, item.Type));
                    Drawing.DrawString(null, fontPtr, item.Description, new Rectangle(rect.X + 8, rect.Y + 27, rect.Width, rect.Height).ToRawRectangle(), eD3DFontDrawFlags.Left, Color.FromArgb(item.TextAlpha, Color.White));
                }
            }
        }

    }
}
