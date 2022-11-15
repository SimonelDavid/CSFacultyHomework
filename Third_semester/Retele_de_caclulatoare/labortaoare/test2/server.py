# Cerinta noua: clientul trimite un sir de caractere:propozitie cu spatii, iar serverul va calcula numarul total de spatii din propozitie si va calcula numarul de cifre din adresa ip.
# In server se va face suma celor doua(numarul de spatii goale si numarul de cifre din adresa ip) si o va trimite clientului. 
# Clientul afiseaza suma specificand in linia de comanda si textul dar si adresa ip pe care sa facut calculul.
import socket
import sys

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

def check_space(string):
     
    # counter
    count = 0
     
    # loop for search each index
    for i in range(0, len(string)):
         
        # Check each char
        # is blank or not
        if string[i] == " ":
            count += 1
         
    return count

while True:
    print("####### Server asculta #######")

    count = 0
    count += 1

    text, data = s.recvfrom(4096)
    text = str(text.decode('utf-8'))
    suma_spatii = check_space(text)

    port = int(input("Citeste port: \n"))

    port += suma_spatii
    port = str(port)
    print("portul nou este: ", port)

    uniue_char = "".join(set(text))

    print("caractere unice:", uniue_char)
    uniue_char = str(uniue_char)
    s.sendto(port.encode('utf-8'),data)
    ip_precedent = 0
    if count == 0:
        uniue_char = uniue_char+" "+str(data[0])
        ip_precedent=data[0]
    if count > 0:
        uniue_char = uniue_char+" "+str(data[0])
        ip_precedent = data[0]

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
    s1.sendto(uniue_char.encode('utf-8'),data)

    print("\n\n Server a primit: ", text, "\n\n")

    