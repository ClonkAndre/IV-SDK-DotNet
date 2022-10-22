using System;
using System.IO;

namespace Manager {
    internal class Helper {

        public static byte[] GetByteArray(Stream input)
        {
            using (MemoryStream ms = new MemoryStream()) {
                input.CopyTo(ms);
                return ms.ToArray();
            }
        }

    }
}
