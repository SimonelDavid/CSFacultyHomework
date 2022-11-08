#!/bin/python3


#client.py

import socket
import sys

def play(s):
	data = s.recv(10)
	print("id joc: ", decode(data))
	litera = s.recv(10)
	if not litera:
		print("sunt 2")
	else:
		print("sunt 1")
		s.send(encode(input("cuvant>>")))
		s.send(encode(input("litera>>")))

	while True:
		continua = s.recv(10)
		if decode(continua) == "da":
			litera = s.recv(10)
			s.send(encode(input("cuvant>>")))
			s.send(encode(input("litera>>")))
		if decode(continua) == "g":
			print("ai pierdut")
			return
		if decode(continua) == "c":
			print("ai castigat")
			return

def encode(data):
	return bytes(data, 'utf-8')

def decode(data):
	return data.decode('utf-8')

if len(sys.argv) != 3 :
	print("./client.py ip port")
	exit()

TCP_IP = sys.argv[1]
TCP_PORT = int(sys.argv[2])
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
play(s)
s.close()