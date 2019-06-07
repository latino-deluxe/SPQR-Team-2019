#include "linesensor.h"
#include "pid.h"
#include "motors.h"
#include "myspi_old.h"
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
byte linesensbyteI;
byte linesensbyteO;
byte linesensbyte;
elapsedMillis exitTimer;

void checkLineSensors() {
  linesensbyteI = 0;
  linesensbyteO = 0;
  linesensbyte  = 0;
  exitTimer = 0;
  for(int i = 0; i<4; i++) {
    linetriggerI[i] = analogRead(linepinsI[i]) > LINE_THRESH;
    linetriggerO[i] = analogRead(linepinsO[i]) > LINE_THRESH;
    if(linetriggerI[i] || linetriggerO[i]) lineCnt = EXTIME;
    linesensbyteI = linesensbyteI + (linetriggerI[i]<<i);
    linesensbyteO = linesensbyteO + (linetriggerO[i]<<i);
  }
  linesensbyte = linesensbyteI | linesensbyteO;
  if(linesensbyte > 0) bounds = true;
  else bounds = false;
  outOfBounds();
}

void outOfBounds() {
  if(lineCnt == EXTIME) {
    switch(linesensbyte) {
      case 0:
        outDir = 0;
        outVel = 0;
      break;

      case 1:
        outDir = 180;
        outVel = 200;
      break;

      case 2:
        outDir = 270;
        outVel = 200;
      break;

      case 4:
        outDir = 0;
        outVel = 200;
      break;

      case 8:
        outDir = 90;
        outVel = 200;
      break;



      case 3:
        outDir = 225;
        outVel = 200;
      break;

      case 6:
        outDir = 315;
        outVel = 200;
      break;

      case 12:
        outDir = 45;
        outVel = 200;
      break;

      case 9:
        outDir = 135;
        outVel = 200;
      break;



      default:
        outDir = new_Dir + 180;
        if(outDir > 360) outDir = outDir - 360;
        outVel = 200;
      break;
    }
  }

  if(lineCnt > 0) preparePID(outDir, outVel);
  else preparePID(0, 0);

  lineCnt--;
  if(lineCnt < 0) {
    lineCnt = 0;
    outDir = 0;
  }

  /*Serial.print("Byte:   ");
  Serial.print(linesensbyteO);
  Serial.print("    Direzione:    ");
  Serial.println(outDir);
  delay(150);*/
}


void playSafe() {
  
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