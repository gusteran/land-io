#pragma once

#include "bot.h"
#include "constants.h"
#include "player.h"
#include "tile.h"
#include <algorithm>
#include <random>
#include <vector>

class Board {
  public:
    Board();
    bool update();
    void printBoard();
    bool spawnPlayer(Player *player);
    bool killPlayer(Player *player);
    bool completeTerritory(Player *player);

  private:
    Tile field[ROWS][COLS];
    std::vector<Player *> players;
    std::vector<std::pair<int, int>> spawnLocations;
    int currentSpawnLocation = 0;

    void generateSpawnLocation();
};
