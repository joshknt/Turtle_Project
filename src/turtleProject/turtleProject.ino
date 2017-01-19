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

#define BOTTOMTEMPPINONE 2 
OneWire bottomWireOne(BOTTOMTEMPPINONE);  
DallasTemperature bottomTempOne(&bottomWireOne);

#define MIDDLETEMPPINONE 3 
OneWire middleWireOne(MIDDLETEMPPINONE);  
DallasTemperature middleTempOne(&middleWireOne);

#define TOPTEMPPINONE 4
OneWire topWireOne(TOPTEMPPINONE);  
DallasTemperature topTempOne(&topWireOne);

//******************************************************************
//Sensor Egg 2
//The pins need to be changed for second set of sensors
//byte xPinTwo = A3;
//byte yPinTwo = A4;
//byte zPinTwo = A5;

//#define BOTTOMTEMPPINTWO 5 
//OneWire bottomWireTwo(BOTTOMTEMPPINTWO);  
//DallasTemperature bottomTempTwo(&bottomWireTwo);

//#define MIDDLETEMPPINTWO 6 
//OneWire middleWireTwo(MIDDLETEMPPINTWO);  
//DallasTemperature middleTempTwo(&middleWireTwo);

//#define TOPTEMPPINTWO 7 
//OneWire topWireTwo(TOPTEMPPINTWO);  
//DallasTemperature topTempTwo(&topWireTwo);

//******************************************************************
//Sensor Egg 3
//The pins need to be changed for a third set of sensors
//byte xPinThree = A6;
//byte yPinThree = A7;
//byte zPinThree = A8;

//#define BOTTOMTEMPPINTHREE 8 
//OneWire bottomWireThree(BOTTOMTEMPPINTHREE);  
//DallasTemperature bottomTempThree(&bottomWireThree);

//#define MIDDLETEMPPINTHREE 9 
//OneWire middleWireThree(MIDDLETEMPPINTHREE);  
//DallasTemperature middleTempThree(&middleWireThree);

//#define TOPTEMPPINTHREE 10 
//OneWire topWireThree(TOPTEMPPINTHREE);  
//DallasTemperature topTempThree(&topWireThree);

//******************************************************************
//Sensor Egg 4
//The pins need to be changed for a third set of sensors
//byte xPinFour = A9;
//byte yPinFour = A10;
//byte zPinFour = A11;

//#define BOTTOMTEMPPINFOUR 11 
//OneWire bottomWireFour(BOTTOMTEMPPINFOUR);  
//DallasTemperature bottomTempFour(&bottomWireFour);

//#define MIDDLETEMPPINFOUR 12 
//OneWire middleWireFour(MIDDLETEMPPINFOUR);  
//DallasTemperature middleTempFour(&middleWireFour);

//#define TOPTEMPPINFOUR 13 
//OneWire topWireFour(TOPTEMPPINFOUR);  
//DallasTemperature topTempFour(&topWireFour);

//#####################################################################




//#######################__DECLARE VARIABLES__#########################
const int TOTALRECORDS = 50; //constant declares the number of records
int recordNumber = 0; //holds which record being sent
int arrayIndex = 0; //array bounds checker
char recordNameOne[8] = "r"; //begins the record naming convention
char recordNameTwo[8] = "r"; //begins the record naming convention
char recordNameThree[8] = "r"; //begins the record naming convention
char recordNameFour[8] = "r"; //begins the record naming convention

Record nestOne[TOTALRECORDS]; //stores records
Record nestTwo[TOTALRECORDS];
Record nestThree[TOTALRECORDS];
Record nestFour[TOTALRECORDS];
//#####################################################################



//*********************************************************************
void setup()
{
	Serial.begin(9600);
	analogReference(EXTERNAL); //needed to reference 3.3v for accelerometer

  //Needed for DS18B20 support
  //Nest one 
  bottomTempOne.begin();
  middleTempOne.begin();
  topTempOne.begin();

  //Nest two
//  bottomTempTwo.begin(); 
//  middleTempTwo.begin();
//  topTempTwo.begin();
  
  //Nest three
//  bottomTempThree.begin(); 
//  middleTempThree.begin();
//  topTempThree.begin();
  
  //Nest four
//  bottomTempFour.begin(); 
//  middleTempFour.begin();
//  topTempFour.begin();
}



//*********************************************************************
//Main Driver
void loop()
{
	//If array to hold records reaches maximum send data
	if (arrayIndex > TOTALRECORDS)
	{
		//Todo: Send data over wifi or SD Card write
		arrayIndex = 0; //this is to overwrite array after transmitting data
	}


  //Request temperatures from sensors
  requestTemperatures();

  
  //Create new record object and name for each nest
  strcat(recordNameOne, recordNumber);
  strcat(recordNameTwo, recordNumber);
  strcat(recordNameThree, recordNumber);
  strcat(recordNameFour, recordNumber);


  //Store records for each nest
  //Temps are multiplied by 100 to keep the precision but save two bytes 
  //  by not making them floats and letting the desktop software reconvert them
  Record recordNameOne(1, recordNumber, 100 * bottomTempOne.getTempFByIndex(0), 100 * middleTempOne.getTempFByIndex(0), 
                       100 * topTempOne.getTempFByIndex(0), analogRead(xPinOne), analogRead(yPinOne), analogRead(zPinOne)); //nest one
                       
  //Record recordNameTwo(2, recordNumber, 100 * bottomTempTwo.getTempFByIndex(0), 100 * middleTempTwo.getTempFByIndex(0),
  //                       100 * topTempTwo.getTempFByIndex(0), analogRead(xPinTwo), analogRead(yPinTwo), analogRead(zPinTwo)); //nest two
                         
  //Record recordNameThree(3, recordNumber, 100 * bottomTempThree.getTempFByIndex(0), 100 * middleTempThree.getTempFByIndex(0), 
  //                         100 * topTempThree.getTempFByIndex(0), analogRead(xPinThree), analogRead(yPinThree), analogRead(zPinThree)); //nest three
  
  //Record recordNameFour(4, recordNumber, 100 * bottomTempFour.getTempFByIndex(0), 100 * middleTempThree.getTempFByIndex(0), 
  //                         100 * topTempFour.getTempFByIndex(0), analogRead(xPinFour), analogRead(yPinFour), analogRead(zPinFour)); //nest four

  
  //Test print data to serial monitor after each recording
  recordNameOne.printToSerial();
  

  //Store records in arrays                   
  nestOne[arrayIndex] = recordNameOne;
  //nestTwo[arrayIndex] = recordNameTwo;
  //nestThree[arrayIndex] = recordNameThree;
  //nestFour[arrayIndex] = recordNameFour;  

  
	//Incrememnt counters
	recordNumber++;
	arrayIndex++;

  //Delay for 1 second between readings for testing
  //delay(1000);
}


//*********************************************************************
//Request temperature reading from DS18B20 sensor
void requestTemperatures()
{
  //Nest One
  bottomTempOne.requestTemperatures();
  middleTempOne.requestTemperatures();
  topTempOne.requestTemperatures();

  //Nest Two
//  bottomTempTwo.requestTemperatures();
//  middleTempTwo.requestTemperatures();
//  topTempTwo.requestTemperatures();

  //Nest Three
//  bottomTempThree.requestTemperatures();
//  middleTempThree.requestTemperatures();
//  topTempThree.requestTemperatures();

  //Nest Four
//  bottomTempFour.requestTemperatures();
//  middleTempFour.requestTemperatures();
//  topTempFour.requestTemperatures();
}


