#include "libs"

#define LA3 220.00
#define C4  261.63
#define F3  174.61

//Costanti durata note
#define BPM  240
#define H 2*Q                               //half 2/4
#define Q 60000/BPM                         //quarter 1/4
#define E Q/2                               //eighth 1/8
#define S Q/4                               //sixteenth 1/16
#define W 4*Q                               //whole 4/4
#define buzzer 22

void imperial_march() {
  /*tone(pin, note, duration)*/
  tone(buzzer, LA3, Q);
  delay(1 + Q / 2);            //delay duration should always be 1 ms more than the note in order to separate them.
  noTone(buzzer);
  delay(1 + Q / 2);
  tone(buzzer, LA3, Q);
  delay(1 + Q / 2);
  noTone(buzzer);
  delay(1 + Q / 2);
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
  delay(1 + S / 2);
  tone(buzzer, LA3, H);
  delay(1 + H / 2);
  noTone(buzzer);
  delay(1 + H / 2);
  noTone(buzzer);
}
