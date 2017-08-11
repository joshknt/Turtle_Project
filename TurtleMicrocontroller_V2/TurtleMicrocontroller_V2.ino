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
#include <SparkFun_ADXL345.h>
#include <stdarg.h>
#include <DHT.h>


//************************************************************************
//########################################################################
//************************************************************************


  // Constants:
  #define COUNTRY_CODE    108
  #define BOARD_ID        02
  #define MAX_RECORDS     10
  #define MAX_LINE        100
  #define DHT_TYPE        DHT22
  
  // Temp Arrays
  #define TEMP_ARRAY_ONE_BOTTOM_PIN   8
  #define TEMP_ARRAY_ONE_MIDDLE_PIN   9
  #define TEMP_ARRAY_ONE_TOP_PIN      10
  #define TEMP_ARRAY_TWO_BOTTOM_PIN   11 
  #define TEMP_ARRAY_TWO_MIDDLE_PIN   12
  #define TEMP_ARRAY_TWO_TOP_PIN      13
  
  // Nest DHT22 Sensors (Temperature/Humidty)
  #define NEST_ONE_DHT_PIN      22   
  #define NEST_TWO_DHT_PIN      23
  #define NEST_THREE_DHT_PIN    24
  #define NEST_FOUR_DHT_PIN     25
  #define NEST_FIVE_DHT_PIN     26
  
  // Nest ADXL345 Sensors (Gyroscope/Accelerometer)
  #define NEST_ONE_ADXL_PIN     40
  #define NEST_TWO_ADXL_PIN     41  
  #define NEST_THREE_ADXL_PIN   42
  #define NEST_FOUR_ADXL_PIN    43
  #define NEST_FIVE_ADXL_PIN    44
  
  // End Constants


//************************************************************************
//########################################################################
//************************************************************************


  // Global Variables:
  SoftwareSerial  xbee(2, 3); 
  
  TempArray  tempArrayOne(1);
  TempArray  tempArrayTwo(2);
  
  Nest       nestOne(1);
  Nest       nestTwo(2);
  Nest       nestThree(3);
  Nest       nestFour(4);
  Nest       nestFive(5);

  ADXL345    adxlOne    = ADXL345(NEST_ONE_ADXL_PIN);
  ADXL345    adxlTwo    = ADXL345(NEST_TWO_ADXL_PIN);
  ADXL345    adxlThree  = ADXL345(NEST_THREE_ADXL_PIN);
  ADXL345    adxlFour   = ADXL345(NEST_FOUR_ADXL_PIN);
  ADXL345    adxlFive   = ADXL345(NEST_FIVE_ADXL_PIN);

  DHT        dhtOne(NEST_ONE_DHT_PIN, DHT_TYPE);
  DHT        dhtTwo(NEST_TWO_DHT_PIN, DHT_TYPE);
  DHT        dhtThree(NEST_THREE_DHT_PIN, DHT_TYPE);
  DHT        dhtFour(NEST_FOUR_DHT_PIN, DHT_TYPE);
  DHT        dhtFive(NEST_FIVE_DHT_PIN, DHT_TYPE);

  float      offset[5][3];  // [Nest#][X(Y,Z)] Initial nest offset to zero values

  char       tempArrayString[MAX_LINE];
  char       nestString[MAX_LINE];
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

//************************************************************************
//########################################################################
//************************************************************************
/*
 * Name:  InitTempSensors
 * 
 * Description: Start the DS18B20 temp sensors
 * 
 * Inputs: None.
 * 
 * Outputs: None.
 * 
 * Return:  None.
 * 
 * Notes: None.
 */

  void InitTempSensors()
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
 * Name: InitDHT    
 * 
 * Description: Start the DHT22 temp/hum sensors
 * 
 * Inputs:  None.
 * 
 * Outputs: None.
 * 
 * Return:  None.
 * 
 * Notes: None.
 */
  void InitDHT()
  {
    dhtOne.begin();
    dhtTwo.begin(); 
    dhtThree.begin(); 
    dhtFour.begin(); 
    dhtFive.begin();  
  }

 
