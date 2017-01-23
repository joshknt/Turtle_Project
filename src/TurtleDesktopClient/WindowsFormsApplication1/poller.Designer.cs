namespace WindowsFormsApplication1
{
    partial class poller
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.printToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.printPreviewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.documentationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.terminal_list = new System.Windows.Forms.ListBox();
            this.sensor_selector = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.dateTimepicker = new System.Windows.Forms.DateTimePicker();
            this.data_tabControl = new System.Windows.Forms.TabControl();
            this.temp_tab = new System.Windows.Forms.TabPage();
            this.accel_tab = new System.Windows.Forms.TabPage();
            this.collectionlist = new System.Windows.Forms.ListBox();
            this.updatelistbutton = new System.Windows.Forms.Button();
            this.collectionStatus = new System.Windows.Forms.RichTextBox();
            this.redtemp_tab = new System.Windows.Forms.TabPage();
            this.yellowtemp_tab = new System.Windows.Forms.TabPage();
            this.bluetemp_tab = new System.Windows.Forms.TabPage();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.data_tabControl.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(667, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem2,
            this.printToolStripMenuItem,
            this.printPreviewToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(37, 20);
            this.toolStripMenuItem1.Text = "File";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(143, 22);
            this.toolStripMenuItem2.Text = "Settings";
            // 
            // printToolStripMenuItem
            // 
            this.printToolStripMenuItem.Name = "printToolStripMenuItem";
            this.printToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.printToolStripMenuItem.Text = "Print";
            // 
            // printPreviewToolStripMenuItem
            // 
            this.printPreviewToolStripMenuItem.Name = "printPreviewToolStripMenuItem";
            this.printPreviewToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.printPreviewToolStripMenuItem.Text = "Print Preview";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.documentationToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // documentationToolStripMenuItem
            // 
            this.documentationToolStripMenuItem.Name = "documentationToolStripMenuItem";
            this.documentationToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
            this.documentationToolStripMenuItem.Text = "Documentation";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
            this.aboutToolStripMenuItem.Text = "About";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 452);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(667, 22);
            this.statusStrip1.TabIndex = 3;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.BackColor = System.Drawing.SystemColors.Control;
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(118, 17);
            this.toolStripStatusLabel1.Text = "toolStripStatusLabel1";
            // 
            // terminal_list
            // 
            this.terminal_list.FormattingEnabled = true;
            this.terminal_list.Location = new System.Drawing.Point(13, 67);
            this.terminal_list.Name = "terminal_list";
            this.terminal_list.Size = new System.Drawing.Size(132, 95);
            this.terminal_list.TabIndex = 4;
            this.terminal_list.SelectedIndexChanged += new System.EventHandler(this.terminal_list_SelectedIndexChanged);
            // 
            // sensor_selector
            // 
            this.sensor_selector.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.sensor_selector.Enabled = false;
            this.sensor_selector.FormattingEnabled = true;
            this.sensor_selector.Location = new System.Drawing.Point(13, 168);
            this.sensor_selector.Name = "sensor_selector";
            this.sensor_selector.Size = new System.Drawing.Size(132, 21);
            this.sensor_selector.TabIndex = 5;
            this.sensor_selector.SelectedIndexChanged += new System.EventHandler(this.sensor_selector_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(153, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 18);
            this.label1.TabIndex = 6;
            this.label1.Text = "Date:";
            // 
            // dateTimepicker
            // 
            this.dateTimepicker.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.dateTimepicker.Location = new System.Drawing.Point(203, 27);
            this.dateTimepicker.Name = "dateTimepicker";
            this.dateTimepicker.Size = new System.Drawing.Size(170, 20);
            this.dateTimepicker.TabIndex = 7;
            this.dateTimepicker.ValueChanged += new System.EventHandler(this.dateTimepicker_ValueChanged);
            // 
            // data_tabControl
            // 
            this.data_tabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.data_tabControl.Controls.Add(this.temp_tab);
            this.data_tabControl.Controls.Add(this.accel_tab);
            this.data_tabControl.Controls.Add(this.redtemp_tab);
            this.data_tabControl.Controls.Add(this.yellowtemp_tab);
            this.data_tabControl.Controls.Add(this.bluetemp_tab);
            this.data_tabControl.Location = new System.Drawing.Point(156, 54);
            this.data_tabControl.Name = "data_tabControl";
            this.data_tabControl.SelectedIndex = 0;
            this.data_tabControl.Size = new System.Drawing.Size(499, 379);
            this.data_tabControl.TabIndex = 8;
            // 
            // temp_tab
            // 
            this.temp_tab.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.temp_tab.Location = new System.Drawing.Point(4, 22);
            this.temp_tab.Name = "temp_tab";
            this.temp_tab.Padding = new System.Windows.Forms.Padding(3);
            this.temp_tab.Size = new System.Drawing.Size(491, 353);
            this.temp_tab.TabIndex = 0;
            this.temp_tab.Text = "Temperature";
            this.temp_tab.UseVisualStyleBackColor = true;
            // 
            // accel_tab
            // 
            this.accel_tab.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.accel_tab.Location = new System.Drawing.Point(4, 22);
            this.accel_tab.Name = "accel_tab";
            this.accel_tab.Size = new System.Drawing.Size(491, 353);
            this.accel_tab.TabIndex = 2;
            this.accel_tab.Text = "Movement";
            this.accel_tab.UseVisualStyleBackColor = true;
            // 
            // collectionlist
            // 
            this.collectionlist.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.collectionlist.Enabled = false;
            this.collectionlist.FormattingEnabled = true;
            this.collectionlist.Location = new System.Drawing.Point(13, 195);
            this.collectionlist.Name = "collectionlist";
            this.collectionlist.Size = new System.Drawing.Size(132, 238);
            this.collectionlist.TabIndex = 10;
            this.collectionlist.SelectedIndexChanged += new System.EventHandler(this.collectionlist_SelectedIndexChanged);
            // 
            // updatelistbutton
            // 
            this.updatelistbutton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.updatelistbutton.Location = new System.Drawing.Point(12, 29);
            this.updatelistbutton.Name = "updatelistbutton";
            this.updatelistbutton.Size = new System.Drawing.Size(133, 32);
            this.updatelistbutton.TabIndex = 11;
            this.updatelistbutton.Text = "Update Lists";
            this.updatelistbutton.UseVisualStyleBackColor = true;
            this.updatelistbutton.Click += new System.EventHandler(this.updatelistbutton_Click);
            // 
            // collectionStatus
            // 
            this.collectionStatus.BackColor = System.Drawing.SystemColors.Window;
            this.collectionStatus.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.collectionStatus.Location = new System.Drawing.Point(22, 208);
            this.collectionStatus.Name = "collectionStatus";
            this.collectionStatus.ReadOnly = true;
            this.collectionStatus.Size = new System.Drawing.Size(111, 139);
            this.collectionStatus.TabIndex = 12;
            this.collectionStatus.Text = "Select a date, terminal, and sensor to view list of collections.";
            // 
            // redtemp_tab
            // 
            this.redtemp_tab.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.redtemp_tab.Location = new System.Drawing.Point(4, 22);
            this.redtemp_tab.Name = "redtemp_tab";
            this.redtemp_tab.Padding = new System.Windows.Forms.Padding(3);
            this.redtemp_tab.Size = new System.Drawing.Size(491, 353);
            this.redtemp_tab.TabIndex = 3;
            this.redtemp_tab.Text = "Red Temperature";
            this.redtemp_tab.UseVisualStyleBackColor = true;
            // 
            // yellowtemp_tab
            // 
            this.yellowtemp_tab.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.yellowtemp_tab.Location = new System.Drawing.Point(4, 22);
            this.yellowtemp_tab.Name = "yellowtemp_tab";
            this.yellowtemp_tab.Padding = new System.Windows.Forms.Padding(3);
            this.yellowtemp_tab.Size = new System.Drawing.Size(491, 353);
            this.yellowtemp_tab.TabIndex = 4;
            this.yellowtemp_tab.Text = "Yellow Temperature";
            this.yellowtemp_tab.UseVisualStyleBackColor = true;
            // 
            // bluetemp_tab
            // 
            this.bluetemp_tab.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.bluetemp_tab.Location = new System.Drawing.Point(4, 22);
            this.bluetemp_tab.Name = "bluetemp_tab";
            this.bluetemp_tab.Padding = new System.Windows.Forms.Padding(3);
            this.bluetemp_tab.Size = new System.Drawing.Size(491, 353);
            this.bluetemp_tab.TabIndex = 5;
            this.bluetemp_tab.Text = "Blue Temperature";
            this.bluetemp_tab.UseVisualStyleBackColor = true;
            // 
            // poller
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.LightSkyBlue;
            this.ClientSize = new System.Drawing.Size(667, 474);
            this.Controls.Add(this.collectionStatus);
            this.Controls.Add(this.updatelistbutton);
            this.Controls.Add(this.collectionlist);
            this.Controls.Add(this.data_tabControl);
            this.Controls.Add(this.dateTimepicker);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.sensor_selector);
            this.Controls.Add(this.terminal_list);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.Name = "poller";
            this.Text = "poller";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.data_tabControl.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem printToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem printPreviewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem documentationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ListBox terminal_list;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DateTimePicker dateTimepicker;
        private System.Windows.Forms.TabControl data_tabControl;
        private System.Windows.Forms.TabPage temp_tab;
        private System.Windows.Forms.ComboBox sensor_selector;
        private System.Windows.Forms.TabPage accel_tab;
        private System.Windows.Forms.ListBox collectionlist;
        private System.Windows.Forms.Button updatelistbutton;
        private System.Windows.Forms.RichTextBox collectionStatus;
        private System.Windows.Forms.TabPage redtemp_tab;
        private System.Windows.Forms.TabPage yellowtemp_tab;
        private System.Windows.Forms.TabPage bluetemp_tab;
    }
}