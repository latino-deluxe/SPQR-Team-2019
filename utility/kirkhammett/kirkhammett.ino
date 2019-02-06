
//LIBRERIE------------------------------------
#include "libraries/BNO055.cpp"   //LIBRERIE IMU,I2C,PRESA PALLA
#include "libraries/BNO055.h"
#include "libraries/I2C.cpp"
#include "libraries/I2C.h"
#include "libraries/VL53L0X.h"
#define SerialTest Serial          //SERIALE TEST
#define SerialOMV  Serial1         //SERIALE CAMERA
#define bluetooth  Serial3         //SERIALE COMUNICAZIONE BT

//MAPPATURA PIN SHIELD-------------------------------
#define PIN_LED_R 40
#define PIN_LED_Y 39
#define PIN_LED_G 38
#define PIN_BUTTON1 28
#define PIN_BUTTON2 27
#define PIN_BUTTON3 26

//PIN IR BOARD-------------------------------
#define PIN_PIEZO 22
#define SWITCH_SX 24
#define SWITCH_DX 25

//VARIABILI PER GESTIONE SWITCH---------------
int SWS = 0;
int SWD = 0;

//PIN SPI------------------------------------
//#define Nbyte 1
#define _SCK   52
#define _MISO  50
#define _MOSI  51
#define _SS    53

//MASCHERE DEI SENSORI DI LINEA-------------------------------
//maschera per la porta PINK per ricavare il valore del pin di Arduino
#define S1 1   // A8  bit 0 di PINK
#define S2 2   // A9  bit 1 di PINK
#define S3 4   // A10 bit 2 di PINK
#define S4 8   // A11 bit 3 di PINK
#define S5 16  // A12 bit 4 di PINK
#define S6 32  // A13 bit 5 di PINK

//FLAG DEI TEST------------------------------------
bool flagtest = false;  // Necessario per i test

//PIN MOTORI----------------------------------------
// 1 2 3 motori
byte INA_MOT [4] = {0,  2,  10,  12}; //pin INA
byte INB_MOT [4] = {0,  3,  11,  13}; //pin INB
byte PWM_MOT [4] = {0,  6,   7,   8}; //pin PWM

//VARIABILI DEI MOTORI-------------------------------
float speed1;    // velocitá motore 1
float speed2;    // velocitá motore 2
float speed3;    // velocitá motore 3
float pidfactor; // fattore di PID
float sins[360]; // array dei seni a gradi interi da O a 359 per velocizzare

//da utilizzare per sviluppi futuri-------------------
signed int old_Dir = 0;  // angolo di direzione precedente a quella attuale
signed int new_Dir = 0;  // angolo di direzione corrente del moto
float old_vMot;          // velocitá di moto precedente
float new_vMot;          // velocitá di moto corrente

//VARIABILI RELATIVE ALLA LETTURA DELLA PALLA---------------
byte spi_temp_byte = 0;    // dato grezzo letto da SPI
byte ball_sensor = 0;      // sensore che vede la palla
byte ball_distance = 0;    // distanza della palla con valore da 0 a 6
bool ball_seen = false;    // palla in vista si/no era byte
byte old_s_ball;           // sensore che vedeva la palla in precedenza, paragonato con ball_sensor
unsigned long time_s_ball; // millisecondipassati dal cambiamento di sensore che vede la palla (KEEPER)

//VARIABILI PER IMU-------------------------------------------
BNO055 IMU(0x28);        //crea oggetto IMU dalla classe BNO055 con indirizzo I2C 0x28
int imu_temp_euler = 0;
int imu_current_euler = 0;

//VARIABILI PER I SENSORI A ULTRASUONI----------------------
long us_t0 = 0;                // inizio misura ultrasuoni
long us_t1 = 0;                // misura del tempo durante la misura
byte us_flag = false;          // misura in corso si/no
int us_values[4];               // array delle misure degli ultrasuoni
int us_sx, us_dx, us_px, us_fr;// copie con altro nome dell'array

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

//VARIABILI E COSTANTI DEL PID--------------------------------
#define KP  0.7             // K proporzionale
#define KI  0.001           // K integrativo
#define KD  0.001           // K derivativo
float errorePre = 0.0;      // angolo di errore precedente
float integral = 0.0;       // somisa degli angoli di errore
bool reaching_ball = false; // serve per aumentare il PID del 20% GOALIE
int st = 0; // storcimento sulle fasce


