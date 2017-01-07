#ifndef __RECORD_H__
#define __RECORD_H__


class Record
{
	private:
		int nestID;  //holds which nest it is in
		unsigned long recordNumber;  //holds which record it is - max: 2^32
		int temp;
		int humidity;
		int xAcc;
		int yAcc;
		int zAcc;

	public:
		Record();
    Record(int nID);
		Record(int nID, int rn, int t, int h, int x, int y, int z);
};


#endif //__RECORD_H__
