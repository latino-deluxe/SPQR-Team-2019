#include <Arduino.h>
#ifndef MAIN
#define extr extern
#else
#define extr
#endif

// IR shield pin
#define BUZZER 27
#define SWITCH_SX 26
#define SWITCH_DX 28

// Notes
#define LA3 220.00
#define C4 261.63
#define F3 174.61
#define E6 1318.51
#define F6 1396.91
#define GB6 1479.98

// You can modify this if you need
// LIMITI DEL CAMPO (CAMP LIMITS)
#define Lx_min 115  // min acceptable value for field width
#define Lx_max 195  // max acceptable value for field width
#define LyF_min 190 // valore minimo accettabile di lunghezza sulle fasce
#define LyF_max 270
// valore massimo accettabile di lunghezza sulle fasce (lunghezza campo)
#define LyP_min 139 // valore minimo accettabile di lunghezza tra le porte
#define LyP_max 250
// valore massimo accettabile di lunghezza tra le porte// con misura x OK
// con us_dx o us_sx < DxF sto nelle fasce 30 + 30 - 1/2
// robot
#define DxF 48
// con  misura y OK e robot a EST o A OVEST con us_fx o us_px < DyF sto a
// NORD o a SUD  era - 10
#define DyF 91
// con misura y OK e robot al CENTRO (tra le porte) con us_fx o us_px < DyP
// sto a NORD o a SUD era - 22
#define DyP 69
#define robot 21 // robot's diameter

// ZONE DEL CAMPO // codici utilizzabili per una matice 3x3
#define EAST 2     //ex EST
#define WEST 0   //ex OVEST
#define CENTER 1  //ex CENTRO
#define NORTH 0    //ex NORD
#define SOUTH 2     //ex SUD

#define NORTH_WEST 1                          //ex NORD_OVEST
#define NORTH_CENTER 2                        //ex NORD_CENTRO
#define NORTH_EAST 3                          //ex NORD_EST
#define CENTER_WEST 4                         //ex CENTRO_OVEST
#define CENTER_CENTER 5                       //ex CENTRO_CENTRO
#define CENTER_EAST 6   // (NEW ZONE CODES)   //ex CENTRO_EST
#define SOUTH_WEST 7                          //ex SUD_OVEST
#define SOUTH_CENTER 8                        //ex SUD_CENTRO
#define SOUTH_EAST 9                          //ex SUD_EST

// PID, VARS AND COSTANSTS
#define KP 0.7   // Proportional K
#define KI 0.001 // Integrative K
#define KD 0.001 // Derivate K

// SPI - will be soon deprecated
#define SS_PIN 2

// Linesensors and interrupt
#define LN0 A14
#define LN1 A15
#define LN2 A7
#define LN3 A6
#define LN4 A9
#define LN5 A16
#define INT_LUNG 6

#define BNO055_SAMPLERATE_DELAY_MS (60)

// GOALIE'S CONSTANTS (GOALIE & MENAMOLI)-----------------------------
#define GOALIE_MAX 130
#define GOALIE_MIN 200
#define GOALIE_SLOW1 130
#define GOALIE_SLOW2 150
#define GOALIE_DANGER 100
#define VEL_RET 180
#define GOALIE_P 255   // keeper's speed
//angles to attack from ball sensor
#define AA0 0
#define AA1 30
#define AA2 60
#define AA3 80
#define AA4 90
#define AA5 120
#define AA6 130
#define AA7 160
#define AA8 180
#define AA9 135
#define AA10 135
#define AA11 135
#define AA12 180
#define AA13 200
#define AA14 230
#define AA15 240
#define AA16 280
#define AA17 280
#define AA18 300
#define AA19 330

#define BT Serial1

#define DEBUG_PRINT BT

// IMU
extr int imu_temp_euler, imu_current_euler;

// Line Sensors
extr byte lineReading;
extr byte n_us;     // ultr
extr volatile byte lineSensors[INT_LUNG];
extr int VL_INT;    // velocitá di uscita dalle linee
extr int EXT_LINEA; // direzione di uscita dalla lineaasuono da controllare dopo la fuga dalla linea
extr int waiting;    // ex attesa tempo di attesa palla dopo un interrupt (utilizzata dallo
                    // switch destro)
extr bool danger;   // avviso che terminata da poco la gestione interrupt
extr unsigned long
    tdanger;        // misura il tempo dal termine della gestione interrupt

// Motors
extr float speed1, speed2, speed3, pidfactor, sins[360];

// MySPI
extr byte mess, ball_sensor, ball_distance, old_s_ball, ball_degrees;
extr long time_s_ball, tspi;
extr bool ball_seen;

// PID
extr float errorePre;    // previous error angle
extr float integral;     // somisa degli angoli di errore
extr bool reaching_ball; // serve per aumentare il PID del 20% GOALIE
extr int st;             // storcimento sulle fasce
// da utilizzare per sviluppi futuri
extr signed int old_Dir; // angolo di direzione precedente a quella attuale
extr signed int new_Dir; // angolo di direzione corrente del moto
extr float old_vMot;     // previous motion speed
extr float new_vMot;     // current motion speed

// US
extr int reading;
extr long us_t0;                     // US measure start
extr long us_t1;                     // time value during measure
extr bool us_flag;                   // is it measuring or not?
extr int us_values[4];               // US values array
extr int us_sx, us_dx, us_px, us_fr; // copies with other names in the array

// POSITION
extr int old_status_x;  // posizione precedente nel campo vale EST, OVEST o
                        // CENTRO o 255 >USI FUTURI<
extr int old_status_y;  // posizione precedente nel campo vale SUD, NORD o
                        // CENTRO o 255 >USI FUTURI<
extr bool goal_zone;    // sto al centro rispetto alle porte
                        // assigned by WhereAmI but unused
extr bool good_field_x; // vedo tutta la larghezza del campo si/no
extr bool good_field_y; // vedo tutta la lunghezza del campo si/no
extr int status_x;      // posizione nel campo vale EST, OVEST o CENTRO o 255
extr int status_y;      // posizione nel campo vale SUD, NORD o CENTRO o 255
extr int guessed_x, guessed_y;
extr int zoneIndex;

// extr int currentlocation; // risultato misure zone campo da 1 a 9 o 255 se
//                           // undefined
// extr int guessedlocation; // risultato misure zone campo da 1 a 9 (da
// CENTER_CENTER a SOUTH_WEST)
// extr int old_currentlocation; // zona precedente del robot in campo da 1 a 9
// o
//                               // 255 se undefined >USI FUTURI<
// extr int old_guessedlocation; // zona precedente del robot in campo da 1 a 9
// (da
//                               // CENTER_CENTER a SOUTH_WEST) >USI FUTURI<
// extr byte zone[3][3];         // il primo indice = NORD SUD CENTRO  il secondo
//                               // indice  EST OVEST CENTRO
// signed int zone_prob[3][3];

// BLUETOOTH
extr int a;
extr unsigned long old_timer;

// Interrupt
extr byte lineBallSensor;
extr byte lineBallDistance;

// comrade communication
extr int iAmHere;
extr int friendZone;
extr int role;
extr bool comrade;

// test new angle
extr int globalDir;
extr int globalSpeed;
