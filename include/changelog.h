/*
 * Robot 2019 - Emanuele Latino, Siria Sannino, Emanuele Coletta
 *
 * 3/12/2018
 *
 * Stesura codice Kirkhammet convertito per Teensy
 *
 * IMU funziona su I2c-Wire
 * Ultrasuoni funzionano con I2c Wire2 senza problemi, wire.h e affini sono
 * richiamati tutti da bno, daje todo:      ((per farlo giocare un minimo))
 *    motori
 *    spi {
 *        controlla codice atmega ma dovrebbe adare
 *    }
 *
 *
 * 4/12/2018
 *
 * Repository GitHub, codice tutto nel main per evitare errori, da rivedere
 * extern (non è un grande problema, è fattibile) Da adesso il codice rimane su
 * platformio, tutto sincronizzato tra i vari computer. la todo rimane
 * invariata, come del resto tutto il codice.   -Emanuele Latino
 *
 *
 * 5/12/2018
 *
 * Effettuate modifiche a repo, motori completamente funzionanti (dal punto di
 * vista software) Aggiunta tab pid Riformattato codice con file .h includendo
 * nei vari file i necessari (se chiamate da funzioni in altri file) todo: spi
 * (team mauri, per farlo giocare) bluetooth sensori di linea camera
 *
 *  10/12/2018
 *  Testate nuova scheda interfaccia Teensy-vecchio hardware con IMU e
 * ultrasuoni. Codice funzionante per leggere i quattro ultrasuoni assieme e
 * mettere i valori nell'array.   -Emanuele Coletta & Siria Sannino
 *
 *  todo:
 *    spi (team mauri, per farlo giocare)
 *    bluetooth
 *    sensori di linea
 *    camera
 *    sistemare commenti codice Ultrasuoni
 *    da vedere la funzione millis() invece di delay() per i print in Seriale
 *    (millis() non blocca il codice e potrebbe aiutare i print in serial)
 *
 *
 *  12/12/2018
 *  Realizzata SPI e interfaccia con AVR644 per i sensori palla. Sistemati i
 * commenti e tradotti in inglese. L'uso di millis richiede scrivere delle
 * funzioni apposite, magari usarlo solo per i test (solo lì serve la
 * comunicazione seriale)
 *
 *  todo:
 *    SENSORI DI LINEA
 *    bluetooth
 *    camera
 *
 *  - Emanuele Coletta & Siria Sannino
 *
 * 13/12/2018
 * La repo diventa privata, il nome ufficiale è SPQR 2019.
 * -Test per il fetch da repo privata delle 22:18
 * -Test fetch manjaro II
 *
 * 19/12/2018
 * Sistemati gli #include per far funzionare goalie e pid.
 * Un sacco di variabili erano mancanti non importate dal codice vecchio.
 * Ad alcune variabili sembra che venga assegnato un valore nei tab non ancora
 * importati. Da sistemare
 *
 * 16/1/2019
 * Due big refactor del codice, header e cpp e variabili sono ora utilizzate
 * bene Sistemati US e zone, ora funzionano. Da investigare i sensori di linea
 * TODO:
 *  SENSORI DI LINEA
 *  bluetooth e camera, trascurabili per ora
 *
 * 21/1/2019 - 17:30
 * Prima implementazione sensori di linea. Funzionano benino ma hanno portato un
 * paio di bug con la palla, investighiamo
 * TODO:
 *  Fixare bug palla
 *  bluetooth e camera, trascurabili per ora
 *
 * 4/2/2019 - 16:22
 * Sotto consiglio di Flavio, ora c'è solo un drivePID per loop e ogni drivePID
 * è stato sostituito con un'impostazione della velocità globale. Prossimo passo
 * cambio interrupt
 *
 * 4/2/2019 - 19:51
 * Con aiuto di Flavio, nuovi interrupt migliori con trigonometria. Da ultimare
 * il punto di stop se la palla di trova in un certo range di sensori rispetto a
 * quello dove era la palla a interrupt attivato
 *
 * 6/2/2019 - 19.51
 * Tentantivo di sistemazione dei sensori di linea, fallimentare(probabilmente
 * per il campo orribile), e di space_invaders, fallimetare Approfondire la
 * prossima volta ULTRASUONI O I2C ROTTI, DA VERIFICARE
 *
 * 11/2/2019
 * Nuova implementazione space_invaders, da sistemare. Fixati ultrasuoni (pin
 * collegato male)
 * TODO.
 *  PIC e Camera(finalmente funzionante)
 *  Fixare space space_invaders col metodo della somma vettoriale
 *
 * 25/2/2019
 * Ennesimo space_invaders che funziona male, da rivedere per l'ennesima volta.
 * Nuovo PID, modificate le variabili ed ottimizzato il codice per un PID che
 * "svirgoli" di meno e sia più preciso Inizio nuovo codice AVR12 (AVRupgrade)
 * con interpolazione a 20 sensori, da testare con SPI perché seriale non
 * funzionante. Iniziata nuova SPI per comunicazione con AVRupgrade, da
 * ultimare. Apparentemente abbiamo una seconda scheda Teensy (testata e
 * funzionante) su cui fare esperimenti in parallelo, da montare il robot
 * completp
 *
 * TODO:
 *  Data la vicinanza della Romecup bisogna decidere ciò che è da sistemare per
 * la gara
 *
 *
 * 27/2/2019
 * Decisione ruoli (vedi lavagnetta o foto su whatsapp). Goalie con palla dietro
 * e storcimento. Storcimento strano a sinistra, da sistemare i calcoli.
 * Storcimento in goalie solo a distanza ravvicinata per evitare che scodi
 * pesantemente Space invaders circa funzionante, è una buona base da
 * migliorare. Linee sistemati, gli angoli lo mettono ancora in crisi
 *
 * TODO:
 *  Vedi lavagnetta o foto su whatsapp
 *
 * 18/3/2019
 *  Sistemati i robot che non riuscivano a giocare. Telecamera su robot attaccante,
 *  da sistemare ancora un po' lo storcimento nella fascia di sinistra (Ematino).
 *  Iniziato bluetooth tra i due robot, si connettono ma non comunicano la zona
 *
 *  TODO:
 *    Migliorare comunicazione bluetooth
 *    Migliorare tutto finché si può
 *
 * 27/3/2019
 *  Menu di test da Serial Monitor, a prova di scemo (Il Test 6 non serve a un cizzo)
 *  Miglioramenti a space invaders per non uscire dietro
 *  Miglioramenti storcimento incrementale per attaccante
 *
 *  TODO:
 *    Migliorare tutto quel che si può
 *    Migliorare logica comrade col bluetooth
 *
 *
 *
 *
 *
 *
 */
