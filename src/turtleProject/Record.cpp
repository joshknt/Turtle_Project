#include <Arduino.h>
#include "Record.h"

Record::Record()
{
	nestID = 0;
}

Record::Record(int nID)
{
  nestID = nID;
}


Record::Record(int nID, long rn, int x, int y, int z)
{
	nestID = nID;
	recordNumber = rn;
	xAcc = x;
	yAcc = y;
	zAcc = z;
}

//use this after DB18B20 is working
//Record::Record(int nID, long rn, int bt, int mt, int tt, int x, int y, int z)
//{
//  nestID = nID;
//  recordNumber = rn;
//  bottomTemp = bt;
//  midTemp = mt;
//  topTemp = tt;
//  xAcc = x;
//  yAcc = y;
//  zAcc = z;
//}


int Record::getNestID()
{ 
  return this->nestID;  
}


long Record::getRecordNumber()
{
  return recordNumber;  
}


int Record:: getBottomTemp()
{
  return bottomTemp;
}


int Record::getXAcc()
{
  return xAcc;
}


int Record::getYAcc()
{
  return yAcc;
}


int Record::getZAcc()
{
  return zAcc;
}


void Record::printToSerial()
{
  Serial.print("NestID: "); 
  Serial.println(this->nestID);
  
  Serial.print("Record #: "); 
  Serial.println(this->recordNumber);

  //Serial.print("Bottom Temp: "); 
  //Serial.println(this->bottomTemp);
  
  Serial.print("X: ");
  Serial.print(this->xAcc);
  Serial.print(" Y: ");
  Serial.print(this->yAcc);
  Serial.print(" Z: ");
  Serial.println(this->zAcc);
}

