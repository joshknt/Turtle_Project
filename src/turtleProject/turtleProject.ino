




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
int xPinOne = A0; 
int yPinOne = A1;
int zPinOne = A2;

//#define BOTTOMTEMPPINONE 2 
//OneWire bottomWireOne(BOTTOMTEMPPINONE);  
//DallasTemperature bottomTempOne(&bottomWireOne);

//#define MIDDLETEMPPIN 3 
//OneWire middleWireOne(MIDDLETEMPPINONE);  
//DallasTemperature middleTempOne(&middleWireOne);

//#define TOPTEMPPIN 4 
//OneWire topWireOneOne(TOPTEMPPINONE);  
//DallasTemperature topTempOne(&topWireOne);

//******************************************************************
//Sensor Egg 2
//The pins need to be changed for second set of sensors
//byte xPinTwo = A3;
//byte yPinTwo = A4;
//byte zPinTwo = A5;

//#define BOTTOMTEMPPIN 5 
//OneWire bottomWireTwo(BOTTOMTEMPPINTWO);  
//DallasTemperature bottomTempTwo(&bottomWireTwo);

//#define MIDDLETEMPPIN 6 
//OneWire middleWireTwo(MIDDLETEMPPINTWO);  
//DallasTemperature middleTempTwo(&middleWireTwo);

//#define TOPTEMPPIN 7 
//OneWire topWireTwo(TOPTEMPPINTWO);  
//DallasTemperature topTempTwo(&topWireTwo);

//******************************************************************
//Sensor Egg 3
//The pins need to be changed for a third set of sensors
//byte xPinThree = A6;
//byte yPinThree = A7;
//byte zPinThree = A8;

//#define BOTTOMTEMPPIN 8 
//OneWire bottomWireThree(BOTTOMTEMPPINTHREE);  
//DallasTemperature bottomTempThree(&bottomWireThree);

//#define MIDDLETEMPPIN 9 
//OneWire middleWireThree(MIDDLETEMPPINTHREE);  
//DallasTemperature middleTempThree(&middleWireThree);

//#define TOPTEMPPIN 10 
//OneWire topWireThree(TOPTEMPPINTHREE);  
//DallasTemperature topTempThree(&topWireThree);

//******************************************************************
//Sensor Egg 4
//The pins need to be changed for a third set of sensors
//byte xPinFour = A9;
//byte yPinFour = A10;
//byte zPinFour = A11;

//#define BOTTOMTEMPPIN 11 
//OneWire bottomWireFour(BOTTOMTEMPPINFOUR);  
//DallasTemperature bottomTempFour(&bottomWireFour);

//#define MIDDLETEMPPIN 12 
//OneWire middleWireFour(MIDDLETEMPPINFOUR);  
//DallasTemperature middleTempFour(&middleWireFour);

//#define TOPTEMPPIN 13 
//OneWire topWireFour(TOPTEMPPINFOUR);  
//DallasTemperature topTempFour(&topWireFour);

//#####################################################################




//#######################__DECLARE VARIABLES__#########################
const int TOTALRECORDS = 80; //constant declares the number of records
int recordNumber = 0; //holds which record being sent
int arrayIndex = 0; //array bounds checker
Record nestOne[TOTALRECORDS]; //stores records
Record nestTwo[TOTALRECORDS];
Record nestThree[TOTALRECORDS];
Record nestFour[TOTALRECORDS];

//todo: change to c-strings
String recordName = "r"; //begins the record naming convention
//#####################################################################



//*********************************************************************
void setup()
{
	Serial.begin(9600);
	analogReference(EXTERNAL); //needed to reference 3.3v for accelerometer

  //bottomTemp.begin(); //needed for DS18B20
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
  //todo: modify this to work with c-strings
  recordName = "r" + recordNumber;

  //store data
  //there must be a new block for each nest
  Record recordNameOne(1, recordNumber, analogRead(xPinOne), analogRead(yPinOne), analogRead(zPinOne)); //nest one
  //Record recordNameTwo(2, recordNumber, analogRead(xPinTwo), analogRead(yPinTwo), analogRead(zPinTwo)); //nest two
  //Record recordNameThree(3, recordNumber, analogRead(xPinThree), analogRead(yPinThree), analogRead(zPinThree)); //nest three
  //Record recordNameFour(4, recordNumber, analogRead(xPinFour), analogRead(yPinFour), analogRead(zPinFour)); //nest four
  
  //test print data to serial monitor after each recording
  recordNameOne.printToSerial();

  //store records in arrays                   
  nestOne[arrayIndex] = recordNameOne;
  //nestTwo[arrayIndex] = recordNameTwo;
  //nestThree[arrayIndex] = recordNameThree;
  //nestFour[arrayIndex] = recordNameFour;  

  
	//incrememnt counters
	recordNumber++;
	arrayIndex++;


	//delay(10000); //delay for 10 seconds between each reading
}


