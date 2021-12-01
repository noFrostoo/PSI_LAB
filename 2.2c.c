#if 0
TMP=$(mktemp -d)
gcc -o $TMP/a.out $0 utils.c && $TMP/a.out $@ ; RV=$?
rm -rf $TMP
exit $RV
#endif

#include "utils.h"

// dane do wysłania
char data[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";

int main(int argc, char** argv) {
    // weryfikacja odpowiedniej liczby argumentów
    assert(argc >= 3, "Usage: %s <addr-or-domain> <port>\n", argv[0]);

    // stworzenie gniazda
    int sck = socket(AF_INET, SOCK_STREAM, 0);
    error(sck, "socket failed");
    struct sockaddr_in addr = parse_addr(argv[1], argv[2]);

    // połączenie się z serwerem i wysłanie danych
    int err = connect(sck, (struct sockaddr*) &addr, sizeof(addr));
    error(err, "connect failed");
    ssize_t len = send(sck, data, sizeof(data), 0);
    error(len, "send failed");

    close(sck);
}