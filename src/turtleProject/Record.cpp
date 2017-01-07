#include "Record.h"

Record::Record()
{
	nestID = 0;
}

Record::Record(int nID)
{
  nestID = nID;
}


Record::Record(int nID, int rn, int t, int h, int x, int y, int z)
{
	nestID = nID;
	recordNumber = rn;
	temp = t;
	humidity = h;
	xAcc = x;
	yAcc = y;
	zAcc = z;
}
