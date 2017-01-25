using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TurtleDesktop
{
    public partial class SettingsForm : Form
    {
        TurtleDesktop.Properties.Settings settings = new Properties.Settings();
        public SettingsForm()
        {
            InitializeComponent();
            settings.Reload();
            if(settings.rBinPath.Length > 0)
            {
                RFolderTextBox.Text = settings.rBinPath;
            }
            if (settings.DataPath.Length > 0)
            {
                DataFolderTextBox.Text = settings.DataPath;
            }
        }

        private void Help_R_Button_Click(object sender, EventArgs e)
        {
            MessageBox.Show("A 32-bit distribution of the R language must be installed on this computer to generate graphs. Once installed, the folder containing the bin should be R\\R-X.X.X\\bin\\i386", "R-Help", MessageBoxButtons.OK,MessageBoxIcon.Information,MessageBoxDefaultButton.Button1);
        }

        private void Help_Data_Button_Click(object sender, EventArgs e)
        {
            MessageBox.Show("This folder will be the location which both raw and organized data will be stored. It should be an empty folder, with any name.", "Data-Help", MessageBoxButtons.OK, MessageBoxIcon.Information, MessageBoxDefaultButton.Button1);
        }

        private void Browse_button_Click(object sender, EventArgs e)
        {
            folderBrowserDialog1.ShowDialog();
            RFolderTextBox.Text = folderBrowserDialog1.SelectedPath;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            folderBrowserDialog1.ShowDialog();
            DataFolderTextBox.Text = folderBrowserDialog1.SelectedPath;
        }

        private void saveButton_Click(object sender, EventArgs e)
        {
            settings.rBinPath = RFolderTextBox.Text;
            StringBuilder datapathsb = new StringBuilder();
            for(int i = 0; i < DataFolderTextBox.Text.Length; i++)
            {
                if (DataFolderTextBox.Text[i] == '\\')
                    datapathsb.Append('/');
                else
                    datapathsb.Append(DataFolderTextBox.Text[i]);
            }
            settings.DataPath = datapathsb.ToString();
            settings.Save();
        }
    }
}
