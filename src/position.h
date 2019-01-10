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

void WhereAmI();
void update_location_complete();
void ritornacentro();
void fugacentro();
void ritornaporta(int);
void update_sensors_all();
