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
            OnImGuiRendering += Main_OnImGuiRendering;
        }

        private void Main_OnImGuiRendering(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
        {
            ImGuiIV.Text("This will show up in the 'TestPlugin by ItsClonkAndre' collapsing header within the IV-SDK .NET Manager Plugins tab.");
        }

    }
}
