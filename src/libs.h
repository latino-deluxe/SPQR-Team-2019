#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <SPI.h>

#define bluetooth  Serial3         // BT communication serial

//IR shield pin
#define BUZZER 27
#define SWITCH_SX 24
#define SWITCH_DX 25

//SPI pins
#define SS_PIN 2


#define LN1 A14
#define LN2 A15
#define LN3 A0
#define LN4 A1
#define LN5 A2
#define LN6 A3

#define LA3 220.00
#define C4  261.63
#define F3  174.61
#define E6  1318.51
#define F6  1396.91
#define GB6 1479.98

//COSTANTI PER ATTACCANTE (GOALIE & MENAMOLI)-----------------------------
#define GOALIE_MAX 130
#define GOALIE_MIN 200
#define GOALIE_SLOW1 130
#define GOALIE_SLOW2 150
#define GOALIE_DANGER 100
#define VEL_RET 180
#define GOALIE_P 255 // velocità portiere
#define AA0  0   // angoli di attacco in funzione del sensore palla
#define AA1  30
#define AA2  60
#define AA3  80
#define AA4  90
#define AA5  120
#define AA6  130
#define AA7  160
#define AA8  170
#define AA9  999
#define AA10 999
#define AA11 999
#define AA12 190
#define AA13 200
#define AA14 230
#define AA15 240
#define AA16 270
#define AA17 280
#define AA18 300
#define AA19 337
