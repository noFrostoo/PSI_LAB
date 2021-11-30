#if 0
TMP=$(mktemp -d)
gcc -o $TMP/a.out $0 utils.c && $TMP/a.out $@ ; RV=$?
rm -rf $TMP
exit $RV
#endif

#include "utils.h"

int main(int argc, char** argv) {
    assert(argc >= 2, "Usage: %s <port>\n", argv[0]);

    int sck = socket(AF_INET, SOCK_STREAM, 0);
    error(sck, "socket failed");
    struct sockaddr_in addr = parse_addr("0.0.0.0", argv[1]);

    int err = bind(sck, (struct sockaddr*) &addr, sizeof(addr));
    error(err, "bind failed");
    err = listen(sck, 0);
    error(err, "listen failed");

    while (1) {
        int conn = accept(sck, NULL, NULL);
        error(conn, "accept failed");
        puts("Incoming connection:\n");
        char buf[1024];
        ssize_t len;
        while ((len = recv(conn, buf, sizeof(buf), 0)) > 0) {
            fwrite(buf, sizeof(char), len, stdout);
            usleep(10000);
        }
        puts("\n\nConnection closed\n");
    }

    close(sck);
}