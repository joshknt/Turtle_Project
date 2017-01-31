#ifndef __RECORD_H__
#define __RECORD_H__


class Record
{
	private:
		uint8_t nestID;  //holds which nest it is in
    uint16_t bottomTemp;
    uint16_t middleTemp;
    uint16_t topTemp;
		int xAcc;
		int yAcc;
		int zAcc;

	public:
		Record();
    Record(uint8_t nID, uint16_t bt, uint16_t mt, uint16_t tt, int x, int y, int z); //use this after DS18B20 is working
    uint8_t getNestID() {return this->nestID;}
    uint16_t getBottomTemp() {return this->bottomTemp;}
    uint16_t getMiddleTemp() {return this->middleTemp;}
    uint16_t getTopTemp() {return this->topTemp;}
    int getXAcc() {return this->xAcc;}
    int getYAcc() {return this->yAcc;}
    int getZAcc() {return this->zAcc;}
    void printToSerial();
};


#endif //__RECORD_H__
