/***********************************************************************************
 * Data Driver.
 * Description: Frontend code for managing the Data in a way that allows it to be 
 * displayed graphically.
 * Author: Derek Brown
 * 
 * Changelog:
 * 1/8/17 - Program origin. Laid groundwork for frontend design
 * 1/9/17 - Added R functionality
 * 1/11/17 - Cleaned up code
 * 1/22/17 - Updated data tabs to include support for three temperature probes.
 *          TODO: fix aspect ratio of tab control to force 1:1
 *          TODO: add ability to refine graph image based on a set increment of time.
 *          TODO: add ability to zoom in, and right click to save images to a chosen directory.
 *          TODO: add appropriate color to red, yellow, and blue lines in graphs.
 *          TODO: fix temperature tab.
 *          TODO: fix sensor/terminal choosing bugs.
 * ********************************************************************************/

using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using RDotNet;
using RDotNet.NativeLibrary;

namespace WindowsFormsApplication1
{
    public partial class poller : Form
    {
        TurtleDesktop.Properties.Settings settings = new TurtleDesktop.Properties.Settings();
        protected bool sensorSelected = false; // determines if the user has selected a sensor.
        REngine r_engine;
        public poller()
        {
            InitializeComponent();

            // Initialize R //
            var envPath = Environment.GetEnvironmentVariable("PATH"); // prepare R environment
            Environment.SetEnvironmentVariable("PATH", envPath + Path.PathSeparator + settings.rBinPath);
            r_engine = REngine.CreateInstance("RDotNet", settings.rBinPath + "\\R.DLL");
            r_engine.Initialize();
        }

        private void gen_button_Click(object sender, EventArgs e)
        {
            generateGraphics();
        }

        string generatefilePath(string terminalID, string sensorID, string date, string collection)
        {
            // string path = settings.DataPath + "/" + terminalID + "/" + sensorID + "/" + date + "_" + terminalID + sensorID + "/";
            string path = convertPath(settings.DataPath) + "/" + terminalID + "/" + sensorID + "/" + date + "_" + terminalID + sensorID + "/";
            return path;
        }

        private void populateTerminals()
        {
            settings.Reload();
            string path = settings.DataPath + "/";
            terminal_list.Items.Clear();
            for (int i = 0; i < settings.maxTerminals; i++)
            {
                string termnum = i.ToString();
                if (i < 10)
                    termnum = "00" + i.ToString();
                else if(i < 100)
                    termnum = "0" + i.ToString();
                if (Directory.Exists(path + settings.countryCode + termnum))
                {
                    terminal_list.Items.Add(settings.countryCode + termnum); // Add terminal, if directory file was discovered.
                }
            }
            if (terminal_list.Items.Count != 0)
            {
                terminal_list.Text = "No terminal found. Sync terminal units or check data location under settings.";
            }
        }

        private void populateSensors()
        {
            sensorSelected = false;
            string path = settings.DataPath + "/";
            sensor_selector.Items.Clear();
            for (int i = 0; i < settings.maxSensors; i++)
            {
                string sensnum = i.ToString();
                if (i < 10)
                    sensnum = "0" + i.ToString();
                if (Directory.Exists(path + (string)terminal_list.SelectedItem + "/" + sensnum))
                {
                    sensor_selector.Items.Add(sensnum); // Add terminal, if directory file was discovered.
                }
            }
        }

        private void populateCollections()
        {
            string date = dateTimepicker.Value.ToString("MM") + "-" + dateTimepicker.Value.Day.ToString() + "-" + dateTimepicker.Value.Year.ToString()[2] + dateTimepicker.Value.Year.ToString()[3];
            string path = settings.DataPath + "/" + (string)terminal_list.SelectedItem + "/" + (string)(sensor_selector.SelectedItem) + "/" + date + "_" + (string)terminal_list.SelectedItem + (string)(sensor_selector.SelectedItem);
            if (Directory.Exists(path))
            {
                collectionlist.Items.Clear();
                for (int i = 0; i < settings.maxCollections; i++)
                {
                    string sensnum = i.ToString();
                    if (i < 10)
                        sensnum = "0" + i.ToString();
                    if (File.Exists(path + "/" + i.ToString() + "-" + (string)terminal_list.SelectedItem + (string)(sensor_selector.Text) + ".csv"))
                    {
                        collectionlist.Items.Add(i.ToString() + "-" + (string)terminal_list.SelectedItem + (string)(sensor_selector.Text));
                    }
                }
            }
            if (collectionlist.Items.Count == 0)
            {
                collectionStatus.Visible = true;
                collectionStatus.Enabled = true;
                collectionlist.Enabled = false;
                
                collectionStatus.Text = (sensorSelected) ? "No data found for selected parameters." : "Select a sensor to search data collections.";
            }
            else
            {
                collectionStatus.Visible = false;
                collectionStatus.Enabled = false;
                collectionlist.Enabled = true;

            }
        }

