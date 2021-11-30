#!/usr/bin/env python3

import socket
import sys

# weryfikacja odpowiedniej ilości argumentów
if len(sys.argv) < 2:
    print(f'Usage: {sys.argv[0]} <port>', file=sys.stderr)
    exit(1)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sck:
    # powiązanie gniazda z portem
    sck.bind(('0.0.0.0', int(sys.argv[1])))
    # ustawienie gniazda w tryb nasłuchiwania
    sck.listen()

    while True:
        # zaakceptowanie połączenia od klienta
        conn, addr = sck.accept()
        print(f'Incoming connection from {addr}:\n')

        with conn:
            # odbieranie i wypisywanie danych w pętli
            while (data := conn.recv(10)):
                print(data.decode(), end='')

        print('\n\nConnection closed\n')