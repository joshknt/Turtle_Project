using System;
using System.Collections.Generic;
using System.Text;

namespace WindowsService1
{
    public static class Library
    {
        public static void writeErrorLog(Exception ex)
        {
            System.IO.StreamWriter stream = null;
            try
            {
                stream = new System.IO.StreamWriter(AppDomain.CurrentDomain.BaseDirectory + "\\Logs.txt", true);
                stream.WriteLine(DateTime.Now.ToString() + ": " + ex.Source.ToString().Trim() + "; " + ex.Message.ToString().Trim());
                stream.Flush();
                stream.Close();
            }
            catch { }
        }

        public static void writeErrorLog(string message)
        {
            System.IO.StreamWriter stream = null;
            try
            {
                stream = new System.IO.StreamWriter(AppDomain.CurrentDomain.BaseDirectory + "\\Logs.txt", true);
                stream.WriteLine(DateTime.Now.ToString() + ": " + message);
                stream.Flush();
                stream.Close();
            }
            catch { }
        }

        public class RecordGroup
        {
            public RecordGroup(int id, string firstRecord, short Protocol) {
                RecordGroupID = id;
                records = new List<string>();
                records.Add(firstRecord);
                protocol = Protocol;
            }
            public int RecordGroupID; // the full board id
            public List<string> records;
            public short protocol;

        }

        public static void searchInsertList(List<RecordGroup> list, int id, string record, short protocol)
        {
            foreach(RecordGroup board in list)
            {
                if(board.RecordGroupID == id && board.protocol == protocol) // if the record has a list it belongs to already
                {
                    board.records.Add(record);
                    return;
                }
            }
            list.Add(new RecordGroup(id, record, protocol)); // a new list is to be created if the record doesn't have a list
                                                    // it belongs to.
        }

        public static int formatBoardID(string[] slice)
        {
            for (int i = 1; i < 4; i++)
            {
                if (slice[i].Length == 1)
                {
                    if (i != 3)
                        slice[i].Insert(0, "00");
                    else
                        slice[i].Insert(0, "0");
                }
                else if (slice[i].Length == 2 && i != 3)
                {
                    slice[i].Insert(0, "0");
                }
            }
            return System.Convert.ToInt32(String.Format("{0}{1}{2}", slice[1], slice[2], slice[3]));
        }
    }
}
