#if 0
TMP=$(mktemp -d)
gcc -o $TMP/a.out $0 utils.c && $TMP/a.out $@ ; RV=$?
rm -rf $TMP
exit $RV
#endif

#include "utils.h"
#include <time.h>

// czas zwracany przez clock() najwyraźniej nie płynie,
// gdy wątek jest zablokowany
double time_now() {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec * 1e-9;
}

int main(int argc, char** argv) {
    // weryfikacja odpowiedniej liczby argumentów
    assert(argc >= 3, "Usage: %s <addr-or-domain> <port>\n", argv[0]);

    // stworzenie gniazda
    int sck = socket(AF_INET, SOCK_STREAM, 0);
    error(sck, "socket failed");
    struct sockaddr_in addr = parse_addr(argv[1], argv[2]);

    // połączenie sie z serwerem
    int err = connect(sck, (struct sockaddr*) &addr, sizeof(addr));
    error(err, "connect failed");

    char data[16 * 1024];
    char fillchar = 'a';
    int i = 0;

    while (1) {
        // wygenerowanie bufora z danymi
        memset(data, fillchar, sizeof(data));
        fillchar = (fillchar - 'a' + 1) % 26 + 'a';

        // wysłanie danych i sprawdzenie, ile zajęło to czasu
        double start = time_now();
        ssize_t len = send(sck, data, sizeof(data), 0);
        double end = time_now();

        error(len, "send failed");
        // wypisanie informacji o czasie wysyłania bufora danych
        printf("sending buffer #%d took %.2f ms\n", i, (end - start) * 1000);
        i++;
    }

    close(sck);
}