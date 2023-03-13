#pragma once

#include "player.h"

class Bot : public Player {
  public:
    Bot(short id, std::string name);
    ~Bot();
    MoveResult update(Tile (&field)[ROWS][COLS]);

  private:
    void pickMove(Tile (&field)[ROWS][COLS]);
    bool facingTrail(Tile (&field)[ROWS][COLS]);
    MoveResult move(Tile (&field)[ROWS][COLS]);
    std::vector<Direction> directions = {EAST, EAST, WEST, WEST, WEST, WEST};
};