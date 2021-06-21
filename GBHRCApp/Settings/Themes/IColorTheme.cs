using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GBHRCApp.Settings
{
    abstract class IColorTheme
    {
        public FastColoredTextBoxNS.Style keyword_style { get; protected set; }
        public FastColoredTextBoxNS.Style comment_style { get; protected set; }
        public FastColoredTextBoxNS.Style value_style   { get; protected set; }
        public FastColoredTextBoxNS.Style function_style { get; protected set; }
        public FastColoredTextBoxNS.Style delimeters_style { get; protected set; }
        public FastColoredTextBoxNS.Style string_style { get; protected set; }
    }
}
