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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(poller));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip_settings = new System.Windows.Forms.ToolStripMenuItem();
            this.printToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.printPreviewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.documentationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.createLogsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.terminal_list = new System.Windows.Forms.ListBox();
            this.sensor_selector = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.dateTimepicker = new System.Windows.Forms.DateTimePicker();
            this.data_tabControl = new System.Windows.Forms.TabControl();
            this.gen_tab = new System.Windows.Forms.TabPage();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.accel_tab = new System.Windows.Forms.TabPage();
            this.redtemp_tab = new System.Windows.Forms.TabPage();
            this.yellowtemp_tab = new System.Windows.Forms.TabPage();
            this.bluetemp_tab = new System.Windows.Forms.TabPage();
            this.collectionlist = new System.Windows.Forms.ListBox();
            this.updatelistbutton = new System.Windows.Forms.Button();
            this.collectionStatus = new System.Windows.Forms.RichTextBox();
            this.SD_ImportButton = new System.Windows.Forms.Button();
            this.dataBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripProgressBar1 = new System.Windows.Forms.ToolStripProgressBar();
            this.logdataBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.menuStrip1.SuspendLayout();
            this.data_tabControl.SuspendLayout();
            this.gen_tab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            resources.ApplyResources(this.menuStrip1, "menuStrip1");
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1,
            this.helpToolStripMenuItem});
            this.menuStrip1.Name = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            resources.ApplyResources(this.toolStripMenuItem1, "toolStripMenuItem1");
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStrip_settings,
            this.printToolStripMenuItem,
            this.printPreviewToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            // 
            // toolStrip_settings
            // 
            resources.ApplyResources(this.toolStrip_settings, "toolStrip_settings");
            this.toolStrip_settings.Name = "toolStrip_settings";
            this.toolStrip_settings.Click += new System.EventHandler(this.toolStrip_settings_Click);
            // 
            // printToolStripMenuItem
            // 
            resources.ApplyResources(this.printToolStripMenuItem, "printToolStripMenuItem");
            this.printToolStripMenuItem.Name = "printToolStripMenuItem";
            // 
            // printPreviewToolStripMenuItem
            // 
            resources.ApplyResources(this.printPreviewToolStripMenuItem, "printPreviewToolStripMenuItem");
            this.printPreviewToolStripMenuItem.Name = "printPreviewToolStripMenuItem";
            // 
            // helpToolStripMenuItem
            // 
            resources.ApplyResources(this.helpToolStripMenuItem, "helpToolStripMenuItem");
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.documentationToolStripMenuItem,
            this.aboutToolStripMenuItem,
            this.createLogsToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            // 
            // documentationToolStripMenuItem
            // 
            resources.ApplyResources(this.documentationToolStripMenuItem, "documentationToolStripMenuItem");
            this.documentationToolStripMenuItem.Name = "documentationToolStripMenuItem";
            // 
            // aboutToolStripMenuItem
            // 
            resources.ApplyResources(this.aboutToolStripMenuItem, "aboutToolStripMenuItem");
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // createLogsToolStripMenuItem
            // 
            resources.ApplyResources(this.createLogsToolStripMenuItem, "createLogsToolStripMenuItem");
            this.createLogsToolStripMenuItem.Name = "createLogsToolStripMenuItem";
            this.createLogsToolStripMenuItem.Click += new System.EventHandler(this.createLogsToolStripMenuItem_Click);
            // 
            // terminal_list
            // 
            resources.ApplyResources(this.terminal_list, "terminal_list");
            this.terminal_list.FormattingEnabled = true;
            this.terminal_list.Name = "terminal_list";
            this.terminal_list.SelectedIndexChanged += new System.EventHandler(this.terminal_list_SelectedIndexChanged);
            // 
            // sensor_selector
            // 
            resources.ApplyResources(this.sensor_selector, "sensor_selector");
            this.sensor_selector.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.sensor_selector.FormattingEnabled = true;
            this.sensor_selector.Name = "sensor_selector";
            this.sensor_selector.SelectedIndexChanged += new System.EventHandler(this.sensor_selector_SelectedIndexChanged);
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // dateTimepicker
            // 
            resources.ApplyResources(this.dateTimepicker, "dateTimepicker");
            this.dateTimepicker.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.dateTimepicker.Name = "dateTimepicker";
            this.dateTimepicker.ValueChanged += new System.EventHandler(this.dateTimepicker_ValueChanged);
            // 
            // data_tabControl
            // 
            resources.ApplyResources(this.data_tabControl, "data_tabControl");
            this.data_tabControl.Controls.Add(this.gen_tab);
            this.data_tabControl.Controls.Add(this.accel_tab);
            this.data_tabControl.Controls.Add(this.redtemp_tab);
            this.data_tabControl.Controls.Add(this.yellowtemp_tab);
            this.data_tabControl.Controls.Add(this.bluetemp_tab);
            this.data_tabControl.Name = "data_tabControl";
            this.data_tabControl.SelectedIndex = 0;
            // 
            // gen_tab
            // 
            resources.ApplyResources(this.gen_tab, "gen_tab");
            this.gen_tab.Controls.Add(this.dataGridView1);
            this.gen_tab.Name = "gen_tab";
            this.gen_tab.UseVisualStyleBackColor = true;
            // 
            // dataGridView1
            // 
            resources.ApplyResources(this.dataGridView1, "dataGridView1");
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.AllowUserToResizeColumns = false;
            this.dataGridView1.AllowUserToResizeRows = false;
            this.dataGridView1.BackgroundColor = System.Drawing.Color.White;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.EditMode = System.Windows.Forms.DataGridViewEditMode.EditProgrammatically;
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            // 
            // accel_tab
            // 
            resources.ApplyResources(this.accel_tab, "accel_tab");
            this.accel_tab.Name = "accel_tab";
            this.accel_tab.UseVisualStyleBackColor = true;
            // 
            // redtemp_tab
            // 
            resources.ApplyResources(this.redtemp_tab, "redtemp_tab");
            this.redtemp_tab.Name = "redtemp_tab";
            this.redtemp_tab.UseVisualStyleBackColor = true;
            // 
            // yellowtemp_tab
            // 
            resources.ApplyResources(this.yellowtemp_tab, "yellowtemp_tab");
            this.yellowtemp_tab.Name = "yellowtemp_tab";
            this.yellowtemp_tab.UseVisualStyleBackColor = true;
            // 
            // bluetemp_tab
            // 
            resources.ApplyResources(this.bluetemp_tab, "bluetemp_tab");
            this.bluetemp_tab.Name = "bluetemp_tab";
            this.bluetemp_tab.UseVisualStyleBackColor = true;
            // 
            // collectionlist
            // 
            resources.ApplyResources(this.collectionlist, "collectionlist");
            this.collectionlist.FormattingEnabled = true;
            this.collectionlist.Name = "collectionlist";
            this.collectionlist.SelectedIndexChanged += new System.EventHandler(this.collectionlist_SelectedIndexChanged);
            // 
            // updatelistbutton
            // 
            resources.ApplyResources(this.updatelistbutton, "updatelistbutton");
            this.updatelistbutton.Name = "updatelistbutton";
            this.updatelistbutton.UseVisualStyleBackColor = true;
            this.updatelistbutton.Click += new System.EventHandler(this.updatelistbutton_Click);
            // 
            // collectionStatus
            // 
            resources.ApplyResources(this.collectionStatus, "collectionStatus");
            this.collectionStatus.BackColor = System.Drawing.SystemColors.Window;
            this.collectionStatus.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.collectionStatus.Name = "collectionStatus";
            this.collectionStatus.ReadOnly = true;
            // 
            // SD_ImportButton
            // 
            resources.ApplyResources(this.SD_ImportButton, "SD_ImportButton");
            this.SD_ImportButton.Name = "SD_ImportButton";
            this.SD_ImportButton.UseVisualStyleBackColor = true;
            this.SD_ImportButton.Click += new System.EventHandler(this.SD_ImportButton_Click);
            // 
            // dataBrowserDialog
            // 
            resources.ApplyResources(this.dataBrowserDialog, "dataBrowserDialog");
            // 
            // toolStripStatusLabel1
            // 
            resources.ApplyResources(this.toolStripStatusLabel1, "toolStripStatusLabel1");
            this.toolStripStatusLabel1.BackColor = System.Drawing.SystemColors.Control;
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            // 
            // statusStrip1
            // 
            resources.ApplyResources(this.statusStrip1, "statusStrip1");
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolStripProgressBar1});
            this.statusStrip1.Name = "statusStrip1";
            // 
            // toolStripProgressBar1
            // 
            resources.ApplyResources(this.toolStripProgressBar1, "toolStripProgressBar1");
            this.toolStripProgressBar1.Name = "toolStripProgressBar1";
            // 
            // logdataBrowserDialog
            // 
            resources.ApplyResources(this.logdataBrowserDialog, "logdataBrowserDialog");
            // 
            // poller
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.LightSkyBlue;
            this.Controls.Add(this.SD_ImportButton);
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
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.data_tabControl.ResumeLayout(false);
            this.gen_tab.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }


        private void Poller_FormClosing(object sender, System.Windows.Forms.FormClosingEventArgs e)
        {
            r_engine.Close();
            r_engine.Dispose();
            System.Environment.Exit(0);
        }



        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem toolStrip_settings;
        private System.Windows.Forms.ToolStripMenuItem printToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem printPreviewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem documentationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ListBox terminal_list;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DateTimePicker dateTimepicker;
        private System.Windows.Forms.TabControl data_tabControl;
        private System.Windows.Forms.TabPage gen_tab;
        private System.Windows.Forms.ComboBox sensor_selector;
        private System.Windows.Forms.TabPage accel_tab;
        private System.Windows.Forms.ListBox collectionlist;
        private System.Windows.Forms.Button updatelistbutton;
        private System.Windows.Forms.RichTextBox collectionStatus;
        private System.Windows.Forms.TabPage redtemp_tab;
        private System.Windows.Forms.TabPage yellowtemp_tab;
        private System.Windows.Forms.TabPage bluetemp_tab;
        private System.Windows.Forms.Button SD_ImportButton;
        private System.Windows.Forms.FolderBrowserDialog dataBrowserDialog;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripMenuItem createLogsToolStripMenuItem;
        private System.Windows.Forms.FolderBrowserDialog logdataBrowserDialog;
        private System.Windows.Forms.ToolStripProgressBar toolStripProgressBar1;
    }
}