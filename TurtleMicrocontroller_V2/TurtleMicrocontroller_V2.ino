/* Originating Author:
 *    Josh Kent 
 *    
 *  Contributing Authors:  
 *    <N/A>
 *  
 * Description:
 *    
 * 
 * Notes:
 *    This implementation is for the Arduino Mega (ATmega2560 processor). 
 *    
 * SPI_INTERFACE:
 *    Arduino Uno:
 *      MISO/SDO: 12
 *      MOSI/SDA: 11  
 *      CLK: 13
 *      SS: 10
 *
 *    Arduino Mega:
 *      MISO/SDO: 50
 *      MOSI/SDA: 51
 *      CLK: 52
 *      SS: 53
 * 
 * License:
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 * 
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 * 
 *    For a copy of the GNU General Public License, please visit
 *    <http://www.gnu.org/licenses/>.
 */

#include "Nest.h"
#include "TempArray.h"
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

#include <Wire.h>

//************************************************************************
//########################################################################
//************************************************************************


  // Constants:
  #define COUNTRY_CODE    108
  #define BOARD_ID        02
  #define MAX_RECORDS     10
  
  // Temp Arrays
  #define TEMP_ARRAY_ONE_BOTTOM_PIN   02
  #define TEMP_ARRAY_ONE_MIDDLE_PIN   03
  #define TEMP_ARRAY_ONE_TOP_PIN      04
  #define TEMP_ARRAY_TWO_BOTTOM_PIN   05 
  #define TEMP_ARRAY_TWO_MIDDLE_PIN   06
  #define TEMP_ARRAY_TWO_TOP_PIN      07
  
  // Nest DHT22 Sensors (Temperature/Humidty)
  #define NEST_ONE_DHT_PIN      40   
  #define NEST_TWO_DHT_PIN      41
  #define NEST_THREE_DHT_PIN    42
  
  // Nest ADXL345 Sensors (Gyroscope/Accelerometer)
  #define NEST_ONE_ADXL_PIN     53
  #define NEST_TWO_ADXL_PIN     23  
  #define NEST_THREE_ADXL_PIN   24
  
  // End Constants


//************************************************************************
//########################################################################
//************************************************************************


  // Global Variables:
  SoftwareSerial  xbee(2, 3); 
  
  TempArray  tempArrayOne;
  TempArray  tempArrayTwo;
  
  Nest       nestOne(1);
  Nest       nestTwo(2);
  Nest       nestThree(3);
  Nest       nestFour(4);
  Nest       nestFive(5);

  float      offset[5][3];  // [Nest#][X(Y,Z)] Initial nest offset to zero values

  char       *tempArrayString;
  char       *nestString;
  // End Global Variables


//************************************************************************
//########################################################################
//************************************************************************


  // Nest Initialization:

  OneWire           tempArrayOneBottomWire(TEMP_ARRAY_ONE_BOTTOM_PIN);
  OneWire           tempArrayOneMiddleWire(TEMP_ARRAY_ONE_MIDDLE_PIN);
  OneWire           tempArrayOneTopWire(TEMP_ARRAY_ONE_TOP_PIN);
  OneWire           tempArrayTwoBottomWire(TEMP_ARRAY_TWO_BOTTOM_PIN);
  OneWire           tempArrayTwoMiddleWire(TEMP_ARRAY_TWO_MIDDLE_PIN);
  OneWire           tempArrayTwoTopWire(TEMP_ARRAY_TWO_TOP_PIN);
  
  DallasTemperature tempArrayOneBottom(&tempArrayOneBottomWire);
  DallasTemperature tempArrayOneMiddle(&tempArrayOneMiddleWire);
  DallasTemperature tempArrayOneTop(&tempArrayOneTopWire);
  DallasTemperature tempArrayTwoBottom(&tempArrayTwoBottomWire);
  DallasTemperature tempArrayTwoMiddle(&tempArrayTwoMiddleWire);
  DallasTemperature tempArrayTwoTop(&tempArrayTwoTopWire);

  // End Nest Initialization

void SetNestOnePin()
{
  
}

void SetNestTwoPin()
{

}

void SetNestThreePin()
{
  
}

void SetNestFourPin()
{
  
}

