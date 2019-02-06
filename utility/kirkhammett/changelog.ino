/*
   STORIA DELLE VERSIONI E RELATIVE MODIFICHE

   Versione 01
   Ripulitura errori e ordinamento variabili locali/globali rispetto a sw base di Flavio
   Introduzione test su monitor seriale

   Versione 02
   Modifica del modo di attivazione dei test
   il flag di attivazione test é solo un bool e indica se gioco normale o test
   i test si selezionano con un comando da tastiera
   il comando é un solo byte ed é indicato da un carattere da 0 a 9 e poi a,b,c ecc.

   Versione 03
   Modificata gestione di goalie e le routine di controllo posizione in field position

   Versione 04
   Cambiata logica di scelta zona senza la matrice di probabilita introducendo matrice 3x3

   Versione 05
   Fa i test anche da remoto se montata la scheda bluetooth
   Consente di uscire e entrare nei test senza ricaricare il programma
   Inverte 140 e 220 nella gestione della palla vista dai sensori 9 e 11

   Versione 05c
   Ridotta in goalie la oscillazione quando ha la palla davanti
   Introdotte commentate in gestioneinterrupt le visualizzazioni del sensore di linea e della zona
   Introdotta commentata nel loop la visualizzazione della zona
   Inserita costante MOTORI per semplificare il cambio di velocita' per motori diversi
   Inserita define condizionata al valore di MOTORI per cambio automatico velocitá
   Nel caso non conosca posizione x imposta per il controllo della y i limiti di fascia (piú ampia)
   Cambiati i valori di DyF e DyP con valori maggiori senza sottrazione di 22 (robot) e 10 (1/2 portiere)

   Versione 06
   La ISR memorizza la situazione dei sensori al momento dell'interrupt linea_new
   La ISR memorizza la situazione dei sensori al precedente interrupt linea_old
   Al primo interrupt (che attiva il flag_interrupt) linea_new e linea_old diventano uguali
   La ISR memorizza la situazione degli ultrasuoni quando scatta il primo interrupt

   Versione 07
   Aggiunti i test d e f g
   La ISR conteggia gli interrupt dopo il primo mentre attivo il flag dell' interrupt
   La ISR memorizza le letture dei sensori di linea all'interrupt in un array

   Versione 07c
   Modificata la routine di ritorna al centro in modo da tener conto di status_x e status_y
   Modificata la gestione dell' interrupt in modo da tener conto di status_x e status_y
   Angoli di attacco definiti automaticamente per robot veloce e lento

   Versione 08
   Modificato il test d in modo da individuare tutti i sensori attivi durante la frenata
   Modificata ISR senza individuazione del primo sensore
   Modificata gestione interrupt tenendo conto dei sensori attivati durante la frenata

   Versione 09
   Integrata la gestione interrupt per tener conto anche della uscita con 5 sensori
   Integrata la gestione interrupt in modo che aggiorni le variabili status_x e status_y
   Modificato il ritorno verso il centro
   La gestione dell'interrupt n.3 impedisce di andare sulla palla che sta fuori oscurando i sensori
   Modificato goalie in modo che tenti di convergere verso la porta sulle fasce

   Versione 10
   Cambio di role tramite Switch sinistro
   Cambio di velocità tramite switch destro
   Modifica funzione portiere
   Modifica linee : i sensori mascherati dipendono solo dai sensori di linea (provvisoriamente si sono impostate le variabili d1,d2 e d3 a 99 per disabilitare nel while il mascheramento nel sensore palla)

   Latino:
   Modifica goalie: se palla dietro con distanza 4 o 5 valuta se andare in direzione 200 (sininstra) o 160 (destra)
   Modificati angoli di presa palla
   Messa in ordine delle varie costanti per velocità e angoli palla
   Aumento delle velocità di 20 su VEL_RET
   Gestione interrupt: aumentati tempo dt di 200
   Integrazione della gestione del role del robot basandosi sul suo compagno in gara tramite il bluetooth DA VERIFICARE
   Modificati angoli 300 e 120 in 295 e 115. Portati i simmetrici 60 a 55  240 in 235.
   Modificati angoli di uscita e tempi di rientro nell'interrupt.
   Aumentato da 15 a 25 st che va a modificare il centro in drivePID nella tab pid.
   Implementato il drift. Ora a OVEST corregge a 45 e a EST a 315.
   Tolto al momento la gestione del role tramite BT.
   Creata funzione menamoli.
   Adesso se la palla va dietro il portiere torna in porta.
   Quando riceve un interrupt durante menamoli, il robot torna al centro porta per evitare che esca per tentare di prendere la palla o situazioni scomode in cui l'avversario si ritorva con la porta nostra scoperta
   Portato st in menamoli e goalie a EST a 25 e a OVEST a 35
   Modificato completamente gestione interrupt
   apportate modifiche al drift in goalie e menamoli. Ora menamoli torna alla porta dopo un interrupt
   Modificate nuovamente velocità e angoli. Velocità portate al massimo e angoli tarati come vecchi motori veloci.
   Creata una nuova gestione dell'interrupt che si basa solamente su sensori palla e ultrasuoni. Funziona ma da rivedere, in caso di problemi utilizzare la gestione interrupt che utilizza solo sensori linee senza mie modifiche e sperare per il meglio.
   Commentate le attack rotation in goalie e menamoli - vedi se gioca meglio
   gestione interrupt spalla e us : adesso si mascherano i due sensori precedenti e i due successivi del sensore che vede la palla, così da evitare le uscite dalle linee bloccando il robot per 2500ms in caso la veda con lo stesso sensore.

   MODIFICHE POST PRIMO GIORNO ROMECUP

   Tempo dell'interrupt portato a un secondo (1000ms)
   Abilitato mascheramento dei sensori nella gestione dell'interrupt

   MODIFICHE SECONDO GIORNO ROMECUP

   Modificato completamente la decisione del drift in goalie e menamoli, da verificare
   Modifica in space invaders: tolleranza distanze portate da 2&3 a 3&4, così quando la palla sta a centro campo il robot non rimane fermo e fa goal
   Adesso lo switch destro viene utilizzato per variare i tempi di attesa dopo un interrupt: se HIGH, il robot attende il movimento della palla per due secondi. Se LOW, per un solo secondo.
   Modifica a goalie e menamoli: ora lo storcimento avviene con i sensori 19,0 e 1. Risolto problema del mancato drift.
   Modificata tolleranza in gest interrupt e velocità massima di rientro

   MODIFICHE CAMPIDOGLIO

   Modificate distanze del portiere, ora segna di più. Speriamo bene..
   MODIFICA IN PARTITA: aumentato storcimento di 15 gradi da entrambi i settori a nord. atk_rot rimasta invariata.

   ---------------------------------------------------------------- CODICE VINCENTE ITALIANO-----------------------------------------------------------------------

   E.Latino, M.Tannino 


  PRO TIP: LA RAUCH HA CAMBIATO LO STORCIMENTO ORA atk_rot E' IN DISUSO
  SONO TORNATO FATER MATER

  MODIFICHE RAUCH:

  Ritornati ai case individuali e migliorati
  Introdotto 1 secondo di rallentamento dopo interrupt
  Rientro migliorato

  MODIFICHE EUROPERO (v15.3):

  Aumentato storcimento portiere e attaccante
  Cerco di non fare autogoal durante il ritorno in porta
  Aumentate le velocità portiere rispetto GOALIE_MIN (GOALIE_P)
  Ridotta a due la distanza di attacco portiere
  Portiere si muove solo sulla linea della porta
  Se la palla non si muove per 3 secondi divento "menamoli"
  Sostituito goalie a menamoli
  Tentativo bluetooth (Non riescono a mandarsi il check, soluzione: forse check hardware sul led verde del modulo)
  Il portiere non si incaglia sulla porta
  Distanza precisa della palla con distanza media degli ultimi 5 valori (ball_distance_precise)
  Aggiustati i rispettivi valori usando ball_distance_precise

   --------------------------------------------------------------- CODICE VINCENTE EUROPEO ------------------------------------------------------------------------

   A. Mauri, V. Ambler

  MODIFICHE MONDIALI (versione KIRK HAMMETT)

  Sostituito buzzer=HIGH con tone
  Comunicazione tra robot attraverso bluetooth per capire se è presente o no il compagno e gestire il role
  Aggiunto super_mario e tab buzzer
  Aggiunta telecamera e migliorate tattiche generali di presa palla, controllo palla e posizionamento
  Aggiunte più condizioni alla fase di attacco considerando la posizione esatta del centro del blob
  Telecamera decentrata: se in angolo nord ovest non trova l'obiettivo, risolto tramite utilizzo ultrasuoni
  Unita gestione interrupt europei con gestione interrupt rauch e gestione interrupt porcata di emanuele
  Modificato totalmente gestione palla dietro in goalie e menamoli
  Aggiunte strategie con la gestione dei ruoli tramite bluetooth in space_invaders
  Cambio di role BT in main
  Diminuite velocità in danger, palla dietro e rientro del portiere causa perdita palla o uscita dal campo violenta
  Create le costanti per più velocità, come la velocità in danger e quelle laterali a varie distanze
  Unificate le modifiche in goalie in menamoli
  Commenti generali in goalie, menamoli, space_invaders, effettuate modiifche alla logica di space invaders per renderlo più simile a quello scritto originariamente per i nazionali
  Gestione palla dietro nel ritorno 
  Aggiunta TAKE ON ME
  Attesa dell'interrupt portata a 800 causa attse troppo lunghe in fase di attacco
  Sistemate coordinate della porta con valori universali per entrambe le telecamere
  Tornati angoli di attacco foglio magico
  Robot continua l'attacco in fase di storcimento sulle linee
  
  ----FINE SVILUPPO A ROMA, CI VEDIAMO A MONTEREAL-----


  ***MONTREAL***
  *attesa interrupt portata da 800 a 500
  *portata a 140 da 120 la velocità danger
  *ritarati gli angoli con scelta di attacco in base alla X della porta e non più con gli ultrasuoni, funziona ma da rivedere proprio la scelta degli angoli in base all'evenenienza
  *integrazione modifiche goalie in menamoli
*/
