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


Record::Record(int nID, int rn, int x, int y, int z)
{
	nestID = nID;
	recordNumber = rn;
	xAcc = x;
	yAcc = y;
	zAcc = z;
}

int Record::getNestID()
{ 
  return nestID;  
}


unsigned long Record::getRecordNumber()
{
  return recordNumber;  
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
  
  Serial.print("X: ");
  Serial.print(this->xAcc);
  Serial.print(" Y: ");
  Serial.print(this->yAcc);
  Serial.print(" Z: ");
  Serial.println(this->zAcc);
}

