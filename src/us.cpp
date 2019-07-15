#include "Wire.h"
#include "us.h"
#include "vars.h"
#include <Arduino.h>

// Start I2C On Wire1 for US
void initUS() { Wire1.begin(); }

void testUS() {
  // test from srf02_example
  for (int i = 0; i < 4; i++) {
    // step 1: instruct sensor to read echoes
    // transmit to device #112 (0x70)
    Wire1.beginTransmission(112 + i);
    // sets register pointer to the command register (0x00)
    Wire1.write(byte(0x00));
    // command sensor to measure in "centimeters" (0x51). 0x50 inches and 0x52
    // microseconds
    Wire1.write(byte(0x51));
    // stop transmitting
    Wire1.endTransmission();
    // step 2: wait for readings to happen
    // datasheet suggests at least 65 milliseconds
    delay(70);

    // step 3: instruct sensor to return a particular echo reading
    // transmit to device #112
    Wire1.beginTransmission(112 + i);
    // sets register pointer to echo #1 register (0x02)
    Wire1.write(byte(0x02));
    Wire1.endTransmission();

    // step 4: request reading from sensor
    // request 2 bytes from slave device #112
    Wire1.requestFrom(112 + i, 2);

    // step 5: receive reading from sensor
    if (2 <= Wire1.available()) {
      // if two bytes were received
      // receive high byte (overwrites  previous reading)
      reading = Wire1.read();
      // shift high byte to be high 8 bits
      reading = reading << 8;
      // receive low byte as lower 8 bit
      reading |= Wire1.read();
      us_values[i] = reading;
    }
  }

  // putting US values into declared array index
  us_fr = us_values[0];
  us_dx = us_values[1];
  us_px = us_values[2];
  us_sx = us_values[3];

  // test
  Serial.println("---------------------");
  for (int i = 0; i < 4; i++) {
    Serial.println(us_values[i]);
    delay(250);
  }
  Serial.println("---------------------");
}

void us_trigger() {
  for (int i = 0; i < 4; i++) {
    // step 1: instruct sensor to read echoes
    // transmit to device #112 (0x70)
    Wire1.beginTransmission(112 + i);
    // sets register pointer to the command register (0x00)
    Wire1.write(byte(0x00));
    // command sensor to measure in "centimeters" (0x51). 0x50 inches and 0x52
    // microseconds
    Wire1.write(byte(0x51));
    Wire1.endTransmission();
  }
}

void us_scheduling() {
  if (us_flag == false) {
    us_trigger();
    us_flag = true;
    us_t0 = millis();
  } else {
    us_t1 = millis();
    if ((us_t1 - us_t0) > 70) {
      us_receive();
      us_flag = false;
    }
  }
}

void us_receive() {

  for (byte i = 0; i < 4; i++) {
    // transmit to device #112s

    Wire1.beginTransmission(112 + i);
    // sets register pointer to echo 1 register(0x02)
    Wire1.write(byte(0x02));
    Wire1.endTransmission();

    // step 4: request reading from sensor
    // request 2 bytes from slave device #112
    Wire1.requestFrom(112 + i, 2);

    // step 5: receive reading from sensor
    // receive high byte (overwrites  previous reading)
    reading = Wire1.read();
    // shift high byte to be high 8 bits
    reading = reading << 8;
    // receive low byte as lower 8 bit
    reading |= Wire1.read();
    us_values[i] = reading;
  }
}

void readUS() {
  us_scheduling();
  us_fr = us_values[0]; // FRONT US
  us_dx = us_values[1]; // DX US
  us_px = us_values[2]; // BACK US
  us_sx = us_values[3]; // SX US
}
