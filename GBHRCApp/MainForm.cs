using GBHRCApp.API;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GBHRCApp
{
    public partial class MainForm : Form
    {
        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HTCAPTION = 0x2;

        [DllImport("User32.dll")]
        public static extern bool ReleaseCapture();
        [DllImport("User32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

        public MainForm()
        {
            InitializeComponent();

            try
            {
                var vers = RubtidApi.get_version();
                if (vers != Properties.Settings.Default.dll_version || !File.Exists("GBHRC.dll"))
                {
                    RubtidApi.download_dll();
                    Properties.Settings.Default.Save();
                }
            }
            catch (Exception e)
            {

            }

        }

        private void run_proccess_button_Click(object sender, EventArgs e)
        {
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            GBHRCApi.Inject();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Process.Start("https://discord.gg/QNT6mwXVWg");
        }

        private void button2_Click_1(object sender, EventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {

            try
            {
                RubtidApi.get_version();

                var response = GBHRCApi.Inject();
                if (!response.success())
                {
                    MessageBox.Show(response.get_response(), "Injection error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }catch(Exception exc)
            {
                MessageBox.Show("Server returns: " + exc.Message, "Error");
                return;
            }
        }

        private void panel2_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
