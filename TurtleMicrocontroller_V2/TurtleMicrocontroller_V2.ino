
#include "Nest.h"
#include "TempArray.h"
#include <DallasTemperature.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>


//************************************************************************
//########################################################################
//************************************************************************

// Constants:

#define COUNTRY_CODE    108
#define BOARD_ID        02
#define MAX_RECORDS     100

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

  TempArray tempArrayOne[MAX_RECORDS];
  TempArray tempArrayTwo[MAX_RECORDS];
  
  Nest      nestOne[MAX_RECORDS];
  Nest      nestTwo[MAX_RECORDS];
  Nest      nestThree[MAX_RECORDS];

// End Global Variables

//************************************************************************
//########################################################################
//************************************************************************

// Nest Setup:

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

// End Nest Setup

//************************************************************************
//########################################################################
//************************************************************************

void setup() 
{
  Serial.begin(9600);

}

//************************************************************************
//########################################################################
//************************************************************************

void loop() 
{
  Serial.println("k");
}
