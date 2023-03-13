#pragma once

#include "bot.h"
#include "constants.h"
#include "player.h"
#include "tile.h"
#include <algorithm>
#include <queue>
#include <random>
#include <vector>

class Board {
  public:
    Board();
    bool update();
    void printBoard();
    bool addBot(Player *player);
    bool spawnPlayer(Player *player);
    bool killPlayer(Player *player);
    bool completeTerritory(Player *player);
    std::vector<std::pair<int, int>> getNeighbors(std::pair<int, int> location);
    bool checkConcavity(Player *player, std::pair<int, int> location);
    bool fillTerritory(Player *player, std::pair<int, int> location);
    bool isInBounds(std::pair<int, int> location);
    bool againstWall(std::pair<int, int> location);

  private:
    Tile field[ROWS][COLS];
    std::vector<Player *> players;
    std::vector<std::pair<int, int>> spawnLocations;
    int currentSpawnLocation = 0;

    std::minstd_rand0 rng = std::default_random_engine{};
    void generateSpawnLocation();
};
