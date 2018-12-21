#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <SPI.h>

#define BNO055_SAMPLERATE_DELAY_MS (60)

#define bluetooth  Serial3         // BT communication serial

//IR shield pin
#define BUZZER 27
#define SWITCH_SX 24
#define SWITCH_DX 25

//SPI pins
#define SS_PIN 2

//Linesensors
#define LN0 A14
#define LN1 A15
#define LN2 A7
#define LN3 A6
#define LN4 A9
#define LN5 A16

//Note
#define LA3 220.00
#define C4  261.63
#define F3  174.61
#define E6  1318.51
#define F6  1396.91
#define GB6 1479.98

//COSTANTI PER ATTACCANTE (GOALIE & MENAMOLI)-----------------------------
#define GOALIE_MAX 130
#define GOALIE_MIN 200
#define GOALIE_SLOW1 130
#define GOALIE_SLOW2 150
#define GOALIE_DANGER 100
#define VEL_RET 180
#define GOALIE_P 255 // velocità portiere
#define AA0  0   // angoli di attacco in funzione del sensore palla
#define AA1  30
#define AA2  60
#define AA3  80
#define AA4  90
#define AA5  120
#define AA6  130
#define AA7  160
#define AA8  170
#define AA9  999
#define AA10 999
#define AA11 999
#define AA12 190
#define AA13 200
#define AA14 230
#define AA15 240
#define AA16 270
#define AA17 280
#define AA18 300
#define AA19 337

//ZONE DEL CAMPO
#define EST           2        // codici utilizzabili per una matice 3x3
#define OVEST         0
#define CENTRO        1
#define NORD          0
#define SUD           2

#define NORD_OVEST    1
#define NORD_CENTRO   2
#define NORD_EST      3
#define CENTRO_OVEST  4
#define CENTRO_CENTRO 5        // codici zona nuovi
#define CENTRO_EST    6
#define SUD_OVEST     7
#define SUD_CENTRO    8
#define SUD_EST       9


// LIMITI DEL CAMPO
#define Lx_min 115            // valore minimo accettabile di larghezza
#define Lx_max 195            // valore massimo accettabile di larghezza (larghezza campo)
#define LyF_min 190           // valore minimo accettabile di lunghezza sulle fasce
#define LyF_max 270           // valore massimo accettabile di lunghezza sulle fasce (lunghezza campo)
#define LyP_min 139           // valore minimo accettabile di lunghezza tra le porte
#define LyP_max 250           // valore massimo accettabile di lunghezza tra le porte
#define DxF     48            // con misura x OK con us_dx o us_sx < DxF sto nelle fasce 30 + 30 - 1/2 robot
#define DyF     91            // con  misura y OK e robot a EST o A OVEST con us_fx o us_px < DyF sto a NORD o a SUD  era - 10
#define DyP     69            // con misura y OK e robot al CENTRO (tra le porte) con us_fx o us_px < DyP sto a NORD o a SUD era - 22
#define robot   21            // diametro del robot