        private void generateGraphics()
        {
            string terminal = (string)terminal_list.SelectedItem;
            string sensor = (string)sensor_selector.SelectedItem;
            string date = dateTimepicker.Value.ToString("MM") + "-" + dateTimepicker.Value.Day.ToString() + "-" + dateTimepicker.Value.Year.ToString()[2] + dateTimepicker.Value.Year.ToString()[3];
            string collection = (string)collectionlist.SelectedItem;
            string path = generatefilePath(terminal, sensor, date, collection); // path to save plots to

            try
            {
                // Find file and times of collection samples:
                string collectionLocation = path + collection + ".csv";
                r_engine.Evaluate("timeVec <- read.table(\"" + collectionLocation + "\", sep = ',', header = TRUE)$TIMESTAMPTIME");
                var timeVec = r_engine.GetSymbol("timeVec");

                // Temperature Red:
                NumericVector tempredVec = r_engine.Evaluate("tempredVec <- read.table('" + collectionLocation + "', sep = ',', header = TRUE)$TEMPRED").AsNumeric();
                r_engine.Evaluate("png('" + path + collection + "/tempred.png', width = 720, height = 580)"); // prepare temperature graph
                r_engine.Evaluate("plot(tempredVec, xlab = 'Time', ylab = 'Temperature', main = 'Temperature Changes for Nest " + terminal + sensor + "', xaxt = 'n')"); // generate base graph
                r_engine.Evaluate("axis(1, at = timeVec, labels = timeVec, las = 1)");
                r_engine.Evaluate("dev.off()"); // complete plot
                redtemp_tab.BackgroundImage = Image.FromFile(path + collection + "/tempred.png");

                // Temperature Yellow:
                NumericVector tempyellowVec = r_engine.Evaluate("tempyellowVec <- read.table('" + collectionLocation + "', sep = ',', header = TRUE)$TEMPYELLOW").AsNumeric();
                r_engine.Evaluate("png('" + path + collection + "/tempyellow.png', width = 720, height = 580)"); // prepare temperature graph
                r_engine.Evaluate("plot(tempyellowVec, xlab = 'Time', ylab = 'Temperature', main = 'Temperature Changes for Nest " + terminal + sensor + "', xaxt = 'n')"); // generate base graph
                r_engine.Evaluate("axis(1, at = timeVec, labels = timeVec, las = 1)");
                r_engine.Evaluate("dev.off()"); // complete plot
                yellowtemp_tab.BackgroundImage = Image.FromFile(path + collection + "/tempyellow.png");

                // Temperature Blue:
                NumericVector tempblueVec = r_engine.Evaluate("tempblueVec <- read.table('" + collectionLocation + "', sep = ',', header = TRUE)$TEMPBLUE").AsNumeric();
                r_engine.Evaluate("png('" + path + collection + "/tempblue.png', width = 720, height = 580)"); // prepare temperature graph
                r_engine.Evaluate("plot(tempblueVec, xlab = 'Time', ylab = 'Temperature', main = 'Temperature Changes for Nest " + terminal + sensor + "', xaxt = 'n')"); // generate base graph
                r_engine.Evaluate("axis(1, at = timeVec, labels = timeVec, las = 1)");
                r_engine.Evaluate("dev.off()"); // complete plot
                bluetemp_tab.BackgroundImage = Image.FromFile(path + collection + "/tempblue.png");

                //General Tab
                DataFrame df = r_engine.Evaluate("read.table('" + collectionLocation + "', sep = ',', header = TRUE)[,5:10]").AsDataFrame();
                for (int i = 0; i < df.ColumnCount; ++i)
                {
                    dataGridView1.ColumnCount++;
                    dataGridView1.Columns[i].Name = df.ColumnNames[i];
                }
                for (int i = 0; i < df.RowCount; ++i)
                {
                    dataGridView1.RowCount++;
                    dataGridView1.Rows[i].HeaderCell.Value = df.RowNames[i];
                    for (int k = 0; k < df.ColumnCount; ++k)
                    {
                        dataGridView1[k, i].Value = df[i, k];
                    }
                }

                // Acceleration:
                NumericVector XACCEL = r_engine.Evaluate("XACCEL <- read.table('" + collectionLocation + "', sep = ',', header = TRUE)$X").AsNumeric();
                NumericVector YACCEL = r_engine.Evaluate("YACCEL <- read.table('" + collectionLocation + "', sep = ',', header = TRUE)$Y").AsNumeric();
                NumericVector ZACCEL = r_engine.Evaluate("ZACCEL <- read.table('" + collectionLocation + "', sep = ',', header = TRUE)$Z").AsNumeric();
                r_engine.Evaluate("png('" + path + collection + "/motion.png', width = 720, height = 580)"); // prepare temperature graph
                r_engine.Evaluate("plot(XACCEL, type = 'o', col = 'blue', ylim = c(100,500), xlab = 'Time', ylab = 'Motion', main = 'Motion Data for Nest " + terminal + sensor + "', xaxt = 'n')"); // generate base graph
                r_engine.Evaluate("lines(YACCEL, type='o', pch=22, lty=2, col='red')");
                r_engine.Evaluate("lines(ZACCEL, type='o', pch=22, lty=2, col='green')");
                r_engine.Evaluate("axis(1, at = timeVec, labels = timeVec, las = 1)");
                r_engine.Evaluate("legend(1, 150, c('X-Axis','Y-Axis', 'Z-Axis'), cex=0.8, col = c('blue', 'red', 'green'), pch = 21:22, lty = 1:3)"); // add legend
                r_engine.Evaluate("dev.off()"); // complete plot
                accel_tab.BackgroundImage = Image.FromFile(path + collection + "/motion.png");


            }
            catch{ } // todo: catch exceptions for errors

            
        }

