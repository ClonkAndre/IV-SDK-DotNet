using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using IVSDKDotNet;
using IVSDKDotNet.Manager;

namespace TestPlugin
{
    public class Main : ManagerPlugin
    {

        public Main() : base("TestPlugin", "ItsClonkAndre")
        {
            OnImGuiGlobalRendering += Main_OnImGuiGlobalRendering;
            OnImGuiManagerRendering += Main_OnImGuiManagerRendering;
        }

        private void Main_OnImGuiGlobalRendering(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
        {
            // In here you can use ImGui as you would normally use it...

#if false
            // Example:
            if (ImGuiIV.Begin("TestPluginWindow"))
            {
                ImGuiIV.TextUnformatted("Hello");
            }
            ImGuiIV.End();
#endif
        }
        private void Main_OnImGuiManagerRendering(IntPtr devicePtr)
        {
            // In here you can directly use ImGui widgets as they will be shown within the plugin's collapsing header within the IV-SDK .NET Manager "Plugins" tab.
            ImGuiIV.Text("This will show up in the 'TestPlugin by ItsClonkAndre' collapsing header within the IV-SDK .NET Manager Plugins tab.");
        }

    }
}
