#include <Arduino.h>
#include "vars.h"
#include "us.h"
#include "bluetooth.h"
#include "myspi_old.h"
#include "position.h"
#include "imu.h"
#include "motors.h"
#include "pid.h"

void testMenu(){
  brake();

  Serial.println();
  Serial.println("Velocitá 115200 e NESSUN FINE RIGA >no LF<");
  Serial.println("Digitare il test (1-->7) da eseguire e premere ENTER >no LF<");
  Serial.println("Digitare 0 per uscire dai test >no LF<");
  Serial.println();

  Serial.println("Test Menu: ");
  Serial.println("1)Test Palla");
  Serial.println("2)Test US");
  Serial.println("3)Test IMU");
  Serial.println("4)Test Motori");
  Serial.println("5)Recenter");
  Serial.println("6)Test BT");
  Serial.println("7)GigaTestZone");

  do{
    test = Serial.read();
    Serial.println();
    Serial.print("Test"); Serial.print(char(test));

    if (test == '0') Serial.println("Esce dal test e torna a giocare");
    if (test == '1') Serial.println("Test Palla, accendere la palla e girarla tra i sensori");
    if (test == '2') Serial.println("Test US, tenere il robot fermo ed in piano");
    if (test == '3') Serial.println("Test IMU, tenere il robot in piano");
    if (test == '4') Serial.println("Test Motori, accendere I MOTORI e tenerlo sospeso");
    if (test == '5') Serial.println("Recenter, accendere il robot e storcerlo");
    if (test == '6') Serial.println("Test BT, connettersi al BT");
    if (test == '7') Serial.println("GigaTestZone, test grafico matrice zone (1-->9), US, IMU e zona compagno (se presente)");
  }  while (Serial.available() == 0);

  do{
    switch(test){
      case '0':
        Serial.println("Fine test");
        flagtest = false;
        return;
      break;
      case '1'://test palla
        testBall();
        delay(1500);
      break;
      case '2'://test us
        testUS();
        delay(1500);
      break;
      case '3'://test imu
        testIMU();
        delay(1500);
      break;
      case '4'://test motori
        testMotors();
        delay(1500);
      break;
      case '5'://test recenter
        preparePID(0,0);
        delay(1500);
      break;
      case '6'://test bt
        testBluetooth();
        delay(1500);
      break;
      case '7'://gigaTestZone
        gigaTestZone();
        delay(1500);
      break;
      default://default, todo, maybe
      break;
    }
  } while (Serial.available() == 0);
}
