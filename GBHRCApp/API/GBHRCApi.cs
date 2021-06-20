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
        unsafe public struct ApiResponse
        {
            int status;
            IntPtr response;

            public bool success()
            {
                return Convert.ToBoolean(status);
            }

            public string get_response()
            {
                return Marshal.PtrToStringAnsi(response);
            }
        }

        [DllImport("GBHRC_API.dll", CharSet = CharSet.Ansi,CallingConvention =CallingConvention.StdCall)]
        private static extern ApiResponse SendLuaScript(char[] lua_text);

        [DllImport("GBHRC_API.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern ApiResponse Inject();

        [DllImport("GBHRC_API.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern ApiResponse AttachToProcess();

        [DllImport("GBHRC_API.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern ApiResponse DeAttachFromProcess();

        static public ApiResponse send_lua(string script)
        {
            script += ' ';
            var array = script.ToList();
            array.Add('\0');
            return SendLuaScript(array.ToArray());
        }
    }
}
