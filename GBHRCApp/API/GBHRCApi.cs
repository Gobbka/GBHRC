using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace GBHRCApp.API
{
    class GBHRCApi
    {
        [DllImport("GBHRC_API.dll", CharSet = CharSet.Ansi,CallingConvention =CallingConvention.StdCall)]
        public static extern bool SendLuaScript(char[] lua_text);

        [DllImport("GBHRC_API.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern bool Inject();
    }
}
