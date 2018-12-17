#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <SPI.h>

#define bluetooth  Serial3         // BT communication serial

//IR shield pin
#define PIN_PIEZO 22
#define SWITCH_SX 24
#define SWITCH_DX 25

//SPI pins
#define SS_PIN 2


#define LN1 A14
