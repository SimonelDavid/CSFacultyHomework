# Cerinta noua: clientul trimite un sir de caractere:propozitie cu spatii, iar serverul va calcula numarul total de spatii din propozitie si va calcula numarul de cifre din adresa ip.
# In server se va face suma celor doua(numarul de spatii goale si numarul de cifre din adresa ip) si o va trimite clientului. 
# Clientul afiseaza suma specificand in linia de comanda si textul dar si adresa ip pe care sa facut calculul.
import socket
import sys
import string
import random
import urllib.util.ssl_

if len(sys.argv) == 3:
    # Get "IP address of Server" and also the "port number" from argument 1 and argument 2
    UDP_IP = sys.argv[1]
    UDP_PORT = int(sys.argv[2])
else:
    print("Ruleaza astfel : python3 server.py <arg1 : ip : ip-ul acesta de exemplu = 127.0.0.1> <arg2 : port : 4444 >")
    exit(1)

try:
        s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
except socket.error:
        print("Eroare la crearea socket-ului server")
        sys.exit()
try:
        s.bind((UDP_IP,UDP_PORT))
except socket.error:
        print("Eroare la conectarea la server")
        sys.exit()

def get_random_string(length, text):
    result_str = ''.join(random.choice(text) for i in range(length))
    print("Random string of length", length, "is:", result_str)

def productAscii(text):
 
    prod = 1
    text = str(text)
    # Traverse string to find the product
    for i in range(0, len(text)):
        prod = prod * ord(text[i])
 
    # Return the product
    return prod

while True:
    print("####### Server asculta #######")

    count = 0
    count += 1

    text, data = s.recvfrom(4096)
    text = str(text.decode('utf-8'))

    text = text[::-1]

    random_3_chars = get_random_string(3, text)
    prod = productAscii(random_3_chars)

    port = int(input("Citeste port: \n"))

    print("portul nou este: ", port)
    if port < 40000 or port > 50000:
        port = int(input('Portul este gresit! Trebuie sa fie intre 40000 si 50000. Alege un alt port: \n'))

    port = str(port)

    s.sendto(port.encode('utf-8'),data)

    port = int(port)

    try:
        s1=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    except socket.error:
            print("Eroare la crearea socket-ului server")
            sys.exit()
    try:
            s1.bind((UDP_IP,port))
    except socket.error:
            print("Eroare la conectarea la server")
            sys.exit()
    s1.sendto(prod.encode('utf-8'),data)

    print("\n\n Server a primit: ", text, "\n\n")

    