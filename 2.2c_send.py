#!/usr/bin/env python3

import socket
from string import ascii_lowercase
import sys

# weryfikacja odpowiedniej ilości argumentów
if len(sys.argv) < 3:
    print(f'Usage: {sys.argv[0]} <addr-or-domain> <port>', file=sys.stderr)
    exit(1)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sck:
    # połączenie się z serwerem
    sck.connect((sys.argv[1], int(sys.argv[2])))
    # wysłanie danych
    sck.send((ascii_lowercase * 2).encode())
