#include <Arduino.h>

void initSPI();
void readSPI();
void ball_read_position();
void testBall();
byte getSensorIndex(byte);
bool inSensorRange(byte, byte);
