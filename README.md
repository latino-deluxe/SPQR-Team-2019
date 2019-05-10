# SPQR-Team-2019 /// SPQR2 - Emanuele Latino, Emanuele Coletta, Siria Sannino
_Repo privata con il codice aggiornato dell'anno 2018-2019, vincitore delle nazionali_

Branch dedicato al multithreading. Lo sto curando io (Ematino) qualsiasi proposta o appunto, insomma se vedi una minchiata sentiti libero di scrivermi per email o fare una pull request.

Il codice con il multithreading consente di fare più cose contemporaneamente, senza attese e perdite di velocità. Il loop totale dovrebbe essere uguale a quello senza multithreading.

Le incompatibilità fino ad ora sono state solamente riscontrate con la IMU dopo aver preso un interrupt (smette di leggere per un po' dopo aver preso la linea e poi riprende normalmente). Questo problema non si riscontrerà con il nuovo robot dato che le linee non saranno gestite con l'interrupt quindi è un problema momentaneo :)

Spostato di prepotenza in un thread tutto il loop tranne lettura IMU. Da testare se funziona correttamente, sarebbe meglio dividere il tutto in altri thread visto che ne abbiamo ancora 3 liberi.

1/5/2019 - In aereo - 5 thread utilizzati su 8 [espandibili se giochi con la libreria]


# TODO:
IMU nei thread
Storcimento buono

Varie ed eventuali. Sentiti libero di aggiornare
