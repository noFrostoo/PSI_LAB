#if 0
TMP=$(mktemp -d)
gcc -o $TMP/a.out $0 utils.c && $TMP/a.out $@ ; RV=$?
rm -rf $TMP
exit $RV
#endif

#include "utils.h"

int main(int argc, char** argv) {
    // weryfikacja odpowiedniej ilości argumentów
    assert(argc >= 2, "Usage: %s <port>\n", argv[0]);

    // stworzenie gniazda
    int sck = socket(AF_INET, SOCK_STREAM, 0);
    error(sck, "socket failed");
    struct sockaddr_in addr = parse_addr("0.0.0.0", argv[1]);

    // powiązanie gniazda z portem
    int err = bind(sck, (struct sockaddr*) &addr, sizeof(addr));
    error(err, "bind failed");

    // ustawienie gniazda w tryb nasłuchiwania
    err = listen(sck, 0);
    error(err, "listen failed");

    while (1) {
        // zaakceptowanie połączenia od klienta
        int conn = accept(sck, NULL, NULL);
        error(conn, "accept failed");
        puts("Incoming connection:\n");

        char buf[1024];
        ssize_t len;
        // odbieranie danych w pętli i wypisywanie do konsoli
        while ((len = recv(conn, buf, sizeof(buf), 0)) > 0) {
            fwrite(buf, sizeof(char), len, stdout);
        }

        close(conn);
        puts("\n\nConnection closed\n");
    }

    close(sck);
}