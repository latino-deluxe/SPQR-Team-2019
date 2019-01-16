#include "Wire.h"
#include "us.h"
#include "vars.h"
#include <Arduino.h>

void initUS(){
    // Start I2C On Wire1 for US
    Wire1.begin();
}

void readUSTEST() {
  // test
  for (int i = 0; i < 4; i++) {       //  int i = 3;
                                      // step 1: instruct sensor to read echoes
    Wire1.beginTransmission(112 + i); // transmit to device #112 (0x70)
    Wire1.write(
        byte(0x00)); // sets register pointer to the command register (0x00)
    Wire1.write(byte(
        0x51)); // command sensor to measure in "inches" (0x50)
                // use 0x51 for centimeters or use 0x52 for ping microseconds
    Wire1.endTransmission(); // stop transmitting

    // step 2: wait for readings to happen
    delay(70); // datasheet suggests at least 65 milliseconds

    // step 3: instruct sensor to return a particular echo reading
    Wire1.beginTransmission(112 + i); // transmit to device #112
    Wire1.write(byte(0x02)); // sets regi#include "main.cpp"ster pointer to echo
                             // #1 register (0x02)
    Wire1.endTransmission(); // stop transmitting

    // step 4: request reading from sensor
    Wire1.requestFrom(112 + i, 2); // request 2 bytes from slave device #112

    // step 5: receive reading from sensor
    if (2 <= Wire1.available()) { // if two bytes were received
      reading =
          Wire1.read(); // receive high byte (overwrites  previous reading)
      reading = reading << 8;  // shift high byte to be high 8 bits
      reading |= Wire1.read(); // receive low byte as lower 8 bit
      us_values[i] = reading;  // test
                               //  Serial.println(reading);
                               //  delay(1500);
    }
  }

  us_fr = us_values[0]; // putting US values into declared array index
  us_dx = us_values[1];
  us_px = us_values[2];
  us_sx = us_values[3];

  // altenative test
  Serial.println("---------------------");
  for (int i = 0; i < 4; i++) {
    Serial.println(us_values[i]);
    delay(250);
  }
  Serial.println("---------------------");
}

void us_trigger() {
    for (int i = 0; i < 4; i++) {       //  int i = 3;
                                        // step 1: instruct sensor to read echoes
      Wire1.beginTransmission(112 + i); // transmit to device #112 (0x70)
      Wire1.write(byte(0x00)); // sets register pointer to the command register (0x00)
      Wire1.write(byte(  0x51)); // command sensor to measure in "inches" (0x50)
                                // use 0x51 for centimeters or use 0x52 for ping microseconds
      Wire1.endTransmission(); // stop transmitting
  }
}



void us_scheduling() {
  if (us_flag == false) {
    us_trigger();
    us_flag = true;
    us_t0 = millis();
  }
  else {
    us_t1 = millis();
    if ((us_t1 - us_t0) > 70) {
      us_receive();
      us_flag = false;
    }
  }
}

void us_receive() {

  for (byte i = 0; i < 4; i++) {

    Wire1.beginTransmission(112 + i); // transmit to device #112
    Wire1.write(byte(0x02)); // sets regi#include "main.cpp"ster pointer to echo
                             // #1 register (0x02)
    Wire1.endTransmission(); // stop transmitting

    // step 4: request reading from sensor
    Wire1.requestFrom(112 + i, 2); // request 2 bytes from slave device #112

    // step 5: receive reading from sensor
      reading = Wire1.read(); // receive high byte (overwrites  previous reading)
      reading = reading << 8;  // shift high byte to be high 8 bits
      reading |= Wire1.read(); // receive low byte as lower 8 bit
      us_values[i] = reading;  // test
                               //  Serial.println(reading);
                               //  delay(1500);
  }
}



void readUS() {
  us_scheduling();
  us_fr = us_values[0]; // FRONT US
  us_dx = us_values[1]; // DX US
  us_px = us_values[2]; // BACK US
  us_sx = us_values[3]; // SX US
}
