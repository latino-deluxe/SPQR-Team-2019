/*SENSORS INTERPOLATION FOR BALL DETECTION. ARDUINO CODE BY Alessandro Mauri, PIC PORTING by Emanuele Coletta & Siria Sannino*/
#include <xc.h>
//#include <p18f2550.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "usart_custom.h"


#pragma config OSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = SBORDIS // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 2 // Brown Out Reset Voltage bits ()

// CONFIG2H
#pragma config WDT = OFF // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768 // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

// CONFIG4L
#pragma config STVREN = ON // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)


#define TOUT 100
#define DEBUG 1
#define THRL 30
#define THRH 253

void readSensors_old();

//byte tx_data = 0;
float tmp_y, tmp_x;
//int pins[] = {TRISB0, TRISB1, TRISB2, TRISB3, TRISB4, TRISB5, TRISB6, TRISB7, TRISC0, TRISC1, TRISC2, TRISC3}, t;
int t;
float vect[2], s_data[12], dist, angle, angle2;
const float sins[12] = {0, 0.5, 0.866, 1, 0.866, 0.5, 0, -0.5, -0.866, -1, -0.866, -0.5},
cosins[12] = {1, 0.866, 0.5, 0, -0.5, -0.866, -1, -0.866, -0.5, 0, 0.5, 0.866};

void main() {
    // Sets all pin of port B and C to output, except for C6, used for Serial communication
    TRISB = 0b11111111; //PORTB as Input
    TRISC = 0b10111111; //PORTC as Input    RC7 = RX, RC6 = TX

    // nRBPU = 0;    //Enables PORTB Internal Pull Up Resistors
    UART_Init(38400);

    do {
        //Read from sensors
        readSensors_old();
        //Bit of delay, should not be needed
        __delay_ms(100);
    } while (1);
}

void readSensors_old() {
    //Reades from sensors and constructs the array
    for (int i = 0; i < 255; i++) {
        s_data[0] += !LATBbits.LATB0;
        s_data[1] += !LATBbits.LATB1;
        s_data[2] += !LATBbits.LATB2;
        s_data[3] += !LATBbits.LATB3;
        s_data[4] += !LATBbits.LATB4;
        s_data[5] += !LATBbits.LATB5;
        s_data[6] += !LATBbits.LATB6;
        s_data[7] += !LATBbits.LATB7;
        s_data[8] += !LATCbits.LATC0;
        s_data[9] += !LATCbits.LATC1;
        s_data[10] += !LATCbits.LATC2;
        s_data[11] += !LATCbits.LATC3;
    }

    //printf("");

    //Calculation magic by Alessandro
    for (int i = 0; i < 12; i++) {
        //Fix some offsets
        if ((s_data[i] < THRL) || (s_data[i] > THRH)) {
            s_data[i] = 0;
        }
        
        //adds all the sins and cosins of each reading together
        tmp_y = (s_data[i] * sins[i]);
        tmp_x = (s_data[i] * cosins[i]);
        //vector construct
        vect[0] += tmp_y;
        vect[1] += tmp_x;
        //Reset the array index
        s_data[i] = 0;
    }

    angle = atan2(vect[0], vect[1]);
    angle = (angle * 4068) / 71;
    dist = sqrt((vect[0] * vect[0]) + (vect[1] * vect[1]));
    //cast from [-180, 180] to [0,360]. Thanks stack overflow :D
    angle = ((int) angle + 360) % 360;
     //divided for single-byte communication
    angle2 = angle / 2;
    //Resets the vector array
    vect[0] = 0;
    vect[1] = 0;
}

/*
Slave Code

#include <xc.h>
#include <pic16f877a.h>
#include "uart.h"
// BEGIN CONFIG
#pragma config FOSC = HS
#pragma config WDTE = OFF 
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF 
#pragma config CP = OFF 
//END CONFIG

void main()
{
  TRISB = 0x00; //PORTB as Output
  UART_Init(9600);

  do
  {
    if(UART_Data_Ready())
       PORTB = UART_Read();
    __delay_ms(100);
  }while(1);
}
 */
