#include "driver.h"

int startGameClock() {
    auto start = std::chrono::steady_clock::now();
    Board board;
    short botId = 1;
    while (1) {
        std::cout << std::endl;

        auto end = std::chrono::steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                .count();
        std::cout << "Running board update at " << time << " ms" << std::endl;

        Player * player = new Bot(botId++, "player"+botId);

        bool res = board.spawnPlayer(player);
        std::cout << res << std::endl;

        if (time > GAME_DURATION) {
            std::cout << "Game Over!\n";
            return 0;
        }

        if (!board.update()) {
            std::cout << "Board update failed\n";
            return -1;
        }

        board.printBoard();

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    }
    return 0;
}
