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

        FastColoredTextBoxNS.Style comment_style;
        FastColoredTextBoxNS.Style keyword_style;
        FastColoredTextBoxNS.Style number_style;
        FastColoredTextBoxNS.Style function_style;

        bool attached = false;
        public LuaForm()
        {
            InitializeComponent();
            orangestyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0xd6,0x9d,0x85)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
            greenstyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x41,0xb4,0x95)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
            graystyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x57,0x57,0x57)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
            bluestyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x89,0xd4,0xe6)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Bold);
           
            pinkstyle = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0xc4,0x7b,0xad)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Regular);
            // #76715e
            comment_style = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x76,0x71,0x5e)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Regular);
            // #fa2772
            keyword_style = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0xfa,0x27,0x72)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Regular);
            // #9358fe
            number_style = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x93,0x58,0xfe)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Regular);
            // #66d9ee
            function_style = new FastColoredTextBoxNS.TextStyle(new SolidBrush(Color.FromArgb(0x66,0xd9,0xee)), new SolidBrush(this.fastColoredTextBox1.BackColor), FontStyle.Regular);
            

            this.fastColoredTextBox1.Text = "-- a new blank space --join GBHRC discord channel";
            update_files_list();
        }

        void update_files_list()
        {
            if (!Directory.Exists("lua"))
                Directory.CreateDirectory("lua");

            var files = Directory.GetFiles("lua");
            ScriptBox.Items.Clear();
            foreach(var file in files)
            {
                ScriptBox.Items.Add(file);
            }
        }

        void console_log(string text)
        {
            ConsoleTextBox.Text += (text + "\r\n");
        }

        public string preprocess(string code)
        {
            console_log("[+] Preprocessing");
            console_log("[+] Linking");
            return code;
        }

        public string get_script()
        {
            return preprocess( this.fastColoredTextBox1.Text );
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

            e.ChangedRange.ClearStyle(function_style);
            e.ChangedRange.ClearStyle(comment_style);
            e.ChangedRange.ClearStyle(keyword_style);
            //e.ChangedRange.SetStyle(orangestyle, @"\b(local)\s+(?<range>[\w_]+?)\b");
            //e.ChangedRange.SetStyle(greenstyle, @"\b(local)\b");
            // comment
            e.ChangedRange.SetStyle(comment_style, @"(--(.+)?)");
            // string
            e.ChangedRange.SetStyle(orangestyle, "\"([^\"]+)?\"");

            e.ChangedRange.SetStyle(graystyle, ";|,");
            // key word
            e.ChangedRange.SetStyle(keyword_style, @"\b(for|while|if|end|do|then|function|local)\b");
            // any base type value
            e.ChangedRange.SetStyle(number_style, @"\b(true|false|nil|\d+|0x\d+)\b");
            // function
            e.ChangedRange.SetStyle(function_style, @"([\w]+)\((.+)?\)");
            // pre processor
            e.ChangedRange.SetStyle(graystyle, @"^(#include)\b");

        }

        private void button2_Click(object sender, EventArgs e)
        {
            var result = GBHRCApi.AttachToProcess();
            if (!result.success())
            {
                console_log(result.get_response());
                return;
            }

            result = GBHRCApi.send_lua(get_script());
            if (!result.success())
            {
                console_log(result.get_response());
                return;
            }
            console_log("Script sended");
            GBHRCApi.DeAttachFromProcess();
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
            var item = ScriptBox.SelectedItem;
            if(item != null)
                select_script_item(item.ToString());
            //
        }

        private void exit_button_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void hide_button_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void ClearConsoleButton_Click(object sender, EventArgs e)
        {
            ConsoleTextBox.Text = "";
        }

        private void button4_Click(object sender, EventArgs e)
        {
            update_files_list();
        }

        private void InjectButton_Click(object sender, EventArgs e)
        {
            var result = GBHRCApi.Inject();

            console_log("INJECTION: " + result.get_response());
        }
    }
}
