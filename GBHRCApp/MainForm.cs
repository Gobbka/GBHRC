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
    public partial class MainForm : Form
    {
        LuaForm form;

        public MainForm()
        {
            InitializeComponent();
            this.form = new LuaForm();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.form.Show();
        }

        private void run_proccess_button_Click(object sender, EventArgs e)
        {
            
        }
    }
}
