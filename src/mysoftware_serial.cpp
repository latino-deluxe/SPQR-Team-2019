#include "mysoftware_serial.h"
#include "vars.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

/*
 *
 * TODO
 *
 */

SoftwareSerial mySerial(10, 11); // RX, TX
long dist, degree;
char mystr[20];

void initSoftwareSerial(){
  mySerial.begin(115200);
}

void readSoftwareSerial(){
  if(mySerial.available() > 0){
    Serial.println("puzzette");
    Serial.println(mySerial.read());
    //receive the full char
    mySerial.readBytes(mystr, 20);

    //translates the char array to long
    sscanf(mystr, "%ld", &mess);

    //excludes the dist part from the long, with a AND operation
    degree = mess & 0b111111111; //mess & 1023

    //shifts to the right the distance, getting the original dist byte
    dist = mess >> 9;
  }else{
    Serial.println("No data available");
  }
}

void testSoftwareSerial(){
  readSoftwareSerial();

  Serial.println(mess);
  // Serial.print("Degrees: ");
  // Serial.println(degree);
  // Serial.print("Distance: ");
  // Serial.println(dist);
}
