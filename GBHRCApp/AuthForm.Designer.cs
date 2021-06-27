namespace GBHRCApp
{
    partial class AuthForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.title_lable = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.token_field = new System.Windows.Forms.TextBox();
            this.next_button = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // title_lable
            // 
            this.title_lable.AutoSize = true;
            this.title_lable.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.title_lable.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(182)))), ((int)(((byte)(182)))), ((int)(((byte)(182)))));
            this.title_lable.Location = new System.Drawing.Point(9, 9);
            this.title_lable.Name = "title_lable";
            this.title_lable.Size = new System.Drawing.Size(120, 33);
            this.title_lable.TabIndex = 0;
            this.title_lable.Text = "GBHRC";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.SystemColors.Menu;
            this.label1.Location = new System.Drawing.Point(12, 62);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Enter auth token";
            // 
            // token_field
            // 
            this.token_field.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(51)))), ((int)(((byte)(51)))), ((int)(((byte)(51)))));
            this.token_field.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.token_field.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.token_field.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(80)))), ((int)(((byte)(80)))));
            this.token_field.Location = new System.Drawing.Point(12, 78);
            this.token_field.Name = "token_field";
            this.token_field.Size = new System.Drawing.Size(394, 24);
            this.token_field.TabIndex = 2;
            // 
            // next_button
            // 
            this.next_button.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(51)))), ((int)(((byte)(51)))), ((int)(((byte)(51)))));
            this.next_button.FlatAppearance.BorderSize = 0;
            this.next_button.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.next_button.ForeColor = System.Drawing.SystemColors.Menu;
            this.next_button.Location = new System.Drawing.Point(12, 113);
            this.next_button.Name = "next_button";
            this.next_button.Size = new System.Drawing.Size(394, 51);
            this.next_button.TabIndex = 3;
            this.next_button.Text = "NEXT";
            this.next_button.UseVisualStyleBackColor = false;
            this.next_button.Click += new System.EventHandler(this.next_button_Click);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(51)))), ((int)(((byte)(51)))), ((int)(((byte)(51)))));
            this.panel1.Location = new System.Drawing.Point(15, 45);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(391, 3);
            this.panel1.TabIndex = 4;
            // 
            // AuthForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.ClientSize = new System.Drawing.Size(418, 176);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.next_button);
            this.Controls.Add(this.token_field);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.title_lable);
            this.Name = "AuthForm";
            this.Text = "AuthForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label title_lable;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox token_field;
        private System.Windows.Forms.Button next_button;
        private System.Windows.Forms.Panel panel1;
    }
}