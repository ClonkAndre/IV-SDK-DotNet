using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Reflection;

using IVSDKDotNet;
using IVSDKDotNet.Attributes;
using IVSDKDotNet.Enums;

using Manager.Classes;

// Designed with ImRAD
// Check out the project on GitHub: https://github.com/tpecholt/imrad

namespace Manager.UI
{
    internal class ManagerUI
    {

        #region Variables
        public static bool IsConfigUIOpened;
        private static bool invalidKey;

        private static DateTime nextRefresh = DateTime.MinValue;

        // Filter
        private static bool showIVSDKDotNetScripts = true;
        private static bool showScriptHookDotNetScripts = true;
        private static string scriptNameFilter;

        // Developer
        private static int selectedModuleIndex;
        private static string targetModuleOffset;
        private static string readModuleValue;

        // Other
        private static IntPtr ivsdkDotNetLogo;
        #endregion

        #region Methods
        private static void AddField(FoundScript foundScript, FieldInfo info)
        {
            // Early handle custom attributes for members
            object[] customAttributes = info.GetCustomAttributes(false);
            for (int i = 0; i < customAttributes.Length; i++)
            {
                object attributeObj = customAttributes[i];

                if (attributeObj.GetType() == typeof(HideInInspectorAttribute))
                {
                    return;
                }
                else if (attributeObj.GetType() == typeof(SeparatorAttribute))
                {
                    SeparatorAttribute a = attributeObj as SeparatorAttribute;

                    if (string.IsNullOrWhiteSpace(a.Text))
                        ImGuiIV.Separator();
                    else
                        ImGuiIV.SeparatorText(a.Text);
                }
                else if (attributeObj.GetType() == typeof(SpaceAttribute))
                {
                    ImGuiIV.Dummy(new Vector2(0f, (attributeObj as SpaceAttribute).Height));
                }
            }

            if (IsTypeSupported(info.FieldType, out SupportedPublicFields fieldType))
            {
                // The field name
                ImGuiIV.Text(info.Name);

                // Check if readonly attribute is set
                bool readOnlyAttributeSet = false;
                if (GetAttribute(info, out ReadOnlyInInspectorAttribute readOnlyInInspectorAttribute))
                {
                    readOnlyAttributeSet = true;
                    ImGuiIV.BeginDisabled();
                }

                // Get other attributes
                float speed = 1f;
                float min = 0f;
                float max = 0f;

                if (GetAttribute(info, out SpeedAttribute speedAttribute))
                    speed = speedAttribute.Speed;
                if (GetAttribute(info, out RangeAttribute rangeAttribute))
                {
                    min = rangeAttribute.Minimum;
                    max = rangeAttribute.Maximum;
                }

                switch (fieldType)
                {
                    case SupportedPublicFields._byte:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.TheScriptObject, Convert.ToByte(value));
                        }
                        break;
                    case SupportedPublicFields._sbyte:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.TheScriptObject, Convert.ToSByte(value));
                        }
                        break;
                    case SupportedPublicFields._short:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.TheScriptObject, Convert.ToInt16(value));
                        }
                        break;
                    case SupportedPublicFields._ushort:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.TheScriptObject, Convert.ToUInt16(value));
                        }
                        break;
                    case SupportedPublicFields._int:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.TheScriptObject, value);
                        }
                        break;
                    case SupportedPublicFields._uint:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.TheScriptObject, Convert.ToUInt32(value));
                        }
                        break;
                    case SupportedPublicFields._long:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.TheScriptObject, Convert.ToInt64(value));
                        }
                        break;
                    case SupportedPublicFields._ulong:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.TheScriptObject, Convert.ToUInt64(value));
                        }
                        break;
                    case SupportedPublicFields._float:
                        {
                            float value = Convert.ToSingle(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat(string.Format("##{0}", info.Name), ref value, speed, min, max))
                                info.SetValue(foundScript.TheScriptObject, Convert.ToSingle(value));
                        }
                        break;
                    case SupportedPublicFields._double:
                        {
                            float value = Convert.ToSingle(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat(string.Format("##{0}", info.Name), ref value, speed, min, max))
                                info.SetValue(foundScript.TheScriptObject, Convert.ToDouble(value));
                        }
                        break;
                    case SupportedPublicFields._decimal:
                        {
                            float value = Convert.ToSingle(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat(string.Format("##{0}", info.Name), ref value, speed, min, max))
                                info.SetValue(foundScript.TheScriptObject, Convert.ToDecimal(value));
                        }
                        break;
                    case SupportedPublicFields._bool:
                        {
                            bool value = Convert.ToBoolean(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.CheckBox(string.Format("##{0}", info.Name), ref value))
                                info.SetValue(foundScript.TheScriptObject, value);
                        }
                        break;
                    case SupportedPublicFields._string:
                        {
                            string value = Convert.ToString(info.GetValue(foundScript.TheScriptObject));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.InputText(string.Format("##{0}", info.Name), ref value))
                                info.SetValue(foundScript.TheScriptObject, value);
                        }
                        break;
                    case SupportedPublicFields._Vector2:
                        {
                            Vector2 value = (Vector2)info.GetValue(foundScript.TheScriptObject);
                            float[] arr = new float[2] { value.X, value.Y };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat2(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.TheScriptObject, new Vector2(arr[0], arr[1]));
                        }
                        break;
                    case SupportedPublicFields._Vector3:
                        {
                            Vector3 value = (Vector3)info.GetValue(foundScript.TheScriptObject);
                            float[] arr = new float[3] { value.X, value.Y, value.Z };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat3(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.TheScriptObject, new Vector3(arr[0], arr[1], arr[2]));
                        }
                        break;
                    case SupportedPublicFields._Vector4:
                        {
                            Vector4 value = (Vector4)info.GetValue(foundScript.TheScriptObject);
                            float[] arr = new float[4] { value.X, value.Y, value.Z, value.W };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat4(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.TheScriptObject, new Vector4(arr[0], arr[1], arr[2], arr[3]));
                        }
                        break;
                    case SupportedPublicFields._Quaternion:
                        {
                            Quaternion value = (Quaternion)info.GetValue(foundScript.TheScriptObject);
                            float[] arr = new float[4] { value.X, value.Y, value.Z, value.W };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat4(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.TheScriptObject, new Quaternion(arr[0], arr[1], arr[2], arr[3]));
                        }
                        break;
                    case SupportedPublicFields._Color:
                        {
                            Color value = (Color)info.GetValue(foundScript.TheScriptObject);
                            Vector4 arr = ImGuiIV.ColorToFloatRGB(value);

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.ColorEdit4(string.Format("##{0}", info.Name), ref arr, eImGuiColorEditFlags.InputRGB))
                                info.SetValue(foundScript.TheScriptObject, ImGuiIV.FloatRGBToColor(arr));
                        }
                        break;
                    case SupportedPublicFields._Size:
                        {
                            Size value = (Size)info.GetValue(foundScript.TheScriptObject);
                            int[] arr = new int[2] { value.Width, value.Height };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt2(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.TheScriptObject, new Size(arr[0], arr[1]));
                        }
                        break;
                    case SupportedPublicFields._SizeF:
                        {
                            SizeF value = (SizeF)info.GetValue(foundScript.TheScriptObject);
                            float[] arr = new float[2] { value.Width, value.Height };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat2(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.TheScriptObject, new SizeF(arr[0], arr[1]));
                        }
                        break;
                    case SupportedPublicFields._Point:
                        {
                            Point value = (Point)info.GetValue(foundScript.TheScriptObject);
                            int[] arr = new int[2] { value.X, value.Y };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt2(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.TheScriptObject, new Point(arr[0], arr[1]));
                        }
                        break;
                    case SupportedPublicFields._PointF:
                        {
                            PointF value = (PointF)info.GetValue(foundScript.TheScriptObject);
                            float[] arr = new float[2] { value.X, value.Y };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat2(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.TheScriptObject, new PointF(arr[0], arr[1]));
                        }
                        break;
                    case SupportedPublicFields._IList:
                        {
                            object obj = info.GetValue(foundScript.TheScriptObject);

                            if (obj == null)
                            {
                                ImGuiIV.SameLine(0f, 30f);
                                ImGuiIV.TextColored(Color.Yellow, "This list is not initialized yet.");
                                break;
                            }

                            IList value = (IList)obj;
                            
                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            ImGuiIV.TextColored(Color.Yellow, "There are {0} element(s) in this list.", value.Count);

                            if (ImGuiIV.TreeNode(string.Format("Click to show content of {0}.", info.Name)))
                            {
                                ImGuiIV.SetNextItemWidth(ImGuiIV.GetContentRegionAvail().X);
                                if (ImGuiIV.BeginListBox(string.Format("##{0}", info.Name)))
                                {
                                    for (int i = 0; i < value.Count; i++)
                                        ImGuiIV.Selectable(value[i].ToString());

                                    ImGuiIV.EndListBox();
                                }
                                ImGuiIV.TreePop();
                            }
                        }
                        break;
                    case SupportedPublicFields._ICollection:
                        {
                            object obj = info.GetValue(foundScript.TheScriptObject);

                            if (obj == null)
                            {
                                ImGuiIV.SameLine(0f, 30f);
                                ImGuiIV.TextColored(Color.Yellow, "This collection is not initialized yet.");
                                break;
                            }

                            ICollection value = (ICollection)obj;

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            ImGuiIV.TextColored(Color.Yellow, "There are {0} element(s) in this collection.", value.Count);

                            if (ImGuiIV.TreeNode(string.Format("Click to show content of {0}.", info.Name)))
                            {
                                ImGuiIV.SetNextItemWidth(ImGuiIV.GetContentRegionAvail().X);
                                if (ImGuiIV.BeginListBox(string.Format("##{0}", info.Name)))
                                {
                                    foreach (object item in value)
                                        ImGuiIV.Selectable(item.ToString());

                                    ImGuiIV.EndListBox();
                                }
                                ImGuiIV.TreePop();
                            }
                        }
                        break;
                }

                if (readOnlyAttributeSet)
                    ImGuiIV.EndDisabled();

                // What type this field is
                ImGuiIV.SetItemTooltip(string.Format("This field is a {0}.", info.FieldType.Name));

                // Add help marker if attribute was set so the dev can add comments to these fields in the manager
                if (GetAttribute(info, out HelpMarkerAttribute attr))
                {
                    ImGuiIV.SameLine();
                    ImGuiIV.HelpMarker(attr.Text);
                }

