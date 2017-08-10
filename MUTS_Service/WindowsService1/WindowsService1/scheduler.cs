using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.ServiceProcess;
using System.Text;
using System.Timers;
using System.IO.Ports;
using System.Management;


namespace WindowsService1
{
    public partial class scheduler : ServiceBase
    {
        private short RXTIME = 10000; // maximum time to wait between packet transfers. 10 seconds
        private Timer timer1 = null;
        private Timer RxTimer = null;
        private SerialPort portIN = null;
        private string PORTNAME = "COM";
        private string DATADIRECTORY = "E:\\testprograms\\MUTS_Java\\DATA"; // location data will be logged to.
        private List<Library.RecordGroup> sortedRecords = new List<Library.RecordGroup>(); // sorted records are stored here.
        private short recordInterval = 30; // in minutes
        private string dataBuffer;
        public scheduler()
        {
            InitializeComponent();
        }

        private bool openPort()
        {
            try
            {
                if(portIN != null)
                {
                    if (portIN.IsOpen)
                        portIN.Close();//close port so it may be updated.
                }
                portIN = new SerialPort(PORTNAME, 9800, Parity.None, 8, StopBits.One);
                portIN.Open();
                portIN.RtsEnable = true;
                portIN.DtrEnable = true;
                portIN.DataReceived += new SerialDataReceivedEventHandler(_DataIncoming);
                return true;
                
            }
            catch(Exception e) // TODO
            {
                Library.writeErrorLog(e.Message);
                return false;
            }
            
        }

        protected override void OnStart(string[] args)
        {
            
            timer1 = new Timer();
            this.timer1.Interval = 10000; // where 1000 is a second.
            this.timer1.Elapsed += new System.Timers.ElapsedEventHandler(this.timer1_Tick);
            timer1.Enabled = true;

            RxTimer = new Timer();
            this.RxTimer.Interval = RXTIME;
            this.RxTimer.Elapsed += new System.Timers.ElapsedEventHandler(this.timerRX_Tick);
            this.RxTimer.Enabled = false;

            if (checkPort())
            {
                if (openPort())
                {
                    Library.writeErrorLog("Port opened.");
                }
            }
            else
                portIN = new SerialPort();
           
            Library.writeErrorLog("MUTS SERVICES STARTED.");
        }


        private void _DataIncoming(object sender, SerialDataReceivedEventArgs e)
        {
            // set up timer to check for RX timeout //

            if (RxTimer.Enabled == false)
                RxTimer.Enabled = true;

            try
            {


                Library.writeErrorLog("Data was obtained");
                int length = portIN.BytesToRead; // size of obtained packet(s)
                byte[] data = new byte[length]; // raw data buffer

                int nbrDataRead = portIN.Read(data, 0, length); // the number of bytes read is returned by the read function
                if (nbrDataRead == 0)
                    return;
                else
                {
                    Library.writeErrorLog("Data has been read.");
                    dataBuffer += System.Text.Encoding.UTF8.GetString(data, 0, data.Length);
                }

            }
            catch (Exception ex)
            {
                RxTimer.Enabled = false;
                Library.writeErrorLog(ex.Message);
            }
        }



        // *******************************************************************************
        // Timer Tick Function
        // This even occurs at the start of an interval of time defined as timer1.Interval.
        // Perform a check of the COM port here to see if the radio receiver has obtained
        // any new data from the MUTS Terminal.
        // *******************************************************************************
        private void timer1_Tick(object sender, ElapsedEventArgs e)
        {
            //job here
            //The age of the port has become too old, time to check again.
            if (checkPort())
            {
                if(openPort())
                    Library.writeErrorLog("Port opened successfully."); // found port
                else
                {
                    Library.writeErrorLog("Error opening port.");
                }
            }
            else
            {
                Library.writeErrorLog("No wireless USB FTDI Dongle found.");
            }

        }




