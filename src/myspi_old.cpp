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
    ball_distance =
        (mess & 0b11100000) >> 5; // unica differenza con readspi vecchio codice
  }
  return;
}

void ball_read_position() {
  readSPI();        // getting our data from our spi slave
  ball_seen = true; // in any other case the ball is seen by the robot
  if (ball_distance == 6) {
    ball_seen = false; // if the distance is 6 it means that the robot doesnt
                       // see the ball
  }

  if (old_s_ball != ball_sensor) {
    old_s_ball = ball_sensor;
    time_s_ball = millis(); // per quanto tempo lo stesso sensore vede la palla
                            // >usata in keeper e non in goalie<
  }
  return;
}

void testBall() {
  ball_read_position();
  Serial.print(ball_sensor);
  Serial.print(" | ");
  Serial.println(ball_distance);

  delay(500);
}
