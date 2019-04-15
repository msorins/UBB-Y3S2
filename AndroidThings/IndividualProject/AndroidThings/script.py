import socket
from threading import *
import random
import time

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = '192.168.43.130'
port = 6969
print (host)
print (port)
serversocket.connect((host, port))

count = 2000
while count:
    # ledId = random.randint(0, 143)
    ledId = count % 143
    r = random.randint(0, 70)
    g = random.randint(0, 70)
    b = random.randint(0, 70)
    time.sleep(0.2)
    serversocket.sendall("0, {0}, {1}, {2}, {3};\n".format(ledId, r, g, b).encode())
    count -= 1