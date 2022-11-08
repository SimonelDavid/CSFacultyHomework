#!/bin/python3
#server.py
import socket
import sys
import random
id = 0


def play(client1, client2):
	#trimitere id
	client1.send(encode(id))
	client2.send(encode(id))
	letter = random.choice("abcdefghijklmnopqrstuvwxyz")
	#client1 litera random
	client1.send(encode(letter))

	cuvant = decode(client1.recv(10))
	litera_noua = decode(client1.recv(10))
	#conventie: client1 nu poate pierde chiar din prima:))

	while True:
		client2.send(encode("da"))
		client2.send(encode(litera_noua))

		cuvant = decode(client2.recv(10))
		litera = litera_noua
		litera_noua = decode(client2.recv(10))
		if litera not in cuvant:
			client1.send(encode("c"))
			client2.send(encode("g"))
			return

		#switch client
		clientAux = client2
		client2 = client1
		client1 = clientAux

def encode(data):
	return bytes(str(data), 'utf-8')

def decode(data):
      return str(data.decode('utf-8'))


if len(sys.argv) != 2:
	print("./server port")
	exit()


TCP_IP = "0.0.0.0"
TCP_PORT = int(sys.argv[1])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

while 1:
	client1, addr1 = s.accept()
	client2, addr2 = s.accept()
	id+=1
	play(client1, client2)
conn.close()