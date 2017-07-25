
#include "Nest.h"
#include "TempArray.h"
#include <DallasTemperature.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>


//************************************************************************
//########################################################################
//************************************************************************


  // Constants:
  #define DEBUG           true
  
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
  #define NEST_ONE_DHT_PIN      53   
  #define NEST_TWO_DHT_PIN      52
  #define NEST_THREE_DHT_PIN    51
  
  // Nest ADXL345 Sensors (Gyroscope/Accelerometer)
  #define NEST_ONE_ADXL_PIN     22
  #define NEST_TWO_ADXL_PIN     23  
  #define NEST_THREE_ADXL_PIN   24
  
  // End Constants


//************************************************************************
//########################################################################
//************************************************************************


  // Global Variables:
  SoftwareSerial  xbee(0, 1); 
  
  TempArray  tempArrayOne;
  TempArray  tempArrayTwo;
  
  Nest       nestOne(1);
  Nest       nestTwo(2);
  Nest       nestThree(3);
  Nest       nestFour(4);
  Nest       nestFive(5);

  float      offset[5][3];  // [Nest#][X(Y,Z)] Initial nest offset to zero values

  // End Global Variables


//************************************************************************
//########################################################################
//************************************************************************


  // Nest Initialization:

  OneWire           tempArrayOneBottomWire(TEMP_ARRAY_ONE_BOTTOM_PIN);
  OneWire           tempArrayOneMiddleWire(TEMP_ARRAY_ONE_MIDDLE_PIN);
  OneWire           tempArrayOneTopWire(TEMP_ARRAY_ONE_TOP_PIN);
  OneWire           tempArrayTwoBottomWire(TEMP_ARRAY_ONE_BOTTOM_PIN);
  OneWire           tempArrayTwoMiddleWire(TEMP_ARRAY_ONE_MIDDLE_PIN);
  OneWire           tempArrayTwoTopWire(TEMP_ARRAY_ONE_TOP_PIN);
  
  DallasTemperature tempArrayOneBottom(&tempArrayOneBottomWire);
  DallasTemperature tempArrayOneMiddle(&tempArrayOneMiddleWire);
  DallasTemperature tempArrayOneTop(&tempArrayOneTopWire);
  DallasTemperature tempArrayTwoBottom(&tempArrayOneBottomWire);
  DallasTemperature tempArrayTwoMiddle(&tempArrayTwoMiddleWire);
  DallasTemperature tempArrayTwoTop(&tempArrayTwoTopWire);

  // End Nest Initialization


//************************************************************************
//########################################################################
//************************************************************************


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


void GetArrayTemps(TempArray &t1, TempArray &t2)
{
  t1.SetBottomTemp(100 * tempArrayOneBottom.getTempCByIndex(0));
  delay(200);
  t1.SetMiddleTemp(100 * tempArrayOneMiddle.getTempCByIndex(0));
  delay(200);
  t1.SetTopTemp(100 * tempArrayOneTop.getTempCByIndex(0));
  delay(200);
  
  t2.SetBottomTemp(100 * tempArrayTwoBottom.getTempCByIndex(0));
  delay(200);
  t2.SetMiddleTemp(100 * tempArrayTwoMiddle.getTempCByIndex(0));
  delay(200);
  t2.SetTopTemp(100 * tempArrayTwoTop.getTempCByIndex(0));
  delay(200);
}


//************************************************************************
//########################################################################
//************************************************************************


void setup() 
{
#if DEBUG
  Serial.begin(9600);
#endif

  // Setup DS18B20 Support
  InitializeTempSensors();
  
  
  xbee.begin(9600);

}


//************************************************************************
//########################################################################
//************************************************************************


void loop() 
{
  //xbee.write("string");
  GetArrayTemps(tempArrayOne, tempArrayTwo); 
}




