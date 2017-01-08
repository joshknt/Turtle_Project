/*
Arduino Turtle Sketch
Authors: Derek C. Brown, Josh Kent

Purpose: Code which runs on a Arduino Mega unit 
Uses a number (depending on pins available) of DHT temperature/humidity sensor and an ADXL accelerometer
sensors per casted Sensor Egg unit to be placed in a nest to measure changes in temp,humidty,
and movement for the prediction of boils.
*/


#include "Record.h"
#include "DHT.h"

//####################__SENSOR EGG PIN SETUP__#########################

//******************************************************************
//Sensor Egg 1
#define DHTPIN 0
#define SENSORTYPE DHT11
DHT dhtOne(DHTPIN, SENSORTYPE);
int xPin = A3;
int yPin = A4;
int zPin = A5;


//******************************************************************
//Sensor Egg 2
//The pins need to be changed for second set of sensors
//byte tempHumPin = A0;
//byte xPin = A3;
//byte yPin = A4;
//byte zPin = A5;


//******************************************************************
//Sensor Egg 3
//The pins need to be changed for a third set of sensors
//byte tempHumPin = A0;
//byte xPin = A3;
//byte yPin = A4;
//byte zPin = A5;
//#####################################################################




//#######################__DECLARE VARIABLES__#########################
const int TOTALRECORDS = 50;
int recordNumber = 0; //holds which record being sent
int arrayIndex = 0; //array bounds checker
Record nestOne[TOTALRECORDS]; //stores records
String recordName = "r";
//#####################################################################



//*********************************************************************
void setup()
{
	Serial.begin(115200);
	analogReference(EXTERNAL);
  //dhtOne.begin();
}



//*********************************************************************
//Main Driver
void loop()
{
	//if array to hold records reaches maximum send data
	if (arrayIndex > TOTALRECORDS)
	{
		//todo: Send data over wifi
		arrayIndex = 0; //this is to overwrite array after transmitting data
	}


  //create new record object and name for each nest
  recordName = "r" + recordNumber;

  //store data
  //there must be a new block for each nest
  //this will not work since DHT sensor is not working (getting NaN on DHT11)
  Record recordName(1, recordNumber, dhtOne.readTemperature(true), dhtOne.readHumidity(), 
                     analogRead(xPin), analogRead(yPin), analogRead(zPin));

  //test print data to serial monitor after each recording
  recordName.printToSerial();
  
  //store record in record array for nest one                   
  nestOne[arrayIndex] = recordName;  

  
	//incrememnt counters
	recordNumber++;
	arrayIndex++;

	delay(10000); //delay for 10 seconds between each reading
}


