#include "Arduino.h"

void initMotorsGPIO();
void turnMotor(byte, byte, byte, byte);
void brake();
float torad(float);
void initOmnidirectionalSins();
void mot(byte, int);
void testMotors();
