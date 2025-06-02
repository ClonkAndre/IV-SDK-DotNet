using System.Collections.Generic;
using System.Linq;

using IVSDKDotNet.Native;

namespace TestScript
{
    internal static class ListExtensions
    {

        public static List<T> Randomize<T>(this List<T> list)
        {
            // Create a copy of the original list so it doesnt modify the original list
            List<T> result = list.ToList();

            // Go through list and insert items at random places
            for (int i = 0; i < result.Count; i++)
            {
                T item = result[i];

                result.RemoveAt(i);

                result.Insert(Natives.GENERATE_RANDOM_INT_IN_RANGE(0, list.Capacity - 1), item);
            }

            return result;
        }

    }
}
