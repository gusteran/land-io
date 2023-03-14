#include "driver.h"
#include <pthread.h>
#include <unistd.h>

int main(void) {
    pthread_t p;
    auto err = pthread_create(&p, NULL, startGameClock, NULL);
    if (err) {
        std::cerr << "Couldn't create thread!" << std::endl;
    }
    handleSocket();
}
