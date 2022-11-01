import socket
import sys

if len(sys.argv) == 3:
    # Get "IP address of Server" and also the "port number" from argument 1 and argument 2
    ip = sys.argv[1]
    port = int(sys.argv[2])
else:
    print("Run like : python3 client.py <arg1 server ip 127.0.0.1> <arg2 server port 4444 >")
    exit(1)

# Create socket for server
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
print("Do Ctrl+c to exit the program !!")

# Let's send data through UDP protocol
while True:
    text = input("Text: \n")
    caracter = input("Caracter: \n\n")

    s.sendto(text.encode('utf-8'), (ip, port))
    s.sendto(caracter.encode('utf-8'), (ip, port))

    print("\n\n Client Sent : ", text, caracter, "\n\n")
    
    nr, address = s.recvfrom(4096)
    nr = nr.decode('utf-8')
    nr = int(nr)

    for i in range(0, nr):
        poz, address = s.recvfrom(4096)
        poz = poz.decode('utf-8')
        print("\n\n Client received : ", poz, "\n\n")
# close the socket
s.close()