//VARIABILI E COSTANTI POSIZIONI CAMPO-------------------------------------

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

int status_x = CENTRO;                // posizione nel campo vale EST, OVEST o CENTRO o 255
int status_y = CENTRO;                // posizione nel campo vale SUD, NORD o CENTRO o 255
int currentlocation = CENTRO_CENTRO;  // risultato misure zone campo da 1 a 9 o 255 se undefined
int guessedlocation = CENTRO_CENTRO;  // risultato misure zone campo da 1 a 9 (da CENTRO_CENTRO a SUD_OVEST)



int old_status_x = CENTRO;        // posizione precedente nel campo vale EST, OVEST o CENTRO o 255 >USI FUTURI<
int old_status_y = CENTRO;        // posizione precedente nel campo vale SUD, NORD o CENTRO o 255 >USI FUTURI<
int old_currentlocation; // zona precedente del robot in campo da 1 a 9 o 255 se undefined >USI FUTURI<
int old_guessedlocation = CENTRO_CENTRO; // zona precedente del robot in campo da 1 a 9 (da CENTRO_CENTRO a SUD_OVEST) >USI FUTURI<

bool goal_zone = false;         // sto al centro rispetto alle porte         assegnata da WhereAmI ma non usata
bool good_field_x = true;      // vedo tutta la larghezza del campo si/no
bool good_field_y = true;     // vedo tutta la lunghezza del campo si/no




//MATRICE DI PROBABILITÁ-------------------------------
byte zone [3] [3] {1, 2, 3, 4, 5, 6, 7, 8, 9}; // il primo indice = NORD SUD CENTRO  il secondo indice  EST OVEST CENTRO
signed int zone_prob[3] [3] {0, 0, 0, 0, 5, 0, 0, 0, 0};


//VARIABILI INTERRUPT SENSORI LINEE---------------------
volatile byte linesensor = 0;          // sensore che ha dato interrupt byte perché da 1 a 6
volatile byte linea_new;               // stato dei sensori di linea all'ultimo interrupt
volatile byte linea_old = 63;          // stato dei sensori di linea all'interrupt precedente
volatile int ISx;                      // valore ultrasuoni quando scatta il primo interrupt
volatile int IDx;
volatile int IPx;
volatile int IFr;
volatile bool flag_interrupt = false;
volatile byte Nint = 0;        // numero di interrupt consecutivi prima della fine della gestione
volatile byte linea [100];     // letture consecutive all'interrupt dei sensori di linea
int VL_INT;                    // velocitá di uscita dalle linee
int EXT_LINEA;                 // direzione di uscita dalla linea
byte n_us;                     // ultrasuono da controllare dopo la fuga dalla linea
int attesa = 0;                // tempo di attesa palla dopo un interrupt (utilizzata dallo switch destro)
bool danger;                   // avviso che terminata da poco la gestione interrupt
unsigned long tdanger;         // misura il tempo dal termine della gestione interrupt


//VARIABILI PER LA GESTIONE DEL role TRAMITE BLUETOOTH-----
int role = 0, a, count;
long timer, old_timer;
unsigned long tt = 0;  //tempo tra una trasmissione e l'altra
bool compagno = false;                  // ritiene compagno vero se riceve un carattere in datoArrivato
int datoArrivato;                            // per la ricezione
byte tent = 0;                                 // contatore dei tentativi


//VARIABILI PER IL PORTIERE
float bd = 0;
long ta;
bool atk_p = false;
byte ball_array[5];
short i;
byte vel_por = 255;
long diff;
float ball_distance_precise;
long ti;
long tf;
bool flag_atkp;
int paratozza_ang;
int paratozza_vel;

//VARIABILI PORTA
int x = 0;            //posizione x della porta ricevuta dalla telecamera
bool XP_SX = false;   //bool porta a sinistra o destra rispetto al robot
bool XP_DX = false;
bool XP_CENTRO = false;
bool dangergoalie = false;



//VARIABILI CAMERA
String valStringY = "";         //stringa dove si vanno a mettere i pacchetti di dati ricevuti
String valStringB = "";
int startpY = 0;                //inizio del dato
int startpB = 0;
int endpY = 0;                  //fine del dato
int endpB = 0;
int datavalid = 0;              //segnalo se il dato ricevuto è valido
int valY;                       //variabile a cui attribuisco momentaneamente il valore dell x della porta
int valB;
int p = 0;                      //variabile dello switch che decide dove bisogna attaccare
bool attack = false;
