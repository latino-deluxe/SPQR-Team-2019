#include "linesensor.h"
#include "goalie.h"
#include "pid.h"
#include "motors.h"
#include "music.h"
#include "vars.h"
#include <Arduino.h>

// init line sensors and attaches interrput
// void initLineSensors() {
//   pinMode(S0, INPUT);
//   pinMode(S1, INPUT);
//   pinMode(S2, INPUT);
//   pinMode(S3, INPUT);
// }

int linepinsI[4] = {S1I, S2I, S3I, S4I};
int linepinsO[4] = {S1O, S2O, S3O, S4O};
int linetriggerI[4];
int linetriggerO[4];
int lineCnt;
int CNTY;
int CNTX;
byte linesensbyteI;
byte linesensbyteO;
byte linesensbyte;
byte linesensbyteOLDY;
byte linesensbyteOLDX;
elapsedMillis exitTimer;

void checkLineSensors() {
  linesensbyteI = 0;
  linesensbyteO = 0;
  // linesensbyte  = 0;
  exitTimer = 0;
  for(int i = 0; i < 4; i++) {
    linetriggerI[i] = analogRead(linepinsI[i]) > LINE_THRESH;
    linetriggerO[i] = analogRead(linepinsO[i]) > LINE_THRESH;
    if(linetriggerI[i] || linetriggerO[i]) lineCnt = EXTIME;
    linesensbyteI = linesensbyteI + (linetriggerI[i]<<i);
    linesensbyteO = linesensbyteO + (linetriggerO[i]<<i);
  }
  // playSafe();
  linesensbyte |= (linesensbyteI | linesensbyteO);
  if(linesensbyte > 0) bounds = true;
  else bounds = false;
  if(bounds) outOfBounds();                                            
}

void outOfBounds() {
  // if(lineCnt == EXTIME) {
  if((linesensbyte == 2 || linesensbyte == 8)) {
    linesensbyteOLDY = linesensbyte;
    CNTY = 1000;
    CNTY--;
  }
  if(CNTY <= 0) {
    CNTY = 0;
    linesensbyteOLDY = 0;
  }

  if((linesensbyte == 1 || linesensbyte == 4)) {
    linesensbyteOLDX = linesensbyte;
    CNTX = 1000;
    CNTX--;
  }
  if(CNTX <= 0) {
    CNTX = 0;
    linesensbyteOLDY = 0;
  }

    switch(linesensbyte) {
      case 0:
      case 15:
        tone(30, LA3);
      break;


      case 10:
        if(linesensbyteOLDX == 1) {
          outDir = 180;
          outVel = 255;
          tone(30, F6);
        } else if(linesensbyteOLDX == 4) {
          outDir = 0;
          outVel = 255;
          tone(30, F4);
        }
        else {
          outDir = 0;
          outVel = 0;
          tone(30, LA3);
        }
      break;

      case 5:
        if(linesensbyteOLDY == 2) {
          outDir = 270;
          outVel = 255;
          tone(30, F6);
        } else if(linesensbyteOLDY == 8) {
          outDir = 90;
          outVel = 255;
          tone(30, F4);
        }
        else {
          outDir = 0;
          outVel = 0;
          tone(30, LA3);
        }
      break;

      case 1:
      case 11:
        outDir = 180;
        outVel = 255;
      break;

      case 2:
      case 7:
        outDir = 270;
        outVel = 255;
      break;

      case 4:
      case 14:
        outDir = 0;
        outVel = 255;
      break;

      case 8:
      case 13:
        outDir = 90;
        outVel = 255;
      break;



      case 3:
        outDir = 225;
        outVel = 255;
      break;

      case 6:
        outDir = 315;
        outVel = 255;
      break;

      case 12:
        outDir = 45;
        outVel = 255;
      break;

      case 9:
        outDir = 135;
        outVel = 255;
      break;



      default:
        outDir = 0;
        outVel = 0;
        // goCenter();         //UNA VOLTA ABILITATI GLI US
      break;
    }
  // }

  if(lineCnt > 0) preparePID(outDir, outVel);

  lineCnt--;
  if(lineCnt < 0) {
    lineCnt = 0;
    outDir = 0;
  }

  if(lineCnt == 0) {
    linesensbyte = 0;
    noTone(30);
  }
}

void playSafe() {
  switch(linesensbyte) {
    case 1:
    case 4:
      x = 1;
      y = 0;
    break;

    case 2:
    case 8:
      x = 0;
      y = 1;
    break;

    default:
      x = 1;
      y = 1;
    break;
  }
}

void testLineSensors(){

  checkLineSensors();

  Serial.println("----------");  
  for(int i = 0; i<4; i++) {
    Serial.print(linetriggerI[i]);
    Serial.print("-");
    Serial.print(linetriggerO[i]);
    Serial.print(" | ");
  }
  Serial.println();
  Serial.println("----------"); 
  
  Serial.print("Byte:   ");
  Serial.print(linesensbyteO);
  Serial.print("    Direzione:    ");
  Serial.println(outDir);
  delay(150);

  Serial.println("----------"); 

}