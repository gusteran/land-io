#pragma once

#include "player.h"

class Bot : public Player {
  public:
    Bot(short id, std::string name);
    ~Bot();
    bool update(Tile (&field)[ROWS][COLS]);

  private:
    void pickMove(Tile (&field)[ROWS][COLS]);
    bool facingTrail(Tile (&field)[ROWS][COLS]);
    bool move(Tile (&field)[ROWS][COLS]);
};