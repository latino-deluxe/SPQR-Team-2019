#include <SoftwareSerial.h>

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
void setup() {
  Serial.begin(9600);
  Serial.print("$");
  Serial.print("$");
  Serial.print("$");
  delay(1000);
  Serial.println("SF,1");
  delay(500);
  Serial.println("R,1");
  delay(2500);
  Serial.println("---");
  //bluetooth.begin(9600);
}

void read() {
  if (bluetooth.available()) {
    // Send any characters the bluetooth prints to the serial monitor
    Serial.print((char)bluetooth.read());
    delay(75);
  }
}

void write() {
  if (Serial.available()) {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print((char)Serial.read());
    delay(75);
  }
  // and loop forever and ever!
}

void loop() {
  read();
  write();
}
