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
        public LuaForm()
        {
            InitializeComponent();
        }

        public string get_text()
        {
            return this.richTextBox1.Text;
        }
    }
}
