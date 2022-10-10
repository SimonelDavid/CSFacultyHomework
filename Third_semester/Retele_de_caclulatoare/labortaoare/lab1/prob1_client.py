#Enunt: Clientul trimite serverului doua numere. Serverul le primeste, le afiseaza pe ecran si trimite clientului suma lor.
#
#Rulare in doua terminale diferite:
#	python server.py
#	python client.py
import socket

TCP_IP = "127.0.0.1"
TCP_PORT = 8888
st = input("Dati un numar: ")
MESSAGE = st.encode()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
s.send(MESSAGE)
print("Am trimis la server: ",MESSAGE)

st2 = input("Dati al doilea numar:")
MESSAGE2 = st2.encode()
s.send(MESSAGE2)
print("Am trimis la server: ",MESSAGE2)

data = s.recv(10)
s.close()

print("Am primit de la server: ", data)