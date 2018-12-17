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
