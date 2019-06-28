#include <Arduino.h>
#include "vars.h"
#include "chat.h"
#include "us.h"
#include "bluetooth.h"
#include "nano_ball.h"
#include "goalie.h"
#include "camera.h"
#include "position.h"
#include "imu.h"
#include "motors.h"
#include "pid.h"
#include "position.h"
#include "linesensor.h"

int testDelay = 10;
elapsedMillis ao3 = 0;

void testMenu(){
  brake();

  DEBUG_PRINT.println();
  DEBUG_PRINT.println("Velocitá 9600 e NESSUN FINE RIGA >no LF<");
  DEBUG_PRINT.println("Digitare il test (1-->7) da eseguire e premere ENTER >no LF<");
  DEBUG_PRINT.println("Digitare 0 per uscire dai test >no LF<");
  DEBUG_PRINT.println();

  DEBUG_PRINT.println("Test Menu: ");
  DEBUG_PRINT.println("0)Esci dai test e gioca");
  DEBUG_PRINT.println("1)Test Palla");
  DEBUG_PRINT.println("2)Test US");
  DEBUG_PRINT.println("3)Test IMU");
  DEBUG_PRINT.println("4)Test Motori");
  DEBUG_PRINT.println("5)Recenter");
  DEBUG_PRINT.println("6)Test BT");
  DEBUG_PRINT.println("7)GigaTestZone");
  DEBUG_PRINT.println("8)Test Camera");
  DEBUG_PRINT.println("9)Test Sensori Linea");

  do{
    test = DEBUG_PRINT.read();
    DEBUG_PRINT.println();
    DEBUG_PRINT.print("Test "); DEBUG_PRINT.print(test); DEBUG_PRINT.println(" ");

    if (test == '0') DEBUG_PRINT.println("Esce dal test e torna a giocare");
    else if (test == '1') DEBUG_PRINT.println("Test Palla, accendere la palla e girarla tra i sensori");
    else if (test == '2') DEBUG_PRINT.println("Test US, tenere il robot fermo ed in piano");
    else if (test == '3') DEBUG_PRINT.println("Test IMU, tenere il robot in piano");
    else if (test == '4') DEBUG_PRINT.println("Test Motori, accendere I MOTORI e tenerlo sospeso");
    else if (test == '5') DEBUG_PRINT.println("Recenter, accendere il robot e storcerlo");
    else if (test == '6') DEBUG_PRINT.println("Test BT, connettersi al BT");
    else if (test == '7') DEBUG_PRINT.println("GigaTestZone, test grafico matrice zone (1-->9), US, IMU e zona compagno (se presente)");
    else if (test == '8') DEBUG_PRINT.println("CAMERA");
    else if (test == '9') DEBUG_PRINT.println("Linee");
    else if (test == 'l') DEBUG_PRINT.println("Taratura Linee");

    else {
      DEBUG_PRINT.println(" Comando sconosciuto");
      flagtest = false;
    }
  }  while (DEBUG_PRINT.available() > 0);

  do{
    switch(test){
      case '0':
        DEBUG_PRINT.println("Fine test");
        flagtest = false;
        return;
      break;
      case '1'://test palla
        testBallNano();
        delay(testDelay);
      break;
      case '2'://test us
        testUS();
        delay(testDelay);
      break;
      case '3'://test imu
        testIMU();
        delay(testDelay);
      break;
      case '4'://test motori
        testMotors();
        delay(testDelay);
      break;
      case '5'://test recenter
        readIMU();
        delay(5);
        drivePID(0,0);
        //delay(testDelay);
      break;
      case '6'://test bt
        testBluetooth();
        delay(testDelay);
      break;
      case '7'://gigaTestZone
        gigaTestZone();
        delay(10);
      break;
      case '8':
        goal_orientation = digitalRead(SWITCH_SX);     //se HIGH attacco gialla, difendo blu
        goalPosition();
        readIMU();

        DEBUG_PRINT.print(pAtk);
        DEBUG_PRINT.print(" | ");
        DEBUG_PRINT.print(fixCamIMU(pAtk));

        DEBUG_PRINT.print(" --- ");

        DEBUG_PRINT.print(pDef);
        DEBUG_PRINT.print(" | ");
        DEBUG_PRINT.println(fixCamIMU(pDef));
        // DEBUG_PRINT.print("  | Delta:  ");;
        // DEBUG_PRINT.println(delta);
        delay(100);
      break;
      case '9':
        // testLineSensors();
      break;
      case 'l':
        DEBUG_PRINT.print("Sensore 1 In - Out");
        DEBUG_PRINT.print(analogRead(S1I));
        DEBUG_PRINT.print(" | ");
        DEBUG_PRINT.println(analogRead(S1O));
        DEBUG_PRINT.print("Sensore 2 In - Out");
        DEBUG_PRINT.print(analogRead(S2I));
        DEBUG_PRINT.print(" | ");
        DEBUG_PRINT.println(analogRead(S2O));
        DEBUG_PRINT.print("Sensore 3 In - Out");
        DEBUG_PRINT.print(analogRead(S3I));
        DEBUG_PRINT.print(" | ");
        DEBUG_PRINT.println(analogRead(S3O));
        DEBUG_PRINT.print("Sensore 4 In - Out");
        DEBUG_PRINT.print(analogRead(S4I));
        DEBUG_PRINT.print(" | ");
        DEBUG_PRINT.print(analogRead(S4O));
        DEBUG_PRINT.print("\n--------------------------");
        DEBUG_PRINT.println(" ");
        delay(100);
      break;
      default://default, todo, maybe
      break;
      case 'b':
        goalPosition();
        if(cameraReady == 1) {
          storcimentoPorta();
          calcPhyZoneCam = true;
          cameraReady = 0;
        }
        calculateLogicZone();
        
        Ao();
        friendo(500);
        
        if(ao3 >= 200){
          Serial.print(comrade);
          Serial.print(" | ");
          Serial.println(friendZone);
          ao3 = 0;
        }
        
      break;
    }
  } while (DEBUG_PRINT.available() == 0);
}



