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
using Manager.Classes.ScriptHookDotNet;
using Manager.Classes.Scripts;
using Manager.Classes.Threading;
using Manager.Managers;

// Designed with ImRAD
// Check out the project on GitHub: https://github.com/tpecholt/imrad

namespace Manager.UI
{
    internal static class ManagerUI
    {

        #region Variables
        public static bool IsConfigUIOpened;

        private static DateTime nextRefresh = DateTime.MinValue;

        // Filter
        private static bool showIVSDKDotNetScripts = true;
        private static bool showScriptHookDotNetScripts = true;
        private static bool showOnlyConstructedScripts = true;
        private static string scriptNameFilter;

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
                            int value = Convert.ToInt32(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.GetTheScriptObject(), Convert.ToByte(value));
                        }
                        break;
                    case SupportedPublicFields._sbyte:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.GetTheScriptObject(), Convert.ToSByte(value));
                        }
                        break;
                    case SupportedPublicFields._short:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.GetTheScriptObject(), Convert.ToInt16(value));
                        }
                        break;
                    case SupportedPublicFields._ushort:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.GetTheScriptObject(), Convert.ToUInt16(value));
                        }
                        break;
                    case SupportedPublicFields._int:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.GetTheScriptObject(), value);
                        }
                        break;
                    case SupportedPublicFields._uint:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.GetTheScriptObject(), Convert.ToUInt32(value));
                        }
                        break;
                    case SupportedPublicFields._long:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.GetTheScriptObject(), Convert.ToInt64(value));
                        }
                        break;
                    case SupportedPublicFields._ulong:
                        {
                            int value = Convert.ToInt32(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt(string.Format("##{0}", info.Name), ref value, speed, (int)min, (int)max))
                                info.SetValue(foundScript.GetTheScriptObject(), Convert.ToUInt64(value));
                        }
                        break;
                    case SupportedPublicFields._float:
                        {
                            float value = Convert.ToSingle(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat(string.Format("##{0}", info.Name), ref value, speed, min, max))
                                info.SetValue(foundScript.GetTheScriptObject(), Convert.ToSingle(value));
                        }
                        break;
                    case SupportedPublicFields._double:
                        {
                            float value = Convert.ToSingle(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat(string.Format("##{0}", info.Name), ref value, speed, min, max))
                                info.SetValue(foundScript.GetTheScriptObject(), Convert.ToDouble(value));
                        }
                        break;
                    case SupportedPublicFields._decimal:
                        {
                            float value = Convert.ToSingle(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat(string.Format("##{0}", info.Name), ref value, speed, min, max))
                                info.SetValue(foundScript.GetTheScriptObject(), Convert.ToDecimal(value));
                        }
                        break;
                    case SupportedPublicFields._bool:
                        {
                            bool value = Convert.ToBoolean(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.CheckBox(string.Format("##{0}", info.Name), ref value))
                                info.SetValue(foundScript.GetTheScriptObject(), value);
                        }
                        break;
                    case SupportedPublicFields._string:
                        {
                            string value = Convert.ToString(info.GetValue(foundScript.GetTheScriptObject()));

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.InputText(string.Format("##{0}", info.Name), ref value))
                                info.SetValue(foundScript.GetTheScriptObject(), value);
                        }
                        break;
                    case SupportedPublicFields._Vector2:
                        {
                            Vector2 value = (Vector2)info.GetValue(foundScript.GetTheScriptObject());
                            float[] arr = new float[2] { value.X, value.Y };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat2(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.GetTheScriptObject(), new Vector2(arr[0], arr[1]));
                        }
                        break;
                    case SupportedPublicFields._Vector3:
                        {
                            Vector3 value = (Vector3)info.GetValue(foundScript.GetTheScriptObject());
                            float[] arr = new float[3] { value.X, value.Y, value.Z };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat3(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.GetTheScriptObject(), new Vector3(arr[0], arr[1], arr[2]));
                        }
                        break;
                    case SupportedPublicFields._Vector4:
                        {
                            Vector4 value = (Vector4)info.GetValue(foundScript.GetTheScriptObject());
                            float[] arr = new float[4] { value.X, value.Y, value.Z, value.W };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat4(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.GetTheScriptObject(), new Vector4(arr[0], arr[1], arr[2], arr[3]));
                        }
                        break;
                    case SupportedPublicFields._Quaternion:
                        {
                            Quaternion value = (Quaternion)info.GetValue(foundScript.GetTheScriptObject());
                            float[] arr = new float[4] { value.X, value.Y, value.Z, value.W };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat4(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.GetTheScriptObject(), new Quaternion(arr[0], arr[1], arr[2], arr[3]));
                        }
                        break;
                    case SupportedPublicFields._Color:
                        {
                            Color value = (Color)info.GetValue(foundScript.GetTheScriptObject());
                            Vector4 arr = ImGuiIV.ColorToFloatRGB(value);

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.ColorEdit4(string.Format("##{0}", info.Name), ref arr, eImGuiColorEditFlags.InputRGB))
                                info.SetValue(foundScript.GetTheScriptObject(), ImGuiIV.FloatRGBToColor(arr));
                        }
                        break;
                    case SupportedPublicFields._Size:
                        {
                            Size value = (Size)info.GetValue(foundScript.GetTheScriptObject());
                            int[] arr = new int[2] { value.Width, value.Height };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt2(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.GetTheScriptObject(), new Size(arr[0], arr[1]));
                        }
                        break;
                    case SupportedPublicFields._SizeF:
                        {
                            SizeF value = (SizeF)info.GetValue(foundScript.GetTheScriptObject());
                            float[] arr = new float[2] { value.Width, value.Height };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat2(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.GetTheScriptObject(), new SizeF(arr[0], arr[1]));
                        }
                        break;
                    case SupportedPublicFields._Point:
                        {
                            Point value = (Point)info.GetValue(foundScript.GetTheScriptObject());
                            int[] arr = new int[2] { value.X, value.Y };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragInt2(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.GetTheScriptObject(), new Point(arr[0], arr[1]));
                        }
                        break;
                    case SupportedPublicFields._PointF:
                        {
                            PointF value = (PointF)info.GetValue(foundScript.GetTheScriptObject());
                            float[] arr = new float[2] { value.X, value.Y };

                            // The field data
                            ImGuiIV.SameLine(0f, 30f);
                            if (ImGuiIV.DragFloat2(string.Format("##{0}", info.Name), ref arr, speed))
                                info.SetValue(foundScript.GetTheScriptObject(), new PointF(arr[0], arr[1]));
                        }
                        break;
                    case SupportedPublicFields._IList:
                        {
                            object obj = info.GetValue(foundScript.GetTheScriptObject());

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
                            object obj = info.GetValue(foundScript.GetTheScriptObject());

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
                    DebugTab(devicePtr);
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
            for (int i = 0; i < ScriptManager.GetActiveScriptsCount(); i++)
            {
                FoundScript fs = ScriptManager.GetActiveScripts()[i];

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
        //private static bool testNotifyIsError;
        //private static string testNotifyTitle;
        //private static string testNotifyDesc;
        //private static string testNotifyAdditionalContent;
        private static string shdnMessageContent;
        private static int shdnMessageTimeMS;
        private static bool shdn_cc_showCachedEntitiesWithOwnerOnly;
        private static int shdn_cc_showCachedEntitiesOfThisTypeOnly;
        private static string zoneInfoLabel, zoneTextLabel;
        private static Vector3 zoneMin, zoneMax;
        private static void DebugTab(IntPtr devicePtr)
        {
            /// @begin TabItem
            if (ImGuiIV.BeginTabItem("DEBUG"))
            {
                /// @separator

                // Threads
                if (ImGuiIV.TreeNode("Threads"))
                {
                    ImGuiIV.SeparatorText("Game Thread IDs");

                    foreach(KeyValuePair<GameThread, ThreadData> pairs in ThreadManager.GetDataOfGameThreads())
                    {
                        ImGuiIV.TextUnformatted("{0} - ID: {1}, TlsContext: {2}", pairs.Key, pairs.Value.ThreadID, pairs.Value.TlsContext);
                    }

                    ImGuiIV.Spacing();
                    ImGuiIV.SeparatorText("Managed Threads");

                    NetThread[] activeThreads = ThreadManager.GetActiveThreads();
                    ImGuiIV.TextUnformatted("Active Threads: {0}", activeThreads.Length);

                    for (int i = 0; i < activeThreads.Length; i++)
                    {
                        NetThread thread = activeThreads[i];

                        if (ImGuiIV.TreeNode(string.Format("Thread #{0} - {1}", thread.ThreadId, thread.ThreadName)))
                        {
                            if (ImGuiIV.Button("Try shutdown (Request cancellation)"))
                            {
                                thread.TryShutdown();
                            }

                            ImGuiIV.Spacing(2);
                            ImGuiIV.TextDisabled("Details");
                            ImGuiIV.TextUnformatted("ID: {0}", thread.ThreadId);
                            ImGuiIV.TextUnformatted("Name: {0}", thread.ThreadName);
                            ImGuiIV.TextUnformatted("Type: {0}", thread.Type);

                            ImGuiIV.Spacing();
                            ImGuiIV.TextDisabled("States");
                            ImGuiIV.TextUnformatted("ThreadState: {0}", thread.ThreadState);
                            ImGuiIV.TextUnformatted("IsRunning: {0}", thread.IsRunning);
                            ImGuiIV.TextUnformatted("IsInLoop: {0}", thread.IsInLoop);
                            ImGuiIV.TextUnformatted("IsThreadAbleToTick: {0}", thread.IsThreadAbleToTick);
                            ImGuiIV.TextUnformatted("WasShutdownRequested: {0}", thread.WasShutdownRequested);
                            ImGuiIV.TreePop();
                        }
                    }

                    ImGuiIV.Spacing(3);
                    ImGuiIV.TreePop();
                }

                // Tasks
                if (ImGuiIV.TreeNode("Tasks"))
                {
                    ImGuiIV.TextUnformatted("Active Tasks: {0}", TaskManager.GetActiveTasksCount());

                    ImGuiIV.TreePop();
                }

                // IV-SDK .NET
                if (ImGuiIV.TreeNode("IVSDKDotNet"))
                {

                    // General Debug
                    ImGuiIV.SeparatorText("Debug");
                    ImGuiIV.CheckBox("Disable Key Events", ref Main.Instance.DisableKeyEvents);
                    ImGuiIV.CheckBox("Throw On Error", ref Main.Instance.ThrowOnError);
                    ImGuiIV.CheckBox("Allow Write To Debug Output", ref Main.Instance.AllowWriteToDebugOutput);
                    ImGuiIV.TextUnformatted("Console Log Items: {0}", Logger.GetLogItems().Count);
                    ImGuiIV.TextUnformatted("Last Console Command: {0}", ConsoleUI.GetLastConsoleCommand());

                    // Lists
                    ImGuiIV.Spacing();
                    ImGuiIV.SeparatorText("Lists");
                    ImGuiIV.TextUnformatted("Active Scripts: {0}", ScriptManager.GetActiveScriptsCount());
                    ImGuiIV.TextUnformatted("Action Queue: {0}", ThreadManager.GetMainThreadActionQueueCount());
                    ImGuiIV.TextUnformatted("Active Tasks: {0}", Main.Instance.ActiveTasks.Count);
                    ImGuiIV.TextUnformatted("Delayed Actions: {0}", DelayedActionManager.GetDelayedActionsCount());


                    ImGuiIV.TreePop();
                }

                // ScriptHookDotNet
                if (ImGuiIV.TreeNode("ScriptHookDotNet"))
                {

                    ImGuiIV.SeparatorText("Debug");
                    ImGuiIV.CheckBox("Enable Verbose Logging", ref SHDNManager.EnableVerboseLogging);
                    ImGuiIV.CheckBox("Enable Native Call Logging", ref SHDNManager.NativeCallLoggingEnabled);

                    ImGuiIV.Spacing();
                    ImGuiIV.SeparatorText("Current Running Scripts");
                    ImGuiIV.TextUnformatted("CurrentConstructingScript: {0}", SHDNManager.CurrentConstructingScript != null ? SHDNManager.CurrentConstructingScript.GUID : Guid.Empty);
                    ImGuiIV.TextUnformatted("CurrentTickScript: {0}", SHDNManager.CurrentTickScript != null ? SHDNManager.CurrentTickScript.GUID : Guid.Empty);
                    ImGuiIV.TextUnformatted("CurrentMouseDownScript: {0}", SHDNManager.CurrentMouseDownScript != null ? SHDNManager.CurrentMouseDownScript.GUID : Guid.Empty);
                    ImGuiIV.TextUnformatted("CurrentMouseUpScript: {0}", SHDNManager.CurrentMouseUpScript != null ? SHDNManager.CurrentMouseUpScript.GUID : Guid.Empty);
                    ImGuiIV.TextUnformatted("CurrentScriptCommandScript: {0}", SHDNManager.CurrentScriptCommandScript != null ? SHDNManager.CurrentScriptCommandScript.GUID : Guid.Empty);
                    ImGuiIV.TextUnformatted("CurrentPerFrameDrawingScript: {0}", SHDNManager.CurrentPerFrameDrawingScript != null ? SHDNManager.CurrentPerFrameDrawingScript.GUID : Guid.Empty);

                    ImGuiIV.Spacing();
                    ImGuiIV.SeparatorText("Testing");

                    ImGuiIV.TextDisabled("Message");
                    ImGuiIV.InputText("shdnMessageContent", ref shdnMessageContent);
                    ImGuiIV.DragInt("shdnMessageTimeMS", ref shdnMessageTimeMS);
                    if (ImGuiIV.Button("Set message"))
                        Main.Instance.SHDN_ShowMessage(shdnMessageContent, shdnMessageTimeMS);

                    ImGuiIV.Spacing();
                    ImGuiIV.SeparatorText("ContentCache");
                    ImGuiIV.TextUnformatted("Current Cached Entity Count: {0}", SHDNContentCacheManager.GetCachedEntityCount());
                    ImGuiIV.TextUnformatted("Current Cached Players Count: {0}", SHDNContentCacheManager.GetCachedPlayersCount());
                    ImGuiIV.TextUnformatted("(LEGACY) metadata Count: {0}", GTA.ContentCache.metadata.Count);

                    if (ImGuiIV.TreeNode("Cached entities"))
                    {
                        ImGuiIV.CheckBox("ShowCachedEntitiesWithOwnerOnly", ref shdn_cc_showCachedEntitiesWithOwnerOnly);
                        ImGuiIV.SliderInt("ShowCachedEntitiesOfThisTypeOnly", ref shdn_cc_showCachedEntitiesOfThisTypeOnly, 0, 9);

                        ImGuiIV.TextDisabled("Show entities of type: {0}", shdn_cc_showCachedEntitiesOfThisTypeOnly == 0 ? "ALL" : ((GTA.HandleType)shdn_cc_showCachedEntitiesOfThisTypeOnly).ToString());

                        CachedEntity[] cachedEntities = SHDNContentCacheManager.GetCachedEntities();
                        for (int i = 0; i < cachedEntities.Length; i++)
                        {
                            CachedEntity cachedEntity = cachedEntities[i];

                            // Filter
                            if (shdn_cc_showCachedEntitiesWithOwnerOnly && cachedEntity.OwnerScriptID == Guid.Empty)
                                continue;
                            if (shdn_cc_showCachedEntitiesOfThisTypeOnly != 0)
                            {
                                if ((int)cachedEntity.TheEntity.Type != shdn_cc_showCachedEntitiesOfThisTypeOnly)
                                    continue;
                            }

                            if (ImGuiIV.TreeNode(string.Format("Cached Entity {0} (Type: {1})", cachedEntity.TheEntity.UID, cachedEntity.TheEntity.Type)))
                            {
                                ImGuiIV.TextUnformatted("OwnerScriptID: {0}", cachedEntity.OwnerScriptID);
                                ImGuiIV.TextUnformatted("Entity Type: {0}", cachedEntity.TheEntity.Type);
                                ImGuiIV.TextUnformatted("Entity Handle: {0}", cachedEntity.TheEntity.UID);

                                ImGuiIV.TreePop();
                            }
                        }

                        ImGuiIV.TreePop();
                    }

                    if (ImGuiIV.TreeNode("Cached players"))
                    {
                        GTA.Player[] cachedPlayers = SHDNContentCacheManager.GetCachedPlayers();

                        if (cachedPlayers != null)
                        {
                            for (int i = 0; i < cachedPlayers.Length; i++)
                            {
                                GTA.Player cachedPlayer = cachedPlayers[i];

                                if (ImGuiIV.TreeNode(string.Format("Cached Player {0} (IsLocalPlayer: {1})", i, cachedPlayer.isLocalPlayer)))
                                {
                                    ImGuiIV.TextUnformatted("ID: {0}", cachedPlayer.ID);
                                    ImGuiIV.TextUnformatted("Index: {0}", cachedPlayer.Index);
                                    ImGuiIV.TextUnformatted("PedHandle: {0}", cachedPlayer.PedHandle);
                                    ImGuiIV.TextUnformatted("Name: {0}", cachedPlayer.Name);
                                    ImGuiIV.TextUnformatted("isActive: {0}", cachedPlayer.isActive);
                                    ImGuiIV.TextUnformatted("isLocalPlayer: {0}", cachedPlayer.isLocalPlayer);

                                    ImGuiIV.TreePop();
                                }
                            }
                        }

                        ImGuiIV.TreePop();
                    }

                    ImGuiIV.TreePop();
                }

                // Game
                if (ImGuiIV.TreeNode("Game"))
                {

                    ImGuiIV.SeparatorText("States");
                    ImGuiIV.BeginDisabled();
                    ImGuiIV.CheckBox("FirstFrame", ref Main.Instance.FirstFrame);
                    ImGuiIV.CheckBox("IsGTAIVWindowInFocus", ref Main.Instance.IsGTAIVWindowInFocus);
                    ImGuiIV.CheckBox("OnWindowFocusChangedEventCalled", ref Main.Instance.OnWindowFocusChangedEventCalled);
                    ImGuiIV.EndDisabled();

                    ImGuiIV.Spacing();

                    // Pad
                    if (ImGuiIV.TreeNode("Pad"))
                    {
                        IVPad pad = IVPad.GetPad();
                        ImGuiIV.TextUnformatted("Pad Pointer: {0} ({1})", pad.GetUIntPtr(), pad.GetUIntPtr().ToUInt32().ToString("X"));

                        unsafe
                        {
                            bool isUsingController = *(bool*)(pad.GetUIntPtr().ToUInt32() + 0x328C);
                            ImGuiIV.TextUnformatted("isUsingController: {0}", isUsingController);
                        }

                        ImGuiIV.TreePop();
                    }

                    // Player
                    if (ImGuiIV.TreeNode("Player"))
                    {
                        UIntPtr playerPedPtr = IVPlayerInfo.FindThePlayerPed();
                        
                        if (playerPedPtr != UIntPtr.Zero)
                        {
                            ImGuiIV.TextUnformatted("Player Ped Pointer: {0} ({1})", playerPedPtr, playerPedPtr.ToUInt32().ToString("X"));
                            ImGuiIV.TextUnformatted("PlayerHandle: {0}", Main.Instance.PlayerPedHandle);
                            ImGuiIV.TextUnformatted("PlayerVehicleHandle: {0}", Main.Instance.PlayerVehicleHandle);
                            ImGuiIV.TextUnformatted("DoesPlayerCharExists: {0}", IVSDKDotNet.Native.Natives.DOES_CHAR_EXIST(Main.Instance.PlayerPedHandle));
                        }
                        else
                        {
                            ImGuiIV.TextDisabled("Player does not exist yet");
                        }

                        ImGuiIV.TreePop();
                    }

                    // Players
                    if (ImGuiIV.TreeNode("Players"))
                    {
                        for (int i = 0; i < 32; i++)
                        {
                            ImGuiIV.TextUnformatted("Is player {0} active: {1}", i, IVPlayerInfo.IsPlayerActive(i));
                        }

                        ImGuiIV.TreePop();
                    }

                    // Phone
                    if (ImGuiIV.TreeNode("Phone"))
                    {

                        IVPhoneInfo thePhoneInfo = IVPhoneInfo.ThePhoneInfo;

                        if (thePhoneInfo != null && IVPlayerInfo.FindThePlayerPed() != UIntPtr.Zero)
                        {
                            ImGuiIV.TextUnformatted("Current Phone Number: {0}", thePhoneInfo.CurrentNumberInput);
                            ImGuiIV.TextUnformatted("Phone State: {0}", (ePhoneState)thePhoneInfo.State);
                        }
                        else
                        {
                            ImGuiIV.TextDisabled("Phone is not initialized yet");
                        }

                        ImGuiIV.TreePop();
                    }

                    // Zones
                    if (ImGuiIV.TreeNode("Zones"))
                    {
                        ImGuiIV.TextDisabled("TotalNumberOfMapZones: {0}", IVTheZones.TotalNumberOfMapZones);
                        ImGuiIV.TextDisabled("ZonesRevealed: {0}", IVTheZones.ZonesRevealed);

                        //string name = IVTheZones.GetZoneNameByCoords(Main.Instance.ppos);
                        //int index = IVTheZones.GetZoneNumberByName(name);
                        //ImGuiIV.TextUnformatted("Current Zone Name (by coords): {0}", name);
                        //ImGuiIV.TextUnformatted("Current number: {0}", index);
                        //ImGuiIV.TextUnformatted("Current zone name by index: {0}", IVTheZones.GetZoneNameByIndex(index));

                        if (ImGuiIV.Button("Reset"))
                            IVTheZones.Reset();

                        if (ImGuiIV.CollapsingHeader("Add new zone##ManagerZonesHeader"))
                        {
                            if (ImGuiIV.Button("Add"))
                                Logger.LogDebugEx("Added new zone. Index: {0}", IVTheZones.Add(zoneInfoLabel, zoneTextLabel, zoneMin, zoneMax));

                            ImGuiIV.InputText("InfoLabel", ref zoneInfoLabel);
                            ImGuiIV.InputText("TextLabel", ref zoneTextLabel);
                            ImGuiIV.DragFloat3("Min", ref zoneMin);
                            ImGuiIV.DragFloat3("Max", ref zoneMax);
                        }

                        IVZone[] zones = IVTheZones.MapZoneArray;
                        for (int i = 0; i < zones.Length; i++)
                        {
                            IVZone zone = zones[i];

                            if (ImGuiIV.TreeNode(string.Format("Zone #{0} ({1})", i, zone.InfoLabel)))
                            {
                                ImGuiIV.TextUnformatted("InfoLabel: {0}", zone.InfoLabel);
                                ImGuiIV.TextUnformatted("TextLabel: {0}", zone.TextLabel);
                                ImGuiIV.TextUnformatted("MinX: {0}", zone.MinX);
                                ImGuiIV.TextUnformatted("MinY: {0}", zone.MinY);
                                ImGuiIV.TextUnformatted("MinZ: {0}", zone.MinZ);
                                ImGuiIV.TextUnformatted("MaxX: {0}", zone.MaxX);
                                ImGuiIV.TextUnformatted("MaxY: {0}", zone.MaxY);
                                ImGuiIV.TextUnformatted("MaxZ: {0}", zone.MaxZ);
                                ImGuiIV.TextUnformatted("Unk1: {0}", zone.Unk1);
                                ImGuiIV.TextUnformatted("Unk2: {0}", zone.Unk2);
                                ImGuiIV.TextUnformatted("PopulationType: {0}", zone.PopulationType);
                                ImGuiIV.TextUnformatted("Scumminess: {0}", zone.Scumminess);

                                //ImGuiIV.TextColored(Color.Yellow, "Is player within zone: {0}", IVTheZones.IsPointInZone(Main.Instance.ppos, zone));

                                ImGuiIV.TreePop();
                            }
                        }

                        ImGuiIV.TreePop();
                    }

                    
                    ImGuiIV.TreePop();
                }

                // ImGui
                if (ImGuiIV.TreeNode("ImGui"))
                {
                    IntPtr rageD3D9DevicePtr = RAGE.GetDirect3DDevice9();
                    ImGuiIV.TextUnformatted("RAGE Direct3D Device 9:        {0} ({1})", rageD3D9DevicePtr, rageD3D9DevicePtr.ToInt32().ToString("X"));
                    ImGuiIV.TextUnformatted("EndScene Direct3D Device 9:    {0} ({1})", devicePtr, devicePtr.ToInt32().ToString("X"));

                    ImGuiIV.Spacing();
                    ImGuiIV.SeparatorText("ImGuiIV States");
                    ImGuiIV.TextUnformatted("ActiveScriptWindows: {0}", ImGuiIV.ActiveScriptWindows);

                    ImGuiIV.Spacing();
                    ImGuiIV.SeparatorText("IO States");
                    ImGuiIV_IO io = ImGuiIV.GetIO();
                    ImGuiIV.TextUnformatted("WantCaptureKeyboard: {0}", io.WantCaptureKeyboard);
                    ImGuiIV.TextUnformatted("WantCaptureMouse: {0}", io.WantCaptureMouse);
                    ImGuiIV.TextUnformatted("WantTextInput: {0}", io.WantTextInput);

                    ImGuiIV.TreePop();
                }

                // File Cache Manager
                if (ImGuiIV.TreeNode("File Cache Manager"))
                {
                    ImGuiIV.TextUnformatted("View all the currently cached files in the following directories");

                    if (ImGuiIV.Button("Get full path of file"))
                    {
                        string scriptPath = FileCacheManager.GetFullPathOfCachedFile("Businesses.net.dll", Folder.Scripts | Folder.IVSDKDotNet_Scripts);
                        
                        if (scriptPath == null)
                        {
                            Logger.LogWarning("could not find file");
                        }
                        else
                        {
                            Logger.LogWarning(scriptPath);
                        }
                    }
                    if (ImGuiIV.Button("Test IsFilePresentWithVersionCheck"))
                    {
                        Logger.LogWarningEx("No wildcard exact version: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", "1.9.0.38745"));
                        Logger.LogWarningEx("No wildcard wrong version: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", "1.9.0"));
                        Logger.Log("-");
                        Logger.LogWarningEx("Equal wildcard exact version: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", "= 1.9.0.38745"));
                        Logger.LogWarningEx("Double equal wildcard exact version: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", "== 1.9.0.38745"));
                        Logger.Log("-");
                        Logger.LogWarningEx("Lower wildcard exact version: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", "< 1.9.0.38745"));
                        Logger.LogWarningEx("Lower wildcard with version 2.0: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", "< 2.0"));
                        Logger.Log("-");
                        Logger.LogWarningEx("Higher wildcard exact version: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", "> 1.9.0.38745"));
                        Logger.LogWarningEx("Higher wildcard with version 1.5: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", "> 1.5"));
                        Logger.Log("-");
                        Logger.LogWarningEx("Lower or equal wildcard exact version: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", "<= 1.9.0.38745"));
                        Logger.LogWarningEx("Lower or equal wildcard with version 2.0: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", "<= 2.0"));
                        Logger.Log("-");
                        Logger.LogWarningEx("Higher or equal wildcard exact version: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", ">= 1.9.0.38745"));
                        Logger.LogWarningEx("Higher or equal wildcard with version 1.5: {0}", FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, "ClonksCodingLib.GTAIV.dll", ">= 1.5"));
                    }

                    if (ImGuiIV.CollapsingHeader("Main Folder"))
                    {
                        string[] files = FileCacheManager.GetCachedFiles(Folder.Main);

                        ImGuiIV.TextColored(Color.Yellow, "{0} cached files.", files.Length);

                        for (int i = 0; i < files.Length; i++)
                        {
                            string file = files[i];
                            ImGuiIV.TextUnformatted(file);
                        }
                    }
                    if (ImGuiIV.CollapsingHeader("Scripts Folder"))
                    {
                        string[] files = FileCacheManager.GetCachedFiles(Folder.Scripts);

                        ImGuiIV.TextColored(Color.Yellow, "{0} cached files.", files.Length);

                        for (int i = 0; i < files.Length; i++)
                        {
                            string file = files[i];
                            ImGuiIV.TextUnformatted(file);
                        }
                    }
                    if (ImGuiIV.CollapsingHeader("Plugins Folder"))
                    {
                        string[] files = FileCacheManager.GetCachedFiles(Folder.Plugins);

                        ImGuiIV.TextColored(Color.Yellow, "{0} cached files.", files.Length);

                        for (int i = 0; i < files.Length; i++)
                        {
                            string file = files[i];
                            ImGuiIV.TextUnformatted(file);
                        }
                    }
                    if (ImGuiIV.CollapsingHeader("Update Folder"))
                    {
                        string[] files = FileCacheManager.GetCachedFiles(Folder.Update);

                        ImGuiIV.TextColored(Color.Yellow, "{0} cached files.", files.Length);

                        for (int i = 0; i < files.Length; i++)
                        {
                            string file = files[i];
                            ImGuiIV.TextUnformatted(file);
                        }
                    }
                    if (ImGuiIV.CollapsingHeader("IVSDKDotNet\\Scripts Folder"))
                    {
                        string[] files = FileCacheManager.GetCachedFiles(Folder.IVSDKDotNet_Scripts);

                        ImGuiIV.TextColored(Color.Yellow, "{0} cached files.", files.Length);

                        for (int i = 0; i < files.Length; i++)
                        {
                            string file = files[i];
                            ImGuiIV.TextUnformatted(file);
                        }
                    }

                    ImGuiIV.TreePop();
                }

                // MinHook Manager
                if (ImGuiIV.TreeNode("MinHook Manager"))
                {
                    ImGuiIV.TextUnformatted("Registered Hooks count: {0}", MinHookManager.GetRegisteredHooksCount());
                    ImGuiIV.TreePop();
                }

                //ImGuiIV.Spacing();
                //ImGuiIV.SeparatorText("Test Notification and Popup");
                //ImGuiIV.CheckBox("Test notification is error", ref testNotifyIsError);

                //ImGuiIV.InputText("TestNotifyTitle", ref testNotifyTitle);
                //ImGuiIV.InputText("TestNotifyDesc", ref testNotifyDesc);
                //ImGuiIV.InputText("TestNotifyAdditionalContent", ref testNotifyAdditionalContent);

                //if (ImGuiIV.Button("Show test notification"))
                //    NotificationUI.ShowNotificationEx(testNotifyIsError ? NotificationType.Error : NotificationType.Default,
                //        DateTime.UtcNow.AddSeconds(5d),
                //        new NotificationContent(testNotifyTitle, testNotifyDesc, testNotifyAdditionalContent),
                //        null);

                //if (ImGuiIV.Button("open test popup"))
                //{
                //    ImGuiIV.OpenPopup("testpopuplkof");
                //}

                //ImGuiIV.CreateSimplePopupDialog("testpopuplkof", "test", true, true, true, "close", "test", () => { }, () => { });

                /// @separator
                ImGuiIV.EndTabItem();
            }
            /// @end TabItem
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
                ImGuiIV.TextUnformatted(string.Format("Active IV-SDK .NET Scripts: {0}", ScriptManager.GetIVSDKDotNetScripts().Length));
                /// @end Text

                /// @begin Text
                ImGuiIV.TextUnformatted(string.Format("Active ScriptHookDotNet Scripts: {0}", ScriptManager.GetScriptHookDotNetScripts().Length));
                /// @end Text

                /// @begin Text
                // Time since last script reload
                TimeSpan timeSinceLastScriptLoad = DateTime.Now - ScriptManager.TimeSinceLastScriptLoad;

                if (timeSinceLastScriptLoad.TotalSeconds < 59d)
                    ImGuiIV.TextUnformatted("Last Script Load Occured: {0} Second(s) ago ({1})", (int)timeSinceLastScriptLoad.TotalSeconds, ScriptManager.TimeSinceLastScriptLoad);
                else if (timeSinceLastScriptLoad.TotalMinutes < 61d)
                    ImGuiIV.TextUnformatted("Last Script Load Occured: {0} Minute(s) ago ({1})", (int)timeSinceLastScriptLoad.TotalMinutes, ScriptManager.TimeSinceLastScriptLoad);
                else
                    ImGuiIV.TextUnformatted("Last Script Load Occured: {0} Hour(s) ago ({1})", (int)timeSinceLastScriptLoad.TotalHours, ScriptManager.TimeSinceLastScriptLoad);
                /// @end Text

                /// @begin Separator
                ImGuiIV.Spacing(3);
                ImGuiIV.SeparatorText("Control");
                /// @end Separator

                /// @begin Button
                if (ImGuiIV.Button("Abort all Scripts", new Vector2(150f, 0f)))
                {
                    ScriptManager.AbortScripts(ScriptType.All, AbortReason.Manager);
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
                    ScriptManager.AbortScripts(ScriptType.IVSDKDotNet, AbortReason.Manager);
                }
                /// @end Button

                /// @begin Button
                ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                if (ImGuiIV.Button("Abort all ScriptHookDotNet Scripts", new Vector2(290f, 0f)))
                {
                    ScriptManager.AbortScripts(ScriptType.ScriptHookDotNet, AbortReason.Manager);
                }
                /// @end Button

                /// @begin Separator
                ImGuiIV.SeparatorEx(eImGuiSeparatorFlags.Horizontal);
                /// @end Separator

                /// @begin Button
                if (ImGuiIV.Button("Reload all Scripts", new Vector2(150f, 0f)))
                {
                    ScriptManager.LoadScriptsInternal();
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
                    ScriptManager.LoadIVSDKDotNetScripts();
                }
                /// @end Button

                /// @begin Button
                ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                if (ImGuiIV.Button("Reload all ScriptHookDotNet Scripts", new Vector2(290f, 0f)))
                {
                    ScriptManager.LoadSHDNScripts();
                }
                /// @end Button

                /// @begin Separator
                ImGuiIV.Spacing(3);
                ImGuiIV.SeparatorText("Active Scripts");
                /// @end Separator

                /// @begin CheckBox
                ImGuiIV.CheckBox("Show IV-SDK .NET scripts", ref showIVSDKDotNetScripts);
                /// @end CheckBox

                /// @begin CheckBox
                ImGuiIV.SameLine(0, 2 * ImGuiIV.GetStyle().ItemSpacing.X);
                ImGuiIV.CheckBox("Show ScriptHookDotNet scripts", ref showScriptHookDotNetScripts);
                /// @end CheckBox

                /// @begin CheckBox
                ImGuiIV.SameLine(0, 2 * ImGuiIV.GetStyle().ItemSpacing.X);
                ImGuiIV.CheckBox("Show constructed scripts only", ref showOnlyConstructedScripts);
                /// @end CheckBox

                /// @begin Text
                ImGuiIV.TextUnformatted("Search for scripts by file name or actual name");
                /// @end Text

                /// @begin Input
                ImGuiIV.SetNextItemWidth(350);
                ImGuiIV.InputText("##scriptNameFilterInputText", ref scriptNameFilter);
                /// @end Input

                /// @begin Separator
                ImGuiIV.Spacing(3);
                ImGuiIV.SeparatorEx(eImGuiSeparatorFlags.Horizontal);
                /// @end Separator

                if (ScriptManager.GetActiveScriptsCount() == 0)
                {
                    /// @begin Text
                    ImGuiIV.TextDisabled("There are currently no active scripts.");
                    /// @end Text
                }
                else
                {
                    for (int i = 0; i < ScriptManager.GetActiveScriptsCount(); i++)
                    {
                        FoundScript fs = ScriptManager.GetActiveScripts()[i];

                        // Filter
                        if (showOnlyConstructedScripts && !fs.WasConstructed())
                            continue;

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

                                if (!fs.EntryPoint.FullName.ToLower().Contains(searchStringLower)
                                    && !fs.TheFileInfo.DoesStringMatchWithAnyFileName(searchStringLower, true, true))
                                {
                                    continue;
                                }
                            }
                        }
                        else
                        {
                            if (!string.IsNullOrWhiteSpace(scriptNameFilter))
                            {
                                string searchStringLower = scriptNameFilter.ToLower();

                                if (!fs.EntryPoint.FullName.ToLower().Contains(searchStringLower)
                                    && !fs.TheFileInfo.DoesStringMatchWithAnyFileName(searchStringLower, true, true))
                                {
                                    continue;
                                }
                            }
                        }

                        // Make it obvious when a script was not yet constructed
                        bool wasCustomHeaderStylePushed = false;
                        if (!fs.WasConstructed())
                        {
                            ImGuiIV.PushStyleColor(eImGuiCol.Header,        Color.FromArgb(100, 255, 255, 0));
                            ImGuiIV.PushStyleColor(eImGuiCol.HeaderHovered, Color.FromArgb(150, 255, 255, 0));
                            ImGuiIV.PushStyleColor(eImGuiCol.HeaderActive,  Color.FromArgb(165, 255, 255, 0));
                            wasCustomHeaderStylePushed = true;
                        }

                        /// @begin CollapsingHeader
                        if (ImGuiIV.CollapsingHeader(string.Format("{0} ({1} - {2})", fs.EntryPoint.FullName, fs.ScriptType, fs.ID)))
                        {
                            if (wasCustomHeaderStylePushed)
                            {
                                ImGuiIV.PopStyleColor(3);
                                wasCustomHeaderStylePushed = false;
                            }

                            if (!fs.WasConstructed())
                            {
                                ImGuiIV.TextColored(Color.Yellow, "This script was not constructed yet.");
                                ImGuiIV.TextColored(Color.Yellow, "More things will be available here once the script was constructed.");
                                ImGuiIV.Spacing();
                            }

                            /// @begin Separator
                            ImGuiIV.SeparatorText("Control");
                            /// @end Separator

                            /// @begin Button
                            if (ImGuiIV.Button("Abort this script", new Vector2(150f, 0f)))
                            {
                                ScriptManager.AbortScriptInternal(AbortReason.Manual, fs, false, true);
                                goto SKIP_TO_END;
                            }
                            /// @end Button

                            /// @begin Button
                            ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                            if (ImGuiIV.Button("Reload this script", new Vector2(170f, 0f)))
                            {
                                string fullPath = fs.TheFileInfo.FullPath;
                                string actualName = fs.EntryPoint.FullName;
                                if (ScriptManager.AbortScriptInternal(AbortReason.Manual, fs, true))
                                {
                                    if (!ScriptManager.LoadAssembly(fullPath))
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

                            if (fs.WasConstructed())
                            {
                                /// @begin Button
                                ImGuiIV.SameLine(0, 1 * ImGuiIV.GetStyle().ItemSpacing.X);
                                if (ImGuiIV.Button(fs.Running ? "Pause this script" : "Resume this script", new Vector2(170f, 0f)))
                                {
                                    fs.Running = !fs.Running;
                                }
                                /// @end Button
                            }

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

                                // ===========================================
                                // ================ COLUMN 0 =================
                                // ===========================================
                                ImGuiIV.TextUnformatted("Type");
                                ImGuiIV.TextUnformatted("ID");
                                ImGuiIV.TextUnformatted("Actual Name");
                                ImGuiIV.TextUnformatted("File Name");
                                ImGuiIV.TextUnformatted("Path");
                                ImGuiIV.TextUnformatted("Active Tasks");
                                ImGuiIV.TextUnformatted("Uses Threaded Tick");

                                if (fs.IsIVSDKDotNetScript && fs.IsScriptReady())
                                {
                                    ImGuiIV.TextUnformatted("No Abort Forced");
                                }

                                ImGuiIV.TextUnformatted("Was Constructed");
                                ImGuiIV.TextUnformatted("Is Ready");
                                ImGuiIV.TextUnformatted("Is Running");

                                // ===========================================
                                // ================ COLUMN 1 =================
                                // ===========================================
                                ImGuiIV.TableNextColumn(1);

                                ImGuiIV.TextUnformatted(fs.ScriptType.ToString()); // Type
                                ImGuiIV.TextUnformatted(fs.ID.ToString()); // ID
                                ImGuiIV.TextUnformatted(fs.EntryPoint.FullName); // Actual Name
                                ImGuiIV.TextUnformatted(fs.TheFileInfo.FileName); // File Name

                                ImGuiIV.TextUnformatted(fs.TheFileInfo.FullPath); // Path
                                ImGuiIV.SetItemTooltip(fs.TheFileInfo.FullPath);

                                ImGuiIV.TextUnformatted(Main.Instance.ActiveTasks.Count(x => x.OwnerID == fs.ID).ToString()); // Active Tasks
                                ImGuiIV.TextUnformatted((fs.ThreadID != -1).ToString()); // Uses Threaded Tick

                                if (fs.IsIVSDKDotNetScript && fs.IsScriptReady())
                                {
                                    ImGuiIV.TextUnformatted(fs.GetScriptAs<Script>().ForceNoAbort.ToString()); // No Abort Forced
                                }

                                ImGuiIV.TextUnformatted(fs.WasConstructed().ToString()); // Was Constructed
                                ImGuiIV.TextUnformatted(fs.IsScriptReady().ToString()); // Is Ready
                                ImGuiIV.TextUnformatted(fs.Running.ToString()); // Is Running

                                /// @separator
                                ImGuiIV.EndTable();
                            }
                            /// @end Table

                            if (fs.WasConstructed())
                            {
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
                            }

                            ImGuiIV.Spacing(3);
                        }
                        /// @end CollapsingHeader
                        
                        if (wasCustomHeaderStylePushed)
                        {
                            ImGuiIV.PopStyleColor(3);
                            wasCustomHeaderStylePushed = false;
                        }
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
                ImGuiIV.TextUnformatted(string.Format("Active Plugins: {0}", PluginManager.GetActivePluginsCount()));
                /// @end Text

                /// @begin Text
                // Time since last plugin reload
                TimeSpan timeSinceLastPluginLoad = DateTime.Now - PluginManager.TimeSinceLastPluginLoad;

                if (timeSinceLastPluginLoad.TotalSeconds < 59d)
                    ImGuiIV.TextUnformatted("Last Plugin Load Occured: {0} Second(s) ago ({1})", (int)timeSinceLastPluginLoad.TotalSeconds, PluginManager.TimeSinceLastPluginLoad);
                else if (timeSinceLastPluginLoad.TotalMinutes < 61d)
                    ImGuiIV.TextUnformatted("Last Plugin Load Occured: {0} Minute(s) ago ({1})", (int)timeSinceLastPluginLoad.TotalMinutes, PluginManager.TimeSinceLastPluginLoad);
                else
                    ImGuiIV.TextUnformatted("Last Plugin Load Occured: {0} Hour(s) ago ({1})", (int)timeSinceLastPluginLoad.TotalHours, PluginManager.TimeSinceLastPluginLoad);
                /// @end Text

                /// @begin Separator
                ImGuiIV.Spacing(3);
                ImGuiIV.SeparatorText("Control");
                /// @end Separator

                /// @begin Button
                if (ImGuiIV.Button("Reload all plugins", new Vector2(150f, 0f)))
                {
                    PluginManager.LoadPlugins();
                }
                /// @end Button

                ImGuiIV.SameLine(0, 3 * ImGuiIV.GetStyle().ItemSpacing.X);

                /// @begin Button
                if (ImGuiIV.Button("Unload all plugins", new Vector2(150f, 0f)))
                {
                    PluginManager.UnloadPlugins(AbortReason.Manual, true);
                }
                /// @end Button

                /// @begin Separator
                ImGuiIV.Spacing(3);
                ImGuiIV.SeparatorText("Active plugins");
                /// @end Separator

                if (PluginManager.ActivePlugins.Count == 0)
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

                    for (int i = 0; i < PluginManager.ActivePlugins.Count; i++)
                    {
                        FoundPlugin plugin = PluginManager.ActivePlugins[i];

                        if (!plugin.IsReady())
                            continue;

                        /// @begin CollapsingHeader
                        if (ImGuiIV.CollapsingHeader(string.Format("{0} by {1}##IVSDKDotNetManagerPlugin", plugin.ThePluginInstance.DisplayName, plugin.ThePluginInstance.Author)))
                        {
                            // Allow plugin to draw their own stuff within this CollapsingHeader
                            PluginManager.RaiseOnImGuiManagerRenderingEvent(plugin, devicePtr);
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
                                    PluginManager.UnloadPlugin(AbortReason.Manual, plugin, true);
                                }
                                else
                                {
                                    NotificationUI.ShowNotification(NotificationType.Info, DateTime.UtcNow.AddSeconds(5d), string.Format("Plugin {0} cannot be unloaded.", plugin.EntryPoint.FullName), "The Plugin set to never allow unloads except if it creates an error.", "PLUGIN_CANNOT_BE_ABORTED");
                                }
                            }
                            if (ImGuiIV.Selectable("Reload this Plugin"))
                            {
                                if (plugin.CanPluginBeAborted(AbortReason.Manual, false))
                                {
                                    string fullPath = plugin.FullPath;
                                    string actualName = plugin.EntryPoint.FullName;
                                    if (PluginManager.UnloadPlugin(AbortReason.Manual, plugin, true))
                                    {
                                        if (!PluginManager.LoadAssembly(fullPath))
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
                                    NotificationUI.ShowNotification(NotificationType.Info, DateTime.UtcNow.AddSeconds(5d), string.Format("Plugin {0} cannot be reloaded.", plugin.EntryPoint.FullName), "The Plugin set to never allow unloads except if it creates an error.", "PLUGIN_CANNOT_BE_ABORTED");
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

                    ImGuiIV.HelpMarker("Adjusts the scale of all fonts in ImGui-based windows (e.g., Manager and Console).");
                    ImGuiIV.SameLine();
                    ImGuiIV.SetNextItemWidth(200);
                    ImGuiIV.DragFloat("GlobalFontScale", ref Config.GlobalFontScale, 0.01f);

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
                ImGuiIV.TextUnformatted("Current IVSDKDotNetWrapper Version: {0}", CLR.CLRBridge.Version);
                /// @end Text

                /// @begin Text
                ImGuiIV.TextUnformatted("Current included ScriptHookDotNet Version: {0}", SHDNManager.CurrentSHDNVersion);
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