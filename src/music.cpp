#include "vars.h"

void imperial_march() {
  // tone(pin, note, duration)
  tone(buzzer, LA3, Q);
  delay(1 + Q / 2); // delay duration should always be 1 ms more than the note
                    // in order to separate them.
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

void super_mario() {
  tone(buzzer, 660, 100);
  delay(150);
  tone(buzzer, 660, 100);
  delay(300);
  tone(buzzer, 660, 100);
  delay(300);
  tone(buzzer, 510, 100);
  delay(100);
  tone(buzzer, 660, 100);
  delay(300);
  tone(buzzer, 770, 100);
  delay(550);
  tone(buzzer, 3160, 100);
  delay(575);
}

void startSetup() {
  tone(buzzer, LA3, 100);
  tone(buzzer, LA3, 100);
  tone(buzzer, LA5, 100);
}

void stopSetup() {
  tone(buzzer, LA5, 100);
  tone(buzzer, LA5, 100);
  tone(buzzer, LA2, 100);
}
e E6 1318.51
#define F6 1396.91
#define Gb6 1479.98
#define G6 1567.98
#define Ab6 1661.22
#define LA6 1760.00
#define Bb6 1864.66
#define B6 1975.53
#define C7 2093.00
#define Db7 2217.46
#define D7 2349.32
#define Eb7 2489.02
#define E7 2637.02
#define F7 2793.83
#define Gb7 2959.96
#define G7 3135.96
#define Ab7 3322.44
#define LA7 3520.01
#define Bb7 3729.31
#define B7 3951.07
#define C8 4186.01
#define Db8 4434.92
#define D8 4698.64
#define Eb8 4978.03
// Costanti durata note
#define BPM 240
#define H 2 * Q       // half 2/4
#define Q 60000 / BPM // quarter 1/4
#define E Q / 2       // eighth 1/8
#define S Q / 4       // sixteenth 1/16
#define W 4 * Q       // whole 4/4

#define buzzer 27

    void
    imperial_march();
void super_mario();
void startSetup();
void stopSetup();
