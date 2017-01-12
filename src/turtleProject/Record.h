#ifndef __RECORD_H__
#define __RECORD_H__


class Record
{
	private:
		int nestID;  //holds which nest it is in
		unsigned long recordNumber;  //holds which record it is - max: 2^32
    float bottomTemp;
		int xAcc;
		int yAcc;
		int zAcc;

	public:
		Record();
    Record(int nID);
		Record(int nID, int rn, int x, int y, int z);
    int getNestID();
    unsigned long getRecordNumber();
    float getBottomTemp();
    int getXAcc();
    int getYAcc();
    int getZAcc();
    void printToSerial();
};


#endif //__RECORD_H__
