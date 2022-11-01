#Un client trimite unui server un sir de lungime cel mult 100 de caractere si un caracter. Serverul va returna clientului toate pozitiile pe care caracterul primit se regaseste in sir.
#client1.py este clientul aferent acestui program

import socket
import sys

if len(sys.argv) == 3:
    # Get "IP address of Server" and also the "port number" from argument 1 and argument 2
    ip = sys.argv[1]
    port = int(sys.argv[2])
else:
    print("Run like : python3 server.py <arg1:server ip:this system IP 127.0.0.1> <arg2:server port:4444 >")
    exit(1)

# Create a UDP socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# Bind the socket to the port
server_address = (ip, port)
s.bind(server_address)
print("Do Ctrl+c to exit the program !!")

while True:
    print("####### Server is listening #######")

    text, data = s.recvfrom(4096)
    caracter, data = s.recvfrom(4096)

    text = str(text.decode('utf-8'))
    caracter = str(caracter.decode('utf-8'))

    print("\n\n Server received: ", text, caracter, data, "\n\n")

    nr = text.count(caracter)
    nr = str(nr)

    s.sendto(nr.encode('utf-8'), data)

    for i in range(0,len(text)):
        if text[i] == caracter:
            poz = str(i)
            s.sendto(poz.encode('utf-8'), data)
            print("\n Server sent : ", i,"\n")
    print("\n\n Server the work\n\n")