//************************************************************************
//########################################################################
//************************************************************************
/*
 * Name: InitAccSensors()
 * 
 * Description: Initializes the ADXL345 accl/gyro sensors
 * 
 * Inputs: None.
 * 
 * Outputs: None.
 * 
 * Return: None.
 * 
 * Notes:  When the arduino is first powered on, the sensors take an 
 *          initial reading to use as an offset
 */
  void InitAccSensors()
  {
    adxlOne.powerOn();
    adxlTwo.powerOn();
    adxlThree.powerOn();
    adxlFour.powerOn();
    adxlFive.powerOn();
  
    adxlOne.setRangeSetting(2);
    adxlTwo.setRangeSetting(2);
    adxlThree.setRangeSetting(2);
    adxlFour.setRangeSetting(2);
    adxlFive.setRangeSetting(2);
  
    adxlOne.setSpiBit(0);
    adxlTwo.setSpiBit(0);
    adxlThree.setSpiBit(0);
    adxlFour.setSpiBit(0);
    adxlFive.setSpiBit(0);
  
    int x, y, z = 0;
    adxlOne.readAccel(&x, &y, &z);
    offset[0][0] = x;
    offset[0][1] = y;
    offset[0][2] = z;
  
    adxlTwo.readAccel(&x, &y, &z);
    offset[1][0] = x;
    offset[1][1] = y;
    offset[1][2] = z;
    
    adxlThree.readAccel(&x, &y, &z);
    offset[2][0] = x;
    offset[2][1] = y;
    offset[2][2] = z;
    
    adxlFour.readAccel(&x, &y, &z);
    offset[3][0] = x;
    offset[3][1] = y;
    offset[3][2] = z;
    
    adxlFive.readAccel(&x, &y, &z);
    offset[4][0] = x;
    offset[4][1] = y;
    offset[4][2] = z;
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
    
    t1.SetBottomTemp(100 * tempArrayOneBottom.getTempCByIndex(0));
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
 * Name:  RequestTemperatures
 * 
 * Description: Request the DS18B20 to get the temperatures 
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
 * Name: GetNestValues
 * 
 * Description: Get temp/hum/orientation from the each nest
 * 
 * Inputs: n1(2-5) - Nest object to store all the data
 * 
 * Outputs: n1(2-5) - Nest object with all relevant data
 * 
 * Return: None.
 * 
 * Notes: None.
 * 
 */
  void GetNestValues(Nest &n1, Nest &n2, Nest &n3, Nest &n4, Nest &n5)
  {
    int x, y, z = 0;
    adxlOne.readAccel(&x, &y, &z);
    n1.SetXDegrees(x - offset[0][0]);
    n1.SetYDegrees(y - offset[0][1]);
    n1.SetZDegrees(z - offset[0][2]);

    adxlTwo.readAccel(&x, &y, &z);
    n2.SetXDegrees(x - offset[1][0]);
    n2.SetYDegrees(y - offset[1][1]);
    n2.SetZDegrees(z - offset[1][2]);

    adxlThree.readAccel(&x, &y, &z);
    n3.SetXDegrees(x - offset[2][0]);
    n3.SetYDegrees(y - offset[2][1]);
    n3.SetZDegrees(z - offset[2][2]);

    adxlFour.readAccel(&x, &y, &z);
    n4.SetXDegrees(x - offset[3][0]);
    n4.SetYDegrees(y - offset[3][1]);
    n4.SetZDegrees(z - offset[3][2]);

    adxlFive.readAccel(&x, &y, &z);
    n5.SetXDegrees(x - offset[4][0]);
    n5.SetYDegrees(y - offset[4][1]);
    n5.SetZDegrees(z - offset[4][2]);

    float hum, temp = 0.0;
    n1.SetTemperature(dhtOne.readTemperature() * 100);
    n1.SetHumidity(dhtOne.readHumidity() * 100);

    n2.SetTemperature(dhtTwo.readTemperature() * 100);
    n2.SetHumidity(dhtTwo.readHumidity() * 100);

    n3.SetTemperature(dhtThree.readTemperature() * 100);
    n3.SetHumidity(dhtThree.readHumidity() * 100);

    n4.SetTemperature(dhtFour.readTemperature() * 100);
    n4.SetHumidity(dhtFour.readHumidity() * 100);

    n5.SetTemperature(dhtFive.readTemperature() * 100);
    n5.SetHumidity(dhtFive.readHumidity() * 100);
  }


//************************************************************************
//########################################################################
//************************************************************************
/*
 * Name:  xbeeWriteAllData
 * 
 * Description: Formats and transmits xbee strings to send wirelessly
 * 
 * Inputs: None.
 * 
 * Outputs: None.
 * 
 * Return: None.
 * 
 * Notes: None.
 * 
 */
  void xbeeWriteAllData()
  {
    char buf[MAX_LINE];
    uint8_t protocol = 2;

    sprintf(buf, "%d,%d,%d,%s", protocol, COUNTRY_CODE, BOARD_ID,tempArrayOne.ToString());
    xbee.write(buf);
    delay(50);
    
    sprintf(buf, "%d,%d,%d,%s", protocol, COUNTRY_CODE, BOARD_ID,tempArrayTwo.ToString());
    xbee.write(buf);
    delay(50);


    protocol = 1;

    sprintf(buf, "%d,%d,%d,%s", protocol, COUNTRY_CODE, BOARD_ID,nestOne.ToString());
    xbee.write(buf);
    delay(50);

    sprintf(buf, "%d,%d,%d,%s", protocol, COUNTRY_CODE, BOARD_ID,nestTwo.ToString());
    xbee.write(buf);
    delay(50);

    sprintf(buf, "%d,%d,%d,%s", protocol, COUNTRY_CODE, BOARD_ID,nestThree.ToString());
    xbee.write(buf);
    delay(50);

    sprintf(buf, "%d,%d,%d,%s", protocol, COUNTRY_CODE, BOARD_ID,nestFour.ToString());
    xbee.write(buf);
    delay(50);

    sprintf(buf, "%d,%d,%d,%s", protocol, COUNTRY_CODE, BOARD_ID,nestFive.ToString());
    xbee.write(buf);
    delay(50);
  }


//************************************************************************
//########################################################################
//************************************************************************
/*
 * Name: setup
 * 
 * Description: Begin/initialize all sensors and xbee
 * 
 * Inputs: None.
 * 
 * Outputs: None.
 * 
 * Return: None.
 * 
 * Notes: None.
 * 
 */
  void setup() 
  {
    Serial.begin(9600);       // Start serial monitor
    xbee.begin(9600);         // Start xBee
    
    // Setup DS18B20 Support
    InitTempSensors();  // Start DS18B20 temp sensors
    InitAccSensors();   // Start ADXL 345 sensors
    InitDHT();          // Start DHT22 sensors
  }


//************************************************************************
//########################################################################
//************************************************************************
/*
 * Name: MinutesToDelay
 * 
 * Description: Will delay the arduino for a set number of minutes
 * 
 * Inputs: min - an unsigned 8-bit integer for how many minutes to delay
 * 
 * Outputs: None.
 * 
 * Return: None.
 * 
 * Notes: None.
 * 
 */
  void MinutesToDelay(uint8_t min)
  {
    for(int i = 0; i < min * 2; i++)
      delay(30000);
  }
 
//************************************************************************
//########################################################################
//************************************************************************
/*
 * Name: loop
 * 
 * Description: Main processing loop
 * 
 * Inputs: None.
 * 
 * Outputs: None.
 * 
 * Return: None.
 * 
 * Notes: None.
 * 
 */

  void loop() 
  {
    GetArrayTemps(tempArrayOne, tempArrayTwo); 
    GetNestValues(nestOne, nestTwo, nestThree, nestFour, nestFive);
    
    xbeeWriteAllData();
    MinutesToDelay(30);
  }