        private void updatelistbutton_Click(object sender, EventArgs e)
        {
            populateTerminals();
        }

        private void terminal_list_SelectedIndexChanged(object sender, EventArgs e)
        {
            sensor_selector.Enabled = true;
            collectionlist.Items.Clear(); // remove items until sensor chosen.
            sensor_selector.Items.Clear();
            populateSensors();
            sensorSelected = false;
        }

        private void sensor_selector_SelectedIndexChanged(object sender, EventArgs e)
        {
            sensorSelected = true;
            populateCollections();
            
            
        }

        private void collectionlist_SelectedIndexChanged(object sender, EventArgs e)
        {
            generateGraphics();

        }

        private void dateTimepicker_ValueChanged(object sender, EventArgs e)
        {
            collectionlist.Items.Clear(); // prepare to update collections.
            populateCollections();

        }

        private void toolStrip_settings_Click(object sender, EventArgs e)
        {
            TurtleDesktop.SettingsForm setform = new TurtleDesktop.SettingsForm();
            setform.Show();
            setform.Focus();
        }

        private void SD_ImportButton_Click(object sender, EventArgs e)
        {
            string orgPath = settings.DataPath;
            string rawfilename = (string.Empty);
            List<string> filenames = new List<string>();
            StringBuilder sb = new StringBuilder();
            dataBrowserDialog.ShowDialog();
            string SDpath = dataBrowserDialog.SelectedPath;
            try
            {
                // First, get sensor filenames //
                for(int i = 0; i < settings.filenames.Length; i++)
                {
                
                    if(settings.filenames[i] != ',')
                    {
                        sb.Append(settings.filenames[i]);
                    }
                    else
                    {
                        filenames.Add(sb.ToString());
                        sb.Clear();
                    }
                }
                Directory.CreateDirectory(settings.DataPath); //DATA directory if it don't exist already.
                string filepath = orgPath;
                string time = dateTimepicker.Value.ToString("MM") + "-" + dateTimepicker.Value.Day.ToString() + "-" + dateTimepicker.Value.Year.ToString()[2] + dateTimepicker.Value.Year.ToString()[3]; // take time of reading
                if (Directory.Exists(SDpath + "\\"))
                {
                    foreach (string fn in filenames)
                    {
                        if (File.Exists(SDpath + "\\" + fn)) // initial move from sd card for data integrity.  
                        {
                        
                            filepath = orgPath + "\\" + getBoardID(SDpath + "\\" + fn, true) + "\\" + getSensorID(getBoardID(SDpath + "\\" + fn)) + "\\" + time + "_" + getBoardID(SDpath + "\\" + fn) + "\\";
                            Directory.CreateDirectory(filepath);
                            for(int i = 0; i < settings.maxCollections; i++)
                            {
                                rawfilename = i.ToString() + "-" + getBoardID(SDpath + "\\" + fn);
                                if (!File.Exists(filepath + rawfilename + ".csv"))
                                {
                                    break;
                                }
                            }
                            System.IO.File.Move(SDpath + "\\" + fn, filepath + rawfilename + ".temp");
                            Directory.CreateDirectory(filepath + "\\" + rawfilename );
                        }
                        organizeFile(filepath + rawfilename);
                    }
                }
            }
            catch
            {
               
            }

        }
        string getSensorID(string boardID)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append(boardID[6]);
            sb.Append(boardID[7]);
            return(sb.ToString());
        }

