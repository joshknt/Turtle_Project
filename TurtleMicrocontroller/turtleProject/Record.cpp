#include <Arduino.h>
#include "Record.h"

Record::Record()
{
	nestID = 0;
}


Record::Record(uint8_t nID, uint16_t bt, uint16_t mt, uint16_t tt, int x, int y, int z)
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

