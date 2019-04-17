#include "bluetooth.h"
#include "goalie.h"
#include "imu.h"
#include "motors.h"
#include "myspi_old.h"
#include "pid.h"
#include "position.h"
#include "us.h"
#include "vars.h"
#include <Arduino.h>

int testDelay = 10;

void testMenu() {
  brake();

  Serial.println();
  Serial.println("Velocitá 9600 e NESSUN FINE RIGA >no LF<");
  Serial.println(
      "Digitare il test (1-->7) da eseguire e premere ENTER >no LF<");
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
  Serial.println("9)Test Storcimento Camera Incrementale");

  do {
    test = Serial.read();
    Serial.println();
    Serial.print("Test ");
    Serial.print(test);
    Serial.println(" ");

    if (test == '0')
      Serial.println("Esce dal test e torna a giocare");
    else if (test == '1')
      Serial.println("Test Palla, accendere la palla e girarla tra i sensori");
    else if (test == '2')
      Serial.println("Test US, tenere il robot fermo ed in piano");
    else if (test == '3')
      Serial.println("Test IMU, tenere il robot in piano");
    else if (test == '4')
      Serial.println("Test Motori, accendere I MOTORI e tenerlo sospeso");
    else if (test == '5')
      Serial.println("Recenter, accendere il robot e storcerlo");
    else if (test == '6')
      Serial.println("Test BT, connettersi al BT");
    else if (test == '7')
      Serial.println("GigaTestZone, test grafico matrice zone (1-->9), US, IMU "
                     "e zona compagno (se presente)");
    else if (test == '8')
      Serial.println("CAMERA");
    else if (test == '9')
      Serial.println("Storcimento Camera Incrementale");
    else {
      Serial.println(" Comando sconosciuto");
      flagtest = false;
    }
  } while (Serial.available() > 0);

  do {
    switch (test) {
    case '0':
      Serial.println("Fine test");
      flagtest = false;
      return;
      break;
    case '1': // test palla
      testBall();
      delay(testDelay);
      break;
    case '2': // test us
      testUS();
      delay(testDelay);
      break;
    case '3': // test imu
      testIMU();
      delay(testDelay);
      break;
    case '4': // test motori
      testMotors();
      delay(testDelay);
      break;
    case '5': // test recenter
      readIMU();
      delay(5);
      drivePID(0, 0);
      // delay(testDelay);
      break;
    case '6': // test bt
      testBluetooth();
      delay(testDelay);
      break;
    case '7': // gigaTestZone
      gigaTestZone();
      delay(10);
      break;
    case '8':
      Serial.println(portx);
      delay(100);
      break;
    case '9':
      storcimentoPortaIncr();
      preparePID(0, 0, stincr);
      break;
    default: // default, todo, maybe
      break;
    }
  } while (Serial.available() == 0);
}
