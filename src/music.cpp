#include "vars.h"
#include "music.h"

void imperial_march() {
  //tone(pin, note, duration)
  tone(buzzer, LA3, Q);
  delay(1 + Q / 2); //delay duration should always be 1 ms more than the note in order to separate them.
  noTone(buzzer);
  delay(1 + Q / 2);
  tone(buzzer, LA3, Q);
  delay(1 + Q/2);
  noTone(buzzer);
  delay(1 + Q / 2);
  tone(buzzer, LA3, Q);
  delay(1 + Q/2);
  noTone(buzzer);
  delay(1 + Q / 2);
  tone(buzzer, F3, E + S);
  delay(1 + (E + S) / 2);
  noTone(buzzer);
  delay(1 + (E + S) / 2);
  tone(buzzer, C4, S);
  delay(1 + S / 2);
  noTone(buzzer);
  delay(1 + S / 2);
  tone(buzzer, LA3, Q);
  delay(1 + Q / 2);
  noTone(buzzer);
  delay(1 + Q / 2);
  tone(buzzer, F3, E + S);
  delay(1 + (E + S) / 2);
  noTone(buzzer);
  delay(1 + (E + S) / 2);
  tone(buzzer, C4, S);
  delay(1 + S / 2);
  noTone(buzzer);
  delay(1+S/2);
  tone(buzzer, LA3, H);
  delay(1 + H/2);
  noTone(buzzer);
  delay(1 + H/2);
  noTone(buzzer);
}

void super_mario() {
  tone(buzzer, 660 ,100);
  delay ( 150);
  tone(buzzer, 660 ,100);
  delay ( 300);
  tone(buzzer, 660 ,100);
  delay ( 300);
  tone(buzzer, 510 ,100);
  delay ( 100);
  tone(buzzer, 660 ,100);
  delay ( 300);
  tone(buzzer, 770 ,100);
  delay ( 550);
  tone(buzzer, 3160 ,100);
  delay ( 575);
}

void startSetup(){
  tone(30, LA3, 100);
  delay (100);
  noTone(30);
  tone(30, LA3, 100);
  delay (100);
  noTone(30);
  tone(30, LA5, 100);
  delay (100);
  noTone(303);
}

void stopSetup() {
  tone(30, LA5, 100);
  delay (100);
  noTone(30);
  tone(30, LA5, 100);
  delay (100);
  noTone(30);
  tone(30, LA2, 100);
  delay (100);
  noTone(30);
}

void miiChannel() {
  tone(buzzer, F3, 500);
  delay(500);
  noTone(buzzer);
  tone(buzzer, LA3, 200);
  delay(200);
  noTone(buzzer);
  tone(buzzer, B5, 600);
  delay(600);
  noTone(buzzer);
  tone(buzzer, LA3, 450);
  delay(450);
  noTone(buzzer);
  tone(buzzer, F3, 500);
  delay(500);
  noTone(buzzer);
  tone(buzzer, C2, 350);
  delay(350);
  noTone(buzzer);
  tone(buzzer, C2, 350);
  delay(350);
  noTone(buzzer);
  tone(buzzer, C2, 350);
  delay(350);
  noTone(buzzer);
}
