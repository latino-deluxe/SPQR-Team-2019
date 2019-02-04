/*
 * Robot 2019 - Emanuele Latino, Siria Sannino, Emanuele Coletta
 *
 * 3/12/2018
 *
 * Stesura codice Kirkhammet convertito per Teensy
 *
 * IMU funziona su I2c-Wire
 * Ultrasuoni funzionano con I2c Wire2 senza problemi, wire.h e affini sono richiamati tutti da bno, daje
 * todo:      ((per farlo giocare un minimo))
 *    motori
 *    spi {
 *        controlla codice atmega ma dovrebbe adare
 *    }
 *
 *
 * 4/12/2018
 *
 * Repository GitHub, codice tutto nel main per evitare errori, da rivedere extern (non è un grande problema, è fattibile)
 * Da adesso il codice rimane su platformio, tutto sincronizzato tra i vari computer.
 * la todo rimane invariata, come del resto tutto il codice.   -Emanuele Latino
 *
 *
 * 5/12/2018
 *
 * Effettuate modifiche a repo, motori completamente funzionanti (dal punto di vista software)
 * Aggiunta tab pid
 * Riformattato codice con file .h includendo nei vari file i necessari (se chiamate da funzioni in altri file)
 * todo:
 *    spi (team mauri, per farlo giocare)
 *    bluetooth
 *    sensori di linea
 *    camera
 *
 *  10/12/2018
 *  Testate nuova scheda interfaccia Teensy-vecchio hardware con IMU e ultrasuoni. Codice funzionante per leggere i
 *  quattro ultrasuoni assieme e mettere i valori nell'array.   -Emanuele Coletta & Siria Sannino
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
 *  Realizzata SPI e interfaccia con AVR644 per i sensori palla. Sistemati i commenti e tradotti in inglese.
 *  L'uso di millis richiede scrivere delle funzioni apposite, magari usarlo solo per i test (solo lì serve la comunicazione seriale)
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
 * Ad alcune variabili sembra che venga assegnato un valore nei tab non ancora importati.
 * Da sistemare
 *
 * 16/1/2019
 * Due big refactor del codice, header e cpp e variabili sono ora utilizzate bene
 * Sistemati US e zone, ora funzionano. Da investigare i sensori di linea
 * TODO:
 *  SENSORI DI LINEA
 *  bluetooth e camera, trascurabili per ora
 *
 * 21/1/2019 - 17:30
 * Prima implementazione sensori di linea. Funzionano benino ma hanno portato un paio di bug con la palla, investighiamo
 * TODO:
 *  Fixare bug palla
 *  bluetooth e camera, trascurabili per ora
 *
 * 4/2/2019 - 16:22
 * Sotto consiglio di Flavio, ora c'è solo un drivePID per loop e ogni drivePID è stato sostituito con un'impostazione
 * della velocità globale.
 * Prossimo passo cambio interrupt
 *
 * 4/2/2019 - 19:51
 * Con aiuto di Flavio, nuovi interrupt migliori con trigonometria. Da ultimare il punto di stop
 * se la palla di trova in un certo range di sensori rispetto a quello dove era la palla a interrupt attivato
 *
 *
 */
