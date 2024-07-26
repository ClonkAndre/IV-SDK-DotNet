using System;
using System.Collections.Generic;
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
            public bool FadeIn;
            public float Alpha;
            #endregion

            #region Constructor
            public NotificationItem(NotificationType type, string title, string description, string tag)
            {
                Type = type;
                Title = title;
                Description = description;
                Tag = tag;
                FadeOut = false;
                FadeIn = true;
            }
            #endregion
        }
        #endregion

        #region Methods
        public void Cleanup()
        {
            Items.Clear();
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

            // Add notification to list
            NotificationItem item = new NotificationItem(type, title, description, tag);
            Items.Add(item);

            // Start delayed action to remove the notification item
            Main.Instance.StartDelayedAction(Guid.NewGuid(), "Removing notification", showTime, (DelayedAction dA, object obj) =>
            {
                if (CLR.CLRBridge.IsShuttingDown)
                    return;

                ((NotificationItem)obj).FadeOut = true;
            }, item);

            return true;
        }
        private bool DoesNotificationExistsWithTag(string tag)
        {
            for (int i = 0; i < Items.Count; i++)
            {
                NotificationItem item = Items[i];

                if (string.IsNullOrEmpty(item.Tag))
                    return false;

                if (item.Tag == tag)
                    return true;
            }

            return false;
        }

        private Vector3 GetColorFromNotificationType(NotificationType type)
        {
            switch (type)
            {
                case NotificationType.Default:
                    {
                        Vector4 originalBorderColor = ImGuiIV.GetStyle().Colors[(int)eImGuiCol.Border];
                        return new Vector3(originalBorderColor.X, originalBorderColor.Y, originalBorderColor.Z);
                    }
                case NotificationType.Warning:
                    return new Vector3(1.0f, 1.0f, 0.0f);
                case NotificationType.Error:
                    return new Vector3(1.0f, 0.0f, 0.0f);

            }

            return Vector3.One;
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

                // Fading
                if (item.FadeOut)
                {
                    if (!(item.Alpha <= 0.0f))
                    {
                        if (IVPlayerInfo.FindThePlayerPed() != UIntPtr.Zero)
                            item.Alpha -= 1.8f * IVTimer.TimeStep;
                        else
                            item.Alpha -= 0.8f * IVTimer.TimeStep;
                    }

                    if (item.Alpha <= 0.0f)
                    {
                        item.FadeOut = false;
                        Items.RemoveAt(i);
                        continue;
                    }
                }
                if (item.FadeIn)
                {
                    if (!(item.Alpha >= 0.9f))
                    {
                        if (IVPlayerInfo.FindThePlayerPed() != UIntPtr.Zero)
                            item.Alpha += 1.8f * IVTimer.TimeStep;
                        else
                            item.Alpha += 1.0f * IVTimer.TimeStep;
                    }
                    else
                    {
                        item.FadeIn = false;
                    }
                }
                
                // Color stuff
                Vector4 originalTextColor = ImGuiIV.GetStyle().Colors[(int)eImGuiCol.Text];
                Vector3 notificationTypeColor = GetColorFromNotificationType(item.Type);

                ImGuiIV.PushStyleColor(eImGuiCol.Text,      new Vector4(originalTextColor.X, originalTextColor.Y, originalTextColor.Z, item.Alpha));
                ImGuiIV.PushStyleColor(eImGuiCol.Border,    new Vector4(notificationTypeColor, item.Alpha));
                ImGuiIV.PushStyleColor(eImGuiCol.Separator, new Vector4(notificationTypeColor, item.Alpha));

                ImGuiIV.PushStyleVar(eImGuiStyleVar.WindowPadding, new Vector2(10f));

                ImGuiIV.SetNextWindowBgAlpha(item.Alpha);

                // Notification
                ImGuiIV.Begin(string.Format("##IVSDKDotNetNotification_{0}", i), ref open, eImGuiWindowFlags.NoDecoration | eImGuiWindowFlags.NoInputs | eImGuiWindowFlags.NoNavFocus | eImGuiWindowFlags.NoFocusOnAppearing, eImGuiWindowFlagsEx.NoMouseEnable);
                
                ImGuiIV.Text(item.Title);
                ImGuiIV.Separator();
                ImGuiIV.Spacing();
                ImGuiIV.Text(item.Description);
                ImGuiIV.Dummy();

                ImGuiIV.SetWindowPos(new Vector2(38f, 30f + i * (ImGuiIV.GetWindowSize().Y + 8f)));

                ImGuiIV.End();

                ImGuiIV.PopStyleVar();
                ImGuiIV.PopStyleColor(3);
            }
        }

    }
}
