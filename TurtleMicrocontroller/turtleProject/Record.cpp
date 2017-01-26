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


Record::Record(int nID, int bt, int mt, int tt, int x, int y, int z)
{
  nestID = nID;
  bottomTemp = bt;
  middleTemp = mt;
  topTemp = tt;
  xAcc = x;
  yAcc = y;
  zAcc = z;
}


void Record::printToSerial()
{
  Serial.print("NestID: "); 
  Serial.println(this->nestID);
  
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