void SetNestFivePin()
{
  
}

//************************************************************************
//########################################################################
//************************************************************************
/*
 * Name:
 * 
 * Description:
 * 
 * Inputs:
 * 
 * Outputs:
 * 
 * Return:
 * 
 * Notes: 
 */

void InitializeTempSensors()
{
  tempArrayOneBottom.begin();
  tempArrayOneMiddle.begin();
  tempArrayOneTop.begin();

  tempArrayTwoBottom.begin();
  tempArrayTwoMiddle.begin();
  tempArrayTwoTop.begin();
}


//************************************************************************
//########################################################################
//************************************************************************
/*
 * Name:        GetArrayTemps
 * 
 * Description: This function gets the temperatures of the DS18B20
 *                temperature sensors and stores them into their 
 *                respective objects.
 * 
 * Inputs:      t1 - A TempArray object 
 *              t2 - A TempArray object
 * 
 * Outputs:     Two TempArray objects with current temperature readings.
 * 
 * Return:      None.
 * 
 * Notes:       None.
 * 
 */

void GetArrayTemps(TempArray &t1, TempArray &t2)
{
  RequestTemperatures();
  delay(200);
  
  t1.SetBottomTemp(100 * tempArrayOneBottom.getTempCByIndex(0));;
  t1.SetMiddleTemp(100 * tempArrayOneMiddle.getTempCByIndex(0));
  t1.SetTopTemp(100 * tempArrayOneTop.getTempCByIndex(0));
  
  t2.SetBottomTemp(100 * tempArrayTwoBottom.getTempCByIndex(0));
  t2.SetMiddleTemp(100 * tempArrayTwoMiddle.getTempCByIndex(0));
  t2.SetTopTemp(100 * tempArrayTwoTop.getTempCByIndex(0));
}


//************************************************************************
//########################################################################
//************************************************************************
/*
 * Name:        
 * 
 * Description: 
 * 
 * Inputs:      None. 
 * 
 * Outputs:     None.
 * 
 * Return:      None.
 * 
 * Notes:       This function will 0.6 seconds to complete. The DS18B20 
 *                sensors need some time to retrieve the data. Since the 
 *                readings do not require hard-time responsiveness, this
 *                is okay.
 * 
 */

 void RequestTemperatures()
 {
  tempArrayOneBottom.requestTemperatures();
  delay(100);
  tempArrayOneMiddle.requestTemperatures();
  delay(100);
  tempArrayOneTop.requestTemperatures();
  delay(100);
  
  tempArrayTwoBottom.requestTemperatures();
  delay(100);
  tempArrayTwoMiddle.requestTemperatures();
  delay(100);
  tempArrayTwoTop.requestTemperatures();
  delay(100);
 }

 
//************************************************************************
//########################################################################
//************************************************************************
/*
 * Name:
 * 
 * Description:
 * 
 * Inputs:
 * 
 * Outputs:
 * 
 * Return:
 * 
 * Notes:
 * 
 */

void setup() 
{
  Serial.begin(115200);

  // Setup DS18B20 Support
  InitializeTempSensors();
   
  
  xbee.begin(9600);

}


//************************************************************************
//########################################################################
//************************************************************************
/*
 * Name:
 * 
 * Description:
 * 
 * Inputs:
 * 
 * Outputs:
 * 
 * Return:
 * 
 * Notes:
 * 
 */

void loop() 
{
  //xbee.write("string");
  GetArrayTemps(tempArrayOne, tempArrayTwo); 

  tempArrayString = tempArrayOne.ToString();
  nestString = nestOne.ToString();

  Serial.print("Temp One: ");
  Serial.print(tempArrayOne.GetBottomTemp()); Serial.print(" ");
  Serial.print(tempArrayOne.GetMiddleTemp()); Serial.print(" ");
  Serial.println(tempArrayOne.GetTopTemp());

  Serial.print("Temp Two: ");
  Serial.print(tempArrayTwo.GetBottomTemp()); Serial.print(" ");
  Serial.print(tempArrayTwo.GetMiddleTemp()); Serial.print(" ");
  Serial.println(tempArrayTwo.GetTopTemp()); Serial.println();

  

  delay(200);
}




