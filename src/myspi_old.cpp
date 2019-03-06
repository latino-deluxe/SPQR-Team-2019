#include "myspi_old.h"
#include "vars.h"
#include <Arduino.h>
#include <SPI.h>

SPISettings settings(100000, MSBFIRST, SPI_MODE0);

void initSPI() {
  pinMode(SS_PIN, OUTPUT);
  Serial.begin(9600);
  SPI.begin();

  digitalWrite(SS_PIN, HIGH);
}

void readSPI() {
  if (millis() - tspi > 10) {
    mess = 0;
    SPI.beginTransaction(settings);
    digitalWrite(SS_PIN, LOW);
    mess = SPI.transfer(255);
    digitalWrite(SS_PIN, HIGH);
    SPI.endTransaction();
    tspi = millis();
    if (mess == 255)
      return;
    ball_sensor = mess & 0b00011111;
    ball_distance = (mess & 0b11100000) >> 5;
  }
  return;
}

void ball_read_position() {
  // getting our data from our spi slave
  readSPI(); // in any other case the ball is seen by the robot
  ball_seen = true;
  if (ball_distance == 6) { // if the distance is 6 it means that the robot
                            // doesnt see the ball
    ball_seen = false;
  }

  if (old_s_ball != ball_sensor) {
    old_s_ball = ball_sensor;
    // how much time the same sensor sees the ball. Used in keeper
    time_s_ball = millis();
  }
  return;
}

void testBall() {
  ball_read_position();
  DEBUG_PRINT.print(ball_sensor);
  DEBUG_PRINT.print(" | ");
  DEBUG_PRINT.println(ball_distance);

  delay(500);
}

bool inSensorRange(byte sensor, byte range) {
  // BT.println(lineBallSensor);
  for (int i = 0; i <= range; i++) {
    // BT.print(getSensorIndex(sensor - i));
    // BT.print(" | ");
    // BT.println(getSensorIndex(sensor + i))
    if (ball_sensor == ((sensor + 20) - i) % 20 ||
        ball_sensor == ((sensor + 20) + i) % 20 ) {
      return true;
    }
  }
  return false;
}