        string getBoardID(string filepath, bool term = false)
        {
            StringBuilder sb = new StringBuilder();
            StreamReader file = new StreamReader(filepath);
            file.ReadLine(); // remove header
            int count = (term) ? 2 : 3; // if term is true, just read to the termial id, omitting the sensor id.
            for(int i = 0; i < count; i++) // get board id
            {
                while (file.Peek() != ',') 
                {
                    sb.Append((char)file.Read());
                }
                file.Read(); // consume ','
            }
            file.Close();

            return sb.ToString();
        }

        string convertPath(string path)
        {
            StringBuilder sb = new StringBuilder();
            for(int i = 0; i < path.Length; i++)
            {
                if (path[i] == '/')
                    sb.Append('\\');
                else if (path[i] == '\\')
                    sb.Append('/');
                else
                    sb.Append(path[i]);
            }
            return sb.ToString();
        }

        void organizeFile(string datafile)
        {
            StreamReader fileread = new StreamReader(datafile + ".temp");
            StreamWriter filewrite = new StreamWriter(datafile + ".csv");
            int interval = 3; // number of minutes between each measurement
            //   DateTime importtime = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day, DateTime.Now.Hour, DateTime.Now.Minute, DateTime.Now.Second);
            DateTime importtime = DateTime.Now;
            Stack<string> times = new Stack<string>();
            filewrite.WriteLine("COUNTRY, TERMINAL, SENSOR, RECORDNUMBER,TEMPRED,TEMPYELLOW,TEMPBLUE, X, Y, Z, TIMESTAMPDATE, TIMESTAMPTIME"); // append header

            /* Data is written from oldest to newest. Need to read entire file once to build time stack */
            while (!fileread.EndOfStream)
            {
                // hour and minute variables represent point of file import
                times.Push("," + importtime.Month.ToString() + "-" + importtime.Day.ToString() + "-" + importtime.Year.ToString() + ',' + importtime.ToString("HH:mm"));
                importtime = importtime.AddMinutes(- interval); // step back
                fileread.ReadLine(); // consume line
            }
            fileread.Close();
            fileread = new StreamReader(datafile + ".temp"); // reopen file to reset file pointer

            
            while (!fileread.EndOfStream && times.Count > 0)
            {
                filewrite.WriteLine(fileread.ReadLine() + times.Pop());
            }
            fileread.Close();
            filewrite.Close();
            File.Delete(datafile + ".temp");
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        
    }
}

