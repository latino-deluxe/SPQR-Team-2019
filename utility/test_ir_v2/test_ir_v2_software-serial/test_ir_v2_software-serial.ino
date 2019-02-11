/*
test_ir_v2.ino

This code takes data from 12 IR sensors in a circle 30 deg apart from each
other, than converts the data into a byte, containing the direction of
the ball in degrees and its distance, that is then transferred to
the main control via serial communication.
This code is to be used only on the ATMEGA328P and equivalents and it is
meant for the ball recognition part of the SPQR robotics team robots.

Created by: Alessandro Mauri
Day 6/12/2018 (DD/MM/YY)
Modified by: Alessandro Mauri
Day 19/12/2018
Modified by: Emanuele Coletta, Emanuele Latino & Siria Sannino
Day 9/1/2018 Added Software Serial control, with map from -180, 180 to 0,360
*/

#include <math.h>
#include <SoftwareSerial.h>

#define TOUT 100
#define DEBUG 0
#define THRL 30
#define THRH 253


byte tx_data = 0;
float tmp_y, tmp_x;
int pins[] = {A0, 2, 3, 4, 5, 6, 7, 8, 9, A1, 0, 1}, t;
float vect[2], s_data[12], dist, angle, angle2;
const float sins[12] = {0, 0.5, 0.866, 1, 0.866, 0.5, 0, -0.5, -0.866, -1, -0.866, -0.5},
            cosins[12] = {1, 0.866, 0.5, 0, -0.5, -0.866, -1, -0.866, -0.5, 0, 0.5, 0.866};

SoftwareSerial mySerial(10 ,11); // RX, TX

long ssDegree = 0b000000011, ssDist = 0b00000001;

long mess;
char mystr[20];

void setup(){
  Serial.begin(9600);
  mySerial.begin(115200);
  
  for (byte x = 0; x < 12; x++) pinMode(pins[x], INPUT);
}

void loop() {

  t = millis();
  readSensors_old();
  // print unmodiefied values for debug
  if (DEBUG == 1){
    Serial.println("-----------");
    Serial.println(angle);
    Serial.println(dist);
    Serial.println("-----------");
  }
  t = millis() - t;
  if (DEBUG == 11) Serial.println(t);

  dataConstruct();
  //Serial.println(tx_data);
  if (DEBUG == 1) delay(1000);
}

void readSensors_old(){
  for (int i = 0; i < 255; i++){
    s_data[0] += !digitalRead(pins[0]);
    s_data[1] += !digitalRead(pins[1]);
    s_data[2] += !digitalRead(pins[2]);
    s_data[3] += !digitalRead(pins[3]);
    s_data[4] += !digitalRead(pins[4]);
    s_data[5] += !digitalRead(pins[5]);
    s_data[6] += !digitalRead(pins[6]);
    s_data[7] += !digitalRead(pins[7]);
    s_data[8] += !digitalRead(pins[8]);
    s_data[9] += !digitalRead(pins[9]);
    s_data[10] += !digitalRead(pins[10]);
    s_data[11] += !digitalRead(pins[11]);
  }

  for (byte i = 0; i < 12; i++){
    if ((s_data[i] < THRL) || (s_data[i] > THRH)){
      s_data[i] = 0;
    }

    if ((DEBUG == 1) && (s_data[i] != 0)){
      Serial.print(i);
      Serial.print(" | ");
      Serial.println(s_data[i]);
    }

    tmp_y = (s_data[i] * sins[i]);
    tmp_x = (s_data[i] * cosins[i]);
    vect[0] += tmp_y;
    vect[1] += tmp_x;
    s_data[i] = 0;
  }

  if (DEBUG == 1){
    Serial.print("x: ");
    Serial.print(vect[1]);
    Serial.print(" | ");
    Serial.print("y: ");
    Serial.println(vect[0]);
  }
  angle = atan2(vect[0], vect[1]);
  angle = (angle * 4068) / 71;
  dist = sqrt(square(vect[0]) + square(vect[1]));
  //cast da 0 a 360 ;)
  angle = map(angle,-179,180,0,360);

  vect[0] = 0;
  vect[1] = 0;

  //ssDegree = angle;
  //ssDist = dist;

  sendData();
}

void sendData(){
  //constructing the data int. Shift the distance by 9 bits (size of degree int), then ORs the degree int, and voilà 
  mess = ssDist;
  mess = mess << 9;
  mess |= ssDegree;

  //long to string, SERIAL COMMUNICATION CAN ONLY SEND A BYTE, NOT MORE THAN THAT, but a char array can be sent
  String s = String(mess);
  //string to char array
  s.toCharArray(mystr, 20);
  
  Serial.println(mystr);
  
  //send the char array, so the full data can be sent
  mySerial.write(mystr, 20);

  //bit of delay
  delay(1000);
}

void dataConstruct(){
  //WIP: need more data
}
