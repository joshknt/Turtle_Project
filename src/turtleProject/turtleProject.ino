




/*
Arduino Turtle Sketch
Authors: Derek C. Brown, Josh Kent

Purpose: Code which runs on a Arduino Mega unit 
Uses a number (depending on pins available) of DHT temperature/humidity sensor and an ADXL accelerometer
sensors per casted Sensor Egg unit to be placed in a nest to measure changes in temp,humidty,
and movement for the prediction of boils.
*/


#include "Record.h"
#include <DallasTemperature.h>
#include <OneWire.h>

//####################__SENSOR EGG PIN SETUP__#########################

//******************************************************************
//Sensor Egg 1
#define BOTTOMTEMPPIN 2
int xPin = A3; //change these to #define 
int yPin = A4;
int zPin = A5;


//******************************************************************
//Sensor Egg 2
//The pins need to be changed for second set of sensors
//byte xPin = A3;
//byte yPin = A4;
//byte zPin = A5;


//******************************************************************
//Sensor Egg 3
//The pins need to be changed for a third set of sensors
//byte xPin = A3;
//byte yPin = A4;
//byte zPin = A5;
//#####################################################################




//#######################__DECLARE VARIABLES__#########################
const int TOTALRECORDS = 50; //constant declares the number of records
int recordNumber = 0; //holds which record being sent
int arrayIndex = 0; //array bounds checker
Record nestOne[TOTALRECORDS]; //stores records
String recordName = "r"; //begins the record naming convention

OneWire bottomWire(BOTTOMTEMPPIN);
DallasTemperature bottomTemp(&bottomWire);
//#####################################################################



//*********************************************************************
void setup()
{
	Serial.begin(115200);
	analogReference(EXTERNAL); //needed to reference 3.3v for accelerometer

  bottomTemp.begin(); //needed for DS18B20
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
  Record recordName(1, recordNumber, analogRead(xPin), analogRead(yPin), analogRead(zPin));

  //test print data to serial monitor after each recording
  recordName.printToSerial();

  Serial.println(bottomTemp.getTempFByIndex(0));
  //store record in record array for nest one                   
  nestOne[arrayIndex] = recordName;  

  
	//incrememnt counters
	recordNumber++;
	arrayIndex++;

  delay(500);
	//delay(10000); //delay for 10 seconds between each reading
}


