using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using GBHRCApp.API;


namespace GBHRCApp
{
    public partial class LuaForm : Form
    {
        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HTCAPTION = 0x2;

        [DllImport("User32.dll")]
        public static extern bool ReleaseCapture();
        [DllImport("User32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);


        FastColoredTextBoxNS.Style orangestyle;
        FastColoredTextBoxNS.Style greenstyle;
        FastColoredTextBoxNS.Style graystyle;
        FastColoredTextBoxNS.Style bluestyle;
        FastColoredTextBoxNS.Style pinkstyle;

        bool attached = false;
        public LuaForm()
        {
            InitializeComponent();
            orangestyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0xd6,0x9d,0x85)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
            greenstyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x41,0xb4,0x95)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
            graystyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x57,0x57,0x57)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
            bluestyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x89,0xd4,0xe6)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
           
            pinkstyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0xc4,0x7b,0xad)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);

            this.fastColoredTextBox1.Text = "-- a new blank space --join GBHRC discord channel";
            update_files_list();
        }

        void update_files_list()
        {
            if (!Directory.Exists("lua"))
                Directory.CreateDirectory("lua");

            var files = Directory.GetFiles("lua");

            foreach(var file in files)
            {
                ScriptBox.Items.Add(file);
            }
        }

        public string get_text()
        {
            return this.fastColoredTextBox1.Text;
        }

        public void select_script_item(string path)
        {
            fastColoredTextBox1.Text = File.ReadAllText(path);
            CurrentFileLabel.Text = path;
        }

        private void fastColoredTextBox1_Load(object sender, EventArgs e)
        {

        }

        private void fastColoredTextBox1_TextChanged(object sender, FastColoredTextBoxNS.TextChangedEventArgs e)
        {
            e.ChangedRange.ClearStyle(orangestyle);
            e.ChangedRange.ClearStyle(greenstyle);
            e.ChangedRange.ClearStyle(graystyle);
            e.ChangedRange.ClearStyle(bluestyle);
            e.ChangedRange.ClearStyle(pinkstyle);
            //e.ChangedRange.SetStyle(orangestyle, @"\b(local)\s+(?<range>[\w_]+?)\b");
            //e.ChangedRange.SetStyle(greenstyle, @"\b(local)\b");
            e.ChangedRange.SetStyle(greenstyle, @"(--(.+)?)");


            e.ChangedRange.SetStyle(orangestyle, "\"([^\"]+)?\"");
            e.ChangedRange.SetStyle(graystyle, ";");
            e.ChangedRange.SetStyle(pinkstyle, @"\b(for|while|if|end|do|then|function|local)\b");
            e.ChangedRange.SetStyle(bluestyle, @"\b(true|false|nil|\d+)\b");
            e.ChangedRange.SetStyle(bluestyle, @"([\w]+)\(.+?\)");
            e.ChangedRange.SetStyle(graystyle, @"^(#include)\b");

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (!attached)
            {
                GBHRCApi.AttachToProcess();
                attached = true;
            }

            GBHRCApi.send_lua(get_text());
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            // Paste the below code in the your label control MouseDown event
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
            }
        }

        private void ScriptBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            string curItem = ScriptBox.SelectedItem.ToString();
            select_script_item(curItem);
            //
        }
    }
}
