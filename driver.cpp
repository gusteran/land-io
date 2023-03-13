#include "driver.h"

int startGameClock() {
    auto start = std::chrono::steady_clock::now();
    Board board;
    short botId = 1;
    int ticks = 0;
    while (1) {
        std::cout << std::endl;

        auto end = std::chrono::steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                .count();
        std::cout << "Running board update at " << time << " ms" << std::endl;

        std::string name = "Bot" + std::to_string(botId);
        Player *player = new Bot(botId++, name);

        bool res = board.addBot(player);
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

        ticks++;
        end = std::chrono::steady_clock::now();
        time =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                .count();

        time -= ticks * SLEEP_TIME;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(SLEEP_TIME - time));
    }
    return 0;
}
