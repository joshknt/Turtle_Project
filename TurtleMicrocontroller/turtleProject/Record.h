#ifndef __RECORD_H__
#define __RECORD_H__


class Record
{
	private:
		int nestID;  //holds which nest it is in
    int bottomTemp;
    int middleTemp;
    int topTemp;
		int xAcc;
		int yAcc;
		int zAcc;

	public:
		Record();
    Record(int nID);
    Record(int nID, int bt, int mt, int tt, int x, int y, int z); //use this after DS18B20 is working
    int getNestID();
    int getBottomTemp();
    int getMiddleTemp();
    int getTopTemp();
    int getXAcc();
    int getYAcc();
    int getZAcc();
    void printToSerial();
};


#endif //__RECORD_H__
