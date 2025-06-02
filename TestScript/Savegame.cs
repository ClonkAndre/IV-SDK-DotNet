using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CCL.GTAIV;

using IVSDKDotNet;
using IVSDKDotNet.Enums;

namespace TestScript
{
    // Test custom savegame
    internal class Savegame
    {

        public Dictionary<int, float> FloatStats;
        public Dictionary<int, int> IntStats;
        
        public Savegame()
        {
            FloatStats = new Dictionary<int, float>();
            IntStats = new Dictionary<int, int>();
        }

        public void SaveGameStats()
        {
            // Float Stats
            for (int i = 0; i < (int)eFloatStatistic.COUNT; i++)
            {
                FloatStats.Add(i, NativeGame.GetFloatStatistic((eFloatStatistic)i));
            }

            // Int Stats
            for (int i = 253; i < (int)eIntStatistic.COUNT; i++)
            {
                IntStats.Add(i, NativeGame.GetIntegerStatistic((eIntStatistic)i));
            }
        }

        public void SaveToFile(string filename)
        {
            File.WriteAllText(filename, Helper.ConvertObjectToJsonString(this, true));
        }

        public void LoadSavedData()
        {
            // Stats

            // Float Stats
            for (int i = 0; i < (int)eFloatStatistic.COUNT; i++)
            {
                if (FloatStats.TryGetValue(i, out float value))
                    NativeGame.SetFloatStatistic((eFloatStatistic)i, value);
            }

            // Int Stats
            for (int i = 253; i < (int)eIntStatistic.COUNT; i++)
            {
                if (IntStats.TryGetValue(i, out int value))
                    NativeGame.SetIntegerStatistic((eIntStatistic)i, value);
            }
        }

    }
}
