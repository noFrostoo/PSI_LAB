#if 0
TMP=$(mktemp -d)
gcc -o $TMP/a.out $0 utils.c && $TMP/a.out $@ ; RV=$?
rm -rf $TMP
exit $RV
#endif

#include "utils.h"

char data[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";

int main(int argc, char** argv) {
    assert(argc >= 3, "Usage: %s <addr-or-domain> <port>\n", argv[0]);

    int sck = socket(AF_INET, SOCK_STREAM, 0);
    error(sck, "socket failed");
    struct sockaddr_in addr = parse_addr(argv[1], argv[2]);

    int err = connect(sck, (struct sockaddr*) &addr, sizeof(addr));
    error(err, "connect failed");
    ssize_t len = send(sck, data, sizeof(data), 0);
    error(len, "send failed");

    close(sck);
}