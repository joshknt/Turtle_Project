﻿/***********************************************************************************
 * Data Driver.
 * Description: Frontend code for managing the Data in a way that allows it to be 
 * displayed graphically.
 * Author: Derek Brown
 * 
 * Changelog:
 * 1/8/17 - Program origin. Laid groundwork for frontend design
 * 1/9/17 - Added R functionality
 * 1/11/17 - Cleaned up code
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
        public Settings settings = new Settings(); // initialize the settings
        protected bool sensorSelected = false; // determines if the user has selected a sensor.

        public poller()
        {
            InitializeComponent();
        }

        private void gen_button_Click(object sender, EventArgs e)
        {
            generateGraphics();
        }

        string generatefilePath(string terminalID, string sensorID, string date, string collection)
        {
            string path = settings.orgDataPath + terminalID + "/"+ sensorID + "/" + date + "_" +  terminalID+sensorID + "/";
            return path;
        }

        private void populateTerminals()
        {
            string path = settings.orgDataPath;
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
            string path = settings.orgDataPath;
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
            string date = dateTimepicker.Value.Month.ToString() + "-" + dateTimepicker.Value.Day.ToString() + "-" + dateTimepicker.Value.Year.ToString()[2] + dateTimepicker.Value.Year.ToString()[3];
            string path = settings.orgDataPath + (string)terminal_list.SelectedItem + "/" + (string)(sensor_selector.SelectedItem) + "/" + date + "_" + (string)terminal_list.SelectedItem + (string)(sensor_selector.SelectedItem);
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
            string date = dateTimepicker.Value.Month.ToString() + "-" + dateTimepicker.Value.Day.ToString() + "-" + dateTimepicker.Value.Year.ToString()[2] + dateTimepicker.Value.Year.ToString()[3];
            string collection = (string)collectionlist.SelectedItem;
            string path = generatefilePath(terminal, sensor, date, collection); // path to save plots to

            var envPath = Environment.GetEnvironmentVariable("PATH"); // prepare R environment
            Environment.SetEnvironmentVariable("PATH", envPath + Path.PathSeparator + settings.rBinPath);
            REngine r_engine = REngine.CreateInstance("RDotNet", settings.rBinPath + "\\R.DLL");
            r_engine.Initialize();

            try
            {
                // Find file and times of collection samples:
                //string collectionLocation = path + collection + "-" + terminal + sensor + ".csv";
                string collectionLocation = path + collection + ".csv";
                r_engine.Evaluate("timeVec <- read.table(\"" + collectionLocation + "\", sep = ',', header = TRUE)$TIMESTAMPTIME");
                var timeVec = r_engine.GetSymbol("timeVec");

                // Temperature:
                NumericVector temperatureVec = r_engine.Evaluate("temperatureVec <- read.table('" + collectionLocation + "', sep = ',', header = TRUE)$TEMPERATURE").AsNumeric();
                r_engine.Evaluate("png('" + path + collection + "/temp.png, width = 720, height = 580')"); // prepare temperature graph
                r_engine.Evaluate("plot(temperatureVec, xlab = 'Time', ylab = 'Temperature', main = 'Temperature Changes for Nest " + terminal + sensor + "', xaxt = 'n')"); // generate base graph
                r_engine.Evaluate("axis(1, at = timeVec, labels = timeVec, las = 1)");
                r_engine.Evaluate("dev.off()"); // complete plot
                temp_tab.BackgroundImage = Image.FromFile(path + collection + "/temp.png");

                // Humidity:
                NumericVector humidityVec = r_engine.Evaluate("humidityVec <- read.table('" + collectionLocation + "', sep = ',', header = TRUE)$HUMIDITY").AsNumeric();
                r_engine.Evaluate("png('" + path + collection + "/humid.png, width = 720, height = 580')"); // prepare temperature graph
                r_engine.Evaluate("plot(humidityVec, xlab = 'Time', ylab = 'Humidity', main = 'Humidity Changes for Nest " + terminal + sensor + "', xaxt = 'n')"); // generate base graph
                r_engine.Evaluate("axis(1, at = timeVec, labels = timeVec, las = 1)");
                r_engine.Evaluate("dev.off()"); // complete plot
                humidity_tab.BackgroundImage = Image.FromFile(path + collection + "/humid.png");

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
            catch{ } // throw out exceptions for missing file errors
            r_engine.Close();
            r_engine.Dispose();
        }

        private void updatelistbutton_Click(object sender, EventArgs e)
        {
            populateTerminals();
        }

        private void terminal_list_SelectedIndexChanged(object sender, EventArgs e)
        {
            sensor_selector.Enabled = true;
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
    }
}