

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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SettingsForm));
            this.RFolderTextBox = new System.Windows.Forms.TextBox();
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
            resources.ApplyResources(this.RFolderTextBox, "RFolderTextBox");
            this.RFolderTextBox.Name = "RFolderTextBox";
            // 
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
            // 
            // RBrowse_button
            // 
            resources.ApplyResources(this.RBrowse_button, "RBrowse_button");
            this.RBrowse_button.Name = "RBrowse_button";
            this.RBrowse_button.UseVisualStyleBackColor = true;
            this.RBrowse_button.Click += new System.EventHandler(this.Browse_button_Click);
            // 
            // DataBrowseButton
            // 
            resources.ApplyResources(this.DataBrowseButton, "DataBrowseButton");
            this.DataBrowseButton.Name = "DataBrowseButton";
            this.DataBrowseButton.UseVisualStyleBackColor = true;
            this.DataBrowseButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // label3
            // 
            resources.ApplyResources(this.label3, "label3");
            this.label3.Name = "label3";
            // 
            // DataFolderTextBox
            // 
            resources.ApplyResources(this.DataFolderTextBox, "DataFolderTextBox");
            this.DataFolderTextBox.Name = "DataFolderTextBox";
            // 
            // Help_R_Button
            // 
            resources.ApplyResources(this.Help_R_Button, "Help_R_Button");
            this.Help_R_Button.FlatAppearance.BorderSize = 0;
            this.Help_R_Button.Name = "Help_R_Button";
            this.Help_R_Button.UseVisualStyleBackColor = true;
            this.Help_R_Button.Click += new System.EventHandler(this.Help_R_Button_Click);
            // 
            // Help_Data_Button
            // 
            resources.ApplyResources(this.Help_Data_Button, "Help_Data_Button");
            this.Help_Data_Button.FlatAppearance.BorderSize = 0;
            this.Help_Data_Button.Name = "Help_Data_Button";
            this.Help_Data_Button.UseVisualStyleBackColor = true;
            this.Help_Data_Button.Click += new System.EventHandler(this.Help_Data_Button_Click);
            // 
            // folderBrowserDialog1
            // 
            resources.ApplyResources(this.folderBrowserDialog1, "folderBrowserDialog1");
            // 
            // saveButton
            // 
            resources.ApplyResources(this.saveButton, "saveButton");
            this.saveButton.Name = "saveButton";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
            // 
            // cancelButton
            // 
            resources.ApplyResources(this.cancelButton, "cancelButton");
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // SettingsForm
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.LightSkyBlue;
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.Help_Data_Button);
            this.Controls.Add(this.Help_R_Button);
            this.Controls.Add(this.DataBrowseButton);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.DataFolderTextBox);
            this.Controls.Add(this.RBrowse_button);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.RFolderTextBox);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SettingsForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox RFolderTextBox;
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