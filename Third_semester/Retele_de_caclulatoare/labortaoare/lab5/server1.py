#Un client trimite unui server doua numere. Serverul va returna clientului suma celor doua numere.
#client1.py este clientul aferent acestui program

import socket
import sys

if len(sys.argv) == 3:
    # Get "IP address of Server" and also the "port number" from argument 1 and argument 2
    ip = sys.argv[1]
    port = int(sys.argv[2])
else:
    print("Run like : python3 server.py <arg1:server ip:this system IP 192.168.1.6> <arg2:server port:4444 >")
    exit(1)

# Create a UDP socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# Bind the socket to the port
server_address = (ip, port)
s.bind(server_address)
print("Do Ctrl+c to exit the program !!")

while True:
    print("####### Server is listening #######")
    a, data = s.recvfrom(4096)
    b, data = s.recvfrom(4096)
    nr1 = int(a.decode('utf-8'))
    nr2 = int(b.decode('utf-8'))
    print("\n\n 2. Server received: ", nr1, nr2, data, "\n\n")
    suma = nr1+nr2
    suma = str(suma)
    s.sendto(suma.encode('utf-8'), data)
    print("\n\n 1. Server sent : ", suma,"\n\n")