using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GBHRCApp.Settings.Themes
{
    class MonokaiTheme : IColorTheme
    {
        public MonokaiTheme(Color background_color)
        {
            // #76715e
            comment_style = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x76, 0x71, 0x5e)), new SolidBrush(background_color), FontStyle.Regular);
            // #fa2772
            keyword_style = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0xfa, 0x27, 0x72)), new SolidBrush(background_color), FontStyle.Regular);
            // #9358fe
            value_style = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x93, 0x58, 0xfe)), new SolidBrush(background_color), FontStyle.Regular);
            // #66d9ee
            function_style = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x66, 0xd9, 0xee)), new SolidBrush(background_color), FontStyle.Regular);

            delimeters_style = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x57, 0x57, 0x57)), new SolidBrush(background_color), FontStyle.Regular);

            string_style = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0xd6, 0x9d, 0x85)), new SolidBrush(background_color), FontStyle.Bold); ;
        }
    }
}
