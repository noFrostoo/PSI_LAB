#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void error(int err, const char* msg);

void errorf(int err, const char* msg, ...);

void assert(bool cond, const char* msg, ...);

struct sockaddr_in parse_addr(const char* addr, const char* port);
