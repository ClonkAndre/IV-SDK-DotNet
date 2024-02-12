using System;
using System.Collections.Generic;
using System.Drawing;
using System.Numerics;

using IVSDKDotNet;
using IVSDKDotNet.Enums;

using Manager.Classes;

namespace Manager.UI
{
    public class NotificationUI
    {

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
            public bool FadeOut;
            public float TextAlpha;
            public float BackgroundAlpha;
            #endregion

            #region Constructor
            public NotificationItem(NotificationType type, string title, string description, string tag)
            {
                Type = type;
                Title = title;
                Description = description;
                Tag = tag;
                FadeOut = false;
                TextAlpha = 1.0f;
                BackgroundAlpha = 0.8f;
            }
            #endregion
        }
        #endregion

        #region Functions
        public bool ShowNotification(NotificationType type, DateTime showTime, string title, string description, string tag)
        {
            if (!Config.ShowNotifications)
                return false;

            if (!string.IsNullOrEmpty(tag))
            {
                if (DoesNotificationExistsWithTag(tag))
                    return false;
            }

            //string correctedTitle = title;
            //string correctedDesc = description;

            //if (correctedTitle.Length > 62)
            //{
            //    correctedTitle = correctedTitle.Remove(59);
            //    correctedTitle += "...";
            //}
            //if (correctedDesc.Length > 63)
            //{
            //    correctedDesc = correctedDesc.Remove(59);
            //    correctedDesc += "...";
            //}

            // Add notification to list
            NotificationItem item = new NotificationItem(type, title, description, tag);
            Items.Add(item);

            // Start delayed action to remove the notification item
            Main.Instance.StartDelayedAction(Guid.NewGuid(), "Removing notification", showTime, (DelayedAction dA, object obj) =>
            {
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
        internal NotificationUI()
        {
            Items = new List<NotificationItem>();
        }
        #endregion

        public void DoUI()
        {
            bool open = true;

            for (int i = 0; i < Items.Count; i++)
            {
                NotificationItem item = Items[i];

                if (item.FadeOut)
                {
                    if (!(item.BackgroundAlpha <= 0.0f))
                        item.BackgroundAlpha -= 0.01f;
                    if (!(item.TextAlpha <= 0.0f))
                        item.TextAlpha -= 0.01f;

                    if (item.BackgroundAlpha <= 0.0f && item.TextAlpha <= 0.0f)
                    {
                        item.FadeOut = false;
                        Items.RemoveAt(i);
                    }
                }

                ImGuiIV.SetNextWindowBgAlpha(item.BackgroundAlpha);
                ImGuiIV.SetNextWindowPos(new Vector2(40f, 32f + i * 55f));

                ImGuiIV.PushStyleColor(eImGuiCol.ImGuiCol_Text, new Vector4(1f, 1f, 1f, item.TextAlpha));
                ImGuiIV.PushStyleColor(eImGuiCol.ImGuiCol_Border, new Vector4(0.7f, 0.7f, 0.7f, item.BackgroundAlpha));
                ImGuiIV.Begin(string.Format("Notification {0}", i), ref open, eImGuiWindowFlags.NoDecoration | eImGuiWindowFlags.NoInputs | eImGuiWindowFlags.NoNavFocus | eImGuiWindowFlags.NoFocusOnAppearing, true);
                ImGuiIV.Text(item.Title);
                ImGuiIV.Text(item.Description);
                ImGuiIV.End();
                ImGuiIV.PopStyleColor(2);
            }
        }

    }
}
