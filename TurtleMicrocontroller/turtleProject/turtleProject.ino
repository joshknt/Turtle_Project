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

*****************************************************************
SPI_INTERFACE:
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

*******************************************************************
TODO:
1. Add error checking for temps
2. Pass nest array to writeToFile()
3. Find interrupt pins for boards
*******************************************************************
*/



#include "Record.h"
#include <DallasTemperature.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>


#define COUNTRY_CODE 108
#define BOARD_ID 01
#define LED_WRITE_PIN 5
#define SD_PIN 10
#define TOTAL_RECORDS 2
#define FILE_EXTENSION ".txt"

//####################__SENSOR EGG PIN SETUP__#########################

//******************************************************************
//Sensor Egg 1
Adafruit_ADXL345_Unified acclOne = Adafruit_ADXL345_Unified(00000);
sensors_event_t eventOne;
float xOffsetOne, yOffsetOne, zOffsetOne;

#define BOTTOM_TEMP_PIN_ONE 2 
OneWire bottomWireOne(BOTTOM_TEMP_PIN_ONE);  
DallasTemperature bottomTempOne(&bottomWireOne);

#define MIDDLE_TEMP_PIN_ONE 3 
OneWire middleWireOne(MIDDLE_TEMP_PIN_ONE);  
DallasTemperature middleTempOne(&middleWireOne);

#define TOP_TEMP_PIN_ONE 4
OneWire topWireOne(TOP_TEMP_PIN_ONE);  
DallasTemperature topTempOne(&topWireOne);

//******************************************************************
//Sensor Egg 2


//******************************************************************
//Sensor Egg 3


//******************************************************************
//Sensor Egg 4


//#####################################################################


//#######################__DECLARE VARIABLES__#########################
uint8_t arrayIndex = 0; //Array position
//char FILE_EXTENSION[4] = ".txt"; //Variable to hold extension type
char recordNameOne[3] = "r"; //Begins the record naming convention
Record nestOne[TOTAL_RECORDS]; //Stores records

File file;  //File object for writing to the SD card
char fileName[5]; //Holds changing file names
//#####################################################################


//*********************************************************************
void setup()
{
	Serial.begin(115200);

  //Setup ADXL345 support and offsets
  acclOne.begin();
  acclOne.setRange(ADXL345_RANGE_2_G);
  acclOne.getEvent(&eventOne);
  xOffsetOne = eventOne.acceleration.x;
  yOffsetOne = eventOne.acceleration.y;
  zOffsetOne = eventOne.acceleration.z;
  

  //Setup SD support
  if(!SD.begin(SD_PIN))
  {
    Serial.println("SD not initialized");
  }


  //Declare LED pin as output and set it to off
  pinMode(LED_WRITE_PIN, OUTPUT);
  digitalWrite(LED_WRITE_PIN, LOW);

  
  //Setup DS18B20 support
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

  //Get accelerometer data
  acclOne.getEvent(&eventOne);

  //Create new record object and name for each nest
  sprintf(recordNameOne, "r%d", arrayIndex);
 
  //Store records a nest (seperate nests will each need their own constructor)
  //Data multiplied by 100 to keep the precision but saves two bytes 
  //  by not making them floats and letting the desktop software reconvert them
  Record recordNameOne(1, 100 * bottomTempOne.getTempCByIndex(0), 100 * middleTempOne.getTempCByIndex(0), 
                       100 * topTempOne.getTempCByIndex(0), (100* xOffsetOne) - (100 * eventOne.acceleration.x), 
                       (100* yOffsetOne) - (100 * eventOne.acceleration.y), (100* zOffsetOne) - (100 * eventOne.acceleration.z));                

  //Test print data to serial monitor after each recording
  recordNameOne.printToSerial();
  Serial.print("Array Index: ");
  Serial.println(arrayIndex);

  //Store records in arrays                   
  nestOne[arrayIndex] = recordNameOne;
  
	//Increment array index
	arrayIndex++;
 
  //If array to hold records reaches maximum send data
  if (arrayIndex >= TOTAL_RECORDS)
  {
    writeToFile("one", 1);
    arrayIndex = 0; //this is to overwrite array after transmitting data
  }
  
  
  //Delay for five minutes between readings 
  delay(2000);
  //secondsOfDelay(300);
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
void writeToFile(char* nest, int nestNum)
{   
    //Create file name (ex: "one.txt",  "two.txt", ect.)
    sprintf(fileName, "%s%s", nest, FILE_EXTENSION);
    
    file = SD.open(fileName, FILE_WRITE);

    //check if file opened properly
    if(file)
    { 
      //LED to indicate write so system will not be powered down
      digitalWrite(LED_WRITE_PIN, HIGH);
      delay(2000);
      
      Serial.println("File Opened");

      //increment through nest data 
      for(int i = 0; i < TOTAL_RECORDS; i++)
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

      //Close file 
      file.close();

      //Turn off LED to show it is to remove card without corruption
      digitalWrite(LED_WRITE_PIN, LOW);
      
      Serial.println("File Close");
    }  
    else
    {
      Serial.println("FILE NOT OPENED");
    }
}
