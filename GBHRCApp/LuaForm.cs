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
using GBHRCApp.Settings;
using GBHRCApp.Settings.Themes;

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

        IColorTheme editor_theme;


        bool attached = false;
        public LuaForm()
        {
            this.editor_theme = new MonokaiTheme(Color.FromArgb(51,51,51));

            InitializeComponent();



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

            e.ChangedRange.ClearStyle(editor_theme.function_style);
            e.ChangedRange.ClearStyle(editor_theme.comment_style);
            e.ChangedRange.ClearStyle(editor_theme.keyword_style);
            //e.ChangedRange.SetStyle(orangestyle, @"\b(local)\s+(?<range>[\w_]+?)\b");
            //e.ChangedRange.SetStyle(greenstyle, @"\b(local)\b");
            // comment
            e.ChangedRange.SetStyle(editor_theme.comment_style, @"(--(.+)?)");
            // string
            e.ChangedRange.SetStyle(editor_theme.string_style, "\"([^\"]+)?\"");

            e.ChangedRange.SetStyle(editor_theme.delimeters_style, ";|,");
            // key word
            e.ChangedRange.SetStyle(editor_theme.keyword_style, @"\b(for|while|if|end|do|then|function|local)\b");
            // any base type value
            e.ChangedRange.SetStyle(editor_theme.value_style, @"\b(true|false|nil|\d+|0x\d+)\b");
            // function
            e.ChangedRange.SetStyle(editor_theme.function_style, @"([\w]+)\((.+)?\)");
            // pre processor
            e.ChangedRange.SetStyle(editor_theme.delimeters_style, @"^(#include)\b");

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

        private void button3_Click(object sender, EventArgs e)
        {

        }
    }
}
