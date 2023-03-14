#pragma once

#include "board.h"
#include "constants.h"
#include <arpa/inet.h> //close
#include <chrono>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <sys/types.h>
#include <thread>
#include <unistd.h> //close

void *startGameClock(void *);
void handleSocket();
