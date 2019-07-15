import socket
import sys
<<<<<<< HEAD
import threading as threading
=======
from thread import *

def receive():
    while True:
        try:
            data = s.recv(1024)
            print(data)
        except socket.error:
            pass
>>>>>>> a638e09ed8d4ce10f7da913b2b7a89765d8816cf

def receive():
	try:
		s.listen(10)
		s.recv(2014)
	except socket.error:
		s.close()
		sys.exit();

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
        print("Failed to create socket ("+socket.error+")")
        sys.exit()

HOST = "192.168.4.1"
PORT = 9999

try:
    s.connect((HOST, PORT))
except socket.error:
    print("Connessione rifiutata")
    sys.exit()

name = input("Inserisci il tuo nickname: ")
#s.sendall(str(name + ' è entrato nella chat').encode('UTF-8'))

threading._start_new_thread(receive, () )

while 1:
    try:
        print(s.recv(1024).decode('UTF-8'))
        st = input()
        s.sendall(str('<' + name + '>  : '+ st).encode('UTF-8'))
    except socket.error:
        print("Errore indefinito")
        sys.exit()
