using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GBHRCApp
{
    public partial class LuaForm : Form
    {
        FastColoredTextBoxNS.Style orangestyle;
        FastColoredTextBoxNS.Style greenstyle;
        FastColoredTextBoxNS.Style graystyle;
        FastColoredTextBoxNS.Style bluestyle;
        FastColoredTextBoxNS.Style darkbluestyle;
        public LuaForm()
        {
            InitializeComponent();
            orangestyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0xd6,0x9d,0x85)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
            greenstyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x3f,0xc8,0x83)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
            graystyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x57,0x57,0x57)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
            bluestyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x89,0xd4,0xe6)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
            darkbluestyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x2c,0x68,0xbf)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
        }

        public string get_text()
        {
            return this.fastColoredTextBox1.Text;
        }

        private void fastColoredTextBox1_Load(object sender, EventArgs e)
        {

        }

        private void fastColoredTextBox1_TextChanged(object sender, FastColoredTextBoxNS.TextChangedEventArgs e)
        {
            e.ChangedRange.ClearStyle(graystyle);
            //e.ChangedRange.SetStyle(orangestyle, @"\b(local)\s+(?<range>[\w_]+?)\b");
            e.ChangedRange.SetStyle(greenstyle, @"\b(local)\b");
            e.ChangedRange.SetStyle(orangestyle, "\"(.+)?\"");
            e.ChangedRange.SetStyle(graystyle, ";");
            e.ChangedRange.SetStyle(greenstyle, @"\b(for|while|if|end|then|function)\b");
            e.ChangedRange.SetStyle(darkbluestyle, @"\b(true|false)\b");
            e.ChangedRange.SetStyle(bluestyle, @"([\w]+)\(\)");
            e.ChangedRange.SetStyle(graystyle, @"^(#include)\b");
        }
    }
}
