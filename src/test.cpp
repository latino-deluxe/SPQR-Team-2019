#include <Arduino.h>
#include "vars.h"
#include "us.h"
#include "bluetooth.h"
#include "nano_ball.h"
#include "camera.h"
#include "position.h"
#include "imu.h"
#include "motors.h"
#include "pid.h"
#include "linesensor.h"

int testDelay = 10;

void testMenu(){
  brake();

  Serial.println();
  Serial.println("Velocitá 9600 e NESSUN FINE RIGA >no LF<");
  Serial.println("Digitare il test (1-->7) da eseguire e premere ENTER >no LF<");
  Serial.println("Digitare 0 per uscire dai test >no LF<");
  Serial.println();

  Serial.println("Test Menu: ");
  Serial.println("0)Esci dai test e gioca");
  Serial.println("1)Test Palla");
  Serial.println("2)Test US");
  Serial.println("3)Test IMU");
  Serial.println("4)Test Motori");
  Serial.println("5)Recenter");
  Serial.println("6)Test BT");
  Serial.println("7)GigaTestZone");
  Serial.println("8)Test Camera");
  Serial.println("9)Test Sensori Linea");

  do{
    test = Serial.read();
    Serial.println();
    Serial.print("Test "); Serial.print(test); Serial.println(" ");

    if (test == '0') Serial.println("Esce dal test e torna a giocare");
    else if (test == '1') Serial.println("Test Palla, accendere la palla e girarla tra i sensori");
    else if (test == '2') Serial.println("Test US, tenere il robot fermo ed in piano");
    else if (test == '3') Serial.println("Test IMU, tenere il robot in piano");
    else if (test == '4') Serial.println("Test Motori, accendere I MOTORI e tenerlo sospeso");
    else if (test == '5') Serial.println("Recenter, accendere il robot e storcerlo");
    else if (test == '6') Serial.println("Test BT, connettersi al BT");
    else if (test == '7') Serial.println("GigaTestZone, test grafico matrice zone (1-->9), US, IMU e zona compagno (se presente)");
    else if (test == '8') Serial.println("CAMERA");
    else if (test == '9') Serial.println("Linee");
    else if (test == 'l') Serial.println("Taratura Linee");

    else {
      Serial.println(" Comando sconosciuto");
      flagtest = false;
    }
  }  while (Serial.available() > 0);

  do{
    switch(test){
      case '0':
        Serial.println("Fine test");
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

        Serial.print(pAtk);
        Serial.print(" | ");
        Serial.print(fixCamIMU(pAtk));

        Serial.print(" --- ");

        Serial.print(pDef);
        Serial.print(" | ");
        Serial.println(fixCamIMU(pDef));
        // Serial.print("  | Delta:  ");;
        // Serial.println(delta);
        delay(100);
      break;
      case '9':
        testLineSensors();
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
    }
  } while (Serial.available() == 0);
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