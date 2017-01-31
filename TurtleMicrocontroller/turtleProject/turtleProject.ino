/*
Arduino Turtle Sketch
Authors: Josh Kent

Purpose: Code which runs on a Arduino Mega unit 
Uses a number (depending on pins available) of DHT temperature/humidity sensor and an ADXL accelerometer
sensors per casted Sensor Egg unit to be placed in a nest to measure changes in temp,humidty,
and movement for the prediction of boils.

This implementation is for the Arduino Mega. This is because of the 
different pins used for the SPI bus that the MicroSD card uses and
the accelerometers use. 

Arduino Uno:
MISO/SDO: 12
MOSI/SDA: 11  
CLK: 13
SS: 10
INT_1: //check which pins are interrupt pins for Uno

Arduino Mega:
MISO/SDO: 50
MOSI/SDA: 51
CLK: 52
SS: 53
INT_1: //check which pins are interrupt pins for Mega
*/



#include "Record.h"
#include <DallasTemperature.h>
#include <OneWire.h>
#include <SPI.h>
#include <SD.h>
#include <SparkFun_ADXL345.h>

#define COUNTRY_CODE 108
#define BOARD_ID 01
#define LEDWRITEPIN 5

//####################__SENSOR EGG PIN SETUP__#########################

//******************************************************************
//Sensor Egg 1
int xPinOne = A0; 
int yPinOne = A1;
int zPinOne = A2;
ADXL345 acclOne = ADXL345(9);

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


//******************************************************************
//Sensor Egg 3


//******************************************************************
//Sensor Egg 4


//#####################################################################


//#######################__DECLARE VARIABLES__#########################
const int TOTALRECORDS = 2; //constant declares the number of records
int arrayIndex = 0; //array position
char *fileExtension = ".txt"; //variable to hold extension type
char recordNameOne[8] = "r"; //begins the record naming convention
Record nestOne[TOTALRECORDS]; //stores records

File file;  //file object for writing to the SD card
char fileName[8]; //holds changing file names

int sdPin = 10; //pin for SD card (UNO) 
int accPin = 9; //pin for accelerometer
//int sdPin = 53 //pin for SD card (Mega)
//#####################################################################


//*********************************************************************
void setup()
{
	Serial.begin(115200);
  
	analogReference(EXTERNAL); //needed to reference 3.3v for accelerometer

  //setup SD support
  pinMode(sdPin, OUTPUT);
  if(!SD.begin(sdPin))
  {
    Serial.println("MicroSD not initialized");
  }

  //declare LED pin as output and set it to off
  pinMode(LEDWRITEPIN, OUTPUT);
  digitalWrite(LEDWRITEPIN, LOW);
  
  //Needed for DS18B20 support
  //Nest one 
  bottomTempOne.begin();
  middleTempOne.begin();
  topTempOne.begin();
}


//*********************************************************************
//Main Driver
void loop()
{
  //Request temperatures from sensors
  requestTemperatures();

  //Create new record object and name for each nest
  strcat(recordNameOne, arrayIndex);

  //Store records a nest (seperate nests will each need their own constructor)
  //Temps are multiplied by 100 to keep the precision but save two bytes 
  //  by not making them floats and letting the desktop software reconvert them
  Record recordNameOne(1, 100 * bottomTempOne.getTempCByIndex(0), 100 * middleTempOne.getTempCByIndex(0), 
                       100 * topTempOne.getTempCByIndex(0), analogRead(xPinOne), analogRead(yPinOne), analogRead(zPinOne)); //nest one               

  //Test print data to serial monitor after each recording
  recordNameOne.printToSerial();
  Serial.print("Array Index: ");
  Serial.println(arrayIndex);
  
  //Store records in arrays                   
  nestOne[arrayIndex] = recordNameOne;
  
	//Increment array index
	arrayIndex++;
 
  //If array to hold records reaches maximum send data
  if (arrayIndex >= TOTALRECORDS)
  {
    //TODO: the nest array needs to be passed
    writeToFile("one", 1);

    //this is to overwrite array after transmitting data
    arrayIndex = 0; 
  }
  
  
  //Delay for three minutes between readings 
  delay(10000);
  //secondsOfDelay(240);
}


//*********************************************************************
//Request temperature reading from DS18B20 sensor
void requestTemperatures()
{
  //Nest One
  bottomTempOne.requestTemperatures();
  middleTempOne.requestTemperatures();
  topTempOne.requestTemperatures();
}


//*********************************************************************
//Allows device to delay by seconds rather than m/s
void secondsOfDelay(int seconds)
{
  for(int i = 0; i < seconds; i++)
  {
    delay(1000);
  }
}


//*********************************************************************
//Writes data from arrays into text file
//TODO: the nest array needs to be passed
void writeToFile(char* nest, int nestNum)
{
    //create file name (ex: "one.txt",  "two.txt", ect.)
    sprintf(fileName, "%s%s", nest, fileExtension);
    
    //LED to indicate write so system will not be powered down
    digitalWrite(LEDWRITEPIN, HIGH);
    delay(2000);
    
    file = SD.open(fileName, FILE_WRITE);

    //check if file opened properly
    if(file)
    { 
      Serial.println("File Opened");
      delay(1000);
      //increment through nest data 
      for(int i = 0; i < TOTALRECORDS; i++)
      {
        file.print(COUNTRY_CODE); file.print(",");
        file.print(BOARD_ID); file.print(",");
        file.print(nestNum); file.print(",");
        file.print(nestOne[i].getBottomTemp()); file.print(",");
        file.print(nestOne[i].getMiddleTemp()); file.print(",");
        file.print(nestOne[i].getTopTemp()); file.print(",");
        file.print(nestOne[i].getXAcc()); file.print(",");
        file.print(nestOne[i].getYAcc()); file.print(",");
        file.println(nestOne[i].getZAcc());
      }

      //close file 
      file.close();

      digitalWrite(LEDWRITEPIN, LOW);
      
      Serial.println("File Close");
      delay(1000);
    }  
}