        // *******************************************************************************
        // RX Timer Tick Function
        // *******************************************************************************
        private void timerRX_Tick(object sender, ElapsedEventArgs e)
        {
            Library.writeErrorLog("RX timer ticked");
            //The transfer must be done.
            DateTime time = new DateTime();
            string file;



            try
            {
                /////////////////////////////////////////////////////
                
                string[] convertedData;

                convertedData = dataBuffer.Split('\n'); // split the buffer into records, delimited by newline
                
                foreach (string record in convertedData)// for each record in a packet is another way to phrase this.
                {
                    try
                    {

                        Library.writeErrorLog(string.Format("Attempting to get board ID and protocol from {0}",record));

                        string[] slice = record.Split(new[] { ',' }, 5); // break record up into five parts so the first four may be extracted.
                        short protocol = System.Convert.ToInt16(slice[0]);
                        int ID = Library.formatBoardID(slice); // obtain boardID, which is the first three values of the record string after protocol.
                        // first, check if an entry for this board and sensor combo exist in the list //
                        string newrecord = string.Format("{0},{1},{2},{3}", slice[1], slice[2], slice[3], slice[4]);
                        Library.searchInsertList(sortedRecords, ID, newrecord,protocol); // store record.
                        Library.writeErrorLog(String.Format("record {0} inserted into list", newrecord));

                    }
                    catch (Exception prex)
                    {
                        Library.writeErrorLog(prex.Message);
                        //bad record
                        //TODO: add handle
                    }

                }

                
                /////////////////////////////////////////////////////

                if (sortedRecords.Count > 0)
                {
                    Library.writeErrorLog(String.Format("Attempting to write record(s) to {0} files",sortedRecords.Count));
                    foreach (Library.RecordGroup group in sortedRecords) 
                    {
                        time = DateTime.Now;
                        switch (group.protocol)
                        {
                            case 1: file = String.Format("{0}\\{1}_{2}.csv", DATADIRECTORY, time.Date.ToString("MMddyyyy"), group.RecordGroupID); break;
                            case 2: file = String.Format("{0}\\S_{1}_{2}.csv", DATADIRECTORY, time.Date.ToString("MMddyyyy"), group.RecordGroupID); break;
                            default: file = String.Format("{0}\\U_{1}_{2}.csv", DATADIRECTORY, time.Date.ToString("MMddyyyy"), group.RecordGroupID); break;

                        }
                        

                        if (!System.IO.File.Exists(file))
                        {
                            System.IO.File.Create(file).Dispose();
                        }
                        using (System.IO.StreamWriter sw = new System.IO.StreamWriter(file, true))
                        {
                            group.records.Reverse(); // set record order from last packet to first packet for timestamping.
                            for(int i = 0; i < group.records.Count; i++)
                            {
                                group.records[i] = string.Format("{0},{1},{2}", time.ToString("hh:mm"), group.records[i], time.ToString("d"));
                                time = time.AddMinutes(-recordInterval);
                            }
                            if(group.protocol != 2)
                                group.records.Reverse(); // sort data from least recent to most recent, unless data is from sand sensors.
                            foreach (string record in group.records)
                            {                         
                                sw.WriteLine(record);
                            }
                            sw.Dispose();
                        }
                    }
                }
                else
                {
                    Library.writeErrorLog("Data transfer timed out.");
                }
            }
            catch(Exception ex)
            {
                Library.writeErrorLog("Error writing to data files.");
                Library.writeErrorLog(ex.Message);

            }
            finally
            {
                RxTimer.Enabled = false;
                dataBuffer = String.Empty;
                sortedRecords.Clear();
            }
            //portIN.Write("404ERR");
        }

        private bool checkPort()
        {
            try {
                //First, find port name//
                ManagementObjectSearcher searcher = new ManagementObjectSearcher(
                @"Select * FROM Win32_PnpEntity WHERE PNPDeviceID LIKE '%FTDIBUS%'");
                foreach (ManagementObject queryobj in searcher.Get())
                {
                    if ((string)queryobj.GetPropertyValue("PNPDeviceID") == "FTDIBUS\\VID_0403+PID_6015+DN02MM8QA\\0000")
                    {
                        PORTNAME = (string)queryobj.GetPropertyValue("Name");
                        int index = 0;
                        for (; index < PORTNAME.Length - 3 && (PORTNAME[index].ToString() + PORTNAME[index + 1] + PORTNAME[index + 2] != "COM"); index++) { }
                        PORTNAME = PORTNAME.Substring(index).TrimEnd(')');
                        Library.writeErrorLog(PORTNAME);
                        return true; // port found and confirmed. Updated PORTNAME.
                    }
                }
            }
            catch
            {
                Library.writeErrorLog("Error on port check.");
                return false;
            }

            return false;
        }
        protected override void OnStop()
        {
            timer1.Enabled = false;
            if(RxTimer != null)
            {
                RxTimer.Enabled = false;
            }
            if(portIN != null)
            {
                if (portIN.IsOpen)
                    portIN.Close();
            }
            Library.writeErrorLog("MUTS Service has stopped.");
        }
    }
}
