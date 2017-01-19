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



Record::Record(int nID, long rn, int bt, int mt, int tt, int x, int y, int z)
{
  nestID = nID;
  recordNumber = rn;
  bottomTemp = bt;
  middleTemp = mt;
  topTemp = tt;
  xAcc = x;
  yAcc = y;
  zAcc = z;
}


int Record::getNestID()
{ 
  return this->nestID;  
}


long Record::getRecordNumber()
{
  return recordNumber;  
}


int Record::getBottomTemp()
{
  return bottomTemp;
}


int Record::getMiddleTemp()
{
  return middleTemp;
}


int Record::getTopTemp()
{
  return topTemp;
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

  Serial.print("Bottom Temp: "); 
  Serial.println(this->bottomTemp);

  Serial.print("Middle Temp: ");
  Serial.println(this->middleTemp);

  Serial.print("Top Temp: ");
  Serial.println(this->topTemp);
  
  Serial.print("X: ");
  Serial.print(this->xAcc);
  Serial.print(" Y: ");
  Serial.print(this->yAcc);
  Serial.print(" Z: ");
  Serial.println(this->zAcc);

  Serial.println();
  Serial.println();
}

