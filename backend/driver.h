#pragma once

#include "board.h"
#include "constants.h"
#include <arpa/inet.h> //close
#include <chrono>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
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

const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string base64_encode(const unsigned char *input, size_t input_length) {
    std::string output;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    for (size_t k = 0; k < input_length; k++) {
        char_array_3[i++] = input[k];
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
                              ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
                              ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++) {
                output += base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] =
            ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] =
            ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; j < i + 1; j++) {
            output += base64_chars[char_array_4[j]];
        }

        while (i++ < 3) {
            output += '=';
        }
    }

    return output;
}
