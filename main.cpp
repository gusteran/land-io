#include "driver.h"
#include <signal.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t ppid_before_fork, pid;

    ppid_before_fork = getpid();
    pid = fork();
    if (pid == -1)
        std::cerr << "bad fork!" << std::endl;
    if (!pid) { // in child process...
        int r = prctl(PR_SET_PDEATHSIG, SIGTERM);

        if (r == -1)
            std::cerr << "parent process exited before prctl..." << std::endl;
        if (getppid() != ppid_before_fork)
            std::cerr << "child process was adopted. not continuing..."
                      << std::endl;

        startGameClock();
    }
    for (int i = 0; i < 10; i++) {
        std::cout << "awaiting anything" << std::endl;
        sleep(1);
    }
}