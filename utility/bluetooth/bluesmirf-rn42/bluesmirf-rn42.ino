/*
  Example Bluetooth Serial Passthrough Sketch
  by: Jim Lindblom
  SparkFun Electronics
  date: February 26, 2013
  license: Public domain

  This example sketch converts an RN-42 bluetooth module to
  communicate at 9600 bps (from 115200), and passes any serial
  data between Serial Monitor and bluetooth module.
*/
#include <SoftwareSerial.h>

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

//SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
<<<<<<< HEAD
=======

#define bluetooth Serial3
>>>>>>> 5c0171dd181357ae6f20ec98cb5c060f067c30fc

#define bluetooth Serial3

void setup() {
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
<<<<<<< HEAD
  
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
=======
  bluetooth.begin(9600);
>>>>>>> 5c0171dd181357ae6f20ec98cb5c060f067c30fc
}

void read() {
  while (bluetooth.available()) {
    // Send any characters the bluetooth prints to the serial monitor
    Serial.print((char)bluetooth.read());
    delay(50);
  }
}

void write() {
  while (Serial.available()) {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print((char)Serial.read());
    delay(50);
  }
  // and loop forever and ever!
}

void loop() {
  read();
  write();
}
