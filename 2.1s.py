#!/usr/bin/env python3

import socket
import sys

if len(sys.argv) < 2:
    print(f'Usage: {sys.argv[0]} <port>', file=sys.stderr)
    exit(1)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sck:
    sck.bind(('0.0.0.0', int(sys.argv[1])))
    sck.listen()

    while True:
        conn, addr = sck.accept()
        print(f'Incoming connection from {addr}:\n')
        while (data := conn.recv(10)):
            print(data.decode(), end='')
        print('\n\nConnection closed\n')