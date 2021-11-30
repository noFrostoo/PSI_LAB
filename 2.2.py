#!/usr/bin/env python3

import socket
from string import ascii_lowercase
import sys

if len(sys.argv) < 3:
    print(f'Usage: {sys.argv[0]} <addr-or-domain> <port>', file=sys.stderr)
    exit(1)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sck:
    sck.connect((sys.argv[1], int(sys.argv[2])))
    sck.sendall((ascii_lowercase * 2).encode())