#if DEBUG
                ImGuiIV.SameLine();
                ImGuiIV.TextDisabled(info.FieldType.FullName);
#endif
            }
        }
        #endregion

        #region Functions
        private static bool GetAttribute<T>(FieldInfo field, out T attribute)
        {
            object foundAttribute = field.GetCustomAttribute(typeof(T));

            if (foundAttribute == null)
            {
                attribute = default(T);
                return false;
            }

            attribute = (T)foundAttribute;
            return true;
        }
        private static bool IsTypeSupported(Type t, out SupportedPublicFields fieldType)
        {
            // byte
            if (t == typeof(byte))
            {
                fieldType = SupportedPublicFields._byte;
                return true;
            }

            // sbyte
            else if (t == typeof(sbyte))
            {
                fieldType = SupportedPublicFields._sbyte;
                return true;
            }

            // short
            else if (t == typeof(short))
            {
                fieldType = SupportedPublicFields._short;
                return true;
            }

            // ushort
            else if (t == typeof(ushort))
            {
                fieldType = SupportedPublicFields._ushort;
                return true;
            }

            // int
            else if (t == typeof(int))
            {
                fieldType = SupportedPublicFields._int;
                return true;
            }

            // uint
            else if (t == typeof(uint))
            {
                fieldType = SupportedPublicFields._uint;
                return true;
            }

            // long
            else if (t == typeof(long))
            {
                fieldType = SupportedPublicFields._long;
                return true;
            }

            // ulong
            else if (t == typeof(ulong))
            {
                fieldType = SupportedPublicFields._ulong;
                return true;
            }

            // float
            else if (t == typeof(float))
            {
                fieldType = SupportedPublicFields._float;
                return true;
            }

            // double
            else if (t == typeof(double))
            {
                fieldType = SupportedPublicFields._double;
                return true;
            }

            // decimal
            else if (t == typeof(decimal))
            {
                fieldType = SupportedPublicFields._decimal;
                return true;
            }

            // bool
            else if (t == typeof(bool))
            {
                fieldType = SupportedPublicFields._bool;
                return true;
            }

            // string
            else if (t == typeof(string))
            {
                fieldType = SupportedPublicFields._string;
                return true;
            }

            // Vector2
            else if (t == typeof(Vector2))
            {
                fieldType = SupportedPublicFields._Vector2;
                return true;
            }

            // Vector3
            else if (t == typeof(Vector3))
            {
                fieldType = SupportedPublicFields._Vector3;
                return true;
            }

            // Vector4
            else if (t == typeof(Vector4))
            {
                fieldType = SupportedPublicFields._Vector4;
                return true;
            }

            // Quaternion
            else if (t == typeof(Quaternion))
            {
                fieldType = SupportedPublicFields._Quaternion;
                return true;
            }

            // Color
            else if (t == typeof(Color))
            {
                fieldType = SupportedPublicFields._Color;
                return true;
            }

            // Size
            else if (t == typeof(Size))
            {
                fieldType = SupportedPublicFields._Size;
                return true;
            }

            // SizeF
            else if (t == typeof(SizeF))
            {
                fieldType = SupportedPublicFields._SizeF;
                return true;
            }

            // Point
            else if (t == typeof(Point))
            {
                fieldType = SupportedPublicFields._Point;
                return true;
            }

            // PointF
            else if (t == typeof(PointF))
            {
                fieldType = SupportedPublicFields._PointF;
                return true;
            }

            // List
            else if (t.IsGenericType && t.GetGenericTypeDefinition() == typeof(List<>))
            {
                fieldType = SupportedPublicFields._IList;
                return true;
            }

            // Dictionary
            else if (t.IsGenericType && t.GetGenericTypeDefinition() == typeof(Dictionary<,>))
            {
                fieldType = SupportedPublicFields._ICollection;
                return true;
            }

            // Unsupported
            fieldType = SupportedPublicFields.Unknown;
            return false;
        }
        #endregion

        public static void DoUI(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
        {
            // Show public fields of scripts in another window
            ShowPublicFieldsWindow();

            if (!IsConfigUIOpened)
                return;

            // Create IV-SDK .NET logo texture
            if (ivsdkDotNetLogo == IntPtr.Zero)
                ivsdkDotNetLogo = Reflection.LocalImGuiIV.CreateTextureFromMemory(Properties.Resources.ivsdkdotnet_logo_small);

            /// @style Dark
            /// @unit px
            /// @begin TopWindow
            ImGuiIV.SetNextWindowSize(new Vector2(800f, 800f), eImGuiCond.FirstUseEver);
            if (ImGuiIV.Begin("IV-SDK .NET Manager###ManagerDesign", ref IsConfigUIOpened))
            {
                /// @separator

                /// @begin TabBar
                if (ImGuiIV.BeginTabBar("tabBar1"))
                {
                    /// @separator

#if DEBUG
                    DebugTab();
#endif
                    ScriptsTab();
                    PluginsTab(devicePtr, ctx);
                    SettingsTab();
                    AboutTab();

                    /// @separator
                    ImGuiIV.EndTabBar();
                }
                /// @end TabBar

                /// @separator
            }
            ImGuiIV.End();
            /// @end TopWindow
        }
        private static void ShowPublicFieldsWindow()
        {
            for (int i = 0; i < Main.Instance.ActiveScripts.Count; i++)
            {
                FoundScript fs = Main.Instance.ActiveScripts[i];

                if (fs.PublicFieldsWindowOpen)
                {
                    if (ImGuiIV.Begin(string.Format("Public fields of script {0}", fs.EntryPoint.FullName), ref fs.PublicFieldsWindowOpen))
                    {
                        ImGuiIV.SetWindowSize(new Vector2(550f, 600f), eImGuiCond.FirstUseEver);

                        // Public fields of entry point
                        if (ImGuiIV.CollapsingHeader(string.Format("{0}##{1}", fs.EntryPoint.Name, fs.ID)))
                        {
                            if (fs.EntryPointPublicFields != null && fs.EntryPointPublicFields.Length != 0)
                            {
                                for (int p = 0; p < fs.EntryPointPublicFields.Length; p++)
                                    AddField(fs, fs.EntryPointPublicFields[p]);
                            }
                            else
                            {
                                ImGuiIV.TextDisabled("There are no public fields within this type.");
                            }
                        }

                        // Other public fields
                        if (fs.OtherPublicFields != null)
                        {
                            for (int p = 0; p < fs.OtherPublicFields.Count; p++)
                            {
                                if (ImGuiIV.CollapsingHeader(string.Format("{0}##{1}", fs.OtherPublicFields[p][0].DeclaringType.Name, fs.ID)))
                                {
                                    for (int pp = 0; pp < fs.OtherPublicFields[p].Length; pp++)
                                    {
                                        AddField(fs, fs.OtherPublicFields[p][pp]);
                                    }
                                }
                            }
                        }

                    }
                    ImGuiIV.End();
                }
            }
        }

#if DEBUG
        private static bool testNotifyIsError;
        private static string testNotifyTitle;
        private static string testNotifyDesc;
        private static string testNotifyAdditionalContent;
        private static string shdnMessageContent;
        private static int shdnMessageTimeMS;
        public static Threading.ScriptThread[] scriptThreads;
        public delegate void TestThreadMethodDelegate();
        public static TestThreadMethodDelegate d;
        private static void DebugTab()
        {
            /// @begin TabItem
            if (ImGuiIV.BeginTabItem("DEBUG"))
            {
                /// @separator

                // Threads
                if (ImGuiIV.TreeNode("Threads"))
                {

                    ImGuiIV.TreePop();
                }

                // General Debug
                ImGuiIV.Spacing();
                ImGuiIV.SeparatorText("General Debug");
                ImGuiIV.CheckBox("Disable Key Events", ref Main.Instance.DisableKeyEvents);
                ImGuiIV.CheckBox("Throw On Error", ref Main.Instance.ThrowOnError);
                ImGuiIV.CheckBox("Do Not Reset ImGui Style", ref Main.Instance.DoNotResetImGuiStyle);
                ImGuiIV.CheckBox("Allow Write To Debug Output", ref Main.Instance.AllowWriteToDebugOutput);
                ImGuiIV.TextUnformatted("Main Thread ID: {0}", Main.Instance.MainThreadID);
                ImGuiIV.TextUnformatted("Console Log Items: {0}", Logger.GetLogItems().Count);
                ImGuiIV.TextUnformatted("Last Console Command: {0}", Main.Instance.Console.GetLastConsoleCommand());

                ImGuiIV.Spacing();
                ImGuiIV.SeparatorText("Test Notification and Popup");
                ImGuiIV.CheckBox("Test notification is error", ref testNotifyIsError);

                ImGuiIV.InputText("TestNotifyTitle", ref testNotifyTitle);
                ImGuiIV.InputText("TestNotifyDesc", ref testNotifyDesc);
                ImGuiIV.InputText("TestNotifyAdditionalContent", ref testNotifyAdditionalContent);

                if (ImGuiIV.Button("Show test notification"))
                    Main.Instance.Notification.ShowNotificationEx(testNotifyIsError ? NotificationType.Error : NotificationType.Default,
                        DateTime.UtcNow.AddSeconds(5d),
                        new NotificationContent(testNotifyTitle, testNotifyDesc, testNotifyAdditionalContent),
                        null);

                if (ImGuiIV.Button("open test popup"))
                {
                    ImGuiIV.OpenPopup("testpopuplkof");
                }

                ImGuiIV.CreateSimplePopupDialog("testpopuplkof", "test", true, true, true, "close", "test", () => { }, () => { });

                // ScriptHookDotNet
                ImGuiIV.Spacing();
                ImGuiIV.SeparatorText("ScriptHookDotNet");
                ImGuiIV.CheckBox("Enable Verbose Logging", ref SHDNStuff.EnableVerboseLogging);
                ImGuiIV.CheckBox("Enable Native Call Logging", ref SHDNStuff.NativeCallLoggingEnabled);
                ImGuiIV.BeginDisabled();
                ImGuiIV.CheckBox("WereScriptHookDotNetScriptsLoadedThisSession", ref SHDNStuff.WereScriptHookDotNetScriptsLoadedThisSession);
                ImGuiIV.EndDisabled();

                ImGuiIV.Spacing();
                ImGuiIV.TextDisabled("Message");
                ImGuiIV.InputText("shdnMessageContent", ref shdnMessageContent);
                ImGuiIV.DragInt("shdnMessageTimeMS", ref shdnMessageTimeMS);

                if (ImGuiIV.Button("Set message"))
                    Main.Instance.SHDN_ShowMessage(shdnMessageContent, shdnMessageTimeMS);

                ImGuiIV.Spacing();
                ImGuiIV.TextDisabled("Current Running Scripts");
                ImGuiIV.TextUnformatted("CurrentConstructingScript: {0}", SHDNStuff.CurrentConstructingScript != null ? SHDNStuff.CurrentConstructingScript.GUID : Guid.Empty);
                ImGuiIV.TextUnformatted("CurrentTickScript: {0}", SHDNStuff.CurrentTickScript != null ? SHDNStuff.CurrentTickScript.GUID : Guid.Empty);
                ImGuiIV.TextUnformatted("CurrentMouseDownScript: {0}", SHDNStuff.CurrentMouseDownScript != null ? SHDNStuff.CurrentMouseDownScript.GUID : Guid.Empty);
                ImGuiIV.TextUnformatted("CurrentMouseUpScript: {0}", SHDNStuff.CurrentMouseUpScript != null ? SHDNStuff.CurrentMouseUpScript.GUID : Guid.Empty);
                ImGuiIV.TextUnformatted("CurrentScriptCommandScript: {0}", SHDNStuff.CurrentScriptCommandScript != null ? SHDNStuff.CurrentScriptCommandScript.GUID : Guid.Empty);
                ImGuiIV.TextUnformatted("CurrentPerFrameDrawingScript: {0}", SHDNStuff.CurrentPerFrameDrawingScript != null ? SHDNStuff.CurrentPerFrameDrawingScript.GUID : Guid.Empty);

                ImGuiIV.Spacing();
                ImGuiIV.TextDisabled("ContentCache");
                ImGuiIV.TextUnformatted("PlayerCache Count: {0}", GTA.ContentCache.PlayerCache.Count);
                ImGuiIV.TextUnformatted("PedCache Count: {0}", GTA.ContentCache.PedCache.Count);
                ImGuiIV.TextUnformatted("VehicleCache Count: {0}", GTA.ContentCache.VehicleCache.Count);
                ImGuiIV.TextUnformatted("ObjectCache Count: {0}", GTA.ContentCache.ObjectCache.Count);
                ImGuiIV.TextUnformatted("PickupCache Count: {0}", GTA.ContentCache.PickupCache.Count);
                ImGuiIV.TextUnformatted("GroupCache Count: {0}", GTA.ContentCache.GroupCache.Count);
                ImGuiIV.TextUnformatted("BlipCache Count: {0}", GTA.ContentCache.BlipCache.Count);
                ImGuiIV.TextUnformatted("CameraCache Count: {0}", GTA.ContentCache.CameraCache.Count);
                ImGuiIV.TextUnformatted("FireCache Count: {0}", GTA.ContentCache.FireCache.Count);
                ImGuiIV.TextUnformatted("DeleteCache Count: {0}", GTA.ContentCache.DeleteCache.Count);
                ImGuiIV.TextUnformatted("DeleteQueue Count: {0}", GTA.ContentCache.DeleteQueue.Count);
                ImGuiIV.TextUnformatted("metadata Count: {0}", GTA.ContentCache.metadata.Count);

                // Lists
                ImGuiIV.Spacing();
                ImGuiIV.SeparatorText("Lists");
                ImGuiIV.TextUnformatted("Active Scripts: {0}", Main.Instance.ActiveScripts.Count);
                ImGuiIV.TextUnformatted("Action Queue: {0}", Main.Instance.ActionQueue.Count);
                ImGuiIV.TextUnformatted("Active Tasks: {0}", Main.Instance.ActiveTasks.Count);
                ImGuiIV.TextUnformatted("Delayed Actions: {0}", Main.Instance.DelayedActions.Count);

                // States
                ImGuiIV.Spacing();
                ImGuiIV.SeparatorText("States");
                ImGuiIV.BeginDisabled();
                ImGuiIV.CheckBox("FirstFrame", ref Main.Instance.FirstFrame);
                ImGuiIV.CheckBox("IsGTAIVWindowInFocus", ref Main.Instance.IsGTAIVWindowInFocus);
                ImGuiIV.CheckBox("OnWindowFocusChangedEventCalled", ref Main.Instance.OnWindowFocusChangedEventCalled);
                ImGuiIV.CheckBox("WasBoundPhoneNumbersProcessed", ref Main.Instance.WasBoundPhoneNumbersProcessed);
                ImGuiIV.EndDisabled();

                // Player
                ImGuiIV.Spacing();
                ImGuiIV.SeparatorText("Player");

                UIntPtr playerPedPtr = IVPlayerInfo.FindThePlayerPed();
                ImGuiIV.TextUnformatted("Player Ped Pointer: {0}", playerPedPtr);

                if (playerPedPtr != UIntPtr.Zero)
                {
                    IVPed playerPed = IVPed.FromUIntPtr(playerPedPtr);
                    int handle = (int)IVPools.GetPedPool().GetIndex(playerPedPtr);
                    ImGuiIV.TextUnformatted("PlayerIndex: {0}", playerPed.PlayerIndex);
                    ImGuiIV.TextUnformatted("PlayerHandle: {0}", handle);
                    ImGuiIV.TextUnformatted("DoesPlayerCharExists: {0}", IVSDKDotNet.Native.Natives.DOES_CHAR_EXIST(handle));

                }

                // Phone
                IVPhoneInfo thePhoneInfo = IVPhoneInfo.ThePhoneInfo;
                if (thePhoneInfo != null && IVPlayerInfo.FindThePlayerPed() != UIntPtr.Zero)
                {
                    ImGuiIV.Spacing();
                    ImGuiIV.SeparatorText("Phone");
                    ImGuiIV.TextUnformatted("Current Phone Number: {0}", thePhoneInfo.CurrentNumberInput);
                    ImGuiIV.TextUnformatted("Phone State: {0}", (ePhoneState)thePhoneInfo.State);
                }

                ImGuiIV.Spacing();
                ImGuiIV.SeparatorText("Threading test");

                if (scriptThreads == null)
                {
                    if (ImGuiIV.Button("Create test threads"))
                    {
                        //scriptThreads = new Threading.ScriptThread[2];
                        //scriptThreads[0] = new Threading.ScriptThread(ScriptTestThreadLoop);
                        //scriptThreads[1] = new Threading.ScriptThread(ScriptTestThreadLoop2);
                    }
                }
                else
                {
                    if (ImGuiIV.Button("Launch threads"))
                    {
                        for (int i = 0; i < scriptThreads.Length; i++)
                        {
                            scriptThreads[i].Launch();
                        }
                    }
                    if (ImGuiIV.Button("Abort threads"))
                    {
                        for (int i = 0; i < scriptThreads.Length; i++)
                        {
                            scriptThreads[i].Abort();
                            scriptThreads[i] = null;
                        }
                        scriptThreads = null;
                    }
                }

                /// @separator
                ImGuiIV.EndTabItem();
            }
            /// @end TabItem
        }
        private static void ScriptTestThreadLoop()
        {
            //while (!ImGuiIV.IsKeyDown(eImGuiKey.ImGuiKey_H))
            //{
            //    IVSDKDotNet.Native.Natives.PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", "press H to continue", 10, true);
            //    scriptThread.Wait(1);
            //}

            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_H, false))
            {
                IVSDKDotNet.Native.Natives.PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", "Hello and welcome", 3000, true);
                scriptThreads[0].Wait(3000);
                IVSDKDotNet.Native.Natives.PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", "this is a little test", 3000, true);
                scriptThreads[0].Wait(3000);
                IVSDKDotNet.Native.Natives.PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", "and it really works!", 3000, true);
                scriptThreads[0].Wait(3000);
            }
        }
        private static void ScriptTestThreadLoop2()
        {
            while (true)
            {
                int index = IVSDKDotNet.Native.Natives.CONVERT_INT_TO_PLAYERINDEX(IVSDKDotNet.Native.Natives.GET_PLAYER_ID());
                IVSDKDotNet.Native.Natives.GET_PLAYER_CHAR(index, out int ped);
                IVSDKDotNet.Native.Natives.GET_CHAR_COORDINATES(ped, out Vector3 pos);

                IVSDKDotNet.Native.Natives.DRAW_CHECKPOINT(pos, 1f, Color.Red);
                scriptThreads[1].Wait(1);
            }
        }
