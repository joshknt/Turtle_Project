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
    int getBottomTemp() {return this->bottomTemp;}
    int getMiddleTemp() {return this->middleTemp;}
    int getTopTemp() {return this->topTemp;}
    int getXAcc() {return this->xAcc;}
    int getYAcc() {return this->yAcc;}
    int getZAcc() {return this->zAcc;}
    void printToSerial();
};


#endif //__RECORD_H__
