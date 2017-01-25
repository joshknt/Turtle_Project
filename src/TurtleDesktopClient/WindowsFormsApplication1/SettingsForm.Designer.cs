namespace TurtleDesktop
{
    partial class SettingsForm
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
            this.RFolderTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.RBrowse_button = new System.Windows.Forms.Button();
            this.DataBrowseButton = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.DataFolderTextBox = new System.Windows.Forms.TextBox();
            this.Help_R_Button = new System.Windows.Forms.Button();
            this.Help_Data_Button = new System.Windows.Forms.Button();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.saveButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // RFolderTextBox
            // 
            this.RFolderTextBox.Location = new System.Drawing.Point(12, 92);
            this.RFolderTextBox.Name = "RFolderTextBox";
            this.RFolderTextBox.Size = new System.Drawing.Size(308, 20);
            this.RFolderTextBox.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F);
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(132, 37);
            this.label1.TabIndex = 1;
            this.label1.Text = "Settings";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 73);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(85, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "R 32-Bit BIN File";
            // 
            // RBrowse_button
            // 
            this.RBrowse_button.Location = new System.Drawing.Point(326, 91);
            this.RBrowse_button.Name = "RBrowse_button";
            this.RBrowse_button.Size = new System.Drawing.Size(75, 21);
            this.RBrowse_button.TabIndex = 3;
            this.RBrowse_button.Text = "Browse";
            this.RBrowse_button.UseVisualStyleBackColor = true;
            this.RBrowse_button.Click += new System.EventHandler(this.Browse_button_Click);
            // 
            // DataBrowseButton
            // 
            this.DataBrowseButton.Location = new System.Drawing.Point(326, 133);
            this.DataBrowseButton.Name = "DataBrowseButton";
            this.DataBrowseButton.Size = new System.Drawing.Size(75, 21);
            this.DataBrowseButton.TabIndex = 6;
            this.DataBrowseButton.Text = "Browse";
            this.DataBrowseButton.UseVisualStyleBackColor = true;
            this.DataBrowseButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 115);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(62, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Data Folder";
            // 
            // DataFolderTextBox
            // 
            this.DataFolderTextBox.Location = new System.Drawing.Point(12, 134);
            this.DataFolderTextBox.Name = "DataFolderTextBox";
            this.DataFolderTextBox.Size = new System.Drawing.Size(308, 20);
            this.DataFolderTextBox.TabIndex = 4;
            // 
            // Help_R_Button
            // 
            this.Help_R_Button.Location = new System.Drawing.Point(407, 91);
            this.Help_R_Button.Name = "Help_R_Button";
            this.Help_R_Button.Size = new System.Drawing.Size(75, 21);
            this.Help_R_Button.TabIndex = 7;
            this.Help_R_Button.Text = "Help";
            this.Help_R_Button.UseVisualStyleBackColor = true;
            this.Help_R_Button.Click += new System.EventHandler(this.Help_R_Button_Click);
            // 
            // Help_Data_Button
            // 
            this.Help_Data_Button.Location = new System.Drawing.Point(407, 133);
            this.Help_Data_Button.Name = "Help_Data_Button";
            this.Help_Data_Button.Size = new System.Drawing.Size(75, 21);
            this.Help_Data_Button.TabIndex = 8;
            this.Help_Data_Button.Text = "Help";
            this.Help_Data_Button.UseVisualStyleBackColor = true;
            this.Help_Data_Button.Click += new System.EventHandler(this.Help_Data_Button_Click);
            // 
            // saveButton
            // 
            this.saveButton.Location = new System.Drawing.Point(122, 168);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(128, 31);
            this.saveButton.TabIndex = 9;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.Location = new System.Drawing.Point(256, 168);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(128, 31);
            this.cancelButton.TabIndex = 10;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            // 
            // SettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.LightSkyBlue;
            this.ClientSize = new System.Drawing.Size(501, 211);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.Help_Data_Button);
            this.Controls.Add(this.Help_R_Button);
            this.Controls.Add(this.DataBrowseButton);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.DataFolderTextBox);
            this.Controls.Add(this.RBrowse_button);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.RFolderTextBox);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(517, 250);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(517, 227);
            this.Name = "SettingsForm";
            this.Text = "SettingsForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox RFolderTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button RBrowse_button;
        private System.Windows.Forms.Button DataBrowseButton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox DataFolderTextBox;
        private System.Windows.Forms.Button Help_R_Button;
        private System.Windows.Forms.Button Help_Data_Button;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button cancelButton;
    }
}