/* 
  elapsedMicros t1,t2,t3,t4,t5,t6,t7,t8,t9;

  role = digitalRead(SWITCH_DX);                //se HIGH sono attaccante
  goal_orientation = digitalRead(SWITCH_SX);     //se HIGH attacco gialla, difendo blu

  if(Serial.available() > 0) testMenu();

  Serial.print("IMU");
  t1 = 0;
  readIMU();
  Serial.print(t1);
  Serial.print("| US  |");
  t2 = 0;
  readUS();
  Serial.print(t2);
  Serial.print("| NANO  |");
  t3 = 0;
  readBallNano();
  Serial.print(t3);
  Serial.print("| CAMERA  |");
  t4 = 0;
  goalPosition();
  Serial.print(t4);
  Serial.print("| STORCIMENTO |");
  t5 = 0;
  if(cameraReady == 1) {
    storcimentoPorta();
    calcPhyZoneCam = true;
    cameraReady = 0;
  }
  Serial.print(t5);
  Serial.print("| ZONA LOGICA |");
  t6 = 0;
  calculateLogicZone();
  Serial.print(t6);
  Serial.print("| GIOCO |");
  t7 = 0;
  if(ball_seen){
    if(role) goalie();
    else keeper();
  } else {
    if(role) preparePID(0, 0, 0);
    else centerGoalPost();
  }
  Serial.print(t7);
  Serial.print("| LINESENSOR  |");
  t8 = 0;
  checkLineSensors();                           //Last thing in loop, for priority
  Serial.print(t8);
  Serial.print("| SAFETYSAFE  |");
  t9 = 0;
  safetysafe();
  Serial.println(t9);


*/