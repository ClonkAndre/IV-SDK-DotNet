using System;
using System.Collections.Generic;
using System.Numerics;

using IVSDKDotNet;
using IVSDKDotNet.Enums;

using Manager.Classes;

namespace Manager.UI
{
    public struct NotificationContent
    {
        #region Variables
        public string Title;
        public string Description;
        public string AdditionalContent;
        #endregion

        #region Constructor
        public NotificationContent(string title, string desc, string additionalContent)
        {
            Title = title;
            Description = desc;
            AdditionalContent = additionalContent;
        }
        #endregion
    }

    public class NotificationUI
    {

        #region Variables
        private List<NotificationItem> items;
        #endregion

        #region Classes
        public class NotificationItem
        {
            #region Variables
            public NotificationType Type;
            public string Title;
            public string Description;
            public string AdditionalContent;
            public string Tag;

            public bool CanBeRemoved;

            // Animation stuff
            public bool FadeIn;
            public float Alpha;
            #endregion

            #region Constructor
            public NotificationItem(NotificationType type, string title, string description, string additionalContent, string tag)
            {
                Type = type;
                Title = title;
                Description = description;
                AdditionalContent = additionalContent;
                Tag = tag;
                FadeIn = true;
            }
            #endregion
        }
        #endregion

        #region Methods
        public void Cleanup()
        {
            items.Clear();
        }
        #endregion

        #region Functions
        public bool ShowNotificationEx(NotificationType type, DateTime showTime, NotificationContent content, string tag)
        {
            if (!Config.ShowNotifications)
                return false;

            if (!string.IsNullOrEmpty(tag))
            {
                if (DoesNotificationExistsWithTag(tag))
                    return false;
            }

            if (string.IsNullOrEmpty(content.Title))
                return false;

            // Add notification to list
            NotificationItem item = new NotificationItem(type, content.Title, content.Description, content.AdditionalContent, tag);
            items.Add(item);

            // Start delayed action to remove the notification item
            Main.Instance.StartDelayedAction(Guid.NewGuid(), "Removing notification", showTime, (DelayedAction dA, object obj) =>
            {
                if (CLR.CLRBridge.IsShuttingDown)
                    return;

                ((NotificationItem)obj).CanBeRemoved = true;
            }, item);

            return true;
        }
        public bool ShowNotification(NotificationType type, DateTime showTime, string title, string description, string tag)
        {
            if (!Config.ShowNotifications)
                return false;

            if (!string.IsNullOrEmpty(tag))
            {
                if (DoesNotificationExistsWithTag(tag))
                    return false;
            }

            if (string.IsNullOrEmpty(title))
                return false;

            // Add notification to list
            NotificationItem item = new NotificationItem(type, title, description, null, tag);
            items.Add(item);

            // Start delayed action to remove the notification item
            Main.Instance.StartDelayedAction(Guid.NewGuid(), "Removing notification", showTime, (DelayedAction dA, object obj) =>
            {
                if (CLR.CLRBridge.IsShuttingDown)
                    return;

                ((NotificationItem)obj).CanBeRemoved = true;
            }, item);

            return true;
        }

        private bool DoesNotificationExistsWithTag(string tag)
        {
            for (int i = 0; i < items.Count; i++)
            {
                NotificationItem item = items[i];

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
                case NotificationType.Info:
                    return new Vector3(0.0f, 0.533f, 1.0f);
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
            items = new List<NotificationItem>(4);
        }
        #endregion

        public void DoUI()
        {
            bool open = true;

            for (int i = 0; i < items.Count; i++)
            {
                NotificationItem item = items[i];

                if (item.CanBeRemoved)
                {
                    items.RemoveAt(i);
                    continue;
                }

                // Fading
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

                // Begin Notification UI
                {
                    ImGuiIV.Begin(string.Format("##IVSDKDotNetNotification_{0}", i), ref open, eImGuiWindowFlags.NoDecoration | eImGuiWindowFlags.NoInputs | eImGuiWindowFlags.NoNavFocus | eImGuiWindowFlags.NoFocusOnAppearing, eImGuiWindowFlagsEx.NoMouseEnable);

                    // Title
                    ImGuiIV.Text(item.Title);

                    ImGuiIV.Separator();
                    ImGuiIV.Spacing();

                    // Description
                    ImGuiIV.Text(item.Description);

                    // Additional Content
                    if (!string.IsNullOrEmpty(item.AdditionalContent))
                        ImGuiIV.Text(item.AdditionalContent);

                    ImGuiIV.Dummy();

                    ImGuiIV.SetWindowPos(new Vector2(38f, 30f + i * (ImGuiIV.GetWindowSize().Y + 8f)));

                    ImGuiIV.End();
                }

                ImGuiIV.PopStyleVar();
                ImGuiIV.PopStyleColor(3);
            }
        }

    }
}
