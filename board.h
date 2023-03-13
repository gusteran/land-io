#ifndef __BOARD__
#define __BOARD__

#include "constants.h"
#include "player.h"
#include "tile.h"
#include <algorithm>
#include <vector>

class Board {
  public:
    Board();
    bool update();

  private:
    Tile field[ROWS][COLS];
    std::vector<Player *> players;
};

#endif
