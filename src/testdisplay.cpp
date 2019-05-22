#include "testdisplay.h"
#include "vars.h"
#include <TM1637Display.h>

TM1637Display display(CLK, DIO);
  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };

void writeDigit(int place, int digit) {
    if(digit > 9) digit = 9;
    if(digit < 0) digit = 0;

    if(place < 0) place = 0;
    if(place > 3) place = 3;

    display.setBrightness(0x0f);
    
    data[place] = 0xff;

    // All segments on
    display.setSegments(data);

    // Selectively set different digits
    data[place] = display.encodeDigit(digit);
    display.setSegments(data);
}

void clearDisplay(){
    display.clear();    
}

void deepClearDisplay(){
    for(int i = 0; i < 4; i++){
        data[i] = blank[i];
    }
}