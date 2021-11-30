#include "utils.h"

void error(int err, const char* msg) {
    if (err < 0) {
        perror(msg);
        exit(errno);
    }
}

void errorf(int err, const char* msg, ...) {
    if (err < 0) {
        va_list args;
        va_start(args, msg);
        char* fmt = (char*) malloc(vsnprintf(NULL, 0, msg, args));
        vsprintf(fmt, msg, args);
        va_end(args);
        perror(fmt);
        free(fmt);
        exit(errno);
    }
}

void assert(bool cond, const char* msg, ...) {
    if (!cond) {
        va_list args;
        va_start(args, msg);
        vfprintf(stderr, msg, args);
        va_end(args);
        exit(1);
    }
}

struct sockaddr_in parse_addr(const char* addr, const char* port) {
    struct sockaddr_in result;
    struct hostent* hp = gethostbyname(addr);

    assert(hp != NULL, "unknown host: %s\n", addr);

    int port_i = atoi(port);
    assert(0 < port_i && port_i <= 65535, "invalid port number: %s\n", port);

    result.sin_family = AF_INET;
    memcpy((char*) &result.sin_addr, hp->h_addr_list[0], hp->h_length);
    result.sin_port = htons(port_i);

    return result;
}