#endif

        private static void ScriptsTab()
        {
            /// @begin TabItem
            if (ImGuiIV.BeginTabItem("Scripts"))
            {
                /// @separator

                /// @begin Separator
                ImGuiIV.SeparatorText("Details");
                /// @end Separator

                /// @begin Text
                ImGuiIV.TextUnformatted(string.Format("Active IV-SDK .NET Scripts: {0}", Main.Instance.ActiveScripts.Count(x => x.IsIVSDKDotNetScript)));
                /// @end Text

                /// @begin Text
                ImGuiIV.TextUnformatted(string.Format("Active ScriptHookDotNet Scripts: {0}", Main.Instance.ActiveScripts.Count(x => x.IsScriptHookDotNetScript)));
                /// @end Text

                /// @begin Text
                // Time since last script reload
                TimeSpan timeSinceLastScriptLoad = DateTime.Now - Main.Instance.TimeSinceLastScriptLoad;

                if (timeSinceLastScriptLoad.TotalSeconds < 59d)
                    ImGuiIV.TextUnformatted("Last Script Load Occured: {0} Second(s) ago ({1})", (int)timeSinceLastScriptLoad.TotalSeconds, Main.Instance.TimeSinceLastScriptLoad);
                else if (timeSinceLastScriptLoad.TotalMinutes < 61d)
                    ImGuiIV.TextUnformatted("Last Script Load Occured: {0} Minute(s) ago ({1})", (int)timeSinceLastScriptLoad.TotalMinutes, Main.Instance.TimeSinceLastScriptLoad);
                else
                    ImGuiIV.TextUnformatted("Last Script Load Occured: {0} Hour(s) ago ({1})", (int)timeSinceLastScriptLoad.TotalHours, Main.Instance.TimeSinceLastScriptLoad);
                /// @end Text

                /// @begin Separator
                ImGuiIV.Spacing(3);
                ImGuiIV.SeparatorText("Control");
                /// @end Separator

                /// @begin Button
                if (ImGuiIV.Button("Abort all Scripts", new Vector2(150f, 0f)))
                {
                    Main.Instance.AbortScripts(ScriptType.All, AbortReason.Manager, false);
                }
                /// @end Button

                /// @begin Separator
                ImGuiIV.SameLine(0, 3 * ImGuiIV.GetStyle().ItemSpacing.X);
                ImGuiIV.SeparatorEx(eImGuiSeparatorFlags.Vertical);
                /// @end Separator

                /// @begin Button
                ImGuiIV.SameLine(0, 3 * ImGuiIV.GetStyle().ItemSpacing.X);
                if (ImGuiIV.Button("Abort all IV-SDK .NET Scripts", new Vector2(250f, 0f)))
                {
                    Main.Instance.AbortScripts(ScriptType.IVSDKDotNet, AbortReason.Manager, false);
                }
                /// @end Button

                /// @begin Button
                ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                if (ImGuiIV.Button("Abort all ScriptHookDotNet Scripts", new Vector2(290f, 0f)))
                {
                    Main.Instance.AbortScripts(ScriptType.ScriptHookDotNet, AbortReason.Manager, false);
                }
                /// @end Button

                /// @begin Separator
                ImGuiIV.SeparatorEx(eImGuiSeparatorFlags.Horizontal);
                /// @end Separator

                /// @begin Button
                if (ImGuiIV.Button("Reload all Scripts", new Vector2(150f, 0f)))
                {
                    Main.Instance.LoadScripts();
                }
                /// @end Button

                /// @begin Separator
                ImGuiIV.SameLine(0, 3 * ImGuiIV.GetStyle().ItemSpacing.X);
                ImGuiIV.SeparatorEx(eImGuiSeparatorFlags.Vertical);
                /// @end Separator

                /// @begin Button
                ImGuiIV.SameLine(0, 3 * ImGuiIV.GetStyle().ItemSpacing.X);
                if (ImGuiIV.Button("Reload all IV-SDK .NET Scripts", new Vector2(250f, 0f)))
                {
                    Main.Instance.LoadIVSDKDotNetScripts();
                }
                /// @end Button

                /// @begin Button
                ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                if (ImGuiIV.Button("Reload all ScriptHookDotNet Scripts", new Vector2(290f, 0f)))
                {
                    Main.Instance.LoadSHDNScripts();
                }
                /// @end Button

                /// @begin Separator
                ImGuiIV.Spacing(3);
                ImGuiIV.SeparatorText("Active Scripts");
                /// @end Separator

                /// @begin CheckBox
                ImGuiIV.CheckBox("Show IV-SDK .NET Scripts", ref showIVSDKDotNetScripts);
                /// @end CheckBox

                /// @begin CheckBox
                ImGuiIV.SameLine(0, 2 * ImGuiIV.GetStyle().ItemSpacing.X);
                ImGuiIV.CheckBox("Show ScriptHookDotNet Scripts", ref showScriptHookDotNetScripts);
                /// @end CheckBox

                /// @begin Text
                ImGuiIV.AlignTextToFramePadding();
                ImGuiIV.TextUnformatted("Search for:");
                /// @end Text

                /// @begin Input
                ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                ImGuiIV.SetNextItemWidth(300);
                ImGuiIV.InputText("##scriptNameFilterBtn", ref scriptNameFilter);
                /// @end Input

                /// @begin Separator
                ImGuiIV.Spacing(3);
                ImGuiIV.SeparatorEx(eImGuiSeparatorFlags.Horizontal);
                /// @end Separator

                if (Main.Instance.ActiveScripts.Count == 0)
                {
                    /// @begin Text
                    ImGuiIV.TextDisabled("There are currently no active scripts.");
                    /// @end Text
                }
                else
                {
                    for (int i = 0; i < Main.Instance.ActiveScripts.Count; i++)
                    {
                        FoundScript fs = Main.Instance.ActiveScripts[i];

                        // Filter
                        if (fs.ScriptType != ScriptType.Unknown) // Skip type filter if script type is unknown
                        {
                            if (string.IsNullOrWhiteSpace(scriptNameFilter))
                            {
                                if (!showIVSDKDotNetScripts || !showScriptHookDotNetScripts)
                                {
                                    if (showIVSDKDotNetScripts && !fs.IsIVSDKDotNetScript)
                                        continue;
                                    if (showScriptHookDotNetScripts && !fs.IsScriptHookDotNetScript)
                                        continue;
                                }
                            }
                            else
                            {
                                string searchStringLower = scriptNameFilter.ToLower();

                                if (!fs.EntryPoint.FullName.ToLower().Contains(searchStringLower))
                                {
                                    if (!fs.FileName.ToLower().Contains(searchStringLower))
                                    {
                                        continue;
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (!string.IsNullOrWhiteSpace(scriptNameFilter))
                            {
                                string searchStringLower = scriptNameFilter.ToLower();

                                if (!fs.EntryPoint.FullName.ToLower().Contains(searchStringLower))
                                {
                                    if (!fs.FileName.ToLower().Contains(searchStringLower))
                                    {
                                        continue;
                                    }
                                }
                            }
                        }

                        /// @begin CollapsingHeader
                        if (ImGuiIV.CollapsingHeader(string.Format("{0} ({1} - {2})", fs.EntryPoint.FullName, fs.ScriptType, fs.ID)))
                        {
                            /// @separator

                            /// @begin Separator
                            ImGuiIV.SeparatorText("Control");
                            /// @end Separator

                            /// @begin Button
                            if (ImGuiIV.Button("Abort this script", new Vector2(150f, 0f)))
                            {
                                Main.Instance.AbortScriptInternal(AbortReason.Manual, fs, false);
                                goto SKIP_TO_END;
                            }
                            /// @end Button

                            /// @begin Button
                            ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                            if (ImGuiIV.Button("Reload this script", new Vector2(170f, 0f)))
                            {
                                string fullPath = fs.FullPath;
                                string actualName = fs.EntryPoint.FullName;
                                if (Main.Instance.AbortScriptInternal(AbortReason.Manual, fs, true))
                                {
                                    if (!Main.Instance.LoadAssembly(fullPath))
                                    {
                                        Logger.LogWarning(string.Format("Failed to reload script '{0}'!", actualName));
                                    }
                                }
                                else
                                {
                                    Logger.LogWarning(string.Format("Failed to abort script '{0}'!", actualName));
                                }

                                continue;
                            }
                            /// @end Button

                            /// @begin Button
                            ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                            if (ImGuiIV.Button(fs.Running ? "Pause this script" : "Resume this script", new Vector2(170f, 0f)))
                            {
                                fs.Running = !fs.Running;
                            }
                            /// @end Button

                            /// @begin Separator
                            ImGuiIV.Spacing(4);
                            ImGuiIV.SeparatorText("Details");
                            /// @end Separator

                            /// @begin Table
                            if (ImGuiIV.BeginTable("table2", 2, eImGuiTableFlags.BordersInnerH | eImGuiTableFlags.BordersInnerV | eImGuiTableFlags.BordersOuterH | eImGuiTableFlags.BordersOuterV))
                            {
                                ImGuiIV.TableSetupColumn("Property", eImGuiTableColumnFlags.WidthFixed, 150);
                                ImGuiIV.TableSetupColumn("Value");
                                ImGuiIV.TableHeadersRow();
                                ImGuiIV.TableNextRow(0, 0);
                                ImGuiIV.TableSetColumnIndex(0);
                                /// @separator

                                // - - - COLUMN 0 - - -

                                /// @begin Text
                                ImGuiIV.TextUnformatted("Type");
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted("ID");
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted("Actual Name");
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted("File Name");
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted("Path");
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted("Active Tasks");
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted("Uses Threaded Tick");
                                /// @end Text

                                if (fs.RegisteredEvents != null)
                                {
                                    /// @begin Text
                                    ImGuiIV.TextUnformatted("Registered Events");
                                    /// @end Text
                                }

                                if (fs.IsIVSDKDotNetScript)
                                {
                                    /// @begin Text
                                    ImGuiIV.TextUnformatted("No Abort Forced");
                                    /// @end Text
                                }

                                /// @begin Text
                                ImGuiIV.TextUnformatted("Is Ready");
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted("Is Running");
                                /// @end Text

                                // - - - COLUMN 1 - - -

                                /// @begin Text
                                ImGuiIV.TableNextColumn(1);
                                ImGuiIV.TextUnformatted(fs.ScriptType.ToString()); // Type
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted(fs.ID.ToString()); // ID
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted(fs.EntryPoint.FullName); // Actual Name
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted(fs.FileName); // File Name
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted(fs.FullPath); // Path
                                ImGuiIV.SetItemTooltip(fs.FullPath);
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted(Main.Instance.ActiveTasks.Count(x => x.OwnerID == fs.ID).ToString()); // Active Tasks
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted((fs.TickThread != -1).ToString()); // Uses Threaded Tick
                                /// @end Text

                                if (fs.RegisteredEvents != null)
                                {
                                    /// @begin Text
                                    ImGuiIV.TextUnformatted(fs.RegisteredEvents.Count.ToString()); // Registered Events
                                    /// @end Text
                                }

                                if (fs.IsIVSDKDotNetScript)
                                {
                                    /// @begin Text
                                    ImGuiIV.TextUnformatted(fs.GetScriptAs<Script>().ForceNoAbort.ToString()); // No Abort Forced
                                    /// @end Text
                                }

                                /// @begin Text
                                ImGuiIV.TextUnformatted(fs.IsScriptReady().ToString()); // Is Ready
                                /// @end Text

                                /// @begin Text
                                ImGuiIV.TextUnformatted(fs.Running.ToString()); // Is Running
                                /// @end Text


                                /// @separator
                                ImGuiIV.EndTable();
                            }
                            /// @end Table

                            /// @begin CheckBox
                            ImGuiIV.Spacing(3);
                            ImGuiIV.CheckBox("Show public field(s)", ref fs.PublicFieldsWindowOpen);
                            /// @end CheckBox

                            /// @begin Separator
                            ImGuiIV.Spacing(4);
                            ImGuiIV.SeparatorText("Registered Stuff");
                            /// @end Separator

                            /// @begin CollapsingHeader
                            if (fs.ConsoleCommands != null)
                            {
                                if (fs.ConsoleCommands.Count == 0)
                                    ImGuiIV.BeginDisabled();
                                if (ImGuiIV.CollapsingHeader(string.Format("{0} registered console command(s)##{1}", fs.ConsoleCommands.Count, fs.ID)))
                                {
                                    string[] keys = fs.ConsoleCommands.Keys.ToArray();
                                    for (int c = 0; c < keys.Length; c++)
                                    {
                                        ImGuiIV.BulletText(keys[c]);
                                    }
                                }
                                if (fs.ConsoleCommands.Count == 0)
                                    ImGuiIV.EndDisabled();
                            }
                            else
                            {
                                ImGuiIV.TextUnformatted("List of console commands is not initialized.");
                            }
                            /// @end CollapsingHeader

                            /// @begin CollapsingHeader
                            if (fs.BoundPhoneNumbers != null)
                            {
                                if (fs.BoundPhoneNumbers.Count == 0)
                                    ImGuiIV.BeginDisabled();
                                if (ImGuiIV.CollapsingHeader(string.Format("{0} registered phone number(s)##{1}", fs.BoundPhoneNumbers.Count, fs.ID)))
                                {
                                    string[] keys = fs.BoundPhoneNumbers.Keys.ToArray();
                                    for (int c = 0; c < keys.Length; c++)
                                    {
                                        ImGuiIV.BulletText(keys[c]);
                                    }
                                }
                                if (fs.BoundPhoneNumbers.Count == 0)
                                    ImGuiIV.EndDisabled();
                            }
                            else
                            {
                                ImGuiIV.TextUnformatted("List of phone numbers is not initialized.");
                            }
                            /// @end CollapsingHeader

                            /// @begin CollapsingHeader
                            if (fs.Textures != null)
                            {
                                if (fs.Textures.Count == 0)
                                    ImGuiIV.BeginDisabled();
                                if (ImGuiIV.CollapsingHeader(string.Format("{0} registered texture(s)##{1}", fs.Textures.Count, fs.ID)))
                                {
                                    Vector2 button_sz = new Vector2(64f);
                                    float window_visible_x2 = ImGuiIV.GetWindowPos().Y + ImGuiIV.GetWindowContentRegionMax().X * 2f;

                                    for (int c = 0; c < fs.Textures.Count; c++)
                                    {
                                        IntPtr txtPtr = fs.Textures[c];

                                        ImGuiIV.PushID(c);

                                        Vector2 pos = ImGuiIV.GetCursorScreenPos();
                                        ImGuiIV.Image(txtPtr, button_sz);
                                        ImGuiIV.ImagePreviewToolTip(txtPtr, button_sz, pos, 32f, 5f);

                                        float last_button_x2 = ImGuiIV.GetItemRectMax().X;
                                        float next_button_x2 = last_button_x2 + 10f + button_sz.X; // Expected position if next button was on same line
                                        if (i + 1 < fs.Textures.Count && next_button_x2 < window_visible_x2)
                                            ImGuiIV.SameLine();

                                        ImGuiIV.PopID();
                                    }
                                }
                                if (fs.Textures.Count == 0)
                                    ImGuiIV.EndDisabled();
                            }
                            else
                            {
                                ImGuiIV.TextUnformatted("List of textures is not initialized.");
                            }
                            /// @end CollapsingHeader

                            ImGuiIV.Spacing(3);

                            /// @separator
                        }
                        /// @end CollapsingHeader
                    }
                }

SKIP_TO_END:

                /// @separator
                ImGuiIV.EndTabItem();
            }
            /// @end TabItem
        }
        private static void PluginsTab(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
        {
            /// @begin TabItem
            if (ImGuiIV.BeginTabItem("Plugins"))
            {

                /// @begin Separator
                ImGuiIV.SeparatorText("Details");
                /// @end Separator

                /// @begin Text
                ImGuiIV.TextUnformatted(string.Format("Active Plugins: {0}", Main.Instance.ThePluginManager.ActivePlugins.Count));
                /// @end Text

                /// @begin Text
                // Time since last plugin reload
                TimeSpan timeSinceLastPluginLoad = DateTime.Now - Main.Instance.ThePluginManager.TimeSinceLastPluginLoad;

                if (timeSinceLastPluginLoad.TotalSeconds < 59d)
                    ImGuiIV.TextUnformatted("Last Plugin Load Occured: {0} Second(s) ago ({1})", (int)timeSinceLastPluginLoad.TotalSeconds, Main.Instance.TimeSinceLastScriptLoad);
                else if (timeSinceLastPluginLoad.TotalMinutes < 61d)
                    ImGuiIV.TextUnformatted("Last Plugin Load Occured: {0} Minute(s) ago ({1})", (int)timeSinceLastPluginLoad.TotalMinutes, Main.Instance.TimeSinceLastScriptLoad);
                else
                    ImGuiIV.TextUnformatted("Last Plugin Load Occured: {0} Hour(s) ago ({1})", (int)timeSinceLastPluginLoad.TotalHours, Main.Instance.TimeSinceLastScriptLoad);
                /// @end Text

                /// @begin Separator
                ImGuiIV.Spacing(3);
                ImGuiIV.SeparatorText("Control");
                /// @end Separator

                /// @begin Button
                if (ImGuiIV.Button("Reload all plugins", new Vector2(150f, 0f)))
                {
                    Main.Instance.ThePluginManager.LoadPlugins();
                }
                /// @end Button

                ImGuiIV.SameLine(0, 3 * ImGuiIV.GetStyle().ItemSpacing.X);

                /// @begin Button
                if (ImGuiIV.Button("Unload all plugins", new Vector2(150f, 0f)))
                {
                    Main.Instance.ThePluginManager.UnloadPlugins(AbortReason.Manual, true);
                }
                /// @end Button

                /// @begin Separator
                ImGuiIV.Spacing(3);
                ImGuiIV.SeparatorText("Active plugins");
                /// @end Separator

                if (Main.Instance.ThePluginManager.ActivePlugins.Count == 0)
                {
                    /// @begin Text
                    ImGuiIV.TextDisabled("There are currently no active plugins.");
                    /// @end Text
                }
                else
                {
                    /// @begin Text
                    ImGuiIV.TextDisabled("Tip: Right-click on a Plugin to open up a popup which gives you some control over the Plugin.");
                    /// @end Text

                    ImGuiIV.Spacing(2);

                    for (int i = 0; i < Main.Instance.ThePluginManager.ActivePlugins.Count; i++)
                    {
                        FoundPlugin plugin = Main.Instance.ThePluginManager.ActivePlugins[i];

                        if (!plugin.IsReady())
                            continue;

                        /// @begin CollapsingHeader
                        if (ImGuiIV.CollapsingHeader(string.Format("{0} by {1}##IVSDKDotNetManagerPlugin", plugin.ThePluginInstance.DisplayName, plugin.ThePluginInstance.Author)))
                        {
                            // Allow plugin to draw their own stuff within this CollapsingHeader
                            Main.Instance.ThePluginManager.RaiseOnImGuiManagerRenderingEvent(plugin, devicePtr);
                        }
                        /// @end CollapsingHeader

                        /// @begin Popup
                        // When CollapsingHeader was right-clicked, a popup will appear.
                        if (ImGuiIV.BeginPopupContextItem(string.Format("##PluginContextItem{0}", plugin.ID), eImGuiPopupFlags.MouseButtonRight))
                        {
                            if (ImGuiIV.Selectable("Unload this Plugin"))
                            {
                                if (plugin.CanPluginBeAborted(AbortReason.Manual, false))
                                {
                                    Main.Instance.ThePluginManager.UnloadPlugin(AbortReason.Manual, plugin, true);
                                }
                                else
                                {
                                    Main.Instance.Notification.ShowNotification(NotificationType.Info, DateTime.UtcNow.AddSeconds(5d), string.Format("Plugin {0} cannot be unloaded.", plugin.EntryPoint.FullName), "The Plugin set to never allow unloads except if it creates an error.", "PLUGIN_CANNOT_BE_ABORTED");
                                }
                            }
                            if (ImGuiIV.Selectable("Reload this Plugin"))
                            {
                                if (plugin.CanPluginBeAborted(AbortReason.Manual, false))
                                {
                                    string fullPath = plugin.FullPath;
                                    string actualName = plugin.EntryPoint.FullName;
                                    if (Main.Instance.ThePluginManager.UnloadPlugin(AbortReason.Manual, plugin, true))
                                    {
                                        if (!Main.Instance.ThePluginManager.LoadAssembly(fullPath))
                                        {
                                            Logger.LogWarning(string.Format("Failed to reload Plugin '{0}'!", actualName));
                                        }
                                    }
                                    else
                                    {
                                        Logger.LogWarning(string.Format("Failed to unload Plugin '{0}'!", actualName));
                                    }
                                }
                                else
                                {
                                    Main.Instance.Notification.ShowNotification(NotificationType.Info, DateTime.UtcNow.AddSeconds(5d), string.Format("Plugin {0} cannot be reloaded.", plugin.EntryPoint.FullName), "The Plugin set to never allow unloads except if it creates an error.", "PLUGIN_CANNOT_BE_ABORTED");
                                }
                            }
                            if (ImGuiIV.Selectable("Close popup"))
                            {
                                ImGuiIV.CloseCurrentPopup();
                            }
                            ImGuiIV.EndPopup();
                        }
                        /// @begin Popup
                    }
                }

                ImGuiIV.EndTabItem();
            }
            /// @end TabItem
        }
        private static void SettingsTab()
        {
            if (ImGuiIV.BeginTabItem("Settings"))
            {
                /// @begin Text
                ImGuiIV.TextUnformatted("Change some IV-SDK .NET settings.");
                /// @end Text

                /// @begin Button
                ImGuiIV.Spacing(3);
                if (ImGuiIV.Button("Save settings", new Vector2(210f, 0f)))
                    Config.SaveSettings();
                /// @end Button

                /// @begin Button
                ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                if (ImGuiIV.Button("Restore default settings", new Vector2(210f, 0f)))
                    ImGuiIV.OpenPopup("Restore default settings?");
                /// @end Button

                ImGuiIV.CreateSimplePopupDialog("Restore default settings?", string.Format("This will reset all settings to its default value and will save the file.{0}" +
                    "Are you sure you want to restore the default settings?", Environment.NewLine), true, true, true, "Yes", "No", () =>
                    {
                        Config.RestoreDefaults();
                        Config.SaveSettings();
                    }, () => ImGuiIV.CloseCurrentPopup());

                /// @begin CollapsingHeader
                if (ImGuiIV.CollapsingHeader("Main"))
                {
                    ImGuiIV.Spacing(2);

                    /// @begin CheckBox
                    ImGuiIV.HelpMarker(string.Format("Sets if the IVSDKDotNet.log file should be created in the main directory of GTA IV or not.{0}" +
                        "If set to false, the Log files will be created in the 'logs' folder within the 'IVSDKDotNet' directory.", Environment.NewLine));
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("CreateLogFilesInMainDirectory", ref Config.CreateLogFilesInMainDirectory);
                    /// @end CheckBox

                    /// @begin Slider
                    ImGuiIV.HelpMarker("Determines how many logs files can be stored inside the 'logs' folder within the 'IVSDKDotNet' directory.");
                    ImGuiIV.SameLine();
                    ImGuiIV.SetNextItemWidth(200);
                    ImGuiIV.SliderInt("MaxLogsFiles", ref Config.MaxLogsFiles, 0, 50);
                    /// @end Slider

                    /// @begin CheckBox
                    ImGuiIV.HelpMarker("Sets if the Manager can check for new IV-SDK .NET updates.");
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("EnableAutomaticUpdateCheck", ref Config.EnableAutomaticUpdateCheck);
                    /// @end CheckBox

                    ImGuiIV.Dummy(new Vector2(0f, 4f));
                }
                /// @end CollapsingHeader

                /// @begin CollapsingHeader
                if (ImGuiIV.CollapsingHeader("Keys"))
                {
                    Helper.AskToOpenWebPageButton(true, "Click here to find a list of all key names (Links to docs.microsoft.com).", Vector2.Zero, new Uri("https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.keys?view=windowsdesktop-6.0"));
                    ImGuiIV.TextUnformatted("Recommended modifiers that can be used with all keys: Control, Alt, Shift.");
                    ImGuiIV.Spacing(2);

                    /// @begin Input
                    ImGuiIV.HelpMarker(string.Format("Defines the key that is used to switch the cursor visiblity which is used for script windows, the IV-SDK .NET console and manager window.{0}" +
                        "If the cursor is visible, the mouse input of GTA IV will be disabled.", Environment.NewLine));
                    ImGuiIV.SameLine();
                    ImGuiIV.SetNextItemWidth(200);
                    ImGuiIV.InputText("SwitchCursorKey", ref Config.SwitchCursorKey);
                    /// @end Input

                    /// @begin Input
                    ImGuiIV.HelpMarker(string.Format("Defines the key that is used to open/close the IV-SDK .NET manager window.", Environment.NewLine));
                    ImGuiIV.SameLine();
                    ImGuiIV.SetNextItemWidth(200);
                    ImGuiIV.InputText("OpenManagerWindowKey", ref Config.OpenManagerWindowKey);
                    /// @end Input

                    /// @begin Input
                    ImGuiIV.HelpMarker("Defines the key that is used to open/close the IV-SDK .NET console.");
                    ImGuiIV.SameLine();
                    ImGuiIV.SetNextItemWidth(200);
                    ImGuiIV.InputText("OpenConsoleKey", ref Config.OpenConsoleKey);
                    /// @end Input

                    /// @begin Input
                    ImGuiIV.HelpMarker("Defines the key that is used to reload all scripts.");
                    ImGuiIV.SameLine();
                    ImGuiIV.SetNextItemWidth(200);
                    ImGuiIV.InputText("ReloadScriptsKey", ref Config.ReloadScriptsKey);
                    /// @end Input
                }
                /// @end CollapsingHeader

                /// @begin CollapsingHeader
                if (ImGuiIV.CollapsingHeader("Scripts"))
                {
                    ImGuiIV.Spacing(2);

                    ImGuiIV.HelpMarker(string.Format("If set to true, this makes it so that scripts which have this property set, are not able to be aborted if all scripts are being aborted via the console or manager, making it act more like an ASI mod.{0}" +
                        "It is however still possible for them to be unloaded, by either the scripts creating an error and the manager catching them, or by the user to reload each script manually via the manager.", Environment.NewLine));
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("AllowScriptsToForceNoAbort", ref Config.AllowScriptsToForceNoAbort);

                    ImGuiIV.HelpMarker("Sets if all running scripts will pause from executing when the GTA IV window is not currently in focus.");
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("PauseExecutionWhenNotInFocus", ref Config.PauseScriptExecutionWhenNotInFocus);

                    ImGuiIV.HelpMarker(string.Format("This prevents scripts from loading if the IVSDKDotNetWrapper version the script was made with is older then the current one.{0}" +
                        "Setting this to false will load every script even if the IVSDKDotNetWrapper version the script was made with is older then the current one.", Environment.NewLine));
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("DoNotLoadLegacyScripts", ref Config.DoNotLoadLegacyScripts);

                    ImGuiIV.HelpMarker("This reloads all scripts right before loading a save, starting a new game or when switching episodes.");
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("ReloadScriptsOnReload", ref Config.ReloadScriptsOnReload);

                    ImGuiIV.HelpMarker("This will load your ScriptHookDotNet mods within the 'scripts' folder located in the main directory of GTA IV.");
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("LoadScriptHookDotNetScripts", ref Config.LoadScriptHookDotNetScripts);

                    ImGuiIV.Dummy(new Vector2(0f, 4f));
                }
                /// @end CollapsingHeader

                /// @begin CollapsingHeader
                if (ImGuiIV.CollapsingHeader("Notification"))
                {
                    ImGuiIV.Spacing(2);

                    ImGuiIV.HelpMarker("If set to false, no notifications will be shown on screen. This is not recommended as you might miss important notifications.");
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("ShowNotifications", ref Config.ShowNotifications);

                    ImGuiIV.Dummy(new Vector2(0f, 4f));
                }
                /// @end CollapsingHeader

                /// @begin CollapsingHeader
                if (ImGuiIV.CollapsingHeader("Style"))
                {
                    ImGuiIV.Spacing(2);

                    ImGuiIV.HelpMarker("Sets the style of the ImGui windows.\n\rAvailable styles: dark, classic, light");
                    ImGuiIV.SameLine();
                    ImGuiIV.SetNextItemWidth(200);
                    ImGuiIV.InputText("ImGuiStyle", ref Config.ImGuiStyle);

                    ImGuiIV.HelpMarker("Sets if the IV-SDK .NET Manager and Console windows will use a custom theme instead of the one set above.");
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("UseCustomThemeForManagerAndConsole", ref Config.UseCustomThemeForManagerAndConsole);

                    ImGuiIV.Dummy(new Vector2(0f, 4f));
                }
                /// @end CollapsingHeader

                /// @begin CollapsingHeader
                if (ImGuiIV.CollapsingHeader("API"))
                {
                    ImGuiIV.Spacing(2);

                    ImGuiIV.HelpMarker(string.Format("Sets if API Connections are allowed.{0}" +
                        "If set to true, applications can connect to the IV-SDK .NET Manager via the API and see, for example, which scripts are running, or can even reload them.", Environment.NewLine));
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("AllowConnections", ref Config.AllowRemoteConnections);

                    ImGuiIV.HelpMarker("Shows a notification when some application connected with the IV-SDK .NET Manager via the API.");
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("ShowNotificationOnConnection", ref Config.ShowNotificationOnConnection);

                    ImGuiIV.HelpMarker("Allows connected API clients to reload scripts.");
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("AllowRemoteReloadScripts", ref Config.AllowRemoteReloadScripts);

                    ImGuiIV.HelpMarker("Allows connected API clients to load scripts.");
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("AllowRemoteLoadScripts", ref Config.AllowRemoteLoadScripts);

                    ImGuiIV.HelpMarker("Allows connected API clients to abort scripts.");
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("AllowRemoteAbortScripts", ref Config.AllowRemoteAbortScripts);

                    ImGuiIV.HelpMarker(string.Format("Allows connected API clients to call GTA IV Native Functions like 'ADD_EXPLOSION' or 'SET_CHAR_COORDINATES'.{0}" +
                        "As you might can tell, this could be abused in some way. Turn this off to avoid other applications being able to call those Functions.", Environment.NewLine));
                    ImGuiIV.SameLine();
                    ImGuiIV.CheckBox("AllowRemoteNativeFunctionCalls", ref Config.AllowRemoteNativeFunctionCalls);

                    ImGuiIV.Dummy(new Vector2(0f, 4f));
                }
                /// @end CollapsingHeader

                ImGuiIV.EndTabItem();
            }
        }
        private static void AboutTab()
        {
            /// @begin TabItem
            if (ImGuiIV.BeginTabItem("About"))
            {
                /// @separator

                /// @begin Image
                ImGuiIV.Image(ivsdkDotNetLogo, new Vector2(140f, 140f));
                /// @end Image

                /// @begin Child
                ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                ImGuiIV.BeginChild("child3", new Vector2(500f, 140f), eImGuiChildFlags.AlwaysUseWindowPadding, eImGuiWindowFlags.NoSavedSettings);
                {
                    /// @separator

                    /// @begin Text
#if DEBUG
                    ImGuiIV.TextUnformatted("IV-SDK .NET DEBUG Version {0}", CLR.CLRBridge.Version);
#elif PREVIEW
                    ImGuiIV.TextUnformatted("IV-SDK .NET PREVIEW Version {0}", CLR.CLRBridge.Version);
#else
                    ImGuiIV.TextUnformatted("IV-SDK .NET Release Version {0}", CLR.CLRBridge.Version);
#endif
                    /// @end Text

                    /// @begin Text
                    ImGuiIV.TextUnformatted("Made by ItsClonkAndre");
                    /// @end Text

                    /// @begin Text
                    ImGuiIV.Spacing(5);
                    ImGuiIV.AlignTextToFramePadding();
                    ImGuiIV.TextUnformatted("View this project on");
                    /// @end Text

                    /// @begin Button
                    ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                    Helper.AskToOpenWebPageButton(true, "GitHub", Vector2.Zero, new Uri("https://github.com/ClonkAndre/IV-SDK-DotNet"));
                    /// @end Button

                    /// @begin Text
                    ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                    ImGuiIV.TextUnformatted("or");
                    /// @end Text

                    /// @begin Button
                    ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                    Helper.AskToOpenWebPageButton(true, "gtaforums", Vector2.Zero, new Uri("https://gtaforums.com/topic/986510-iv-sdk-net/"));
                    /// @end Button

                    /// @begin Button
                    //Helper.AskToOpenWebPageButton(false, "Check out cool projects made by using IV-SDK .NET", Vector2.Zero, new Uri("https://github.com/topics/iv-sdk-net"));
                    Helper.AskToOpenWebPageButton(false, "Check out cool projects made with IV-SDK .NET", Vector2.Zero, new Uri("https://github.com/topics/iv-sdk-net"));
                    /// @end Button

                    /// @separator
                    ImGuiIV.EndChild();
                }
                /// @end Child

                /// @begin Button
                ImGuiIV.Spacing(3);
                if (ImGuiIV.Button("Check for updates"))
                {
                    Main.Instance.UpdateChecker.CheckForUpdates(false);
                }
                /// @end Button

                /// @begin Text
                ImGuiIV.TextUnformatted("Current IVSDKDotNetWrapper Version: {0}", Main.Instance.CurrentWrapperVersion);
                /// @end Text

                /// @begin Text
                ImGuiIV.TextUnformatted("Current included ScriptHookDotNet Version: {0}", SHDNStuff.CurrentSHDNVersion);
                /// @end Text

                /// @begin Separator
                ImGuiIV.Spacing(3);
                ImGuiIV.SeparatorText("Made possible with");
                /// @end Separator

                /// @begin Button
                Helper.AskToOpenWebPageButton(false, "IV-SDK", new Vector2(200f, 0f), new Uri("https://github.com/Zolika1351/iv-sdk"));
                /// @end Button

                /// @begin Button
                ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                Helper.AskToOpenWebPageButton(false, "InGameTimecycEditor", new Vector2(200f, 0f), new Uri("https://github.com/akifle47/InGameTimecycEditor"));
                /// @end Button

                /// @begin Button
                ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                Helper.AskToOpenWebPageButton(false, "Dear ImGui", new Vector2(200f, 0f), new Uri("https://github.com/ocornut/imgui"));
                /// @end Button

                /// @begin Separator
                ImGuiIV.Spacing(5);
                ImGuiIV.SeparatorText("Epic Supporters!");
                /// @end Separator

                /// @begin Text
                ImGuiIV.TextUnformatted("Become a member today to have your name shown in one of the nodes below!");
                /// @end Text

                /// @begin Button
                Helper.AskToOpenWebPageButton(false, "Visit Patreon", new Vector2(250f, 0f), new Uri("https://www.patreon.com/itsclonkandre"));
                ImGuiIV.SameLine();
                Helper.AskToOpenWebPageButton(false, "Visit Ko-fi", new Vector2(250f, 0f), new Uri("https://ko-fi.com/itsclonkandre"));
                /// @end Button

                /// @begin CollapsingHeader
                ImGuiIV.Spacing(2);
                if (ImGuiIV.CollapsingHeader("Tier 3"))
                {
                    /// @separator

                    ImGuiIV.Spacing(2);

                    if (Main.Instance.TierThreeSupporters.Count == 0)
                    {
                        ImGuiIV.TextUnformatted("No one here yet!");
                    }
                    else
                    {
                        for (int i = 0; i < Main.Instance.TierThreeSupporters.Count; i++)
                        {
                            string name = Main.Instance.TierThreeSupporters[i];
                            ImGuiIV.BulletText(name);
                        }
                    }

                    ImGuiIV.Spacing(2);

                    /// @separator
                }
                /// @end CollapsingHeader

                /// @begin CollapsingHeader
                if (ImGuiIV.CollapsingHeader("Tier 2"))
                {
                    /// @separator

                    ImGuiIV.Spacing(2);

                    if (Main.Instance.TierTwoSupporters.Count == 0)
                    {
                        ImGuiIV.TextUnformatted("No one here yet!");
                    }
                    else
                    {
                        for (int i = 0; i < Main.Instance.TierTwoSupporters.Count; i++)
                        {
                            string name = Main.Instance.TierTwoSupporters[i];
                            ImGuiIV.BulletText(name);
                        }
                    }

                    ImGuiIV.Spacing(2);

                    /// @separator
                }
                /// @end CollapsingHeader

                /// @begin CollapsingHeader
                if (ImGuiIV.CollapsingHeader("Tier 1"))
                {
                    /// @separator

                    ImGuiIV.Spacing(2);

                    if (Main.Instance.TierOneSupporters.Count == 0)
                    {
                        ImGuiIV.TextUnformatted("No one here yet!");
                    }
                    else
                    {
                        for (int i = 0; i < Main.Instance.TierOneSupporters.Count; i++)
                        {
                            string name = Main.Instance.TierOneSupporters[i];
                            ImGuiIV.BulletText(name);
                        }
                    }

                    ImGuiIV.Spacing(2);

                    /// @separator
                }
                /// @end CollapsingHeader

                /// @separator
                ImGuiIV.EndTabItem();
            }
            /// @end TabItem
        }

    }
}