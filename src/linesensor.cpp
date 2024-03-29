#include "linesensor.h"
#include "goalie.h"
#include "position.h"
#include "pid.h"
#include "motors.h"
#include "music.h"
#include "vars.h"
#include "nano_ball.h"
#include <Arduino.h>

int linepinsI[4] = {S1I, S2I, S3I, S4I};
int linepinsO[4] = {S1O, S2O, S3O, S4O};
int linetriggerI[4];
int linetriggerO[4];
int lineCnt;
int CNTY;
int CNTX;
int prevDir;
int ai, ar;

byte linesensbyteI;
byte linesensbyteO;
byte linesensbyte;
byte linesensbytefst;
byte linesensbyteOLDY;
byte linesensbyteOLDX;

bool fboundsX;
bool fboundsY;

int outDir;
int outVel;

elapsedMillis ltimer;

void checkLineSensors() {
  linesensbyteI = 0;
  linesensbyteO = 0;

  for(int i = 0; i < 4; i++) {
    linetriggerI[i] = analogRead(linepinsI[i]) > LINE_THRESH;
    linetriggerO[i] = analogRead(linepinsO[i]) > LINE_THRESH;
    linesensbyteI = linesensbyteI | (linetriggerI[i]<<i);
    linesensbyteO = linesensbyteO | (linetriggerO[i]<<i);
  }

  if ((linesensbyteI > 0) || (linesensbyteO > 0)) {
    if(exitTimer > EXTIME) {
      fboundsX = true;
      fboundsY = true;
    }
    exitTimer = 0;
  }

  linesensbyte |= (linesensbyteI | linesensbyteO);

  outOfBounds();
}

void outOfBounds(){

  if(fboundsX == true) {
    if(linesensbyte & 0x02) linesensbyteOLDX = 2;
    else if(linesensbyte & 0x08) linesensbyteOLDX = 8;
    //BIBOP ERROROZZO
    //if(linesensbyteOLDX != 0) fboundsX == false;
    if(linesensbyteOLDX != 0) fboundsX = false;
  }
  if(fboundsY == true) {
    if(linesensbyte & 0x01) linesensbyteOLDY = 1;
    else if(linesensbyte & 0x04) linesensbyteOLDY = 4;
    //BIBOP ERROROZZO
    //if(linesensbyteOLDY != 0) fboundsY == false;
    if(linesensbyteOLDY != 0) fboundsY = false;
  }

    //
    // Serial.print(linesensbyte);
    // Serial.print(" ");
    // Serial.print(linesensbyteOLDX);
    // Serial.print(" ");
    // Serial.print(linesensbyteOLDY);
    // Serial.print(" ");
    // Serial.print(exitTimer);
    // Serial.println(" ");




  if (exitTimer <= EXTIME){
    //fase di rientro
    if(linesensbyte == 15) {
      linesensbyte = linesensbyteOLDY | linesensbyteOLDX;        //ZOZZATA MAXIMA
      //digitalWrite(Y, HIGH);
    }

    switch(linesensbyte){
      case 1:
        outDir = 180;
        outVel = 250;
        ai = 0;
        ar = 30;
        break;
      case 2:
        outDir = 270;
        outVel = 250;
        ai = 90;
        ar = 60;
        break;
      case 4:
        outDir = 0;
        outVel = 250;
        ai = 180;
        ar = 30;
        break;
      case 8:
        outDir = 90;
        outVel = 250;
        ai = 270;
        ar = 60;
        break;
      case 3:
        outDir = 225;
        outVel = 250;
        ai = 45;
        ar = 20;
        break;
      case 6:
        outDir = 315;
        outVel = 250;
        ai = 135;
        ar = 20;
        break;
      case 12:
        outDir = 45;
        outVel = 250;
        ai = 225;
        ar = 20;
        break;
      case 9:
        outDir = 135;
        outVel = 250;
        ai = 315;
        ar = 20;
        break;
      case 7:
        outDir = 270;
        outVel = 250;
        ai = 90;
        ar = 60;
        break;
      case 13:
        outDir = 90;
        outVel = 250;
        ai = 270;
        ar = 60;
        break;
      case 11:
        outDir = 180;
        outVel = 250;
        ai = 0;
        ar = 60;
        break;
      case 14:
        outDir = 0;
        outVel = 250;
        ai = 180;
        ar = 60;
        break;


      case 5:
        //digitalWrite(R, HIGH);
        if(linesensbyteOLDX == 2) {
          outDir = 270;
          ai = 90;
          ar = 30;
        }
        if(linesensbyteOLDX == 8) {
          outDir = 90;
          ai = 270;
          ar = 30;
        }
        outVel = 250;
        break;
      case 10:
        //digitalWrite(G, HIGH);
        if(linesensbyteOLDY == 4) {
          outDir = 0;
          ai = 180;
          ar = 30;
        }
        if(linesensbyteOLDY == 1) {
          outDir = 180;
          ai = 0;
          ar = 30;
        }
        outVel = 250;
        break;
      case 15:
      // Serial.print(linesensbyteOLDX);
      // Serial.print(" ");
      // Serial.print(linesensbyteOLDY);
      // Serial.println(" ");



        break;
      case 0:
      default:
        //;)
        break;
    }
    ballMask(1);
    if(exitTimer < 45) outVel = 330;
    else outVel = 230;
    preparePID(outDir, outVel, 0);
    
    tone(30, LA3);
    keeper_backToGoalPost = true;
    keeper_tookTimer = true;
  }else{
    //fine rientro
    ballMask(0);
    linesensbyte = 0;
    linesensbyteOLDY = 0;
    linesensbyteOLDX = 0;
    noTone(30);
    //digitalWrite(Y, LOW);
    //digitalWrite(G, LOW);

    lineSensByteBak = 30;
  }

   lineSensByteBak = linesensbyte;
   if(exitTimer == 99) slow = true;
   else slow = false;
}

int ball = -1;
elapsedMillis mask;
elapsedMillis slowly;

void ballMask(int on) {
  float diffB;

  if(on) {
    ball = ball_degrees;
    mask = 0;
  }
  else {
    if(ball != -1) {
      if(inAngle(ball_degrees, ai, ar) == 0) {
        ball = -1;
        return;
      }
      else {
        if(mask < 500) preparePID(0, 0, 0);         //prima era 150
        else {
          ball = -1;
          return;
        }
      }
    } else return;
  }

}

void safetysafe() {
  if(slow)  slowly = 0;
  if(!slow) if(slowly < 600){
    if(ball_degrees > 45 && ball_degrees < 315) globalSpeed = globalSpeed / 1.4;
  }
}


void testLineSensors() {
  checkLineSensors();
  DEBUG_PRINT.println("______________");
  for(int i = 0; i<4; i++) {
    DEBUG_PRINT.print(linetriggerI[i]);
    DEBUG_PRINT.print("-");
    DEBUG_PRINT.print(linetriggerO[i]);
    DEBUG_PRINT.print(" | ");
  }
  DEBUG_PRINT.println();
  DEBUG_PRINT.print("________________");

  DEBUG_PRINT.println("Byte:    ");
  DEBUG_PRINT.print(linesensbyteO);
  DEBUG_PRINT.print("   Direzione:    ");
  DEBUG_PRINT.println(outDir);
  delay(150);

  DEBUG_PRINT.println("______________");
}
