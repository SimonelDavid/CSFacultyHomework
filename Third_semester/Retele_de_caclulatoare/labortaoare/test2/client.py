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
try:
        s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
except socket.error:
        print("Eroare la conectarea socket-ului client")
        sys.exit()


# Let's send data through UDP protocol
while True:
    text = input("Text: \n")

    s.sendto(text.encode('utf-8'), (ip, port))

    port_nou,source=s.recvfrom(100)

    port_nou = port_nou.decode('utf-8')

    print("portul nou este: ", port_nou)
    
    unique_chars, data = s.recvfrom(4096)

    unique_chars = unique_chars.decode('utf-8')
    print("caractere unice: ", unique_chars)
    
# close the socket
s.close()