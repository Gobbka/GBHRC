using GBHRCApp.API;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GBHRCApp
{
    public partial class MainForm : Form
    {
        LuaForm luaForm;

        public MainForm()
        {
            InitializeComponent();
            this.luaForm = new LuaForm();
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
            this.luaForm.Show();

        }
    }
}
