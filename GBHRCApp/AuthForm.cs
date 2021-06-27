using GBHRCApp.API;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GBHRCApp
{
    public partial class AuthForm : Form
    {
        public AuthForm()
        {
            InitializeComponent();
        }

        private void next_button_Click(object sender, EventArgs e)
        {
            string response;
            if (!RubtidApi.auth(token_field.Text,out response)){
                MessageBox.Show("server returns:\n" + response, "Auth error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                RubtidApi.set_local_token(token_field.Text);
                MainForm form = new MainForm();
                this.Hide();
                form.ShowDialog();
                this.Close();
            }

            
        }
    }
}
