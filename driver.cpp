#include "board.h"
#include "constants.h"
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <thread>

int main(int argc, char *argv[]) {
    Board board;
    while (1) {
        if (!board.update()) {
            std::cout << "Board update failed\n";
            return -1;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    }
    return 0;
}
