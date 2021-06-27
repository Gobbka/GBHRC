using GBHRCApp.API;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GBHRCApp
{
    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Form next_form;
            var token = RubtidApi.get_local_token();
            if (token != null)
            {
                string response; 
                if(!RubtidApi.auth(token, out response))
                {
                    MessageBox.Show(response);
                    next_form = new AuthForm();
                }
                else
                {
                    next_form = new MainForm();
                }
            }
            else
            {
                next_form = new AuthForm();
            }


            Application.Run(next_form);
        }
    }
}
