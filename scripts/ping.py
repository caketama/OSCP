import ipaddress
import subprocess

address = ipaddress.ip_network("10.11.1.0/24")
for ip in address:
    ip = str(ip)
    ping = subprocess.Popen(["ping", "-c 1", ip])
    print(ping)
