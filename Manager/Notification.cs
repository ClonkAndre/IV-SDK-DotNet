using System;
using System.Collections.Generic;
using System.Drawing;

using IVSDKDotNet.Native;

namespace Manager {
    public class Notification {

        #region Variables
        public List<NotificationItem> Items;
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
            if (DoesNotificationExistsWithTag(tag))
                return false;

            string correctedTitle = title;
            string correctedDesc = description;

            if (correctedTitle.Length > 62) {
                correctedTitle = correctedTitle.Remove(59);
                correctedTitle += "...";
            }
            if (correctedDesc.Length > 63) {
                correctedDesc = correctedDesc.Remove(59);
                correctedDesc += "...";
            }

            // Add notification to list
            NotificationItem item = new NotificationItem(type, correctedTitle, correctedDesc, tag);
            Items.Add(item);

            // Start delayed action to remove the notification item
            Main.managerInstance.StartDelayedAction(Guid.NewGuid(), "Removing notification", showTime, (DelayedAction dA, object obj) => {
                ((NotificationItem)obj).FadeOut = true;
            }, item);

            return true;
        }
        private bool DoesNotificationExistsWithTag(string tag)
        {
            for (int i = 0; i < Items.Count; i++) {
                if (Items[i].Tag == tag) return true;
            }

            return false;
        }

        private Color GetColorFromNotificationType(int alpha, NotificationType style)
        {
            //switch (style) {
            //    case NotificationType.Default:  return Color.FromArgb(alpha, 255, 255, 255);
            //    case NotificationType.Error:    return Color.FromArgb(alpha, 255, 0, 0);
            //}
            return Color.FromArgb(alpha, 255, 255, 255);
        }
        #endregion

        #region Constructor
        internal Notification()
        {
            Items = new List<NotificationItem>();
        }
        #endregion

        public void Draw()
        {
            for (int i = 0; i < Items.Count; i++) {
                NotificationItem item = Items[i];

                // Animation
                if (item.FadeIn) {
                    if (!(item.BackgroundAlpha >= 110))
                        item.BackgroundAlpha += 12;
                    if (!(item.TextAlpha >= 255))
                        item.TextAlpha += 13;

                    if (item.TextAlpha > 255)
                        item.TextAlpha = 255;
                }
                if (item.FadeOut) {
                    if (!(item.BackgroundAlpha <= 0))
                        item.BackgroundAlpha -= 12;
                    if (!(item.TextAlpha <= 0))
                        item.TextAlpha -= 13;

                    if (item.BackgroundAlpha < 0)
                        item.BackgroundAlpha = 0;
                    if (item.TextAlpha < 0)
                        item.TextAlpha = 0;
                }

                // Check fade in
                if (item.FadeIn && item.BackgroundAlpha >= 110 && item.TextAlpha >= 255) item.FadeIn = false;

                // Remove from list
                if (item.FadeOut && item.BackgroundAlpha <= 0 && item.TextAlpha <= 0) Items.RemoveAt(i);

                Natives.DRAW_CURVED_WINDOW(.019f, .028f + i * .06f, .35f, .057f, item.BackgroundAlpha);

                DrawText(item.Title, new PointF(.027f, .0375f + i * .06f), new SizeF(.210f, .28f), GetColorFromNotificationType(item.TextAlpha, item.Type));
                DrawText(item.Description, new PointF(.027f, .0587f + i * .06f), new SizeF(.203f, .21f), Color.FromArgb(item.TextAlpha, 255, 255, 255));

            }
        }

    }
}
